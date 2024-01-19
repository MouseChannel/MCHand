#pragma once
#include <vector>

extern "C" {
typedef void (*CallbackFunction)(const char* message);

__attribute__((visibility("default"))) void RegisterCallback(CallbackFunction callback);
__attribute__((visibility("default"))) void OnlyTest();


__attribute__((visibility("default"))) void MCHand_Init(const char* onnx_path);
__attribute__((visibility("default"))) void MCHand_Setinput_name(const char* input_name);
__attribute__((visibility("default"))) void MCHand_Setoutput_name(const char* output_name);
__attribute__((visibility("default"))) void MCHand_NeedJoint();

__attribute__((visibility("default"))) void MCHand_NeedMesh();
// __attribute__((visibility("default"))) void MCHand_Infer(float* input_img, int height, int width);
__attribute__((visibility("default"))) int* MCHand_Infer();


// __attribute__((visibility("default"))) std::vector<float> MCHand_GetOutput(const char* output_name);
__attribute__((visibility("default"))) float* MCHand_GetLeftJoint();
__attribute__((visibility("default"))) float* MCHand_GetRightJoint();
__attribute__((visibility("default"))) int* MCHand_GetLeftMeshFace();
__attribute__((visibility("default"))) float* MCHand_GetLeftMesh();
__attribute__((visibility("default"))) int* MCHand_GetRightMeshFace();
__attribute__((visibility("default"))) float* MCHand_GetRightMesh();

__attribute__((visibility("default"))) float* MCHand_vis_joint();
}
