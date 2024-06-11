/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-11 17:19:18
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Inc\sys_config.h
 * @Description: 一些配置选项
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */

/*HAL库引用*/
#include "can.h"
#include "usart.h"

/*can总线电机最大总数*/
#define MOTOR_COUNT 8

/*电机can*/
#define MOTOR_CAN1 hcan1

/*IMU模块can*/
#define CH110_can hcan2

/*遥控器串口*/
#define REMOTE_UART huart3

/*板间通信串口*/
#define COMMUNICATE_UART huart1

/*视觉PC通信串口*/
#define VISION_UART huart6

/*遥控器数据字节数*/
#define REMOTE_DATA_SIZE 18

/*板间通信数据字节数*/
#define COMMUNICATION_RECEIVE_DATA_SIZE 15
#define COMMUNICATION_SEND_DATA_SIZE 28

#define can1 (uint8_t)1
#define can2 (uint8_t)2

//  ==== 电机ID分配 ====
#define YAW_MOTOR_ID 0x205
#define PITCH_MOTOR_ID 0x206
#define FRICTION_MOTOR1_ID 0x201
#define FRICTION_MOTOR2_ID 0x202
#define TRIGGER_MOTOR_ID 0x203

/* 电机旋转角度累计(启用宏定义则对对应ID电机进行累计计算) */
// #define enable_angle_sum_clac_0x201
// #define enable_angle_sum_clac_0x202
// #define enable_angle_sum_clac_0x203
// #define enable_angle_sum_clac_0x2046
// #define enable_angle_sum_clac_0x205
// #define enable_angle_sum_clac_0x206
// #define enable_angle_sum_clac_0x207
// #define enable_angle_sum_clac_0x208
// #define enable_angle_sum_clac_0x209
