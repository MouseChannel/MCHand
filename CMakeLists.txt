cmake_minimum_required(VERSION 3.13)

set(CMAKE_CUDA_ARCHITECTURES 75)
set(CMAKE_CUDA_COMPILER /usr/local/cuda/bin/nvcc)
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CUDA_STANDARD 20)
project(MCHand)


add_executable(MCHand main.cpp
)
file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)
message(STATUS ${SRC})

# set(IMGUIDIR ${PROJECT_SOURCE_DIR}/lib/imgui)

add_library(src ${SRC})
target_include_directories(src PUBLIC /home/mocheng/project/TensorRT/include /home/mocheng/project/TensorRT/parsers/onnx)


set(Torch_DIR "/home/mocheng/software/libtorch-cxx11-abi-shared-with-deps-2.0.1+cu118/libtorch/share/cmake/Torch")

find_package(Torch REQUIRED)
target_include_directories(src PUBLIC ${Torch_INCLUDE_DIRS})
message(STATUS ${Torch_INCLUDE_DIRS})
target_link_directories(src PUBLIC ${Torch_LIBRARY_DIR})

find_package(CUDAToolkit REQUIRED)
target_include_directories(src PUBLIC ${CUDAToolkit_INCLUDE_DIRS})
target_link_directories(src PUBLIC ${CUDAToolkit_LIBRARY_DIR})

find_package(OpenCV REQUIRED)
target_include_directories(src PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_directories(src PUBLIC ${OpenCV_LIBRARY_DIRS})
#target_link_directories(MCHand PUBLIC lib/libtorchnew/lib)

target_link_directories(src PUBLIC /home/mocheng/software/TensorRT-8.6.1.6/lib)


target_include_directories(src PUBLIC ${PROJECT_SOURCE_DIR}/include)


target_link_libraries(src PUBLIC ${OpenCV_LIBS} torch_cpu nvinfer nvonnxparser /home/mocheng/project/TensorRT/cmake-build-debug/libnvinfer_plugin.so cudart cublas)

target_link_libraries(MCHand src)