#include "NvOnnxParser.h"
#include "NvInfer.h"
#include "NvInferPlugin.h"
#include <iostream>

class mylogger : public nvinfer1::ILogger
{
    void log(Severity severity, const char* msg) noexcept override
    {
        if (severity != Severity::kVERBOSE)
        {
            std::cout << std::to_string((int)severity) << "[TRT] " << std::string(msg) << std::endl;
        }
        // else
        // {
        //     std::cout << "verbose:" << "[TRT] " << std::string(msg) << std::endl;
        // }
    }
};


