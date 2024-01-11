#pragma once
#include <memory>
#include <torch/script.h>


namespace mchand
{
    class Engine;

    class MCHand
    {
    public:
        MCHand();
        ~MCHand();
        void Init(std::string onnx_path);
        void Set_input();
        void Infer(torch::Tensor input_image);
        

    private:
        std::shared_ptr<Engine> mEngine;
        
    };
}
