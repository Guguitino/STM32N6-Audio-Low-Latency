/*
 * LowPass_FirstOrder.c
 *
 *  Created on: Oct 15, 2025
 *      Author: adamg
 */

#include "LowPass_FirstOrder.h"

void LowPass_FirstOrder_Init(LowPass_FirstOrder *filt, float32_t fc_Hz, float32_t fs_Hz)
{
	/* Store sampling frequency and compute filter coefficient */
	filt->fs_Hz = fs_Hz;

	LowPass_FirstOrder_SetCutOff(filt, fc_Hz);

	/* Reset output */
	filt->out = 0.0f;

}

void LowPass_FirstOrder_SetCutOff(LowPass_FirstOrder *filt, float32_t fc_Hz)
{
	if (fc_Hz > (0.5f * filt->fs_Hz))
	{
		fc_Hz = 0.5f * filt-> fs_Hz;
	}
	else if (fc_Hz < 0.0f)
	{
		fc_Hz = 0.0f;
	}

	float32_t alpha = 2 * PI * fc_Hz /filt->fs_Hz;

	filt->coeff[0] = alpha / (1.0f + alpha);
	filt->coeff[1] = 1.0f / (1.0f + alpha);
}

float32_t LowPass_FirstOrder_Update(LowPass_FirstOrder *filt, float32_t inp)
{
	/* Perform IIR filter update to compute newest output sample
	 *
	 * Vout[n] = alpha /(1 + alpha) * Vin[n] + 1 / (1 + alpha) * Vout[n-1]
	 *
	 * */

	filt->out = filt->coeff[0] * inp +filt->coeff[1] * filt->out;

	if (filt->out > 1.0f)
	{
		filt->out = 1.0f;
	}
	else if(filt->out < -1.0f)
	{
		filt->out = -1.0f;
	}
	return filt->out;

}



