/**
 * 
 * @file user_main.c
 * 
 * @brief Main program file.
 * 
 * @copyright
 * Copyright 2015 Martin Bo Kristensen Grønholdt <oblivion@@ace2>
 * 
 * @license
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include "osapi.h"
#include "os_type.h"
#include "user_config.h"
#include "user_interface.h"

/**
 * @brief Timer for handling events.
 */
static os_timer_t dispatch_timer;

/**
 * @brief Test the iprintf macro.
 */
void test_macros(void)
{
	static unsigned long i = 0;
	
	i++;
	iprintf(INFO, "Debug macro test run %lu\n\n", i);
	iprintf(DEBUG, "This is a debug message.\n");
	iprintf(WARNING, "This is a warning.\n");
	iprintf(ERROR, "This is an error\n\n");
}

/**
 * @brief Called when initialisation is over.
 * 
 * Starts the timer that will handle events.
 */
void user_main(void)
{
	ets_printf("Running...\n");
    //Disarm timer
    os_timer_disarm(&dispatch_timer);
    //Setup timer, pass callback as parameter.
    os_timer_setfn(&dispatch_timer, (os_timer_func_t *)test_macros, NULL);
    //Arm the timer, run every DISPATCH_TIME ms.
    os_timer_arm(&dispatch_timer, 1000, 1);
}

/**
 * @brief Main entry point and init code.
 */
void ICACHE_FLASH_ATTR user_init(void)
{
	system_set_os_print(false);

	//Register function to run when done.
	system_init_done_cb(user_main);
	
    // Set baud rate of debug port
    uart_div_modify(0,UART_CLK_FREQ / 115200);
}
