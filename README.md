# FreeRTOS_Infantry_Gimbal_2024
 About the Repechage for RMUC 2024

在sys_config.h文件中有关于系统的一些配置选项，建议优先阅读

云台的主逻辑在Gimbal_Task内

本项目使用FreeRTOS，但仅有一个云台任务(*Gimbal_Task*)，数据接收等均在接收中断回调函数内完成处理

本工程大多数功能运行在中断内，请**谨慎**使用HAL_Delay

PID控制器和通信发送均在TIM6溢出中断里跑

每个子状态状态机里都有相对应的进入时间戳(*enterModeXXTime*)和一个可供模式内自行使用的时间戳(*ModeXXTime*)

状态机初始化在main.c里

电机的添加在init.c里面(*add_motor*)

add_motor函数内部会注册对应电机的结构体内存空间并记录该电机的接收/发送ID、使用标志位，因此在使用与电机相关的函数时**切记**先使用add_motor函数添加对应电机

pid.c文件内的PID函数有不同电机PID运算方式(*例如速度PID、串级绝对编码器位置PID等*)，且内部带有不同运算方式所需结构体和变量的内存注册和释放，因此一个电机需要切换运算方式(*例如从位置控制切换为速度控制*)的时候，只需要直接调用所需的另一个PID函数即可

云台-底盘夹角Theta在gimbal.c内定义


**本项目横跨2021~2024年，每部分的代码水平并不一致，代码风格也不一致，敬请谅解**

PS:代码风格不一致，主要还是时间久了看腻了就开始用点别的，如果用keil5看变量、函数什么的因为风格不统一导致有障碍，麻烦请使用一个现代化的IDE或者Editor，直接利用不同的颜色进行区分