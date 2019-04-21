/* ===== [debounce.c] =====
 * Copyright Matias Brignone <mnbrignone@gmail.com>
 * All rights reserved.
 *
 * Version: 0.0.1
 * Creation Date: 2019/04/07
 */


/* ===== Dependencies ===== */
#include "uart_print.h"


/* ===== Macros of private constants ===== */


/* ===== Implementations of public functions ===== */

void clear_screen() {
    uartWriteByte(UART_USB, 27);
    uartWriteString(UART_USB, "[2J");
    uartWriteByte(UART_USB, 27);
    uartWriteString(UART_USB, "[H");
}

void print_welcome_msg() {
    uartWriteString(UART_USB, "***** WELCOME TO THE SYSTEM *****\r\n");
    uartWriteString(UART_USB, "By Matias Brignone\r\n");
}


void print_adc_value(uint16_t adc_value)    {
    char adc_value_string[12];  // any 32 bits value will fit here

    uartWriteString(UART_USB, "ADC Value: ");
    
    sprintf(adc_value_string, "%d \r\n", adc_value);
    uartWriteString(UART_USB, adc_value_string);
}

void print_help()   {
    uartWriteString(UART_USB, "OPTIONS:\r\n");
    uartWriteString(UART_USB, "0 - TOGGLE_LED\r\n");
    uartWriteString(UART_USB, "1 - ECHO_ARDUINO\r\n");
    uartWriteString(UART_USB, "2 - CONFIG_MODE_1\r\n");
    uartWriteString(UART_USB, "3 - CONFIG_MODE_2\r\n");
    uartWriteString(UART_USB, "4 - START_PROCESS\r\n");
    uartWriteString(UART_USB, "5 - GET_ARDUINO_STATE\r\n");
    uartWriteString(UART_USB, "6 - READ_ADC\r\n");
}