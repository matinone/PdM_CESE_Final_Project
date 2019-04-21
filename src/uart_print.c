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


/* ===== Prototypes of private functions ===== */

/*------------------------------------------------------------------
|  Function: print_single_stat
| ------------------------------------------------------------------
|  Description: prints the statistics for a single command.
|
|  Parameters:
|       stat_string - string representing the command
|       stat_value  - number of times the command was sent
|
|  Returns:  void
*-------------------------------------------------------------------*/
void print_single_stat(const char* stat_string, uint16_t stat_value);


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
    uartWriteString(UART_USB, "7 - GET_CMD_STATS\r\n");
}


void print_single_stat(const char* stat_string, uint16_t stat_value)  {
    char stat_value_string[6];  // any 16 bits value will fit here

    uartWriteString(UART_USB, stat_string);
    
    sprintf(stat_value_string, "%d \r\n", stat_value);
    uartWriteString(UART_USB, stat_value_string);
}


void print_cmd_stats(pc_command_stats_t * stats) {
    uartWriteString(UART_USB, "COMMAND STATISTICS:\r\n");

    print_single_stat("TOGGLE_LED: ", stats->toggle_led);
    print_single_stat("ECHO_ARDUINO: ", stats->echo_arduino);
    print_single_stat("CONFIG_MODE_1: ", stats->config_mode_1);
    print_single_stat("CONFIG_MODE_2: ", stats->config_mode_2);
    print_single_stat("START_PROCESS: ", stats->start_process);
    print_single_stat("GET_ARDUINO_STATE: ", stats->get_arduino_state);
    print_single_stat("READ_ADC: ", stats->read_adc);
    print_single_stat("GET_CMD_STATS: ", stats->get_cmd_stats);
    print_single_stat("INVALID_CMD: ", stats->invalid_cmd);
}