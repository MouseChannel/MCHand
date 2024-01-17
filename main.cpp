#include "MCHand.hpp"
#include <iostream>
#include <PostPrecess.hpp>

#include "PreProcess.hpp"
#include "MANO.hpp"

// std::vector<std::string> split(const std::string& s, char delimiter, bool recursive = false)
// {
//     std::vector<std::string> tokens;
//     std::istringstream tokenStream(s);
//     std::string token;
//
//     while (std::getline(tokenStream, token, delimiter))
//     {
//         if (recursive)
//         {
//             auto rr = split(token, ' ');
//             int r = 0;
//         }
//         tokens.push_back(token);
//     }
//
//     return tokens;
// }

int main()
{
    using namespace mchand;
   


    MANO::Init();
    MCHand m;
    m.Init("/home/mocheng/project/RECONSTRCUT/InterWild/demo/mochengres.onnx");
    m.Set_input_name("input");
    m.Set_output_name("rjoint_img");
    m.Set_output_name("ljoint_img");
    m.Set_output_name("rmano_mesh");
    m.Set_output_name("lmano_mesh");

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

        // 复制图像数据

        // auto input_mat = PreProcess::processInput_img(frame);


        auto test_img = cv::imread("/home/mocheng/project/MCHand/me.jpg",
                                   cv::IMREAD_COLOR | cv::IMREAD_IGNORE_ORIENTATION);
        frame = test_img;

        cv::Mat destImage = cv::Mat::zeros(frame.size(), frame.type());
        frame.copyTo(destImage);
         

        std::vector<float> test_arr;
        if (frame.isContinuous())
        {
            test_arr.assign(frame.data, frame.data + frame.total() * frame.channels());
        }
        else
        {
            for (int i = 0; i < frame.rows; ++i)
            {
                test_arr.insert(test_arr.end(), frame.ptr<uchar>(i),
                                frame.ptr<uchar>(i) + frame.cols * frame.channels());
            }
        }
      

    
        m.Infer(test_arr, frame.rows, frame.cols);

       
        auto imgr = m.Get_Output("rjoint_img");
        auto imgl = m.Get_Output("ljoint_img");

        auto meshr = m.Get_Output("rmano_mesh");

        auto meshl = m.Get_Output("lmano_mesh");

        // PostProcess::save_obj(meshr, false);
        // PostProcess::vis_joint(imgr, destImage);
        PostProcess::vis_joint(imgr, destImage);
        // cv::imwrite("testarr.jpg", destImage1);
        // PostProcess::vis_joint(imgr, destImage);
        cv::imshow("Camera", destImage);


        if (cv::waitKey(1) == 27)
        {
            break;
        }
    }

    return 0;
}
