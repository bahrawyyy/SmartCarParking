/*
 * PIR.c
 *
 *  Created on: Sep 13, 2023
 *      Author: Abdallah
 */


#include "PIR.h"



void PIR_Init(void)
{

	GPIO_PinConfig_t PinCfg;

	PinCfg.GPIO_PinNumber = PIR_1;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_PULLDOWN;
	MCAL_GPIO_Init(PIR_PORT, &PinCfg);


	PinCfg.GPIO_PinNumber = PIR_2;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_PULLDOWN;
	MCAL_GPIO_Init(PIR_PORT, &PinCfg);

}




void PIR_Read(uint16_t PIR, uint8_t *pir_reading)
{

	switch(PIR)
	{
	case PIR_1:
	{
		if(MCAL_GPIO_ReadPin(PIR_PORT, PIR_1) == GPIO_PIN_HIGH)
		{
			*pir_reading = GPIO_PIN_HIGH;
		}else{
			*pir_reading = GPIO_PIN_LOW;
		}
		break;
	}
	case PIR_2:
	{
		if(MCAL_GPIO_ReadPin(PIR_PORT, PIR_2) == GPIO_PIN_HIGH)
		{
			*pir_reading = GPIO_PIN_HIGH;
		}else{
			*pir_reading = GPIO_PIN_LOW;
		}
		break;
	}
	}
}
