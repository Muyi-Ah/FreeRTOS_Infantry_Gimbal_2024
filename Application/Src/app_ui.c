// #include "app_ui.h"

// uint8_t send_flag_test;
// uint8_t send_flag_test3;

// int32_t start_angle1;
// int32_t end_angle1;
// int32_t start_angle2;
// int32_t end_angle2;

// graphic_data_struct_t graphic_data_struct_1;
// graphic_data_struct_t graphic_data_struct_2;
// graphic_data_struct_t graphic_data_struct_3;
// graphic_data_struct_t graphic_data_struct_4;
// graphic_data_struct_t graphic_data_struct_5;
// graphic_data_struct_t graphic_data_struct_6;
// graphic_data_struct_t graphic_data_struct_7;
// graphic_data_struct_t graphic_data_struct_8;
// graphic_data_struct_t graphic_data_struct_9;
// graphic_data_struct_t graphic_data_struct_10;
// graphic_data_struct_t graphic_data_struct_11;
// graphic_data_struct_t graphic_data_struct_12;
// graphic_data_struct_t graphic_data_struct_13;
// graphic_data_struct_t graphic_data_struct_14;
// graphic_data_struct_t graphic_data_struct_15;
// graphic_data_struct_t graphic_data_struct_16;
// graphic_data_struct_t graphic_data_struct_17;
// graphic_data_struct_t graphic_data_struct_18;
// graphic_data_struct_t graphic_data_struct_19;
// graphic_data_struct_t graphic_data_struct_20;
// graphic_data_struct_t graphic_data_struct_21;
// graphic_data_struct_t graphic_data_struct_22;

// char graphic_name_1[3]  = "one";
// char graphic_name_2[3]  = "two";
// char graphic_name_3[3]  = "thr";
// char graphic_name_4[3]  = "fou";
// char graphic_name_5[3]  = "fiv";
// char graphic_name_6[3]  = "six";
// char graphic_name_7[3]  = "sev";
// char graphic_name_8[3]  = "eig";
// char graphic_name_9[3]  = "nin";
// char graphic_name_10[3] = "ten";
// char graphic_name_11[3] = "ele";
// char graphic_name_12[3] = "tew";
// char graphic_name_13[3] = "-13";
// char graphic_name_14[3] = "-14";
// char graphic_name_15[3] = "-15";
// char graphic_name_16[3] = "-16";
// char graphic_name_17[3] = "-17";
// char graphic_name_18[3] = "-18";
// char graphic_name_19[3] = "-19";
// char graphic_name_20[3] = "-20";
// char graphic_name_21[3] = "-21";
// char graphic_name_22[3] = "-22";

// /* 字符用 */
// graphic_data_struct_t s_words_power_limit;        // “功率上限值”
// graphic_data_struct_t s_words_shoot_speed_limit;  // “射速上限值”
// graphic_data_struct_t s_words_capacitor_charging_power;  // “电容板充电功率”
// graphic_data_struct_t s_words_shoot_rate;                // “射速档次”
// graphic_data_struct_t s_words_shooting_speed;            // “实时射速”
// graphic_data_struct_t s_words_max_rpm;                   // “最大轮速”
// graphic_data_struct_t s_words_capacitor_vlote;           // “电容电压”

// char words_name_power_limit[3]       = "wd1";         // “功率上限值”
// char words_name_shoot_speed_limit[3] = "wd2";         // “射速上限值”
// char words_name_capacitor_charging_power[3] = "wd3";  // “电容板充电功率”
// char words_name_shoot_rate[3]      = "wd4";           // “射速档次”
// char words_name_shooting_speed[3]  = "wd5";           // “实时射速”
// char words_name_max_rpm[3]         = "wd6";           // “最大轮速”‘
// char words_name_capacitor_vlote[3] = "wd7";           // “电容电压”

// char words_power_limit[30]              = "power_limit:";
// char words_shoot_speed_limit[30]        = "shoot_speed_limit:";
// char words_capacitor_charging_power[30] = "charging_power:";
// char words_shoot_rate[30]               = "shoot_rate:";
// char words_shooting_speed[30]           = "shooting_speed:";
// char words_max_rpm[30]                  = "max_rpm:";
// char words_capacitor_vlote[30]          = "capacitor_vlote:";

// /* 浮点用 */
// graphic_data_struct_t s_float_capacitor_vlote; /* 电容电压 */
// graphic_data_struct_t s_float_charging_power;  /* 充电功率 */
// graphic_data_struct_t s_float_shooting_speed;  /* 实际射速 */

// char float_name_capacitor_vlote[3] = "wd8";
// char float_name_charging_power[3]  = "wd9";
// char float_name_shooting_speed[3]  = "wdE";

// int32_t send_capacitance_charging_power;

// uint8_t latch1;

// uint8_t rotate_latch_flag_test;

// uint8_t clean_all_ui;
// uint8_t stay;
// int32_t voltage;

// /* 本地函数声明 */
// void UI_words_config(void);
// void UI_words_add(void);
// void UI_volte_init_add(void);
// void UI_volte_update(void);
// void UI_charging_power_init_add(void);
// void UI_charging_power_update(void);
// void UI_chassis_orientation_indicator_add(void);
// void UI_chassis_orientation_indicator_update(void);

// void ui_task(void *pvParameters) {
//   for (;;) {
//     client_id                       = get_client_id();
//     send_capacitance_charging_power = capacitance_charging_power / 100;

//     /* 初始化UI */
//     if (stay == 0) {
//       graphic_image_set(&graphic_data_struct_1, graphic_name_1, add, Straight,
//                         0, cyan, 0, 0, 2, 0, 540, 0, 1920, 540);  // Y轴
//       graphic_image_set(&graphic_data_struct_2, graphic_name_2, add, Straight,
//                         0, cyan, 0, 0, 1, 960, 0, 0, 960, 1080);  // X轴

//       graphic_image_set(&graphic_data_struct_3, graphic_name_3, add, Straight,
//                         0, white, 0, 0, 1, 820, 390, 0, 1100, 390);  // 大标线1
//       graphic_image_set(&graphic_data_struct_4, graphic_name_4, add, Straight,
//                         0, white, 0, 0, 1, 840, 315, 0, 1080, 315);  // 大标线2
//       graphic_image_set(&graphic_data_struct_5, graphic_name_5, add, Straight,
//                         0, white, 0, 0, 1, 860, 240, 0, 1060, 240);  // 大标线3

//       graphic_image_set(&graphic_data_struct_6, graphic_name_6, add, Straight,
//                         0, white, 0, 0, 1, 930, 375, 0, 960, 375);  // 标线1-1
//       graphic_image_set(&graphic_data_struct_7, graphic_name_7, add, Straight,
//                         0, white, 0, 0, 1, 940, 360, 0, 960, 360);  // 标线1-2
//       graphic_image_set(&graphic_data_struct_8, graphic_name_8, add, Straight,
//                         0, cyan, 0, 0, 1, 930, 345, 0, 960, 345);  // 标线1-3
//       graphic_image_set(&graphic_data_struct_11, graphic_name_11, add, Straight,
//                         0, cyan, 0, 0, 1, 940, 330, 0, 960, 330);  // 标线1-4

//       graphic_image_set(&graphic_data_struct_12, graphic_name_12, add, Straight,
//                         0, cyan, 0, 0, 1, 930, 300, 0, 960, 300);  // 标线2-1
//       graphic_image_set(&graphic_data_struct_13, graphic_name_13, add, Straight,
//                         0, cyan, 0, 0, 1, 940, 285, 0, 960, 285);  // 标线2-2
//       graphic_image_set(&graphic_data_struct_14, graphic_name_14, add, Straight,
//                         0, cyan, 0, 0, 1, 930, 270, 0, 960, 270);  // 标线2-3
//       graphic_image_set(&graphic_data_struct_15, graphic_name_15, add, Straight,
//                         0, cyan, 0, 0, 1, 940, 255, 0, 960, 255);  // 标线2-4

//       graphic_image_set(&graphic_data_struct_16, graphic_name_16, add, Straight,
//                         0, white, 0, 0, 2, 960, 490, 0, 1300, 490);  // 标线0-1
//       graphic_image_set(&graphic_data_struct_17, graphic_name_17, add, Straight,
//                         0, white, 0, 0, 2, 960, 440, 0, 1220, 440);  // 标线0-2

//       graphic_image_set(&graphic_data_struct_18, graphic_name_18, add,
//                         Rectangle, 0, green, 0, 0, 2, 900, 415, 0, 960,
//                         390);  // 大标线1框
//       graphic_image_set(&graphic_data_struct_19, graphic_name_19, add,
//                         Rectangle, 0, white, 0, 0, 2, 960, 440, 0, 1020,
//                         465);  // 标线0-2框

//       graphic_image_set(&graphic_data_struct_9, graphic_name_9, add,
//                         Circular_arc, 1, cyan, 135, 45, 10, 500, 350, 0, 50,
//                         50);
//       //			graphic_image_set( &graphic_data_struct_10, graphic_name_10, add,
//       // Rectangle, 0, cyan,  0, 0, 5, 695, 220, 0, 1233, 180 ); //电容标线框

//       //			add_one_picture( ext_game_robot_status.robot_id, client_id,
//       //&graphic_data_struct_10);  //电容标线框 			vTaskDelay( pdMS_TO_TICKS(
//       //100 )
//       //); 			add_one_picture( ext_game_robot_status.robot_id, client_id,
//       //&graphic_data_struct_8 ); 			vTaskDelay( pdMS_TO_TICKS( 100 ) );
//       //			add_two_picture( ext_game_robot_status.robot_id, client_id,
//       //&graphic_data_struct_6, &graphic_data_struct_7 ); 			vTaskDelay(
//       // pdMS_TO_TICKS( 100 ) ); 			add_five_picture(
//       // ext_game_robot_status.robot_id, client_id, &graphic_data_struct_1,
//       //&graphic_data_struct_2, &graphic_data_struct_3, &graphic_data_struct_4,
//       //&graphic_data_struct_5 ); 			vTaskDelay( pdMS_TO_TICKS( 100 ) );

//       add_two_picture(ext_game_robot_status.robot_id, client_id,
//                       &graphic_data_struct_1, &graphic_data_struct_2);
//       vTaskDelay(pdMS_TO_TICKS(100));
//       add_one_picture(ext_game_robot_status.robot_id, client_id,
//                       &graphic_data_struct_3);
//       vTaskDelay(pdMS_TO_TICKS(100));
//       add_five_picture(ext_game_robot_status.robot_id, client_id,
//                        &graphic_data_struct_4, &graphic_data_struct_5,
//                        &graphic_data_struct_6, &graphic_data_struct_7,
//                        &graphic_data_struct_8);
//       vTaskDelay(pdMS_TO_TICKS(100));
//       add_five_picture(ext_game_robot_status.robot_id, client_id,
//                        &graphic_data_struct_11, &graphic_data_struct_12,
//                        &graphic_data_struct_13, &graphic_data_struct_14,
//                        &graphic_data_struct_15);
//       vTaskDelay(pdMS_TO_TICKS(100));
//       add_two_picture(ext_game_robot_status.robot_id, client_id,
//                       &graphic_data_struct_16, &graphic_data_struct_17);
//       vTaskDelay(pdMS_TO_TICKS(100));
//       add_two_picture(ext_game_robot_status.robot_id, client_id,
//                       &graphic_data_struct_18, &graphic_data_struct_19);
//       vTaskDelay(pdMS_TO_TICKS(100));

//       /* 发文字 */
//       UI_words_config();
//       UI_words_add();
//       /* 发电容电压 */
//       UI_volte_init_add();
//       /* 发充电功率 */
//       UI_charging_power_init_add();
//       /* 发底盘方位指示符 */
//       UI_chassis_orientation_indicator_add();
//     }
//     /* 动态UI */
//     else {
//       //			/* 电容电压动态UI */
//       //			graphic_image_set( &graphic_data_struct_8, graphic_name_8, update,
//       // Straight, 0, green,  0, 0, 30, 700, 200, 0, (700+(votle-12)*44), 200 );

//       /* 更新电容电压数值 */
//       UI_volte_update();
//       /* 更新充电功率数值 */
//       UI_charging_power_update();
//       /* 更新底盘方位指示符 */
//       UI_chassis_orientation_indicator_update();
//     }
//     //		add_one_picture( ext_game_robot_status.robot_id, client_id,
//     //&graphic_data_struct_8 ); //电容条，没用了 		vTaskDelay( pdMS_TO_TICKS(
//     //100 ) );

//     stay = 1;

//     /* 小陀螺动态UI指示 */
//     if (rotate_latch_flag && latch1 == 0) {
//       add_one_picture(ext_game_robot_status.robot_id, client_id,
//                       &graphic_data_struct_9);
//       vTaskDelay(pdMS_TO_TICKS(100));
//       latch1 = 1;
//     } else if (rotate_latch_flag == 0 && latch1) {
//       delete_picture(ext_game_robot_status.robot_id, client_id, each, 1);
//       vTaskDelay(pdMS_TO_TICKS(100));
//       latch1 = 0;
//     }

//     /* 清空所有UI */
//     if (clean_all_ui) {
//       clean_all_ui = 0;
//       delete_picture(ext_game_robot_status.robot_id, client_id, all, 0);
//       vTaskDelay(pdMS_TO_TICKS(100));
//       stay = 0;
//     }

//     /* 挂起任务1s */
//     vTaskDelay(pdMS_TO_TICKS(1));
//   }
// }

// /**	@brief 	UI文字结构体配置
//  * @retval void
//  * @attention
//  */
// void UI_words_config(void) {
//   /* 射速上限值 */
//   //	graphic_image_set(&s_words_shoot_speed_limit,
//   //words_name_shoot_speed_limit, add, Words, 2, cyan, word_size,
//   //strlen(words_shoot_speed_limit), word_width, 50, 900, 0, 0, 0);
//   /* 实际弹丸射速 */
//   //	graphic_image_set(&s_words_shooting_speed, words_name_shooting_speed, add,
//   //Words, 2, cyan, word_size, strlen(words_shooting_speed), word_width, 50,
//   //850, 0, 0, 0);
//   /* 功率上限值 */
//   //	graphic_image_set(&s_words_power_limit, words_name_power_limit, add,
//   //Words, 2, cyan, word_size, strlen(words_power_limit), word_width, 50, 800,
//   //0, 0, 0);
//   /* 充电功率 */
//   graphic_image_set(&s_words_capacitor_charging_power,
//                     words_name_capacitor_charging_power, add, Words, 2, cyan,
//                     word_size, strlen(words_capacitor_charging_power),
//                     word_width, 50, 750, 0, 0, 0);
//   /* 射速档次 */
//   // graphic_image_set(&s_words_shoot_rate, words_name_shoot_rate, add, Words,
//   // 2, cyan, word_size, strlen(words_shoot_rate), word_width, 50, 750, 0, 0,
//   // 0);
//   /* 最大轮速 */
//   //	graphic_image_set(&s_words_max_rpm, words_name_max_rpm, add, Words, 2,
//   //cyan, word_size, strlen(words_max_rpm), word_width, 50, 700, 0, 0, 0);
//   /* 电容电压 */
//   graphic_image_set(&s_words_capacitor_vlote, words_name_capacitor_vlote, add,
//                     Words, 2, cyan, word_size, strlen(words_capacitor_vlote),
//                     word_width, 50, 650, 0, 0, 0);
// }

// /**	@brief 	UI文字添加
//  * @retval void
//  * @attention
//  */
// void UI_words_add(void) {
//   /* 功率上限值 */
//   //	add_word(ext_game_robot_status.robot_id, client_id, &s_words_power_limit,
//   //words_power_limit); 	vTaskDelay(pdMS_TO_TICKS(100));
//   /* 射速上限值 */
//   //	add_word(ext_game_robot_status.robot_id, client_id,
//   //&s_words_shoot_speed_limit, words_shoot_speed_limit);
//   //	vTaskDelay(pdMS_TO_TICKS(100));
//   /* 充电功率 */
//   add_word(ext_game_robot_status.robot_id, client_id,
//            &s_words_capacitor_charging_power, words_capacitor_charging_power);
//   vTaskDelay(pdMS_TO_TICKS(100));
//   /* 射速档次 */
//   // add_word(ext_game_robot_status.robot_id, client_id, &s_words_shoot_rate,
//   // words_shoot_rate); vTaskDelay(pdMS_TO_TICKS(100));
//   /* 实际弹丸射速 */
//   //	add_word(ext_game_robot_status.robot_id, client_id,
//   //&s_words_shooting_speed, words_shooting_speed);
//   //	vTaskDelay(pdMS_TO_TICKS(100));
//   /* 最大轮速 */
//   //	add_word(ext_game_robot_status.robot_id, client_id, &s_words_max_rpm,
//   //words_max_rpm); 	vTaskDelay(pdMS_TO_TICKS(100));
//   /* 电容电压 */
//   add_word(ext_game_robot_status.robot_id, client_id, &s_words_capacitor_vlote,
//            words_capacitor_vlote);
//   vTaskDelay(pdMS_TO_TICKS(100));
// }

// /**	@brief 	UI电容电压数值初始化
//  * @retval void
//  * @attention
//  */
// void UI_volte_init_add(void) {
//   graphic_image_set(&s_float_capacitor_vlote, float_name_capacitor_vlote, add,
//                     Float_number, 3, cyan, 40, 1, 4, 500, 650, 0, 0, 0);
//   /* 将数值添加到最后32位 */
//   assignValuesToInt32(&s_float_capacitor_vlote, voltage);
//   add_one_picture(ext_game_robot_status.robot_id, client_id,
//                   &s_float_capacitor_vlote);
//   vTaskDelay(pdMS_TO_TICKS(100));
// }

// /**	@brief 	UI电容电压数值更新
//  * @retval void
//  * @attention
//  */
// void UI_volte_update(void) {
//   graphic_image_set(&s_float_capacitor_vlote, float_name_capacitor_vlote,
//                     update, Float_number, 3, cyan, 40, 1, 4, 500, 650, 0, 0, 0);
//   /* 将数值添加到最后32位 */
//   assignValuesToInt32(&s_float_capacitor_vlote, voltage);
//   add_one_picture(ext_game_robot_status.robot_id, client_id,
//                   &s_float_capacitor_vlote);
//   vTaskDelay(pdMS_TO_TICKS(100));
// }

// /**	@brief 	UI充电功率数值初始化
//  * @retval void
//  * @attention
//  */
// void UI_charging_power_init_add(void) {
//   graphic_image_set(&s_float_charging_power, float_name_charging_power, add,
//                     Int_number, 3, green, 23, 1, 3, 500, 750, 0, 0, 0);
//   /* 将数值添加到最后32位 */
//   assignValuesToInt32(&s_float_charging_power, send_capacitance_charging_power);
//   add_one_picture(ext_game_robot_status.robot_id, client_id,
//                   &s_float_charging_power);
//   vTaskDelay(pdMS_TO_TICKS(100));
// }

// /**	@brief 	UI充电功率数值更新
//  * @retval void
//  * @attention
//  */
// void UI_charging_power_update(void) {
//   graphic_image_set(&s_float_charging_power, float_name_charging_power, update,
//                     Int_number, 3, green, 23, 1, 3, 500, 750, 0, 0, 0);
//   /* 将数值添加到最后32位 */
//   assignValuesToInt32(&s_float_charging_power, send_capacitance_charging_power);
//   add_one_picture(ext_game_robot_status.robot_id, client_id,
//                   &s_float_charging_power);
//   vTaskDelay(pdMS_TO_TICKS(100));
// }

// /**	@brief 	UI底盘方位指示符初始化
//  * @retval void
//  * @attention
//  */
// void UI_chassis_orientation_indicator_add(void) {
//   graphic_image_set(&graphic_data_struct_20, graphic_name_20, add, Straight, 1,
//                     white, 0, 0, 8, 780, 260, 0, 780, 180);
//   add_one_picture(ext_game_robot_status.robot_id, client_id,
//                   &graphic_data_struct_20);
//   vTaskDelay(pdMS_TO_TICKS(100));
//   graphic_image_set(&graphic_data_struct_21, graphic_name_21, add, Circular_arc,
//                     1, cyan, 0, 45, 315, 780, 180, 0, 50, 50);
//   graphic_image_set(&graphic_data_struct_22, graphic_name_22, add, Circular_arc,
//                     1, red, 0, 315, 45, 780, 180, 0, 50, 50);
//   add_two_picture(ext_game_robot_status.robot_id, client_id,
//                   &graphic_data_struct_21, &graphic_data_struct_22);
//   vTaskDelay(pdMS_TO_TICKS(100));
// }

// /**	@brief 	UI底盘方位指示符更新
//  * @retval void
//  * @attention
//  */
// void UI_chassis_orientation_indicator_update(void) {
//   start_angle1 = 45 + theta;
//   end_angle1   = 315 + theta;
//   start_angle1 = MOD360(start_angle1);
//   end_angle1   = MOD360(end_angle1);

//   start_angle2 = 315 + theta;
//   end_angle2   = 45 + theta;
//   start_angle2 = MOD360(start_angle2);
//   end_angle2   = MOD360(end_angle2);

//   graphic_image_set(&graphic_data_struct_21, graphic_name_21, update,
//                     Circular_arc, 1, cyan, start_angle1, end_angle1, 10, 780,
//                     180, 0, 50, 50);
//   graphic_image_set(&graphic_data_struct_22, graphic_name_22, update,
//                     Circular_arc, 1, red, start_angle2, end_angle2, 10, 780,
//                     180, 0, 50, 50);
//   add_two_picture(ext_game_robot_status.robot_id, client_id,
//                   &graphic_data_struct_21, &graphic_data_struct_22);
//   vTaskDelay(pdMS_TO_TICKS(100));
// }