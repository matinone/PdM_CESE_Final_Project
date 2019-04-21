/* ===== [uart.h] =====
 * Copyright Matias Brignone <mnbrignone@gmail.com>
 * All rights reserved.
 *
 * Version: 0.0.1
 * Creation Date: 2019/04/07
 */


/* ===== Avoid multiple inclusion ===== */
#ifndef __UART_PRINT_H__
#define __UART_PRINT_H__


/* ===== Dependencies ===== */
#include "sapi.h"


/* ===== Prototypes of public functions ===== */
void clear_screen();
void print_welcome_msg();
void print_help();
void print_adc_value(uint16_t adc_value);


/* ===== Avoid multiple inclusion ===== */
#endif // __UART_PRINT_H__
