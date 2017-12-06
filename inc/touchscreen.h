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
#define TOUCHSCREEN_SPI_MOSI_PIN	     GPIO_PIN_15
#define TOUCHSCREEN_SPI_MOSI_PORT	     GPIOB
#define TOUCHSCREEN_SPI_MISO_PIN		 GPIO_PIN_14
#define TOUCHSCREEN_SPI_MISO_PORT        GPIOB
#define TOUCHSCREEN_SPI_CS_PIN           GPIO_PIN_1
#define TOUCHSCREEN_SPI_CS_PORT          GPIOB
#define TOUCHSCREEN_SPI_CLK_ENABLE()     __HAL_RCC_SPI2_CLK_ENABLE()

uint8_t TS_HardwareInit();
uint8_t TS_IsPressed();

#endif /* TOUCHSCREEN_H_ */
