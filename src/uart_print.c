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
#define ASCII_NUMBER_OFFSET 48


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
    uartWriteString(UART_USB, "\r\n \r\n");
}

void print_error_msg()  {
    uartWriteString(UART_USB, "ERROR. Going back to initial state.\r\n");
    uartWriteString(UART_USB, "\r\n \r\n");
}

void print_help_msg()   {
    uartWriteString(UART_USB, "Options:\r\n");
    uartWriteString(UART_USB, "1 - GPIO mode.\r\n");
    uartWriteString(UART_USB, "2 - ADC mode.\r\n");
    uartWriteString(UART_USB, "\r\n \r\n");
}

void print_button_info(debounce_button_t button_array[], uint8_t n_button)  {
    for (int i=0; i<n_button; i++)  {
        uartWriteString(UART_USB, "Button State ");
        uartWriteByte(UART_USB, i + ASCII_NUMBER_OFFSET);
        if (button_array[i].state == BUTTON_UP) {
            uartWriteString(UART_USB, ": RELEASED\r\n");    
        }
        else if (button_array[i].state == BUTTON_DOWN)  {
            uartWriteString(UART_USB, ": PRESSED\r\n"); 
        }
    }
    uartWriteString(UART_USB, "\r\n");
}

void print_adc_value(uint16_t adc_value)    {
    char adc_value_string[12];  // any 32 bits value will fit here

    uartWriteString(UART_USB, "ADC Value: ");
    
    sprintf(adc_value_string, "%d", adc_value);
    uartWriteString(UART_USB, adc_value_string);
    uartWriteString(UART_USB, "\r\n");
}