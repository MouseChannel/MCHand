#include "NvInfer.h"
#include "iostream"
#include <memory>
#include <vector>

namespace mchand
{
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

    class Engine
    {
    public:
        Engine(const std::string onnx_path);
        ~Engine();
        [[nodiscard]] bool infer() const;

        [[nodiscard]] auto get_engine()
        {
            return mEngine;
        }

    private:
        mylogger mlog;
        std::shared_ptr<nvinfer1::IRuntime> mRuntime;
        std::shared_ptr<nvinfer1::ICudaEngine> mEngine;
        std::shared_ptr<nvinfer1::IExecutionContext> mContext;

        std::vector<void*> hostBuffer;
        std::vector<void*> deviceBuffer;
        std::vector<size_t> buffer_size;
    };
}
