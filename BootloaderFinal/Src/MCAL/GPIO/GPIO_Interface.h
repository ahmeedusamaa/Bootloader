/*
 * GPIO_Interface.h
 *
 *  Created on: Aug 9, 2023
 *      Author: adham
 */


#ifndef MCAL_GPIO_GPIO_INTERFACE_H_
#define MCAL_GPIO_GPIO_INTERFACE_H_

#include"../../INC/STD_TYPES.h"
#include"GPIO_Private.h"

/***********************Configuration Structure***************/
typedef struct
{
	uint8_t GPIO_PIN_NUMBER 	; //@ref : GPIO_PIN_NUMBER_SELECT
	uint8_t GPIO_PIN_MODE		; //@ref : GPIO_PIN_MODE_SELECT
	uint8_t AFIO_SELECT			; //@ref : AFIO_MODE_SELECT
	uint8_t GPIO_PIN_OUT_SPEED 	; //@ref : GPIO_PIN_OUT_SPEED_SELECT
}GPIOx_Config_t;

/****************************Reference Macros******************/
//@ref : GPIO_PIN_NUMBER_SELECT
#define GPIO_PIN_0			0
#define GPIO_PIN_1			1
#define GPIO_PIN_2			2
#define GPIO_PIN_3			3
#define GPIO_PIN_4			4
#define GPIO_PIN_5			5
#define GPIO_PIN_6			6
#define GPIO_PIN_7			7
#define GPIO_PIN_8			8
#define GPIO_PIN_9			9
#define GPIO_PIN_10			10
#define GPIO_PIN_11			11
#define GPIO_PIN_12			12
#define GPIO_PIN_13			13
#define GPIO_PIN_14			14
#define GPIO_PIN_15			15


//@ref : GPIO_PIN_MODE_SELECT
#define GPIO_INPUT_ANALOG		0
#define GPIO_INPUT_PUP			1
#define	GPIO_INPUT_PDWN			2
#define GPIO_INPUT_FLOAT		3
#define GPIO_OUT_PP				4
#define GPIO_OUT_OD				5
#define AFIO_INPUT				6
#define AFIO_OUT_PP				7
#define AFIO_OUT_OD				8

//@ref : GPIO_PIN_OUT_SPEED_SELECT
#define GPIO_OUT_SPEED_LOW					0
#define GPIO_OUT_SPEED_MEDIUM				1
#define GPIO_OUT_SPEED_HIGH					2
#define GPIO_OUT_SPEED_VERY_HIGH			3

//@ref : AFIO_MODE_SELECT
#define AFIO_0			0
#define AFIO_1   		1
#define AFIO_2     		2
#define AFIO_3          3
#define AFIO_4          4
#define AFIO_5          5
#define AFIO_6          6
#define AFIO_7          7
#define AFIO_8          8
#define AFIO_9          9
#define AFIO_10         10
#define AFIO_11         11
#define AFIO_12         12
#define AFIO_13         13
#define AFIO_14         14
#define AFIO_15         15

/**********************Helping Macros***************************/
#define PIN_LOW			0ul
#define PIN_HIGH		1ul

/*======================================================
 * 													   *
 * 			APIs Supported by "MCAL GPIO DRIVER"       *
 * 				                                       *
 *======================================================
 */
void MCAL_GPIOx_Init(GPIOx_Registers_t *GPIOx,GPIOx_Config_t *Config);
void MCAL_GPIOx_Pin_Write(GPIOx_Registers_t *GPIOx , uint8_t Pin_Number , uint8_t value);
uint8_t MCAL_GPIOx_Pin_Read(GPIOx_Registers_t *GPIOx , uint8_t Pin_Number);
void MCAL_GPIOx_Port_Write(GPIOx_Registers_t *GPIOx,uint16_t value);
void MCAL_GPIOx_Pin_Toggle(GPIOx_Registers_t *GPIOx , uint8_t Pin_Number);

#endif /* MCAL_GPIO_GPIO_INTERFACE_H_ */
