/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2024-06-08 03:33:01
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2024-06-08 03:33:09
 * @FilePath: \workspace (工作区)c:\Users\Ryan\Desktop\新建文件夹 (4)\remote.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef REMOTE_H
#define REMOTE_H

/*标准库引用*/
#include "stdint.h"

/*HAL库引用*/

/*用户头文件引用*/
#include "sys_config.h"

/* 结构体定义 */
typedef struct {
    struct {
        uint16_t ch0;
        uint16_t ch1;
        uint16_t ch2;
        uint16_t ch3;
        uint8_t s1;
        uint8_t s2;
    } remote;

    struct {
        int16_t x_axis;
        int16_t y_axis;
        int16_t z_axis;
        uint8_t press_left;
        uint8_t press_right;
    } mouse;

    union {
        uint16_t key_code;
        struct {
            uint16_t W_key : 1;
            uint16_t S_key : 1;
            uint16_t A_key : 1;
            uint16_t D_key : 1;
            uint16_t SHIFT_key : 1;
            uint16_t CTRL_key : 1;
            uint16_t Q_key : 1;
            uint16_t E_key : 1;
            uint16_t R_key : 1;
            uint16_t F_key : 1;
            uint16_t G_key : 1;
            uint16_t Z_key : 1;
            uint16_t X_key : 1;
            uint16_t C_key : 1;
            uint16_t V_key : 1;
            uint16_t B_key : 1;
        } key;
    } KeyBoard;

} RecMsg_t;

/* 结构体外部声明 */
extern RecMsg_t RecMsg;

/* 函数外部声明 */
void remote_init(void);
void remote_data_update(uint8_t rx_buf[remote_data_size]);

#endif /*REMOTE_H*/