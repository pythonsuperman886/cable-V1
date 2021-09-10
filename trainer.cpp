//
// Created by explore on 2021/8/21.
//

#include "trainer.h"

#include <utility>

Trainer::Trainer():cuda_available(torch::cuda::is_available()),
                device(Device( cuda_available? torch::kCUDA : torch::kCPU)),
                G(UNet_Generator(1,1)),
                D(PatchGAN_Discriminator(1,1,64)),
                optimizer_D(torch::optim::Adam(D->parameters(), torch::optim::AdamOptions(learning_rate))),
                optimizer_G(torch::optim::Adam(G->parameters(), torch::optim::AdamOptions(learning_rate))),
                criterion_GAN(torch::nn::MSELoss(torch::nn::MSELossOptions().reduction(torch::kMean))),
                criterion_L1(torch::nn::L1Loss(torch::nn::L1LossOptions().reduction(torch::kMean)))


{
//    device =  Device(cuda_available ? torch::kCUDA : torch::kCPU);
    std::cout << (cuda_available ? "CUDA available. Training on GPU." : "Training on CPU.") << '\n';


    transform_A={
        transforms_Grayscale(1),
        transforms_Resize(Size(image_resize_num, image_resize_num), cv::INTER_LINEAR),  // {IH,IW,C} ===method{OW,OH}===> {OH,OW,C}
        transforms_Defect(thickiness,min,max),
        transforms_ToTensor(),                                                                            // Mat Image [0,255] or [0,65535] ===> Tensor Image [0,1]
        transforms_Normalize(0.5, 0.5)                                                         // [0,1] ===> [-1,1]
    };

    transform_B={
        transforms_Grayscale(1),
        transforms_Resize(Size(image_resize_num, image_resize_num), cv::INTER_LINEAR),  // {IH,IW,C} ===method{OW,OH}===> {OH,OW,C}
        transforms_Defect(thickiness,min,max,true),
        transforms_ToTensor(),                                                                            // Mat Image [0,255] or [0,65535] ===> Tensor Image [0,1]
        transforms_Normalize(0.5, 0.5)                                                         // [0,1] ===> [-1,1]
    };



//    G = UNet_Generator(1,1);
//    D = PatchGAN_Discriminator(1,1,64);
    D->to(device);
    G->to(device);


    criterion_GAN->to(device);

}
void Trainer::train() {
    for (size_t epoch = 0; epoch != num_epochs; ++epoch) {


        QCoreApplication::processEvents();


        //        auto real_A = torch::randn({batch_size, 1,128,128}).to(device);
        //        auto real_B = real_A;

        size_t batch_index = 0;
        auto real_labels = torch::ones({batch_size, 1}).to(device);
        auto fake_labels = torch::zeros({batch_size, 1}).to(device);
        while (dataloader(mini_batch)){
            QCoreApplication::processEvents();

            D->train();
            G->train();
            //
            auto real_A = std::get<0>(mini_batch).to(device);
            auto real_B = std::get<1>(mini_batch).to(device);



            int batch_size_data = real_A.size(0);
//            cout<<"batch_size_data: "<<batch_size_data<<endl;
            real_labels = torch::ones({batch_size_data, 1}).to(device);
            fake_labels = torch::zeros({batch_size_data, 1}).to(device);
            //
//            tm.reset();
//            tm.start();

            auto fake_B = G->forward(real_A);

//            tm.stop();

//            cout<<"time forward: "<<tm.getTimeMilli()<<endl;
//
            for(auto &i:D->parameters()){
                i.set_requires_grad(true);
            }

            optimizer_D.zero_grad();

            auto fake_AB = torch::cat({real_A, fake_B.detach()}, /*dim=*/1);

            auto pred_fake = D->forward(fake_AB.detach());
//            cout<<"pred_fake output: "<<pred_fake.sizes()<<endl;

            pred_fake = pred_fake.reshape({batch_size_data, -1});
//            cout<<"pred_fake reshape: "<<pred_fake.sizes()<<endl;

            //    cout<<"d out: "<<out.sizes()<<endl;
            loss_D_fake = criterion_GAN(pred_fake, fake_labels);
//            cout<<"fake_labels size: "<<fake_labels.sizes()<<endl;



            real_AB = torch::cat({real_A, real_B}, /*dim=*/1);
            pred_real = D->forward(real_AB);
            pred_real = pred_real.reshape({batch_size_data, -1});

            loss_D_real = criterion_GAN(pred_real, real_labels);

            loss_D = (loss_D_fake + loss_D_real)*0.5;
            loss_D.backward();
            optimizer_D.step();

            //set require grad D false `````````````````````````````````
            //            optimizer_D.zero_grad();
            //            for(auto param:D->parameters()){
            //                param.requirs_grad = false;
            //            }
            for(auto &i:D->parameters()){
                i.set_requires_grad(false);
            }
            optimizer_G.zero_grad();
            fake_AB = torch::cat({real_A, fake_B}, /*dim=*/1);
            pred_fake = D->forward(fake_AB);
            pred_fake = pred_fake.reshape({batch_size_data, -1});

            loss_G_GAN = criterion_GAN(pred_fake, real_labels);
            loss_G_L1 = criterion_L1(fake_B, real_B) * lambda_L1;
            loss_G = loss_G_GAN + loss_G_L1;
            loss_G.backward();
            optimizer_G.step();



            if ((batch_index + 1) % 2 == 0) {
//                log +=  "Epoch ["+;
//                log"ds";
                std::cout << "Epoch [" << epoch << "/" << num_epochs << "], Step [" << batch_index + 1 << "/"
                << num_samples / batch_size << "], d_loss: " << loss_D.item<double>() << ", g_loss: "
                << loss_G.item<double>()<<"\n";
                ofs << "Epoch [" << epoch << "/" << num_epochs << "], Step [" << batch_index + 1 << "/"
                << num_samples / batch_size << "], d_loss: " << loss_D.item<double>() << ", g_loss: "
                << loss_G.item<double>()<<"\n";
//
                ofs.flush();

            }
//            ofs.write()
            //            torch::save

            ++batch_index;
//            cout<<"real_A size: "<<real_A.sizes()<<endl;
            Mat A = Tensor2Mat(real_A);
            Mat B = Tensor2Mat(real_B);
            Mat C = Tensor2Mat(fake_B);
            Mat m = Mat(5, A.cols, CV_8UC1, Scalar(255));
            vector<Mat> ouputs={
                    A,m,B,m,C
            };


            vconcat(ouputs,combine);
            imwrite("../checkpoints/train_results/result-" + std::to_string(epoch) + ".png",combine);
//            result = denorm(result);
            //            save_image(real_A, sample_output_dir_path + "real_A-" + std::to_string(epoch + 1) + ".png");
            //
            //            fake_B = denorm(fake_B.reshape({fake_B.size(0), 1,128, 128}));
            //            save_image(fake_B, sample_output_dir_path + "fake_B-" + std::to_string(epoch + 1) + ".png");
//            save_image(result,  "result-" + std::to_string(epoch + 1) + ".png");
            transforms::DefectImpl::myseed++;
            transforms::DefectImpl::myseed = transforms::DefectImpl:: myseed %1000;
            if(!Is_continue_train){
//                Is_continue_train = true;
                cout<<"stop training..."<<endl;
                ofs<<"stop training..."<<endl;
                break;

            }
        }
        string path = "../checkpoints/model/epoch_latest_gen.pth";

        torch::save(G, path);
        if(!Is_continue_train){
            Is_continue_train = true;
            cout<<"stop training finished"<<endl;
            ofs<<"stop training finished"<<endl;
            break;

        }

    }
    ofs.close();
    std::cout << "Training finished!\n";
}
Trainer::~Trainer() {

}

void Trainer::init(string train_dir) {
    ofs.open( "../checkpoints/loss.txt", std::ios::out);
    if (ofs.fail()){
        cout<<"打开文件错误!"<<endl;

        exit(0);
    }

    input_dir=std::move(train_dir);
    dataset= ImageFolderWithPaths(input_dir, transform_A,transform_B);
    dataloader = Dataloader(dataset, batch_size, /*shuffle_=*/train_shuffle, /*num_workers_=*/train_workers);
    num_samples = dataset.size();
    cout<<"init train dir: "<<num_samples<<endl;
}

void Trainer::stop_train() {
    Is_continue_train = false;
}



