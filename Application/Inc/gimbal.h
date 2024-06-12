/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-11 17:44:46
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Inc\gimbal.h
 * @Description:
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */
#ifndef GIMBAL_H
#define GIMBAL_H

/*标准库引用*/
#include "stdint.h"

/*FreeRTOS引用*/
#include "FreeRTOS.h"

/*cmsis引用*/
#include "cmsis_os2.h"

/*用户头文件引用*/
#include "drv_uart.h"
#include "init.h"
#include "pid.h"
#include "state_machine.h"
#include "sys_config.h"
#include "motor.h"


//  ==== 变量外部声明 ====

extern uint8_t MotorOutput_Clear_Flag;
extern float Yaw_Target;
extern float Pitch_Target;
extern int32_t PIDYaw_Target;
extern int32_t PIDPitch_Target;
extern int16_t FrictionRPM_Target;
extern int32_t PIDTrigger_Target;;

//  ==== 结构体外部声明 ====

extern primary_PID_param_struct_t IMU_YawPrimary_PIDParam;
extern secondary_PID_param_struct_t IMU_YawSecondary_PIDParam;
extern primary_PID_param_struct_t IMU_PitchPrimary_PIDParam;
extern secondary_PID_param_struct_t IMU_PitchSecondary_PIDParam;
extern primary_PID_param_struct_t TriggerPrimary_PIDParam;
extern secondary_PID_param_struct_t TriggerSecondary_PIDParam;
extern PID_param_struct_t FrictionRotaion_PIDParam;
extern primary_PID_param_struct_t Vision_YAW_Primary_PIDParam;
extern secondary_PID_param_struct_t Vision_YAW_Secondary_PIDParam;
extern primary_PID_param_struct_t Vision_PITCH_Primary_PIDParam;
extern secondary_PID_param_struct_t Vision_PITCH_Secondary_PIDParam;


/*函数外部声明*/

/// @brief 云台任务
/// @param argument
void Gimbal_Task(void* argument);

void Theta_Update(void);

#endif /*GIMBAL_H*/