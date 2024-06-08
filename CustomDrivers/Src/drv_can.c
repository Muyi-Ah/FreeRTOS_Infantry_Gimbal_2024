/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 04:22:12
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-08 07:26:38
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\CustomDrivers\Src\drv_can.c
 * @Description: can报文数据处理
 * 
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved. 
 */
#include "drv_can.h"

/* 函数声明 */
void angle_change_clac(uint8_t index);

/* 变量声明 */
uint8_t tx_data_0x200[8];
uint8_t tx_data_0x1FF[8];
uint8_t tx_data_0x2FF[8];


/**
 * @description: can启动接收
 * @return {void}
 */
void can_manage_init(void)
{
    /* can1 */
    CAN_FilterTypeDef CAN_FilterInitStructure = {0};

    CAN_FilterInitStructure.FilterIdHigh         = 0x0000;
    CAN_FilterInitStructure.FilterIdLow          = 0x0000;
    CAN_FilterInitStructure.FilterMaskIdHigh     = 0x0000;
    CAN_FilterInitStructure.FilterMaskIdLow      = 0x0000;
    CAN_FilterInitStructure.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    CAN_FilterInitStructure.FilterBank           = 0;
    CAN_FilterInitStructure.FilterMode           = CAN_FILTERMODE_IDMASK;
    CAN_FilterInitStructure.FilterScale          = CAN_FILTERSCALE_32BIT;
    CAN_FilterInitStructure.FilterActivation     = CAN_FILTER_ENABLE;
    CAN_FilterInitStructure.SlaveStartFilterBank = 14;

    /* 配置CAN报文滤波器 */
    HAL_CAN_ConfigFilter(&motor_can1, &CAN_FilterInitStructure);

    /* 启动CAN_IT_RX_FIFO0_MSG_PENDING中断通知 */
    HAL_CAN_ActivateNotification(&motor_can1, CAN_IT_RX_FIFO0_MSG_PENDING);

    /* 启动CAN外设 */
    HAL_CAN_Start(&motor_can1);

    /* can2 */
    CAN_FilterInitStructure.FilterIdHigh         = 0x0000;
    CAN_FilterInitStructure.FilterIdLow          = 0x0000;
    CAN_FilterInitStructure.FilterMaskIdHigh     = 0x0000;
    CAN_FilterInitStructure.FilterMaskIdLow      = 0x0000;
    CAN_FilterInitStructure.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    CAN_FilterInitStructure.FilterBank           = 15;
    CAN_FilterInitStructure.FilterMode           = CAN_FILTERMODE_IDMASK;
    CAN_FilterInitStructure.FilterScale          = CAN_FILTERSCALE_32BIT;
    CAN_FilterInitStructure.FilterActivation     = CAN_FILTER_ENABLE;
    CAN_FilterInitStructure.SlaveStartFilterBank = 14;

    /* 配置CAN报文滤波器 */
    HAL_CAN_ConfigFilter(&CH110_can, &CAN_FilterInitStructure);

    /* 启动CAN_IT_RX_FIFO0_MSG_PENDING中断通知 */
    HAL_CAN_ActivateNotification(&CH110_can, CAN_IT_RX_FIFO0_MSG_PENDING);

    /* 启动CAN外设 */
    HAL_CAN_Start(&CH110_can);
}


/**
 * @description: can中断回调
 * @param {CAN_HandleTypeDef*} hcan can实例指针
 * @return {void}
 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan)
{
    /* 电机实例 */
    if (hcan->Instance == motor_can1.Instance) {
        /* 创建局部变量 */
        CAN_RxHeaderTypeDef rx_header;
        uint8_t rx_buf[8];

        /* 获取电机报文 */
        HAL_CAN_GetRxMessage(&motor_can1, CAN_RX_FIFO0, &rx_header, rx_buf);

        for (uint8_t index = 0; index < motor_count; index++) {
            /* 标记电机在线 */
            if (motor_info_list[index]->RecId == rx_header.StdId) {
                motor_info_list[index]->online_reply = 1U;
            }

            /* 更新电机数据 */
            motor_info_list[index]->mechanical_angle      = rx_buf[0] << 8 | rx_buf[1];
            motor_info_list[index]->rpm                   = rx_buf[2] << 8 | rx_buf[3];
            motor_info_list[index]->actual_torque_current = rx_buf[4] << 8 | rx_buf[5];
            motor_info_list[index]->temperature           = rx_buf[6];

            /* 第一次接收数据 */
            if (motor_info_list[index]->first_received == 0U) {
                motor_info_list[index]->mechanical_angle_previous = motor_info_list[index]->mechanical_angle;
                motor_info_list[index]->first_received            = 1U;
            }

            /* 计算累计变化角度 */
            else {
#ifdef enable_angle_sum_clac_0x201
                if (motor_info_list[index]->RecId == 0x201)
                    angle_change_clac(index);
#endif
#ifdef enable_angle_sum_clac_0x202
                if (motor_info_list[index]->RecId == 0x202)
                    angle_change_clac(index);
#endif
#ifdef enable_angle_sum_clac_0x203
                if (motor_info_list[index]->RecId == 0x203)
                    angle_change_clac(index);
#endif
#ifdef enable_angle_sum_clac_0x204
                if (motor_info_list[index]->RecId == 0x204)
                    angle_change_clac(index);
#endif
#ifdef enable_angle_sum_clac_0x205
                if (motor_info_list[index]->RecId == 0x205)
                    angle_change_clac(index);
#endif
#ifdef enable_angle_sum_clac_0x206
                if (motor_info_list[index]->RecId == 0x206)
                    angle_change_clac(index);
#endif
#ifdef enable_angle_sum_clac_0x207
                if (motor_info_list[index]->RecId == 0x207)
                    angle_change_clac(index);
#endif
#ifdef enable_angle_sum_clac_0x208
                if (motor_info_list[index]->RecId == 0x208)
                    angle_change_clac(index);
#endif
#ifdef enable_angle_sum_clac_0x209
                if (motor_info_list[index]->RecId == 0x209)
                    angle_change_clac(index);
#endif

                break;
            }
        }
    }
    /* IMU实例 */
    else if (hcan->Instance == CH110_can.Instance) {
        /* 创建局部变量 */
        CAN_RxHeaderTypeDef rx_header;
        uint8_t rx_buf[8];

        /* 获取IMU报文 */
        HAL_CAN_GetRxMessage(&CH110_can, CAN_RX_FIFO0, &rx_header, rx_buf);

        /* 创建静态局部变量 */
        static float roll_offset  = 0.f;
        static float pitch_offset = 0.f;
        static float yaw_offset   = 0.f;

        /* 欧拉角 */
        if (rx_header.StdId == 0x388) {
            CH110_data.roll  = ((int16_t)(rx_buf[1] << 8 | rx_buf[0]) / 100.0f) - roll_offset;
            CH110_data.pitch = ((int16_t)(rx_buf[3] << 8 | rx_buf[2]) / 100.0f) - pitch_offset;
            CH110_data.yaw   = ((int16_t)(rx_buf[5] << 8 | rx_buf[4]) / 100.0f) - yaw_offset;

            static uint8_t first_received = 0U;

            /* 第一次接收数据 */
            if (first_received == 0U) {
                roll_offset    = CH110_data.roll;
                pitch_offset   = CH110_data.pitch;
                yaw_offset     = CH110_data.yaw;
                first_received = 1U;
            } else {
                /* 角度累计 */
                CH110_cumulative_update();
            }
        }
        /* 角速度 */
        else if (rx_header.StdId == 0x288) {
            CH110_data.X_axisAngularVelocity = (int16_t)(rx_buf[1] << 8 | rx_buf[0]);
            CH110_data.Y_axisAngularVelocity = (int16_t)(rx_buf[3] << 8 | rx_buf[2]);
            CH110_data.Z_axisAngularVelocity = (int16_t)(rx_buf[5] << 8 | rx_buf[4]);
        }

        /* 标记IMU在线 */
        IMU_online_reply = 1U;
    }
}


/**
 * @description: 0x200发送ID数据encode
 * @param {uint8_t} index 索引
 * @return {void}
 */
static void __0x200_Encode( uint8_t index )
{
  
	if( motor_info_list[index]->RecId == 0x201 ){
		tx_data_0x200[0] = motor_info_list[index]->final_output >> 8;
		tx_data_0x200[1] = motor_info_list[index]->final_output;
	}
	else if( motor_info_list[index]->RecId == 0x202 ){
		tx_data_0x200[2] = motor_info_list[index]->final_output >> 8;
		tx_data_0x200[3] = motor_info_list[index]->final_output;
	}
	else if( motor_info_list[index]->RecId == 0x203 ){
		tx_data_0x200[4] = motor_info_list[index]->final_output >> 8;
		tx_data_0x200[5] = motor_info_list[index]->final_output;
	}
	else if( motor_info_list[index]->RecId == 0x204 ){
		tx_data_0x200[6] = motor_info_list[index]->final_output >> 8;
		tx_data_0x200[7] = motor_info_list[index]->final_output;
	}
}


/**
 * @description: 0x1FF发送ID数据encode
 * @param {uint8_t} index 索引
 * @return {void}
 */
static void __0x1FF_Encode( uint8_t index )
{
  
	if( motor_info_list[index]->RecId == 0x205 ){
		tx_data_0x1FF[0] = motor_info_list[index]->final_output >> 8;
		tx_data_0x1FF[1] = motor_info_list[index]->final_output;
	}
	else if( motor_info_list[index]->RecId == 0x206 ){
		tx_data_0x1FF[2] = motor_info_list[index]->final_output >> 8;
		tx_data_0x1FF[3] = motor_info_list[index]->final_output;
	}
	else if( motor_info_list[index]->RecId == 0x207 ){
		tx_data_0x1FF[4] = motor_info_list[index]->final_output >> 8;
		tx_data_0x1FF[5] = motor_info_list[index]->final_output;
	}
	else if( motor_info_list[index]->RecId == 0x208 ){
		tx_data_0x1FF[6] = motor_info_list[index]->final_output >> 8;
		tx_data_0x1FF[7] = motor_info_list[index]->final_output;
	}
}


/**
 * @description: 0x2FF发送ID数据encode
 * @param {uint8_t} index 索引
 * @return {void}
 */
static void __0x2FF_Encode( uint8_t index )
{
  
	if( motor_info_list[index]->RecId == 0x209 ){
		tx_data_0x2FF[0] = motor_info_list[index]->final_output >> 8;
		tx_data_0x2FF[1] = motor_info_list[index]->final_output;
	}
	else if( motor_info_list[index]->RecId == 0x20A ){
		tx_data_0x2FF[2] = motor_info_list[index]->final_output >> 8;
		tx_data_0x2FF[3] = motor_info_list[index]->final_output;
	}
	else if( motor_info_list[index]->RecId == 0x20B ){
		tx_data_0x2FF[4] = motor_info_list[index]->final_output >> 8;
		tx_data_0x2FF[5] = motor_info_list[index]->final_output;
	}
}


/**
 * @description: 电机报文发送
 * @param {CAN_HandleTypeDef} CanHandle can实例
 * @return {void}
 */
void motor_control_send( CAN_HandleTypeDef CanHandle )
{
	// xSemaphoreTake( xCAN1_Semaphore, portMAX_DELAY );
	CAN_TxHeaderTypeDef tx_header[2];
	
	tx_header[0].StdId = 0x200;
	tx_header[0].ExtId = 0;
	tx_header[0].IDE = CAN_ID_STD;
	tx_header[0].RTR = CAN_RTR_DATA;
	tx_header[0].DLC = 8;
	tx_header[0].TransmitGlobalTime = DISABLE;
	
	tx_header[1].StdId = 0x1FF;
	tx_header[1].ExtId = 0;
	tx_header[1].IDE = CAN_ID_STD;
	tx_header[1].RTR = CAN_RTR_DATA;
	tx_header[1].DLC = 8;
	tx_header[1].TransmitGlobalTime = DISABLE;
	
	for( uint8_t index = 0; index < motor_count; index++ )
	{
		if( motor_info_list[index]->SendId == 0x200 )
			__0x200_Encode( index );
		
		else if( motor_info_list[index]->SendId == 0x1FF )
			__0x1FF_Encode( index );
	}
	
	if( HAL_CAN_GetTxMailboxesFreeLevel( &CanHandle ) )
		HAL_CAN_AddTxMessage( &CanHandle, &tx_header[0], tx_data_0x200, ( uint32_t*) CAN_TX_MAILBOX0 );
	
	if( HAL_CAN_GetTxMailboxesFreeLevel( &CanHandle ) )
		HAL_CAN_AddTxMessage( &CanHandle, &tx_header[1], tx_data_0x1FF, ( uint32_t*) CAN_TX_MAILBOX0 );
	
	// xSemaphoreGive( xCAN1_Semaphore );
}