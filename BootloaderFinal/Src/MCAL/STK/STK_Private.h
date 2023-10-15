/*
 * STK_Private.h
 *
 *  Created on: Sep 10, 2023
 *      Author: adham
 */
#ifndef MCAL_STK_STK_PRIVATE_H_
#define MCAL_STK_STK_PRIVATE_H_
/*************************************File Includes*******************************************/
#include"../../INC/STD_TYPES.h"
/*********************************************************************************************/

/*************************************STK Base Address****************************************/
#define STK_BASE_ADDRESS			0xE000E010
/*********************************************************************************************/

/************************************STK Registers Struct*************************************/
typedef struct
{
volatile uint32_t STK_CTRL  ;
volatile uint32_t STK_LOAD  ;
volatile uint32_t STK_VAL   ;
volatile uint32_t STK_CALIB ;

}STK_Registers_t;
/*********************************************************************************************/

/*************************************STK Peripheral instance*********************************/
#define STK			((volatile STK_Registers_t*)STK_BASE_ADDRESS)
/*********************************************************************************************/

/***************************************Registers Macros**************************************/
//@1-CTRL
#define CTRL_ENABLE				0
#define CTRL_TICKINT			1
#define CTRL_CLKSOURCE			2
#define CTRL_COUNTFLAG			16


/*********************************************************************************************/

#endif /* MCAL_STK_STK_PRIVATE_H_ */
