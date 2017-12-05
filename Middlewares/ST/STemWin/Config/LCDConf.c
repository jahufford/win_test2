/*********************************************************************
*          Portions COPYRIGHT 2016 STMicroelectronics                *
*          Portions SEGGER Microcontroller GmbH & Co. KG             *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.32 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The  software has  been licensed  to STMicroelectronics International
N.V. a Dutch company with a Swiss branch and its headquarters in Plan-
les-Ouates, Geneva, 39 Chemin du Champ des Filles, Switzerland for the
purposes of creating libraries for ARM Cortex-M-based 32-bit microcon_
troller products commercialized by Licensee only, sublicensed and dis_
tributed under the terms and conditions of the End User License Agree_
ment supplied by STMicroelectronics International N.V.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCDConf_FlexColor_Template.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

/**
  ******************************************************************************
  * @attention
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#include "stm32f4xx_hal.h"
#include "GUI.h"
#include "GUIDRV_FlexColor.h"
#include "ili9341.h"
#include "lcd_hardware.h"

SPI_HandleTypeDef  h_lcd_spi;
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

//void LCD_Set8Bit(void);
//void LCD_Set16Bit(void);
//void LCD_Hardware_Init(void);
//void LCD_Module_Init();
/*********************************************************************
*
*       Layer configuration (to be modified)
*
**********************************************************************
*/

//
// Physical display size
//
#define XSIZE_PHYS  240 // To be adapted to x-screen size
#define YSIZE_PHYS  320 // To be adapted to y-screen size

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   GUICC_565
  #error Color conversion not defined!
#endif
#ifndef   GUIDRV_FLEXCOLOR
  #error No display driver defined!
#endif

// Color conversion
//
//#define COLOR_CONVERSION GUICC_565
//#define COLOR_CONVERSION GUICC_M565
#define COLOR_CONVERSION GUICC_565

//
// Display driver
//
#define DISPLAY_DRIVER GUIDRV_FLEXCOLOR

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/
/********************************************************************
*
*       LCD_WriteReg
*
* Function description:
*   Sets display register
*/
//static void LCD_WriteReg(U16 Data) {
//  // ... TBD by user
//  uint8_t byte = (uint8_t)Data;
//  LCD_DC_LOW();
//  LCD_CS_LOW();
//  if(HAL_SPI_Transmit(&h_lcd_spi,&byte, 1,0xFFFF) != HAL_OK){
//    Error_Handler();
//    }
//  LCD_CS_HIGH();
//}

/********************************************************************
*
*       LcdWriteData
*
* Function description:
*   Writes a value to a display register
*/
static void LcdWriteData(U16 Data) {
  // ... TBD by user
	uint8_t *p = (uint8_t*)&Data;
	LCD_CS_LOW();
	LCD_DC_HIGH();
	if(Data&0xFF00){
      if(HAL_SPI_Transmit(&h_lcd_spi,(uint8_t*)(p+1), 1,0xFFFF) != HAL_OK){
        Error_Handler();
      }
      if(HAL_SPI_Transmit(&h_lcd_spi,(uint8_t*)(p), 1,0xFFFF) != HAL_OK){
        Error_Handler();
      }
	}else{
      if(HAL_SPI_Transmit(&h_lcd_spi,(uint8_t*)&Data, 1,0xFFFF) != HAL_OK){
        Error_Handler();
      }
	}
	LCD_CS_HIGH();
}
//static void LCD_WriteByte(uint8_t Data) {
//  // ... TBD by user
//	LCD_CS_LOW();
//	LCD_DC_HIGH();
//	if(HAL_SPI_Transmit(&h_lcd_spi,(uint8_t*)&Data, 1,0xFFFF) != HAL_OK){
//		Error_Handler();
//    }
//	LCD_CS_HIGH();
//}
/********************************************************************
*
*       LcdWriteDataMultiple
*
* Function description:
*   Writes multiple values to a display register.
*/
static void LcdWriteDataMultiple(U16 * pData, int NumItems) {
	uint8_t *p = (uint8_t*)pData;
  LCD_CS_LOW();
  LCD_DC_HIGH();
  while (NumItems--) {
    // ... TBD by user

	if(HAL_SPI_Transmit(&h_lcd_spi,(uint8_t*)(p+1), 1,0xFFFF) != HAL_OK){
		//Error_Handler();
    }
	if(HAL_SPI_Transmit(&h_lcd_spi,(uint8_t*)(p), 1,0xFFFF) != HAL_OK){
		//Error_Handler();
    }
	pData++;
  }
  LCD_CS_HIGH();
}

/********************************************************************
*
*       LcdReadDataMultiple
*
* Function description:
*   Reads multiple values from a display register.
*/
static void LcdReadDataMultiple(U16 * pData, int NumItems) {
  while (NumItems--) {
    // ... TBD by user
  }
}

/*********************************************************************
*
*       Public functions
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Function description:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*
*/
void LCD_X_Config(void) {
  GUI_DEVICE * pDevice;
  CONFIG_FLEXCOLOR Config = {0};
  GUI_PORT_API PortAPI = {0};
  //
  // Set display driver and color conversion
  //
  //pDevice = GUI_DEVICE_CreateAndLink(GUIDRV_FLEXCOLOR, GUICC_565, 0, 0);
  //pDevice = GUI_DEVICE_CreateAndLink(GUIDRV_FLEXCOLOR, GUICC_M565, 0, 0);
  pDevice = GUI_DEVICE_CreateAndLink(GUIDRV_FLEXCOLOR, COLOR_CONVERSION, 0, 0);

  //
  // Display driver configuration, required for Lin-driver
  //
  LCD_SetSizeEx (0, XSIZE_PHYS , YSIZE_PHYS);
  LCD_SetVSizeEx(0, VXSIZE_PHYS, VYSIZE_PHYS);
  //
  // Orientation
  //
  //Config.Orientation = GUI_SWAP_XY | GUI_MIRROR_Y;
  Config.Orientation = GUI_SWAP_XY;

  GUIDRV_FlexColor_Config(pDevice, &Config);
  //
  // Set controller and operation mode
  //
  PortAPI.pfWrite16_A0  = LCD_WriteReg;
  PortAPI.pfWrite16_A1  = LcdWriteData;
  PortAPI.pfWriteM16_A1 = LcdWriteDataMultiple;
  PortAPI.pfReadM16_A1  = LcdReadDataMultiple;

  //GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66708, GUIDRV_FLEXCOLOR_M16C0B16);
  GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66709, GUIDRV_FLEXCOLOR_M16C0B16);
  //GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66709, GUIDRV_FLEXCOLOR_M16C1B8);

}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Function description:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;
  (void) LayerIndex;
  (void) pData;
  
  switch (Cmd) {
  case LCD_X_INITCONTROLLER: {
    //
    // Called during the initialization process in order to set up the
    // display controller and put it into operation. If the display
    // controller is not initialized by any external routine this needs
    // to be adapted by the customer...
    //
    // ...
	  //LCD_Set16Bit();
	  LCD_Hardware_Init();
	  LCD_Module_Init();
    return 0;
  }
  default:
    r = -1;
  }
  return r;
}
//void LCD_Set8Bit(){
//  	h_lcd_spi.Init.DataSize = SPI_DATASIZE_8BIT;
//    if(HAL_SPI_Init(&h_lcd_spi) != HAL_OK){
//    	//Error_Handler();
//    }
//}
//void LCD_Set16Bit(){
//  	h_lcd_spi.Init.DataSize = SPI_DATASIZE_16BIT;
//    if(HAL_SPI_Init(&h_lcd_spi) != HAL_OK){
//    	//Error_Handler();
//    }
//}


//void LCD_Hardware_Init(void)
//{
//	__HAL_RCC_GPIOA_CLK_ENABLE();
//	__HAL_RCC_GPIOB_CLK_ENABLE();
//	__HAL_RCC_GPIOC_CLK_ENABLE();
//    // set up LCD SPI ports and pins
//    // SPI SCK
//	GPIO_InitTypeDef GPIO_InitStruct;
//    GPIO_InitStruct.Pin = LCD_SPI_SCK_PIN;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
//    HAL_GPIO_Init(LCD_SPI_SCK_PORT, &GPIO_InitStruct);
//
//    // SPI MISO
//    GPIO_InitStruct.Pin = LCD_SPI_MISO_PIN;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
//    GPIO_InitStruct.Pull = GPIO_PULLUP;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
//    HAL_GPIO_Init(LCD_SPI_MISO_PORT, &GPIO_InitStruct);
//
//    // SPI MOSI
//    GPIO_InitStruct.Pin = LCD_SPI_MOSI_PIN;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
//    HAL_GPIO_Init(LCD_SPI_MOSI_PORT, &GPIO_InitStruct);
//
//    // SPI NSS
//    GPIO_InitStruct.Pin = LCD_SPI_NSS_PIN;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    //GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
//    HAL_GPIO_Init(LCD_SPI_NSS_PORT, &GPIO_InitStruct);
//   	HAL_GPIO_WritePin(LCD_SPI_NSS_PORT,LCD_SPI_NSS_PIN,GPIO_PIN_SET);
//
//   	// SPI D/C
//   	GPIO_InitStruct.Pin = LCD_SPI_DC_PIN;
//   	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//   	GPIO_InitStruct.Pull = GPIO_NOPULL;
//   	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//   	HAL_GPIO_Init(LCD_SPI_DC_PORT, &GPIO_InitStruct);
//
//   	// LCD Reset
//   	GPIO_InitStruct.Pin = LCD_RESET_PIN;
//   	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//   	GPIO_InitStruct.Pull = GPIO_NOPULL;
//   	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//   	HAL_GPIO_Init(LCD_RESET_PORT, &GPIO_InitStruct);
//   	HAL_GPIO_WritePin(LCD_RESET_PORT, LCD_RESET_PIN,GPIO_PIN_SET);
//    //toggle reset
//    HAL_Delay(150);
//    HAL_GPIO_WritePin(LCD_RESET_PORT, LCD_RESET_PIN,GPIO_PIN_SET);
//    HAL_Delay(15);
//    HAL_GPIO_WritePin(LCD_RESET_PORT, LCD_RESET_PIN,GPIO_PIN_RESET);
//    HAL_Delay(30);
//    HAL_GPIO_WritePin(LCD_RESET_PORT, LCD_RESET_PIN,GPIO_PIN_SET);
//    HAL_Delay(150);
//
//
//    LCD_SPI_CLK_ENABLE();
//
//    h_lcd_spi.Instance = LCD_SPIx;
//    h_lcd_spi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
//    //h_lcd_spi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
//    h_lcd_spi.Init.CLKPhase = SPI_PHASE_1EDGE;
//    h_lcd_spi.Init.CLKPolarity = SPI_POLARITY_LOW; // might need to be high with 2nd edge
//    h_lcd_spi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
//    h_lcd_spi.Init.CRCPolynomial;
//    h_lcd_spi.Init.DataSize = SPI_DATASIZE_8BIT;
//    h_lcd_spi.Init.Direction = SPI_DIRECTION_2LINES;
//    h_lcd_spi.Init.FirstBit = SPI_FIRSTBIT_MSB;
//    h_lcd_spi.Init.Mode = SPI_MODE_MASTER;
//    h_lcd_spi.Init.NSS = SPI_NSS_HARD_OUTPUT;
//    //h_lcd_spi.Init.NSS = SPI_NSS_SOFT;
//    h_lcd_spi.Init.TIMode = SPI_TIMODE_DISABLE;
//    h_lcd_spi.State = HAL_SPI_STATE_RESET;
//
//    if(HAL_SPI_Init(&h_lcd_spi) != HAL_OK){
//    	//Error_Handler();
//    }
//}

//void LCD_Module_Init()
//{
//	// adapted from Seed Technology graphics library, by Alber. Miao  Loovee, Viswewara
//	// who go the initialization code from a TFT vendor
//    LCD_WriteReg(LCD_POWERA);
//    LCD_WriteByte(0x39); // these values are straight from the datasheet
//    LCD_WriteByte(0x2C);
//    LCD_WriteByte(0x00);
//    LCD_WriteByte(0x34);// 1.6 volts for  Vcore
//    LCD_WriteByte(0x02);// 5.6 volts for DDVHD
//
//    LCD_WriteReg(LCD_POWERB);
//    LCD_WriteByte(0x00);
//    LCD_WriteByte(0XC1);
//    LCD_WriteByte(0X30); // discharge path is enabled
//
//    LCD_WriteReg(LCD_DTCA); // these values are different than the datasheet
//    LCD_WriteByte(0x85);
//    LCD_WriteByte(0x00);
//    LCD_WriteByte(0x78);
////    LcdWriteData(0x84);
////    LcdWriteData(0x11);
////    LcdWriteData(0x7A);
//
//
//    LCD_WriteReg(LCD_DTCB);
//    LCD_WriteByte(0x00);
//    //LcdWriteData(0x66);
//    LCD_WriteByte(0x00);
//
//    LCD_WriteReg(LCD_POWER_SEQ);
//    LCD_WriteByte(0x64);
//    LCD_WriteByte(0x03);
//    LCD_WriteByte(0X12);
//    LCD_WriteByte(0X81);
//
//    LCD_WriteReg(LCD_PRC);
//    LCD_WriteByte(0x20);
//
//    LCD_WriteReg(0xC0);    	//Power control
//    LCD_WriteByte(0x23);   	//VRH[5:0] 4.6V
//
//    LCD_WriteReg(0xC1);    	//Power control
//    LCD_WriteByte(0x10);   	//SAP[2:0];BT[3:0]
//
//    LCD_WriteReg(0xC5);    	//VCM control
//    LCD_WriteByte(0x3e);   	//Contrast 5.85
//    LCD_WriteByte(0x28);    //-1.5
//
//    LCD_WriteReg(0xC7);    	//VCM control2
//    LCD_WriteByte(0x86);  	 //--
//    //LcdWriteData(0xC0);  	 //--
//
//    LCD_WriteReg(0x36);    	// Memory Access Control
//    //LcdWriteData(0x48);  	//C8
//    LCD_WriteByte(0x28); // row/column exchange, I'm using the module in a
//    					 // horizontal orientation, with the top left corner
//    					 // being x=0 y=0
//    //LCD_WriteByte(0x20);
//    //LcdWriteData(0x3C); // row/column exchange, I'm using the module in a
//
//    LCD_WriteReg(0xF6); // Interface control
//    LCD_WriteByte(0x01);
//    LCD_WriteByte(0x00);
//    LCD_WriteByte(0x01);
//
//    LCD_WriteReg(0x3A); // COLMOD: Pixel Format Set
//    LCD_WriteByte(0x55);// 16 bits/pixel. RGB and MCU interface format
//
//    LCD_WriteReg(0xB0); // RGB interface control
//    LCD_WriteByte(0xC0);
//
//    LCD_WriteReg(0xB1); // Frame Rate Control
//    //LcdWriteData(0x00);
//    LCD_WriteByte(0x00);
//    //LcdWriteData(0x18);// 79Hz. datasheet default is 70Hz, 0x1B
//    LCD_WriteByte(0x1F);
//
//    LCD_WriteReg(0xB6);    	// Display Function Control
//    LCD_WriteByte(0x08);
//    LCD_WriteByte(0x82);
//    LCD_WriteByte(0x27);
//
//    LCD_WriteReg(0xF2);    	// 3Gamma Function Disable
//    LCD_WriteByte(0x00);
//
//    LCD_WriteReg(0x26);    	//Gamma curve selected
//    LCD_WriteByte(0x01);
//
//    LCD_WriteReg(0xE0);    	//Set Gamma
//    LCD_WriteByte(0x0F);
//    LCD_WriteByte(0x31);
//    LCD_WriteByte(0x2B);
//    LCD_WriteByte(0x0C);
//    LCD_WriteByte(0x0E);
//    LCD_WriteByte(0x08);
//    LCD_WriteByte(0x4E);
//    LCD_WriteByte(0xF1);
//    LCD_WriteByte(0x37);
//    LCD_WriteByte(0x07);
//    LCD_WriteByte(0x10);
//    LCD_WriteByte(0x03);
//    LCD_WriteByte(0x0E);
//    LCD_WriteByte(0x09);
//    LCD_WriteByte(0x00);
//
//    LCD_WriteReg(0XE1);    	//Set Gamma
//    LCD_WriteByte(0x00);
//    LCD_WriteByte(0x0E);
//    LCD_WriteByte(0x14);
//    LCD_WriteByte(0x03);
//    LCD_WriteByte(0x11);
//    LCD_WriteByte(0x07);
//    LCD_WriteByte(0x31);
//    LCD_WriteByte(0xC1);
//    LCD_WriteByte(0x48);
//    LCD_WriteByte(0x08);
//    LCD_WriteByte(0x0F);
//    LCD_WriteByte(0x0C);
//    LCD_WriteByte(0x31);
//    LCD_WriteByte(0x36);
//    LCD_WriteByte(0x0F);
//
//    LCD_WriteReg(0x11);    	//Exit Sleep
//    HAL_Delay(120);
//
//    LCD_WriteReg(0x34);
//    LCD_WriteByte(0x01);
//
//    LCD_WriteReg(0x29);    //Display on
//    LCD_WriteReg(0x2c);
////-------------------------------
//	LCD_WriteReg(LCD_COLUMN_ADDR);
//	LCD_DC_HIGH();
//	LCD_CS_LOW();
//	LCD_WriteByte(0);
//	LCD_WriteByte(0);
//	//LCD_WriteWord(0);
//	//LCD_WriteWord(319);
//	LCD_WriteByte(319>>8);
//	LCD_WriteByte((uint8_t)319);
//	LCD_CS_HIGH();
//
//	LCD_WriteReg(LCD_PAGE_ADDR);
//	LCD_DC_HIGH();
//	LCD_CS_LOW();
//	//LCD_WriteWord(0);
//	LCD_WriteByte(0);
//	LCD_WriteByte(0);
//	//LCD_WriteWord(239);
//	LCD_WriteByte(239>>8);
//	LCD_WriteByte((uint8_t)239);
//	LCD_CS_HIGH();
//
//	LCD_WriteReg(LCD_GRAM);
//
//    LCD_FillScreen2(0x00FF);
//    asm("nop");
//    HAL_Delay(500);
//}
void LCD_FillScreen2(uint16_t color)
{
	uint32_t varr = 0xFF;
//	// weak-ass sychronization attempt, at least make the tearing lines be stable
//	while(varr>1){
//      varr = LCD_ReadData(0x45,2);
//      //varr >>= 16;
//      asm("nop");
//	}
	uint8_t burst = 160;
	//uint8_t burst = 2;
	uint32_t color32[burst/2];
	for(uint8_t i=0;i<(burst/2);i++){
      color32[i] = color;
      color32[i] <<=16;
      color32[i] |= color;
	}
	LCD_WriteReg(LCD_COLUMN_ADDR);
	LCD_DC_HIGH();
	LCD_CS_LOW();
	LCD_WriteByte(0);
	LCD_WriteByte(0);
	//LCD_WriteWord(0);
	//LCD_WriteWord(319);
	LCD_WriteByte(319>>8);
	LCD_WriteByte((uint8_t)319);
	LCD_CS_HIGH();

	LCD_WriteReg(LCD_PAGE_ADDR);
	LCD_DC_HIGH();
	LCD_CS_LOW();
	//LCD_WriteWord(0);
	LCD_WriteByte(0);
	LCD_WriteByte(0);
	//LCD_WriteWord(239);
	LCD_WriteByte(239>>8);
	LCD_WriteByte((uint8_t)239);
	LCD_CS_HIGH();

	LCD_WriteReg(LCD_GRAM);

  	h_lcd_spi.Init.DataSize = SPI_DATASIZE_16BIT;
    if(HAL_SPI_Init(&h_lcd_spi) != HAL_OK){
    }
    LCD_DC_HIGH();
    LCD_CS_LOW();
  	uint8_t data = 1;
  	int8_t incr = 1;
    for(uint32_t i=0; i<320*240/burst; i++)
    {
    //	LCD_WriteWord(color);
    	//transmit function can transfer 80 bits at a time, 5 words (5*16)
    	if(HAL_SPI_Transmit(&h_lcd_spi,(uint8_t*)&color32[0], burst,0xFFFF) != HAL_OK){
          Error_Handler();
        }
    	//LCD_WriteByte(data);
    	//LCD_WriteByte(data);
//    	data += incr;
//    	if(data == limit){
//    		incr = -1;
//    	}
//    	if(data == 0){
//    		incr = 1;
//    	}
    }
    LCD_CS_HIGH();
	h_lcd_spi.Init.DataSize = SPI_DATASIZE_8BIT;
    if(HAL_SPI_Init(&h_lcd_spi) != HAL_OK){

    }

}

/*************************** End of file ****************************/

