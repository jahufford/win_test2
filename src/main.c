/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "GUI.h"
#include "WM.h"
#include "PROGBAR.h"
#include "BUTTON.h"
#include "stdlib.h"
#include "debug_serial_port.h"
#include "touchscreen.h"

void Error_Handler(void);
void Button_Init(void);
void SystemClock_Config(void);


#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA



/*******************************************************************
*
*       _DemoButton
*/
static void _DemoButton(void) {
  BUTTON_Handle hButton;

  GUI_SetFont(&GUI_Font8x16);
  GUI_DispStringHCenterAt("Click on button...", 160, 90);
  //
  // Create the button and set text
  //
  hButton = BUTTON_Create(110, 110, 100, 40, GUI_ID_OK, WM_CF_SHOW);
  BUTTON_SetText(hButton, "Click me...");
  //
  // Let window manager handle the button
  //
  while (GUI_WaitKey() != GUI_ID_OK);
  //
  // Delete the button
  //
  WM_DeleteWindow(hButton);
  GUI_ClearRect(0, 50, 319, 239);
  GUI_Delay(1000);
}

#define RECOMMENDED_MEMORY (1024L * 5)

int main(void)
{

	HAL_Init();
    SystemClock_Config();

    __CRC_CLK_ENABLE();
    CRC_HandleTypeDef hcrc;
    hcrc.Instance = CRC;
    if (HAL_CRC_Init(&hcrc) != HAL_OK)
    {
        Error_Handler();
    }
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = LD2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

    DebugSerialPort_Init();
    Button_Init();


    asm("nop");
    volatile int ret;
    ret = GUI_Init();
    asm("nop");
    //
     // Check if recommended memory for the sample is available
     //
     if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
       GUI_ErrorOut("Not enough memory available.");
       return;
     }
     GUI_SetBkColor(GUI_BLACK);
     GUI_Clear();
     GUI_SetColor(GUI_WHITE);
     GUI_SetFont(&GUI_Font24_ASCII);
     GUI_DispStringHCenterAt("WIDGET_SimpleButton - Sample", 160, 5);
     while (1) {
       _DemoButton();
     }
//
//    uint32_t colors[25] = {GUI_BLUE,GUI_GREEN,GUI_RED, GUI_CYAN,GUI_MAGENTA,GUI_YELLOW,
//    					   GUI_LIGHTBLUE,GUI_LIGHTGREEN,GUI_LIGHTRED,GUI_LIGHTCYAN, GUI_LIGHTMAGENTA,
//						   GUI_LIGHTYELLOW,GUI_DARKBLUE,GUI_DARKGREEN,GUI_DARKRED,GUI_DARKCYAN,
//						   GUI_DARKMAGENTA,GUI_DARKYELLOW,GUI_WHITE,GUI_LIGHTGRAY,GUI_GRAY,
//						   GUI_DARKGRAY,GUI_BLACK,GUI_BROWN,GUI_ORANGE};
//
//
//    struct Rectangle rect = {50,50,150,100};
//    GUI_SetColor(GUI_GREEN);
//    GUI_DrawRect(rect.x,rect.y,rect.x+rect.width,rect.y+rect.height);
//
//    uint8_t first_response;
//    uint32_t last_x = rect.x+15;
//    uint32_t last_y = rect.y+15;
//    uint32_t touch_offset_x;
//    uint32_t touch_offset_y;
//    int delta;
//
//	for(;;){
//        HAL_Delay(100);
//		if(TS_IsPressed()){
//            TS_StartRead();
//			int16_t x = TS_GetX(3);//  average a few reads, since quick taps tend to make a bogus read initially
//			int16_t y = TS_GetY(3);
//			TS_SetIdle();
//			TS_EndRead();
//
//			if( x > 0 && y > 0){ // if valid coordinate reads
//				if(InRect(x,y,&rect)){
//                    if(first_response){
////                      GUI_SetColor(GUI_BLACK);
////                      GUI_FillRect(1,1,318,238);
//                    	LCD_FillScreen2(0);
//                    	GUI_SetColor(GUI_WHITE);
//                    	GUI_DrawRect(0,0,319,239);
//                      touch_offset_x = x-rect.x;
//                      touch_offset_y = y-rect.y;
//                      first_response = 0;
//                    }else{
//                    	// it's movement
//                    	delta = last_x - x;
//                    }
//					// erase old rect and crosshairs
//					GUI_SetColor(GUI_BLACK);
//					GUI_DrawRect(rect.x,rect.y,rect.x+rect.width,rect.y+rect.height);
//					GUI_DrawHLine(last_y,rect.x,rect.x+rect.width);
//					GUI_DrawVLine(last_x,rect.y,rect.y+rect.height);
//
//					if((int)x - (int)touch_offset_x <= 0){
//						rect.x=1;
//					}else if( (int)x-(int)touch_offset_x+rect.width >=318){
//						rect.x = 319-rect.width-1;
//					}else{
//						rect.x = x-touch_offset_x;
//					}
//
//					if((int)y - (int)touch_offset_y <= 0){
//						rect.y=1;
//					}else if( (int)y-(int)touch_offset_y+rect.height >= 238){
//						rect.y = 239-rect.height-1;
//					}else{
//                        rect.y = y-touch_offset_y;
//					}
//					GUI_SetColor(GUI_GREEN);
//					GUI_DrawRect(rect.x,rect.y,rect.x+rect.width,rect.y+rect.height);
//
//					GUI_SetColor(GUI_RED);
//					GUI_DrawHLine(y,rect.x,rect.x+rect.width);
//					GUI_DrawVLine(x,rect.y,rect.y+rect.height);
//				}
//				last_x = x;
//				last_y = y;
//				printf("X=%d Y=%d\r\n", x,y);
//            }
//		}else{
//			first_response = 1;
//		}
//	}
}


void Error_Handler(void)
{
  /* Turn LED2 on */
 // BSP_LED_On(LED2);
  while(1)
  {
  }
}

// set up the user button on the nucleo and enable it's interrupt
void Button_Init(void)
{
   	// set up the button
	GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_13;
   	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
   	GPIO_InitStruct.Pull = GPIO_NOPULL;
   	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

   	 // generate interrupt when button is pressed
    volatile uint32_t reg;
    reg = SYSCFG->EXTICR[3];
    reg &= ~(0xF << 4);
    reg |= (SYSCFG_EXTICR4_EXTI13_PC);
    SYSCFG->EXTICR[3] = reg;
//    EXTI->RTSR &= ~(1<<13);
//    //EXTI->FTSR |= (1<<13);
//    EXTI->FTSR |= EXTI_FTSR_TR13;
//    //EXTI->IMR |= (1<<13);
//    EXTI->IMR |= EXTI_IMR_MR13;
    NVIC_SetPriority(EXTI15_10_IRQn, 1);
    NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows:
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSI Frequency(Hz)              = 16000000
  *            PLL_M                          = 16
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            PLL_R                          = 6
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSI Oscillator and activate PLL with HSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 0x10;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  RCC_OscInitStruct.PLL.PLLR = 6;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

   /* Activate the OverDrive to reach the 180 MHz Frequency */
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }

}

