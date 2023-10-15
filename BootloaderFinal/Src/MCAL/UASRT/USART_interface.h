/*
 * UART_interface.h
 *
 *  Created on: Sep 8, 2023
 *      Author: adham
 */
/*******************************File Guard*************************************/
#ifndef MCAL_UASRT_UART_INTERFACE_H_
#define MCAL_UASRT_UART_INTERFACE_H_
/******************************************************************************/

/*******************************File Includes**********************************/
#include"USART_Private.h"
#include"../../INC/Macros.h"
#include"../../INC/STD_TYPES.h"
#include"../RCC/RCC_interface.h"
#include"../GPIO/GPIO_Interface.h"
#include"../NVIC/NVIC_Interface.h"
/******************************************************************************/

/******************************Configuration Structure*************************/
typedef struct
{
	uint8_t UART_Mode					;//@ref : UART_MODE_SELECTION

	uint32_t UART_BaudRate				;//@ref : UART_BR_SELECTION

	uint32_t UART_DataLength			;//@ref : UART_DATA_LENGTH_SELECTION

	uint8_t UART_ParityBits			    ;//@ref : UART_PAARITY_BITS_SELECTION

	uint8_t UART_StopBits				;//@ref : UART_STOP_BITS_SELECTION

	uint8_t	UART_IRQ_State				;//@ref : UART_IRQ_SELECTION

	void	(*UART_CallBack)(void)		; //UART Call Back ptr to function

}UART_Config_t;
/*****************************************************************************/

/******************************Reference Macros*******************************/

//@ref:UART_MODE_SELECTION
#define UART_RX_MODE				(uint32_t)(1<<2) //Bit 2 RE: Receiver enable
#define UART_TX_MODE				(uint32_t)(1<<3) //Bit 3 TE: Transmitter enable
#define UART_TX_RX_MODE			(uint32_t)((1<<2)|(1<<3))


//@ref:UART_BR_SELECTION
#define UART_BAUDRATE_2400			2400
#define UART_BAUDRATE_9600			9600
#define UART_BAUDRATE_19200			19200
#define UART_BAUDRATE_38400			38400
#define UART_BAUDRATE_57600			57600
#define UART_BAUDRATE_115200	    115200
#define UART_BAUDRATE_230400	    230400
#define UART_BAUDRATE_460800	    460800

//@ref : UART_DATA_LENGTH_SELECTION
/*
 Bit 12 M: Word length
This bit determines the word length. It
0: 1 Start bit, 8 Data bits, n Stop bit
1: 1 Start bit, 9 Data bits, n Stop bit
 */
#define UART_DATA_LENGTH_8B		0
#define UART_DATA_LENGTH_9B		(uint32_t)(1<<12)

//@ref : UART_PARITY_BITS_SELECTION
/*
Bit 10 PCE: Parity control enable
0: Parity control disabled
1: Parity control enabled
Bit 9 PS: Parity selection
0: Even parity
1: Odd parity
 */
#define UART_NO_PARITY			0
#define UART_EVEN_PARITY		(uint32_t)(1<<10)
#define UART_ODD_PARITY			(uint32_t)((1<<10)|(1<<0))

//@ref : UART_STOP_BITS_SELECTION
/*
 Bits 13:12 STOP: STOP bits
These bits are used for programming the stop bits.
00: 1 Stop bit
01: 0.5 Stop bit
10: 2 Stop bit
 */
#define UART_ONE_STOP_BIT			0
#define UART_TWO_STOP_BIT			(uint32_t)(1<<13)

//@ref : UART_IRQ_SELECTION
#define UART_IRQ_DIS				0
/*
Bit 7 TXEIE: TXE interrupt enable
 */
#define UART_IRQ_TXE				(uint32_t)(1<<7)
/*
Bit 6 TCIE: Transmission complete interrupt enable
 */
#define UART_IRQ_TC				(uint32_t)(1<<6)
/*
Bit 5 RXNEIE: RXNE interrupt enable
 */
#define UART_IRQ_RXNE				(uint32_t)(1<<5)

/*****************************************************************************/


/*****************************************************************************
 * 							UART APIs										 *
 *****************************************************************************/

void MCAL_UART_Init(UART_Registers_t *UARTx ,UART_Config_t *UARTx_Config);
void MCAL_UART_DeInit(UART_Registers_t *UARTx);
void MCAL_UART_GPIO_SetPins(UART_Registers_t *UARTx);
void MCAL_UART_SendData(UART_Registers_t *UARTx,uint16_t *DataBuffer);
void MCAL_UART_ReciveData(UART_Registers_t *UARTx,uint16_t *DataBuffer);
uint8_t MCAL_UART_Recive_Byte_Synch(UART_Registers_t *UARTx,uint8_t *DataBuffer);
void MCAL_UART_Wait_TC(UART_Registers_t *UARTx);
void MCAL_UART_SendString(UART_Registers_t *UARTx , uint8_t Data[]);
#endif /* MCAL_UASRT_UART_INTERFACE_H_ */
