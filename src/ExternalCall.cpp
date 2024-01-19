#include "ExternalCall.h"

#include <MANO.hpp>
#include <MCHand.hpp>
#include <memory>
#include <PostPrecess.hpp>
#include <PreProcess.hpp>


std::shared_ptr<mchand::MCHand> mc_hand;
CallbackFunction callbackPtr = nullptr;
std::vector<float> rjoint_img;

std::vector<float> ljoint_img;

std::vector<float> rmano_mesh;

std::vector<float> lmano_mesh;


cv::Mat canvas;
cv::Mat frame;
std::vector frame_height_width{0, 0};
cv::VideoCapture cap;
bool has_init = false;

void MCHand_Init(const char* onnx_path)
{
    if (!has_init)
    {
        mchand::MANO::Init();
        cap = cv::VideoCapture(0);

        mc_hand.reset(new mchand::MCHand);
        mc_hand->Init(onnx_path);
        mc_hand->Set_input_name("input");
        has_init = true;
    }
}

void OnlyTest()
{
    // callbackPtr("now");
    // test = cv::imread("/home/mocheng/project/MCHand/me.jpg",
    //                   cv::IMREAD_COLOR | cv::IMREAD_IGNORE_ORIENTATION);
    // test.convertTo(test,CV_32F);
    //
    // // cv::VideoCapture cap(0);
    // //
    // // cap >> frame;
    // // // frame.convertTo(frame,CV_32F);
    // // cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    // std::vector<float> test_arr1;
    // // // test_img1.convertTo(test_img1,CV_32F);
    // test_arr1.assign(test.ptr<float>(), test.ptr<float>() + test.total() * test.channels());
    // auto mes = "onlutest :" + std::to_string(test_arr1[0]) + std::to_string(test_arr1[1]);
    // callbackPtr(mes.c_str());
    // auto test_img1 = cv::imread("/home/mocheng/project/MCHand/me.jpg",
    //                             cv::IMREAD_COLOR);
    // canvas = cv::Mat(test_img1.rows, test_img1.cols,CV_32FC3);
    // MCHand_Infer(test_img1.ptr<float>(), test_img1.rows, test_img1.cols);
    // return test_img1.ptr<float>();


    // auto mes = "mes: " + std::to_string(input_img[0]) + std::to_string(input_img[1]);
    //
    // callbackPtr(mes.c_str());
    // cv::Mat test = cv::Mat(height, width,CV_32FC3, input_img);
    // // cv::cvtColor(test, test, cv::COLOR_BGR2RGB);
    // std::vector<float> test_arr1;
    // // test_img1.convertTo(test_img1,CV_32F);
    // test_arr1.assign(test.ptr<float>(), test.ptr<float>() + test.total() * test.channels());
    // auto mes2 = "mes2: " + std::to_string(test_arr1[0]) + std::to_string(test_arr1[1]) + std::to_string(test_arr1[2]);
    // callbackPtr(mes2.c_str());
    //
    //
    // cv::imwrite("deletesoon.jpg", test);
    //
    // return frame.ptr<float>();
}


void MCHand_Setinput_name(const char* input_name)
{
    mc_hand->Set_input_name(input_name);
}

void MCHand_Setoutput_name(const char* output_name)
{
    mc_hand->Set_output_name(output_name);
}


void RegisterCallback(CallbackFunction callback)
{
    callbackPtr = callback;
}

int* MCHand_Infer()
{
    cap >> frame;
    frame.copyTo(canvas);
    canvas.convertTo(canvas,CV_32FC3);
    cv::cvtColor(canvas, canvas, cv::COLOR_BGR2RGB);

    auto input_mat = mchand::PreProcess::processInput_img(frame);
    mc_hand->Infer(input_mat);
    frame_height_width[0] = canvas.cols;
    frame_height_width[1] = canvas.rows;
    return frame_height_width.data();
}


float* MCHand_GetOutput_RawData(const char* output_name)
{
    rjoint_img = std::move(mc_hand->Get_Output(output_name));
    return rjoint_img.data();
}


float* MCHand_vis_joint()
{
    // canvas = cv::Mat(test_img1.rows, test_img1.cols,CV_32FC3);

    mchand::PostProcess::vis_joint(rjoint_img, canvas);
    mchand::PostProcess::vis_joint(ljoint_img, canvas);

    // callbackPtr("imhere");
    // cv::imwrite("deletesonn.jpg", canvas);
    return canvas.ptr<float>();
}

float* MCHand_GetJoint()
{
    rjoint_img = std::move(mc_hand->Get_Output("rjoint_img"));
    ljoint_img = std::move(mc_hand->Get_Output("ljoint_img"));
}

float* MCHand_GetMesh()
{
}

float* MCHand_GetLeftJoint()
{
    ljoint_img = std::move(mc_hand->Get_Output("ljoint_img"));
    return ljoint_img.data();
}

float* MCHand_GetRightJoint()
{
    rjoint_img = std::move(mc_hand->Get_Output("rjoint_img"));
    return rjoint_img.data();
}

float* MCHand_GetLeftMesh()
{
    lmano_mesh = std::move(mc_hand->Get_Output("lmano_mesh"));
    return lmano_mesh.data();
}

float* MCHand_GetRightMesh()
{
    rmano_mesh = std::move(mc_hand->Get_Output("rmano_mesh"));
    return rmano_mesh.data();
}

void MCHand_NeedJoint()
{
    mc_hand->Set_output_name("rjoint_img");
    mc_hand->Set_output_name("ljoint_img");
}

void MCHand_NeedMesh()
{
    mc_hand->Set_output_name("rmano_mesh");
    mc_hand->Set_output_name("lmano_mesh");
}

int* MCHand_GetLeftMeshFace()
{
    return mchand::MANO::llhand_faces.data();
}

int* MCHand_GetRightMeshFace()
{
    return mchand::MANO::rrhand_faces.data();
}
