/* ===== [main.c] =====
 * Copyright Matias Brignone <mnbrignone@gmail.com>
 * All rights reserved.
 *
 * Program developed as a Final Project for the Subject "Microcontroller Programming", 
 * a course part of the Specialization Career in Embedded Systems (CESE), 
 * offered by the University of Buenos Aires (UBA).
 *
 * Version: 0.0.1
 * Creation Date: 2019/04/20
 */


/* ===== Dependencies ===== */
#include "sapi.h"
#include "main_fsm.h"

/* ===== Entry point ===== */
int main(void)	{     

	// initial board config
	boardConfig();

	main_fsm_init();

	while(1)	{
		main_fsm_execute();
	}

	return 0;
}
