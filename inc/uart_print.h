/* ===== [uart_print.h] =====
 * Copyright Matias Brignone <mnbrignone@gmail.com>
 * All rights reserved.
 *
 * Version: 0.0.1
 * Creation Date: 2019/04/20
 */


/* ===== Avoid multiple inclusion ===== */
#ifndef __UART_PRINT_H__
#define __UART_PRINT_H__


/* ===== Dependencies ===== */
#include "sapi.h"
#include "main_fsm.h"


/* ===== Prototypes of public functions ===== */

/*------------------------------------------------------------------
|  Function: clear_screen
| ------------------------------------------------------------------
|  Description: sends the required characters to clear the console 
				screen. 
|
|  Parameters:
|		- 
|
|  Returns:  void
*-------------------------------------------------------------------*/
void clear_screen();


/*------------------------------------------------------------------
|  Function: print_welcome_msg
| ------------------------------------------------------------------
|  Description: sends a welcome message through the UART. 
|
|  Parameters:
|		- 
|
|  Returns:  void
*-------------------------------------------------------------------*/
void print_welcome_msg();


/*------------------------------------------------------------------
|  Function: print_help
| ------------------------------------------------------------------
|  Description: prints a help message, showing the possible commands
				and a short description. 
|
|  Parameters:
|		- 
|
|  Returns:  void
*-------------------------------------------------------------------*/
void print_help();


/*------------------------------------------------------------------
|  Function: print_adc_value
| ------------------------------------------------------------------
|  Description: prints the value read from the ADC.
|
|  Parameters:
|		adc_value - value to print
|
|  Returns:  void
*-------------------------------------------------------------------*/
void print_adc_value(uint16_t adc_value);


/*------------------------------------------------------------------
|  Function: print_cmd_stats
| ------------------------------------------------------------------
|  Description: prints the statistics of the commands sent by the
|				user.
|
|  Parameters:
|		pc_command_stats - pc_command_stats_t struct holding the 
|						   statistics to print.
|
|  Returns:  void
*-------------------------------------------------------------------*/
void print_cmd_stats(pc_command_stats_t * pc_command_stats);

/* ===== Avoid multiple inclusion ===== */
#endif // __UART_PRINT_H__
