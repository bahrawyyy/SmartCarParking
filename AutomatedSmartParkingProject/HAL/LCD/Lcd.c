/*
 * Lcd.c
 *
 *  Created on: Sep 12, 2022
 *      Author: 10
 */


#include "Lcd.h"
#include <string.h>


#define GET_BIT(REG,PIN) ((REG>>PIN) & 0x1)


//ProtoType of static is defined in source file itself(Private declaration)
static ES_t LCD_ES_tTrigger_Enable(LCD_Instant instant);
static ES_t LCD_ES_tSet_Cursor_Pos(LCD_Instant instant,uint8_t row,uint8_t column);

//We make it static cuz we won't use it anywhere but here
static ES_t LCD_ES_tTrigger_Enable(LCD_Instant instant){
	switch(instant){
	case LCD_Instant_1:
	{
		MCAL_GPIO_WritePin(LCD_1_CMD_PORT, EN_1, GPIO_PIN_HIGH);
		wait_ms(1);
		MCAL_GPIO_WritePin(LCD_1_CMD_PORT, EN_1, GPIO_PIN_LOW);
		wait_ms(2);
		break;
	}
	case LCD_Instant_2:
	{
		MCAL_GPIO_WritePin(LCD_2_CMD_PORT, EN_2, GPIO_PIN_HIGH);
		wait_ms(1);
		MCAL_GPIO_WritePin(LCD_2_CMD_PORT, EN_2, GPIO_PIN_LOW);
		wait_ms(2);
		break;
	}
	}

	return ES_OK;
}


ES_t Lcd_ES_tInit(LCD_Instant instant){

	GPIO_PinConfig_t PinCfg;

	switch(instant){
	case LCD_Instant_1:
	{

		// Pins Configuration for LCD

		// RS output push pull mode
		PinCfg.GPIO_PinNumber = RS_1;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(LCD_1_CMD_PORT, &PinCfg);

		// EN output push pull mode
		PinCfg.GPIO_PinNumber = EN_1;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(LCD_1_CMD_PORT, &PinCfg);

		// D4 output push pull mode
		PinCfg.GPIO_PinNumber = D4_1;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(LCD_1_DATA_PORT, &PinCfg);

		// D5 output push pull mode
		PinCfg.GPIO_PinNumber = D5_1;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(LCD_1_DATA_PORT, &PinCfg);

		// D6 output push pull mode
		PinCfg.GPIO_PinNumber = D6_1;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(LCD_1_DATA_PORT, &PinCfg);

		// D7 output push pull mode
		PinCfg.GPIO_PinNumber = D7_1;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(LCD_1_DATA_PORT, &PinCfg);


		Lcd_ES_tsendCmd(LCD_Instant_1,Four_BitMode);   /* Go into 4-bit operating mode*/
		Lcd_ES_tsendCmd(LCD_Instant_1,D4_D7);  /* 2 Line, 5*7 matrix in 4-bit mode */
		Lcd_ES_tsendCmd(LCD_Instant_1,CursorON);  /* Display on cursor off */
		Lcd_ES_tsendCmd(LCD_Instant_1,IncrCursor);  /* Increment cursor (shift cursor to right) */
		Lcd_ES_tsendCmd(LCD_Instant_1,CLR_Display);  /* Clear display screen */


		break;
	}
	case LCD_Instant_2:
	{

		// Pins Configuration for LCD

		// RS output push pull mode
		PinCfg.GPIO_PinNumber = RS_2;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(LCD_2_CMD_PORT, &PinCfg);

		// EN output push pull mode
		PinCfg.GPIO_PinNumber = EN_2;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(LCD_2_CMD_PORT, &PinCfg);

		// D4 output push pull mode
		PinCfg.GPIO_PinNumber = D4_2;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(LCD_2_DATA_PORT, &PinCfg);

		// D5 output push pull mode
		PinCfg.GPIO_PinNumber = D5_2;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(LCD_2_DATA_PORT, &PinCfg);

		// D6 output push pull mode
		PinCfg.GPIO_PinNumber = D6_2;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(LCD_2_DATA_PORT, &PinCfg);

		// D7 output push pull mode
		PinCfg.GPIO_PinNumber = D7_2;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PUSHPULL;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(LCD_2_DATA_PORT, &PinCfg);


		Lcd_ES_tsendCmd(LCD_Instant_2,Four_BitMode);   /* Go into 4-bit operating mode*/
		Lcd_ES_tsendCmd(LCD_Instant_2,D4_D7);  /* 2 Line, 5*7 matrix in 4-bit mode */
		Lcd_ES_tsendCmd(LCD_Instant_2,CursorON);  /* Display on cursor off */
		Lcd_ES_tsendCmd(LCD_Instant_2,IncrCursor);  /* Increment cursor (shift cursor to right) */
		Lcd_ES_tsendCmd(LCD_Instant_2,CLR_Display);  /* Clear display screen */


		break;
	}
	}


	return ES_OK;

}

/*
 * RS = 0 // To send command
 * RW = 0 //To write on the LCD
 *  4-bit mode
 * Send higher nibble(1/2 Byte)
 * Send Trigger Enable
 * Send Lower nibble
 * Send Trigger Enable
 * delay
 *
 *
 *	Ex. 0x28 0b 0010 1000  //Read bit by bit and see if it is low or high
 */

void wait_ms(uint32_t time){
	uint32_t i,j;
	for(i=0;i<time;i++)
		for(j=0;j<255;j++);
}

ES_t lcd_ES_tclear(LCD_Instant instant)
{

	switch(instant){
	case LCD_Instant_1:
	{
		Lcd_ES_tsendCmd(LCD_Instant_1,CLR_Display);
		break;
	}
	case LCD_Instant_2:
	{
		Lcd_ES_tsendCmd(LCD_Instant_2,CLR_Display);
		break;
	}
	}


	wait_ms(2);
	return ES_OK;
}

ES_t Lcd_ES_tsendCmd(LCD_Instant instant, uint8_t cmd){

	switch(instant){
	case LCD_Instant_1:
	{
		MCAL_GPIO_WritePin(LCD_1_CMD_PORT, RS_1, GPIO_PIN_LOW);


		(GET_BIT(cmd,7)) ? MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D7_1,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D7_1,GPIO_PIN_LOW);
		(GET_BIT(cmd,6)) ? MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D6_1,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D6_1,GPIO_PIN_LOW);
		(GET_BIT(cmd,5)) ? MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D5_1,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D5_1,GPIO_PIN_LOW);
		(GET_BIT(cmd,4)) ? MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D4_1,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D4_1,GPIO_PIN_LOW);
		//Trigger Enable
		LCD_ES_tTrigger_Enable(LCD_Instant_1);
		(GET_BIT(cmd,3)) ? MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D7_1,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D7_1,GPIO_PIN_LOW);
		(GET_BIT(cmd,2)) ? MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D6_1,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D6_1,GPIO_PIN_LOW);
		(GET_BIT(cmd,1)) ? MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D5_1,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D5_1,GPIO_PIN_LOW);
		(GET_BIT(cmd,0)) ? MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D4_1,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D4_1,GPIO_PIN_LOW);
		//Trigger Enable
		LCD_ES_tTrigger_Enable(LCD_Instant_1);
		break;
	}
	case LCD_Instant_2:
	{
		MCAL_GPIO_WritePin(LCD_2_CMD_PORT, RS_2, GPIO_PIN_LOW);


		(GET_BIT(cmd,7)) ? MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D7_2,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D7_2,GPIO_PIN_LOW);
		(GET_BIT(cmd,6)) ? MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D6_2,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D6_2,GPIO_PIN_LOW);
		(GET_BIT(cmd,5)) ? MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D5_2,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D5_2,GPIO_PIN_LOW);
		(GET_BIT(cmd,4)) ? MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D4_2,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D4_2,GPIO_PIN_LOW);
		//Trigger Enable
		LCD_ES_tTrigger_Enable(LCD_Instant_2);
		(GET_BIT(cmd,3)) ? MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D7_2,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D7_2,GPIO_PIN_LOW);
		(GET_BIT(cmd,2)) ? MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D6_2,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D6_2,GPIO_PIN_LOW);
		(GET_BIT(cmd,1)) ? MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D5_2,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D5_2,GPIO_PIN_LOW);
		(GET_BIT(cmd,0)) ? MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D4_2,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D4_2,GPIO_PIN_LOW);
		//Trigger Enable
		LCD_ES_tTrigger_Enable(LCD_Instant_2);
		break;
	}
	}

	return ES_OK;

}
ES_t Lcd_ES_tsendChar(LCD_Instant instant, uint8_t data){

	switch(instant){
	case LCD_Instant_1:
	{
		MCAL_GPIO_WritePin(LCD_1_CMD_PORT, RS_1, GPIO_PIN_HIGH);


		(GET_BIT(data,7)) ? MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D7_1,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D7_1,GPIO_PIN_LOW);
		(GET_BIT(data,6)) ? MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D6_1,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D6_1,GPIO_PIN_LOW);
		(GET_BIT(data,5)) ? MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D5_1,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D5_1,GPIO_PIN_LOW);
		(GET_BIT(data,4)) ? MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D4_1,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D4_1,GPIO_PIN_LOW);
		//Trigger Enable
		LCD_ES_tTrigger_Enable(LCD_Instant_1);
		(GET_BIT(data,3)) ? MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D7_1,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D7_1,GPIO_PIN_LOW);
		(GET_BIT(data,2)) ? MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D6_1,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D6_1,GPIO_PIN_LOW);
		(GET_BIT(data,1)) ? MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D5_1,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D5_1,GPIO_PIN_LOW);
		(GET_BIT(data,0)) ? MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D4_1,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_1_DATA_PORT, D4_1,GPIO_PIN_LOW);
		//Trigger Enable
		LCD_ES_tTrigger_Enable(LCD_Instant_1);
		break;
	}
	case LCD_Instant_2:
	{
		MCAL_GPIO_WritePin(LCD_2_CMD_PORT, RS_2, GPIO_PIN_HIGH);


		(GET_BIT(data,7)) ? MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D7_2,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D7_2,GPIO_PIN_LOW);
		(GET_BIT(data,6)) ? MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D6_2,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D6_2,GPIO_PIN_LOW);
		(GET_BIT(data,5)) ? MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D5_2,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D5_2,GPIO_PIN_LOW);
		(GET_BIT(data,4)) ? MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D4_2,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D4_2,GPIO_PIN_LOW);
		//Trigger Enable
		LCD_ES_tTrigger_Enable(LCD_Instant_2);
		(GET_BIT(data,3)) ? MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D7_2,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D7_2,GPIO_PIN_LOW);
		(GET_BIT(data,2)) ? MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D6_2,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D6_2,GPIO_PIN_LOW);
		(GET_BIT(data,1)) ? MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D5_2,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D5_2,GPIO_PIN_LOW);
		(GET_BIT(data,0)) ? MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D4_2,GPIO_PIN_HIGH) : MCAL_GPIO_WritePin(LCD_2_DATA_PORT, D4_2,GPIO_PIN_LOW);
		//Trigger Enable
		LCD_ES_tTrigger_Enable(LCD_Instant_2);
		break;
	}
	}
	return ES_OK;

}

ES_t Lcd_ES_tsendString(LCD_Instant instant, char *data)
{

	switch(instant){
	case LCD_Instant_1:
	{
		MCAL_GPIO_WritePin(LCD_1_CMD_PORT, RS_1, GPIO_PIN_HIGH);

		unsigned char i=0;
		while(data[i]!=0)
		{
			Lcd_ES_tsendChar(LCD_Instant_1,data[i]);
			i++;
		}
		break;
	}
	case LCD_Instant_2:
	{
		MCAL_GPIO_WritePin(LCD_2_CMD_PORT, RS_2, GPIO_PIN_HIGH);

		unsigned char i=0;
		while(data[i]!=0)
		{
			Lcd_ES_tsendChar(LCD_Instant_2,data[i]);
			i++;
		}
		break;
	}
	}


	return ES_OK;
}

ES_t Lcd_ES_tsendString_xy(LCD_Instant instant, char *data,uint8_t row,uint8_t col){

	switch(instant){
	case LCD_Instant_1:
	{
		MCAL_GPIO_WritePin(LCD_1_CMD_PORT, RS_1, GPIO_PIN_HIGH);


		LCD_ES_tSet_Cursor_Pos(LCD_Instant_1,row,col);
		Lcd_ES_tsendString(LCD_Instant_1,data);
		break;
	}
	case LCD_Instant_2:
	{
		MCAL_GPIO_WritePin(LCD_2_CMD_PORT, RS_2, GPIO_PIN_HIGH);


		LCD_ES_tSet_Cursor_Pos(LCD_Instant_2,row,col);
		Lcd_ES_tsendString(LCD_Instant_2,data);
		break;
	}
	}


	return ES_OK;

}


//A function to display Numbers instead of characters
ES_t Lcd_ES_tdisplayNum(LCD_Instant instant, uint16_t num)
{

	switch(instant){
	case LCD_Instant_1:
	{
		MCAL_GPIO_WritePin(LCD_1_CMD_PORT, RS_1, GPIO_PIN_HIGH);

		uint8_t ch[10],i=0,j=0;
		if(num == 0)
		{
			Lcd_ES_tsendChar(LCD_Instant_1,'0');
		}
		else
		{
			while(num)
			{
				ch[i] = num % 10 + '0';  //To convert int to char
				num /= 10;
				i++;
			} //Thus number entered is reversed so, we want to display it correctly
			for(j=i;j>0;j--)
			{
				Lcd_ES_tsendChar(LCD_Instant_1,ch[j-1]);
			}
		}
		break;
	}
	case LCD_Instant_2:
	{
		MCAL_GPIO_WritePin(LCD_2_CMD_PORT, RS_2, GPIO_PIN_HIGH);

		uint8_t ch[10],i=0,j=0;
		if(num == 0)
		{
			Lcd_ES_tsendChar(LCD_Instant_2,'0');
		}
		else
		{
			while(num)
			{
				ch[i] = num % 10 + '0';  //To convert int to char
				num /= 10;
				i++;
			} //Thus number entered is reversed so, we want to display it correctly
			for(j=i;j>0;j--)
			{
				Lcd_ES_tsendChar(LCD_Instant_2,ch[j-1]);
			}
		}
		break;
	}
	}



	return ES_OK;
}

ES_t Lcd_ES_tdisplayNum_xy(LCD_Instant instant, uint16_t num,uint8_t row,uint8_t col){


	switch(instant){
	case LCD_Instant_1:
	{
		MCAL_GPIO_WritePin(LCD_1_CMD_PORT, RS_1, GPIO_PIN_HIGH);



		if(row == 1){
			Lcd_ES_tsendCmd(LCD_Instant_1,Force1stline);
			wait_ms(1);
		}else if(row == 2){
			Lcd_ES_tsendCmd(LCD_Instant_1,Force2ndline);
			wait_ms(10);
		}else{
			return ES_NOT_OK;
		}


		for(int j=1;j<=col;j++){
			Lcd_ES_tsendCmd(LCD_Instant_1,ShiftRight);
		}

		Lcd_ES_tdisplayNum(LCD_Instant_1,num);
		break;
	}
	case LCD_Instant_2:
	{
		MCAL_GPIO_WritePin(LCD_2_CMD_PORT, RS_2, GPIO_PIN_HIGH);



		if(row == 1){
			Lcd_ES_tsendCmd(LCD_Instant_2,Force1stline);
			wait_ms(1);
		}else if(row == 2){
			Lcd_ES_tsendCmd(LCD_Instant_2,Force2ndline);
			wait_ms(10);
		}else{
			return ES_NOT_OK;
		}


		for(int j=1;j<=col;j++){
			Lcd_ES_tsendCmd(LCD_Instant_2,ShiftRight);
		}

		Lcd_ES_tdisplayNum(LCD_Instant_2,num);
		break;
	}
	}




	return ES_OK;

}

ES_t Lcd_ES_tsendChar_xy(LCD_Instant instant, uint8_t data,uint8_t row,uint8_t col){


	switch(instant){
	case LCD_Instant_1:
	{
		MCAL_GPIO_WritePin(LCD_1_CMD_PORT, RS_1, GPIO_PIN_HIGH);


		if(row == 1){
			Lcd_ES_tsendCmd(LCD_Instant_1,Force1stline);
			wait_ms(1);
		}else if(row == 2){
			Lcd_ES_tsendCmd(LCD_Instant_1,Force2ndline);
			wait_ms(10);
		}else{
			return ES_NOT_OK;
		}

		for(int j=1;j<=col;j++){
			Lcd_ES_tsendCmd(LCD_Instant_1,ShiftRight);
		}
		Lcd_ES_tsendChar(LCD_Instant_1,data);
		break;
	}
	case LCD_Instant_2:
	{
		MCAL_GPIO_WritePin(LCD_2_CMD_PORT, RS_2, GPIO_PIN_HIGH);


		if(row == 1){
			Lcd_ES_tsendCmd(LCD_Instant_2,Force1stline);
			wait_ms(1);
		}else if(row == 2){
			Lcd_ES_tsendCmd(LCD_Instant_2,Force2ndline);
			wait_ms(10);
		}else{
			return ES_NOT_OK;
		}

		for(int j=1;j<=col;j++){
			Lcd_ES_tsendCmd(LCD_Instant_2,ShiftRight);
		}
		Lcd_ES_tsendChar(LCD_Instant_2,data);
		break;
	}
	}




	return ES_OK;
}

static ES_t LCD_ES_tSet_Cursor_Pos(LCD_Instant instant,uint8_t row,uint8_t column){

	switch(instant)
	{
	case LCD_Instant_1:
	{
		column--;
		switch(row){
		case 1:
			Lcd_ES_tsendCmd(LCD_Instant_1,(0x80 + column));
			break;
		case 2:
			Lcd_ES_tsendCmd(LCD_Instant_1,(0xc0 + column));
			break;
		default:
			return ES_NOT_OK;
		}
		break;
	}
	case LCD_Instant_2:
	{
		column--;
		switch(row){
		case 1:
			Lcd_ES_tsendCmd(LCD_Instant_2,(0x80 + column));
			break;
		case 2:
			Lcd_ES_tsendCmd(LCD_Instant_2,(0xc0 + column));
			break;
		default:
			return ES_NOT_OK;
		}
		break;
	}
	}



	return ES_OK;
}

/************************************************************************/
ES_t LCD_ES_tGoTo(LCD_Instant instant, uint8_t Line, uint8_t x){


	switch(instant)
	{
	case LCD_Instant_1:
	{
		if(0 == Line)
		{
			if ( x <=15)
			{
				Lcd_ES_tsendCmd(LCD_Instant_1,(0x80 + x));
			}
		}
		else if (1 == Line)
		{
			if ( x <=15)
			{
				Lcd_ES_tsendCmd(LCD_Instant_1,(0xC0 + x));
			}
		}// In case of 16*4 lcd
		else if(2 == Line)
		{
			if ( x <=15)
			{
				Lcd_ES_tsendCmd(LCD_Instant_1,(0x90 + x));
			}
		}else if(3 == Line)
		{
			if ( x <=15)
			{
				Lcd_ES_tsendCmd(LCD_Instant_1,(0xD0 + x));
			}
		}else{
			return ES_NOT_OK;
		}
		break;
	}
	case LCD_Instant_2:
	{
		if(0 == Line)
		{
			if ( x <=15)
			{
				Lcd_ES_tsendCmd(LCD_Instant_2,(0x80 + x));
			}
		}
		else if (1 == Line)
		{
			if ( x <=15)
			{
				Lcd_ES_tsendCmd(LCD_Instant_2,(0xC0 + x));
			}
		}// In case of 16*4 lcd
		else if(2 == Line)
		{
			if ( x <=15)
			{
				Lcd_ES_tsendCmd(LCD_Instant_2,(0x90 + x));
			}
		}else if(3 == Line)
		{
			if ( x <=15)
			{
				Lcd_ES_tsendCmd(LCD_Instant_2,(0xD0 + x));
			}
		}else{
			return ES_NOT_OK;
		}
		break;
	}
	}




	return ES_OK;
}


/************************************************************************/

