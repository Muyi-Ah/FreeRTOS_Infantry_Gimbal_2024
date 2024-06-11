/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-10 17:41:56
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-11 23:28:47
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Src\init.c
 * @Description: 初始化
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */
#include "init.h"


/**
 * @brief 机器人初始化
 *
 */
void Robot_Init(void)
{
    // pitch yaw
    add_motor(0x205, 0x1FF);
    add_motor(0x206, 0x1FF);

    // 摩擦轮
    add_motor(0x201, 0x200);
    add_motor(0x202, 0x200);

    // 拨盘
    add_motor(0x203, 0x200);

    remote_init(); // 遥控器数据初始化
    // StateMachine_Init(&state_machine); //在main.c内进行状态机初始化
    can_manage_init();  // can初始化
    uart_manage_init(); // 串口初始化

    // 定时器初始化 不可早于add_motor和can、uart的初始化
    HAL_TIM_Base_Start_IT(&htim6);
}