/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-10 17:39:35
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Src\gimbal.c
 * @Description: 云台任务
 * 
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved. 
 */
#include "gimbal.h"


void Gimbal_Task(void *argument){
    for(;;){

        /*解决串口ORE问题*/
        if (__HAL_UART_GET_FLAG(&REMOTE_UART, UART_FLAG_ORE)!=RESET)
        {
            /*清除ORE位*/
            __HAL_UART_CLEAR_OREFLAG( &REMOTE_UART );
            
            /* 重新启动接收 */
            HAL_UARTEx_ReceiveToIdle_DMA(&REMOTE_UART, remote_rx_buf, REMOTE_DATA_SIZE);
        }

        if (__HAL_UART_GET_FLAG(&COMMUNICATE_UART, UART_FLAG_ORE)!=RESET)
        {
            /*清除ORE位*/
           __HAL_UART_CLEAR_OREFLAG( &COMMUNICATE_UART );

            /* 重新启动接收 */
           HAL_UARTEx_ReceiveToIdle_DMA(&COMMUNICATE_UART, communication_rx_buf, COMMUNICATION_RECEIVE_DATA_SIZE);
        }
        
        
    }
}