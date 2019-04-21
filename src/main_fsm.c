/* ===== [main_fsm.c] =====
 * Copyright Matias Brignone <mnbrignone@gmail.com>
 * All rights reserved.
 *
 * Version: 0.0.1
 * Creation Date: 2019/04/20
 */


/* ===== Dependencies ===== */
#include "main_fsm.h"
#include "arduino_command.h"
#include "arduino_fsm.h"
#include "uart_print.h"


/* ===== Macros of private constants ===== */
#define PROCESS_DELAY 10
#define BAUD_RATE 115200
#define ADC_CHANNEL CH1


/* ===== Declaration of private variables ===== */
static main_fsm_state_t main_fsm_state;
static delay_t process_delay;
static arduino_cmd_t current_cmd; 
static pc_command_stats_t pc_command_stats;


/* ===== Prototypes of private functions ===== */

/*------------------------------------------------------------------
|  Function: pc_command_stats_init
| ------------------------------------------------------------------
|  Description: sets all members of pc_command_stats_t struct to
|               zero.
|
|  Parameters:
|       stats - pc_command_stats_t struct to clear
|
|  Returns:  void
*-------------------------------------------------------------------*/
static void pc_command_stats_init(pc_command_stats_t * stats);


/* ===== Implementations of public functions ===== */

void main_fsm_init ()   {
    uartConfig(UART_USB, BAUD_RATE);            // config uart
    
    delayConfig(&process_delay, PROCESS_DELAY); // config delay for the main FSM
    main_fsm_state = INITIAL;                   // set main fsm initial state
    
    pc_command_stats_init(&pc_command_stats);

    reset_arduino_cmd(&current_cmd);
    gpioWrite(LEDB, OFF);

    adcConfig(ADC_ENABLE);
}

// FSM Execute Function
void main_fsm_execute ()    {
    static uint8_t received_byte;
    
    if (delayRead(&process_delay)) {

        uint8_t rsp_status;
        arduino_fsm_state_t current_arduino_state;

        switch(main_fsm_state)   {

            case INITIAL:
                print_welcome_msg();
                main_fsm_state = IDLE;
                break;

            case IDLE:
                if (uartReadByte(UART_USB, &received_byte)) {
                    if (received_byte == 'E')   {
                        if (uartReadByte(UART_USB, &received_byte)) {
                            main_fsm_state = PROCESS_CMD;   // only process command if the format is 'E + number'
                        }
                        else    {
                            uartWriteString(UART_USB, "ERROR: Invalid command received.\r\n");
                        }
                    } 
                    else if (received_byte == 'A') {
                        main_fsm_state = PROCESS_CMD;
                    }
                    else    {
                        uartWriteString(UART_USB, "ERROR: Invalid command received.\r\n");
                        print_help();
                    }
                }
                break;

            case PROCESS_CMD:
                switch (received_byte)  {
                    case TOGGLE_LED:
                        uartWriteString(UART_USB, "Command 0 received - toggle EDU-CIAA LEDB.\r\n");
                        gpioToggle(LEDB);
                        pc_command_stats.toggle_led += 1;

                        main_fsm_state = IDLE;
                        break;

                    case ECHO_ARDUINO:
                        uartWriteString(UART_USB, "Command 1 received - echo to Arduino.\r\n");
                        send_cmd_to_arduino(received_byte);

                        setup_arduino_command(&current_cmd, received_byte);
                        pc_command_stats.echo_arduino += 1;

                        main_fsm_state = WAIT_RSP;
                        break;

                    case CONFIG_MODE_1:
                        uartWriteString(UART_USB, "Command 2 received - configure Arduino in Mode 1.\r\n");
                        send_cmd_to_arduino(received_byte);

                        setup_arduino_command(&current_cmd, received_byte);
                        pc_command_stats.config_mode_1 += 1;

                        main_fsm_state = WAIT_RSP;
                        break;

                    case CONFIG_MODE_2:
                        uartWriteString(UART_USB, "Command 3 received - configure Arduino in Mode 2.\r\n");
                        send_cmd_to_arduino(received_byte);

                        setup_arduino_command(&current_cmd, received_byte);
                        pc_command_stats.config_mode_2 += 1;

                        main_fsm_state = WAIT_RSP;
                        break;

                    case START_PROCESS:
                        uartWriteString(UART_USB, "Command 4 received - start process in Arduino.\r\n");
                        send_cmd_to_arduino(received_byte);

                        setup_arduino_command(&current_cmd, received_byte);
                        pc_command_stats.start_process += 1;

                        main_fsm_state = WAIT_RSP;
                        break;

                    case GET_ARDUINO_STATE:
                        uartWriteString(UART_USB, "Command 5 received - get Arduino FSM state.\r\n");
                        current_arduino_state = get_arduino_fsm_state();
                        uartWriteString(UART_USB, "Arduino FSM State: ");
                        uartWriteString(UART_USB, arduino_fsm_translate(current_arduino_state));
                        uartWriteString(UART_USB, ".\r\n");

                        pc_command_stats.get_arduino_state += 1;

                        main_fsm_state = IDLE;
                        break;

                    case READ_ADC:
                        uartWriteString(UART_USB, "Command 6 received - read ADC value.\r\n");
                        print_adc_value(adcRead(ADC_CHANNEL));
                        pc_command_stats.read_adc += 1;

                        main_fsm_state = IDLE;
                        break;

                    case ARDUINO_DONE:
                        reset_arduino_cmd(&current_cmd);
                        current_cmd.rsp_header = ARDUINO_DONE;
                        rsp_status = check_arduino_rsp(&current_cmd);

                        if (rsp_status == RSP_OK) {
                            if (get_arduino_fsm_state() != ARDUINO_WORKING) {
                                uartWriteString(UART_USB, "ERROR: there is no process to finish in the Arduino.\r\n");
                            }
                            else    {
                                uartWriteString(UART_USB, "Arduino finished its process. Updating Arduino FSM.\r\n");
                                change_arduino_state();
                            }
                        }
                        else {
                            uartWriteString(UART_USB, "ERROR: Arduino tried to update its state, but response was NOT OK.\r\n");
                        }

                        main_fsm_state = IDLE;
                        break;

                    default:
                        uartWriteString(UART_USB, "ERROR: Invalid command received.\r\n");
                        print_help();
                        pc_command_stats.invalid_cmd += 1;

                        main_fsm_state = IDLE;
                }
                break;

            case WAIT_RSP:
            
                if (uartReadByte(UART_USB, &(current_cmd.rsp_header))) {
                    rsp_status = check_arduino_rsp(&current_cmd);

                    if (rsp_status == RSP_OK)   {
                        uartWriteString(UART_USB, "Arduino response OK.\r\n");
                        update_arduino_fsm(&current_cmd);
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


void pc_command_stats_init(pc_command_stats_t * stats)  {
    stats->toggle_led           = 0;
    stats->echo_arduino         = 0;
    stats->config_mode_1        = 0;
    stats->config_mode_2        = 0;
    stats->start_process        = 0;
    stats->get_arduino_state    = 0;
    stats->read_adc             = 0;
    stats->invalid_cmd          = 0;
}


/* ===== Implementations of private functions ===== */

