//
// Created by explore on 2021/8/18.
//

#include "datasets.h"
ImageFolderWithPaths::ImageFolderWithPaths(const std::string& root, std::vector<transforms_Compose> &transform_A_,std::vector<transforms_Compose> &transform_B_)
{
//    mycollect(root);

    QString path = QString::fromStdString(root);
    QDir file_dir(path);

    QStringList filters;
    filters << QString("*.png");


    file_dir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
    file_dir.setNameFilters(filters);                   //设置文件名称过滤器，只为filters格式
    int dirCount = file_dir.count();

    QStringList stringList;
    for(int i=0; i<dirCount; i++) {
        QString filName = file_dir[i];
        QString absolute_path = path +"/" +filName;
//        cout << absolute_path.toStdString()<<endl;
        paths.push_back(absolute_path.toStdString());
    }
//    file_dir.setFilter(QDir::Files);
//    QStringList nameFilters;
//    nameFilters << "*.jpg" << "*.png";
//    QStringList files = file_dir.entryInfoList(nameFilters,QDir::Files|QDir::Readable, QDir::Name);
//    paths = {
//            "/home/explore/Data/origin/39739.png",
//            "/home/explore/Data/origin/39740.png",
//            "/home/explore/Data/origin/39741.png",
//            "/home/explore/Data/origin/39739.png",
//            "/home/explore/Data/origin/39740.png",
//            "/home/explore/Data/origin/39741.png",
//            "/home/explore/Data/origin/39739.png",
//            "/home/explore/Data/origin/39740.png",
//            "/home/explore/Data/origin/39741.png",
//            "/home/explore/Data/origin/39739.png",
//            "/home/explore/Data/origin/39740.png",
//            "/home/explore/Data/origin/39741.png",
//            "/home/explore/Data/origin/39739.png",
//            "/home/explore/Data/origin/39740.png",
//            "/home/explore/Data/origin/39741.png",
//
//
//    };
    fnames = paths;
//    std::cout<<"collect end"<<std::endl;
//    collect(root);
    std::sort(this->paths.begin(), this->paths.end());
//    std::cout<<"sort end"<<std::endl;
//
    std::sort(this->fnames.begin(), this->fnames.end());
//    std::cout<<" sort fnames end"<<std::endl;

    this->transform_A = transform_A_;
    this->transform_B = transform_B_;

//    std::cout<<"imagefolder end"<<std::endl;
}


void ImageFolderWithPaths::mycollect(const std::string& root){
    fs::path ROOT(root);
    for (auto &p : fs::directory_iterator(ROOT)){
        if (!fs::is_directory(p)){
            std::stringstream rpath, fname;
            rpath << p.path().string();
            fname << p.path().filename().string();
            paths.push_back(rpath.str());
            fnames.push_back(rpath.str());
            std::cout<<"rpath: "<<rpath.str()<<std::endl;
            std::cout<<"fname: "<<fname.str()<<std::endl;


        }
//        else{
//
//            std::stringstream subsub;
//            subsub << p.path().filename().string();
//            ImageFolderWithPaths::collect(root + '/' + subsub.str(), sub + subsub.str() + '/', paths, fnames);
//        }
        std::cout<<"for end: "<<std::endl;

    }
    std::cout<<"end end: "<<std::endl;

//    return 0;
}


// -------------------------------------------------------------------------
// namespace{datasets} -> class{ImageFolderWithPaths} -> function{get}
// -------------------------------------------------------------------------
void ImageFolderWithPaths::ImageFolderWithPaths::get(const size_t idx, std::tuple<torch::Tensor,torch::Tensor, std::string, std::string> &data){
    cv::Mat image_Mat = ImageFolderWithPaths::RGB_Loader(this->paths.at(idx));
    Mat image_Mat_B = image_Mat.clone();
    torch::Tensor imageA = transforms::apply(this->transform_A, image_Mat);  // Mat Image ==={Resize,ToTensor,etc.}===> Tensor Image
    torch::Tensor imageB = transforms::apply(this->transform_B, image_Mat_B);  // Mat Image ==={Resize,ToTensor,etc.}===> Tensor Image

    std::string fname = this->fnames.at(idx);
    data = {imageA.detach().clone(),imageB.detach().clone(),fname, fname};
    return;
}


// -------------------------------------------------------------------------
// namespace{datasets} -> class{ImageFolderWithPaths} -> function{size}
// -------------------------------------------------------------------------
size_t ImageFolderWithPaths::ImageFolderWithPaths::size(){
    return this->fnames.size();
}
cv::Mat ImageFolderWithPaths::RGB_Loader(std::string &path){
    cv::Mat BGR, RGB;
    BGR = cv::imread(path, cv::IMREAD_COLOR | cv::IMREAD_ANYDEPTH);  // path ===> color image {B,G,R}
    if (BGR.empty()) {
        std::cerr << "Error : Couldn't open the image '" << path << "'." << std::endl;
        std::exit(1);
    }
    cv::cvtColor(BGR, RGB, cv::COLOR_BGR2RGB);  // {0,1,2} = {B,G,R} ===> {0,1,2} = {R,G,B}
    return RGB.clone();
}

int ImageFolderWithPaths::collect(const std::string& path_) {
    fs::path path(path_);
    if (!fs::exists(path))
    {
        return -1;
    }

    fs::directory_iterator end_iter;
    for (fs::directory_iterator iter(path); iter!=end_iter; ++iter)
    {
    if (fs::is_regular_file(iter->status()))
    {
        paths.push_back(iter->path().string());
        std::cout<<"files: "<<iter->path().string()<<std::endl;
    }

//    if (fs::is_directory(iter->status()))
//    {
//        get_filenames(iter->path().string(), filenames);
//    }
    }

    return paths.size();
}
