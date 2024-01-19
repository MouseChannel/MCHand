#include "Engine.hpp"
#include "NvInfer.h"
#include "NvInferPlugin.h"
#include "NvOnnxParser.h"
#include <memory>

namespace mchand
{
    Engine::Engine(const std::string onnx_path)
    {
        auto builder = nvinfer1::createInferBuilder(mlog);
        initLibNvInferPlugins(&mlog, "");
        auto network = builder->createNetworkV2(1U <<
            static_cast<int>(nvinfer1::NetworkDefinitionCreationFlag::kEXPLICIT_BATCH));
        if (!network)
        {
            throw std::runtime_error("err network");
        }
        auto config = builder->createBuilderConfig();
        if (!config)
        {
            throw std::runtime_error("err config");
        }
        config->setFlag(nvinfer1::BuilderFlag::kFP16);
        auto parser = nvonnxparser::createParser(*network, mlog);
        if (!parser)
        {
            throw std::runtime_error("err parser");
        }
        auto parsed = parser->parseFromFile(onnx_path.c_str(), 2);
        if (!parsed)
        {
            throw std::runtime_error("parse fail");
        }
        std::unique_ptr<cudaStream_t> pStream(new cudaStream_t);
        if (cudaStreamCreateWithFlags(pStream.get(), cudaStreamNonBlocking) != cudaSuccess)
        {
            throw std::runtime_error("create cudaStream fail");
        }
        config->setProfileStream(*pStream);
        auto plan = builder->buildSerializedNetwork(*network, *config);
        if (!plan)
        {
            throw std::runtime_error("err plan");
        }
        mRuntime = std::shared_ptr<nvinfer1::IRuntime>(nvinfer1::createInferRuntime(mlog));
        if (!mRuntime)
        {
            throw std::runtime_error("err mRuntime");
        }
        mEngine = std::shared_ptr<nvinfer1::ICudaEngine>(
            mRuntime->deserializeCudaEngine(plan->data(), plan->size()));
        if (!mEngine)
        {
            throw std::runtime_error("err mEngine");
        }


        mContext = std::shared_ptr<nvinfer1::IExecutionContext>(mEngine->createExecutionContext());
        if (!mContext)
        {
            throw std::runtime_error("err context");
        }

        auto input_and_output_size = mEngine->getNbIOTensors();
    }

    bool Engine::infer(const std::shared_ptr<InputOutput>& input_output) const
    {
        return mContext->executeV2(input_output->get_deviceBuffer().data());
    }
}
