/*
 * debug_serial_port.h
 *
 *  Created on: Dec 6, 2017
 *      Author: joe
 */

#ifndef DEBUG_SERIAL_PORT_H_
#define DEBUG_SERIAL_PORT_H_

#include "stm32f4xx.h"

extern UART_HandleTypeDef h_debug_uart;

#ifdef __GNUC__
  /* With GCC, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

#endif /* DEBUG_SERIAL_PORT_H_ */
