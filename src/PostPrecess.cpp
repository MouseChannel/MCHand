#include "PostPrecess.hpp"
#include "torch/script.h"
#include "PreProcess.hpp"
#include "MANO.hpp"

void mchand::PostProcess::vis_joint(std::vector<float> joint_point, cv::Mat& output_img)
{
    auto trans = PreProcess::Get_output_trans(output_img.cols, output_img.rows);
    trans.convertTo(trans,CV_32F);

    torch::Tensor trans_tensor = torch::from_blob(trans.data, {2, 3},
                                                  torch::TensorOptions().dtype(torch::kFloat32).device(torch::kCPU));
    torch::Tensor joint_point_tensor = torch::from_blob(joint_point.data(), {21, 3}, torch::dtype(torch::kFloat32));
    auto joint_img_xy1 = torch::cat({
                                        joint_point_tensor.slice(1, 0, 2),
                                        torch::ones_like(joint_point_tensor.slice(1, 0, 1))
                                    }, 1);
    auto joint_img = torch::matmul(trans_tensor, joint_img_xy1.transpose(1, 0)).transpose(1, 0);
    joint_img = joint_img.contiguous();

    
    std::vector<float> vector_tensor(joint_img.data_ptr<float>(), joint_img.data_ptr<float>() + joint_img.numel());
    cv::Scalar color{255};
    for (auto i : skeleton)
    {
        auto i1 = i.first;
        auto i2 = i.second;
        auto p11 = vector_tensor[i1 * 2];
        auto p12 = vector_tensor[i1 * 2 + 1];
        auto p21 = vector_tensor[i2 * 2];
        auto p22 = vector_tensor[i2 * 2 + 1];
    
        cv::line(output_img, {(int)p11, (int)p12}, {(int)p21, (int)p22}, color, 2, cv::LINE_AA);
        cv::circle(output_img, {(int)p11, (int)p12}, 3, color, -1, cv::LINE_AA);
        cv::circle(output_img, {(int)p21, (int)p22}, 3, color, -1, cv::LINE_AA);
    }
}
