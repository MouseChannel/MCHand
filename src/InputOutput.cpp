//
// Created by mocheng on 1/11/24.
//
#include "InputOutput.hpp"
#include "torch/script.h"
#include <memory>
#include <numeric>
#include <stdexcept>
#include <utility>


namespace mchand
{
    void InputOutput::Init(std::shared_ptr<nvinfer1::ICudaEngine> engine)
    {
        mEngine = engine;
        auto input_and_output_size = engine->getNbIOTensors();
        hostBuffer.resize(input_and_output_size);
        deviceBuffer.resize(input_and_output_size);
        buffer_size.resize(input_and_output_size);
        create_host_device_buffer(engine);
    }

    void InputOutput::Set_input(torch::Tensor &input_data, std::string input_name)
    {
        auto input_index = mEngine->getBindingIndex(input_name.c_str());
        memcpy(hostBuffer[input_index], input_data.data_ptr<float>(), input_data.numel() * sizeof(float));
    }

    void InputOutput::Set_input(cv::Mat& input_img, std::string input_name)
    {
        int height = input_img.rows;
        int width = input_img.cols;
        int channels = input_img.channels();
        auto options = torch::TensorOptions().dtype(torch::kFloat32).device(torch::kCPU);
        torch::Tensor tensor_image = torch::from_blob(input_img.data, {height, width, channels}, options);
        tensor_image = tensor_image.permute({2, 0, 1});
        tensor_image = tensor_image.contiguous();
        tensor_image = tensor_image.unsqueeze(0);
        Set_input(tensor_image, std::move(input_name));
    }

    void InputOutput::CopyBufferHost2Device()
    {
        memcpyBuffers(true, false);
    }

    void InputOutput::CopyBufferDevice2Host()
    {
        memcpyBuffers(false, true);
    }

    void InputOutput::create_host_device_buffer(std::shared_ptr<nvinfer1::ICudaEngine> mEngine)
    {
        for (int i = 0; i < mEngine->getNbIOTensors(); i++)
        {
            auto dims = mEngine->getBindingDimensions(i);
            size_t vol = 1;

            int vecDim = mEngine->getBindingVectorizedDim(i);
            if (-1 != vecDim) // i.e., 0 != lgScalarsPerVector
            {
                int scalarsPerVec = mEngine->getBindingComponentsPerElement(i);

                dims.d[vecDim] = (dims.d[vecDim] + scalarsPerVec - 1) / scalarsPerVec;
                vol *= scalarsPerVec;
            }
            vol *= std::accumulate(dims.d, dims.d + dims.nbDims, int64_t{1}, std::multiplies<int64_t>{});
            buffer_size[i] = vol;
            if (cudaMalloc(&deviceBuffer[i], vol * 4) != cudaSuccess)
            {
                throw std::runtime_error("err cuda alloc");
            }
            hostBuffer[i] = malloc(vol * 4);
            if (hostBuffer[i] == nullptr)
            {
                throw std::runtime_error("err host alloc");
            }
        }
    }

    void InputOutput::memcpyBuffers(bool copyInput, const bool deviceToHost)
    {
        for (int i = 0; i < mEngine->getNbIOTensors(); i++)
        {
            void* dstPtr
                = deviceToHost ? hostBuffer[i] : deviceBuffer[i];
            const void* srcPtr
                = deviceToHost ? deviceBuffer[i] : hostBuffer[i];
            const size_t byteSize = buffer_size[i] * sizeof(float);
            const cudaMemcpyKind memcpyType = deviceToHost ? cudaMemcpyDeviceToHost : cudaMemcpyHostToDevice;
            if ((copyInput && mEngine->bindingIsInput(i)) || (!copyInput && !mEngine->bindingIsInput(i)))
            {
                auto res = cudaMemcpy(dstPtr, srcPtr, byteSize, memcpyType);
                if (res != cudaSuccess)
                {
                    throw std::runtime_error("copy fail");
                }
            }
        }
    }
}
