/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-10 17:41:56
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-10 17:53:39
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Src\init.c
 * @Description: 初始化
 * 
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved. 
 */
#include "init.h"

/*创建变量*/

StateMachine state_machine;


/**
 * @description: 机器人初始化
 * @return {void}
 */
void Robot_Init(void)
{
    remote_init();
    StateMachine_Init(&state_machine);
    can_manage_init();
    uart_manage_init();
}