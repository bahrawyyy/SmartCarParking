/*
 * Stm32_F103C6_USART_driver.c
 *
 *  Created on: Jul 20, 2023
 *      Author: Abdallah
 */


#include "Stm32_F103C6_USART_driver.h"


// Generic Variables ( To be used in other functions;
UART_Config Global_UART_Config[3] = {0};




static uint8_t which_UART(USART_Typedef * USARTx)
{
	if(USARTx == USART1)
		return 0;
	else if(USARTx == USART2)
		return 1;
	else if(USARTx == USART3)
		return 2;
	return 3;
}



/**================================================================
 * @Fn					- MCAL_UART_Init
 * @brief 				- Initializes UART (Supported feature : ASYNCHRONOUS only)
 * @param [in] 			- USARTx: where x can be (1..3) depending on the device used
 * @param [in] 			- UARTCfg: All the UART configurations
 * @retval 				- None
 * Note					- The driver supports Asynchronous mode & HSI clock 8 Mhz
 */

void MCAL_UART_Init(USART_Typedef * USARTx, UART_Config* UARTCfg)
{
	uint32_t Pclk,BRR;


	//	Global_UART_Config = UARTCfg;   // To have backup



	// 1- Enable clock for the given USART Peripheral

	if(USARTx == USART1){
		Global_UART_Config[0] = *UARTCfg;
		RCC_USART1_CLK_EN();
	}
	else if(USARTx == USART2){
		Global_UART_Config[1] = *UARTCfg;
		RCC_USART2_CLK_EN();
	}else if(USARTx == USART3){
		Global_UART_Config[2] = *UARTCfg;
		RCC_USART3_CLK_EN();
	}



	// 2- Enable the USART Module (Bit 13 UE: USART enable)
	USARTx->CR1 |= (1<<13);

	// 3- Enable the Tx/Rx according to the USART_Mode_Configuration item
	USARTx->CR1 |= UARTCfg->USART_Mode;

	// 4- Payload length CR1
	USARTx->CR1 |= UARTCfg->Payload_length;

	// Parity bits CR1
	USARTx->CR1 |= UARTCfg->Parity;

	// Stop bits CR2
	USARTx->CR2 |= UARTCfg->StopBits;

	// Flow control CR3
	USARTx->CR3 |= UARTCfg->HWFlowCtrl;


	// Configuration of Baud rate (BRR register)
	// PCLK1 for USART2,3
	// PCLK2 for USART1

	if(USARTx == USART1)
	{
		Pclk = MCAL_RCC_GetPCLK2Freq();
	}else{
		Pclk = MCAL_RCC_GetPCLK1Freq();
	}

	BRR = UART_BRR_Register(Pclk,UARTCfg->BaudRate);
	USARTx->BRR = BRR;


	// Enable / Disable Interrupts
	if(UARTCfg->IRQ_Enable != UART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= (UARTCfg->IRQ_Enable);

		// Enable NVIC for USARTx IRQ

		if(USARTx == USART1)
			NVIC_IRQ37_USART1_Enable;
		else if(USARTx == USART2)
			NVIC_IRQ38_USART2_Enable;
		else if(USARTx == USART3)
			NVIC_IRQ39_USART3_Enable;

	}

}



/**================================================================
 * @Fn					- MCAL_UART_DeInit
 * @brief 				- DeInitializes UART (Supported feature : ASYNCHRONOUS only)
 * @param [in] 			- USARTx: where x can be (1..3) depending on the device used
 * @retval 				- None
 * Note					- Resets the USART module using RCC Reset registers
 */


void MCAL_UART_DeInit(USART_Typedef * USARTx)
{

	if(USARTx == USART1)
	{
		RCC_USART1_Reset();
		NVIC_IRQ37_USART1_Disable;
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_Reset();
		NVIC_IRQ38_USART2_Disable;
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_Reset();
		NVIC_IRQ39_USART3_Disable;
	}

}



/**================================================================
 * @Fn					- MCAL_UART_SendData
 * @brief 				- Send buffer on UART
 * @param [in] 			- USARTx: where x can be (1..3) depending on the device used
 * @param [in] 			- pTxBuffer: buffer
 * @param [in]			- PollingEn: Enable polling or not
 * @retval 				- None
 * Note					- When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
							the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
							because it is replaced by the parity.
							When receiving with the parity enabled, the value read in the MSB bit is the received parity bit.
 */




void MCAL_UART_SendData(USART_Typedef * USARTx, uint16_t* pTxBuffer, enum Polling_Mechanism PollingEn)
{
	// Wait until TXE flag is set (Empty)
	if(PollingEn == Enable){
		while(!(USARTx->SR & 1<<7));
	}

	uint8_t index = which_UART(USARTx);


	// Check the word length

	//	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	//			the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	//			because it is replaced by the parity.
	//			When receiving with the parity enabled, the value read in the MSB bit is the received parity bit.

	if(Global_UART_Config[index].Payload_length == UART_Payload_Length_9B)
	{
		USARTx->DR = (*pTxBuffer & (uint16_t)0x01FF);
	}else
	{
		USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
	}
}





void MCAL_UART_SendString(USART_Typedef * USARTx, uint8_t* pTxBuffer, enum Polling_Mechanism PollingEn)
{
    uint16_t DefaultStop = '\r';

    uint8_t i = 0;
    while (pTxBuffer[i] != '\0')
    {
        MCAL_UART_SendData(USARTx, &(pTxBuffer[i]), PollingEn);
        i++;
    }
    MCAL_UART_SendData(USARTx, &DefaultStop, PollingEn);
}




/**================================================================
 * @Fn					- MCAL_UART_WAIT_TC
 * @brief 				- Waits until the last buffer is sent
 * @param [in] 			- USARTx: where x can be (1..3) depending on the device used
 * @retval 				- None
 * Note					- None
 */


void MCAL_UART_WAIT_TC (USART_Typedef *USARTx )
{
	// Wait until TC flag is set in the SR
	while(!(USARTx->SR & 1<<6));
}



/**================================================================
 * @Fn					- MCAL_UART_ReceiveData
 * @brief 				- Send buffer on UART
 * @param [in] 			- USARTx: where x can be (1..3) depending on the device used
 * @param [in] 			- pRxBuffer: buffer
 * @param [in]			- PollingEn: Enable polling or not
 * @retval 				- None
 * Note					- When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
							the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
							because it is replaced by the parity.
							When receiving with the parity enabled, the value read in the MSB bit is the received parity bit.
 */


void MCAL_UART_ReceiveData(USART_Typedef * USARTx, uint16_t* pRxBuffer, enum Polling_Mechanism PollingEn)
{
	// Wait until RXNE flag is set in the SR
	if(PollingEn == Enable){
		while(!(USARTx->SR & 1<<5));
	}

	uint8_t index = which_UART(USARTx);

	// Check the word length

	if(Global_UART_Config[index].Payload_length == UART_Payload_Length_9B)
	{
		if(Global_UART_Config[index].Parity == UART_Parity_NONE)
		{
			*((uint16_t*)pRxBuffer) = USARTx->DR;
		}else{
			// MSB is parity not data (8 bits data, 1 parity)
			*((uint16_t*)pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);
		}
	}else
	{    // 8 bits data
		if(Global_UART_Config[index].Parity == UART_Parity_NONE)
		{
			*((uint16_t*)pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);
		}else{
			// MSB is parity not data (7 bits data, 1 parity)
			*((uint16_t*)pRxBuffer) = (USARTx->DR & (uint8_t)0x7F);
		}


	}

}


/**================================================================
 * @Fn					- MCAL_UART_GPIO_SetPins
 * @brief 				- Initializes GPIO pins
 * @param [in] 			- USARTx: where x can be (1..3) depending on the device used
 * @retval 				- None
 * Note					- should enable the corresponding AFIO & GPIO in RCC clock
 * 						  based on the recommended settings in data sheet
 */



void MCAL_UART_GPIO_SetPins(USART_Typedef * USARTx)
{
	GPIO_PinConfig_t PinCfg;


	if(USARTx == USART1)
	{
		// PA9 --> Tx
		PinCfg.GPIO_PinNumber = GPIO_PIN_9;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_OUTPUT_PUSHPULL;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(GPIOA, &PinCfg);


		// PA10 --> Rx
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA, &PinCfg);


		if(Global_UART_Config[0].HWFlowCtrl == UART_HWFlowCtrl_CTS || Global_UART_Config[0].HWFlowCtrl == UART_HWFlowCtrl_RTS_CTS)
		{
			// PA11 --> CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_11;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

		if(Global_UART_Config[0].HWFlowCtrl == UART_HWFlowCtrl_RTS || Global_UART_Config[0].HWFlowCtrl == UART_HWFlowCtrl_RTS_CTS)
		{
			// PA12 --> RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_12;
			PinCfg.GPIO_MODE = GPIO_MODE_AF_OUTPUT_PUSHPULL;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}


	}
	else if(USARTx == USART2)
	{

		// PA2 --> Tx
		PinCfg.GPIO_PinNumber = GPIO_PIN_2;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_OUTPUT_PUSHPULL;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(GPIOA, &PinCfg);


		// PA3 --> Rx
		PinCfg.GPIO_PinNumber = GPIO_PIN_3;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA, &PinCfg);


		if(Global_UART_Config[1].HWFlowCtrl == UART_HWFlowCtrl_CTS || Global_UART_Config[1].HWFlowCtrl == UART_HWFlowCtrl_RTS_CTS)
		{
			// PA0 --> CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_0;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

		if(Global_UART_Config[1].HWFlowCtrl == UART_HWFlowCtrl_RTS || Global_UART_Config[1].HWFlowCtrl == UART_HWFlowCtrl_RTS_CTS)
		{
			// PA1 --> RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_1;
			PinCfg.GPIO_MODE = GPIO_MODE_AF_OUTPUT_PUSHPULL;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

	}
	else if(USARTx == USART3)
	{

		// PB10 --> Tx
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_OUTPUT_PUSHPULL;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(GPIOB, &PinCfg);


		// PA11 --> Rx
		PinCfg.GPIO_PinNumber = GPIO_PIN_11;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOB, &PinCfg);


		if(Global_UART_Config[2].HWFlowCtrl == UART_HWFlowCtrl_CTS || Global_UART_Config[2].HWFlowCtrl == UART_HWFlowCtrl_RTS_CTS)
		{
			// PB13 --> CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}

		if(Global_UART_Config[2].HWFlowCtrl == UART_HWFlowCtrl_RTS || Global_UART_Config[2].HWFlowCtrl == UART_HWFlowCtrl_RTS_CTS)
		{
			// PA14 --> RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_MODE = GPIO_MODE_AF_OUTPUT_PUSHPULL;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

	}
}







// ISR

void USART1_IRQHandler(void)
{
	Global_UART_Config[0].P_IRQ_CallBack();
}

void USART2_IRQHandler(void)
{
	Global_UART_Config[1].P_IRQ_CallBack();
}

void USART3_IRQHandler(void)
{
	Global_UART_Config[2].P_IRQ_CallBack();
}









