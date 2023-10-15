/*
 * RTOS_Interface.h
 *
 *  Created on: Aug 21, 2023
 *      Author: adham
 */

#ifndef OS_RTOS_INTERFACE_H_
#define OS_RTOS_INTERFACE_H_
#include"../INC/STD_TYPES.h"
 uint8_t  RTOS_uint8_tCreateTask(void(*handler)(void),uint32_t copy_u8periodicity,uint8_t Copy_u8priority,uint8_t fdelay);
 void scheduler (void);
 uint8_t RTos_DeleteTask(uint8_t Priority);
 uint8_t Rtos_Suspend (uint8_t Priority);
 uint8_t Rtos_ResumeTask (uint8_t priority);
 void Start_OS(void);


#endif /* OS_RTOS_INTERFACE_H_ */
