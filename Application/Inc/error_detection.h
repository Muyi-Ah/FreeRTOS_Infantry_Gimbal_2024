/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-10 22:50:56
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Inc\error_detection.h
 * @Description: 
 * 
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved. 
 */
#ifndef ERROR_DETECTION_H
#define ERROR_DETECTION_H

/*标准库引用*/
#include "stdint.h"

/*HAL库引用*/

/*cmsis引用*/
#include "cmsis_os2.h"

/*用户头文件引用*/
#include "sys_config.h"


/* 变量外部声明 */  

extern uint8_t motor_error;
extern uint8_t error_motor[MOTOR_COUNT];

extern uint8_t IMU_online_reply;
extern uint8_t IMU_error;

extern uint8_t remote_online_reply;
extern uint8_t remote_error;

extern uint8_t communication_online_reply;
extern uint8_t communication_error;

/* 函数外部声明 */
void ErrorDetection_Task(void* argument);

#endif /*ERROR_DETECTION_H*/