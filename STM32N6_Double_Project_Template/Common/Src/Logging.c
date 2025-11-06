/*
 * Logging.c
 *
 *  Created on: Nov 4, 2025
 *      Author: adamg
 */

#include "Logging.h"

/**
  * @brief  print function to USART1 (connected to the STLINK-V3EC USB connector (CN6))
  * @param  msg the message string
  * @retval None
  */
void print(char *msg, ...)
{
	char buff[250];
	va_list args;
	va_start(args, msg);
	vsprintf(buff, msg, args);

	for(int i = 0; i < strlen(buff); i++)
	{
		USART1->TDR = buff[i];
		while(!(USART1->ISR & USART_ISR_TXE))
		{
			//Just waiting
		}
	}
	while(!(USART1->ISR & USART_ISR_TC))
	{
		//Just waiting
	}
}
