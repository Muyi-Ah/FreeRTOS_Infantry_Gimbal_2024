/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-12 21:23:36
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Src\vision.c
 * @Description: 视觉数据处理
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */
#include "vision.h"

uint16_t RobotHubYaw, RobotHubPitch, ArmorYaw, ArmorPitch;
uint8_t VisionFireFlag;
struct vision_t vision;

void VisionData_Update(volatile const uint8_t* buf)
{
    uint16_t recvParamCnt;

    // 字符转整形
    recvParamCnt = sscanf((const char*)buf,
                          "[%4hu/%4hu/%4hu/%4hu/%1hu]",
                          &RobotHubYaw,
                          &RobotHubPitch,
                          &ArmorYaw,
                          &ArmorPitch,
                          &VisionFireFlag);

    vision.IsAimed = 0; // 假设接收失败

    // 数据有误
    if (recvParamCnt != 5) {
        vision.IsAimed = 0;
        vision.IsFire  = 0;
        return;
    }
    if (RobotHubYaw == 0 && RobotHubPitch == 0 && ArmorYaw == 0 && ArmorPitch == 0) {
        vision.IsAimed = 0;
        vision.IsFire  = 0;
        return;
    }

    vision.IsAimed = 1;              // 接收成功
    vision.IsFire  = VisionFireFlag; // 开火标志位

    if (vision.AimType == RobotHub) // 中心瞄准模式
    {
        vision.VisionTargetYaw   = (float)(RobotHubYaw - 1000);
        vision.VisionTargetPitch = (float)(RobotHubPitch - 1000);
    } else if (vision.AimType == Armor) // 装甲板瞄准模式
    {
        vision.VisionTargetYaw   = (float)(ArmorYaw - 1000);
        vision.VisionTargetPitch = (float)(ArmorPitch - 1000);
    }
}