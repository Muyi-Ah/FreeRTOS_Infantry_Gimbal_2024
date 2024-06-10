/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-08 07:18:58
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Inc\communication.h
 * @Description: 
 * 
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved. 
 */
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/*标准库引用*/
#include "stdint.h"

/*用户头文件引用*/
#include "simple_verify.h"
#include "sys_config.h"


/*函数外部声明*/

void CommunicationData_Update(uint8_t* rx_buf);

#endif /*COMMUNICATION_H*/