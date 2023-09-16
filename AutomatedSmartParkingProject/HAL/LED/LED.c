/*
 * LED.c
 *
 *  Created on: Sep 13, 2023
 *      Author: Abdallah
 */

#include "LED.h"




void LED_Init(void)
{
	GPIO_PinConfig_t PinCfg;

	PinCfg.GPIO_PinNumber = R_LED;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LED_PORT, &PinCfg);


	PinCfg.GPIO_PinNumber = G_LED;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LED_PORT, &PinCfg);


	// By default, they are off
	MCAL_GPIO_WritePin(LED_PORT, R_LED, GPIO_PIN_HIGH);
	MCAL_GPIO_WritePin(LED_PORT, G_LED, GPIO_PIN_HIGH);


}


// LEDs are connected normally to VCC, so they need a GND to work

void LED_ON(uint32_t LED)
{
	switch(LED)
	{
	case R_LED:
	{
		MCAL_GPIO_WritePin(LED_PORT, R_LED, GPIO_PIN_LOW);
		break;
	}
	case G_LED:
	{
		MCAL_GPIO_WritePin(LED_PORT, G_LED, GPIO_PIN_LOW);
		break;
	}
	}
}



void LED_OFF(uint32_t LED)
{
	switch(LED)
	{
	case R_LED:
	{
		MCAL_GPIO_WritePin(LED_PORT, R_LED, GPIO_PIN_HIGH);
		break;
	}
	case G_LED:
	{
		MCAL_GPIO_WritePin(LED_PORT, G_LED, GPIO_PIN_HIGH);
		break;
	}
	}
}
