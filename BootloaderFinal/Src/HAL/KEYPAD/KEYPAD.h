/*
 * KEYPAD.h
 *
 *  Created on: Jul 7, 2023
 *      Author: adham
 */

#ifndef HAL_KEYPAD_KEYPAD_H_
#define HAL_KEYPAD_KEYPAD_H_
//-----------------------------
//Includes
#include"../../INC/STD_TYPES.h"
#include"../../INC/Macros.h"
#include"../../MCAL/GPIO/GPIO_Interface.h"
#include"../../MCAL/GPIO/GPIO_Private.h"
//-----------------------------

//-----------------------------
#define KEY_NOT_PRESSED 255
//KEYPAD configurations
#define KEYPAD_PORT				GPIOB
#define KEYPAD_ARR_VALUES		{{7,8,9,0},{4,5,6,0},{3,2,1,0},{0,0,0,0}}
#define NO_PRESSED_KEY			255

#define ROW_OFFSET				0
#define ROW_NUM					4

#define COL_OFFSET				4
#define COL_NUM					4


enum KEYPAD_PINS {
ROW0 = 0 ,
ROW1 ,
ROW2 ,
ROW3 ,
COL0 ,
COL1 ,
COL2 ,
COL3
};
//-----------------------------


/*======================================================
 * 													   	*
 * 			APIs Supported by "HAL KEYPAD DRIVER"       *
 * 				                                        *
 *======================================================
 */
void HAL_KEYPAD_Init();
uint8_t HAL_KEYPAD_Get_PressedKey();
#endif /* HAL_KEYPAD_KEYPAD_H_ */
