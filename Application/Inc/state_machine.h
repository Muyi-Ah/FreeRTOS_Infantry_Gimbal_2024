/*
 * @Author: Ryan Xavier 467030312@qq.com
 * @Date: 2024-06-08 08:03:18
 * @LastEditors: Ryan Xavier 467030312@qq.com
 * @LastEditTime: 2024-06-10 17:30:13
 * @FilePath: \FreeRTOS_Infantry_Gimbal_2024\Application\Inc\state_machine.h
 * @Description:
 *
 * Copyright (c) 2024 by Ryan Xavier, All Rights Reserved.
 */
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

/*标准库引用*/
#include "stdint.h"


/*枚举定义*/

typedef enum { STATE_INIT, STATE_MAINTENANCE, STATE_RUNNING } MainState;

typedef enum {
    SUBSTATE_NONE,
    SUBSTATE_MODE_11,
    SUBSTATE_MODE_12,
    SUBSTATE_MODE_13,
    SUBSTATE_MODE_21,
    SUBSTATE_MODE_22,
    SUBSTATE_MODE_23,
    SUBSTATE_MODE_31,
    SUBSTATE_MODE_32,
    SUBSTATE_MODE_33
} SubState;

typedef enum {
    EVENT_ENTER_INIT,
    EVENT_ENTER_MAINTENANCE,
    EVENT_START_RUNNING,
    EVENT_SWITCH_MODE_11,
    EVENT_SWITCH_MODE_12,
    EVENT_SWITCH_MODE_13,
    EVENT_SWITCH_MODE_21,
    EVENT_SWITCH_MODE_22,
    EVENT_SWITCH_MODE_23,
    EVENT_SWITCH_MODE_31,
    EVENT_SWITCH_MODE_32,
    EVENT_SWITCH_MODE_33
} Event;



/*结构体定义*/

typedef struct state_machine {
    MainState currentState;
    SubState currentSubState;
} StateMachine;



/*函数外部声明*/

void StateMachine_Init(StateMachine* sm);
void StateMachine_HandleEvent(StateMachine* sm, Event event);



#endif /*STATE_MACHINE_H*/