/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 08:02:47
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-09 00:30:32
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Src\state_machine.c
 * @Description: 状态机
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */
#include "state_machine.h"

/**
 * @description: 状态机初始化
 * @param {StateMachine} *sm 状态机结构体指针
 * @return {void}
 */
void StateMachine_Init(StateMachine* sm)
{
    sm->currentState    = STATE_INIT;
    sm->currentSubState = SUBSTATE_NONE;
}

/**
 * @description: 状态切换
 * @param {StateMachine*} sm 状态机结构体指针
 * @param {Event} event 状态事件
 * @return {void}
 */
void StateMachine_HandleEvent(StateMachine* sm, Event event)
{
    switch (sm->currentState) {
        /*初始化状态下*/
        case STATE_INIT:
            if (event == EVENT_START_RUNNING) {
                sm->currentState = STATE_RUNNING;

            } else if (event == EVENT_ENTER_MAINTENANCE) {
                sm->currentState = STATE_MAINTENANCE;
            }
            break;

        /*维护状态下*/
        case STATE_MAINTENANCE:
            if (event == STATE_RUNNING) {
                sm->currentState = STATE_RUNNING;
            } else if (event == STATE_INIT) {
                sm->currentState    = STATE_INIT;
                sm->currentSubState = SUBSTATE_NONE;
            }
            break;

        /*运行状态下*/
        case STATE_RUNNING:
            if (event == EVENT_SWITCH_MODE_11) {
                sm->currentSubState = SUBSTATE_MODE_11;
            } else if (event == EVENT_SWITCH_MODE_12) {
                sm->currentSubState = SUBSTATE_MODE_12;
            } else if (event == EVENT_SWITCH_MODE_13) {
                sm->currentSubState = SUBSTATE_MODE_13;
            } else if (event == EVENT_SWITCH_MODE_21) {
                sm->currentSubState = SUBSTATE_MODE_21;
            } else if (event == EVENT_SWITCH_MODE_22) {
                sm->currentSubState = SUBSTATE_MODE_22;
            } else if (event == EVENT_SWITCH_MODE_23) {
                sm->currentSubState = SUBSTATE_MODE_23;
            } else if (event == EVENT_SWITCH_MODE_31) {
                sm->currentSubState = SUBSTATE_MODE_31;
            } else if (event == EVENT_SWITCH_MODE_32) {
                sm->currentSubState = SUBSTATE_MODE_32;
            } else if (event == EVENT_SWITCH_MODE_33) {
                sm->currentSubState = SUBSTATE_MODE_33;
            } else if (event == EVENT_ENTER_INIT) {
                sm->currentState    = STATE_INIT;
                sm->currentSubState = SUBSTATE_NONE;
            } else if (event == EVENT_ENTER_MAINTENANCE) {
                sm->currentState = STATE_MAINTENANCE;
            }
            break;

        default: break;
    }
}