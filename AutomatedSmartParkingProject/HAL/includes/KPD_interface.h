/*
 * KPD_interface.h
 *
 *  Created on: May 4, 2023
 *      Author: Abdallah
 */

#ifndef HAL_KPD_KPD_INTERFACE_H_
#define HAL_KPD_KPD_INTERFACE_H_

#include "Stm32_F103C6_gpio_driver.h"
#include "stm32f103c6.h"
#include "ErrorStates.h"
#include "Lcd.h"

#define KPD_U8_NOT_PRESSED 0xff

ES_t KPD_ES_tGetKeyPressed(uint8_t *copy_pu8ReturnedKey);
ES_t KPD_init(void);

#endif /* HAL_KPD_KPD_INTERFACE_H_ */
