/*
 * SPI_Private.h
 *
 *  Created on: Aug 27, 2023
 *      Author: ahmed osama
 */

#ifndef MCAL_SPI_SPI_PRIVATE_H_
#define MCAL_SPI_SPI_PRIVATE_H_

#include "../../INC/STD_TYPES.h"

/************************SPI Registers Structure*****************/
typedef struct
{
	volatile uint32_t SPI_CR1		;
	volatile uint32_t SPI_CR2		;
	volatile uint32_t SPI_SR        ;
	volatile uint32_t SPI_DR        ;
	volatile uint32_t SPI_CRCPR     ;
	volatile uint32_t SPI_RXCRCR    ;
	volatile uint32_t SPI_TXCRCR    ;
	volatile uint32_t SPI_I2SCFGR   ;
	volatile uint32_t SPI_I2SPR     ;

}SPI_Registers_t;

/************************Base Addresses*****************/
#define SPI1_BASE		0x40013000
#define SPI2_BASE		0x40003800
#define SPI3_BASE		0x40003C00
#define SPI4_BASE		0x40013400

/***************************SPI Instance************************************/
#define SPI1			((volatile SPI_Registers_t*)SPI1_BASE)
#define SPI2			((volatile SPI_Registers_t*)SPI2_BASE)
#define SPI3			((volatile SPI_Registers_t*)SPI3_BASE)
#define SPI4			((volatile SPI_Registers_t*)SPI4_BASE)

#endif /* MCAL_SPI_SPI_PRIVATE_H_ */
