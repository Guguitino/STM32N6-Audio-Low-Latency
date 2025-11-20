/*
 * TimerUtils.h
 *
 *  Created on: Oct 22, 2025
 *      Author: adamg
 */

#ifndef TIMERUTILS_H_
#define TIMERUTILS_H_

#include "stm32n6xx_hal.h"
#include "stm32n6xx_hal_tim.h"
#include "arm_math_types.h"

#define TIMER_GROUP_CLOCK_FREQUENCY 400000000 // 400 MHz

typedef struct
{
	TIM_HandleTypeDef *htim;
	float32_t IncrementFrequency;
	float32_t IncrementPeriod_ms;
	int32_t CounterPeriod;
}TimCtx_t;

typedef struct
{
	TimCtx_t *TimCtx;
	uint32_t TimCountStart;
	uint32_t TimCountStop;
	float32_t TimeElapsed_ms;
}ExecTimeMeasurement_t;

typedef struct
{
	TimCtx_t *TimCtx;
	int32_t LastTickCycle;
	int32_t NewTickCycle;
	int32_t DelayCycle;
}NBDelay_t;

void TimInit(TimCtx_t *TimCtx);
uint32_t TimGetCycleCount(TimCtx_t *TimCtx);
int32_t TimMsToCycles(TimCtx_t *TimCtx, int32_t Time_ms);
void ExecTimeMeasurementStart(ExecTimeMeasurement_t *mes);
void ExecTimeMeasurementStop(ExecTimeMeasurement_t *mes);
void NBDelayInit(NBDelay_t *Delay, int32_t Delay_ms);
uint32_t NBDelayHasRunOut(NBDelay_t *Delay);

#endif /* TIMERUTILS_H_ */
