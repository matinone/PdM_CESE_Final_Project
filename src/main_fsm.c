/* ===== [debounce.c] =====
 * Copyright Matias Brignone <mnbrignone@gmail.com>
 * All rights reserved.
 *
 * Version: 0.0.1
 * Creation Date: 2019/04/07
 */


/* ===== Dependencies ===== */
#include "main_fsm.h"
#include "arduino_command.h"
#include "uart_print.h"


/* ===== Macros of private constants ===== */
#define PROCESS_DELAY 10
#define BAUD_RATE 115200
// #define ASCII_OFFSET 48


/* ===== Declaration of private variables ===== */
static main_fsm_state_t main_fsm_state;
static delay_t process_delay;
static arduino_cmd_t current_cmd; 


/* ===== Prototypes of private functions ===== */


/* ===== Implementations of public functions ===== */

void main_fsm_init ()   {
    uartConfig(UART_USB, BAUD_RATE);                    // config uart
    
    delayConfig(&process_delay, PROCESS_DELAY);         // config delay for the main FSM
    main_fsm_state = INITIAL;                           // set main fsm initial state
    
    reset_arduino_cmd(&current_cmd);
    gpioWrite(LEDB, OFF);
}

// FSM Execute Function
void main_fsm_execute ()    {
    static uint8_t received_byte;
    
    if (delayRead(&process_delay)) {

        uint8_t rsp_status;

        switch(main_fsm_state)   {

            case INITIAL:
                print_welcome_msg();
                main_fsm_state = IDLE;
                break;

            case IDLE:
                if (uartReadByte(UART_USB, &received_byte)) {
                    main_fsm_state = PROCESS_CMD;
                }
                break;

            case PROCESS_CMD:
                switch (received_byte)  {
                    case TOGGLE_LED:
                        uartWriteString(UART_USB, "Command 1 received - toggle EDU-CIAA LEDB.\r\n");
                        gpioToggle(LEDB);
                        main_fsm_state = IDLE;
                        break;

                    case ECHO_ARDUINO:
                        uartWriteString(UART_USB, "Command 2 received - echo to Arduino.\r\n");
                        //send_command_to_arduino(received_byte);
                        uartWriteString(UART_USB, "A_1\r\n");

                        reset_arduino_cmd(&current_cmd);
                        current_cmd.cmd = received_byte;
                        start_arduino_timeout(&current_cmd);

                        main_fsm_state = WAIT_RSP;
                        break;

                    case ARDUINO_DONE:
                        reset_arduino_cmd(&current_cmd);
                        current_cmd.rsp_header = ARDUINO_DONE;
                        rsp_status = check_arduino_rsp(&current_cmd);

                        if (rsp_status == RSP_OK) {
                            uartWriteString(UART_USB, "Arduino finished its process. Updating Arduino FSM.\r\n");
                            // change_arduino_state();
                        }
                        else {
                            uartWriteString(UART_USB, "ERROR: Arduino tried to update its state, but response was NOT OK.\r\n");
                        }
                        
                        main_fsm_state = IDLE;
                        break;

                    default:
                        uartWriteString(UART_USB, "ERROR: Invalid command received.\r\n");
                        main_fsm_state = IDLE;
                }
                break;

            case WAIT_RSP:
            
                if (uartReadByte(UART_USB, &(current_cmd.rsp_header))) {
                    rsp_status = check_arduino_rsp(&current_cmd);

                    if (rsp_status == RSP_OK)   {
                        // update_arduino_fsm(&current_cmd);
                        uartWriteString(UART_USB, "Arduino response OK.\r\n");
                    }
                    else {
                        uartWriteString(UART_USB, "ERROR: Arduino response NOT OK, could not process command.\r\n");
                    }

                    main_fsm_state = IDLE;
                }

                if (delayRead(&(current_cmd.delay)))    {
                    uartWriteString(UART_USB, "ERROR: Arduino response timeout, could not process command.\r\n");
                    main_fsm_state = IDLE;
                }
                break;

            default:
                main_fsm_state = IDLE;
        }   // switch(fsm_uart_state)
    }   // if (delayRead(&uart_output_delay))
}   // void main_fsm_execute


/* ===== Implementations of private functions ===== */

