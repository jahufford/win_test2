/*
 * touchscreen.c
 *
 *  Created on: Dec 5, 2017
 *      Author: joe
 */

#include "touchscreen.h"

SPI_HandleTypeDef  h_touchscreen_spi;

uint8_t touchscreen_is_pressed;

// returns 1 on success, 0 on failure
uint8_t TS_HardwareInit()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	//__HAL_RCC_GPIOF_CLK_ENABLE();
    // set up Touchscreen SPI ports and pins
    // Touchscreen SCK
	GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = TOUCHSCREEN_SPI_SCK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(TOUCHSCREEN_SPI_SCK_PORT, &GPIO_InitStruct);

    // SPI MISO
    GPIO_InitStruct.Pin = TOUCHSCREEN_SPI_MISO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(TOUCHSCREEN_SPI_MISO_PORT, &GPIO_InitStruct);

    // SPI MOSI
    GPIO_InitStruct.Pin = TOUCHSCREEN_SPI_MOSI_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(TOUCHSCREEN_SPI_MOSI_PORT, &GPIO_InitStruct);

    // SPI chip select
    GPIO_InitStruct.Pin = TOUCHSCREEN_SPI_CS_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    //GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(TOUCHSCREEN_SPI_CS_PORT, &GPIO_InitStruct);
   	HAL_GPIO_WritePin(TOUCHSCREEN_SPI_CS_PORT,TOUCHSCREEN_SPI_CS_PIN,GPIO_PIN_SET);
   	HAL_GPIO_WritePin(TOUCHSCREEN_SPI_CS_PORT,TOUCHSCREEN_SPI_CS_PIN,GPIO_PIN_RESET);
   	HAL_GPIO_WritePin(TOUCHSCREEN_SPI_CS_PORT,TOUCHSCREEN_SPI_CS_PIN,GPIO_PIN_SET);


   	// set up the button
    GPIO_InitStruct.Pin = GPIO_PIN_13;
   	//GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
   	//GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
   	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
   	GPIO_InitStruct.Pull = GPIO_NOPULL;
   	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   	//GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
   	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

   	 // generate interrupt when button is pressed
//   	     //SYSCFG_IEXTICR4;
    volatile uint32_t reg;
    reg = SYSCFG->EXTICR[3];
    //reg = 0xFFFFFFFF;
    reg &= ~(0xF << 4);
    //reg |= (0x2 << 4);
    reg |= (SYSCFG_EXTICR4_EXTI13_PC);
    //reg |= (SYSCFG_EXTICR4_EXTI13_PB);
    SYSCFG->EXTICR[3] = reg;
//    EXTI->RTSR &= ~(1<<13);
//    //EXTI->FTSR |= (1<<13);
//    EXTI->FTSR |= EXTI_FTSR_TR13;
//    //EXTI->IMR |= (1<<13);
//    EXTI->IMR |= EXTI_IMR_MR13;
    NVIC_SetPriority(EXTI15_10_IRQn, 1);
    NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
    NVIC_EnableIRQ(EXTI15_10_IRQn);


   	// set up touchscreen IRQ external input pin
    GPIO_InitStruct.Pin = TOUCHSCREEN_IRQ_PIN;
   	//GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
   	//GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
   	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
   	GPIO_InitStruct.Pull = GPIO_NOPULL;
   	//GPIO_InitStruct.Pull = GPIO_PULLUP;
   	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   	HAL_GPIO_Init(TOUCHSCREEN_IRQ_PORT, &GPIO_InitStruct);

    reg = SYSCFG->EXTICR[1];
    reg &= ~(SYSCFG_EXTICR2_EXTI7_Msk);  // ~(0xF << 12)
    reg |= (SYSCFG_EXTICR2_EXTI7_PA);
    SYSCFG->EXTICR[1] = reg;
    touchscreen_is_pressed = 0;
    NVIC_SetPriority(EXTI9_5_IRQn, 1);
    NVIC_ClearPendingIRQ(EXTI9_5_IRQn);
   // NVIC_EnableIRQ(EXTI9_5_IRQn);

    TOUCHSCREEN_SPI_CLK_ENABLE();

    h_touchscreen_spi.Instance = TOUCHSCREEN_SPI;
    //h_lcd_spi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    h_touchscreen_spi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
    h_touchscreen_spi.Init.CLKPhase = SPI_PHASE_1EDGE;
    h_touchscreen_spi.Init.CLKPolarity = SPI_POLARITY_LOW; // might need to be high with 2nd edge
    h_touchscreen_spi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    h_touchscreen_spi.Init.CRCPolynomial;
    h_touchscreen_spi.Init.DataSize = SPI_DATASIZE_8BIT;
    h_touchscreen_spi.Init.Direction = SPI_DIRECTION_2LINES;
    h_touchscreen_spi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    h_touchscreen_spi.Init.Mode = SPI_MODE_MASTER;
    h_touchscreen_spi.Init.NSS = SPI_NSS_HARD_OUTPUT;
    //h_lcd_spi.Init.NSS = SPI_NSS_SOFT;
    h_touchscreen_spi.Init.TIMode = SPI_TIMODE_DISABLE;
    h_touchscreen_spi.State = HAL_SPI_STATE_RESET;

    if(HAL_SPI_Init(&h_touchscreen_spi) != HAL_OK){
    	return 0;
    }


//  while(1){
//    	TOUCHSCREEN_CS_LOW();
//    	TS_WriteData(0x00);
//    	TS_WriteData(0x01);
//    	TOUCHSCREEN_CS_HIGH();
//    }
	return 1;
}

uint8_t TS_IsPressed()
{
	return touchscreen_is_pressed;
}

void TS_WriteData(uint8_t data) {
	//TOUCHSCREEN_CS_LOW();
	if(HAL_SPI_Transmit(&h_touchscreen_spi,(uint8_t*)&data, 1,0xFFFF) != HAL_OK){
		Error_Handler();
    }
	//TOUCHSCREEN_CS_HIGH();
}
