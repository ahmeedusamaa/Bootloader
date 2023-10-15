/*
 * SPI_Interface.h
 *
 *  Created on: Aug 27, 2023
 *      Author: ahmed osama
 */

#ifndef MCAL_SPI_SPI_INTERFACE_H_
#define MCAL_SPI_SPI_INTERFACE_H_

#include "../../INC/Macros.h"
#include "SPI_Private.h"
#include "../RCC/RCC_interface.h"
#include "../NVIC/NVIC_Interface.h"
#include "../GPIO/GPIO_Interface.h"


struct S_IRQ_SRC
{
	uint8_t TXE:1;			/*TX buffer empty interrupt*/
	uint8_t RXNE:1;			/*RX buffer empty interrupt*/
	uint8_t Reserved:6;

};

/*******************Configuration Structure*******************/
typedef struct
{
	uint16_t Mode ;								/*specifies Master/Slave selection
												This parameter must be set based on @ref SPI_Mode*/
	uint16_t Communication_Mode ;				/*specifies data directional mode
												This parameter must be set based on @ref SPI_Communication_Mode*/
	uint16_t Data_frame ;						/*specifies Data frame format
												This parameter must be set based on @ref SPI_Data_frame*/
	uint16_t NSS ;								/*specifies NSS
												This parameter must be set based on @ref SPI_Software_slave_management*/
	uint16_t Frame_format ;						/*specifies MSB/LSB  transmitted first
												This parameter must be set based on @ref SPI_Frame_format*/
	uint16_t Prescaler ;						/*specifies Baud rate control
												This parameter must be set based on @ref SPI_Prescaler*/
	uint16_t Clock_polarity ;					/*specifies Clock polarity
												This parameter must be set based on @ref SPI_Clock_polarity*/
	uint16_t Clock_phase ;						/*specifies Clock phase
												This parameter must be set based on @ref SPI_Clock phase*/
	uint16_t IRQ_Enable ;						/*specifies Interrupt Enable
												This parameter must be set based on @ref SPI_IRQ_Enable*/
	void(*CALLBACK)(struct S_IRQ_SRC IRQ_SRC);
}SPI_Config_t;


/*************************Reference Macros*************************/
/****@ref SPI_Mode****/
/*SPI_CR1*/
#define SPI_Mode_Slave								(0)					/*Slave configuration*/
#define SPI_Mode_Master								(1<<2)				/*Master configuration*/

/****@ref SPI_Communication_Mode****/
/*SPI_CR1*/
#define SPI_Communication_2_line					(0) 				/*Transmit and receive(Full duplex)*/
#define SPI_Communication_2_line_RXONLY				(1<<10) 			/*Receive-only mode*/
#define SPI_Communication_1_line_TXONLY				(1<<15) 			/*transmit-only mode*/
#define SPI_Communication_1_line_RXONLY				(1<<15 | 1<<14)	 	/*receive-only mode*/


/****@ref SPI_Data_frame****/
/*SPI_CR1*/
#define SPI_Data_frame_8Bit						      (0)				/*8-bit data frame format is selected*/
#define SPI_Data_frame_16Bit					      (1<<11)			/*16-bit data frame format is selected*/

/********************************************************************************************************************/
/*@ref SPI_Software_slave_management*/
/*SPI_CR1*/
/*Hardware*/
#define SPI_NSS_Hardware_slave	   				      (0)			    /*Software slave management disabled*/
/*SPI_CR2*/
#define SPI_NSS_Hardware_Master_SS_output_disabled	  ~(1<<2)				/*output is disabled in master mode and the cell can work in multimaster configuration*/
#define SPI_NSS_Hardware_Master_SS_output__Enable     (1<<2)			/*output is enabled in master mode and when the cell is enabled. The cell cannot work
																		in a multimaster environment.*/
/*SPI_CR1*/
/*Software*/
#define SPI_NSS_Software_Internal_reset	           	 (1<<9)
#define SPI_NSS_Software_Internal_set	         	 (1<<9 | 1<<8)
/********************************************************************************************************************/

/**@ref SPI_Frame_format**/
/*SPI_CR1*/
#define SPI_Frame_format_MSB					      (0)				/*MSB transmitted first*/
#define SPI_Frame_format_LSB					      (1<<7)			/*LSB transmitted first*/

/***@ref SPI_Baud_rate***/
/*SPI_CR1*/
#define SPI_Prescaler_2							      (0)
#define SPI_Prescaler_4	                              (1<<3)
#define SPI_Prescaler_8                               (2<<3)
#define SPI_Prescaler_16	                          (3<<3)
#define SPI_Prescaler_32	                          (4<<3)
#define SPI_Prescaler_64	                          (5<<3)
#define SPI_Prescaler_128	                          (6<<3)
#define SPI_Prescaler_256	                          (7<<3)

/***@ref SPI_Clock_polarity***/
/*SPI_CR1*/
#define SPI_Clock_polarity_Idle_0				      (0)				/*CK to 0 when idle*/
#define SPI_Clock_polarity_Idle_1				      (1<<1)			/*CK to 1 when idle*/

/***@ref SPI_Clock_phase***/
/*SPI_CR1*/
#define SPI_Clock_phase_first_Edge				      (0)				/*The first clock transition is the first data capture edge*/
#define SPI_Clock_phase_second_Edge 			      (1<<0)			/*The second clock transition is the first data capture edge*/

/***@ref SPI_IRQ_Enable***/
/*SPI_CR2*/
#define SPI_IRQ_Enable_NONE						      (0)
#define SPI_IRQ_Enable_TXEIE					      (1<<7)		 	/*TX buffer empty interrupt enable*/
#define SPI_IRQ_Enable_RXNEIE					      (1<<6)			/*RX buffer not empty interrupt enable*/
#define SPI_IRQ_Enable_ERRIE					      (1<<5)			/*Error interrupt enable*/

typedef enum
{
	PollingEnable,
	PollingDisable
}Polling_mechanism;

/***************************APIs*****************************/
void MCAL_SPI_Init(SPI_Registers_t* SPIx, SPI_Config_t* SPI_Config);
void MCAL_SPI_DeInit(SPI_Registers_t* SPIx);
void MCAL_SPI_SendData(SPI_Registers_t* SPIx, uint16_t *TxPuffer, Polling_mechanism PollingEn);
void MCAL_SPI_ReceiveData(SPI_Registers_t* SPIx, uint16_t *RxPuffer, Polling_mechanism PollingEn);
void MCAL_SPI_TX_RX(SPI_Registers_t *SPIx, uint16_t *pBuffer, Polling_mechanism pollingEn);
void MCAL_SPI_GPIO_SetPins(SPI_Registers_t *SPIx);




#endif /* MCAL_SPI_SPI_INTERFACE_H_ */
