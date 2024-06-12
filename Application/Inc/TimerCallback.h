/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-11 15:07:44
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-11 16:48:51
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Inc\TimerCallback.h
 * @Description:
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */
#ifndef TIMERCALLBACK_H
#define TIMERCALLBACK_H

//  ==== 标准库引用 ====
#include "stdint.h"

//  ==== 用户头文件引用 ====
#include "communication.h"
#include "pid.h"
#include "gimbal.h"
#include "motor.h"
#include "drv_can.h"
#include "vision.h"

//  ==== 函数外部声明 ====

/// @brief TIM6用户回调处理函数 该函数在main.c中被定时器溢出中断回调函数调用
/// @param
void TIM6_Callback_Function(void);

#endif /* TIMERCALLBACK_H */