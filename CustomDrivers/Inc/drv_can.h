/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:12
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-08 11:12:54
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\CustomDrivers\Inc\drv_can.h
 * @Description:
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */
#ifndef DRV_CAN_H
#define DRV_CAN_H

/*标准库引用*/
#include "stdint.h"

/*HAL库引用*/
#include "can.h"

/*用户头文件引用*/
#include "CH110.h"
#include "error_detection.h"
#include "motor.h"
#include "sys_config.h"


/* 函数外部声明 */

void can_manage_init(void);

#endif /*DRV_CAN_H*/