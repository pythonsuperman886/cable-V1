//
// Created by explore on 2021/8/21.
//

#ifndef CABLE_V1_CAMERA_H
#define CABLE_V1_CAMERA_H
#include "common.h"

class Camera {
public:
    Camera();
    ~Camera() ;
    bool PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo);
    Mat readFrame();

private:
    int nRet = MV_OK;
    void* handle = nullptr;
    MV_FRAME_OUT_INFO_EX stImageInfo;
    unsigned char * pData ;
    int g_nPayloadSize;
    int frequency;
    Mat srcImage;
};


#endif //CABLE_V1_CAMERA_H
