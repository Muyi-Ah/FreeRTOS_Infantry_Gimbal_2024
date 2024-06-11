/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-08 07:20:26
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Inc\motor.h
 * @Description: 
 * 
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved. 
 */
#ifndef MOTOR_H
#define MOTOR_H

/*标准库引用*/
#include "stdint.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"

/*FreeRTOS引用*/
#include "FreeRTOS.h"
#include "portable.h"

/*用户头文件引用*/
#include "error_codes.h"
#include "sys_config.h"


/* 枚举定义 */

enum PID_type_t {
    nothing,
    rotating_speed,
    relative_angle,
    absolute_angle,
    relative_angle_cascade,
    absolute_angle_cascade,
    gyro_angle_cascade,
    CH110_gyro_angle_cascade,
    vision_angle_cascade,
};


/* 结构体定义 */

struct motor_info_t {
    enum PID_type_t PID_type;
    void* PID_structure_addr;
    uint32_t RecId;
    uint32_t SendId;
    int16_t final_output;
    uint16_t mechanical_angle;
    uint16_t mechanical_angle_previous;
    uint16_t rpm;
    uint16_t actual_torque_current;
    uint8_t temperature;

    uint8_t first_received;
    uint8_t online_reply;
    uint8_t used;

    int32_t angle_change_sum;
};

struct rotating_speed_t {
    int16_t target_value; // 0-8550
    int16_t actual_RPM;
    int16_t output;
    int16_t error;
    int16_t error_previous;
    int32_t cumulative_error;
};

struct relative_angle_t {
    int32_t target_value; // 0-8191
    uint16_t mechanical_angle;
    uint16_t mechanical_angle_previous;
    int16_t output;
    int32_t error;
    int32_t error_previous;
    int32_t cumulative_error;
    int32_t spindle_angle_change_sum;
};

struct absolute_angle_t {
    uint16_t target_value; // 0-8191
    uint16_t mechanical_angle;
    int16_t output;
    int16_t error;
    int16_t error_previous;
    int32_t cumulative_error;
};

struct relative_angle_cascade_t {
    int32_t primary_target_value; // 0-8191
    uint16_t mechanical_angle;
    uint16_t mechanical_angle_previous;
    int16_t primary_output;
    int32_t primary_error;
    int32_t primary_error_previous;
    int32_t primary_cumulative_error;

    int16_t secondary_target_value;
    int16_t angular_velocity;
    int16_t secondary_output;
    int32_t secondary_error;
    int32_t secondary_error_previous;
    int32_t secondary_cumulative_error;

    int32_t spindle_angle_change_sum;
    uint8_t used;
};

struct absolute_angle_cascade_t {
    uint16_t primary_target_value; // 0-8191
    uint16_t mechanical_angle;
    int16_t primary_output;
    int16_t primary_error;
    int16_t primary_error_previous;
    int32_t primary_cumulative_error;

    int16_t secondary_target_value;
    int16_t angular_velocity;
    int16_t secondary_output;
    int16_t secondary_error;
    int16_t secondary_error_previous;
    int32_t secondary_cumulative_error;
};

struct gyro_angle_cascade_t {
    float primary_target_value;
    int16_t primary_output;
    float primary_error;
    float primary_error_previous;
    float primary_cumulative_error;

    int16_t secondary_target_value;
    int16_t secondary_output;
    int16_t secondary_error;
    int16_t secondary_error_previous;
    int32_t secondary_cumulative_error;
};

struct vision_angle_cascade_t {
    int32_t primary_target_value;
    int16_t primary_output;
    int32_t primary_error;
    int32_t primary_error_previous;
    int32_t primary_cumulative_error;

    int16_t secondary_target_value;
    int16_t secondary_output;
    int16_t secondary_error;
    int16_t secondary_error_previous;
    int32_t secondary_cumulative_error;
};


/* 结构体指针列表外部声明 */

extern struct motor_info_t* motor_info_list[MOTOR_COUNT];
extern struct rotating_speed_t* rotating_speed_list[MOTOR_COUNT];
extern struct relative_angle_t* relative_angle_list[MOTOR_COUNT];
extern struct absolute_angle_t* absolute_angle_list[MOTOR_COUNT];
extern struct relative_angle_cascade_t* relative_angle_cascade_list[MOTOR_COUNT];
extern struct absolute_angle_cascade_t* absolute_angle_cascade_list[MOTOR_COUNT];
extern struct gyro_angle_cascade_t* gyro_angle_cascade_list[MOTOR_COUNT];
extern struct vision_angle_cascade_t* vision_angle_cascade_list[MOTOR_COUNT];


/* 函数外部声明 */

void add_motor(uint32_t RecId, uint32_t SendId);
int8_t request_structure_memory(uint8_t index, enum PID_type_t type);
int8_t release_structure_memory(uint8_t index);
uint16_t absolute_angle_remainder(int32_t value);
void motor_angle_sum_clear(uint32_t RecId);
// int32_t get_motor_angle_sum(uint32_t RecId);
void angle_change_clac(uint8_t index);
void MotorOutput_AllClear(void);

#endif /*MOTOR_H*/