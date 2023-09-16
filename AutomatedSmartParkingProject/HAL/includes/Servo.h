/*
 * Servo.h
 *
 *  Created on: Sep 13, 2023
 *      Author: Abdallah
 */

#ifndef HAL_INCLUDES_SERVO_H_
#define HAL_INCLUDES_SERVO_H_

#include "Stm32_F103C6_gpio_driver.h"
#include "Stm32_F103C6_TIMER_driver.h"


#define SERVO_ENTRY_PIN		GPIO_PIN_8
#define SERVO_EXIT_PIN		GPIO_PIN_9

#define SERVO_PORT			GPIOB


typedef enum{
	Servo_Entry,
	Servo_Exit
}Servo_Index;

typedef enum{
	DOWN,
	UP
}Servo_Direction;

void Servo_Init(Servo_Index servo);
void Servo_Move(Servo_Index servo, Servo_Direction dir);

#endif /* HAL_INCLUDES_SERVO_H_ */
