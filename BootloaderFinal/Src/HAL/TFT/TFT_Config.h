/*
 * TFT_Cnofig.h
 *
 *  Created on: Sep 10, 2023
 *      Author: Mohamed Sayed
 */

#ifndef HAL_TFT_TFT_CONFIG_H_
#define HAL_TFT_TFT_CONFIG_H_
/*********** Commands Table  *****************/

#define SLPOUT_MODE   0x11
#define DISPON        0x29
#define CASET         0x2A // Coloum address set
#define RASET         0x2B // Row address set
#define RGB_ADDRESS   0x3A
#define ST_DRAWING    0x2C


/************ Data Configuration ************/

#define RGB_VALUE    0x05
#define SET_X_BORDER 127
#define SET_Y_BORDER 159



#endif /* HAL_TFT_TFT_CONFIG_H_ */
