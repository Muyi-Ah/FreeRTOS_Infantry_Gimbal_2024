/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:03
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-08 07:24:11
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Src\motor.c
 * @Description: 
 * 
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved. 
 */
#include "motor.h"

uint8_t rotating_speed_count;
uint8_t relative_angle_count;
uint8_t absolute_angle_count;
uint8_t relative_angle_cascade_count;
uint8_t absolute_angle_cascade_count;
uint8_t gyro_angle_cascade_count;
uint8_t vision_angle_cascade_count;

struct motor_info_t* motor_info_list[motor_count];
struct rotating_speed_t* rotating_speed_list[motor_count];
struct relative_angle_t* relative_angle_list[motor_count];
struct absolute_angle_t* absolute_angle_list[motor_count];
struct relative_angle_cascade_t* relative_angle_cascade_list[motor_count];
struct absolute_angle_cascade_t* absolute_angle_cascade_list[motor_count];
struct gyro_angle_cascade_t* gyro_angle_cascade_list[motor_count];
struct vision_angle_cascade_t* vision_angle_cascade_list[motor_count];

void add_motor( uint32_t RecId, uint32_t SendId )
{
	static uint8_t motor_info_count;

	/* 申请内存空间以存储新添加电机的信息 */
	motor_info_list[motor_info_count] = ( struct motor_info_t* )pvPortMalloc( sizeof( struct motor_info_t ) );
	
	/* 存储电机接收ID */
	motor_info_list[motor_info_count]->RecId = RecId;
	
	/* 存储电机发送ID */
	motor_info_list[motor_info_count]->SendId = SendId;
	
	/* 标记此电机为已使用 */
	motor_info_list[motor_info_count]->used = 1U;
	
	/* 数组索引递增 */
	motor_info_count++;
}

int8_t request_structure_memory( uint8_t index, enum PID_type_t type )
{	
	switch( type )
	{
		case rotating_speed:
			
			/* 申请内存空间以存储PID操作所需的数据 */
			rotating_speed_list[rotating_speed_count] = ( struct rotating_speed_t* )pvPortMalloc( sizeof( struct rotating_speed_t ) );
			
			/* 清除新申请内存空间中的数据 */
			memset( ( void* )rotating_speed_list[rotating_speed_count], 0, sizeof( struct rotating_speed_t ) );
			
			/* 申请内存空间以存储PID操作所需的数据 */
			motor_info_list[index]->PID_structure_addr = ( void* )rotating_speed_list[rotating_speed_count];
			
			/* 存储电机将使用的PID控制方法 */
			motor_info_list[index]->PID_type = rotating_speed;
			
			/* 数组索引递增 */
			rotating_speed_count++;
			break;
		
		case relative_angle:
			/* 同上 */
			relative_angle_list[relative_angle_count] = ( struct relative_angle_t* )pvPortMalloc( sizeof( struct relative_angle_t ) );

			memset( ( void* )relative_angle_list[relative_angle_count], 0, sizeof( struct relative_angle_t ) );
			
			motor_info_list[index]->PID_structure_addr = ( void* )relative_angle_list[relative_angle_count];
			motor_info_list[index]->PID_type = relative_angle;
			relative_angle_count++;
			break;
		
		case absolute_angle:
			/* 同上 */
			absolute_angle_list[absolute_angle_count] = ( struct absolute_angle_t* )pvPortMalloc( sizeof( struct absolute_angle_t ) );
			
			memset( ( void* )absolute_angle_list[absolute_angle_count], 0, sizeof( struct absolute_angle_t ) );
			
			motor_info_list[index]->PID_structure_addr = ( void* )absolute_angle_list[absolute_angle_count];
			motor_info_list[index]->PID_type = absolute_angle;
			absolute_angle_count++;
			break;
		
		case relative_angle_cascade:
			/* 同上 */
			relative_angle_cascade_list[relative_angle_cascade_count] = ( struct relative_angle_cascade_t* )pvPortMalloc( sizeof( struct relative_angle_cascade_t ) );
			
			memset( ( void* )relative_angle_cascade_list[relative_angle_cascade_count], 0, sizeof( struct relative_angle_cascade_t ) );
			
			motor_info_list[index]->PID_structure_addr = ( void* )relative_angle_cascade_list[relative_angle_cascade_count];
			motor_info_list[index]->PID_type = relative_angle_cascade;
			relative_angle_cascade_count++;
			break;
		
		case absolute_angle_cascade:
			/* 同上 */
			absolute_angle_cascade_list[absolute_angle_cascade_count] = ( struct absolute_angle_cascade_t* )pvPortMalloc( sizeof( struct absolute_angle_cascade_t ) );

			memset( ( void* )absolute_angle_cascade_list[absolute_angle_cascade_count], 0, sizeof( struct absolute_angle_cascade_t ) );
			
			motor_info_list[index]->PID_structure_addr = ( void* )absolute_angle_cascade_list[absolute_angle_cascade_count];
			motor_info_list[index]->PID_type = absolute_angle_cascade;
			absolute_angle_cascade_count++;
			break;
		
		case gyro_angle_cascade:
			/* 同上 */
			gyro_angle_cascade_list[gyro_angle_cascade_count] = ( struct gyro_angle_cascade_t* )pvPortMalloc( sizeof( struct gyro_angle_cascade_t ) );
			
			memset( ( void* )gyro_angle_cascade_list[gyro_angle_cascade_count], 0, sizeof( struct gyro_angle_cascade_t ) );
			
			motor_info_list[index]->PID_structure_addr = ( void* )gyro_angle_cascade_list[gyro_angle_cascade_count];
			motor_info_list[index]->PID_type = gyro_angle_cascade;
			gyro_angle_cascade_count++;
			break;
		
		case vision_angle_cascade:
			/* 同上 */
			vision_angle_cascade_list[vision_angle_cascade_count] = ( struct vision_angle_cascade_t* )pvPortMalloc( sizeof( struct vision_angle_cascade_t ) );
		
			memset( ( void* )vision_angle_cascade_list[vision_angle_cascade_count], 0, sizeof( struct vision_angle_cascade_t ) );
			
			motor_info_list[index]->PID_structure_addr = ( void* )vision_angle_cascade_list[vision_angle_cascade_count];
			motor_info_list[index]->PID_type = vision_angle_cascade;
			vision_angle_cascade_count++;
		
		default:
			return TYPE_ERROR;
	}
	return LIB_OK;
}

int8_t release_structure_memory( uint8_t index)
{
	enum PID_type_t type;
	type = motor_info_list[index]->PID_type;
	
	switch( type )
	{
		case rotating_speed:
			rotating_speed_count--;
			break;
		
		case relative_angle:
			relative_angle_count--;
			break;
		
		case absolute_angle:
			absolute_angle_count--;
			break;
		
		case relative_angle_cascade:
			relative_angle_cascade_count--;
			break;
		
		case absolute_angle_cascade:
			absolute_angle_cascade_count--;
			break;
		
		case gyro_angle_cascade:
			gyro_angle_cascade_count--;
			break;
		
		default:
			return TYPE_ERROR;
	}
	
	void *addr = motor_info_list[index]->PID_structure_addr;
	
	/* 释放内存 */
	vPortFree( addr );
	
	/* 清除已释放内存的地址 */
	motor_info_list[index]->PID_structure_addr = NULL;
	
	/* 清除PID类型 */
	motor_info_list[index]->PID_type = nothing;
	
	return LIB_OK;
}

/* 将需要旋转的角度转换为电机角度 */
uint16_t absolute_angle_remainder( int32_t value )
{
	if( value > 8192 )
		return value % 8192;
	else if( value < 0 )
		return 8192 + ( value % 8192 );
	else
		return value;
}

/* 清除指定ID电机的累计旋转角度 */
void motor_angle_sum_clear( uint32_t RecId )
{
	for( uint8_t index = 0; index < motor_count; index++ )
	{
		if( motor_info_list[index]->RecId == RecId )
			motor_info_list[index]->angle_change_sum = 0;
	}
}

/* 获取指定ID电机的累计旋转角度（不知为何极其的慢） */
// int32_t get_motor_angle_sum( uint32_t RecId )
// {
// 	for( uint8_t index = 0; index < motor_count; index++ )
// 	{
// 		if( motor_info_list[index]->RecId == RecId )
// 		{
// 			return motor_info_list[index]->angle_change_sum;
// 		}
// 	}
// }

/* 用于算出电机相对于上一次所改变的角度 */
void angle_change_clac(uint8_t index)
{
    int16_t res1 = 0, res2 = 0;

    if (motor_info_list[index]->mechanical_angle - motor_info_list[index]->mechanical_angle_previous > 0) {
        res1 = motor_info_list[index]->mechanical_angle - motor_info_list[index]->mechanical_angle_previous - 8192;
        res2 = motor_info_list[index]->mechanical_angle - motor_info_list[index]->mechanical_angle_previous;
        if (abs(res1) < abs(res2)) {
            motor_info_list[index]->angle_change_sum += res1;
        } else {
            motor_info_list[index]->angle_change_sum += res2;
        }
    } else {
        res1 = motor_info_list[index]->mechanical_angle - motor_info_list[index]->mechanical_angle_previous + 8192;
        res2 = motor_info_list[index]->mechanical_angle - motor_info_list[index]->mechanical_angle_previous;
        if (abs(res1) < abs(res2)) {
            motor_info_list[index]->angle_change_sum += res1;
        } else {
            motor_info_list[index]->angle_change_sum += res2;
        }
    }

    /* 更新previous值 */
    motor_info_list[index]->mechanical_angle_previous = motor_info_list[index]->mechanical_angle;
}