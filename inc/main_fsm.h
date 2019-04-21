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
typedef enum {
	INITIAL,
	IDLE,
	PROCESS_CMD,
	WAIT_RSP
}	main_fsm_state_t;

typedef enum {
	TOGGLE_LED 			= '1',
	ECHO_ARDUINO 		= '2',
	CONFIG_MODE_1 		= '3',
	CONFIG_MODE_2 		= '4',
	START_PROCESS 		= '5',
	GET_ARDUINO_STATE 	= '6',
	ARDUINO_DONE 		= 'A',
}	pc_command_t;


/* ===== Prototypes of public functions ===== */
void main_fsm_init();
void main_fsm_execute();


/* ===== Avoid multiple inclusion ===== */
#endif // __MAIN_FSM_H__
