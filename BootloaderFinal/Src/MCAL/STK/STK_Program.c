/*
 * STK_Program.c
 *
 *  Created on: Sep 10, 2023
 *      Author: adham
 */

/*************************************File Includes*******************************************/
#include"STK_Interface.h"
#include"STK_Config.h"
/*********************************************************************************************/

/*************************************Global Variables****************************************/
static void (*GL_CallBack)(void) = NULL ;
static uint8_t	GL_PeridoicFlag = 0 ;
/*********************************************************************************************/

/************************************APIs Implementation**************************************/
void MCAL_STK_Init(void)
{
	/*1-Clock Source Selection*/
	if(STK_CLK_SRC == STK_AHB)
	{
		SET_BIT(STK->STK_CTRL,CTRL_CLKSOURCE);
	}
	else
	{
		//AHB_DIV8 By Default
		/*Nothing*/
	}
	/*2-Interrupt State*/
	if(STK_IRQ_STATE == STK_IRQ_EN)
	{
		SET_BIT(STK->STK_CTRL,CTRL_TICKINT);
	}
	else
	{
		//IRQ Disable by default
		/*Nothing*/
	}
}


void MCAL_STK_BusyWait(uint32_t Ticks)
{
	/*1-Reset the timer Value Register*/
	STK->STK_VAL = 0 ;
	/*2-Load the Value in the Value Register*/
	STK->STK_LOAD = Ticks ;
	/*3-Start The timer*/
	SET_BIT(STK->STK_CTRL,CTRL_ENABLE);
	/*4-Wait until down flow*/
	while(!GET_BIT(STK->STK_CTRL,CTRL_COUNTFLAG));
	/*5-Stop the timer*/
	CLR_BIT(STK->STK_CTRL,CTRL_ENABLE);
}

void MCAL_STK_Dealy_us(uint32_t Time)
{
	uint32_t NumberOfTicks = Time*2 ;
	MCAL_STK_BusyWait(NumberOfTicks) ;
}
void MCAL_STK_Dealy_ms(uint32_t Time)
{
	uint32_t NumberOfTicks = Time*2000 ;
	MCAL_STK_BusyWait(NumberOfTicks) ;
}
void MCAL_STK_Set_Interval_Periodic(uint32_t Ticks , void(*callBack)(void))
{
	/*1-Set Call back function*/
	GL_CallBack = callBack ;
	/*2-Reset the timer Value Register*/
	STK->STK_VAL = 0 ;
	/*3-Load the Value in the Value Register*/
	STK->STK_LOAD = Ticks ;
	/*4-Start The timer*/
	SET_BIT(STK->STK_CTRL,CTRL_ENABLE);
	/*5-Set the Periodic Flag */
	GL_PeridoicFlag = 1 ;
}
void MCAL_STK_Set_Interval_Single(uint32_t Ticks , void(*callBack)(void))
{
	/*1-Set Call back function*/
	GL_CallBack = callBack ;
	/*2-Reset the timer Value Register*/
	STK->STK_VAL = 0 ;
	/*3-Load the Value in the Value Register*/
	STK->STK_LOAD = Ticks ;
	/*4-Start The timer*/
	SET_BIT(STK->STK_CTRL,CTRL_ENABLE);
	/*5-Set the Periodic Flag */
	GL_PeridoicFlag = 0 ;
}
uint32_t MCAL_STK_Get_ElapsedTime(void)
{
	//3ada wa2t 2ad eh
	return (STK->STK_LOAD - STK->STK_VAL);

}
uint32_t MCAL_STK_Get_RemainingTime(void)
{
	//Fadely wa2t 2ad eh
	return STK->STK_VAL;
}
void MCAL_STK_StopInterval(void)
{
	/*Stop SYSTK*/
	CLR_BIT(STK->STK_CTRL,CTRL_ENABLE);
	/*Reset the Value Register*/
	STK->STK_VAL = 0 ;
}
/*********************************************************************************************/

/*******************************************IRQ Handler***************************************/
void SysTick_Handler(void)
{
	if(GL_CallBack != NULL)
	{
		GL_CallBack();
	}
	if(GL_PeridoicFlag !=1)
	{
		/*Stop the timer*/
		CLR_BIT(STK->STK_CTRL,CTRL_ENABLE);
	}
}
/*********************************************************************************************/
