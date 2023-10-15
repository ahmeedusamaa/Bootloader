/*
 * RTOS_Program.c
 *
 *  Created on: Aug 21, 2023
 *      Author: adham
 */


 #include "../INC/STD_TYPES.h"
 #include "../MCAL/STK/STK_Interface.h"
 #include "RTOS_INTERFACE.h"
 #include "RTOS_Config.h"
 #include "RTOS_Interface.h"
 #include "RTOS_Private.h"

Task SystemTasks[MAX_NUMBER_TASKS] = {0}; // 20 task      50
uint8_t  Timing [MAX_NUMBER_TASKS];
Task Empty = {0};



 uint8_t RTOS_uint8_tCreateTask(void(*handler)(void),uint32_t copy_uint32_tperiodicity,uint8_t Copy_uint8_tpriority,uint8_t fdelay)
 {
	 uint8_t Local_ErrorState = 0 ;
	 if (Copy_uint8_tpriority < MAX_NUMBER_TASKS )
	 {
		 // verify priority within limit
		 if (SystemTasks[Copy_uint8_tpriority].TaskHandler == 0 )
		 {
			 SystemTasks[Copy_uint8_tpriority].TaskHandler = handler            ;
			 SystemTasks[Copy_uint8_tpriority].periodicity = copy_uint32_tperiodicity ;
			 Timing     [Copy_uint8_tpriority]             = fdelay ;
			 SystemTasks[Copy_uint8_tpriority].Tstate      = Running ;

		 }
		 else
		 {
			 Local_ErrorState = 2 ;

		 }


	 }
	 else
	 {
		 Local_ErrorState = 1 ;

	 }




 }


void scheduler (void)  // callback function systk
{
	uint8_t Local_Counter = 0 ;
	for ( Local_Counter = 0 ; Local_Counter < MAX_NUMBER_TASKS ;  Local_Counter ++)
	{
		/*IS there is a task ? */
		if (SystemTasks[Local_Counter].TaskHandler != 0 )
		{
			if (SystemTasks[Local_Counter].Tstate == Running)  // 1 -- 0
			{
			 if (Timing[Local_Counter]==0)
			   {
				SystemTasks[Local_Counter].TaskHandler();
				Timing[Local_Counter] =  SystemTasks[Local_Counter].periodicity ;   // 10 => 9 => 8 - 7 -6- 5 -4 3 -2-1
			   }
			   else
		 	   {
				Timing[Local_Counter] -- ;
			   }

		   }
		}
	}
}


uint8_t RTos_DeleteTask(uint8_t Priority)   // RTos_DeleteTask (0)    uint8_t x = RTos_DeleteTask (0)
{
	uint8_t Local_ErrorState = 0;
	if (SystemTasks[Priority].TaskHandler != 0 )
	{
		SystemTasks[Priority] = Empty;
	}
	else
	{
		Local_ErrorState = 1 ;  // there_is no task

	}
	return Local_ErrorState ;

}



uint8_t Rtos_Suspend (uint8_t Priority)
{
		uint8_t Local_ErrorState = 0 ;
	if (SystemTasks[Priority].TaskHandler != 0 )
	{
		SystemTasks[Priority].Tstate = Suspend;
	}
	else
	{
		Local_ErrorState = 1 ;

	}
	return Local_ErrorState ;

}



uint8_t Rtos_ResumeTask (uint8_t priority)
{
	uint8_t Local_ErrorState = 0;
	if (SystemTasks[priority].TaskHandler != 0 )
	{
		SystemTasks[priority].Tstate = Running ;
	}
	else
	{
		Local_ErrorState = 1 ;

	}
	return Local_ErrorState ;

}

void Start_OS(void)
{
	MSTK_vSetInterval_periodic(ticktime,scheduler);
}
