/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2024-06-08 03:28:24
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2024-06-08 03:28:37
 * @FilePath: \workspace (工作区)c:\Users\Ryan\Desktop\新建文件夹 (4)\error_detection.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef ERROR_DETECTION_H
#define ERROR_DETECTION_H

/*标准库引用*/
#include "stdint.h"

/*HAL库引用*/

/*用户头文件引用*/
#include "sys_config.h"

/* 变量外部声明 */  
extern uint8_t motor_error;
extern uint8_t error_motor[motor_count];

extern uint8_t IMU_online_reply;
extern uint8_t IMU_error;

extern uint8_t remote_online_reply;
extern uint8_t remote_error;

extern uint8_t communication_online_reply;
extern uint8_t communication_error;

/* 函数外部声明 */

#endif /*ERROR_DETECTION_H*/