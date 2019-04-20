/* ===== [uart.h] =====
 * Copyright Matias Brignone <mnbrignone@gmail.com>
 * All rights reserved.
 *
 * Version: 0.0.1
 * Creation Date: 2019/04/07
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
	WAIT_RSP,
	CHECK_RSP
}	main_fsm_state_t;


/* ===== Prototypes of public functions ===== */
void main_fsm_init();
void main_fsm_execute();


/* ===== Avoid multiple inclusion ===== */
#endif // __MAIN_FSM_H__
