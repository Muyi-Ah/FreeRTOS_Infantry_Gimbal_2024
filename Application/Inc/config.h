/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-08 07:19:22
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Inc\config.h
 * @Description: 
 * 
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved. 
 */
#define motor_count 8

#define referee_recive_uart huart7
#define referee_recive_data_size 4096

#define motor_can1 hcan1
#define motor_data_size 13
#define motor_queue_lenght 30

#define can1 (uint8_t)1
#define can2 (uint8_t)2