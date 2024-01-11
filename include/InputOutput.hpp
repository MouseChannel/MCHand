#pragma once
#include "torch/script.h"
#include <vector>
#include <memory>
#include "opencv2/opencv.hpp"
#include <NvInfer.h>

namespace mchand
{
    class InputOutput
    {
    public:
        static void Init(std::shared_ptr<nvinfer1::ICudaEngine> engine);
        static void Set_input(std::vector<float> input_data, std::string input_name = "input");
        static void Set_input(torch::Tensor& input_data, std::string input_name = "input");
        static void Set_input(cv::Mat& input_img, std::string input_name = "input");
        static void CopyBufferHost2Device();
        static void CopyBufferDevice2Host();

        static std::vector<void*> hostBuffer;
        static std::vector<void*> deviceBuffer;
        static std::vector<size_t> buffer_size;

    private:
        static void create_host_device_buffer(std::shared_ptr<nvinfer1::ICudaEngine> engine);
        static void memcpyBuffers(bool copyInput, const bool deviceToHost);
        static std::shared_ptr<nvinfer1::ICudaEngine> mEngine;
    };
}
