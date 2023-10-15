/*
 * TFT_Interface.h
 *
 *  Created on: Sep 10, 2023
 *      Author: Mohamed Sayed
 */

#ifndef HAL_TFT_TFT_INTERFACE_H_
#define HAL_TFT_TFT_INTERFACE_H_
#include "TFT_Config.h"
#include "../../INC/STD_TYPES.h"
#include "../../MCAL/SPI/SPI_Interface.h"
void HAL_TFT_SPI_voidInit (void);
void HAL_TFT_voidInit (void);
void HAL_TFT_voidSendCommand (uint8_t command);
void HAL_TFT_voidSendData (uint8_t data);
void HAL_TFT_voidShowPhoto ( uint16_t* image);


#endif /* HAL_TFT_TFT_INTERFACE_H_ */
