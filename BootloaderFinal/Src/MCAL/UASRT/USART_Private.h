/*
 * UART_Private.h
 *
 *  Created on: Sep 8, 2023
 *      Author: adham
 */

/****************************File Guard*******************************/
#ifndef MCAL_UASRT_UART_PRIVATE_H_
#define MCAL_UASRT_UART_PRIVATE_H_
/*********************************************************************/

/*****************************Includes********************************/
#include"../../INC/Macros.h"
#include"../../INC/STD_TYPES.h"
/*********************************************************************/

/****************************BASE_Addresses***************************/
#define UART1_BASE_ADDRESS			(0x40011000)
#define UART2_BASE_ADDRESS			(0x40004400)
#define UART6_BASE_ADDRESS			(0x40011400)
/*********************************************************************/

/**************************UART Registers***************************/
typedef struct {
volatile uint32_t UART_SR     ;
volatile uint32_t UART_DR     ;
volatile uint32_t UART_BRR    ;
volatile uint32_t UART_CR1    ;
volatile uint32_t UART_CR2    ;
volatile uint32_t UART_CR3    ;
volatile uint32_t UART_GTPR   ;
}UART_Registers_t;
/********************************************************************/

/***************************Peripheral Instants*********************/
#define UART1		((volatile UART_Registers_t*)UART1_BASE_ADDRESS)
#define UART2		((volatile UART_Registers_t*)UART2_BASE_ADDRESS)
#define UART6		((volatile UART_Registers_t*)UART6_BASE_ADDRESS)
/*******************************************************************/

/**************************Private Macros***************************/
#define UART1_INDEX				0
#define UART2_INDEX				1
#define UART6_INDEX				3

#define UART1_IRQN				37
#define UART2_IRQN				38
#define UART6_IRQN				71
/*******************************************************************/

/**************************Registers Bits Macros********************/

//@USART_CR1:
#define UE			13
//@USART_SR
/*
 * Bit 7 TXE: Transmit data register empty
 */
#define TXE			7
/*
 * Bit 6 TC: Transmission complete
 */
#define TC			6
/*
 * Bit 5 RXNE: Read data register not empty
 */
#define RXNE		5

/*******************************************************************/

/**************************BaudRate Calculation Macros*************/
#define USART_DIV_FACTOR(PCLK,BR)				(uint32_t)(PCLK/(16*BR))
#define USART_DIV_FACTOR_MUL100(PCLK,BR)		(uint32_t)((25*PCLK)/(4*BR))
#define USART_MANTISSA_MUL100(PCLK,BR)			(uint32_t)(USART_DIV_FACTOR(PCLK,BR) *100)
#define DIV_MANTISSA(PCLK,BR)					(uint32_t)(USART_DIV_FACTOR(PCLK,BR))
#define DIV_FRACTION(PCLK,BR)					(uint32_t)(((USART_DIV_FACTOR_MUL100(PCLK,BR) - USART_MANTISSA_MUL100(PCLK,BR))*16)/100)
#define USART_BRR_VALUE(PCLK,BR)				((DIV_MANTISSA(PCLK,BR)<<4)|(DIV_FRACTION(PCLK,BR)&0xF))
/******************************************************************/
#endif /* MCAL_UASRT_UART_PRIVATE_H_ */
