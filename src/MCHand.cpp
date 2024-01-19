#include "MCHand.hpp"

#include <Engine.hpp>
#include <InputOutput.hpp>
#include "PreProcess.hpp"

namespace mchand
{
    MCHand::MCHand()
    {
    }

    void MCHand::Init(std::string onnx_path)
    {
        mEngine.reset(new Engine(onnx_path));
        input_output.reset(new InputOutput);
        input_output->Init(mEngine->get_handle());
    }

    void MCHand::Set_input_name(std::string input_name)
    {
        input_output->Set_input_name(input_name);
    }

    void MCHand::Set_output_name(std::string output_name)
    {
        input_output->Set_output_name(std::move(output_name));
    }

    void MCHand::Infer(std::vector<float>& raw_data, int height, int width)
    {
        auto dst_img = cv::Mat(height, width,CV_32FC3, raw_data.data());
        auto fixed_img = PreProcess::processInput_img(dst_img);
       
        Infer(fixed_img);
    }

    void MCHand::Infer(float* raw_data, int height, int width)
    {
        auto dst_img = cv::Mat(height, width,CV_32FC3, raw_data );
        // cv::cvtColor(dst_img, dst_img, cv::COLOR_BGR2RGB);
         
       
        auto fixed_img = PreProcess::processInput_img(dst_img);
       
        Infer(fixed_img);
    }

    // void MCHand::Infer(torch::Tensor& input_image)
    // {
    //     input_output->Set_input_data(input_image);
    //     input_output->CopyBufferHost2Device();
    //
    //     bool state = mEngine->infer(input_output);
    //     assert(state);
    //     input_output->CopyBufferDevice2Host();
    // }
}
