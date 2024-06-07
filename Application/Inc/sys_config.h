/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2024-06-08 03:33:43
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2024-06-08 03:33:54
 * @FilePath: \workspace (工作区)c:\Users\Ryan\Desktop\新建文件夹 (4)\sys_config.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*电机最大总数*/
#define motor_count 8

/*电机can*/
#define motor_can1 hcan1

/*IMU模块can*/
#define CH110_can hcan2

#define remote_uart huart3
/*遥控器数据字节数*/
#define remote_data_size			18

/* 电机旋转角度累计(启用宏定义则对对应ID电机进行累计计算) */
// #define enable_angle_sum_clac_0x201
// #define enable_angle_sum_clac_0x202
// #define enable_angle_sum_clac_0x203
// #define enable_angle_sum_clac_0x204
// #define enable_angle_sum_clac_0x205
// #define enable_angle_sum_clac_0x206
// #define enable_angle_sum_clac_0x207
// #define enable_angle_sum_clac_0x208
// #define enable_angle_sum_clac_0x209

