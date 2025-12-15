/*
 * TimerUtils.c
 *
 *  Created on: Oct 22, 2025
 *      Author: adamg
 */

#include "TimerUtils.h"
#include "stm32n6xx_hal.h"
#include "stm32n6xx_hal_tim.h"
#include "main.h"
#include "logging.h"

void TimInit(TimCtx_t *TimCtx)
{
	if(!(TimCtx->htim))
	{
		print("Timer Handle not specified\n");
		Error_Handler();
	}
	TIM_HandleTypeDef *htim = TimCtx->htim;
	uint32_t Presc = htim->Init.Prescaler ;
	TimCtx->IncrementFrequency = ((float32_t)TIMER_GROUP_CLOCK_FREQUENCY) / (float32_t)Presc;
	TimCtx->IncrementPeriod_ms = 1000.0f / TimCtx->IncrementFrequency;
	TimCtx->CounterPeriod = htim->Init.Period;

	HAL_TIM_Base_Start(htim);
}

uint32_t TimGetCycleCount(TimCtx_t *TimCtx)
{
	return __HAL_TIM_GetCounter(TimCtx->htim);
}

int32_t TimMsToCycles(TimCtx_t *TimCtx, int32_t Time_ms)
{
	float32_t Frequency = TimCtx->IncrementFrequency;
	float32_t Cycles = ((float32_t) Time_ms) * Frequency / 1000.0f;
	return ((int32_t)Cycles);
}

/* Time measurement demo :
	ExecTimeMeasurement DelayMes;
	DelayMes.TimCtx = &TimCtx6;
	ExecTimeMeasurementStart(&DelayMes);
	HAL_Delay(50);
	ExecTimeMeasurementStop(&DelayMes);
*/
void ExecTimeMeasurementStart(ExecTimeMeasurement_t *mes)
{
	TIM_HandleTypeDef *htim = mes->TimCtx->htim;
	mes->TimCountStart = __HAL_TIM_GetCounter(htim);
}

void ExecTimeMeasurementStop(ExecTimeMeasurement_t *mes)
{
	TIM_HandleTypeDef *htim = mes->TimCtx->htim;
	mes->TimCountStop = __HAL_TIM_GetCounter(htim);
	float32_t CountDiff = (float32_t)mes->TimCountStop - (float32_t)mes->TimCountStart;
	if(CountDiff < 0)
	{
		CountDiff += mes->TimCtx->CounterPeriod;
	}
	mes->TimeElapsed_ms = CountDiff * mes->TimCtx->IncrementPeriod_ms;
}

void NBDelayInit(NBDelay_t *Delay, int32_t Delay_ms)
{
	if(!(Delay->TimCtx))
	{
		print("Timer Context not specified\n");
		Error_Handler();
	}
	Delay->DelayCycle = TimMsToCycles(Delay->TimCtx, Delay_ms);
	Delay->LastTickCycle = TimGetCycleCount(Delay->TimCtx);
}

/**
 * @brief  Test if the delay has run out.
 * @param  Delay : NBDelay struct
 * @retval If the delay has not run out : 0
 * 		   If the delay has run out : Number of addditionnal cycles waited (non-zero)
 */
uint32_t NBDelayHasRunOut(NBDelay_t *Delay)
{
	uint32_t result = 0;
	TimCtx_t *TimCtx = Delay->TimCtx;

	Delay->NewTickCycle = TimGetCycleCount(TimCtx);
	int32_t CurrentNumberOfCycleElapsed = Delay->NewTickCycle - Delay->LastTickCycle;
	//Test for wrapping
	if (CurrentNumberOfCycleElapsed < 0)
	{
		CurrentNumberOfCycleElapsed += TimCtx->CounterPeriod;
	}

	if (CurrentNumberOfCycleElapsed > Delay->DelayCycle)
	{
		Delay->LastTickCycle = Delay->NewTickCycle;
		result = CurrentNumberOfCycleElapsed - Delay->DelayCycle;
	}



	return result;
}



