#include "MCHand.hpp"
#include <iostream>
#include "PreProcess.hpp"


int main()
{
    using namespace mchand;
    auto origin_image1 = cv::imread("/home/mocheng/project/MCHand/me.jpg",
                                    cv::IMREAD_IGNORE_ORIENTATION | cv::IMREAD_COLOR);
    auto input_mat = PreProcess::processInput_img(origin_image1);

    MCHand m;
    m.Init("/home/mocheng/project/RECONSTRCUT/InterWild/demo/mochengres.onnx");
    m.Set_input_name("input");
    m.Set_output_name("joint_img");
    m.Infer(input_mat);
    auto d = m.Get_Output<float>();
    return 0;
}
