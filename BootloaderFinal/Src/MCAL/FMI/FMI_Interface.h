/*
 * FMI_Interface.h
 *
 *  Created on: Sep 4, 2023
 *      Author: adham
 */

#ifndef MCAL_FMI_FMI_INTERFACE_H_
#define MCAL_FMI_FMI_INTERFACE_H_
/********************Includes*****************/
#include"../../INC/STD_TYPES.h"
#include"../../INC/Macros.h"
/*********************************************/

/********************Sectors Enum**************/

typedef enum {
	SECTOR0 ,
	SECTOR1 ,
	SECTOR2 ,
	SECTOR3 ,
	SECTOR4 ,
	SECTOR5
}Flash_Memory_Sectors_t;


/***********************************************/
/*******************************************************************
 * 							MCAL APIs							   *
 *******************************************************************/
void MCALFMI_vMassErase(void);
void MCALFMI_vSectorErase(Flash_Memory_Sectors_t A_u8SectorNo);
void MCALFMI_vFlashWrite(uint32_t A_u32Address,uint16_t* A_pu16Data,uint16_t  A_u16Length);

#endif /* MCAL_FMI_FMI_INTERFACE_H_ */
