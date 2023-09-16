/*
 * Servo.c
 *
 *  Created on: Sep 13, 2023
 *      Author: Abdallah
 */


#include "Servo.h"


void Servo_Init(Servo_Index servo)
{
	GPIO_PinConfig_t PinCfg;

	switch(servo)
	{
	case Servo_Entry:
	{
		PinCfg.GPIO_PinNumber = SERVO_ENTRY_PIN;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(SERVO_PORT, &PinCfg);
		break;
	}
	case Servo_Exit:
	{
		PinCfg.GPIO_PinNumber = SERVO_EXIT_PIN;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(SERVO_PORT, &PinCfg);
		break;
	}
	}
}

// Back to zero --> 1.5ms
// go to 90 --> 2ms

void Servo_Move(Servo_Index servo, Servo_Direction dir)
{
	switch(servo)
	{
	case Servo_Entry:
	{
		if(dir == UP)
		{
			MCAL_GPIO_WritePin(SERVO_PORT, SERVO_ENTRY_PIN, GPIO_PIN_HIGH);
			Delay_us(2000);
			MCAL_GPIO_WritePin(SERVO_PORT, SERVO_ENTRY_PIN, GPIO_PIN_LOW);
		}else{
			MCAL_GPIO_WritePin(SERVO_PORT, SERVO_ENTRY_PIN, GPIO_PIN_HIGH);
			Delay_us(1487);
			MCAL_GPIO_WritePin(SERVO_PORT, SERVO_ENTRY_PIN, GPIO_PIN_LOW);
		}
		break;
	}
	case Servo_Exit:
	{
		if(dir == UP)
		{
			MCAL_GPIO_WritePin(SERVO_PORT, SERVO_EXIT_PIN, GPIO_PIN_HIGH);
			Delay_us(2000);
			MCAL_GPIO_WritePin(SERVO_PORT, SERVO_EXIT_PIN, GPIO_PIN_LOW);
		}else{
			MCAL_GPIO_WritePin(SERVO_PORT, SERVO_EXIT_PIN, GPIO_PIN_HIGH);
			Delay_us(1487);
			MCAL_GPIO_WritePin(SERVO_PORT, SERVO_EXIT_PIN, GPIO_PIN_LOW);
		}

		break;
	}
	}
}
