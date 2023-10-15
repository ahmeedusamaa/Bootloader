/*********************************************************************************************************
 * ********************************************************************************************************
AUTHOR  : ADHAM EHAB
MICRO   : STM32F401CCU6
LAYER   : MCAL
DRIVER  : NVIC_Driver
File    : PROGRAM File
Version :1.0
********************************************************************************************************
*********************************************************/

/*************Includes**********************************/
#include "NVIC_Private.h"
#include "NVIC_Interface.h"
/******************************************************/


/***************************Global Variables Section***********************/
uint8_t Global_uint8GroupModeSelection ;


/***********APIs Implementation************************/

/**================================================================
* @Fn    		: MCAL_NVIC_EnIRQ
* @brief 		: This function used to enable the IRQ in the NVIC Peripheral
* @param [in] 	: Interrupt ID according to IVT in Data Sheet --->@ref:IRQn_t
* @param [out] 	: Function State [STATUS_SUCCESS , STATUS_ERROR]
* Note			: remember that according to our UQFN48 package we only have 52 maskable interrupt channels
*===================================================================*/
ReturnStatus MCAL_NVIC_EnIRQ(IRQn_t Interrupt_ID)
{
	if(IRQ_IS_VALID(Interrupt_ID))
	{
		uint8_t RegNumber = Interrupt_ID/32 ;
		uint8_t BitNumber = Interrupt_ID%32 ;
		NVIC->NVIC_ISER[RegNumber] |= (1<<BitNumber);
		return STATUS_SUCCESS;
	}
	else
	{
		return STATUS_ERROR;
	}
}

/**================================================================
* @Fn    		: MCAL_NVIC_DisIRQ
* @brief 		: This function used to Disable the IRQ in the NVIC Peripheral
* @param [in] 	: Interrupt ID according to IVT in Data Sheet --->@ref:IRQn_t
* @param [out] 	: Function State [STATUS_SUCCESS , STATUS_ERROR]
* Note			: remember that according to our UQFN48 package we only have 52 maskable interrupt channels
*===================================================================*/
ReturnStatus MCAL_NVIC_DisIRQ(IRQn_t Interrupt_ID)
{
	if(IRQ_IS_VALID(Interrupt_ID))
	{
		uint8_t RegNumber = Interrupt_ID/32 ;
		uint8_t BitNumber = Interrupt_ID%32 ;
		NVIC->NVIC_ICER[RegNumber] |= (1<<BitNumber);
		return STATUS_SUCCESS;
	}
	else
	{
		return STATUS_ERROR;
	}
}

/**================================================================
* @Fn    		: MCAL_NVIC_Set_Pending
* @brief 		: This function used to set IRQ pending in the NVIC Peripheral
* @param [in] 	: Interrupt ID according to IVT in Data Sheet --->@ref:IRQn_t
* @param [out] 	: Function State [STATUS_SUCCESS , STATUS_ERROR]
* Note			: remember that according to our UQFN48 package we only have 52 maskable interrupt channels
*===================================================================*/
ReturnStatus MCAL_NVIC_Set_Pending(IRQn_t Interrupt_ID)
{
	if(IRQ_IS_VALID(Interrupt_ID))
	{
		uint8_t RegNumber = Interrupt_ID/32 ;
		uint8_t BitNumber = Interrupt_ID%32 ;
		NVIC->NVIC_ISPR[RegNumber] |= (1<<BitNumber);
		return STATUS_SUCCESS;
	}
	else
	{
		return STATUS_ERROR;
	}
}

/**================================================================
* @Fn    		: MCAL_NVIC_Clr_Pending
* @brief 		: This function used to clear IRQ pending in the NVIC Peripheral
* @param [in] 	: Interrupt ID according to IVT in Data Sheet --->@ref:IRQn_t
* @param [out] 	: Function State [STATUS_SUCCESS , STATUS_ERROR]
* Note			: remember that according to our UQFN48 package we only have 52 maskable interrupt channels
*===================================================================*/
ReturnStatus MCAL_NVIC_Clr_Pending(IRQn_t Interrupt_ID)
{
	if(IRQ_IS_VALID(Interrupt_ID))
	{
		uint8_t RegNumber = Interrupt_ID/32 ;
		uint8_t BitNumber = Interrupt_ID%32 ;
		NVIC->NVIC_ICPR[RegNumber] |= (1<<BitNumber);
		return STATUS_SUCCESS;
	}
	else
	{
		return STATUS_ERROR;
	}
}

/**================================================================
* @Fn    		: MCAL_NVIC_Is_Active
* @brief 		: This function used to read the state of a given IRQ_ID
* @param [in] 	: Interrupt ID according to IVT in Data Sheet --->@ref:IRQn_t
* @param [out] 	: Function State [IRQ_ACTIVE , IRQ_NOT_ACTIVE , IRQ_INVALID]
* Note			: remember that according to our UQFN48 package we only have 52 maskable interrupt channels
*===================================================================*/
IRQ_State_t MCAL_NVIC_Is_Active(IRQn_t Interrupt_ID)
{
	if(IRQ_IS_VALID(Interrupt_ID))
		{
			uint8_t RegNumber = Interrupt_ID/32 ;
			uint8_t BitNumber = Interrupt_ID%32 ;
			if(GET_BIT(NVIC->NVIC_IABR[RegNumber] ,BitNumber) == 1)
			{
				return IRQ_ACTIVE;
			}
			else
				return IRQ_NOT_ACTIVE;

		}
	else
		return IRQ_INVALID;
}

/**================================================================
* @Fn    		: MCAL_NVIC_Set_GroupMode
* @brief 		: This function used to configure the SCB_AIRC register to select the number of groups and sub groups
* @param [in] 	: Group Mode selection  --->@ref:Priority_GroupsMode_t
* @param [out] 	: Function State [STATUS_SUCCESS , STATUS_ERROR]
* Note			: remember that according to our UQFN48 package we only have 52 maskable interrupt channels
*===================================================================*/
ReturnStatus MCAL_NVIC_Set_GroupMode(Priority_GroupsMode_t GroupMode)
{
	if(GroupMode>=PRIRORITY_16GROUP || GroupMode<=PRIORITY_16SUB )
	{
		Global_uint8GroupModeSelection = GroupMode ;
		SCB_AIRCR = VECTKEY | (GroupMode<<8);
		return STATUS_SUCCESS ;
	}
	else
		return STATUS_ERROR ;

}

/**================================================================
* @Fn    		: MCAL_NVIC_Set_InterruptPriority
* @brief 		: This function used to configure the priority of a given peripheral
* @param [in] 	: IRQn , group , subGroup
* @param [out] 	: Function State [STATUS_SUCCESS , STATUS_ERROR]
* Note			: remember that according to our UQFN48 package we only have 52 maskable interrupt channels
*===================================================================*/
ReturnStatus MCAL_NVIC_Set_InterruptPriority(IRQn_t Interrupt_ID ,Priority_Groups_t group , Priority_Sub_Groups_t subGroup )
{
	if(IRQ_IS_VALID(Interrupt_ID) && (group>=NVIC_PRI_GROUP_0 || group>=NVIC_PRI_GROUP_15 ) && (subGroup>=NVIC_PRI_SUB_GROUP_0 ||subGroup>=NVIC_PRI_SUB_GROUP_15))
	{
		switch(Global_uint8GroupModeSelection)
		{
		case PRIRORITY_16GROUP :
			NVIC->NVIC_IPR[Interrupt_ID] |= (group<<4);break ;
		case PRIORITY_8GROUP_2SUB :
			NVIC->NVIC_IPR[Interrupt_ID] |= (group<<5) | (subGroup<<4); break ;
		case PRIORITY_4GROUP_4SUB  :
			NVIC->NVIC_IPR[Interrupt_ID] |= (group<<6) | (subGroup<<4); break ;
		case PRIORITY_2GROUP_8SUB  :
			NVIC->NVIC_IPR[Interrupt_ID] |= (group<<7) | (subGroup<<4); break ;
		case PRIORITY_16SUB  :
			NVIC->NVIC_IPR[Interrupt_ID] |=  (subGroup<<4); break ;
		default :
			return STATUS_ERROR;
		}
		return STATUS_SUCCESS ;
	}
	else
	{
		STATUS_ERROR ;
	}
}
/**************************************************************************************/
