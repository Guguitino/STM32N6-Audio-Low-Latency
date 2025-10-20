/*
 * audio_process.c
 *
 *  Created on: Oct 16, 2025
 *      Author: adamg
 */
#include "AudioProcess.h"

void AudioProcess(int16_t *AudioInBuffer, int16_t *AudioOutBuffer, LowPass_FirstOrder *LPFilter)
{
	float32_t sample_in;
	float32_t sample_processed;
	int16_t sample_out;

	for(uint32_t sampleIndex = 0; sampleIndex < (AUDIO_BUFFER_SIZE/2); sampleIndex++)
	{
		sample_in = ((float32_t)AudioInBuffer[sampleIndex]) / 32768.0f;

		sample_processed = LowPass_FirstOrder_Update(LPFilter, sample_in);
		//sample_processed = sample_in;

		sample_out = (int16_t)(sample_processed * 32768.0f);
		AudioOutBuffer[sampleIndex] = sample_out;

	}
}


