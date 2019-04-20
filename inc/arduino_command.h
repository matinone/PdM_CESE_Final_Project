/* ===== [uart.h] =====
 * Copyright Matias Brignone <mnbrignone@gmail.com>
 * All rights reserved.
 *
 * Version: 0.0.1
 * Creation Date: 2019/04/07
 */


/* ===== Avoid multiple inclusion ===== */
#ifndef __ARDUINO_COMMAND_H__
#define __ARDUINO_COMMAND_H__


/* ===== Dependencies ===== */
#include "sapi.h"


/* ===== Macros of public constants ===== */
#define ARDUINO_TIMEOUT 2000
#define RSP_OK 1
#define RSP_ERROR 0

/* ===== Public structs and enums ===== */
typedef struct {
	uint8_t cmd;
	uint8_t rsp_header;
	uint8_t rsp;
	delay_t delay;
}	arduino_cmd_t;


/* ===== Prototypes of public functions ===== */
void reset_arduino_cmd(arduino_cmd_t * cmd);
void start_arduino_timeout(arduino_cmd_t * cmd);
uint8_t check_arduino_rsp(arduino_cmd_t * cmd);


/* ===== Avoid multiple inclusion ===== */
#endif // __ARDUINO_COMMAND_H__
