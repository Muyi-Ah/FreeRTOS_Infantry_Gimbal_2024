/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-08 07:20:31
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Inc\pid.h
 * @Description: 
 * 
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved. 
 */
#ifndef PID_H
#define PID_H

/*标准库引用*/
#include "stdint.h"
#include "stddef.h"

/*用户头文件引用*/
#include "motor.h"
#include "CH110.h"

enum direction {
    Both,
    CW,
    CCW,
};

enum euler_axis {
    roll,
    pitch,
    yaw,
};

enum speed_loop_data_source {
    gyro,
    motor,
};

typedef struct {
    float kp;
    float ki;
    float kd;
    int32_t cumulative_err_max;
    int16_t output_max;
} PID_param_struct_t;

typedef PID_param_struct_t primary_PID_param_struct_t;
typedef PID_param_struct_t secondary_PID_param_struct_t;

int8_t rotating_speed_calculation(uint32_t RecId,
                                  int16_t target_value,
                                  int16_t target_value_max,
                                  PID_param_struct_t structure);
int8_t relative_angle_calculation(uint32_t RecId,
                                  int32_t target_value,
                                  int32_t CW_angle_max,
                                  int32_t CCW_angle_max,
                                  PID_param_struct_t structure);
int8_t
absolute_angle_calculation(uint32_t RecId, uint16_t target_value, enum direction direct, PID_param_struct_t structure);
int8_t relative_angle_cascade_calculation(uint32_t RecId,
                                          int32_t target_value,
                                          int32_t CW_angle_max,
                                          int32_t CCW_angle_max,
                                          primary_PID_param_struct_t primary_structure,
                                          secondary_PID_param_struct_t secondary_structure);
int8_t absolute_angle_cascade_calculation(uint32_t RecId,
                                          uint16_t target_value,
                                          enum direction direct,
                                          primary_PID_param_struct_t primary_structure,
                                          secondary_PID_param_struct_t secondary_structure);
int8_t CH110_gyro_angle_cascade_calculation(uint32_t RecId,
                                            int32_t target_value,
                                            enum euler_axis angular_velocity_axis,
                                            enum speed_loop_data_source speed_src,
                                            uint8_t output_inversion,
                                            primary_PID_param_struct_t primary_structure,
                                            secondary_PID_param_struct_t secondary_structure);
int8_t vision_angle_cascade_caculation(uint32_t RecId,
                                       int32_t target_value,
                                       enum euler_axis angular_velocity_axis,
                                       enum speed_loop_data_source speed_src,
                                       uint8_t output_inversion,
                                       primary_PID_param_struct_t primary_structure,
                                       secondary_PID_param_struct_t secondary_structure);

#endif /*PID_H*/