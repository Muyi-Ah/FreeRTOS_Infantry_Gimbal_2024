/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-09 00:13:09
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Src\communication.c
 * @Description: 版间通信
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */
#include "communication.h"


/*创建变量*/

uint8_t communication_send_buf[COMMUNICATION_SEND_DATA_SIZE];


/**
 * @description: 板间通信数据更新
 * @param {uint8_t*} rx_buf 数据接收数组
 * @return {void}
 */
void CommunicationData_Update(uint8_t* rx_buf)
{
    if (verify_accumulation_check_sum(rx_buf, COMMUNICATION_RECEIVE_DATA_LENGTH)) {
        /* code */
    }
}


/**
 * @description: 板间通信数据发送
 * @return {void}
 */
void CommunicationData_Send(void)
{
    /* code */

    /* 附加校验值 */
    append_accumulation_check_sum(communication_send_buf, COMMUNICATION_SEND_DATA_SIZE);

    /* 发送数据到下板 */
    // uart_msg_send( &COMMUNICATE_UART, communication_send_buf, COMMUNICATION_SEND_DATA_SIZE );
}