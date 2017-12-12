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

#include "FRAMEWIN.h"
#include "DROPDOWN.h"
#include "LISTBOX.h"
#include <stddef.h>

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define SPEED 1000

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 5)

/*******************************************************************
*
*       static code
*
********************************************************************
*/
/*******************************************************************
*
*       _ShowSeveralFunctions
*/
static void _ShowSeveralFunctions(DROPDOWN_Handle hDropDown) {
  int NumEntries;
  int i;
  int Key;
  int Cnt;
  char ac[] = "-- sec to play with dropdown control";

  Key = 0;
  Cnt = 15;
  //
  // Set focus
  //
  GUI_DispStringAtCEOL("WM_SetFocus", 5, 55);
  GUI_Delay(SPEED * 0.9);
  WM_SetFocus(hDropDown);
  GUI_Delay(SPEED * 0.7);
  //
  // Add strings
  //
  GUI_DispStringAtCEOL("DROPDOWN_AddString", 5, 55);
  GUI_Delay(SPEED * 0.8);
  DROPDOWN_AddString(hDropDown, "English");
  DROPDOWN_AddString(hDropDown, "Deutsch");
  DROPDOWN_AddString(hDropDown, "Français");
  DROPDOWN_AddString(hDropDown, "Japanese");
  DROPDOWN_AddString(hDropDown, "Italiano");
  DROPDOWN_AddString(hDropDown, "Español");
  DROPDOWN_AddString(hDropDown, "Other language ...");
  GUI_Delay(SPEED * 0.6);
  //
  // Increment selection
  //
  GUI_DispStringAtCEOL("DROPDOWN_IncSel", 5, 55);
  GUI_Delay(SPEED);
  NumEntries = DROPDOWN_GetNumItems(hDropDown);
  for (i = 0; i < (NumEntries - 2); i++) {
    DROPDOWN_IncSel(hDropDown);
    GUI_Delay(SPEED / 6);
	}
  GUI_Delay(SPEED / 4);
  //
  // Expand dropdown
  //
  GUI_DispStringAtCEOL("DROPDOWN_Expand", 5, 55);
  GUI_Delay(SPEED);
  DROPDOWN_Expand(hDropDown);
  GUI_Delay(SPEED * 0.75);
  //
  // Add scrollbar
  //
  GUI_DispStringAtCEOL("DROPDOWN_SetAutoScroll", 5, 55);
  GUI_Delay(SPEED);
  DROPDOWN_SetAutoScroll(hDropDown, 1);
  GUI_Delay(SPEED * 0.75);
  //
  // Set font
  //
  GUI_DispStringAtCEOL("DROPDOWN_SetFont", 5, 55);
  GUI_Delay(SPEED);
  DROPDOWN_SetFont(hDropDown, &GUI_Font16B_1);
  GUI_Delay(SPEED * 0.75);
  //
  // Set text color
  //
  GUI_DispStringAtCEOL("DROPDOWN_SetTextColor", 5, 55);
  GUI_Delay(SPEED);
  DROPDOWN_SetTextColor(hDropDown, 0, 0x00BB00);
  DROPDOWN_SetTextColor(hDropDown, 2, GUI_BLACK);
  GUI_Delay(SPEED * 0.75);
  //
  // Set background color
  //
  GUI_DispStringAtCEOL("DROPDOWN_SetBkColor", 5, 55);
  GUI_Delay(SPEED);
  DROPDOWN_SetBkColor(hDropDown, 0, GUI_YELLOW);
  DROPDOWN_SetBkColor(hDropDown, 2, GUI_RED);
  GUI_Delay(SPEED * 0.75);
  //
  // Delete item
  //
  GUI_DispStringAtCEOL("DROPDOWN_DeleteItem", 5, 55);
  GUI_Delay(SPEED);
  DROPDOWN_DeleteItem(hDropDown, 5);
  GUI_Delay(SPEED * 0.75);
  //
  // Collapse dropdown
  //
  GUI_DispStringAtCEOL("DROPDOWN_Collapse", 5, 55);
  GUI_Delay(SPEED);
  DROPDOWN_Collapse(hDropDown);
  GUI_Delay(SPEED * 0.75);
  //
  // Decrement selection
  //
  GUI_DispStringAtCEOL("DROPDOWN_DecSel", 5, 55);
  GUI_Delay(SPEED);
  NumEntries = DROPDOWN_GetNumItems(hDropDown);
  for (i = 0; i < (NumEntries - 2); i++) {
    DROPDOWN_DecSel(hDropDown);
    GUI_Delay(SPEED / 6);
	}
  GUI_Delay(SPEED / 4);
  //
  // Let user play with dropdown control
  //
  GUI_DispStringAtCEOL("", 5, 55);
  while (!Key && (Cnt > 0)) {
    ac[0] = '0' + (Cnt / 10);
    ac[1] = '0' + (Cnt-- % 10);
    GUI_DispStringAtCEOL(ac, 5, 40);
    GUI_Delay(1000);
    Key = GUI_GetKey();
  }
  //
  // Delete dropdown widget
  //
  GUI_DispStringAtCEOL("DROPDOWN_Delete", 5, 55);
  GUI_Delay(SPEED * 1.1);
  WM_DeleteWindow(hDropDown);
  GUI_Delay(SPEED * 0.75);
}

/*******************************************************************
*
*       _DemoDropDown
*/
static void _DemoDropDown(void) {
  WM_HWIN hDropDown;

  //
  // Display titel
  //
  GUI_SetBkColor(0xB00000);
  GUI_SetColor(0xFFFFFF);
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_DispStringHCenterAt("Dropdown - Sample", 160, 5);
  GUI_Delay(SPEED / 2);
  //
  // Create listbox
  //
  GUI_SetFont(&GUI_Font8x16);
  GUI_SetTextAlign(GUI_TA_LEFT);
  GUI_DispStringAtCEOL("using", 5, 40);
  GUI_DispStringAtCEOL("DROPDOWN_CreateEx", 5, 55);
  GUI_Delay(SPEED * 0.9);
  hDropDown = DROPDOWN_CreateEx(100, 80, 120, 115-50, WM_HBKWIN, WM_CF_SHOW, 0, 0);
  GUI_Delay(SPEED * 0.75);
  //
  // Show serveral functions of listbox
  //
  _ShowSeveralFunctions(hDropDown);
  //
  // Clear display
  //
  GUI_Clear();
  GUI_Delay(SPEED * 1.5);
}

/*******************************************************************
*
*       _DemoDropDownAsChild
*/
static void _DemoDropDownAsChild(void) {
  WM_HWIN hFrame;
  WM_HWIN hDropDown;

  //
  // Display titel
  //
  GUI_SetBkColor(0xB00000);
  GUI_SetColor(0xFFFFFF);
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_DispStringHCenterAt("Dropdown as child - Sample", 160, 5);
  GUI_Delay(SPEED / 2);
  //
  // Create framewin
  //
  GUI_SetFont(&GUI_Font8x16);
  GUI_SetTextAlign(GUI_TA_LEFT);
  GUI_DispStringAtCEOL("using", 5, 40);
  GUI_DispStringAtCEOL("FRAMEWIN_Create", 5, 55);
  GUI_Delay(SPEED);
  hFrame = FRAMEWIN_Create("DropDown", NULL, WM_CF_SHOW, 80, 80, 160, 140);
  FRAMEWIN_SetFont(hFrame, &GUI_Font16B_ASCII);
  FRAMEWIN_SetActive(hFrame, 1);
  GUI_Delay(SPEED * 0.75);
  //
  // Create listbox
  //
  GUI_DispStringAtCEOL("DROPDOWN_CreateEx", 5, 55);
  GUI_Delay(SPEED);
  hDropDown = DROPDOWN_CreateEx(20, 20, 120, 65, WM_GetClientWindow(hFrame), WM_CF_SHOW, 0, 0);
  GUI_Delay(SPEED * 0.75);
  //
  // Show serveral functions of listbox
  //
  _ShowSeveralFunctions(hDropDown);
  //
  // Delete framewin widget
  //
  GUI_DispStringAtCEOL("WM_DeleteWindow", 5, 55);
  GUI_Delay(SPEED);
  WM_DeleteWindow(hFrame);
  GUI_Delay(SPEED * 0.75);
  //
  // Clear display
  //
  GUI_Clear();
  GUI_Delay(SPEED * 1.5);
}


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
     WM_SetDesktopColor(0xB00000);
       GUI_Exec();
       while(1) {
         _DemoDropDown();
         _DemoDropDownAsChild();
       }
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

