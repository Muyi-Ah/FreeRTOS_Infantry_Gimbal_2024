/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 23:37:11
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-08 23:41:43
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Inc\simple_verify.h
 * @Description: 
 * 
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved. 
 */
#ifndef SIMPLE_VERIFY_H
#define SIMPLE_VERIFY_H

/*标准库引用*/
#include "stdint.h"


/*函数外部声明*/

int32_t summation(uint8_t* pBuffer, uint32_t lenght);
void append_accumulation_check_sum(uint8_t* pBuffer, uint32_t lenght);
uint8_t verify_accumulation_check_sum(uint8_t* pBuffer, uint32_t lenght);

#endif /*SIMPLE_VERIFY_H*/