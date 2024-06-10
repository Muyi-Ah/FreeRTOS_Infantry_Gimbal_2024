/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-10 17:41:56
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-10 22:10:31
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
    remote_init();
    // StateMachine_Init(&state_machine); //在main.c内进行状态机初始化
    can_manage_init();
    uart_manage_init();
}