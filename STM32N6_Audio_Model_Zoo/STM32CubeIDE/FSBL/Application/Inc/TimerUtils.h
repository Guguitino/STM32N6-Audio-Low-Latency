/*
 * TimerUtils.h
 *
 *  Created on: Oct 22, 2025
 *      Author: adamg
 */

#ifndef APPLICATION_INC_TIMERUTILS_H_
#define APPLICATION_INC_TIMERUTILS_H_

#include "stm32n6xx_hal.h"
#include "stm32n6xx_hal_tim.h"
#include "arm_math_types.h"

#define TIMER_GROUP_CLOCK_FREQUENCY 400000000 // 400 MHz

typedef struct
{
	TIM_HandleTypeDef *htim;
	float32_t TimPeriod_ms;
	uint32_t TimCountStart;
	uint32_t TimCountStop;
	float32_t TimeElapsed_ms;
}ExecTimeMeasurement;

void ExecTimeMeasurementStart(ExecTimeMeasurement *mes);

void ExecTimeMeasurementStop(ExecTimeMeasurement *mes);

#endif /* APPLICATION_INC_TIMERUTILS_H_ */
