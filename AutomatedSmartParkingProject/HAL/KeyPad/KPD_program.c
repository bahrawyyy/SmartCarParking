/*
 * KPD_program.c
 *
 *  Created on: May 4, 2023
 *      Author: Abdallah
 */



#include "KPD_interface.h"
#include "KPD_config.h"





#define NULL ((void *)0)


/* Steps of driver */

/** COLS and ROWS can be reversed
 *  1- SET COLS to be input and activate pull up to avoid floating
 	2- SET ROWS to be output and initially high
 	3- Activate a specific ROW and read the 4 COLS
 */

/* Activation steps */
/* DIO_ES_tSetPinValue(DIO_U8_PORT_B, DIO_U8_PIN_7, LOW);
 * if conditions to read the four columns
 * if all are high then activate the next row by
 * changing the pin only
 * Don't forget to activate only a row at a time
 * to avoid multiple options for switches and get confused
 *
 *
 */

/**
 * ROWS PB4 --> PB7 OUTPUT
 * COLS PD2 --> PD5 INPUT
 */

#define ROWS_NUM 4
#define COLS_NUM 3
#define INIT 0

const uint8_t KPD_Au8Keys[ROWS_NUM][COLS_NUM] = KPD_KEYS;

// To avoid the unarrangement and uncontiguous
const uint8_t KPD_Au8RowsPins[4] = {KPD_U8_R1,KPD_U8_R2,KPD_U8_R3,KPD_U8_R4};
const uint8_t KPD_Au8ColsPins[3] = {KPD_U8_C1,KPD_U8_C2,KPD_U8_C3};




ES_t KPD_init()
{

	GPIO_PinConfig_t PinCfg;

	// Keypad Configuration


	// Rows

	// R1 output push pull mode
	PinCfg.GPIO_PinNumber = KPD_U8_R1;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_2MHZ;
	MCAL_GPIO_Init(KPD_U8_PORTROWS, &PinCfg);

	// R2 output push pull mode
	PinCfg.GPIO_PinNumber = KPD_U8_R2;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_2MHZ;
	MCAL_GPIO_Init(KPD_U8_PORTROWS, &PinCfg);

	// R3 output push pull mode
	PinCfg.GPIO_PinNumber = KPD_U8_R3;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_2MHZ;
	MCAL_GPIO_Init(KPD_U8_PORTROWS, &PinCfg);

	// R4 output push pull mode
	PinCfg.GPIO_PinNumber = KPD_U8_R4;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_2MHZ;
	MCAL_GPIO_Init(KPD_U8_PORTROWS, &PinCfg);




	// Columns

	// C1 input pull down mode
	PinCfg.GPIO_PinNumber = KPD_U8_C1;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_PULLDOWN;
	MCAL_GPIO_Init(KPD_U8_PORTCOLS, &PinCfg);

	// C2 input pull down mode
	PinCfg.GPIO_PinNumber = KPD_U8_C2;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_PULLDOWN;
	MCAL_GPIO_Init(KPD_U8_PORTCOLS, &PinCfg);

	// C3 input pull down mode
	PinCfg.GPIO_PinNumber = KPD_U8_C3;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_PULLDOWN;
	MCAL_GPIO_Init(KPD_U8_PORTCOLS, &PinCfg);


	MCAL_GPIO_WritePin(KPD_U8_PORTROWS, KPD_U8_R1, GPIO_PIN_LOW);
	MCAL_GPIO_WritePin(KPD_U8_PORTROWS, KPD_U8_R2, GPIO_PIN_LOW);
	MCAL_GPIO_WritePin(KPD_U8_PORTROWS, KPD_U8_R3, GPIO_PIN_LOW);
	MCAL_GPIO_WritePin(KPD_U8_PORTROWS, KPD_U8_R4, GPIO_PIN_LOW);



	return ES_OK;
}


// -------------------------------------------------------------------------------------------- //

ES_t KPD_ES_tGetKeyPressed(uint8_t *copy_pu8ReturnedKey)
{
	*copy_pu8ReturnedKey = KPD_U8_NOT_PRESSED;
	uint8_t Local_u8RowsCounter,Local_u8ColsCounter,Local_u8PinVal,Local_u8Flag = GPIO_PIN_HIGH;
	if(copy_pu8ReturnedKey != NULL)
	{
		/* Activation of each row "for loop" */
		for(Local_u8RowsCounter=INIT;Local_u8RowsCounter<ROWS_NUM;Local_u8RowsCounter++)
		{
			// Activate row
			MCAL_GPIO_WritePin(KPD_U8_PORTROWS,KPD_Au8RowsPins[Local_u8RowsCounter],GPIO_PIN_HIGH);
			// Check which input pin has zero "pressed"
			// by reading 4 pins input "columns"
			for(Local_u8ColsCounter=INIT;Local_u8ColsCounter<COLS_NUM;Local_u8ColsCounter++)
			{
				Local_u8PinVal = MCAL_GPIO_ReadPin(KPD_U8_PORTCOLS,KPD_Au8ColsPins[Local_u8ColsCounter]);
				if(Local_u8PinVal == GPIO_PIN_HIGH){ /* Switch is pressed */
					/* The switch which reaches between the activated
					 * Column and the pressed key */
					wait_ms(20);   // Debouncing
					// Check if the pin is still low "problem of multiple display"
					Local_u8PinVal = MCAL_GPIO_ReadPin(KPD_U8_PORTCOLS,KPD_Au8ColsPins[Local_u8ColsCounter]);  // Update the PinVal
					// will not get out of the while until he raised his hand "Value = HIGH"
					// You want to let stuck the code here until the value equals high
					while(Local_u8PinVal == GPIO_PIN_HIGH){
						// Continues reading until the value equals high
						Local_u8PinVal = MCAL_GPIO_ReadPin(KPD_U8_PORTCOLS,KPD_Au8ColsPins[Local_u8ColsCounter]);   // Update the PinVal
					}
					*copy_pu8ReturnedKey = KPD_Au8Keys[Local_u8RowsCounter][Local_u8ColsCounter];
					Local_u8Flag = GPIO_PIN_LOW;
					break;
				}
			}
			// Deactivate ROW
			MCAL_GPIO_WritePin(KPD_U8_PORTROWS,KPD_Au8RowsPins[Local_u8RowsCounter],GPIO_PIN_LOW);
			if(Local_u8Flag == GPIO_PIN_LOW)
				break;
		}


	}else{
		return ES_NOT_OK;
	}
	return ES_OK;
}
