/* ===== [main_fsm.h] =====
 * Copyright Matias Brignone <mnbrignone@gmail.com>
 * All rights reserved.
 *
 * Version: 0.0.1
 * Creation Date: 2019/04/20
 */


/* ===== Avoid multiple inclusion ===== */
#ifndef __MAIN_FSM_H__
#define __MAIN_FSM_H__


/* ===== Dependencies ===== */
#include "sapi.h"


/* ===== Public structs and enums ===== */

/*------------------------------------------------------------------
|  Enum: main_fsm_state_t
| ------------------------------------------------------------------
|  Description: holds the states for the main program FSM.
|
|  Values:
|		INITIAL		- initial state, unconditional transition to 
|					  IDLE after reset
|		IDLE		- waiting for commands from User or Arduino 
|		PROCESS_CMD	- processing the received command, according to 
|					  pc_command_t enum
|		WAIT_RSP 	- waiting for a response from Arduino
*-------------------------------------------------------------------*/
typedef enum {
	INITIAL,
	IDLE,
	PROCESS_CMD,
	WAIT_RSP
}	main_fsm_state_t;


/*------------------------------------------------------------------
|  Enum: pc_command_t
| ------------------------------------------------------------------
|  Description: holds the values of the valid commands that can be
				received.
|
|  Values:
|		TOGGLE_LED			- toggle LEDB in EDU-CIAA
|		ECHO_ARDUINO		- send message to Arduino and wait for
							  positive answer 
|		CONFIG_MODE_1 		- configure Arduino in Mode 1
|		CONFIG_MODE_2 		- configure Arduino in Mode 2
|		START_PROCESS		- start process in Arduino
|		GET_ARDUINO_STATE	- get Arduino FSM state
|		READ_ADC			- read ADC value in EDU-CIAA 
|		ARDUINO_DONE		- Arduino finish processing
*-------------------------------------------------------------------*/
typedef enum {
	TOGGLE_LED 			= '0',
	ECHO_ARDUINO 		= '1',
	CONFIG_MODE_1 		= '2',
	CONFIG_MODE_2 		= '3',
	START_PROCESS 		= '4',
	GET_ARDUINO_STATE 	= '5',
	READ_ADC			= '6',
	ARDUINO_DONE 		= 'A',
}	pc_command_t;


/*------------------------------------------------------------------
|  Struct: pc_command_stats_t
| ------------------------------------------------------------------
|  Description: holds the number of times each command is sent by
|				the user.
|
|  Members:
|		toggle_led 			- number of TOGGLE_LED received
|		echo_arduino 		- number of ECHO_ARDUINO received
|		config_mode_1 		- number of CONFIG_MODE_1 received
|		config_mode_2 		- number of CONFIG_MODE_2 received
|		start_process 		- number of START_PROCESS received
|		get_arduino_state 	- number of GET_ARDUINO_STATE received
|		read_adc 			- number of READ_ADC received
*-------------------------------------------------------------------*/
typedef struct {
	uint16_t toggle_led;
	uint16_t echo_arduino;
	uint16_t config_mode_1;
	uint16_t config_mode_2;
	uint16_t start_process;
	uint16_t get_arduino_state;
	uint16_t read_adc;
	uint16_t invalid_cmd;
}	pc_command_stats_t;



/* ===== Prototypes of public functions ===== */

/*------------------------------------------------------------------
|  Function: main_fsm_init
| ------------------------------------------------------------------
|  Description: sets the initial state of the main program FSM and
|				performs the following actions:
|				- Configure UART.
|				- Reset current command.
|				- Clear PC command statistics.
|				- Clear LEDB.
|				- Enable ADC.
|
|  Parameters:
|		-
|
|  Returns:  void
*-------------------------------------------------------------------*/
void main_fsm_init();


/*------------------------------------------------------------------
|  Function: main_fsm_execute
| ------------------------------------------------------------------
|  Description: controls the execution of the main program. It 
|				handles the command transmission/reception and 
|				performs the requested actions.
|
|  Parameters:
|		- 
|
|  Returns:  void
*-------------------------------------------------------------------*/
void main_fsm_execute();


/* ===== Avoid multiple inclusion ===== */
#endif // __MAIN_FSM_H__
