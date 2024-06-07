/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-08 07:18:50
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Inc\CH110.h
 * @Description: 
 * 
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved. 
 */
#ifndef CH110_H
#define CH110_H\

/*标准库引用*/
#include "stdint.h"
#include "math.h"

/*HAL库引用*/

/*用户头文件引用*/

/* 结构体定义 */
typedef struct{
	float roll; /* x轴 */
	float pitch;/* y轴 */
	float yaw;	/* z轴 */
	int16_t X_axisAngularVelocity;
	int16_t Y_axisAngularVelocity;
	int16_t Z_axisAngularVelocity;
}CH110_data_t;

/* 变量外部声明 */
extern CH110_data_t CH110_data;
extern float roll_cumulative_change_angle;
extern float pitch_cumulative_change_angle;
extern float yaw_cumulative_change_angle;

/* 函数外部声明 */
void CH110_cumulative_update(void);

#endif /*CH110_H*/