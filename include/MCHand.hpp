#pragma once
#include <InputOutput.hpp>
#include "Engine.hpp"
#include <memory>
#include <utility>
#include <torch/script.h>


namespace mchand
{
    class Engine;
     

    class MCHand
    {
    public:
        MCHand();
        ~MCHand() = default;
        void Init(std::string onnx_path);
        void Set_input_name(std::string input_name);
        void Set_output_name(std::string output_name);
        // void Infer(torch::Tensor& input_image);

        template <typename T>
        void Infer(T& input_data)
        {
            input_output->Set_input_data(input_data);
            input_output->CopyBufferHost2Device();

            bool state = mEngine->infer(input_output);
            assert(state);
            input_output->CopyBufferDevice2Host();
        }

        // template <typename T>
        // std::vector<T> Get_Output(std::string output_name)
        // {
        //     return input_output->Get_output(std::move(output_name));
        // }

        template <typename T = float>
        std::vector<T> Get_Output()
        {
            auto rawData = input_output->Get_output_data();
            std::vector<T> data(input_output->get_output_buffer_size());
            memcpy(data.data(), rawData, data.size() * sizeof(T));
            return data;
        }

    private:
        std::shared_ptr<Engine> mEngine;
        std::shared_ptr<InputOutput> input_output;
    };
}
