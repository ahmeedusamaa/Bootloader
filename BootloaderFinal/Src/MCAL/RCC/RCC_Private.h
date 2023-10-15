/*
 * STM32_F401xx.h
 *
 *  Created on: Aug 8, 2023
 *      Author: Adham Ehab
 */


#ifndef INC_STM32_F401XX_HEADER_H_
#define INC_STM32_F401XX_HEADER_H_

//-----------------------------------------
//File Includes
#include "../../INC/STD_TYPES.h"

/************************RCC Registers**********************/
typedef struct
{
	volatile uint32_t RCC_CR 		;
	volatile uint32_t RCC_PLLCFGR	;
	volatile uint32_t RCC_CFGR		;
	volatile uint32_t RCC_CIR		;
	volatile uint32_t RCC_AHB1RSTR	;
	volatile uint32_t RCC_AHB2RSTR	;
	volatile uint32_t Reserved1     ;
	volatile uint32_t Reserved2     ;
	volatile uint32_t RCC_APB1RSTR  ;
	volatile uint32_t RCC_APB2RSTR  ;
	volatile uint32_t Reserved3		;
	volatile uint32_t Reserved4		;
	volatile uint32_t RCC_AHB1ENR	;
	volatile uint32_t RCC_AHB2ENR   ;
	volatile uint32_t Reserved5		;
	volatile uint32_t Reserved6		;
	volatile uint32_t  RCC_APB1ENR	;
	volatile uint32_t  RCC_APB2ENR	;
	volatile uint32_t  Reserved7	;
	volatile uint32_t  Reserved8	;
	volatile uint32_t  RCC_AHB1LPENR;
	volatile uint32_t  RCC_AHB2LPENR;
	volatile uint32_t  Reserved9	;
	volatile uint32_t  Reserved10	;
	volatile uint32_t  RCC_APB1LPENR;
	volatile uint32_t  RCC_APB2LPENR;
	volatile uint32_t  Reserved11	;
	volatile uint32_t  Reserved12	;
	volatile uint32_t  RCC_BDCR		;
	volatile uint32_t  RCC_CSR		;
	volatile uint32_t  Reserved13	;
	volatile uint32_t  Reserved14	;
	volatile uint32_t  RCC_SSCGR	;
	volatile uint32_t  RCC_PLLI2SCFGR;
	volatile uint32_t Reserved15	;
	volatile uint32_t RCC_DCKCFG	;



}RCC_Registers_t;

/***************************RCC Instance************************************/
#define RCC_BASE			0x40023800
#define RCC					((volatile RCC_Registers_t*)RCC_BASE)
/*****************************Private Macros********************************/
//@RCC_CR BITS MACROS
#define HSION		0
#define HSIRDY		1
#define HSEON		16
#define HSERDY		17
#define HSEBYP		18
#define PLLON		24
#define PLLRDY		25
#define PLLI2SON	26
#define PLLI2SRDY	27
//@RCC_CFGR BITS MACROS
#define SW0			0
#define SW1			1
//@RCC_CFGR SWS Macros
#define HSI_SELECTED	0
#define HSE_SELECTED	1
#define PLL_SELECTED	2

/***********************************RCC HSI clock value*******************************/
#define HSI_CLK				(uint32_t)16000000
/*************************************************************************************/

#endif /* INC_STM32_F401XX_H_ */
