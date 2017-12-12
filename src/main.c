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

#include <stddef.h>
#include <string.h>
#include "WM.h"
#include "FRAMEWIN.h"
#include "BUTTON.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 5)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static int _Color;
static int _Font;
static int _Pressed;

#define BW 90
#define BH 40

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Round button sample", 0,      20,  20, 240, 205, FRAMEWIN_CF_MOVEABLE },
  { BUTTON_CreateIndirect,   "Button",   GUI_ID_BUTTON0,   115,  30,  110,  110 },
  { BUTTON_CreateIndirect,   "Callback", GUI_ID_BUTTON1,    10,  5,  BW,  BH },
  { BUTTON_CreateIndirect,   "Font",     GUI_ID_BUTTON2,    10,  5+BH+3,  BW,  BH },
  { BUTTON_CreateIndirect,   "Color",    GUI_ID_BUTTON3,    10,  5+2*BH+2*3,  BW,  BH },
  { BUTTON_CreateIndirect,   "Cancel",   GUI_ID_CANCEL,     10,  5+3*BH+3*3,  BW,  BH }
};

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/
/*********************************************************************
*
*       _OnPaint
*
* Function description
*   Paints the owner drawn button
*/
static void _OnPaint(BUTTON_Handle hObj) {
  int Index;
  char ac[50];
  GUI_RECT Rect;

  Index = (WIDGET_GetState(hObj) & BUTTON_STATE_PRESSED) ? 1 : 0;
  WM_GetClientRect(&Rect);
  //
  // Draw filled ellipse with button background color
  //
  GUI_SetColor(BUTTON_GetBkColor(hObj, Index));
  GUI_FillEllipse(Rect.x1 / 2, Rect.y1 / 2, Rect.x1 / 2, Rect.y1 / 2);
  //
  // Draw black shape
  //
  GUI_SetColor(GUI_BLACK);
  GUI_DrawEllipse(Rect.x1 / 2, Rect.y1 / 2, Rect.x1 / 2, Rect.y1 / 2);
  //
  // Draw button text with widget attributes
  //
  GUI_SetColor(BUTTON_GetTextColor(hObj, Index));
  GUI_SetBkColor(BUTTON_GetBkColor(hObj, Index));
  GUI_SetFont(BUTTON_GetFont(hObj));
  BUTTON_GetText(hObj, ac, sizeof(ac));
  if (_Pressed) {
    strcpy(ac + strlen(ac), "\npressed");
  }
  GUI_DispStringInRect(ac, &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
}

/*********************************************************************
*
*       _cbButton
*
* Function description
*  1. Calls the owner draw function if the WM_PAINT message has been send
*  2. Calls the original callback for further messages
*  3. After processing the messages the function evaluates the pressed-state
*     if the WM_TOUCH message has been send
*/
static void _cbButton(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
    case WM_PAINT:
      _OnPaint(pMsg->hWin);
      break;
    default:
      BUTTON_Callback(pMsg); // The original callback
      break;
  }
  if (pMsg->MsgId == WM_TOUCH) {
    if (BUTTON_IsPressed(pMsg->hWin)) {
      if (!_Pressed) {
        _Pressed = 1;
      }
    } else {
      _Pressed = 0;
    }
  }
}

/*********************************************************************
*
*       _cbDialog
*
* Function description
*   Dialog callback routine
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  int           NCode;
  int           Id;
  WM_HWIN       hDlg;
  BUTTON_Handle hButton;

  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
    case WM_PAINT:
      WM_DefaultProc(pMsg); // Handle dialog items
      //
      // After drawing the dialog items add some user drawn items to the window
      //
      GUI_SetPenSize(10);
      GUI_SetColor(GUI_GREEN);
      GUI_DrawLine( 95,  5, 185, 95);
      GUI_SetColor(GUI_RED);
      GUI_DrawLine( 95, 95, 185,  5);
      break;
    case WM_INIT_DIALOG:
      hButton = WM_GetDialogItem(hDlg, GUI_ID_BUTTON0);
      WM_SetHasTrans(hButton);              // Set transparency flag for button

      break;
    case WM_KEY:
      switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
        case GUI_KEY_ESCAPE:
          GUI_EndDialog(hDlg, 1);
          break;
        case GUI_KEY_ENTER:
          GUI_EndDialog(hDlg, 0);
          break;
      }
      break;
    case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);      // Id of widget
      NCode = pMsg->Data.v;                 // Notification code
      switch (NCode) {
        case WM_NOTIFICATION_RELEASED:      // React only if released
          hButton = WM_GetDialogItem(hDlg, GUI_ID_BUTTON0);
          if (Id == GUI_ID_BUTTON1) {       // Toggle callback
            if (WM_GetCallback(hButton) == _cbButton) {
              WM_SetCallback(hButton, BUTTON_Callback);
            } else {
              WM_SetCallback(hButton, _cbButton);
            }
            WM_InvalidateWindow(hButton);
          }
          if (Id == GUI_ID_BUTTON2) {       // Toggle font
            if (_Font) {
              BUTTON_SetFont(hButton, &GUI_Font13_1);
            } else {
              BUTTON_SetFont(hButton, &GUI_Font8x16);
            }
            _Font ^= 1;
          }
          if (Id == GUI_ID_BUTTON3) {       // Toggle color
            if (_Color) {
              BUTTON_SetBkColor(hButton, 0, 0xaaaaaa);
              BUTTON_SetBkColor(hButton, 1, GUI_WHITE);
              BUTTON_SetTextColor(hButton, 0, GUI_BLACK);
              BUTTON_SetTextColor(hButton, 1, GUI_BLACK);
            } else {
              BUTTON_SetBkColor(hButton, 0, GUI_BLUE);
              BUTTON_SetBkColor(hButton, 1, GUI_RED);
              BUTTON_SetTextColor(hButton, 0, GUI_WHITE);
              BUTTON_SetTextColor(hButton, 1, GUI_YELLOW);
            }
            _Color ^= 1;
          }
          if (Id == GUI_ID_OK) {            // OK Button
            GUI_EndDialog(hDlg, 0);
          }
          if (Id == GUI_ID_CANCEL) {        // Cancel Button
            GUI_EndDialog(hDlg, 1);
          }
          break;
      }
      break;
    default:
      WM_DefaultProc(pMsg);
  }
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
#if GUI_SUPPORT_MEMDEV
  WM_SetCreateFlags(WM_CF_MEMDEV);
  WM_EnableMemdev(WM_HBKWIN);
#endif
WM_SetDesktopColor(GUI_GREEN);
while(1) {
  _Font = _Color = 0;
  GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbDialog, 0, 0, 0);
  GUI_Delay(1000);
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

