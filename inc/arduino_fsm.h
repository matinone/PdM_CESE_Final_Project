/* ===== [arduino_fsm.h] =====
 * Copyright Matias Brignone <mnbrignone@gmail.com>
 * All rights reserved.
 *
 * Version: 0.0.1
 * Creation Date: 2019/04/20
 */


/* ===== Avoid multiple inclusion ===== */
#ifndef __ARDUINO_FSM_H__
#define __ARDUINO_FSM_H__


/* ===== Dependencies ===== */
#include "sapi.h"
#include "arduino_command.h"


/* ===== Public structs and enums ===== */

/*------------------------------------------------------------------
|  Enum: arduino_fsm_state_t
| ------------------------------------------------------------------
|  Description: holds the states for the Arduino Finite State
|				Machine (FSM).
|
|  Values:
|		ARDUINO_IDLE	- Arduino idle, waiting for commands
|		ARDUINO_MODE_1	- Arduino configured in Mode 1 
|		ARDUINO_MODE_2 	- Arduino configured in Mode 2
|		ARDUINO_WORKING - Arduino is executing certain action
*-------------------------------------------------------------------*/
typedef enum {
	ARDUINO_IDLE,
	ARDUINO_MODE_1,
	ARDUINO_MODE_2,
	ARDUINO_WORKING
}	arduino_fsm_state_t;


/* ===== Prototypes of public functions ===== */

/*------------------------------------------------------------------
|  Function: arduino_fsm_init
| ------------------------------------------------------------------
|  Description: sets the initial state of the Arduino FSM.
|
|  Parameters:
|		-
|
|  Returns:  void
*-------------------------------------------------------------------*/
void arduino_fsm_init();


/*------------------------------------------------------------------
|  Function: update_arduino_fsm
| ------------------------------------------------------------------
|  Description: sets the next state of the Arduino FSM according to
|				the values in cmd.
|
|  Parameters:
|		cmd - Arduino command used to set the next state 
|
|  Returns:  void
*-------------------------------------------------------------------*/
void update_arduino_fsm(arduino_cmd_t * cmd);


/*------------------------------------------------------------------
|  Function: change_arduino_state
| ------------------------------------------------------------------
|  Description: changes the state of the Arduino FSM from 
|				ARDUINO_WORKING to ARDUINO_IDLE. 
|
|  Parameters:
|		- 
|
|  Returns:  void
*-------------------------------------------------------------------*/
void change_arduino_state();


/*------------------------------------------------------------------
|  Function: get_arduino_fsm_state
| ------------------------------------------------------------------
|  Description: getter for the current state of the Arduino FSM.
|
|  Parameters:
|		- 
|
|  Returns:  state of the Arduino FSM
*-------------------------------------------------------------------*/
arduino_fsm_state_t get_arduino_fsm_state();


/*------------------------------------------------------------------
|  Function: arduino_fsm_translate
| ------------------------------------------------------------------
|  Description: returns a string representing the state of the
|				Arduino FSM.
|
|  Parameters:
|		state - Arduino FSM state to translate
|
|  Returns:  string with the translated state
*-------------------------------------------------------------------*/
char * arduino_fsm_translate(arduino_fsm_state_t state);


/* ===== Avoid multiple inclusion ===== */
#endif // __ARDUINO_FSM_H__
