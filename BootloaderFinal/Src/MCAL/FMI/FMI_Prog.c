/*
 * FMI_Prog.c
 *
 *  Created on: Sep 4, 2023
 *      Author: adham
 */
/*************************INCLUDES********************************/
#include"../../INC/Macros.h"
#include"../../INC/STD_TYPES.h"
#include"FMI_Interface.h"
#include"FMI_Priv.h"
#include"FMI_Config.h"
/*****************************************************************/
/**********************Private APIEs******************************/
static void FMI_vUnclockFlash(void)
{
	FMI->FMI_KEYR = FMI_KEY1 ;
	FMI->FMI_KEYR = FMI_KEY2 ;
}

static void FMI_vWaitBSY(void)
{
		/*Wait if the flash Busy*/
	while(GET_BIT(FMI->FMI_SR,FMI_SR_BSY) == SET);
}
/*****************************************************************/

/*************************APIs Implementation*********************/
void MCALFMI_vMassErase(void)
{
	for(uint8_t local_itr = APP_SECTOR ; local_itr<=SECTOR5 ;local_itr++)
	{
		MCALFMI_vSectorErase(local_itr);
	}

}
/********************************************************************/
void MCALFMI_vSectorErase(Flash_Memory_Sectors_t A_u8SectorNo)
{
	/*1-Wait if the Flash is Busy*/
	FMI_vWaitBSY();
	/*2-Unlock the Flash Registers*/
	if(GET_BIT(FMI->FMI_CR,FMI_CR_LOCK)== SET)
	{
		FMI_vUnclockFlash();
	}
	/*3-Select the Sector Number*/
	FMI->FMI_CR &= ~((0b1111<<3));
	FMI->FMI_CR |= (A_u8SectorNo<<3);
	/*4-Select the Erase Operation*/
	SET_BIT(FMI->FMI_CR,FMI_CR_SER);
	/*5-Start Erasing Operation*/
	SET_BIT(FMI->FMI_CR,FMI_CR_STRT);
	/*6-Wait for erasing to be done*/
	FMI_vWaitBSY();
	/*7-Clear manually the flag bit*/
	SET_BIT(FMI->FMI_SR,FMI_SR_EOP);
	/*8-Disable the Erase Operation*/
	CLR_BIT(FMI->FMI_CR,FMI_CR_SER);
}
/********************************************************************/
void MCALFMI_vFlashWrite(uint32_t A_u32Address,uint16_t* A_pu16Data,uint16_t  A_u16Length)
{
	/*1-Wait for Flash Busy*/
	 FMI_vWaitBSY();
	 /*2-Unlock the Flash Registers*/
	 if(GET_BIT(FMI->FMI_CR,FMI_CR_LOCK)== SET)
	 {
	 	FMI_vUnclockFlash();
	 }
	 /*3-Select the Writing Length*/
	 FMI->FMI_CR &=~((uint32_t)(0b11<<8)) ;
	 FMI->FMI_CR |= FMI_FLASH_WRITE_HW;
	 /*4-Activate Programming Mode (PG bit) */
	 SET_BIT(FMI->FMI_CR,FMI_CR_PG);
	/* 5- Write Data Array on Flash address */
		for(uint16_t local_itr=0; local_itr<A_u16Length; local_itr++)
		{
			*((volatile uint16_t*)A_u32Address) = A_pu16Data[local_itr];
			A_u32Address += 2 ;
			/*6-Wait for Flash Busy*/
			FMI_vWaitBSY();
			/*7-Clear manually the flag bit*/
			SET_BIT(FMI->FMI_SR,FMI_SR_EOP);
		}
	/*8-Deactivate Programming Mode (PG bit) */
	CLR_BIT(FMI->FMI_CR,FMI_CR_PG);
}
/****************************************************************/
