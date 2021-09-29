//
// Created by explore on 2021/8/21.
//

#include "camera.h"
Camera::Camera() {
    MV_CC_DEVICE_INFO_LIST stDeviceList;
    memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
    nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
    if (MV_OK != nRet)
    {
        printf("Enum Devices fail! nRet [0x%x]\n", nRet);
        exit(0);
        //        return 0 ;
    }
    cout<<"net"<<endl;
    if (stDeviceList.nDeviceNum > 0)
    {
        cout<<"net: "<<stDeviceList.nDeviceNum<<endl;

        for (unsigned int i = 0; i < stDeviceList.nDeviceNum; i++)
        {
            printf("[device %d]:\n", i);
            MV_CC_DEVICE_INFO* pDeviceInfo = stDeviceList.pDeviceInfo[i];
            if (nullptr == pDeviceInfo)
            {
                exit(0);

                //                return 0 ;
            }
            PrintDeviceInfo(pDeviceInfo);
        }
    }else
    {
        exit(0);

        printf("Find No Devices!\n");
        //        break;
    }

    unsigned int nIndex = 0;
    nRet = MV_CC_CreateHandle(&handle, stDeviceList.pDeviceInfo[nIndex]);
    if (MV_OK != nRet)
    {
        printf("MV_CC_CreateHandle fail! nRet [%x]\n", nRet);
        //        break;
        exit(0);

    }
    nRet = MV_CC_OpenDevice(handle);

    if (MV_OK != nRet)
    {
        printf("MV_CC_OpenDevice fail! nRet [%x]\n", nRet);
        exit(0);

        //        break;
    }
    nRet = MV_CC_SetEnumValue(handle, "TriggerMode", 0);
    nRet = MV_CC_SetEnumValue(handle, "PixelFormat", PixelType_Gvsp_BGR8_Packed);
    if (MV_OK != nRet)
    {
        printf("MV_CC_SetTriggerMode fail! nRet [%x]\n", nRet);
        exit(0);

        //        break;
    }
    MVCC_INTVALUE stParam;
    memset(&stParam, 0, sizeof(MVCC_INTVALUE));
    nRet = MV_CC_GetIntValue(handle, "PayloadSize", &stParam);
    if (MV_OK != nRet)
    {
        printf("Get PayloadSize fail! nRet [0x%x]\n", nRet);
        exit(0);

        //        return 0;
    }
    cout<<"grab"<<endl;
    g_nPayloadSize = stParam.nCurValue;

    // Start grab image
    nRet = MV_CC_StartGrabbing(handle);
    if (MV_OK != nRet)
    {
        printf("Start Grabbing fail! nRet [0x%x]\n", nRet);
        exit(0);

        //        return 0;
    }

    stImageInfo = {0};
    memset(&stImageInfo, 0, sizeof(MV_FRAME_OUT_INFO_EX));
    pData = (unsigned char *)malloc(sizeof(unsigned char) * (g_nPayloadSize));
    if (pData == nullptr)
    {
        printf("Allocate memory failed.\n");
        exit(0);
    }
}

bool Camera::PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo)
{
    cout<<"print device info"<<pstMVDevInfo->nTLayerType<<endl;
    if (nullptr == pstMVDevInfo)
    {
        printf("The Pointer of pstMVDevInfo is NULL!\n");
        exit(0);

        return false;
    }
    if (pstMVDevInfo->nTLayerType == MV_GIGE_DEVICE)
    {
        int nIp1 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
        int nIp2 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
        int nIp3 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
        int nIp4 = (pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

        // print current ip and user defined name
        printf("CurrentIp: %d.%d.%d.%d\n" , nIp1, nIp2, nIp3, nIp4);
        printf("UserDefinedName: %s\n\n" , pstMVDevInfo->SpecialInfo.stGigEInfo.chUserDefinedName);
    }
    else if (pstMVDevInfo->nTLayerType == MV_USB_DEVICE)
    {

        printf("UserDefinedName: %s\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName);
        printf("Serial Number: %s\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chSerialNumber);
        printf("Device Number: %d\n\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.nDeviceNumber);
    }
    else
    {
        printf("Not support.\n");
        exit(0);

    }

    return true;
}
Mat Camera::readFrame()
{
    nRet = MV_CC_GetOneFrameTimeout(handle, pData, g_nPayloadSize, &stImageInfo, frequency);
    if (nRet == MV_OK)
    {
        //        printf("Get One Frame: Width[%d], Height[%d], nFrameNum[%d]\n",
        //               stImageInfo.nWidth, stImageInfo.nHeight, stImageInfo.nFrameNum);
    }
    else
    {
        printf("No data[0x%x]\n", nRet);
        free(pData);
        pData = nullptr;
        exit(0);

    }


    bool bConvertRet = false;
    srcImage = cv::Mat(stImageInfo.nHeight, stImageInfo.nWidth, CV_8UC3, pData);

    return srcImage;

}
Camera::~Camera()
{
    nRet = MV_CC_StopGrabbing(handle);
    nRet = MV_CC_CloseDevice(handle);
    nRet = MV_CC_DestroyHandle(handle);
}