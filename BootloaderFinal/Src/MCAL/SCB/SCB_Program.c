/*
 * SCB_Program.c
 *
 *  Created on: Sep 11, 2023
 *      Author: adham
 */

#include"SCB_Private.h"
#include"SCB_interface.h"

void MCAL_SCB_VTOR_SetValue(uint32_t value)
{
	SCB->VTOR = value ;
}
