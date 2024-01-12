#pragma once
#include "opencv2/opencv.hpp"

namespace mchand
{
    class PostProcess
    {
    public:
        static  void vis_joint(std::vector<float> joint_point, cv::Mat& output_img);
    };
}
