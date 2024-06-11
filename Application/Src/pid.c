/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-12 02:16:03
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Src\pid.c
 * @Description: 几种模式下的PID控制器
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */
#include "pid.h"


/**
 * @description: 查找与接收ID对应的索引
 * @param {uint32_t} RecId 接收ID
 * @return {int8_t} 索引
 */
int8_t RecId_find(uint32_t RecId)
{
    for (uint8_t index = 0; index < MOTOR_COUNT; index++) {
        if (motor_info_list[index]->RecId == RecId) {
            return index;
        }
    }
    return INDEX_ERROR;
}


/**
 * @description: int16类型限幅
 * @param {int16_t} amt 输入值
 * @param {int16_t} limit 幅值
 * @return {int16_t} 处理后的值
 */
int16_t limit_int16_t(int16_t amt, int16_t limit)
{
    if (amt < -limit)
        return -limit;
    else if (amt > limit)
        return limit;
    else
        return amt;
}


/**
 * @description: int16类型积分限幅
 * @param {int32_t} amt 积分值
 * @param {int16_t} add 误差值
 * @param {int32_t} limit 限幅值
 * @return {int32_t} 处理后的值
 */
int32_t cumulative_limit_int16_t(int32_t amt, int16_t add, int32_t limit)
{
    if ((amt + add) < -limit)
        return -limit;
    else if ((amt + add) > limit)
        return limit;
    return amt + add;
}


/**
 * @description: int32类型限幅
 * @param {int32_t} amt 积分值
 * @param {int32_t} add 误差值
 * @param {int32_t} limit 限幅值
 * @return {int32_t} 处理后的值
 */
int32_t cumulative_limit_int32_t(int32_t amt, int32_t add, int32_t limit)
{
    if ((amt + add) < -limit)
        return -limit;
    else if ((amt + add) > limit)
        return limit;
    return amt + add;
}


/**
 * @description: 输出限幅
 * @param {int32_t} amt 输入值
 * @param {int16_t} limit 限幅值
 * @return {int16_t} 处理后的值
 */
int16_t output_limit(int32_t amt, int16_t limit)
{
    if (amt < -limit)
        return -limit;
    else if (amt > limit)
        return limit;
    else
        return amt;
}


/**
 * @description: 速度PID
 * @param {uint32_t} RecId 接收ID
 * @param {int16_t} target_value 目标值
 * @param {int16_t} target_value_max 目标值限幅
 * @param {PID_param_struct_t} structure PID结构体
 * @return {int8_t} 错误值
 */
int8_t rotating_speed_calculation(uint32_t RecId,
                                  int16_t target_value,
                                  int16_t target_value_max,
                                  PID_param_struct_t structure)
{
    struct rotating_speed_t* pStruture = NULL;
    int32_t local_pid_result           = 0;

    int8_t index = RecId_find(RecId);

    /* 判断指定的 RecId 是否存在 */
    if (index != -1) {
        /* 判断 PID 类型是否为指定类型 */
        if (motor_info_list[index]->PID_type != rotating_speed) {
            /* 释放原 PID 类型结构的内存空间 */
            release_structure_memory(index);

            /* 申请新 PID 类型结构的内存空间 */
            request_structure_memory(index, rotating_speed);
        }
    }

    /* 指定的 RecId 不存在 */
    else {
        return INDEX_ERROR;
    }

    /* 获取该电机的 PID 结构地址 */
    pStruture = motor_info_list[index]->PID_structure_addr;

    /* 将目标值存储到结构中 */
    pStruture->target_value = target_value;

    /* 目标值限制 */
    pStruture->target_value = limit_int16_t(pStruture->target_value, target_value_max);

    /* 将电机返回的转速值转换为正负值 */
    if (motor_info_list[index]->rpm < 32767) {
        pStruture->actual_RPM = motor_info_list[index]->rpm;
    } else if (motor_info_list[index]->rpm > 32767) {
        pStruture->actual_RPM = motor_info_list[index]->rpm - 65535;
    }

    /* 计算误差 */
    pStruture->error = pStruture->target_value - pStruture->actual_RPM;

    /* 积分限幅 */
    if (structure.cumulative_err_max != 0) {
        pStruture->cumulative_error =
            cumulative_limit_int16_t(pStruture->cumulative_error, pStruture->error, structure.cumulative_err_max);
    }

    /* 计算此次 PID 操作的结果 */
    local_pid_result = (pStruture->error * structure.kp) + (pStruture->cumulative_error * structure.ki) +
                       ((pStruture->error - pStruture->error_previous) * structure.kd);

    /* 更新上一次误差值 */
    pStruture->error_previous = pStruture->error;

    /* 输出限幅 */
    pStruture->output = output_limit(local_pid_result, structure.output_max);

    /* 将输出值放入电机信息结构中等待发送 */
    motor_info_list[index]->final_output = pStruture->output;

    return LIB_OK;
}


/**
 * @description: 相对编码器位置PID
 * @param {uint32_t} RecId 接收ID
 * @param {int32_t*} target_value 目标值地址(数据值为8192制)
 * @param {int32_t} delta 目标值与实际值的最大偏移范围
 * @param {int32_t} CW_angle_max 顺时针旋转最大值(8192制)
 * @param {int32_t} CCW_angle_max 逆时针旋转最大值(8192制)
 * @param {PID_param_struct_t} structure PID结构体
 * @return {int8_t} 错误值
 */
int8_t relative_angle_calculation(uint32_t RecId,
                                  int32_t* target_value,
                                  int32_t delta,
                                  int32_t CW_angle_max,
                                  int32_t CCW_angle_max,
                                  PID_param_struct_t structure)
{
    struct relative_angle_t* pStruture   = NULL;
    int32_t local_pid_result             = 0;
    int32_t mechanical_angle_change      = 0;
    int32_t real_mechanical_angle_change = 0;
    int32_t res1 = 0, res2 = 0;

    int8_t index = RecId_find(RecId);

    /* 判断指定的 RecId 是否存在 */
    if (index != INDEX_ERROR) {
        /* 判断 PID 类型是否为指定类型 */
        if (motor_info_list[index]->PID_type != relative_angle) {
            /* 释放原 PID 类型结构的内存空间 */
            release_structure_memory(index);

            /* 申请新 PID 类型结构的内存空间 */
            request_structure_memory(index, relative_angle);
        }
    }

    /* 指定的 RecId 不存在 */
    else {
        return INDEX_ERROR;
    }

    /* 获取该电机的 PID 结构地址 */
    pStruture = motor_info_list[index]->PID_structure_addr;

    // 判断目标值与实际值的偏移范围
    if (delta != 0) {
        int32_t MinValue = ((int32_t)(roll_cumulative_change_angle * 22.755555f)) - delta;
        int32_t MaxValue = ((int32_t)(roll_cumulative_change_angle * 22.755555f)) + delta;

        if (*target_value < MinValue) {
            *target_value = MinValue;
        } else if (*target_value > MaxValue) {
            *target_value = MaxValue;
        }
    }

    /* 将目标值存储到结构中 */
    pStruture->target_value = target_value;

    /* 将机械角度值存储到结构中 */
    pStruture->mechanical_angle = motor_info_list[index]->mechanical_angle;

    /* 计算角度变化值 */
    mechanical_angle_change = pStruture->mechanical_angle - pStruture->mechanical_angle_previous;

    if (mechanical_angle_change > 0) {
        res1 = mechanical_angle_change - 8192;
        res2 = mechanical_angle_change;
    } else {
        res1 = mechanical_angle_change + 8192;
        res2 = mechanical_angle_change;
    }

    if (abs(res1) < abs(res2)) {
        real_mechanical_angle_change = res1;
    } else {
        real_mechanical_angle_change = res2;
    }

    /* 计算累计变化角度 */
    pStruture->spindle_angle_change_sum += real_mechanical_angle_change;

    /* 更新上一次的角度值 */
    pStruture->mechanical_angle_previous = pStruture->mechanical_angle;

    /* 判断是否需要限制角度 */
    if (CW_angle_max || CCW_angle_max) {
        if (pStruture->target_value > CW_angle_max) {
            pStruture->target_value = CW_angle_max;
        } else if (pStruture->target_value < -CCW_angle_max) {
            pStruture->target_value = -CCW_angle_max;
        }
    }

    /* 计算误差 */
    pStruture->error = pStruture->target_value - pStruture->spindle_angle_change_sum;

    /* 积分限幅 */
    if (structure.cumulative_err_max != 0) {
        pStruture->cumulative_error =
            cumulative_limit_int32_t(pStruture->cumulative_error, pStruture->error, structure.cumulative_err_max);
    }

    /* 计算此次 PID 操作的结果 */
    local_pid_result = (pStruture->error * structure.kp) + (pStruture->cumulative_error * structure.ki) +
                       ((pStruture->error - pStruture->error_previous) * structure.kd);

    /* 更新上一次误差值 */
    pStruture->error_previous = pStruture->error;

    /* 输出限幅 */
    pStruture->output = output_limit(local_pid_result, structure.output_max);

    /* 将输出值放入电机信息结构中等待发送 */
    motor_info_list[index]->final_output = pStruture->output;

    return LIB_OK;
}


/**
 * @description: 绝对编码器位置PID
 * @param {uint32_t} RecId 接收ID
 * @param {uint16_t} target_value 目标值(0-8191)
 * @param {enum direction} direct 转动方向
 * @param {PID_param_struct_t} structure PID结构体
 * @return {int8_t} 错误值
 */
int8_t absolute_angle_calculation(uint32_t RecId,
                                  uint16_t target_value,
                                  enum direction direct,
                                  PID_param_struct_t structure)
{
    struct absolute_angle_t* pStruture = NULL;
    int32_t local_pid_result           = 0;
    uint16_t big_value                 = 0;
    uint16_t small_value               = 0;

    int8_t index = RecId_find(RecId);

    /* 判断指定的 RecId 是否存在 */
    if (index != INDEX_ERROR) {
        /* 判断 PID 类型是否为指定类型 */
        if (motor_info_list[index]->PID_type != absolute_angle) {
            /* 释放原 PID 类型结构的内存空间 */
            release_structure_memory(index);

            /* 申请新 PID 类型结构的内存空间 */
            request_structure_memory(index, absolute_angle);
        }
    }

    /* 指定的 RecId 不存在 */
    else {
        return INDEX_ERROR;
    }

    /* 获取该电机的 PID 结构地址 */
    pStruture = motor_info_list[index]->PID_structure_addr;

    /* 判断值是否超出可控范围 */
    if (target_value > 8192) {
        return NUMERICAL_ERROR;
    } else {
        /* 将目标值存储到结构中 */
        pStruture->target_value = target_value;
    }

    /* 将机械角度值存储到结构中 */
    pStruture->mechanical_angle = motor_info_list[index]->mechanical_angle;

    switch (direct) {
        /* 电机以最短距离转到目标位置 */
        case Both:
            if (pStruture->target_value < pStruture->mechanical_angle) {
                small_value = pStruture->target_value;
                big_value   = pStruture->mechanical_angle;
            } else {
                small_value = pStruture->mechanical_angle;
                big_value   = pStruture->target_value;
            }

            if (big_value - small_value < 8192 - abs(small_value - big_value)) {
                if (pStruture->target_value < pStruture->mechanical_angle) {
                    pStruture->error = -(big_value - small_value);
                } else {
                    pStruture->error = big_value - small_value;
                }
            } else {
                if (pStruture->target_value < pStruture->mechanical_angle) {
                    pStruture->error = 8192 - abs(small_value - big_value);
                } else {
                    pStruture->error = -(8192 - abs(small_value - big_value));
                }
            }
            break;

        /* 电机顺时针方向转到目标位置 */
        case CW:
            if (pStruture->target_value < pStruture->mechanical_angle) {
                small_value = pStruture->target_value;
                big_value   = pStruture->mechanical_angle;
            } else {
                small_value = pStruture->mechanical_angle;
                big_value   = pStruture->target_value;
            }

            if (pStruture->target_value < pStruture->mechanical_angle) {
                pStruture->error = 8192 - abs(small_value - big_value);
            } else {
                pStruture->error = big_value - small_value;
            }
            break;

        /* 电机逆时针方向转到目标位置 */
        case CCW:
            if (pStruture->target_value < pStruture->mechanical_angle) {
                small_value = pStruture->target_value;
                big_value   = pStruture->mechanical_angle;
            } else {
                small_value = pStruture->mechanical_angle;
                big_value   = pStruture->target_value;
            }

            if (pStruture->target_value < pStruture->mechanical_angle) {
                pStruture->error = -(big_value - small_value);
            } else {
                pStruture->error = -(8192 - abs(small_value - big_value));
            }
            break;

        default: return DIRECT_ERROR;
    }

    /* 积分限幅 */
    if (structure.cumulative_err_max != 0) {
        pStruture->cumulative_error =
            cumulative_limit_int16_t(pStruture->cumulative_error, pStruture->error, structure.cumulative_err_max);
    }

    /* 计算此次 PID 操作的结果 */
    local_pid_result = (pStruture->error * structure.kp) + (pStruture->cumulative_error * structure.ki) +
                       ((pStruture->error - pStruture->error_previous) * structure.kd);

    /* 更新上一次误差值 */
    pStruture->error_previous = pStruture->error;

    /* 输出限幅 */
    pStruture->output = output_limit(local_pid_result, structure.output_max);

    /* 将输出值放入电机信息结构中等待发送 */
    motor_info_list[index]->final_output = pStruture->output;

    return LIB_OK;
}


/**
 * @description: 绝对编码器位置串级PID
 * @param {uint32_t} RecId 接收ID
 * @param {uint16_t} target_value 目标值(0-8191)
 * @param {enum direction} direct 旋转方向
 * @param {primary_PID_param_struct_t} primary_structure 外环PID结构体
 * @param {secondary_PID_param_struct_t} secondary_structure 内环PID结构体
 * @return {int8_t} 错误值
 */
int8_t absolute_angle_cascade_calculation(uint32_t RecId,
                                          uint16_t target_value,
                                          enum direction direct,
                                          primary_PID_param_struct_t primary_structure,
                                          secondary_PID_param_struct_t secondary_structure)
{
    struct absolute_angle_cascade_t* pStruture = NULL;
    int32_t primary_pid_result                 = 0;
    int32_t secondary_pid_result               = 0;
    uint16_t big_value                         = 0;
    uint16_t small_value                       = 0;

    int8_t index = RecId_find(RecId);

    /* 判断指定的 RecId 是否存在 */
    if (index != INDEX_ERROR) {
        /* 判断 PID 类型是否为指定类型 */
        if (motor_info_list[index]->PID_type != absolute_angle_cascade) {
            /* 释放原 PID 类型结构的内存空间 */
            release_structure_memory(index);

            /* 申请新 PID 类型结构的内存空间 */
            request_structure_memory(index, absolute_angle_cascade);
        }
    }

    /* 指定的 RecId 不存在 */
    else {
        return INDEX_ERROR;
    }

    /* 获取该电机的 PID 结构地址 */
    pStruture = motor_info_list[index]->PID_structure_addr;

    /* 判断值是否超出可控范围 */
    if (target_value > 8192) {
        return NUMERICAL_ERROR;
    } else {
        /* 将目标值存储到结构中 */
        pStruture->primary_target_value = target_value;
    }

    /* 将机械角度值存储到结构中 */
    pStruture->mechanical_angle = motor_info_list[index]->mechanical_angle;

    switch (direct) {
        /* 电机以最短距离转到目标位置 */
        case Both:
            if (pStruture->primary_target_value < pStruture->mechanical_angle) {
                small_value = pStruture->primary_target_value;
                big_value   = pStruture->mechanical_angle;
            } else {
                small_value = pStruture->mechanical_angle;
                big_value   = pStruture->primary_target_value;
            }

            if (big_value - small_value < 8192 - abs(small_value - big_value)) {
                if (pStruture->primary_target_value < pStruture->mechanical_angle) {
                    pStruture->primary_error = -(big_value - small_value);
                } else {
                    pStruture->primary_error = big_value - small_value;
                }
            } else {
                if (pStruture->primary_target_value < pStruture->mechanical_angle) {
                    pStruture->primary_error = 8192 - abs(small_value - big_value);
                } else {
                    pStruture->primary_error = -(8192 - abs(small_value - big_value));
                }
            }
            break;

        /* 电机顺时针方向转到目标位置 */
        case CW:
            if (pStruture->primary_target_value < pStruture->mechanical_angle) {
                small_value = pStruture->primary_target_value;
                big_value   = pStruture->mechanical_angle;
            } else {
                small_value = pStruture->mechanical_angle;
                big_value   = pStruture->primary_target_value;
            }

            if (pStruture->primary_target_value < pStruture->mechanical_angle) {
                pStruture->primary_error = 8192 - abs(small_value - big_value);
            } else {
                pStruture->primary_error = big_value - small_value;
            }
            break;

        /* 电机逆时针方向转到目标位置 */
        case CCW:
            if (pStruture->primary_target_value < pStruture->mechanical_angle) {
                small_value = pStruture->primary_target_value;
                big_value   = pStruture->mechanical_angle;
            } else {
                small_value = pStruture->mechanical_angle;
                big_value   = pStruture->primary_target_value;
            }

            if (pStruture->primary_target_value < pStruture->mechanical_angle) {
                pStruture->primary_error = -(big_value - small_value);
            } else {
                pStruture->primary_error = -(8192 - abs(small_value - big_value));
            }
            break;

        default: return DIRECT_ERROR;
    }

    /* 积分限幅 */
    if (primary_structure.cumulative_err_max != 0) {
        pStruture->primary_cumulative_error = cumulative_limit_int16_t(
            pStruture->primary_cumulative_error, pStruture->primary_error, primary_structure.cumulative_err_max);
    }

    /* 计算此次 PID 操作的结果 */
    primary_pid_result = (pStruture->primary_error * primary_structure.kp) +
                         (pStruture->primary_cumulative_error * primary_structure.ki) +
                         ((pStruture->primary_error - pStruture->primary_error_previous) * primary_structure.kd);

    /* 更新上一次误差值 */
    pStruture->primary_error_previous = pStruture->primary_error;

    /* 输出限幅 */
    pStruture->primary_output = output_limit(primary_pid_result, primary_structure.output_max);

    /*******************************************外环计算结束*************************************************/

    pStruture->secondary_target_value = pStruture->primary_output;

    /* 将电机返回的转速值转换为正负值 */
    if (motor_info_list[index]->rpm < 32767) {
        pStruture->secondary_error = pStruture->secondary_target_value - motor_info_list[index]->rpm;
    } else if (motor_info_list[index]->rpm > 32767) {
        pStruture->secondary_error = pStruture->secondary_target_value - (motor_info_list[index]->rpm - 65535);
    }

    /* 积分限幅 */
    if (secondary_structure.cumulative_err_max != 0) {
        pStruture->secondary_cumulative_error = cumulative_limit_int16_t(
            pStruture->secondary_cumulative_error, pStruture->secondary_error, secondary_structure.cumulative_err_max);
    }

    /* 计算此次 PID 操作的结果 */
    secondary_pid_result =
        (pStruture->secondary_error * secondary_structure.kp) +
        (pStruture->secondary_cumulative_error * secondary_structure.ki) +
        ((pStruture->secondary_error - pStruture->secondary_error_previous) * secondary_structure.kd);

    /* 更新上一次误差值 */
    pStruture->secondary_error_previous = pStruture->secondary_error;

    /* 输出限幅 */
    pStruture->secondary_output = output_limit(secondary_pid_result, secondary_structure.output_max);

    /* 将输出值放入电机信息结构中等待发送 */
    motor_info_list[index]->final_output = pStruture->secondary_output;

    return LIB_OK;
}


/**
 * @description: 相对编码器位置串级PID
 * @param {uint32_t} RecId 接收ID
 * @param {int32_t*} target_value 目标值地址(数据值为8192制)
 * @param {int32_t} delta 目标值与实际值的最大偏移范围
 * @param {int32_t} CW_angle_max 顺时针旋转最大值
 * @param {int32_t} CCW_angle_max 逆时针旋转最大值
 * @param {primary_PID_param_struct_t} primary_structure 外环PID结构体
 * @param {secondary_PID_param_struct_t} secondary_structure 内环PID结构体
 * @return {int8_t} 错误值
 */
int8_t relative_angle_cascade_calculation(uint32_t RecId,
                                          int32_t* target_value,
                                          int32_t delta,
                                          int32_t CW_angle_max,
                                          int32_t CCW_angle_max,
                                          primary_PID_param_struct_t primary_structure,
                                          secondary_PID_param_struct_t secondary_structure)
{
    struct relative_angle_cascade_t* pStruture = NULL;
    int32_t primary_pid_result                 = 0;
    int32_t secondary_pid_result               = 0;
    int32_t mechanical_angle_change            = 0;
    int32_t real_mechanical_angle_change       = 0;
    int32_t res1 = 0, res2 = 0;

    int8_t index = RecId_find(RecId);

    /* 判断指定的 RecId 是否存在 */
    if (index != INDEX_ERROR) {
        /* 判断 PID 类型是否为指定类型 */
        if (motor_info_list[index]->PID_type != relative_angle_cascade) {
            /* 释放原 PID 类型结构的内存空间 */
            release_structure_memory(index);

            /* 申请新 PID 类型结构的内存空间 */
            request_structure_memory(index, relative_angle_cascade);
        }
    }

    /* 指定的 RecId 不存在 */
    else {
        return INDEX_ERROR;
    }

    /* 获取该电机的 PID 结构地址 */
    pStruture = motor_info_list[index]->PID_structure_addr;

    // 判断目标值与实际值的偏移范围
    if (delta != 0) {
        int32_t MinValue = ((int32_t)(roll_cumulative_change_angle * 22.755555f)) - delta;
        int32_t MaxValue = ((int32_t)(roll_cumulative_change_angle * 22.755555f)) + delta;

        if (*target_value < MinValue) {
            *target_value = MinValue;
        } else if (*target_value > MaxValue) {
            *target_value = MaxValue;
        }
    }

    /* 将目标值存储到结构中 */
    pStruture->primary_target_value = target_value;

    /* 将机械角度值存储到结构中 */
    pStruture->mechanical_angle = motor_info_list[index]->mechanical_angle;

    if (!pStruture->used) {
        pStruture->mechanical_angle_previous = pStruture->mechanical_angle;
        pStruture->used                      = 1;
    }

    /* 计算角度变化值 */
    mechanical_angle_change = pStruture->mechanical_angle - pStruture->mechanical_angle_previous;

    if (mechanical_angle_change > 0) {
        res1 = mechanical_angle_change - 8192;
        res2 = mechanical_angle_change;
    } else {
        res1 = mechanical_angle_change + 8192;
        res2 = mechanical_angle_change;
    }

    if (abs(res1) < abs(res2)) {
        real_mechanical_angle_change = res1;
    } else {
        real_mechanical_angle_change = res2;
    }

    /* 计算累计变化角度 */
    pStruture->spindle_angle_change_sum += real_mechanical_angle_change;

    /* 更新上一次的角度值 */
    pStruture->mechanical_angle_previous = pStruture->mechanical_angle;

    /* 判断是否需要限制角度 */
    if (CW_angle_max || CCW_angle_max) {
        if (pStruture->primary_target_value > CW_angle_max) {
            pStruture->primary_target_value = CW_angle_max;
        } else if (pStruture->primary_target_value < -CCW_angle_max) {
            pStruture->primary_target_value = -CCW_angle_max;
        }
    }

    /* 计算误差 */
    pStruture->primary_error = pStruture->primary_target_value - pStruture->spindle_angle_change_sum;

    /* 积分限幅 */
    if (primary_structure.cumulative_err_max != 0) {
        pStruture->primary_cumulative_error = cumulative_limit_int32_t(
            pStruture->primary_cumulative_error, pStruture->primary_error, primary_structure.cumulative_err_max);
    }

    /* 计算此次 PID 操作的结果 */
    primary_pid_result = (pStruture->primary_error * primary_structure.kp) +
                         (pStruture->primary_cumulative_error * primary_structure.ki) +
                         ((pStruture->primary_error - pStruture->primary_error_previous) * primary_structure.kd);

    /* 更新上一次误差值 */
    pStruture->primary_error_previous = pStruture->primary_error;

    /* 输出限幅 */
    pStruture->primary_output = output_limit(primary_pid_result, primary_structure.output_max);

    /*******************************************外环计算结束*************************************************/

    pStruture->secondary_target_value = pStruture->primary_output;

    /* 将电机返回的转速值转换为正负值 */
    if (motor_info_list[index]->rpm < 32767) {
        pStruture->secondary_error = pStruture->secondary_target_value - motor_info_list[index]->rpm;
    } else if (motor_info_list[index]->rpm > 32767) {
        pStruture->secondary_error = pStruture->secondary_target_value - (motor_info_list[index]->rpm - 65535);
    }

    /* 积分限幅 */
    if (secondary_structure.cumulative_err_max != 0) {
        pStruture->secondary_cumulative_error = cumulative_limit_int16_t(
            pStruture->secondary_cumulative_error, pStruture->secondary_error, secondary_structure.cumulative_err_max);
    }

    /* 计算此次 PID 操作的结果 */
    secondary_pid_result =
        (pStruture->secondary_error * secondary_structure.kp) +
        (pStruture->secondary_cumulative_error * secondary_structure.ki) +
        ((pStruture->secondary_error - pStruture->secondary_error_previous) * secondary_structure.kd);

    /* 更新上一次误差值 */
    pStruture->secondary_error_previous = pStruture->secondary_error;

    /* 输出限幅 */
    pStruture->secondary_output = output_limit(secondary_pid_result, secondary_structure.output_max);

    /* 将输出值放入电机信息结构中等待发送 */
    motor_info_list[index]->final_output = pStruture->secondary_output;

    return LIB_OK;
}


/**
 * @description: 基于CH110 IMU串级PID
 * @param {uint32_t} RecId 接收ID
 * @param {int32_t*} target_value 目标值地址(数据值为8192制)
 * @param {int32_t} delta 目标值与实际值的最大偏移范围
 * @param {enum euler_axis} angular_velocity_axis 转轴数据源
 * @param {enum speed_loop_data_source} speed_src 速度数据源
 * @param {uint8_t} output_inversion 输出是否反向
 * @param {primary_PID_param_struct_t} primary_structure 外环PID结构体
 * @param {secondary_PID_param_struct_t} secondary_structure 内环PID结构体
 * @return {int8_t} 错误值
 */
int8_t CH110_gyro_angle_cascade_calculation(uint32_t RecId,
                                            int32_t* target_value,
                                            int32_t delta,
                                            enum euler_axis angular_velocity_axis,
                                            enum speed_loop_data_source speed_src,
                                            uint8_t output_inversion,
                                            primary_PID_param_struct_t primary_structure,
                                            secondary_PID_param_struct_t secondary_structure)
{
    struct gyro_angle_cascade_t* pStruture = NULL;
    int32_t primary_pid_result             = 0;
    int32_t secondary_pid_result           = 0;

    int8_t index = RecId_find(RecId);

    /* 判断指定的 RecId 是否存在 */
    if (index != INDEX_ERROR) {
        /* 判断 PID 类型是否为指定类型 */
        if (motor_info_list[index]->PID_type != gyro_angle_cascade) {
            /* 释放原 PID 类型结构的内存空间 */
            release_structure_memory(index);

            /* 申请新 PID 类型结构的内存空间 */
            request_structure_memory(index, gyro_angle_cascade);
        }
    }

    /* 指定的 RecId 不存在 */
    else {
        return INDEX_ERROR;
    }

    /* 获取该电机的 PID 结构地址 */
    pStruture = motor_info_list[index]->PID_structure_addr;

    // 判断目标值与实际值的偏移范围
    if (delta != 0) {
        int32_t MinValue = ((int32_t)(roll_cumulative_change_angle * 22.755555f)) - delta;
        int32_t MaxValue = ((int32_t)(roll_cumulative_change_angle * 22.755555f)) + delta;

        if (*target_value < MinValue) {
            *target_value = MinValue;
        } else if (*target_value > MaxValue) {
            *target_value = MaxValue;
        }
    }

    /* 将目标值存储到结构中 */
    pStruture->primary_target_value = *target_value;

    /* 判断使用哪个轴 */
    if (angular_velocity_axis == roll) {
        /* 计算误差 */
        /* 此处将陀螺仪值转换为0-8192 */
        pStruture->primary_error =
            pStruture->primary_target_value - ((int32_t)(roll_cumulative_change_angle * 22.755555f));
    }

    /* 判断使用哪个轴 */
    else if (angular_velocity_axis == pitch) {
        /* 计算误差 */
        /* 此处将陀螺仪值转换为0-8192 */
        pStruture->primary_error =
            pStruture->primary_target_value - ((int32_t)(pitch_cumulative_change_angle * 22.755555f));
    }

    /* 判断使用哪个轴 */
    else if (angular_velocity_axis == yaw) {
        /* 计算误差 */
        /* 此处将陀螺仪值转换为0-8192 */
        pStruture->primary_error =
            pStruture->primary_target_value - ((int32_t)(yaw_cumulative_change_angle * 22.755555f));
    }

    /* 积分限幅 */
    if (primary_structure.cumulative_err_max != 0) {
        pStruture->primary_cumulative_error = cumulative_limit_int16_t(
            pStruture->primary_cumulative_error, pStruture->primary_error, primary_structure.cumulative_err_max);
    }

    /* 计算此次 PID 操作的结果 */
    primary_pid_result = (pStruture->primary_error * primary_structure.kp) +
                         (pStruture->primary_cumulative_error * primary_structure.ki) +
                         ((pStruture->primary_error - pStruture->primary_error_previous) * primary_structure.kd);

    /* 更新上一次误差值 */
    pStruture->primary_error_previous = pStruture->primary_error;

    /* 输出限幅 */
    pStruture->primary_output = output_limit(primary_pid_result, primary_structure.output_max);

    /*******************************************外环计算结束*************************************************/

    pStruture->secondary_target_value = pStruture->primary_output;

    /* 使用电机速度作为速度源 */
    /* 将电机返回的转速值转换为正负值 */
    if (speed_src == motor) {
        if (motor_info_list[index]->rpm < 32767) {
            pStruture->secondary_error = pStruture->secondary_target_value - motor_info_list[index]->rpm;
        } else if (motor_info_list[index]->rpm > 32767) {
            pStruture->secondary_error = pStruture->secondary_target_value - (motor_info_list[index]->rpm - 65535);
        }
    }
    /* 使用陀螺仪角速度作为速度源 */
    else if (speed_src == gyro) {
        if (angular_velocity_axis == roll) {
            pStruture->secondary_error = pStruture->secondary_target_value - CH110_data.X_axisAngularVelocity;
        } else if (angular_velocity_axis == pitch) {
            pStruture->secondary_error = pStruture->secondary_target_value - CH110_data.Y_axisAngularVelocity;
        } else if (angular_velocity_axis == yaw) {
            pStruture->secondary_error = pStruture->secondary_target_value - CH110_data.Z_axisAngularVelocity;
        }
    }

    /* 积分限幅 */
    if (secondary_structure.cumulative_err_max != 0) {
        pStruture->secondary_cumulative_error = cumulative_limit_int16_t(
            pStruture->secondary_cumulative_error, pStruture->secondary_error, secondary_structure.cumulative_err_max);
    }

    /* 计算此次 PID 操作的结果 */
    secondary_pid_result =
        (pStruture->secondary_error * secondary_structure.kp) +
        (pStruture->secondary_cumulative_error * secondary_structure.ki) +
        ((pStruture->secondary_error - pStruture->secondary_error_previous) * secondary_structure.kd);

    /* 更新上一次误差值 */
    pStruture->secondary_error_previous = pStruture->secondary_error;

    /* 输出限幅 */
    pStruture->secondary_output = output_limit(secondary_pid_result, secondary_structure.output_max);

    /* 将输出值放入电机信息结构中等待发送 */
    if (output_inversion == 0U) {
        motor_info_list[index]->final_output = pStruture->secondary_output;
    } else {
        motor_info_list[index]->final_output = -pStruture->secondary_output;
    }

    return LIB_OK;
}