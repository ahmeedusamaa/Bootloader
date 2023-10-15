/*
 * GPIO_Program.c
 *
 *  Created on: Aug 9, 2023
 *      Author: adham
 */

#include "../../INC/Macros.h"
#include "GPIO_Interface.h"


/**================================================================
 * @Fn    		: MCAL_GPIO_Init
 * @brief 		: Function used to initialize a GPIO pin as ip/op/analog/alternative
 * @param [in] 	: Port base address - configurations
 * @param [out] 	: none
 * @retval 		: none
 * Note			: remember that according to our UQFN48 package we only have ports : A-B-C
 *===================================================================*/
void MCAL_GPIOx_Init(GPIOx_Registers_t *GPIOx,GPIOx_Config_t *Config)
{
	if(Config->GPIO_PIN_MODE == GPIO_INPUT_PUP || Config->GPIO_PIN_MODE == GPIO_INPUT_PDWN || Config->GPIO_PIN_MODE == GPIO_INPUT_FLOAT )
	{
		GPIOx->GPIOx_MODER &= ~( 3<<( (Config->GPIO_PIN_NUMBER)<<1 ) );
		switch(Config->GPIO_PIN_MODE)
		{
		case GPIO_INPUT_FLOAT :
			GPIOx->GPIOx_PUPDR &= ~( 3<< ( (Config->GPIO_PIN_NUMBER)<<1 ) );
			break ;
		case GPIO_INPUT_PUP :
			SET_BIT(GPIOx->GPIOx_PUPDR,(  (Config->GPIO_PIN_NUMBER) <<1 ) );
			CLR_BIT(GPIOx->GPIOx_PUPDR,( ( (Config->GPIO_PIN_NUMBER) <<1 )+1) );
			break ;
		case GPIO_INPUT_PDWN :
			CLR_BIT(GPIOx->GPIOx_PUPDR,( (Config->GPIO_PIN_NUMBER)<<1) );
			SET_BIT(GPIOx->GPIOx_PUPDR,( ( (Config->GPIO_PIN_NUMBER) <<1 )+1) );

		}
	}
	else if(Config->GPIO_PIN_MODE == GPIO_OUT_OD || Config->GPIO_PIN_MODE == GPIO_OUT_PP )
	{

		SET_BIT(GPIOx->GPIOx_MODER,( (Config->GPIO_PIN_NUMBER)<<1) );
		CLR_BIT(GPIOx->GPIOx_MODER,( ( (Config->GPIO_PIN_NUMBER) <<1 )+1) );
		switch(Config->GPIO_PIN_MODE)
		{
		case GPIO_OUT_PP :
			CLR_BIT(GPIOx->GPIOx_OTYPER,Config->GPIO_PIN_NUMBER);
			break ;
		case GPIO_OUT_OD :
			SET_BIT(GPIOx->GPIOx_OTYPER,Config->GPIO_PIN_NUMBER);
			break ;

		}
		switch(Config->GPIO_PIN_OUT_SPEED)
		{

		case GPIO_OUT_SPEED_LOW :
			CLR_BIT(GPIOx->GPIOx_OSPEEDR,(Config->GPIO_PIN_NUMBER<<1));
			CLR_BIT(GPIOx->GPIOx_OSPEEDR,((Config->GPIO_PIN_NUMBER<<1)+1));
			break;
		case GPIO_OUT_SPEED_MEDIUM :
			SET_BIT(GPIOx->GPIOx_OSPEEDR,(Config->GPIO_PIN_NUMBER<<1));
			CLR_BIT(GPIOx->GPIOx_OSPEEDR,((Config->GPIO_PIN_NUMBER<<1)+1));
			break;
		case GPIO_OUT_SPEED_HIGH :
			CLR_BIT(GPIOx->GPIOx_OSPEEDR,(Config->GPIO_PIN_NUMBER<<1));
			SET_BIT(GPIOx->GPIOx_OSPEEDR,((Config->GPIO_PIN_NUMBER<<1)+1));
			break;
		case GPIO_OUT_SPEED_VERY_HIGH :
			SET_BIT(GPIOx->GPIOx_OSPEEDR,(Config->GPIO_PIN_NUMBER<<1));
			SET_BIT(GPIOx->GPIOx_OSPEEDR,((Config->GPIO_PIN_NUMBER<<1)+1));
			break;

		}
	}
	else if(Config->GPIO_PIN_MODE == AFIO_OUT_OD || Config->GPIO_PIN_MODE == AFIO_OUT_PP || Config->GPIO_PIN_MODE == AFIO_INPUT )
	{
		CLR_BIT(GPIOx->GPIOx_MODER,( (Config->GPIO_PIN_NUMBER)<<1) );
		SET_BIT(GPIOx->GPIOx_MODER,( ( (Config->GPIO_PIN_NUMBER) <<1 )+1) );
		if(Config->GPIO_PIN_MODE == AFIO_INPUT)
		{
			GPIOx->GPIOx_PUPDR &= ~( 3<< ( (Config->GPIO_PIN_NUMBER)<<1 ) );
		}
		else if(Config->GPIO_PIN_MODE == AFIO_OUT_OD || Config->GPIO_PIN_MODE == AFIO_OUT_PP)
		{
			switch(Config->GPIO_PIN_MODE)
			{
			case AFIO_OUT_PP :
				CLR_BIT(GPIOx->GPIOx_OTYPER,Config->GPIO_PIN_NUMBER);
				break ;
			case AFIO_OUT_OD :
				SET_BIT(GPIOx->GPIOx_OTYPER,Config->GPIO_PIN_NUMBER);
				break ;
			}
		}

		if(Config->GPIO_PIN_NUMBER >=0 && Config->GPIO_PIN_NUMBER <8)
		{
			GPIOx->GPIOx_AFRL |= (Config->AFIO_SELECT<<(Config->GPIO_PIN_NUMBER * 4));
		}
		else
		{
			GPIOx->GPIOx_AFRH |= (uint32_t)(Config->AFIO_SELECT<<(Config->GPIO_PIN_NUMBER % 8)*4);
		}
		switch(Config->GPIO_PIN_OUT_SPEED)
		{

		case GPIO_OUT_SPEED_LOW :
			CLR_BIT(GPIOx->GPIOx_OSPEEDR,(Config->GPIO_PIN_NUMBER<<1));
			CLR_BIT(GPIOx->GPIOx_OSPEEDR,((Config->GPIO_PIN_NUMBER<<1)+1));
			break;
		case GPIO_OUT_SPEED_MEDIUM :
			SET_BIT(GPIOx->GPIOx_OSPEEDR,(Config->GPIO_PIN_NUMBER<<1));
			CLR_BIT(GPIOx->GPIOx_OSPEEDR,((Config->GPIO_PIN_NUMBER<<1)+1));
			break;
		case GPIO_OUT_SPEED_HIGH :
			CLR_BIT(GPIOx->GPIOx_OSPEEDR,(Config->GPIO_PIN_NUMBER<<1));
			SET_BIT(GPIOx->GPIOx_OSPEEDR,((Config->GPIO_PIN_NUMBER<<1)+1));
			break;
		case GPIO_OUT_SPEED_VERY_HIGH :
			SET_BIT(GPIOx->GPIOx_OSPEEDR,(Config->GPIO_PIN_NUMBER<<1));
			SET_BIT(GPIOx->GPIOx_OSPEEDR,((Config->GPIO_PIN_NUMBER<<1)+1));
			break;

		}
	}

}
/**================================================================
 * @Fn    		: MCAL_GPIO_Pin_Write
 * @brief 		: Function used to write a specific value @ref:PIN_VALUE on a pin
 * @param [in] 	: Port base address - Pin number - Value
 * @param [out] 	: none
 * @retval 		: none
 * Note			: remember that according to our UQFN48 package we only have ports : A-B-C
 *===================================================================*/
void MCAL_GPIOx_Pin_Write(GPIOx_Registers_t *GPIOx , uint8_t Pin_Number , uint8_t value)
{

	if(value == PIN_HIGH)
	{
		SET_BIT(GPIOx->GPIOx_ODR , Pin_Number );
	}
	else if(value == PIN_LOW)
	{
		CLR_BIT(GPIOx->GPIOx_ODR , Pin_Number );
	}
}
/**================================================================
 * @Fn    		: MCAL_GPIO_Pin_Read
 * @brief 		: Function used to read a pin value
 * @param [in] 	: Port base address  - pin number
 * @param [out] 	: pin_value
 * @retval 		: @ref:PIN_VALUE
 * Note			: remember that according to our UQFN48 package we only have ports : A-B-C
 *===================================================================*/
uint8_t MCAL_GPIOx_Pin_Read(GPIOx_Registers_t *GPIOx , uint8_t Pin_Number)
{
	if(GET_BIT(GPIOx->GPIOx_IDR,Pin_Number)==1)
		return PIN_HIGH ;
	else
		return PIN_LOW ;
}

void MCAL_GPIOx_Port_Write(GPIOx_Registers_t *GPIOx,uint16_t value)
{
	GPIOx->GPIOx_ODR = value ;
}

void MCAL_GPIOx_Pin_Toggle(GPIOx_Registers_t *GPIOx , uint8_t Pin_Number)
{
	TOGGLE_BIT(GPIOx->GPIOx_ODR,Pin_Number);
}
