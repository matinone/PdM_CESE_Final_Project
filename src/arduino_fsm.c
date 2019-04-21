/* ===== [debounce.c] =====
 * Copyright Matias Brignone <mnbrignone@gmail.com>
 * All rights reserved.
 *
 * Version: 0.0.1
 * Creation Date: 2019/04/07
 */


/* ===== Dependencies ===== */
#include "arduino_fsm.h"
#include "arduino_command.h"
#include "main_fsm.h"


/* ===== Macros of private constants ===== */



/* ===== Declaration of private variables ===== */
static arduino_fsm_state_t arduino_fsm_state;


/* ===== Prototypes of private functions ===== */


/* ===== Implementations of public functions ===== */
void arduino_fsm_init() {
    arduino_fsm_state = ARDUINO_IDLE;
}

void update_arduino_fsm(arduino_cmd_t * cmd)    {
    switch (cmd->cmd)   {
        case CONFIG_MODE_1:
            arduino_fsm_state = ARDUINO_MODE_1;
            uartWriteString(UART_USB, "Arduino FSM changed to MODE 1.\r\n");
            break;
        case CONFIG_MODE_2:
            arduino_fsm_state = ARDUINO_MODE_2;
            uartWriteString(UART_USB, "Arduino FSM changed to MODE 2.\r\n");
            break;
        case START_PROCESS:
            arduino_fsm_state = ARDUINO_WORKING;
            uartWriteString(UART_USB, "Arduino FSM changed to WORKING.\r\n");
            break;
    }
}

void change_arduino_state() {
    if (arduino_fsm_state == ARDUINO_WORKING)   {
        arduino_fsm_state = ARDUINO_IDLE;
    }
}

arduino_fsm_state_t get_arduino_fsm_state() {
    return arduino_fsm_state;
}


char * arduino_fsm_translate(arduino_fsm_state_t state) {
    switch(state)   {
        case ARDUINO_IDLE:
            return "IDLE";
        case ARDUINO_MODE_1:
            return "MODE 1";
        case ARDUINO_MODE_2:
            return "MODE 2";
        case ARDUINO_WORKING:
            return "WORKING";
        default:
            return "INVALID";
    }
}


/* ===== Implementations of private functions ===== */

