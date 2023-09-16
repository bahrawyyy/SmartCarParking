/*
 * Lcd.h
 *
 *  Created on: Sep 12, 2022
 *      Author: 10
 */

#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_


#include "Lcd_Config.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "stm32f103c6.h"
#include "ErrorStates.h"


#define Four_BitMode 0x02
#define Eight_BitMode 0x38
#define CLR_Display 0x01
#define D4_D7 0x28
#define CursorOFF 0x0c
#define CursorON 0x0E
#define IncrCursor 0x06
#define Force1stline 0x80
#define Force2ndline 0xC0
#define ShiftLeft 0x18
#define ShiftRight 0x1C


typedef enum{
	LCD_Instant_1,
	LCD_Instant_2
}LCD_Instant;

// ES_t DIO_ES_tTOGPin(DIO_U8_Port_Type copy_u8_PortId, DIO_U8_Pin_Type copy_u8_PinId);

void wait_ms(uint32_t time);
ES_t Lcd_ES_tInit(LCD_Instant instant);
ES_t Lcd_ES_tsendCmd(LCD_Instant instant,uint8_t cmd);
ES_t Lcd_ES_tsendChar(LCD_Instant instant,uint8_t data);
ES_t Lcd_ES_tsendChar_xy(LCD_Instant instant,uint8_t data,uint8_t row,uint8_t col);

ES_t Lcd_ES_tsendString(LCD_Instant instant,char *data);
ES_t Lcd_ES_tsendString_xy(LCD_Instant instant,char *data,uint8_t row,uint8_t col);

ES_t Lcd_ES_tdisplayNum(LCD_Instant instant,uint16_t num);
ES_t Lcd_ES_tdisplayNum_xy(LCD_Instant instant,uint16_t num,uint8_t row,uint8_t col);

ES_t LCD_ES_tGoTo(LCD_Instant instant,uint8_t Line, uint8_t x);
ES_t lcd_ES_tclear(LCD_Instant instant);


#endif /* HAL_LCD_LCD_H_ */
