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
void SystemClock_Config(void);

//uint16_t LCD_MakeColor(uint8_t red, uint8_t green, uint8_t blue)
uint16_t LCD_MakeColor(uint32_t color_to_convert)
{
	uint8_t blue = color_to_convert>>16;
	uint8_t green = color_to_convert>>8;
	green &= 0xFF;
	uint8_t red = color_to_convert&0xFF;
	uint16_t color = red;
	color <<= 6;
	color |= green;
	color <<= 5;
	color |= blue;
	return color;
}

   GUI_HWIN hWnd;
static void cbForegroundWin(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
    case WM_PAINT:
      GUI_SetBkColor(GUI_GREEN);
      GUI_Clear();
      GUI_SetColor(GUI_BLUE);
      GUI_DispString("Foreground window");

    break;
    default:
      WM_DefaultProc(pMsg);
  }
}
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
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

    uint32_t tickstart = HAL_GetTick();
    for(int i=0;i<4000000;i++){
    	tickstart = HAL_GetTick();
    }
    asm("nop");
    volatile int ret;
    ret = GUI_Init();
    asm("nop");
//    GUI_SetFont(&GUI_Font8x16);
//    GUI_DispString("Hello world!");
//    GUI_DispDecAt( 27, 20,20,4);


    //volatile int x = GUI_IsInitialized();
    //GUI_SetBkColor(GUI_DARKRED);
//    GUI_Clear();
//    asm("nop");
//    //GUI_FillRect(20,20,280,150);
//    //GUI_SetBkColor(GUI_DARKRED);
//    //GUI_SetColor(LCD_MakeColor(GUI_BLUE));
    //GUI_SetColor(GUI_MAKE_COLOR(GUI_RED));
    GUI_SetColor(GUI_WHITE);
    GUI_DrawRect(0,0,319,239);
    GUI_SetColor(GUI_RED);
    GUI_FillRect(20,20,80,40);
    //GUI_SetColor(GUI_MAKE_COLOR(GUI_GREEN));
    GUI_SetColor(GUI_GREEN);
    GUI_FillRect(20,50,80,70);
    GUI_SetColor(GUI_BLUE);
    GUI_FillRect(20,80,80,100);
    GUI_SetColor((GUI_ORANGE));
    GUI_FillRect(20,110,80,120);
    GUI_SetColor(GUI_RED);
    GUI_SetBkColor(GUI_BLACK);
    //GUI_SetBkColorIndex(1);
	//GUI_SetColorIndex(2);
    //GUI_Clear();
    //GUI_SetFont(&GUI_Font20_1);
    int x = 0;
    int y = 120;
    uint32_t colors[25] = {GUI_BLUE,GUI_GREEN,GUI_RED, GUI_CYAN,GUI_MAGENTA,GUI_YELLOW,
    					   GUI_LIGHTBLUE,GUI_LIGHTGREEN,GUI_LIGHTRED,GUI_LIGHTCYAN, GUI_LIGHTMAGENTA,
						   GUI_LIGHTYELLOW,GUI_DARKBLUE,GUI_DARKGREEN,GUI_DARKRED,GUI_DARKCYAN,
						   GUI_DARKMAGENTA,GUI_DARKYELLOW,GUI_WHITE,GUI_LIGHTGRAY,GUI_GRAY,
						   GUI_DARKGRAY,GUI_BLACK,GUI_BROWN,GUI_ORANGE};
    for(int i=0;i<25;i++){
    	GUI_SetColor(colors[i]);
    	GUI_FillRect(x,y,x+10,y+20);
    	x+=10;
    }
    GUI_SetColor(GUI_CYAN);
    GUI_FillRoundedRect(150,30,300,100,10);
    GUI_SetFont(GUI_FONT_32B_ASCII);
    //GUI_SetFont(GUI_FONT_COMIC24B_1);
    GUI_SetColor(GUI_BLUE);
    GUI_SetBkColor(GUI_GREEN);
    GUI_DispCharAt('A',3,200);
    //GUI_DispStringAt("Hi", (LCD_GetXSize()-100)/2, (LCD_GetYSize()-20)/2);
    GUI_SetBkColor(GUI_DARKCYAN);
    GUI_DispStringAt("Hello World!", (LCD_GetXSize()-100)/2, 200);
    GUI_SetColor(GUI_YELLOW);
    GUI_SetFont(GUI_FONT_COMIC24B_1);
    GUI_DispStringAt("Hello World!", 95,150);
    GUI_SetColor(GUI_ORANGE);
    GUI_FillEllipse(100,100,75,25);
    GUI_SetColor(GUI_RED);
    GUI_DrawPie(250,175,50,10,80,0);
    GUI_SetColor(GUI_BLUE);
    GUI_DrawPie(250,175,50,81,135,0);
    GUI_SetColor(GUI_YELLOW);
    GUI_DrawPie(250,175,50,136,215,0);

    GUI_DispStringAt("Progress bar", 100, 20);


    /* Create foreground window */
    //hWnd = WM_CreateWindow(10, 10, 300, 200, WM_CF_SHOW, cbForegroundWin, 0);
    PROGBAR_Handle hProgBar;
    hProgBar = PROGBAR_Create(85, 50, 200, 40, WM_CF_SHOW);
    PROGBAR_SetBarColor(hProgBar, 0, GUI_YELLOW);
    PROGBAR_SetBarColor(hProgBar, 1, GUI_RED);
    PROGBAR_SetValue(hProgBar, 77);
    PROGBAR_SetFont(hProgBar,GUI_FONT_COMIC24B_1);
//    BUTTON_Handle btn = BUTTON_CreateEx(30,180,30,15,0,0,WM_CF_SHOW,0);
//    BUTTON_SetText(btn,"Button");
    BUTTON_Handle hButton;
    GUI_SetFont(&GUI_Font8x16);
    //GUI_DispStringHCenterAt("Click on button...", 160, 90);
    /* Create the button*/
    hButton = BUTTON_Create(30, 160, 100, 30, GUI_ID_OK, WM_CF_SHOW);
    /* Set the button text */
    BUTTON_SetText(hButton, "Button Up");
    BUTTON_Handle hButton2;
    hButton2 = BUTTON_Create(30, 195, 100, 30, GUI_ID_OK, WM_CF_SHOW);
    BUTTON_SetText(hButton2,"Button Down");
    BUTTON_SetPressed(hButton2,1);
    WM_Exec();
    GUI_Exec();
    	HAL_Delay(1000);
//    for(;;){
//    	BUTTON_SetPressed(hButton,1);
//    	WM_Exec();
//    	HAL_Delay(1000);
//    	BUTTON_SetPressed(hButton,0);
//    	WM_Exec();
//    	HAL_Delay(1000);
//    }
        while(1){
    //    	for(int i=0;i<200;i++){
    //    		asm("nop");
    //    	}
        	HAL_Delay(100);
            TOUCHSCREEN_CS_LOW();
          //	// read y position
          //	TS_WriteData(0xD9);
            // read x position
            //TS_WriteData(0xD9);
            TS_WriteData(0x99);
            uint8_t byte[2];
            if(HAL_SPI_Receive(&h_touchscreen_spi,(uint8_t*)byte, 1,0xFFFF) != HAL_OK){
               Error_Handler();
            }
            if(HAL_SPI_Receive(&h_touchscreen_spi,(uint8_t*)&byte[1], 1,0xFFFF) != HAL_OK){
               Error_Handler();
            }

            uint16_t datax = byte[0];
            datax <<= 8;
            datax |= byte[1];
            datax >>= 3;
            TOUCHSCREEN_CS_HIGH();

            TOUCHSCREEN_CS_LOW();
            // read y position
            TS_WriteData(0xD9);
            if(HAL_SPI_Receive(&h_touchscreen_spi,(uint8_t*)byte, 1,0xFFFF) != HAL_OK){
               Error_Handler();
            }
            if(HAL_SPI_Receive(&h_touchscreen_spi,(uint8_t*)&byte[1], 1,0xFFFF) != HAL_OK){
               Error_Handler();
            }

            uint16_t datay = byte[0];
            datay <<= 8;
            datay |= byte[1];
            datay >>= 3;

            TS_WriteData(0x90); // back to idle
            if(HAL_SPI_Receive(&h_touchscreen_spi,(uint8_t*)byte, 1,0xFFFF) != HAL_OK){
               Error_Handler();
            }
            if(HAL_SPI_Receive(&h_touchscreen_spi,(uint8_t*)&byte[1], 1,0xFFFF) != HAL_OK){
               Error_Handler();
            }
            TOUCHSCREEN_CS_HIGH();
//            HAL_Delay(100);
//
//
//            TOUCHSCREEN_CS_LOW();
//             // read z1 position
//             TS_WriteData(0xB9);
//             if(HAL_SPI_Receive(&h_touchscreen_spi,(uint8_t*)byte, 1,0xFFFF) != HAL_OK){
//                Error_Handler();
//             }
//             if(HAL_SPI_Receive(&h_touchscreen_spi,(uint8_t*)&byte[1], 1,0xFFFF) != HAL_OK){
//                Error_Handler();
//             }
//
//             uint16_t dataz1 = byte[0];
//             dataz1 <<= 8;
//             dataz1 |= byte[1];
//             dataz1 >>= 3;
//
//             TS_WriteData(0x90); // back to idle
//             if(HAL_SPI_Receive(&h_touchscreen_spi,(uint8_t*)byte, 1,0xFFFF) != HAL_OK){
//                Error_Handler();
//             }
//             if(HAL_SPI_Receive(&h_touchscreen_spi,(uint8_t*)&byte[1], 1,0xFFFF) != HAL_OK){
//                Error_Handler();
//             }
//             TOUCHSCREEN_CS_HIGH();
//
//            HAL_Delay(100);
//
//
//            TOUCHSCREEN_CS_LOW();
//             // read z1 position
//             TS_WriteData(0x99);
//             if(HAL_SPI_Receive(&h_touchscreen_spi,(uint8_t*)byte, 1,0xFFFF) != HAL_OK){
//                Error_Handler();
//             }
//             if(HAL_SPI_Receive(&h_touchscreen_spi,(uint8_t*)&byte[1], 1,0xFFFF) != HAL_OK){
//                Error_Handler();
//             }
//
//             uint16_t dataz2 = byte[0];
//             dataz2 <<= 8;
//             dataz2 |= byte[1];
//             dataz2 >>= 3;
//
//             TS_WriteData(0x90); // back to idle
//             if(HAL_SPI_Receive(&h_touchscreen_spi,(uint8_t*)byte, 1,0xFFFF) != HAL_OK){
//                Error_Handler();
//             }
//             if(HAL_SPI_Receive(&h_touchscreen_spi,(uint8_t*)&byte[1], 1,0xFFFF) != HAL_OK){
//                Error_Handler();
//             }
//             TOUCHSCREEN_CS_HIGH();

            //printf("X = %d, Y = %d, Z1 = %d, Z2 = %d, zdiff = %d\r\n",datax, datay,dataz1,dataz2,dataz2-dataz1);
            printf("X = %d, Y = %d\r\n",datax, datay);
        }
	for(;;);
}


void Error_Handler(void)
{
  /* Turn LED2 on */
 // BSP_LED_On(LED2);
  while(1)
  {
  }
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

