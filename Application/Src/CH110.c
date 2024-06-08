/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-08 19:48:18
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Src\CH110.c
 * @Description: CH110累计角度更新
 * 
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved. 
 */
#include "CH110.h"

/* 创建结构体 */

CH110_data_t CH110_data;



/* 创建变量 */
/** 累计角度 **/
 
float roll_cumulative_change_angle;
float pitch_cumulative_change_angle;
float yaw_cumulative_change_angle;



/** 累计角度计算过程变量 **/

float roll_offset;
float pitch_offset;
float yaw_offset;
float roll_previous;
float pitch_previous;
float yaw_previous;
float roll_res1, roll_res2;
float pitch_res1, pitch_res2;
float yaw_res1, yaw_res2;
float roll_change, pitch_change, yaw_change;



/**
 * @description: CH110累计角度计算
 * @return {*}
 */
void CH110_cumulative_update(void)
{
    /* 计算roll轴的实际变化角度 */
    if (CH110_data.roll - roll_previous > 0) {
        roll_res1 = CH110_data.roll - roll_previous - 360;
        roll_res2 = CH110_data.roll - roll_previous;
        if (fabsf(roll_res1) < fabsf(roll_res2))
            roll_change = roll_res1;
        else
            roll_change = roll_res2;
    } else {
        roll_res1 = CH110_data.roll - roll_previous + 360;
        roll_res2 = CH110_data.roll - roll_previous;
        if (fabsf(roll_res1) < fabsf(roll_res2))
            roll_change = roll_res1;
        else
            roll_change = roll_res2;
    }

    /* 计算pitch轴的实际变化角度 */
    if (CH110_data.pitch - pitch_previous > 0) {
        pitch_res1 = CH110_data.pitch - pitch_previous - 360;
        pitch_res2 = CH110_data.pitch - pitch_previous;
        if (fabsf(pitch_res1) < fabsf(pitch_res2))
            pitch_change = pitch_res1;
        else
            pitch_change = pitch_res2;
    } else {
        pitch_res1 = CH110_data.pitch - pitch_previous + 360;
        pitch_res2 = CH110_data.pitch - pitch_previous;
        if (fabsf(pitch_res1) < fabsf(pitch_res2))
            pitch_change = pitch_res1;
        else
            pitch_change = pitch_res2;
    }

    /* 计算yaw轴的实际变化角度 */
    if (CH110_data.yaw - yaw_previous > 0) {
        yaw_res1 = CH110_data.yaw - yaw_previous - 360;
        yaw_res2 = CH110_data.yaw - yaw_previous;
        if (fabsf(yaw_res1) < fabsf(yaw_res2))
            yaw_change = yaw_res1;
        else
            yaw_change = yaw_res2;
    } else {
        yaw_res1 = CH110_data.yaw - yaw_previous + 360;
        yaw_res2 = CH110_data.yaw - yaw_previous;
        if (fabsf(yaw_res1) < fabsf(yaw_res2))
            yaw_change = yaw_res1;
        else
            yaw_change = yaw_res2;
    }

    /* 计算累计变化角度 */
    roll_cumulative_change_angle += roll_change;
    pitch_cumulative_change_angle += pitch_change;
    yaw_cumulative_change_angle += yaw_change;

    /* 记录此欧拉角用于下次计算 */
    roll_previous  = CH110_data.roll;
    pitch_previous = CH110_data.pitch;
    yaw_previous   = CH110_data.yaw;
}