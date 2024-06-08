/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:12
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-08 19:47:34
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\CustomDrivers\Src\drv_uart.c
 * @Description: 串口数据处理
 * 
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved. 
 */
#include "drv_uart.h"

/* 创建变量 */
uint8_t remote_rx_buf[remote_data_size];


/**
 * @description: 串口启动接收
 * @return {*}
 */
void uart_manage_init(void)
{
    HAL_UARTEx_ReceiveToIdle_IT(&remote_uart, remote_rx_buf, remote_data_size);
    // HAL_UARTEx_ReceiveToIdle_IT( &communication_uart, communication_rx_buf, communication_receive_data_size );
    // HAL_UARTEx_ReceiveToIdle_IT( &vision_uart, vision_rx_buf, vision_receive_data_size );
}


/**
 * @description: 串口数据发送
 * @param {UART_HandleTypeDef*} huart 串口实例指针
 * @param {uint8_t*} pBuffer 数据列表
 * @param {uint16_t} Lenght 长度
 * @return {*}
 */
void uart_msg_send(UART_HandleTypeDef* huart, uint8_t* pBuffer, uint16_t Lenght)
{
    // taskENTER_CRITICAL();
    HAL_UART_Transmit_IT(huart, pBuffer, Lenght);
    // taskEXIT_CRITICAL();
}


/**
 * @description: 串口回调函数
 * @param {UART_HandleTypeDef*} huart 串口实例指针
 * @param {uint16_t} Size 大小
 * @return {*}
 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* huart, uint16_t Size)
{
    /* 遥控器实例 */
    if (huart->Instance == remote_uart.Instance) {
        /* 更新遥控器数据 */
        remote_data_update(remote_rx_buf);

        /* 重新启动接收 */
        HAL_UARTEx_ReceiveToIdle_IT(&remote_uart, remote_rx_buf, remote_data_size);

        /* 遥控器在线标志位 */
        remote_online_reply = 1U;
    }

    /* 上下板通信和视觉通信先不写 */
}