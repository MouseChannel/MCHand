# 👍Real-time recognition of hand gestures👍

A real-time hand gesture recognition

Inference acceleration by Nvidia Tensorrt , the inference time dropped from **884ms** to **9.3ms**

# 🔨Setup

### pre-requirement

- [NVIDIA TensorRT SDK](https://developer.nvidia.com/tensorrt) for inference
- [MouseChannel Plugin for NVIDIA TensorRT SDK ](https://github.com/MouseChannel/TensorRT) to use custom operator in
  tensorrt
- [InterWild](https://arxiv.org/abs/2303.13652) Published at CVPR 2023 by Facebook  (recognition of hand gestures 2023
  SOTA)

has tested in Ubuntu23.10,by Tensorrt 8.6.1

# 🛸Workflow🛸

Pytorch Model ➡️ ONNX ➡️ Tensorrt

using **three custom operators**

- 🌟**MouseChannelInverse**🌟 : Matrix Inverse by Cuda
- 🌟**MouseChannelSelect**🌟 : Handling dynamic tensor size which is not allowed in native static compute graph
- 🌟**MouseChannelSmallAngle**🌟: Integrated some operations in pytorch and implemented them in cuda

In Pytorch Model Three custom operations are registered. In Tensorrt Use plugins to implement these custom operators

# 🎏Performance🎏

|                         | native pytorch                                 | Tensorrt using float32                       | 
|-------------------------|------------------------------------------------|----------------------------------------------|
| time of inference       | 884.3ms                                        | 9.31ms    (**9498**%🚀)                      | 
| accuracy error(case1)   | 0%  ![float32](./showcase/origin_skeleton.jpg) | 1.1%  ![float32](./showcase/handfloat32.jpg) | 
| accuracy error  (case2) | 0%  ![float32](./showcase/ok_origin.jpg)       | 0.3%  ![float32](./showcase/okfloat32.jpg)   | 

# 🌞Overview🌞

Real-time hand recognition,is able to generate **Hand Joints Image** and generate **Hand Mesh**

### 🫱 showcase

<div align=center>
    <img src="showcase/showcasejoint.jpg" width="40%"> 

<img src="showcase/handmesh.png" width="40%"> 
<br>
real-time Hand Joints
 </div>

###  🤗  Unity Plugin

tested on

![Static Badge](https://img.shields.io/badge/unity2022.3-%20%20?style=for-the-badge&logo=unity&logoColor=black&labelColor=%23F0FFF0&color=black)
![Static Badge](https://img.shields.io/badge/Ubuntu23.10-%20%20?style=for-the-badge&logo=linux&logoColor=black&labelColor=yellow&color=black) 
 
- real-time hand-joint-inference
- real-time animated hand-mesh
<div align=center>
    <img src="showcase/handUnityCase.gif" width="70%">

 </div>
<div align=center>
    <img src="showcase/unityshowcase1.png" width="45%">
<img src="showcase/unityshowcase2.png" width="45%">
<br>
real-time Hand  
 </div>

###  🤗  Unreal Plugin
tested on 

![Static Badge](https://img.shields.io/badge/unreal5.3-%20%20?style=for-the-badge&logo=unrealengine&logoColor=black&labelColor=%23F0FFF0&color=black)
![Static Badge](https://img.shields.io/badge/Ubuntu23.10-%20%20?style=for-the-badge&logo=linux&logoColor=black&labelColor=yellow&color=black) 


- real-time hand-joint-inference
- real-time animated hand-mesh
<div align=center>
    <img src="showcase/UnrealDemo.gif" width="70%">

 </div>
<div align=center>
    <img src="showcase/unrealshowcase1.png" width="45%">
<img src="showcase/unrealshowcase2.png" width="45%">
<br>
real-time Hand 
</div>
