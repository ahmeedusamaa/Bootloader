/*
 * TFT_Program.c
 *
 *  Created on: Sep 10, 2023
 *      Author: Mohamed Sayed
 */

#include "TFT_Interface.h"
#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "../../MCAL/STK/STK_Interface.h"
#include "../../MCAL/SPI/SPI_Interface.h"

void HAL_TFT_SPI_voidInit (void)
{
	SPI_Config_t SPI_Config;
	SPI_Config.Mode=SPI_Mode_Master;
	SPI_Config.Data_frame=SPI_Data_frame_8Bit;
	SPI_Config.Clock_phase=SPI_Clock_phase_second_Edge;
	SPI_Config.Clock_polarity=SPI_Clock_polarity_Idle_1;
	SPI_Config.Communication_Mode=SPI_Communication_2_line;
	SPI_Config.Frame_format=SPI_Frame_format_MSB;
	SPI_Config.Prescaler=SPI_Prescaler_64;
	SPI_Config.NSS=SPI_NSS_Software_Internal_set;

	MCAL_SPI_Init(SPI1, &SPI_Config);
	MCAL_SPI_GPIO_SetPins(SPI1);
}
void HAL_TFT_voidInit (void)
{
	HAL_TFT_SPI_voidInit();
	/*
	Signal creation
	 no reset pin
	 */
	MCAL_GPIOx_Pin_Write (GPIOA,GPIO_PIN_2,PIN_HIGH);
	MCAL_STK_Dealy_us(150);
	MCAL_GPIOx_Pin_Write (GPIOA,GPIO_PIN_2,PIN_LOW);
	MCAL_STK_Dealy_us(2);
	MCAL_GPIOx_Pin_Write (GPIOA,GPIO_PIN_2,PIN_HIGH);
	MCAL_STK_Dealy_us(150);
	MCAL_GPIOx_Pin_Write (GPIOA,GPIO_PIN_2,PIN_LOW);
	MCAL_STK_Dealy_us(150);
	MCAL_GPIOx_Pin_Write (GPIOA,GPIO_PIN_2,PIN_HIGH);
	MCAL_STK_Dealy_us(200000);

	/*
	Sleep out
	 */
	HAL_TFT_voidSendCommand (SLPOUT_MODE);
	MCAL_STK_Dealy_us(200000);
	/*
    RGB 565 mode select
	 */
	HAL_TFT_voidSendCommand(RGB_ADDRESS);
	HAL_TFT_voidSendData (RGB_VALUE);
	/*
    Display command
	 */
	HAL_TFT_voidSendCommand(DISPON);


}
void HAL_TFT_voidSendCommand (uint8_t command)
{
	MCAL_GPIOx_Pin_Write (GPIOA,GPIO_PIN_3,PIN_LOW);// on W/D/C
	MCAL_SPI_SendData (SPI1,command,PollingEnable);
}
void HAL_TFT_voidSendData (uint8_t data)
{
	MCAL_GPIOx_Pin_Write (GPIOA,GPIO_PIN_3,PIN_HIGH);
	MCAL_SPI_SendData (SPI1,data,PollingEnable);
}

void HAL_TFT_voidShowPhoto (uint16_t* image)
{
	/*
 	X -axis Selection
	 */
	HAL_TFT_voidSendCommand (CASET);
	HAL_TFT_voidSendData (0);
	HAL_TFT_voidSendData (0);

	HAL_TFT_voidSendData (0);
	HAL_TFT_voidSendData (SET_X_BORDER);
	/*
 	Y -axis Selection
	 */
	HAL_TFT_voidSendCommand (RASET);
	HAL_TFT_voidSendData (0);
	HAL_TFT_voidSendData (0);

	HAL_TFT_voidSendData (0);
	HAL_TFT_voidSendData (SET_Y_BORDER);

	HAL_TFT_voidSendCommand (ST_DRAWING);
	for (uint16_t counter = 0 ; counter <= sizeof(image)/16 ; counter++)
	{
		HAL_TFT_voidSendData(image[counter]>>8); // to send the MSB first ex. 0x1A40 i have to send 1A first
		HAL_TFT_voidSendData(image[counter]); // for ensure i may write image[counter]&0x00FF;
	}

}
