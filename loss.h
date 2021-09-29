//
// Created by explore on 2021/9/29.
//

#ifndef CABLE_V1_LOSS_H
#define CABLE_V1_LOSS_H


#include <string>
// For External Library
#include <torch/torch.h>


// -----------------------------------
// class{Loss}
// -----------------------------------
class Loss{
private:
    int judge;
    float ideal;
public:
    Loss(){}
    Loss(const std::string loss);
    torch::Tensor operator()(torch::Tensor &input, torch::Tensor &target);
    float ideal_value();
};


#endif //CABLE_V1_LOSS_H
