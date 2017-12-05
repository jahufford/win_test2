///*
// * lcd_hardware.h
// *
// *  Created on: Dec 2, 2017
// *      Author: joe
// */
//
#ifndef LCD_HARDWARE_H_
#define LCD_HARDWARE_H_
//
#include "stm32f4xx_hal.h"
#include "Global.h"
extern SPI_HandleTypeDef  h_lcd_spi;
//
#define LCD_SPIx						 SPI1
#define LCD_SPI_SCK_PIN					 GPIO_PIN_3
#define LCD_SPI_SCK_PORT				 GPIOB
#define LCD_SPI_MISO_PIN				 GPIO_PIN_4
#define LCD_SPI_MISO_PORT				 GPIOB
#define LCD_SPI_MOSI_PIN				 GPIO_PIN_5
#define LCD_SPI_MOSI_PORT				 GPIOB
#define LCD_SPI_NSS_PIN					 GPIO_PIN_10
#define LCD_SPI_NSS_PORT				 GPIOB
#define LCD_SPI_DC_PIN					 GPIO_PIN_8
#define LCD_SPI_DC_PORT                  GPIOA
#define LCD_RESET_PIN					 GPIO_PIN_7
#define LCD_RESET_PORT					 GPIOC
#define LCD_SPI_CLK_ENABLE()			 __HAL_RCC_SPI1_CLK_ENABLE()

#define LCD_CS_LOW() 	HAL_GPIO_WritePin(LCD_SPI_NSS_PORT,LCD_SPI_NSS_PIN,GPIO_PIN_RESET)
#define LCD_CS_HIGH() 	HAL_GPIO_WritePin(LCD_SPI_NSS_PORT,LCD_SPI_NSS_PIN,GPIO_PIN_SET)
#define LCD_DC_LOW()	HAL_GPIO_WritePin(LCD_SPI_DC_PORT, LCD_SPI_DC_PIN, GPIO_PIN_RESET) /* command */
#define LCD_DC_HIGH()	HAL_GPIO_WritePin(LCD_SPI_DC_PORT, LCD_SPI_DC_PIN, GPIO_PIN_SET)   /* data */

#define LCD_SET_DATA()   LCD_DC_HIGH()
#define LCD_SET_CMD()    LCD_DC_LOW()
//
void LCD_WriteByte(uint8_t data);
//
//void LcdWriteReg(U16 Data);
//void LcdWriteData(U16 Data);
//void LcdWriteDataMultiple(U16 * pData, int NumItems);
//
//void LCD_Set8Bit(void);
//void LCD_Set16Bit(void);
void LCD_Hardware_Init(void);
//void LCD_Module_Init();
//
//uint16_t LCD_ReadPixel();
//void LCD_SetColumn(uint16_t col_left, uint16_t col_right);
//void LCD_SetRow(uint16_t row_top, uint16_t row_bottom);
//void LCD_FillScreen2(uint16_t color);
#endif /* LCD_HARDWARE_H_ */
