/*
 * LowPass_FirstOrder.h
 *
 *  Created on: Oct 15, 2025
 *      Author: adamg
 */

#ifndef INC_LOWPASS_FIRSTORDER_H_
#define INC_LOWPASS_FIRSTORDER_H_

#include <arm_math_types.h>

#define PI               3.14159265358979f

typedef struct
{
	/* Filtered output */
	float32_t out;

	/* Filter coefficients */
	float32_t coeff[2];

	/* Sampling frequency (Hz) */
	float32_t fs_Hz;
}LowPass_FirstOrder;

void LowPass_FirstOrder_Init(LowPass_FirstOrder *filt, float32_t fc_Hz, float32_t fs_Hz);

void LowPass_FirstOrder_SetCutOff(LowPass_FirstOrder *filt, float32_t fc_Hz);

float32_t LowPass_FirstOrder_Update(LowPass_FirstOrder *filt, float32_t inp);

#endif /* INC_LOWPASS_FIRSTORDER_H_ */
