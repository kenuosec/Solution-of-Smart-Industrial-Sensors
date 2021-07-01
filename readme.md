## Solution of Smart Industrial Sensors
## 智能工业传感器解决方案

这是前公司的一个项目，改了改可以在工业物联网的场景下使用。
项目包含了IoT模组、MCU最小系统、传感器数据采集电路，经过实际测试可以完美运行，并已实现量产。
此项目仅仅包含了数据采集和上云的硬件设计与MCU侧的代码，不包含上层业务逻辑的实现（作为MCU工程师，不懂。）
***********************************
#### 硬件选型
- **主控MCU：STM32F103RET**
- **4G模块：移远通信EC200T Mini PCIe-C**
***********************************
#### 硬件结构图
![](/pictures/硬件结构图.jpg)
- 硬件开发软件：Altium Designer (18.1.9)
- 2层PCB板
电路原理图
PCB设计图

*************************************
#### 软件结构图
（有空就画）
- 开发环境：Keil uVision V5.23
- 驱动库版本：Std V3.5.0
软件说明
**********************************
完整的物联网平台消息通信流程下图
![物联网平台结构](https://static-aliyun-doc.oss-accelerate.aliyuncs.com/assets/img/zh-CN/3199158061/p132750.png)


![](https://static-aliyun-doc.oss-accelerate.aliyuncs.com/assets/img/zh-CN/3987358061/p203531.png)


![](https://static-aliyun-doc.oss-accelerate.aliyuncs.com/assets/img/zh-CN/3987358061/p203442.png)
