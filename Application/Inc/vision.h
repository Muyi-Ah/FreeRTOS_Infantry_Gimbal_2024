/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-12 21:44:23
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Inc\vision.h
 * @Description:
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */
#ifndef VISION_H
#define VISION_H

/*标准库引用*/
#include "stdint.h"
#include "stdio.h"


//  ==== 枚举定义 ====

enum AimType { Armor, RobotHub };


//  ==== 结构体定义 ====

struct vision_t {
    uint8_t Use;
    uint8_t IsAimed;
    uint8_t IsFire;
    enum AimType AimType;
    float VisionTargetYaw;
    float VisionTargetPitch;
};

//  ==== 结构体外部声明 ====
extern struct vision_t vision;

//  ==== 函数外部声明 ====
void VisionData_Update(volatile const uint8_t* buf);

#endif /*VISION_H*/