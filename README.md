# FreeRTOS_Infantry_Gimbal_2024
 About the Repechage for RMUC 2024

云台的主逻辑在Gimbal_Task内

仅有一个云台任务(RTOS)，数据接收等均在接收中断回调函数内完成处理

本工程大多数功能运行在中断内，请谨慎使用HAL_Delay

PID控制器和通信发送均在TIM6溢出中断里跑

添加电机在init.c里面

每个子状态状态机里都有相对应的进入时间戳(enterModeXXTime)和一个可供模式内自行使用的时间戳(ModeXXTime)