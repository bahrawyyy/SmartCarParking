/*
 * KPD_config.h
 *
 *  Created on: May 4, 2023
 *      Author: Abdallah
 */

#ifndef HAL_KPD_KPD_CONFIG_H_
#define HAL_KPD_KPD_CONFIG_H_


/**
 * ROWS PB4 --> PB7 OUTPUT
 * COLS PD2 --> PD5 INPUT
 */


#define KPD_U8_PORTROWS GPIOB
#define KPD_U8_PORTCOLS GPIOB

#define KPD_U8_R1 GPIO_PIN_0
#define KPD_U8_R2 GPIO_PIN_1
#define KPD_U8_R3 GPIO_PIN_3
#define KPD_U8_R4 GPIO_PIN_4

#define KPD_U8_C1 GPIO_PIN_7
#define KPD_U8_C2 GPIO_PIN_6
#define KPD_U8_C3 GPIO_PIN_5


#define KPD_KEYS {{'#','0','*'},\
				  {'9','8','7'},\
		          {'6','5','4'},\
		          {'3','2','1'}}

#endif /* HAL_KPD_KPD_CONFIG_H_ */
