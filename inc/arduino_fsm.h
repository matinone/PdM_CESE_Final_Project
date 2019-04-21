/* ===== [uart.h] =====
 * Copyright Matias Brignone <mnbrignone@gmail.com>
 * All rights reserved.
 *
 * Version: 0.0.1
 * Creation Date: 2019/04/07
 */


/* ===== Avoid multiple inclusion ===== */
#ifndef __ARDUINO_FSM_H__
#define __ARDUINO_FSM_H__


/* ===== Dependencies ===== */
#include "sapi.h"
#include "arduino_command.h"


/* ===== Public structs and enums ===== */
typedef enum {
	ARDUINO_IDLE,
	ARDUINO_MODE_1,
	ARDUINO_MODE_2,
	ARDUINO_WORKING
}	arduino_fsm_state_t;


/* ===== Prototypes of public functions ===== */
void arduino_fsm_init();
void update_arduino_fsm(arduino_cmd_t * cmd);
void change_arduino_state();
arduino_fsm_state_t get_arduino_fsm_state();


/* ===== Avoid multiple inclusion ===== */
#endif // __ARDUINO_FSM_H__
