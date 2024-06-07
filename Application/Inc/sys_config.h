/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-08 07:21:15
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Inc\sys_config.h
 * @Description: 
 * 
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved. 
 */

/*电机最大总数*/
#define motor_count 8

/*电机can*/
#define motor_can1 hcan1

/*IMU模块can*/
#define CH110_can hcan2

#define remote_uart huart3
/*遥控器数据字节数*/
#define remote_data_size			18

/* 电机旋转角度累计(启用宏定义则对对应ID电机进行累计计算) */
// #define enable_angle_sum_clac_0x201
// #define enable_angle_sum_clac_0x202
// #define enable_angle_sum_clac_0x203
// #define enable_angle_sum_clac_0x204
// #define enable_angle_sum_clac_0x205
// #define enable_angle_sum_clac_0x206
// #define enable_angle_sum_clac_0x207
// #define enable_angle_sum_clac_0x208
// #define enable_angle_sum_clac_0x209

