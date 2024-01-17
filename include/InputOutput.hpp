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
        InputOutput() = default;
        ~InputOutput() = default;
        void Init(std::shared_ptr<nvinfer1::ICudaEngine> engine);
        void Set_input_name(std::string input_name = "input");
        void Set_input_data(std::vector<float> raw_img);
        //example shape(1,3,512,384)
        void Set_input_data(torch::Tensor& input_data);
        // void Set_input_data(void* input_data);
        void Set_input_data(cv::Mat& input_img);
        void Set_output_name(std::string output_name);
        void CopyBufferHost2Device();
        void CopyBufferDevice2Host();

        // void* Get_output(std::string output_name)
        // {
        //     output_index = mEngine->getBindingIndex(output_name.c_str());
        //     return Get_output();
        // }

        void* Get_output_data(std::string output_name)
        {
            // assert(output_index>=0);
            return hostBuffer[outputs[output_name]];
        }


        [[nodiscard]] auto& get_deviceBuffer()
        {
            return deviceBuffer;
        }

        auto get_output_buffer_size(std::string output_name)
        {
            return buffer_size[outputs[output_name]];
        }

        std::vector<void*> hostBuffer;
        std::vector<void*> deviceBuffer;
        std::vector<size_t> buffer_size;
        int32_t input_index = -1;
        // int32_t output_index = -1;
        std::unordered_map<std::string, int> outputs;

    private:
        void create_host_device_buffer(std::shared_ptr<nvinfer1::ICudaEngine> engine);
        void memcpyBuffers(bool copyInput, const bool deviceToHost);
        std::shared_ptr<nvinfer1::ICudaEngine> mEngine;
    };
}
