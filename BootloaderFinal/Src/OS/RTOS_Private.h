/*********************************************************************************************************
 * ********************************************************************************************************
AUTHOR : ADHAM EHAB
MICRO : STM32F401CCU6
DRIVER : OS Module
Version :1.0
********************************************************************************************************
********************************************************************************************************
 */

#ifndef OS_RTOS_PRIVATE_H_
#define OS_RTOS_PRIVATE_H_

 typedef enum{
	 Suspend ,
	 Running
 }Task_State ;

 typedef struct
 {
	 void (*TaskHandler)(void);
	 uint8_t periodicity ;
	 uint8_t firstdelay ;
	 Task_State Tstate ;
 }Task ;

#endif /* OS_RTOS_PRIVATE_H_ */
