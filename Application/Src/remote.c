/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-08 11:05:35
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Src\remote.c
 * @Description: 遥控器数据处理
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */
#include "remote.h"

/* 创建结构体 */
RecMsg_t RecMsg;


/**
 * @description: 遥控器数据初始化
 * @return {void}
 */
void remote_init(void)
{
    RecMsg.remote.ch0 = 1024;
    RecMsg.remote.ch1 = 1024;
    RecMsg.remote.ch2 = 1024;
    RecMsg.remote.ch3 = 1024;
}


/**
 * @description: 遥控器数据更新
 * @param {uint8_t} rx_buf 数据列表
 * @return {void}
 */
void remote_data_update(uint8_t rx_buf[remote_data_size])
{
    RecMsg.remote.ch0 = (rx_buf[0] | rx_buf[1] << 8) & 0x07FF;
    RecMsg.remote.ch1 = (rx_buf[1] >> 3 | rx_buf[2] << 5) & 0x07FF;
    RecMsg.remote.ch2 = (rx_buf[2] >> 6 | rx_buf[3] << 2 | rx_buf[4] << 10) & 0x07FF;
    RecMsg.remote.ch3 = (rx_buf[4] >> 1 | rx_buf[5] << 7) & 0x07FF;

    RecMsg.remote.s1 = ((rx_buf[5] >> 4) & 0x000C) >> 2;
    RecMsg.remote.s2 = ((rx_buf[5] >> 4) & 0x0003);

    RecMsg.mouse.x_axis = (rx_buf[6] | rx_buf[7] << 8);
    RecMsg.mouse.y_axis = (rx_buf[8] | rx_buf[9] << 8);
    RecMsg.mouse.z_axis = (rx_buf[10] | rx_buf[11] << 8);

    RecMsg.mouse.press_left  = rx_buf[12];
    RecMsg.mouse.press_right = rx_buf[13];

    RecMsg.KeyBoard.key_code = (rx_buf[14] | rx_buf[15] << 8);
}