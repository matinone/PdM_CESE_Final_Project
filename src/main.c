/* ===== [main.c] =====
 * Copyright Matias Brignone <mnbrignone@gmail.com>
 * All rights reserved.
 *
 * Version: 0.0.1
 * Creation Date: 2019/04/07
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
