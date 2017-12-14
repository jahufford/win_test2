/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @author  Ac6
  * @version V1.0
  * @date    02-Feb-2015
  * @brief   Default Interrupt Service Routines.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#ifdef USE_RTOS_SYSTICK
#include <cmsis_os.h>
#endif
#include "stm32f4xx_it.h"
#include "touchscreen.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            	  	    Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles SysTick Handler, but only if no RTOS defines it.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
#ifdef USE_RTOS_SYSTICK
	//osSystickHandler();
#endif
}

void NMI_Handler()
{
	while(1){
		asm("nop");
	}
}

void HardFault_Handler()
{
	//while(1){
		asm("nop");
	//};
}

void MemManage_Handler()
{
	while(1){
		asm("nop");
	}
}

void UsageFault_Handler()
{
	while(1){
		asm("nop");
	}
}


//void SVC_Handler()
//{
//	while(1){
//		asm("nop");
//	}
//}

void DebugMon_Handler()
{
	while(1){
		asm("nop");
	}
}

//void PendSV_Handler()
//{
//	while(1){
//		asm("nop");
//	}
//}
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA

void EXTI9_5_IRQHandler(void)
{
	// handle touchscreen interrupt
	if(__HAL_GPIO_EXTI_GET_IT(TOUCHSCREEN_IRQ_PIN)){
      EXTI->IMR &= ~(1<<7); // mask the interrupt
      if(touchscreen_is_pressed){
    	  EXTI->RTSR &= ~(TOUCHSCREEN_IRQ_PIN); // turn off rising egge
    	  EXTI->FTSR |= TOUCHSCREEN_IRQ_PIN; // turn on falling edge
          touchscreen_is_pressed = 0;
      }else{
    	  EXTI->FTSR &= ~(TOUCHSCREEN_IRQ_PIN); // turn off falling edge
    	  EXTI->RTSR |= (TOUCHSCREEN_IRQ_PIN);
          touchscreen_is_pressed = 1;
          // TODO
          // read x y coordinates, and insert to PID queue of the window manager
      }
      EXTI->IMR |= (1<<7); // unmask the interrupt
      __HAL_GPIO_EXTI_CLEAR_IT(TOUCHSCREEN_IRQ_PIN);
	}
}
void EXTI15_10_IRQHandler(void)
{
	asm("nop");
//	char var = 'A';
//	volatile uint32_t reg;
//    reg = EXTI->PR;
//    uint32_t rreg;
//    rreg = GPIO_PIN_13;
//    asm("nop");
//    EXTI->PR |= reg;
    EXTI->PR |= EXTI_PR_PR13;
//    EXTI->IMR &= ~(1<<13);
//    uint8_t byte[2];
//	TS_WriteData(0x90); // back to idle
//	if(HAL_SPI_Receive(&h_touchscreen_spi,(uint8_t*)byte, 1,0xFFFF) != HAL_OK){
//	   Error_Handler();
//	}
//	if(HAL_SPI_Receive(&h_touchscreen_spi,(uint8_t*)&byte[1], 1,0xFFFF) != HAL_OK){
//	   Error_Handler();
//	}
//    reg = EXTI->PR;
    //HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    //HAL_UART_Transmit(&UartHandleWireless, (uint8_t*)&var,1,0xFFFF);
}
