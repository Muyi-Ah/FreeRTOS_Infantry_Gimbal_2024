/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2024-06-08 03:41:26
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2024-06-08 03:41:38
 * @FilePath: \workspace (工作区)c:\Users\Ryan\Desktop\新建文件夹 (4)\remote.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "remote.h"

/* 创建结构体 */
RecMsg_t RecMsg;

void remote_init(void)
{
    RecMsg.remote.ch0 = 1024;
    RecMsg.remote.ch1 = 1024;
    RecMsg.remote.ch2 = 1024;
    RecMsg.remote.ch3 = 1024;
}

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