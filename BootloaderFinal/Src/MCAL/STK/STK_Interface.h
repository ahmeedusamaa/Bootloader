/*
 * STK_Interface.h
 *
 *  Created on: Sep 10, 2023
 *      Author: adham
 */

#ifndef MCAL_STK_STK_INTERFACE_H_
#define MCAL_STK_STK_INTERFACE_H_
/*************************************File Includes*******************************************/
#include"../../INC/Macros.h"
#include"../../INC/STD_TYPES.h"
#include"STK_Config.h"
#include"STK_Private.h"
/*********************************************************************************************/


/*************************************APIs Prototype******************************************/
void MCAL_STK_Init(void);
void MCAL_STK_Start_Timer(uint32_t LoadValue);
void MCAL_STK_Stop_Timer(void);
void MCAL_STK_BusyWait(uint32_t Ticks); //Synchronous --> Polling
void MCAL_STK_Dealy_us(uint32_t Time);
void MCAL_STK_Dealy_ms(uint32_t Time);
void MCAL_STK_Set_Interval_Periodic(uint32_t Ticks , void(*callBack)(void)); //interrupt timing (repeat)
void MCAL_STK_Set_Interval_Single(uint32_t Ticks , void(*callBack)(void)); //interrupt timing (one time)
uint32_t MCAL_STK_Get_ElapsedTime(void);
uint32_t MCAL_STK_Get_RemainingTime(void);
void MCAL_STK_StopInterval(void);
/*********************************************************************************************/

#endif /* MCAL_STK_STK_INTERFACE_H_ */
