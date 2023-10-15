/*
 * RCC_interface.h
 *
 *  Created on: Aug 8, 2023
 *      Author: Adham Ehab
 */

#ifndef INC_RCC_INTERFACE_H_
#define INC_RCC_INTERFACE_H_

#include "../../INC/STD_TYPES.h"
typedef struct {
	uint8_t  RCC_SYS_CLK 			; //@ref : RCC_SYS_CLK_SELECT
	uint8_t  RCC_HSE_MODE 			; //@ref : HSE_MODE_SELECT
	uint8_t  RCC_PERIPHERAL			; //@ref : PERIPHERAL_SELECT
	uint8_t  RCC_BUS_SELECT  		; //@ref : BUS_SELECT
	uint8_t  RCC_PLL_IN_DIV_FACTOR	; //@ref : PLL_IN_DIV_FACT_SELECT
	uint8_t  RCC_PLL_OUT_DIV_FACTOR	; //@ref : PLL_OUT_DIV_FACT_SELECT
	uint16_t RCC_PLL_MUL_FACTOR_VCO	; //@ref : PLL_MUL_FACT_SELECT
	uint8_t	 RCC_PLL_SRC			; //@ref : PLL_SRC_SELECT

}RCC_Config_t;

/****************reference Macros*****************************/
//@ref : RCC_SYS_CLK_SELECT
#define HSI				0
#define HSE				1
#define PLL				2
#define PLLI2S			3

//@ref : HSE_MODE_SELECT
#define HSE_MODE_RC		0
#define HSE_MODE_BYPASS	1

//@ref : PERIPHERAL_SELECT
#define	GPIOA_PERIPHERAL			0
#define GPIOB_PERIPHERAL			1
#define	GPIOC_PERIPHERAL			2
#define SYSCFG_PERIPHERAL			14
#define USART1_PERIPHERAL			4
#define USART6_PERIPHERAL			5
#define USART2_PERIPHERAL			17
#define	SPI1_PERIPHERAL				12
#define	SPI2_PERIPHERAL				14
#define SPI3_PERIPHERAL				15
#define FMI_PERIPHERAL				15

//@ref : BUS_SELECT
#define AHB1_BUS		0
#define AHB2_BUS		1
#define APB1_BUS		2
#define APB2_BUS		3
#define AHB1LP_BUS		4

//@ref : PLL_IN_DIV_FACT_SELECT
#define PLL_IN_DIV_FACT_2    (uint8_t)2
#define PLL_IN_DIV_FACT_3    (uint8_t)3
#define PLL_IN_DIV_FACT_4    (uint8_t)4
#define PLL_IN_DIV_FACT_5    (uint8_t)5
#define PLL_IN_DIV_FACT_6    (uint8_t)6
#define PLL_IN_DIV_FACT_7    (uint8_t)7
#define PLL_IN_DIV_FACT_8    (uint8_t)8
#define PLL_IN_DIV_FACT_9    (uint8_t)9
#define PLL_IN_DIV_FACT_10   (uint8_t)10
#define PLL_IN_DIV_FACT_11   (uint8_t)11
#define PLL_IN_DIV_FACT_12   (uint8_t)12
#define PLL_IN_DIV_FACT_13   (uint8_t)13
#define PLL_IN_DIV_FACT_14   (uint8_t)14
#define PLL_IN_DIV_FACT_15   (uint8_t)15
#define PLL_IN_DIV_FACT_16   (uint8_t)16
#define PLL_IN_DIV_FACT_17   (uint8_t)17
#define PLL_IN_DIV_FACT_18   (uint8_t)18
#define PLL_IN_DIV_FACT_19   (uint8_t)19
#define PLL_IN_DIV_FACT_20   (uint8_t)20
#define PLL_IN_DIV_FACT_21   (uint8_t)21
#define PLL_IN_DIV_FACT_22   (uint8_t)22
#define PLL_IN_DIV_FACT_23   (uint8_t)23
#define PLL_IN_DIV_FACT_24   (uint8_t)24
#define PLL_IN_DIV_FACT_25   (uint8_t)25
#define PLL_IN_DIV_FACT_26   (uint8_t)26
#define PLL_IN_DIV_FACT_27   (uint8_t)27
#define PLL_IN_DIV_FACT_28   (uint8_t)28
#define PLL_IN_DIV_FACT_29   (uint8_t)29
#define PLL_IN_DIV_FACT_30   (uint8_t)30
#define PLL_IN_DIV_FACT_31   (uint8_t)31
#define PLL_IN_DIV_FACT_32   (uint8_t)32
#define PLL_IN_DIV_FACT_33   (uint8_t)33
#define PLL_IN_DIV_FACT_34   (uint8_t)34
#define PLL_IN_DIV_FACT_35   (uint8_t)35
#define PLL_IN_DIV_FACT_36   (uint8_t)36
#define PLL_IN_DIV_FACT_37   (uint8_t)37
#define PLL_IN_DIV_FACT_38   (uint8_t)38
#define PLL_IN_DIV_FACT_39   (uint8_t)39
#define PLL_IN_DIV_FACT_40   (uint8_t)40
#define PLL_IN_DIV_FACT_41   (uint8_t)41
#define PLL_IN_DIV_FACT_42   (uint8_t)42
#define PLL_IN_DIV_FACT_43   (uint8_t)43
#define PLL_IN_DIV_FACT_44   (uint8_t)44
#define PLL_IN_DIV_FACT_45   (uint8_t)45
#define PLL_IN_DIV_FACT_46   (uint8_t)46
#define PLL_IN_DIV_FACT_47   (uint8_t)47
#define PLL_IN_DIV_FACT_48   (uint8_t)48
#define PLL_IN_DIV_FACT_49   (uint8_t)49
#define PLL_IN_DIV_FACT_50   (uint8_t)50
#define PLL_IN_DIV_FACT_51   (uint8_t)51
#define PLL_IN_DIV_FACT_52   (uint8_t)52
#define PLL_IN_DIV_FACT_53   (uint8_t)53
#define PLL_IN_DIV_FACT_54   (uint8_t)54
#define PLL_IN_DIV_FACT_55   (uint8_t)55
#define PLL_IN_DIV_FACT_56   (uint8_t)56
#define PLL_IN_DIV_FACT_57   (uint8_t)57
#define PLL_IN_DIV_FACT_58   (uint8_t)58
#define PLL_IN_DIV_FACT_59   (uint8_t)59
#define PLL_IN_DIV_FACT_60   (uint8_t)60
#define PLL_IN_DIV_FACT_61   (uint8_t)61
#define PLL_IN_DIV_FACT_62   (uint8_t)62
#define PLL_IN_DIV_FACT_63   (uint8_t)63

//@ref : PLL_OUT_DIV_FACT_SELECT
#define PLL_OUT_DIV_FACT_2		(uint8_t)0
#define PLL_OUT_DIV_FACT_4		(uint8_t)1
#define PLL_OUT_DIV_FACT_6		(uint8_t)2
#define PLL_OUT_DIV_FACT_8		(uint8_t)3

//@ref : PLL_MUL_FACT_SELECT
#define PLL_MUL_FACT_432_VCO	(uint16_t)432

//@ref : PLL_SRC_SELECT
#define PLL_SRC_HSI			0
#define PLL_SRC_HSE			1
/***************************RCC APIs*****************************/
void MCAL_RCC_voidInit(RCC_Config_t *config);
void MCAL_RCC_voidPeripheral_EN(uint8_t Peripheral , uint8_t Bus);
void MCAL_RCC_voidPeripheral_DIS(uint8_t Peripheral , uint8_t Bus);
/*~*~*~*~*~*~*~*~*~*~*~*~*~~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*/
uint32_t MCALL_RCC_GetPCLK1Freq(void); //FOR APB1 BUS
uint32_t MCALL_RCC_GetPCLK2Freq(void); //FOR APB2 BUS
uint32_t MCALL_RCC_GetHCLKFreq(void) ; //FOR AHB BUS -> SYSCLK/prescaller
uint32_t MCALL_RCC_GetSYSCLKFreq(void);// HSI 16mhz By Default
/*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*/


/*****************************************************************/


#endif /* INC_RCC_INTERFACE_H_ */
