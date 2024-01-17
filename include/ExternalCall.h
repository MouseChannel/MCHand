#pragma once
extern "C" {
    __attribute__((visibility("default"))) void MCHand_Init(const char* onnx_path);
    __attribute__((visibility("default"))) void MCHand_Setinput_name(const char* input_name);
    __attribute__((visibility("default"))) void MCHand_Setoutput_name(const char* output_name);
    __attribute__((visibility("default"))) void MCHand_Infer(const char* input_name);
}
