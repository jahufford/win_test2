/*
 * touchscreen.h
 *
 *  Created on: Dec 5, 2017
 *      Author: joe
 */
#ifndef TOUCHSCREEN_H_
#define TOUCHSCREEN_H_

#include "stm32f4xx_hal.h"


extern SPI_HandleTypeDef  h_touchscreen_spi;
extern uint8_t touchscreen_is_pressed;

#define TOUCHSCREEN_SPI					 SPI2
#define TOUCHSCREEN_IRQ_PIN              GPIO_PIN_7
#define TOUCHSCREEN_IRQ_PORT             GPIOA
#define TOUCHSCREEN_SPI_SCK_PIN			 GPIO_PIN_7
#define TOUCHSCREEN_SPI_SCK_PORT		 GPIOC
#define TOUCHSCREEN_SPI_MOSI_PIN	     GPIO_PIN_3
#define TOUCHSCREEN_SPI_MOSI_PORT	     GPIOC
#define TOUCHSCREEN_SPI_MISO_PIN		 GPIO_PIN_2
#define TOUCHSCREEN_SPI_MISO_PORT        GPIOC
#define TOUCHSCREEN_SPI_CS_PIN           GPIO_PIN_7
#define TOUCHSCREEN_SPI_CS_PORT          GPIOB
#define TOUCHSCREEN_SPI_CLK_ENABLE()     __HAL_RCC_SPI2_CLK_ENABLE()

#define TOUCHSCREEN_CS_LOW() 	HAL_GPIO_WritePin(TOUCHSCREEN_SPI_CS_PORT,TOUCHSCREEN_SPI_CS_PIN,GPIO_PIN_RESET)
#define TOUCHSCREEN_CS_HIGH() 	HAL_GPIO_WritePin(TOUCHSCREEN_SPI_CS_PORT,TOUCHSCREEN_SPI_CS_PIN,GPIO_PIN_SET)

uint8_t TS_HardwareInit();
uint8_t TS_IsPressed();
void    TS_WriteData(uint8_t data);
#endif /* TOUCHSCREEN_H_ */
