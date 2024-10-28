# 术语表

## MPS

NVIDIA MultiProcess Service (MPS)  NVIDIA 多进程服务 (MPS)

## DNN

DNN（深度神经网络）

## SM

streaming multiprocessors (SMs) 流式多处理器

## InSS

Intelligent Scheduling orchestrator for multi-GPU inference servers with spatio-temporal Sharing

用于具有时空共享的多 GPU 推理服务器的智能调度编排器





# 简介

Temporal sharing [45] and spatial sharing [63] are the two most common ways of sharing resources.
时间共享[45]和空间共享[63]是两种最常见的资源共享方式。

## 挑战

- 同GPU并行模型的干扰
- 推理任务的延迟要求
- 资源分配的碎片化问题

目前大多的GPU资源利用方法没有考虑到碎片化问题，考虑干扰但带来了延迟

- 提出Inss

## 贡献

- 延迟分析模型

  与干扰相关的资源利用率是特定于模型的，并且可以针对每个模型进行独立预测。

- 两阶段智能调度器

  在本地阶段，对于每个 GPU，InSS 利用双延迟深度确定性策略梯度算法 (TD3) 来学习已部署模型的资源分配和批量大小

- 使用十个 DNN 模型和四个 NVIDIA A100 GPU 实现了 InSS 原型