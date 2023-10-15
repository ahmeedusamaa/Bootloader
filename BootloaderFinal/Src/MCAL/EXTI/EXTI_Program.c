/*
 * EXTI.c
 *
 *  Created on: Aug 19, 2023
 *      Author: Adham Ehab
 */

/********************Includes********************/
#include"../../INC/Macros.h"
#include"../../INC/STD_TYPES.h"
#include"EXTI_Interface.h"
#include"EXTI_Private.h"

/************************Global Variables************************/
void (*ptr[15])(void)={NULL};

/*
	Hardware interrupt selection
	To configure the 23 lines as interrupt sources, use the following procedure:
	• Configure the mask bits of the 23 interrupt lines (EXTI_IMR)
	• Configure the Trigger selection bits of the interrupt lines (EXTI_RTSR and EXTI_FTSR)
	• Configure the enable and mask bits that control the NVIC IRQ channel mapped to the
	external interrupt controller (EXTI) so that an interrupt coming from one of the 23 lines
	can be correctly acknowledged.
 */
ReturnStatus MCAL_EXTI_Enable(EXTI_Config_t  *Configuration)
{
	SET_BIT(EXTI->EXTI_IMR,Configuration->EXTI_LineSelection);
	if(Configuration->EXTI_EdgeSelection==EXTI_RISING_EDGE)
	{
		SET_BIT(EXTI->EXTI_RTSR,Configuration->EXTI_LineSelection);
	}
	else if(Configuration->EXTI_EdgeSelection==EXTI_FALLING_EDGE)
	{
		SET_BIT(EXTI->EXTI_FTSR,Configuration->EXTI_LineSelection);
	}
	else if(Configuration->EXTI_EdgeSelection==EXTI_ON_CHANGE)
	{
		SET_BIT(EXTI->EXTI_RTSR,Configuration->EXTI_LineSelection);
		SET_BIT(EXTI->EXTI_FTSR,Configuration->EXTI_LineSelection);
	}
	else
	{
		return STATUS_ERROR;
	}
	uint8_t SYSCFG_Reg = Configuration->EXTI_LineSelection/4;
	uint8_t bit = Configuration->EXTI_LineSelection%4 ;
	switch(SYSCFG_Reg)
	{
			case 0 :
				SYSCFG_EXTICR1_EXTI0_3(Configuration->EXTI_PortSelection,bit);
				break;
			case 1 :
				SYSCFG_EXTICR2_EXTI4_7(Configuration->EXTI_PortSelection,bit);
				break;
			case 2 :
				SYSCFG_EXTICR3_EXTI8_11(Configuration->EXTI_PortSelection,bit);
				break;
			case 3 :
				SYSCFG_EXTICR4_EXTI12_15(Configuration->EXTI_PortSelection,bit);
				break;
			}
	ptr[Configuration->EXTI_LineSelection] = Configuration->CallBack;

	return STATUS_SUCCESS;
}

ReturnStatus MCAL_EXTI_Disable(EXTI_Config_t *Configuration)
{
	CLR_BIT(EXTI->EXTI_IMR,Configuration->EXTI_LineSelection);
	return STATUS_SUCCESS;

}

void EXTI0_IRQHandler(void)
{

	if(ptr[0] != NULL)
	{
	SET_BIT(EXTI->EXTI_PR,0);
	ptr[0]();
	}
}
void EXTI1_IRQHandler(void)
{

	SET_BIT(EXTI->EXTI_PR,1);
	ptr[1]();
}
