/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2024-06-08 03:31:46
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2024-06-08 03:31:55
 * @FilePath: \workspace (工作区)c:\Users\Ryan\Desktop\新建文件夹 (4)\pid.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
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