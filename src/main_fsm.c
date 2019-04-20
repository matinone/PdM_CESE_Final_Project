/* ===== [debounce.c] =====
 * Copyright Matias Brignone <mnbrignone@gmail.com>
 * All rights reserved.
 *
 * Version: 0.0.1
 * Creation Date: 2019/04/07
 */


/* ===== Dependencies ===== */
#include "main_fsm.h"
#include "uart_print.h"


/* ===== Macros of private constants ===== */
#define PROCESS_DELAY 10
#define ARDUINO_TIMEOUT 2000
#define BAUD_RATE 115200


/* ===== Declaration of private variables ===== */
static main_fsm_state_t main_fsm_state;
static delay_t process_delay;
static delay_t arduino_rsp_timeout;


/* ===== Prototypes of private functions ===== */


/* ===== Implementations of public functions ===== */

void main_fsm_init ()   {
    uartConfig(UART_USB, BAUD_RATE);                    // config uart
    delayConfig(&process_delay, PROCESS_DELAY);         // config delay for the main FSM
    main_fsm_state = INITIAL;                           // set main fsm initial state
    delayConfig(&arduino_rsp_timeout, ARDUINO_TIMEOUT); // config delay for arduino response timeout
    gpioWrite(LEDB, OFF);
}

// FSM Execute Function
void main_fsm_execute ()    {
    static uint8_t received_byte;
    
    if (delayRead(&process_delay)) {

        uint8_t received_rsp;

        switch(main_fsm_state)   {

            case INITIAL:
                print_welcome_msg();
                main_fsm_state = IDLE;
                uartWriteString(UART_USB, "Entering IDLE state.\r\n");
                break;

            case IDLE:
                if (uartReadByte(UART_USB, &received_byte)) {
                    main_fsm_state = PROCESS_CMD;
                    uartWriteString(UART_USB, "Entering PROCESS_CMD state.\r\n");
                }
                break;

            case PROCESS_CMD:
                switch (received_byte)  {
                    case '1':
                        uartWriteString(UART_USB, "Command 1 received - toggle LEDB.\r\n");
                        gpioToggle(LEDB);
                        main_fsm_state = IDLE;
                        break;

                    case '2':
                        uartWriteString(UART_USB, "Command 2 received - echo to Arduino.\r\n");
                        //send_command_to_arduino(received_byte);
                        uartWriteString(UART_USB, "A_1\r\n");
                        
                        // config delay for the rsp timeout
                        delayConfig(&arduino_rsp_timeout, ARDUINO_TIMEOUT);
                        delayRead(&arduino_rsp_timeout);    // the delay starts after being read once

                        main_fsm_state = WAIT_RSP;
                        break;

                    default:
                        uartWriteString(UART_USB, "ERROR: Invalid command received.\r\n");
                        main_fsm_state = IDLE;
                }
                break;

            case WAIT_RSP:
                 
                if (uartReadByte(UART_USB, &received_rsp)) {
                    // check_rsp(received_rsp, received_byte);
                    // update_arduino_fsm(received_rsp, received_byte);
                    uartWriteString(UART_USB, "Arduino response OK.\r\n");
                    main_fsm_state = IDLE;
                }

                if (delayRead(&arduino_rsp_timeout))    {
                    uartWriteString(UART_USB, "ERROR: Arduino response timeout.\r\n");
                    main_fsm_state = IDLE;
                }
                break;

            default:
                main_fsm_state = IDLE;
        }   // switch(fsm_uart_state)
    }   // if (delayRead(&uart_output_delay))
}   // void main_fsm_execute


/* ===== Implementations of private functions ===== */

