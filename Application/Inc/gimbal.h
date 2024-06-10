/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-10 22:48:52
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Inc\gimbal.h
 * @Description: 
 * 
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved. 
 */
#ifndef GIMBAL_H
#define GIMBAL_H

/*标准库引用*/
#include "stdint.h"

/*FreeRTOS引用*/
#include "FreeRTOS.h"

/*cmsis引用*/
#include "cmsis_os2.h"

/*用户头文件引用*/
#include "sys_config.h"
#include "drv_uart.h"
#include "state_machine.h"
#include "init.h"


/*函数外部声明*/

/// @brief 云台任务
/// @param argument 
void Gimbal_Task(void* argument);

#endif /*GIMBAL_H*/