//
// Created by explore on 2021/8/18.
//

#ifndef CABLE_DEFECT_DETECT_QT_DATALOADER_H
#define CABLE_DEFECT_DETECT_QT_DATALOADER_H
#include "datasets.h"

class Dataloader {
    private:
        ImageFolderWithPaths dataset;
        size_t batch_size;
        bool shuffle;
        size_t num_workers;
        bool pin_memory;
        bool drop_last;
        size_t size;
        std::vector<size_t> idx;
        size_t count;
        size_t count_max;
        std::mt19937 mt;
    public:
        Dataloader(){};
        Dataloader(ImageFolderWithPaths &dataset_, const size_t batch_size_=1, const bool shuffle_=false, const size_t num_workers_=0, const bool pin_memory_=false, const bool drop_last_=false);
        bool operator()(std::tuple<torch::Tensor, torch::Tensor, std::vector<std::string>, std::vector<std::string>>  &data);
        void reset();
        size_t get_count_max();
    };


#endif //CABLE_DEFECT_DETECT_QT_DATALOADER_H
