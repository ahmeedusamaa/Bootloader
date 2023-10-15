/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Adham Ehab
 * @brief          : Main program body
 ******************************************************************************/

#include"MCAL/RCC/RCC_Interface.h"
#include"APP/HEXPARSER/HexParser.h"
#include"MCAL/SCB/SCB_interface.h"
#include"MCAL/UASRT/USART_interface.h"
#include"MCAL/STK/STK_Interface.h"
#include"HAL/LCD/LCD.h"

/***************************Global Variables************************/
typedef void (*function_t)(void);

function_t App_call = 0; //void (void) ptr to fun

uint8_t TimeOutFlag = 0;

uint8_t UART_RxStatus = 0 ;

uint8_t RecordBuffer[100]; /*Hex Record is 44 digit*/

uint8_t RecordBufferCounter = 0 ;

/*One Way Flag*/
uint8_t EraseFlag = 0;
/******************************************************************/


/**************************STK Call Back function******************/
/*This function will be called after 15 sec*/
void STK_Callback(void)
{
	/*Set the Time out flag*/
	TimeOutFlag = 1 ;
	/*Assign Value to the SCB_VTOR*/
	MCAL_SCB_VTOR_SetValue(0x08008000); //VT_OFSSET_SHIFT
	/*Assign the application call ptr*/
	App_call = *(function_t *)0x08008004;// START OF APP
	/*Call the Application*/
	HAL_LCD_Clear_Screen();
	HAL_LCD_GoToXY(LCD_ROW1,LCD_Column1);
	HAL_LCD_Display_String("Flashing done");
	HAL_LCD_GoToXY(LCD_ROW2,LCD_Column1);
	HAL_LCD_Display_String("Jumping to app");
	MCAL_STK_Dealy_us(10000);
	App_call();
}
/*******************************************************************/

int main()
{
	/**********************Clock Initializations*********************/
	RCC_Config_t MyRCC ;
	MyRCC.RCC_SYS_CLK = HSI ;
	MCAL_RCC_voidInit(&MyRCC);
	MCAL_RCC_voidPeripheral_EN(FMI_PERIPHERAL, AHB1LP_BUS);
	MCAL_RCC_voidPeripheral_EN(USART1_PERIPHERAL, APB2_BUS);
	MCAL_RCC_voidPeripheral_EN(GPIOA_PERIPHERAL, AHB1_BUS);
	MCAL_RCC_voidPeripheral_EN(GPIOC_PERIPHERAL, AHB1_BUS);
	MCAL_RCC_voidPeripheral_EN(GPIOB_PERIPHERAL, AHB1_BUS);
	/***************************************************************/

	/**********************UART Initialization*********************/
	UART_Config_t MyUART ;
	MyUART.UART_BaudRate = UART_BAUDRATE_9600 ;
	MyUART.UART_DataLength = UART_DATA_LENGTH_8B;
	MyUART.UART_IRQ_State = UART_IRQ_DIS ;
	MyUART.UART_CallBack = NULL ;
	MyUART.UART_Mode = UART_TX_RX_MODE;
	MyUART.UART_ParityBits = UART_NO_PARITY;
	MyUART.UART_StopBits = UART_ONE_STOP_BIT;

	MCAL_UART_Init(UART1, &MyUART);
	MCAL_UART_GPIO_SetPins(UART1);
	/**************************************************************/

	/*****************************GPIO Init************************/
	GPIOx_Config_t TimeoutLED ;
	TimeoutLED.GPIO_PIN_MODE = GPIO_OUT_PP;
	TimeoutLED.GPIO_PIN_NUMBER = GPIO_PIN_13;
	TimeoutLED.GPIO_PIN_OUT_SPEED = GPIO_OUT_SPEED_MEDIUM;
	MCAL_GPIOx_Init(GPIOC, &TimeoutLED);
	MCAL_GPIOx_Pin_Write(GPIOC,GPIO_PIN_13, PIN_HIGH);
	/**************************************************************/

	/***********************SYSTK Initialization******************/
	MCAL_STK_Init();
	MCAL_STK_Set_Interval_Single(15000000*2, STK_Callback);
	/************************************************************/

	/************************************************************/
	HAL_LCD_Init();
	HAL_LCD_GoToXY(LCD_ROW1,LCD_Column1);
	HAL_LCD_Display_String("BL:Active");
	HAL_LCD_GoToXY(LCD_ROW2,LCD_Column1);
	HAL_LCD_Display_String("Flashing ...");
	/************************************************************/

	while (TimeOutFlag == 0)
	{
		UART_RxStatus = MCAL_UART_Recive_Byte_Synch(UART1,&RecordBuffer[RecordBufferCounter]);
		if(UART_RxStatus==1)
		{
			/*1-Stop the Timeout*/
			MCAL_STK_StopInterval();
			/*A byte has been recived through the UART*/
			/*Set the erase Flag*/
			if(EraseFlag !=1)
			{
				EraseFlag = 1 ;
				/*This Flag will never be Zero*/
				HexParser_vEraseAppArea();
			}
			/*2-Check end of record*/
			if(RecordBuffer[RecordBufferCounter] == '\n')
			{
				/*Record Recived Complete*/
				/*Set the erase Flag*/
				if(EraseFlag !=1)
				{
					EraseFlag = 1 ;
					/*This Flag will never be Zero*/
					HexParser_vEraseAppArea();
				}
				/*Start Parsing and burning the record*/
				HexParser_vParseData(RecordBuffer); /*whole buffer is 1 record*/
				MCAL_UART_SendString(UART1,"ok");
				RecordBufferCounter = 0 ;
			}
			else
			{
				/*Record is not ended yet*/
				RecordBufferCounter++;
			}
			MCAL_STK_Set_Interval_Single(1000000*2, STK_Callback);


		}

	}
	return 0 ;
}

