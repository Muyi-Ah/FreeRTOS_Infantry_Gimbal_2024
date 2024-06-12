/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-11 15:06:11
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-12 23:10:27
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Src\TimerCallback.c
 * @Description:
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */
#include "TimerCallback.h"

void TIM6_Callback_Function(void)
{
    // 1KHz
    //  定时运行的东西...
    // 控制器计算...

    // 使用视觉
    if (vision.Use) {
        // yaw
        vision_cascade_calculation(YAW_MOTOR_ID,
                                   vision.VisionTargetYaw,
                                   yaw,
                                   gyro,
                                   0U,
                                   Vision_YAW_Primary_PIDParam,
                                   Vision_YAW_Secondary_PIDParam);

        // pitch
        vision_cascade_calculation(YAW_MOTOR_ID,
                                   vision.VisionTargetYaw,
                                   pitch,
                                   gyro,
                                   0U,
                                   Vision_PITCH_Primary_PIDParam,
                                   Vision_PITCH_Secondary_PIDParam);
    }
    // 不使用视觉
    else {
        // yaw
        PIDYaw_Target = Yaw_Target;
        CH110_gyro_angle_cascade_calculation(
            YAW_MOTOR_ID, &PIDYaw_Target, 2048U, yaw, gyro, 0U, IMU_YawPrimary_PIDParam, IMU_YawSecondary_PIDParam);

        // pitch
        PIDPitch_Target = Pitch_Target;
        CH110_gyro_angle_cascade_calculation(PITCH_MOTOR_ID,
                                             &PIDPitch_Target,
                                             0U,
                                             pitch,
                                             gyro,
                                             0U,
                                             IMU_PitchPrimary_PIDParam,
                                             IMU_PitchSecondary_PIDParam);
    }

    // 摩擦轮
    rotating_speed_calculation(FRICTION_MOTOR1_ID, FrictionRPM_Target, 9000U, FrictionRotaion_PIDParam);
    rotating_speed_calculation(FRICTION_MOTOR2_ID, -FrictionRPM_Target, 9000U, FrictionRotaion_PIDParam);

    // 拨盘
    relative_angle_cascade_calculation(
        TRIGGER_MOTOR_ID, PIDTrigger_Target, 49152U, 0U, 0U, TriggerPrimary_PIDParam, TriggerSecondary_PIDParam);
    // 目标值最大偏移范围49152 假设使用M2006 P36且拨盘每圈6颗弹丸 :8192*36/6=49152

    // 电机输出清除 该部分必须运行在PID控制器之后
    if (MotorOutput_Clear_Flag) {
        MotorOutput_AllClear();
    }

    // 发送电机数据
    motor_control_send(&MOTOR_CAN);

    // 云台-底盘夹角更新
    Theta_Update();

    // 板间通信发送
    CommunicationData_Send();
}