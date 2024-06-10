#ifndef INIT_H
#define INIT_H

///用户头文件引用
#include "state_machine.h"
#include "drv_can.h"
#include "drv_uart.h"
#include "remote.h"

/*结构体外部声明*/

extern StateMachine state_machine;


/*函数外部声明*/

void Robot_Init(void);

#endif /*INIT_H*/