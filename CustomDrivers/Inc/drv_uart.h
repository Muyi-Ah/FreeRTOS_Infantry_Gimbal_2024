/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2024-06-08 03:45:26
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2024-06-08 03:46:10
 * @FilePath: \workspace (工作区)c:\Users\Ryan\Desktop\新建文件夹 (4)\CustomDrivers\drv_uart.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef DRV_UART_H
#define DRV_UART_H

/*标准库引用*/
#include "stdint.h"

/*HAL库引用*/
#include "usart.h"

/*用户头文件引用*/
#include "sys_config.h"
#include "error_detection.h"
#include "remote.h"

/* 函数外部声明 */
void uart_manage_init(void);
void uart_msg_send(UART_HandleTypeDef* huart, uint8_t* pBuffer, uint16_t Lenght);

#endif /*DRV_UART_H*/