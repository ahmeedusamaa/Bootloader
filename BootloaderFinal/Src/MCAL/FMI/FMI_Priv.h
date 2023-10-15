/*
 * FMI_Priv.h
 *
 *  Created on: Sep 4, 2023
 *      Author: adham
 */

#ifndef MCAL_FMI_FMI_PRIV_H_
#define MCAL_FMI_FMI_PRIV_H_

#include"../../INC/STD_TYPES.h"

/***************************Base Address************************/
#define FMI_BASE_ADDR	0x40023C00
/**********************Keys Macros******************************/
#define FMI_KEY1	0x45670123
#define FMI_KEY2    0xCDEF89AB
/****************************************************************/

/*********************Registers Structure***********************/
typedef struct
{
	volatile uint32_t   FMI_ACR    	;
	volatile uint32_t   FMI_KEYR   	;
	volatile uint32_t   FMI_OPTKEYR ;
	volatile uint32_t   FMI_SR     	;
	volatile uint32_t   FMI_CR     	;
	volatile uint32_t   FMI_OPTCR  	;
}FMI_Registers_t;
/******************************************************************/

/*******************Peripheral Instance***************************/
#define FMI   ((volatile FMI_Registers_t*)(FMI_BASE_ADDR))
/*****************************************************************/

/******************Bits Macros************************************/
#define FMI_SR_BSY			16
#define FMI_CR_LOCK			31
#define FMI_CR_SER			1
#define FMI_SR_EOP			0
#define FMI_CR_STRT			16
#define FMI_FLASH_WRITE_HW  (0b01<<8)
#define FMI_CR_PG			0
/*****************************************************************/
#endif /* MCAL_FMI_FMI_PRIV_H_ */
