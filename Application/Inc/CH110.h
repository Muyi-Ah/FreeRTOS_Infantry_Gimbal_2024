/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2024-06-08 03:25:00
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2024-06-08 05:15:36
 * @FilePath: \workspace (工作区)c:\Users\Ryan\Desktop\新建文件夹 (4)\CH110.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef CH110_H
#define CH110_H\

/*标准库引用*/
#include "stdint.h"
#include "math.h"

/*HAL库引用*/

/*用户头文件引用*/

/* 结构体定义 */
typedef struct{
	float roll; /* x轴 */
	float pitch;/* y轴 */
	float yaw;	/* z轴 */
	int16_t X_axisAngularVelocity;
	int16_t Y_axisAngularVelocity;
	int16_t Z_axisAngularVelocity;
}CH110_data_t;

/* 变量外部声明 */
extern CH110_data_t CH110_data;
extern float roll_cumulative_change_angle;
extern float pitch_cumulative_change_angle;
extern float yaw_cumulative_change_angle;

/* 函数外部声明 */
void CH110_cumulative_update(void);

#endif /*CH110_H*/