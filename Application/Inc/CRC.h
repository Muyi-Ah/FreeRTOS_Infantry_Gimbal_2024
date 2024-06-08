/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 07:22:29
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-08 17:49:41
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Inc\CRC.h
 * @Description:
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */
#ifndef CRC_H
#define CRC_H

/*标准库引用*/
#include "stdint.h"
#include "stdlib.h"


/*函数外部声明*/

unsigned char Get_CRC8_Check_Sum(unsigned char* pchMessage, unsigned int dwLength, unsigned char ucCRC8);
unsigned int Verify_CRC8_Check_Sum(unsigned char* pchMessage, unsigned int dwLength);
void Append_CRC8_Check_Sum(unsigned char* pchMessage, unsigned int dwLength);
uint16_t Get_CRC16_Check_Sum(uint8_t* pchMessage, uint32_t dwLength, uint16_t wCRC);
uint32_t Verify_CRC16_Check_Sum(uint8_t* pchMessage, uint32_t dwLength);
void Append_CRC16_Check_Sum(uint8_t* pchMessage, uint32_t dwLength);

#endif /*CRC_H*/