/*
 * USART_Program.c
 *
 *  Created on: Sep 8, 2023
 *      Author: adham
 */

/*******************************File Includes**********************************/
#include"USART_Private.h"
#include"USART_interface.h"
/*****************************************************************************/

/******************************Global Variables******************************/
UART_Config_t Gl_UART_Config[3];
/****************************************************************************/
void MCAL_UART_Init(UART_Registers_t *UARTx ,UART_Config_t *UARTx_Config)
{
/****************************We Works on OVER8=0*****************************/
		if(UARTx == UART1)
		{
			Gl_UART_Config[UART1_INDEX] = *UARTx_Config;
			MCAL_RCC_voidPeripheral_EN(USART1_PERIPHERAL, APB2_BUS);
		}
		else if(UARTx == UART2)
		{
			Gl_UART_Config[UART2_INDEX] = *UARTx_Config;
			MCAL_RCC_voidPeripheral_EN(USART2_PERIPHERAL, APB1_BUS);
		}
		else
		{
			Gl_UART_Config[UART6_INDEX] = *UARTx_Config;
			MCAL_RCC_voidPeripheral_EN(USART6_PERIPHERAL, APB2_BUS);
		}
//@1-Enable the USART Peripheral
//Bit 13 UE: USART enable -> CR1
		SET_BIT(UARTx->UART_CR1,UE);
//@2-Enable the Tx/Rx According to user config
//Bit 2 RE: Receiver enable
//Bit 3 TE: Transmitter enable
		UARTx->UART_CR1 |= UARTx_Config->UART_Mode ;
//@3-Data Length
//Bit 12 M: Word length
		UARTx->UART_CR1 |= UARTx_Config->UART_DataLength;
//@4-Parity Bits
//Bit 10 PCE: Parity control enable
//Bit 9 PS: Parity selection
		UARTx->UART_CR1 |= UARTx_Config->UART_ParityBits;
//@5-Stop Bits
//Bits 13:12 STOP: STOP bits
		UARTx->UART_CR2 |= UARTx_Config->UART_StopBits;
//@6-Configure the BaudRate
//PCLK1->USART2
//PCLK2->USART1,USART6
/*
 Bits 15:4 DIV_Mantissa[11:0]: mantissa of USARTDIV
Bits 3:0 DIV_Fraction[3:0]: fraction of USARTDIV
These 4 bits define the fraction of the USART Divider (USARTDIV). When OVER8=1, the
DIV_Fraction3 bit is not considered and must be kept cleared.
 */
		uint32_t pclk , BRR ;
		if(UARTx == UART1 || UARTx == UART6)
		{
			pclk = MCALL_RCC_GetPCLK1Freq();
		}
		else
		{
			pclk = MCALL_RCC_GetPCLK2Freq();
		}

/*
 USART_DIV = Fclk/(16*Baudrate) => OVER8=0 && Baudrate given by the user
 DIV_Mantissa = INTPART(USART_DIV)
 DIV_Fraction = (USART_DIV - DIV_Mantissa)*16
 */
		BRR = USART_BRR_VALUE(pclk,UARTx_Config->UART_BaudRate);
		UARTx->UART_BRR = BRR ;
//@7-Check for interrupt configurations
		if(UARTx_Config->UART_IRQ_State != UART_IRQ_DIS)
		{
			/*
			 * Bit 7 TXEIE: TXE interrupt enable
			 * Bit 6 TCIE: Transmission complete interrupt enable
			 * Bit 5 RXNEIE: RXNE interrupt enable
			 */
			UARTx->UART_CR2 |= UARTx_Config->UART_IRQ_State;
			//Enable the NVIC Peripheral
			if(UARTx == UART1)
			{
				MCAL_NVIC_EnIRQ(UART1_IRQN);
			}
			if(UARTx == UART2)
			{
				MCAL_NVIC_EnIRQ(UART2_IRQN);
			}
			if(UARTx == UART6)
			{
				MCAL_NVIC_EnIRQ(UART1_IRQN);
			}

		}
}

void MCAL_UART_DeInit(UART_Registers_t *UARTx)
{
			if(UARTx == UART1)
			{
				MCAL_RCC_voidPeripheral_DIS(USART1_PERIPHERAL, APB2_BUS);
				MCAL_NVIC_DisIRQ(UART1_IRQN);
			}
			else if(UARTx == UART2)
			{
				MCAL_RCC_voidPeripheral_DIS(USART2_PERIPHERAL, APB1_BUS);
				MCAL_NVIC_DisIRQ(UART2_IRQN);
			}
			else
			{
				MCAL_RCC_voidPeripheral_DIS(USART6_PERIPHERAL, APB2_BUS);
				MCAL_NVIC_DisIRQ(UART6_IRQN);
			}
}

void MCAL_UART_Wait_TC(UART_Registers_t *UARTx)
{
	while(!GET_BIT(UARTx->UART_SR,TC));
}

void MCAL_UART_SendData(UART_Registers_t *UARTx,uint16_t *DataBuffer)
{
/*
* 7. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
for each data to be transmitted in case of single buffer
*/

//@1-Wait until TXE=1
while(!GET_BIT(UARTx->UART_SR,TXE));
//@2-Check the Data length is 8bits or 9bits
/*
When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register), the
value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect because
it is replaced by the parity.
When receiving with the parity enabled, the value read in the MSB bit is the received parity
bit.
 */

		if(UARTx == UART1)
		{
			if(Gl_UART_Config[UART1_INDEX].UART_DataLength == UART_DATA_LENGTH_9B)
			{
				UARTx->UART_DR = (*DataBuffer & (uint16_t)0x1FF);
			}
			else
			{
				UARTx->UART_DR = (*DataBuffer & (uint8_t)0xFF);
			}
		}
		else if(UARTx == UART2)
		{
			if(Gl_UART_Config[UART2_INDEX].UART_DataLength == UART_DATA_LENGTH_9B)
			{
				UARTx->UART_DR = (*DataBuffer & (uint16_t)0x1FF);
			}
			else
			{
				UARTx->UART_DR = (*DataBuffer & (uint8_t)0xFF);
			}
		}
		else
		{
			if(Gl_UART_Config[UART6_INDEX].UART_DataLength == UART_DATA_LENGTH_9B)
			{
				UARTx->UART_DR = (*DataBuffer & (uint16_t)0x1FF);
			}
			else
			{
				UARTx->UART_DR = (*DataBuffer & (uint8_t)0xFF);
			}
		}
		void MCAL_UART_Wait_TC(UARTx);
}



void MCAL_UART_ReciveData(UART_Registers_t *UARTx,uint16_t *DataBuffer)
{
/*
The RXNE bit is set. It indicates that the content of the shift register is transferred to the
RDR. In other words, data has been received and can be read (as well as its
associated error flags).
*/
	while(!GET_BIT(UARTx->UART_SR,RXNE));
	//@2-Check the Data length is 8bits or 9bits

	if(UARTx == UART1)
	{
		if(Gl_UART_Config[UART1_INDEX].UART_DataLength == UART_DATA_LENGTH_9B)
		{
			if(Gl_UART_Config[UART1_INDEX].UART_ParityBits == UART_NO_PARITY)
			{
				*((uint16_t*)DataBuffer) = UARTx->UART_DR;
			}
			else
			{
				*((uint16_t*)DataBuffer) = (UARTx->UART_DR & (uint8_t)0xFF);
			}
		}
		else
		{
			if(Gl_UART_Config[UART1_INDEX].UART_ParityBits == UART_NO_PARITY)
						{
							*((uint16_t*)DataBuffer) = UARTx->UART_DR;
						}
						else
						{
							*((uint16_t*)DataBuffer) = (UARTx->UART_DR & (uint8_t)0x7F);
						}
		}

	}
	else if(UARTx == UART2)
	{
		if(Gl_UART_Config[UART2_INDEX].UART_DataLength == UART_DATA_LENGTH_9B)
		{
			if(Gl_UART_Config[UART2_INDEX].UART_ParityBits == UART_NO_PARITY)
			{
				*((uint16_t*)DataBuffer) = UARTx->UART_DR;
			}
			else
			{
				*((uint16_t*)DataBuffer) = (UARTx->UART_DR & (uint8_t)0xFF);
			}
		}
		else
		{
			if(Gl_UART_Config[UART2_INDEX].UART_ParityBits == UART_NO_PARITY)
						{
							*((uint16_t*)DataBuffer) = UARTx->UART_DR;
						}
						else
						{
							*((uint16_t*)DataBuffer) = (UARTx->UART_DR & (uint8_t)0x7F);
						}
		}
	}
	else
	{

		if(Gl_UART_Config[UART6_INDEX].UART_DataLength == UART_DATA_LENGTH_9B)
		{
			if(Gl_UART_Config[UART6_INDEX].UART_ParityBits == UART_NO_PARITY)
			{
				*((uint16_t*)DataBuffer) = UARTx->UART_DR;
			}
			else
			{
				*((uint16_t*)DataBuffer) = (UARTx->UART_DR & (uint8_t)0xFF);
			}
		}
		else
		{
			if(Gl_UART_Config[UART6_INDEX].UART_ParityBits == UART_NO_PARITY)
						{
							*((uint16_t*)DataBuffer) = UARTx->UART_DR;
						}
						else
						{
							*((uint16_t*)DataBuffer) = (UARTx->UART_DR & (uint8_t)0x7F);
						}
		}
	}


}
void MCAL_UART_GPIO_SetPins(UART_Registers_t *UARTx)
{
	GPIOx_Config_t UART_Pins ;
	if(UARTx == UART1)
	{
		//Activate the Tx
		UART_Pins.GPIO_PIN_NUMBER = GPIO_PIN_9 ;
		UART_Pins.GPIO_PIN_MODE = AFIO_OUT_PP ;
		UART_Pins.AFIO_SELECT = AFIO_7 ;
		UART_Pins.GPIO_PIN_OUT_SPEED = GPIO_OUT_SPEED_MEDIUM;
		MCAL_GPIOx_Init(GPIOA, &UART_Pins);
		//Activate the Rx
		UART_Pins.GPIO_PIN_NUMBER = GPIO_PIN_10 ;
		UART_Pins.GPIO_PIN_MODE = AFIO_INPUT ;
		UART_Pins.AFIO_SELECT = AFIO_7 ;
		MCAL_GPIOx_Init(GPIOA, &UART_Pins);
	}
	else if(UARTx == UART2)
	{
		//Activate the Tx
		UART_Pins.GPIO_PIN_NUMBER = GPIO_PIN_2 ;
		UART_Pins.GPIO_PIN_MODE = AFIO_OUT_PP ;
		UART_Pins.AFIO_SELECT = AFIO_7 ;
		UART_Pins.GPIO_PIN_OUT_SPEED = GPIO_OUT_SPEED_MEDIUM;
		MCAL_GPIOx_Init(GPIOA, &UART_Pins);
		//Activate the Rx
		UART_Pins.GPIO_PIN_NUMBER = GPIO_PIN_3 ;
		UART_Pins.GPIO_PIN_MODE = AFIO_INPUT ;
		UART_Pins.AFIO_SELECT = AFIO_7 ;
		MCAL_GPIOx_Init(GPIOA, &UART_Pins);
	}
	else
	{
		//Activate the Tx
		UART_Pins.GPIO_PIN_NUMBER = GPIO_PIN_10 ;
		UART_Pins.GPIO_PIN_MODE = AFIO_OUT_PP ;
		UART_Pins.AFIO_SELECT = AFIO_8 ;
		UART_Pins.GPIO_PIN_OUT_SPEED = GPIO_OUT_SPEED_MEDIUM;
		MCAL_GPIOx_Init(GPIOB, &UART_Pins);
		//Activate the Rx
		UART_Pins.GPIO_PIN_NUMBER = GPIO_PIN_11 ;
		UART_Pins.GPIO_PIN_MODE = AFIO_INPUT ;
		UART_Pins.AFIO_SELECT = AFIO_8 ;
		MCAL_GPIOx_Init(GPIOB, &UART_Pins);
	}
}

void MCAL_UART_SendString(UART_Registers_t *UARTx , uint8_t *Data)
{
	uint32_t itr = 0;

		while(Data[itr] != '\0')
		{
			MCAL_UART_SendData(UARTx,&Data[itr]);
			while((GET_BIT(UARTx->UART_SR, 6)) == 0);
			itr++;
		}

}
uint8_t MCAL_UART_Recive_Byte_Synch(UART_Registers_t *UARTx,uint8_t *DataBuffer)
{
	uint8_t FlagStatus = 0 ;

	/*No Polling*/
	if(GET_BIT(UARTx->UART_SR,RXNE))
	{
		*DataBuffer = UARTx->UART_DR;
		FlagStatus = 1 ;
	}
	return FlagStatus;
}
