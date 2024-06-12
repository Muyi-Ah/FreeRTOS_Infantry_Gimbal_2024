/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-12 02:19:49
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Src\gimbal.c
 * @Description:
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */
#include "gimbal.h"

//  ==== 本地函数声明 ====

/// @brief 子模式时间戳清除
/// @param
void TimeStamp_Clear(void);

/// @brief 子模式函数
/// @param
void SUBSTATE_MODE_11_Function(void);
void SUBSTATE_MODE_12_Function(void);
void SUBSTATE_MODE_13_Function(void);
void SUBSTATE_MODE_21_Function(void);
void SUBSTATE_MODE_22_Function(void);
void SUBSTATE_MODE_23_Function(void);
void SUBSTATE_MODE_31_Function(void);
void SUBSTATE_MODE_32_Function(void);
void SUBSTATE_MODE_33_Function(void);

/// @brief 使能电机
/// @param
void EnableMotor(void);

/// @brief 失能电机
/// @param
void DisableMotor(void);


//  ==== 创建变量 ====

uint8_t MotorOutput_Clear_Flag;
float Yaw_Target;
float Pitch_Target;
int32_t PIDYaw_Target;
int32_t PIDPitch_Target;
int16_t FrictionRPM_Target;
int32_t PIDTrigger_Target;
float Theta;

// 遥控器控制系数
float REMOTE_YAW_COEFFICIENT   = 0.015f;
float REMOTE_PITCH_COEFFICIENT = 0.003f;

// 摇杆死区
uint8_t REMOTE_DEAD_BAND = 10U;


//  ==== 创建PID结构体 ====

/// @brief IMU控制下的YAW轴外环PID参数
primary_PID_param_struct_t IMU_YawPrimary_PIDParam = {.kp                 = 0,
                                                      .ki                 = 0,
                                                      .kd                 = 0,
                                                      .cumulative_err_max = 0,
                                                      .output_max         = 0};

/// @brief IMU控制下的YAW轴内环PID参数
secondary_PID_param_struct_t IMU_YawSecondary_PIDParam = {.kp                 = 0,
                                                          .ki                 = 0,
                                                          .kd                 = 0,
                                                          .cumulative_err_max = 0,
                                                          .output_max         = 0};

/// @brief IMU控制下的PITCH轴外环PID参数
primary_PID_param_struct_t IMU_PitchPrimary_PIDParam = {.kp                 = 0,
                                                        .ki                 = 0,
                                                        .kd                 = 0,
                                                        .cumulative_err_max = 0,
                                                        .output_max         = 0};

/// @brief IMU控制下的PITCH轴内环PID参数
secondary_PID_param_struct_t IMU_PitchSecondary_PIDParam = {.kp                 = 0,
                                                            .ki                 = 0,
                                                            .kd                 = 0,
                                                            .cumulative_err_max = 0,
                                                            .output_max         = 0};

/// @brief 拨盘外环PID参数
primary_PID_param_struct_t TriggerPrimary_PIDParam = {.kp                 = 0,
                                                      .ki                 = 0,
                                                      .kd                 = 0,
                                                      .cumulative_err_max = 0,
                                                      .output_max         = 0};

/// @brief 拨盘内环PID参数
secondary_PID_param_struct_t TriggerSecondary_PIDParam = {.kp                 = 0,
                                                          .ki                 = 0,
                                                          .kd                 = 0,
                                                          .cumulative_err_max = 0,
                                                          .output_max         = 0};

/// @brief 摩擦轮PID参数
PID_param_struct_t FrictionRotaion_PIDParam = {.kp = 0, .ki = 0, .kd = 0, .cumulative_err_max = 0, .output_max = 0};


//  ==== 函数定义 ====

void Gimbal_Task(void* argument)
{
    for (;;) {
        // 解决串口ORE问题
        if (__HAL_UART_GET_FLAG(&REMOTE_UART, UART_FLAG_ORE) != RESET) {
            // 清除ORE位
            __HAL_UART_CLEAR_OREFLAG(&REMOTE_UART);

            // 重新启动接收
            HAL_UARTEx_ReceiveToIdle_DMA(&REMOTE_UART, remote_rx_buf, REMOTE_DATA_LENGTH);
        }

        // 解决串口ORE问题
        if (__HAL_UART_GET_FLAG(&COMMUNICATE_UART, UART_FLAG_ORE) != RESET) {
            // 清除ORE位
            __HAL_UART_CLEAR_OREFLAG(&COMMUNICATE_UART);

            // 重新启动接收
            HAL_UARTEx_ReceiveToIdle_DMA(&COMMUNICATE_UART, communication_rx_buf, COMMUNICATION_RECEIVE_DATA_LENGTH);
        }

        // 获取系统时间戳，单位为ms
        uint32_t currentTime = osKernelGetSysTimerCount(); // 需configTICK_RATE_HZ配置为1000

        // 检查状态
        switch (state_machine.currentState) {
            // 初始化状态
            case STATE_INIT:
                DisableMotor();                                                // 关闭电机
                Robot_Init();                                                  // 初始化
                StateMachine_HandleEvent(&state_machine, EVENT_START_RUNNING); // 切换到运行
                break;

            // 维护状态
            case STATE_MAINTENANCE:
                DisableMotor();               // 关闭电机
                STATE_MAINTENANCE_Function(); // 运行函数

                // 检查子状态
                switch (state_machine.currentSubState) {
                    // 拨杆全下
                    case SUBSTATE_MODE_33:
                        StateMachine_HandleEvent(&state_machine, EVENT_START_RUNNING); // 切换状态到运行模式
                        break;
                }
                break;

            // 运行状态
            case STATE_RUNNING:
                // 检查子状态
                switch (state_machine.currentSubState) {
                    // 未开启遥控器
                    case SUBSTATE_NONE:
                        DisableMotor(); // 关闭电机
                        break;

                    // 切换到维护模式
                    case SUBSTATE_MODE_11:
                        StateMachine_HandleEvent(&state_machine, EVENT_ENTER_MAINTENANCE); // 切换状态到维护模式
                        break;

                    // 遥控器小陀螺顺时针
                    case SUBSTATE_MODE_12:
                        EnableMotor(); // 启动电机

                        // 获取进入时的时间戳
                        if (state_machine.enterMode12Time == 0) {
                            state_machine.enterMode12Time = currentTime;
                        }
                        // 1s后
                        else if ((currentTime - state_machine.enterMode12Time) >= 1000) {
                            SUBSTATE_MODE_12_Function(); // 运行函数
                        }
                        break;

                    // 遥控器小陀螺逆时针
                    case SUBSTATE_MODE_13:
                        EnableMotor(); // 启动电机

                        // 获取进入时的时间戳
                        if (state_machine.enterMode13Time == 0) {
                            state_machine.enterMode13Time = currentTime;
                        }
                        // 1s后
                        else if ((currentTime - state_machine.enterMode13Time) >= 1000) {
                            SUBSTATE_MODE_13_Function(); // 运行函数
                        }
                        break;

                    // 转场模式
                    case SUBSTATE_MODE_21:
                    case SUBSTATE_MODE_22:
                    case SUBSTATE_MODE_23:
                        EnableMotor();               // 启动电机
                        SUBSTATE_MODE_23_Function(); // 运行函数
                        break;

                    // 遥控器射击模式
                    case SUBSTATE_MODE_31:
                    case SUBSTATE_MODE_32:
                        EnableMotor(); // 启动电机

                        // 获取进入时的时间戳
                        if (state_machine.enterMode32Time == 0) {
                            state_machine.enterMode32Time = currentTime;
                        }
                        // 1s后
                        else if ((currentTime - state_machine.enterMode32Time) >= 1000) {
                            SUBSTATE_MODE_32_Function(); // 运行函数
                        }
                        break;

                    // 键鼠模式
                    case SUBSTATE_MODE_33:
                        EnableMotor();               // 启动电机
                        SUBSTATE_MODE_33_Function(); // 运行函数
                        break;

                    default:
                        DisableMotor(); // 关闭电机
                        break;

                } /* switch sub state end */
                break;

            default:
                DisableMotor(); // 关闭电机
                break;

        } /* switch main state end */

        // 清除非对应子模式的时间戳
        TimeStamp_Clear();

        // 延时1ms
        osDelay(1);
    }
}


/// @brief 遥控器下云台目标值处理
/// @param
static void RemoteTarget_Handle(void)
{
    // YAW轴旋转角度计算
    if (RecMsg.remote.ch0 < 1024 - REMOTE_DEAD_BAND || RecMsg.remote.ch0 > 1024 + REMOTE_DEAD_BAND) {
        Yaw_Target += (float)((RecMsg.remote.ch0 - 1024) * REMOTE_YAW_COEFFICIENT);
    }

    // PITCH轴旋转角度计算
    if (RecMsg.remote.ch1 < 1024 - REMOTE_DEAD_BAND || RecMsg.remote.ch1 > 1024 + REMOTE_DEAD_BAND) {
        Pitch_Target += (float)((RecMsg.remote.ch1 - 1024) * REMOTE_PITCH_COEFFICIENT);
    }
}


void STATE_MAINTENANCE_Function(void)
{
    // 目标值与实际值一致...
    /* code */
}
void SUBSTATE_MODE_11_Function(void)
{
    /* code */
}
void SUBSTATE_MODE_12_Function(void)
{
    /* code */
}
void SUBSTATE_MODE_13_Function(void)
{
    /* code */
}
void SUBSTATE_MODE_21_Function(void)
{
    /* code */
}
void SUBSTATE_MODE_22_Function(void)
{
    /* code */
}
void SUBSTATE_MODE_23_Function(void)
{
    // 遥控器下云台目标值处理
    RemoteTarget_Handle();

    // 摩擦轮停转
    FrictionRPM_Target = 0;

    // 拨盘以当前位置为目标...
}
void SUBSTATE_MODE_31_Function(void)
{
    /* code */
}
void SUBSTATE_MODE_32_Function(void)
{
    // 遥控器下云台目标值处理
    RemoteTarget_Handle();

    // 获取系统时间戳，单位为ms
    uint32_t currentTime = osKernelGetSysTimerCount(); // 需configTICK_RATE_HZ配置为1000

    // 左手拨杆前推发射弹丸
    if (RecMsg.remote.ch3 > 1684 - REMOTE_DEAD_BAND) {
        if (state_machine.Mode32Time == 0) {
            state_machine.Mode32Time = currentTime;
        }
        // 每500ms两发弹丸
        else if (currentTime - state_machine.Mode32Time >= 500) {
            PIDTrigger_Target += 49152 * SHOTS_PER_FIRE; // 假设使用M2006 P36且拨盘每圈6颗弹丸 :8192*36/6=49152
            state_machine.Mode32Time = currentTime;
        }
    }

    // 摩擦轮转动
    FrictionRPM_Target = 4000;
}
void SUBSTATE_MODE_33_Function(void)
{
    /* code */
}

void EnableMotor(void)
{
    MotorOutput_Clear_Flag = 0U;
}

void DisableMotor(void)
{
    MotorOutput_Clear_Flag = 1U;
}


void TimeStamp_Clear(void)
{
    if (state_machine.currentSubState != SUBSTATE_MODE_11) {
        state_machine.enterMode11Time = 0;
        state_machine.Mode11Time      = 0;
    }
    if (state_machine.currentSubState != SUBSTATE_MODE_12) {
        state_machine.enterMode12Time = 0;
        state_machine.Mode12Time      = 0;
    }
    if (state_machine.currentSubState != SUBSTATE_MODE_13) {
        state_machine.enterMode13Time = 0;
        state_machine.Mode13Time      = 0;
    }
    if (state_machine.currentSubState != SUBSTATE_MODE_21) {
        state_machine.enterMode21Time = 0;
        state_machine.Mode21Time      = 0;
    }
    if (state_machine.currentSubState != SUBSTATE_MODE_22) {
        state_machine.enterMode22Time = 0;
        state_machine.Mode22Time      = 0;
    }
    if (state_machine.currentSubState != SUBSTATE_MODE_23) {
        state_machine.enterMode23Time = 0;
        state_machine.Mode23Time      = 0;
    }
    if (state_machine.currentSubState != SUBSTATE_MODE_31) {
        state_machine.enterMode31Time = 0;
        state_machine.Mode31Time      = 0;
    }
    if (state_machine.currentSubState != SUBSTATE_MODE_32) {
        state_machine.enterMode32Time = 0;
        state_machine.Mode32Time      = 0;
    }
    if (state_machine.currentSubState != SUBSTATE_MODE_33) {
        state_machine.enterMode33Time = 0;
        state_machine.Mode33Time      = 0;
    }
}


/// @brief 云台-底盘夹角更新
/// @param
void Theta_Update(void)
{
    Theta = Calculate_Theta(GetMotorEncoderValue(YAW_MOTOR_ID), YAW_MOTOR_INITIAL_ENCODER_VALUE);
}