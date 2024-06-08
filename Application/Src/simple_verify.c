/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 23:35:57
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-08 23:40:50
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Src\simple_verify.c
 * @Description:
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */
#include "simple_verify.h"


/**
 * @description: 算出列表末尾四个字节前的数据累加值
 * @param {uint8_t} *pBuffer 列表首地址
 * @param {uint32_t} lenght 长度(字节)
 * @return {int32_t} 累加值
 */
int32_t summation(uint8_t* pBuffer, uint32_t lenght)
{
    int32_t result = 0;

    for (uint8_t index = 0; index < lenght - 4; index++) {
        result += pBuffer[index];
    }

    return result;
}


/**
 * @description: 附加校验值到列表最后四个字节
 * @param {uint8_t} *pBuffer 列表首地址
 * @param {uint32_t} lenght 长度(字节)
 * @return {void}
 */
void append_accumulation_check_sum(uint8_t* pBuffer, uint32_t lenght)
{
    int32_t result = 0;

    result = summation(pBuffer, lenght);

    pBuffer[lenght - 4] = result;
    pBuffer[lenght - 3] = result >> 8;
    pBuffer[lenght - 2] = result >> 16;
    pBuffer[lenght - 1] = result >> 24;
}


/**
 * @description: 校验数据是否无误
 * @param {uint8_t} *pBuffer 列表首地址
 * @param {uint32_t} lenght 长度(字节)
 * @return {uint8_t} true or false
 */
uint8_t verify_accumulation_check_sum(uint8_t* pBuffer, uint32_t lenght)
{
    int32_t buffer_result;
    int32_t accumulation_result;

    buffer_result =
        pBuffer[lenght - 4] | pBuffer[lenght - 3] << 8 | pBuffer[lenght - 2] << 16 | pBuffer[lenght - 1] << 24;

    accumulation_result = summation(pBuffer, lenght);

    if (buffer_result == accumulation_result) {
        return 1U;
    } else {
        return 0U;
    }
}