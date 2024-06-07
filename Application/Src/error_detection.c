/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2024-06-08 03:38:23
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2024-06-08 03:38:46
 * @FilePath: \workspace (工作区)c:\Users\Ryan\Desktop\新建文件夹 (4)\error_detection.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "error_detection.h"

/* 创建变量 */
uint8_t motor_error;
uint8_t error_motor[motor_count];

uint8_t IMU_online_reply;
uint8_t IMU_error;

uint8_t remote_online_reply;
uint8_t remote_error;

uint8_t communication_online_reply;
uint8_t communication_error;