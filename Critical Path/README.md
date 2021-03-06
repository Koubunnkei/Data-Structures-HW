# 关键路径：软件管理的流程控制问题  
  
## 问题描述  
**给定一些工程活动和事件后对工程进行建模，求出关键路径以进行项目管理**  

## 解决过程  
- **对图的数据结构进行建模，此处使用邻接表对AOE网络进行图的存储**
- **关键在于拓扑排序求出事件的最早发生事件**（*代码中为VE*），**以及逆拓扑排序求出事件的最迟发生时间**（*代码中为VL*）  
- **通过比较活动的最早开始时间以及最迟开始时间是否相等确定是否为关键路径**  

## 关于代码的说明  
**本代码包含两个头文件和一个main文件**

*pre_work.h主要构建整个邻接表的结构，AOENetwork.h构建AOE网络所使用的类*

*main文件主要搭建了一个用例，来显示输出，用例如下图所示*

![image](https://github.com/Koubunnkei/Data-Structures-HW/blob/main/Critical%20Path/IMG_usecase.PNG)
