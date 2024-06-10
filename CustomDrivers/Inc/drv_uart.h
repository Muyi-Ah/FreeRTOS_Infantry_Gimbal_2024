/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:12
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-10 17:21:45
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\CustomDrivers\Inc\drv_uart.h
 * @Description:
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */
#ifndef DRV_UART_H
#define DRV_UART_H

/*标准库引用*/
#include "stdint.h"

/*HAL库引用*/
#include "usart.h"

/*用户头文件引用*/
#include "communication.h"
#include "error_detection.h"
#include "remote.h"
#include "sys_config.h"


/*变量外部声明*/

extern uint8_t remote_rx_buf[REMOTE_DATA_SIZE];
extern uint8_t communication_rx_buf[COMMUNICATION_RECEIVE_DATA_SIZE];

/* 函数外部声明 */

void uart_manage_init(void);
void uart_msg_send(UART_HandleTypeDef* huart, uint8_t* pBuffer, uint16_t Lenght);

#endif /*DRV_UART_H*/