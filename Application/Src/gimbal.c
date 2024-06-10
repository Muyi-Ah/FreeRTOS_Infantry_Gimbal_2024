/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-11 01:52:34
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Src\gimbal.c
 * @Description:
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */
/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-11 01:15:12
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Src\gimbal.c
 * @Description: 云台任务
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

uint8_t MotorOutput_Flag;


//  ==== 函数定义 ====

void Gimbal_Task(void* argument)
{
    for (;;) {
        // 解决串口ORE问题
        if (__HAL_UART_GET_FLAG(&REMOTE_UART, UART_FLAG_ORE) != RESET) {
            // 清除ORE位
            __HAL_UART_CLEAR_OREFLAG(&REMOTE_UART);

            // 重新启动接收
            HAL_UARTEx_ReceiveToIdle_DMA(&REMOTE_UART, remote_rx_buf, REMOTE_DATA_SIZE);
        }

        // 解决串口ORE问题
        if (__HAL_UART_GET_FLAG(&COMMUNICATE_UART, UART_FLAG_ORE) != RESET) {
            // 清除ORE位
            __HAL_UART_CLEAR_OREFLAG(&COMMUNICATE_UART);

            // 重新启动接收
            HAL_UARTEx_ReceiveToIdle_DMA(&COMMUNICATE_UART, communication_rx_buf, COMMUNICATION_RECEIVE_DATA_SIZE);
        }

        // 获取系统时间戳，单位为ms
        uint32_t currentTime = osKernelGetSysTimerCount(); // 需configTICK_RATE_HZ配置为1000

        // 检查状态
        switch (state_machine.currentState) {
            // 初始化状态
            case STATE_INIT:
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

                } /* switch main state end */
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
    /* code */
}
void SUBSTATE_MODE_31_Function(void)
{
    /* code */
}
void SUBSTATE_MODE_32_Function(void)
{
    /* code */
}
void SUBSTATE_MODE_33_Function(void)
{
    /* code */
}

void EnableMotor(void)
{
    MotorOutput_Flag = 1U;
}

void DisableMotor(void)
{
    MotorOutput_Flag = 0U;
}


void TimeStamp_Clear(void)
{
    if (state_machine.currentSubState != SUBSTATE_MODE_11) {
        state_machine.enterMode11Time = 0;
    }
    if (state_machine.currentSubState != SUBSTATE_MODE_12) {
        state_machine.enterMode12Time = 0;
    }
    if (state_machine.currentSubState != SUBSTATE_MODE_13) {
        state_machine.enterMode13Time = 0;
    }
    if (state_machine.currentSubState != SUBSTATE_MODE_21) {
        state_machine.enterMode21Time = 0;
    }
    if (state_machine.currentSubState != SUBSTATE_MODE_22) {
        state_machine.enterMode22Time = 0;
    }
    if (state_machine.currentSubState != SUBSTATE_MODE_23) {
        state_machine.enterMode23Time = 0;
    }
    if (state_machine.currentSubState != SUBSTATE_MODE_31) {
        state_machine.enterMode31Time = 0;
    }
    if (state_machine.currentSubState != SUBSTATE_MODE_32) {
        state_machine.enterMode32Time = 0;
    }
    if (state_machine.currentSubState != SUBSTATE_MODE_33) {
        state_machine.enterMode33Time = 0;
    }
}