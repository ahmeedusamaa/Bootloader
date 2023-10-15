/*
 * SCB_Private.h
 *
 *  Created on: Sep 11, 2023
 *      Author: adham
 */

#ifndef MCAL_SCB_SCB_PRIVATE_H_
#define MCAL_SCB_SCB_PRIVATE_H_
/*****************************File Includes**************************************/
#include"../../INC/STD_TYPES.h"
/********************************************************************************/

/*****************************SCB Base Address***********************************/
#define SCB_BASE_ADDRESS		0xE000ED00
/********************************************************************************/

/*****************************Registers Structure********************************/
typedef struct
{
volatile uint32_t CPUID ;
volatile uint32_t ICSR  ;
volatile uint32_t VTOR  ;
volatile uint32_t AIRCR ;
volatile uint32_t SCR   ;
volatile uint32_t CCR   ;
volatile uint32_t SHPR1 ;
volatile uint32_t SHPR2 ;
volatile uint32_t SHPR3 ;
volatile uint32_t SHCSR ;
volatile uint32_t CFSR  ;
volatile uint32_t HFSR  ;
volatile uint32_t MMAR  ;
volatile uint32_t BFAR  ;
volatile uint32_t AFSR  ;
}SCB_Registers_t;

/*****************************Peripheral Instance*********************************/
#define SCB			((volatile SCB_Registers_t*)SCB_BASE_ADDRESS)
/*********************************************************************************/
#endif /* MCAL_SCB_SCB_PRIVATE_H_ */
