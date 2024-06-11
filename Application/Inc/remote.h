/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-11 14:28:28
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Inc\remote.h
 * @Description:
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */
#ifndef REMOTE_H
#define REMOTE_H

/*标准库引用*/
#include "stdint.h"

/*HAL库引用*/

/*用户头文件引用*/
#include "sys_config.h"
#include "state_machine.h"


//  ==== 拨杆枚举定义 ====
typedef enum { Top = 1, Mid = 3, Bottom = 2 } ToggleSwitch;


/* 结构体定义 */

typedef struct {
    struct {
        uint16_t ch0;
        uint16_t ch1;
        uint16_t ch2;
        uint16_t ch3;
        uint8_t s1;
        uint8_t s2;
    } remote;

    struct {
        int16_t x_axis;
        int16_t y_axis;
        int16_t z_axis;
        uint8_t press_left;
        uint8_t press_right;
    } mouse;

    union {
        uint16_t key_code;
        struct {
            uint16_t W_key : 1;
            uint16_t S_key : 1;
            uint16_t A_key : 1;
            uint16_t D_key : 1;
            uint16_t SHIFT_key : 1;
            uint16_t CTRL_key : 1;
            uint16_t Q_key : 1;
            uint16_t E_key : 1;
            uint16_t R_key : 1;
            uint16_t F_key : 1;
            uint16_t G_key : 1;
            uint16_t Z_key : 1;
            uint16_t X_key : 1;
            uint16_t C_key : 1;
            uint16_t V_key : 1;
            uint16_t B_key : 1;
        } key;
    } KeyBoard;

} RecMsg_t;


/* 结构体外部声明 */

extern RecMsg_t RecMsg;


/* 函数外部声明 */

/// @brief 遥控器数据初始化
/// @param
void remote_init(void);

/// @brief 遥控器数据更新
/// @param rx_buf 数据列表
void remote_data_update(uint8_t rx_buf[REMOTE_DATA_SIZE]);

#endif /*REMOTE_H*/