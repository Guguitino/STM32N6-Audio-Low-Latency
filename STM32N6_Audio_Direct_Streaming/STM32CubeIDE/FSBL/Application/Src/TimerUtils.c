/*
 * TimerUtils.c
 *
 *  Created on: Oct 22, 2025
 *      Author: adamg
 */

#include "TimerUtils.h"
#include "stm32n6xx_hal.h"
#include "stm32n6xx_hal_tim.h"

void ExecTimeMeasurementStart(ExecTimeMeasurement *mes)
{
	TIM_HandleTypeDef *htim = mes->htim;
	float32_t TimerIncrementFrequency = ((float32_t)TIMER_GROUP_CLOCK_FREQUENCY) / ((float32_t)htim->Init.Prescaler );
	mes->TimPeriod_ms = 1000.0f / TimerIncrementFrequency;

	mes->TimCountStart = __HAL_TIM_GetCounter(htim);
}

void ExecTimeMeasurementStop(ExecTimeMeasurement *mes)
{
	TIM_HandleTypeDef *htim = mes->htim;
	mes->TimCountStop = __HAL_TIM_GetCounter(htim);
	mes->TimeElapsed_ms = ((float32_t)mes->TimCountStop - (float32_t)mes->TimCountStart) * mes->TimPeriod_ms;
}
