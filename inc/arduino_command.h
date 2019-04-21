/* ===== [arduino_command.h] =====
 * Copyright Matias Brignone <mnbrignone@gmail.com>
 * All rights reserved.
 *
 * Version: 0.0.1
 * Creation Date: 2019/04/20
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

/*------------------------------------------------------------------
|  Struct: arduino_cmd_t
| ------------------------------------------------------------------
|  Description: holds the relevant information for commands sent to
|				and received from the Arduino.
|
|  Members:
|		cmd 		- command to send to the Arduino
|		rsp_header	- header of the response received from the 
|					  Arduino
|		rsp 		- response status received from the Arduino
|		delay 		- delay used for the response timeout
*-------------------------------------------------------------------*/
typedef struct {
	uint8_t cmd;
	uint8_t rsp_header;
	uint8_t rsp;
	delay_t delay;
}	arduino_cmd_t;


/* ===== Prototypes of public functions ===== */

/*------------------------------------------------------------------
|  Function: reset_arduino_cmd
| ------------------------------------------------------------------
|  Description: sets the default values of the arduino_cmd_t struct.
|
|  Parameters:
|		cmd - arduino command to set
|
|  Returns:  void
*-------------------------------------------------------------------*/
void reset_arduino_cmd(arduino_cmd_t * cmd);


/*------------------------------------------------------------------
|  Function: start_arduino_timeout
| ------------------------------------------------------------------
|  Description: starts the delay (timer) used to check if there is 
|  				a timeout in the response from Arduino.
|
|  Parameters:
|		cmd - arduino command containing the delay
|
|  Returns:  void
*-------------------------------------------------------------------*/
void start_arduino_timeout(arduino_cmd_t * cmd);


/*------------------------------------------------------------------
|  Function: check_arduino_rsp
| ------------------------------------------------------------------
|  Description: checks if the response to the command sent to the
|				Arduino is ok. If the header is ok, it reads an 
				additional byte an checks that it is also ok.
|
|  Parameters:
|		cmd - arduino command to check
|
|  Returns:	RSP_OK on success
			RSP_ERROR on failure
*-------------------------------------------------------------------*/
uint8_t check_arduino_rsp(arduino_cmd_t * cmd);


/*------------------------------------------------------------------
|  Function: send_cmd_to_arduino
| ------------------------------------------------------------------
|  Description: send a command to the Arduino with a given ID.
|
|  Parameters:
|		id - id of the command to send
|
|  Returns:  void
*-------------------------------------------------------------------*/
void send_cmd_to_arduino(uint8_t id);


/* ===== Avoid multiple inclusion ===== */
#endif // __ARDUINO_COMMAND_H__
