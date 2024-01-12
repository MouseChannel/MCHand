#include "MCHand.hpp"

#include <Engine.hpp>
#include <InputOutput.hpp>

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
