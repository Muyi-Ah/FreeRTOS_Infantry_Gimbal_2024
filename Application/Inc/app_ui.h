/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-08 07:18:32
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Inc\app_ui.h
 * @Description: 
 * 
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved. 
 */
#ifndef APP_UI_H
#define APP_UI_H

#define word_size 23
#define word_width 2

/*标准库引用*/
#include "stdint.h"

/*HAL库引用*/

/*用户头文件引用*/
#include "ui.h"
#include "referee.h"

/* 结构体定义 */
typedef /*__packed*/ struct
{ 
	uint8_t graphic_name[3];
	uint32_t operate_tpye:3;
	uint32_t graphic_tpye:3;
	uint32_t layer:4;
	uint32_t color:4;
	uint32_t start_angle:9;
	uint32_t end_angle:9;
	uint32_t width:10;
	uint32_t start_x:11;
	uint32_t start_y:11;
	uint32_t radius:10;
	uint32_t end_x:11;
	uint32_t end_y:11;
}graphic_data_struct_t;

#endif /*APP_UI_H*/