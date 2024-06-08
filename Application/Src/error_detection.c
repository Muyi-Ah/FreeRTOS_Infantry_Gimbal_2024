/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-08 09:03:22
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Src\error_detection.c
 * @Description: 错误检测
 * 
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved. 
 */
#include "error_detection.h"

/* 创建变量 */

uint8_t motor_error;
uint8_t error_motor[motor_count];

uint8_t IMU_online_reply;
uint8_t IMU_error;

uint8_t remote_online_reply;
uint8_t remote_error;

uint8_t communication_online_reply;
uint8_t communication_error;