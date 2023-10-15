/*********************************************************************************************************
 * ********************************************************************************************************
AUTHOR  : ADHAM EHAB
MICRO   : STM32F401CCU6
LAYER   : MCAL
DRIVER  : NVIC_Driver
File    : Private File
Version :1.0
********************************************************************************************************
*********************************************************/
#ifndef MCAL_NVIC_NVIC_PRIVATE_H_
#define MCAL_NVIC_NVIC_PRIVATE_H_

#include "../../INC/STD_TYPES.h"
/************************NVIC Base Address***********************/
#define NVIC_BASE_ADDRESS	(0xE000E100)
/***************************************************************/
typedef struct {

	volatile uint32_t NVIC_ISER[8] 		;
	volatile uint32_t RESERVED0[24]		;
	volatile uint32_t NVIC_ICER[8]		;
	volatile uint32_t RESERVED1[24]		;
	volatile uint32_t NVIC_ISPR[8]		;
	volatile uint32_t RESERVED2[24]		;
	volatile uint32_t NVIC_ICPR [8]		;
	volatile uint32_t RESERVED3[24]		;
	volatile uint32_t NVIC_IABR[8]		;
	volatile uint32_t RESERVED4[56]		;
	volatile uint8_t NVIC_IPR[240]		;
	volatile uint32_t RESERVED5[580] 	;
	volatile uint32_t NVIC_STIR			;
}NVIC_Registers_t;

/**********************NVIC Instant***********************/
#define NVIC	((volatile NVIC_Registers_t*)NVIC_BASE_ADDRESS)
/**********************************************************/

/************************SCB Base Address*****************/
#define SCB_BASE		(0xE000ED00)
/*********SCB Interrupt Priority Register*****************/
#define SCB_AIRCR	*((volatile uint32_t *)(SCB_BASE+0x0C))
/*********************************************************/
#define VECTKEY			(0x5FA)
/*********************************************************/

/**********************Helping Macros*********************/
#define IRQ_IS_VALID(IRQN)		(((IRQN>=WWDG)&&(IRQN<=ADC))                   || \
								((IRQN>=EXTI9_5)&&(IRQN<=USART2))              || \
							    ((IRQN>=EXTI15_10)&&(IRQN<=EXTI18_OTG_FS_WKUP))|| \
								((IRQN==DMA1_Stream7))	 					   || \
								((IRQN>=SDIO)&&(IRQN<=SPI3_NVIC)) 				   || \
								((IRQN>=DMA2_Stream0)&&(IRQN<=DMA2_Stream4))   || \
								((IRQN>=OTG_FS)&&(IRQN<=I2C3_ER))              || \
								((IRQN==FPU)) 			                       || \
								((IRQN==SPI4_NVIC)))
/* this macro is used to check if the IRQ_ID is within the Vector table or no*/

typedef enum {
	IRQ_NOT_ACTIVE ,
	IRQ_ACTIVE ,
	IRQ_INVALID
}IRQ_State_t;

#endif /* MCAL_NVIC_NVIC_PRIVATE_H_ */
