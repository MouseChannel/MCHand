#include "MCHand.hpp"
#include <iostream>
#include <PostPrecess.hpp>

#include "PreProcess.hpp"


int main()
{
    using namespace mchand;
    // auto origin_image1 = cv::imread("/home/mocheng/project/MCHand/me.jpg",
    //                                 cv::IMREAD_IGNORE_ORIENTATION | cv::IMREAD_COLOR);
    // auto input_mat = PreProcess::processInput_img(origin_image1);

    MCHand m;
    m.Init("/home/mocheng/project/RECONSTRCUT/InterWild/demo/mochengres.onnx");
    m.Set_input_name("input");
    m.Set_output_name("joint_img");

    cv::VideoCapture cap(0);

    // 检查摄像头是否成功打开
    if (!cap.isOpened())
    {
        std::cerr << "Error: Could not open the camera." << std::endl;
        return -1;
    }

    // 创建窗口
    cv::namedWindow("Camera", cv::WINDOW_NORMAL);
    while (true)
    {
        // 读取帧
        cv::Mat frame;
        cap >> frame;
        if (frame.empty())
        {
            std::cerr << "Error: Could not read frame from the camera." << std::endl;
            break;
        }
        cv::Mat destImage = cv::Mat::zeros(frame.size(), frame.type());

        // 复制图像数据
        frame.copyTo(destImage);
        auto input_mat = PreProcess::processInput_img(frame);
        m.Infer(input_mat);
        auto d = m.Get_Output();
        PostProcess::vis_joint(d,destImage);
        cv::imshow("Camera", destImage);

        // 按下 ESC 键退出循环
        if (cv::waitKey(1) == 27)
        {
            break;
        }
        
    }

    return 0;
}
