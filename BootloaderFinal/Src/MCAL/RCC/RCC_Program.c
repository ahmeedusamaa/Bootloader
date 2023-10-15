/*
 * RCC.c
 *
 *  Created on: Aug 8, 2023
 *      Author: Adham Ehab
 */

#include "RCC_interface.h"
#include "RCC_Private.h"
#include "../../INC/Macros.h"
/**================================================================
 * @Fn    		: MCAL_RCC_voidInit
 * @brief 		: Initialize the RCC peripheral
 * @param [in] 	: Pointer to the configuration structure
 * @param [out] 	: void
 * @retval 		: none
 * Note			: this function has no prerequisites
 *===================================================================*/
void MCAL_RCC_voidInit(RCC_Config_t *config)
{
	uint8_t	SYS_CLK_MODE ;
	SYS_CLK_MODE = config->RCC_SYS_CLK ;
	if(SYS_CLK_MODE==HSI)
	{
		SET_BIT(RCC->RCC_CR,HSION); // Enable HSI
		while(GET_BIT(RCC->RCC_CR,HSIRDY)==0); // Wait until HSI become stable
		CLR_BIT(RCC->RCC_CFGR,SW0);//Select HSI
		CLR_BIT(RCC->RCC_CFGR,SW1);
	}

	else if(SYS_CLK_MODE==HSE)
	{
		uint8_t HSE_Mode ;
		HSE_Mode = config->RCC_HSE_MODE ;
		if(HSE_Mode==HSE_MODE_RC)
			CLR_BIT(RCC->RCC_CR,HSEBYP); // select RC mode
		else if(HSE_Mode==HSE_MODE_BYPASS)
			SET_BIT(RCC->RCC_CR,HSEBYP); // select bypath mode
		SET_BIT(RCC->RCC_CR,HSEON); // ENABLE HSE
		while(GET_BIT(RCC->RCC_CR,HSERDY)==0);//Wait until the HSE become Stable
		SET_BIT(RCC->RCC_CFGR,SW0);//Select HSE oscillator
		CLR_BIT(RCC->RCC_CFGR,SW1);
	}



	else if(SYS_CLK_MODE==PLL)
	{
		//PLL Configurations
		RCC->RCC_PLLCFGR |= config->RCC_PLL_IN_DIV_FACTOR ;
		RCC->RCC_PLLCFGR |= (config->RCC_PLL_MUL_FACTOR_VCO)<<6 ;
		RCC->RCC_PLLCFGR |= (config->RCC_PLL_OUT_DIV_FACTOR)<<16;
		RCC->RCC_PLLCFGR |= (config->RCC_PLL_SRC)<<22;
		//PLL En
		SET_BIT(RCC->RCC_CR,PLLON);
		while(GET_BIT(RCC->RCC_CR,PLLRDY)==0);//Wait until Main PLL become Stable
	}



	else if(SYS_CLK_MODE==PLLI2S)
	{
		RCC->RCC_PLLCFGR |= config->RCC_PLL_IN_DIV_FACTOR ;
		RCC->RCC_PLLCFGR |= (config->RCC_PLL_SRC)<<22;
		//to be continue
		SET_BIT(RCC->RCC_CR,PLLI2SON);
		while(GET_BIT(RCC->RCC_CR,PLLI2SRDY)==0);//Wait until I2S PLL become Stable
	}

	else {
		//nothing
	}


}
/**================================================================
 * @Fn    		: MCAL_RCC_voidPeripheral_EN
 * @brief 		: Enable the clock for a given peripheral
 * @param [in] 	: Peripheral and bus
 * @param [out] 	: void
 * @retval 		: none
 * Note			: the RCC peripheral must be initialized firist
 *===================================================================*/
void MCAL_RCC_voidPeripheral_EN(uint8_t Peripheral , uint8_t Bus)
{
	switch(Bus)
	{

	case AHB1_BUS : SET_BIT(RCC->RCC_AHB1ENR, Peripheral);
	break ;
	case AHB2_BUS : SET_BIT(RCC->RCC_AHB2ENR, Peripheral);
	break ;
	case APB1_BUS : SET_BIT(RCC->RCC_APB1ENR, Peripheral);
	break ;
	case APB2_BUS : SET_BIT(RCC->RCC_APB2ENR, Peripheral);
	break ;
	case AHB1LP_BUS : SET_BIT(RCC->RCC_AHB1LPENR,Peripheral);
	break;
	}
}
/**================================================================
 * @Fn    		: MCAL_RCC_voidPeripheral_DIS
 * @brief 		: Disable the clock for a given peripheral
 * @param [in] 	: Peripheral and bus
 * @param [out] 	: void
 * @retval 		: none
 * Note			: the RCC peripheral must be initialized firist
 *===================================================================*/
void MCAL_RCC_voidPeripheral_DIS(uint8_t Peripheral , uint8_t Bus)
{
	switch(Bus)
	{

	case AHB1_BUS : SET_BIT(RCC->RCC_AHB1RSTR, Peripheral);
	break ;
	case AHB2_BUS : SET_BIT(RCC->RCC_AHB2RSTR, Peripheral);
	break ;
	case APB1_BUS : SET_BIT(RCC->RCC_APB1RSTR, Peripheral);
	break ;
	case APB2_BUS : SET_BIT(RCC->RCC_APB2RSTR, Peripheral);
	break ;
	}
}


uint32_t MCALL_RCC_GetPCLK1Freq(void)
{
/*
 0xx: AHB clock not divided
100: AHB clock divided by 2
101: AHB clock divided by 4
110: AHB clock divided by 8
111: AHB clock divided by 16
 */
	uint8_t APB1Prescaller[8U]={0,0,0,0,1,2,3,4};
	return MCALL_RCC_GetHCLKFreq()>>APB1Prescaller[(RCC->RCC_CFGR>>10)&0b111]; // >> = divide by 2powerN
}
uint32_t MCALL_RCC_GetPCLK2Freq(void)
{
	/*
0xx: AHB clock not divided
100: AHB clock divided by 2
101: AHB clock divided by 4
110: AHB clock divided by 8
111: AHB clock divided by 16
	 */
	uint8_t APB2Prescaller[8U]={0,0,0,0,1,2,3,4};
	return MCALL_RCC_GetHCLKFreq()>>APB2Prescaller[(RCC->RCC_CFGR>>13)&0b111]; // >> = divide by 2powerN
}
uint32_t MCALL_RCC_GetHCLKFreq(void)
{
/*
0xxx: system clock not divided
1000: system clock divided by 2
1001: system clock divided by 4
1010: system clock divided by 8
1011: system clock divided by 16
1100: system clock divided by 64
1101: system clock divided by 128
1110: system clock divided by 256
1111: system clock divided by 512
*/

uint8_t AHBPrescaller[16U]={0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9};
return MCALL_RCC_GetSYSCLKFreq()>>AHBPrescaller[(RCC->RCC_CFGR>>4)&0xF];
}
uint32_t MCALL_RCC_GetSYSCLKFreq(void)
{
	/*
00: HSI oscillator used as the system clock
01: HSE oscillator used as the system clock
10: PLL used as the system clock
11: not applicable
	 */
	switch((RCC->RCC_CFGR>>2)&0b11)
	{
	case HSI_SELECTED :
		return HSI_CLK;
		break;
	case HSE_SELECTED :
		/*To do */
		break;
	case PLL_SELECTED :
		/*To do */
		break;
	default :
		return HSI_CLK;
	}
}
