/*
 * FSBLMain.c
 *
 *  Created on: Nov 4, 2025
 *      Author: adamg
 */

#include "FSBLMain.h"
#include "Logging.h"

#define APP_LOCATION (0x34100000 + 4)

static void JumpToApp(void);

void FSBLMain(void)
{
	uint32_t timeNow = HAL_GetTick();
	while(1)
	{
		print("FSBL time: %d\r\n", HAL_GetTick());
		if((HAL_GetTick()- timeNow) >= 5000) // Waiting 5 second before jumping to app.
		{
			JumpToApp();
		}
	}
}

static void JumpToApp(void)
{
	void (*app_reset_handler)(void) = (void *)(*((uint32_t *)(APP_LOCATION)));
	app_reset_handler();
}

