/*
 * GPIO_Private.h
 *
 *  Created on: Aug 9, 2023
 *      Author: adham
 */

#ifndef MCAL_GPIO_GPIO_PRIVATE_H_
#define MCAL_GPIO_GPIO_PRIVATE_H_

#include"../../INC/STD_TYPES.h"

/************************GPIOx Registers Structure*****************/
typedef struct
{
	volatile uint32_t GPIOx_MODER 	;
	volatile uint32_t GPIOx_OTYPER 	;
	volatile uint32_t GPIOx_OSPEEDR	;
	volatile uint32_t GPIOx_PUPDR	;
	volatile uint32_t GPIOx_IDR		;
	volatile uint32_t GPIOx_ODR 	;
	volatile uint32_t GPIOx_BSRR	;
	volatile uint32_t GPIOx_LCKR	;
	volatile uint32_t GPIOx_AFRL	;
	volatile uint32_t GPIOx_AFRH	;
}GPIOx_Registers_t;

/************************GPIO Base Addresses*****************/
#define GPIOA_BASE		0x40020000
#define GPIOB_BASE		0x40020400
#define GPIOC_BASE		0x40020800

/************************GPIO Base Addresses*****************/
#define GPIOA		((GPIOx_Registers_t*)GPIOA_BASE)
#define GPIOB		((GPIOx_Registers_t*)GPIOB_BASE)
#define GPIOC		((GPIOx_Registers_t*)GPIOC_BASE)
/**************************************************************/


#endif /* MCAL_GPIO_GPIO_PRIVATE_H_ */
