/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-11 14:48:21
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Src\remote.c
 * @Description: 遥控器数据处理
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */
#include "remote.h"

/// @brief 遥控器数据结构体
RecMsg_t RecMsg;


void remote_init(void)
{
    RecMsg.remote.ch0 = 1024;
    RecMsg.remote.ch1 = 1024;
    RecMsg.remote.ch2 = 1024;
    RecMsg.remote.ch3 = 1024;
}


void StateMachine_SubState_Update(void)
{
    // 左侧拨杆
    switch (RecMsg.remote.s1) {
        case Top:
            // 右侧拨杆
            switch (RecMsg.remote.s2) {
                case Top: StateMachine_HandleEvent(&state_machine, EVENT_SWITCH_MODE_11); break;
                case Mid: StateMachine_HandleEvent(&state_machine, EVENT_SWITCH_MODE_12); break;
                case Bottom: StateMachine_HandleEvent(&state_machine, EVENT_SWITCH_MODE_13); break;

                default: break;
            } /* s2 end */
            break;

        case Mid:
            // 右侧拨杆
            switch (RecMsg.remote.s2) {
                case Top: StateMachine_HandleEvent(&state_machine, EVENT_SWITCH_MODE_21); break;
                case Mid: StateMachine_HandleEvent(&state_machine, EVENT_SWITCH_MODE_22); break;
                case Bottom: StateMachine_HandleEvent(&state_machine, EVENT_SWITCH_MODE_23); break;

                default: break;
            } /* s2 end */
            break;

        case Bottom:
            // 右侧拨杆
            switch (RecMsg.remote.s2) {
                case Top: StateMachine_HandleEvent(&state_machine, EVENT_SWITCH_MODE_31); break;
                case Mid: StateMachine_HandleEvent(&state_machine, EVENT_SWITCH_MODE_32); break;
                case Bottom: StateMachine_HandleEvent(&state_machine, EVENT_SWITCH_MODE_33); break;

                default: break;
            } /* s2 end */
            break;

        default: break;
    } /* s1 end */
}


void remote_data_update(uint8_t rx_buf[REMOTE_DATA_SIZE])
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

    // 状态机子状态更新
    StateMachine_SubState_Update();
}