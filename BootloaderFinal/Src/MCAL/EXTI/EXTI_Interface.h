/*
 * EXTI_Interface.h
 *
 *  Created on: Aug 19, 2023
 *      Author: Adham Ehab
 */

#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

/********************Includes********************/
#include"../../INC/STD_TYPES.h"
#include"EXTI_Config.h"


/********************Reference Configurations********************/
typedef enum
{
	EXTI_LINE_0 = 0 ,
	EXTI_LINE_1 	,
	EXTI_LINE_2 	,
	EXTI_LINE_3 	,
	EXTI_LINE_4 	,
	EXTI_LINE_5 	,
	EXTI_LINE_6 	,
	EXTI_LINE_7 	,
	EXTI_LINE_8 	,
	EXTI_LINE_9 	,
	EXTI_LINE_10 	,
	EXTI_LINE_11 	,
	EXTI_LINE_12 	,
	EXTI_LINE_13 	,
	EXTI_LINE_14 	,
	EXTI_LINE_15 	,


}EXTI_Line_t;

typedef enum
{
	EXTI_PORTA=0,
	EXTI_PORTB ,
	EXTI_PORTC
}EXTI_Portn_t;

typedef enum
{
	EXTI_RISING_EDGE=0,
	EXTI_FALLING_EDGE ,
	EXTI_ON_CHANGE
}EXTI_Edge_t;

typedef enum
{
	EXTI_DISABLE=0	,
	EXTI_ENABLE
}EXTI_State_t;

/********************Structure CConfiguration********************/
typedef struct
{
	EXTI_Line_t			EXTI_LineSelection;	/*@ref: EXTI_Line_t*/
	EXTI_Portn_t		EXTI_PortSelection; /*@ref: EXTI_Portn_t*/
	EXTI_Edge_t			EXTI_EdgeSelection; /*@ref: EXTI_Edge_t*/
	EXTI_State_t		EXTI_StateSelection; /*@ref: EXTI_State_t*/
	void(*CallBack)(void);
}EXTI_Config_t;

/************************APIs************************/

ReturnStatus MCAL_EXTI_Enable(EXTI_Config_t  *Configuration);
ReturnStatus MCAL_EXTI_Disable(EXTI_Config_t *Configuration);

#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
