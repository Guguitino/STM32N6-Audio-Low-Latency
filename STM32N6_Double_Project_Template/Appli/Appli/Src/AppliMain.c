/*
 * AppliMain.c
 *
 *  Created on: Nov 4, 2025
 *      Author: adamg
 */

#include "AppliMain.h"
#include "Logging.h"

void AppliMain(void)
{
	while(1)
	{
		print("Appli time: %d\r\n", (uint32_t)HAL_GetTick());
		HAL_Delay(100);
	}
}
