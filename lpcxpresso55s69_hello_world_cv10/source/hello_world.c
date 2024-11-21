/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include <stdbool.h>
#include "fsl_power.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

bool constantTimeStringCompare(const void *a, const void *b, size_t length);
int password(void);


/*******************************************************************************
 * Variables
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/

int password() {
	//int32_t status;
	uint32_t DWT1, DWT2;

	char password_stored[20] = "1234";
	char input[20];

	PRINTF("\r\nEnter password: ");

	SCANF("%s", input);

	//status = strcmp(input, password_stored);
	DWT1 = DWT->CYCCNT;
	int result = secure_compare(input, password_stored, strlen(password_stored));
	DWT2 = DWT->CYCCNT;
	PRINTF("\r\nInput: %s", input);

	if(result == 0) {
		PRINTF("\r\nInput correct");
	} else {
		PRINTF("\r\nInput invalid");}

	return (DWT2-DWT1);

}

/*bool constantTimeStringCompare(const void *a, const void *b, size_t length)
{
	const char *ca = a;
	const char *cb = b;
	bool result = true;

	for (size_t i = 0; i < length; i++) {
		result &= ca[i] == cb [i];
	}
	return result;

}*/




int secure_compare(const char *a, const char *b, size_t length) {
	int result = 0;
	for (size_t i = 0; i < length; i++) {
		 result |= a[i] ^ b[i];
	}
	return result;
}

/*!
 * @brief Main function
 */
int main(void)
{
    char ch;

    /* Init board hardware. */
    /* set BOD VBAT level to 1.65V */
    POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);
    /* attach main clock divide to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
#if !defined(DONT_ENABLE_FLASH_PREFETCH)
    /* enable flash prefetch for better performance */
    SYSCON->FMCCR |= SYSCON_FMCCR_PREFEN_MASK;
#endif

    uint32_t DWT1, DWT2;

    while (1)
    {

        //DWT1 = DWT->CYCCNT;
        uint32_t status = password();
        //DWT2 = DWT->CYCCNT;
        PRINTF("\r\nCycles in function: %d", status);


    }
}
