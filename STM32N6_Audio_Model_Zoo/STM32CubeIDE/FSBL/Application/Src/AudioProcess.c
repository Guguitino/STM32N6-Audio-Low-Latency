/*
 * audio_process.c
 *
 *  Created on: Oct 16, 2025
 *      Author: adamg
 */
#include "AudioMain.h"
#include "AudioProcess.h"

#include "arm_math.h"

extern LowPass_FirstOrder LPFilter;

extern arm_rfft_fast_instance_f32 fftHandler;
extern float32_t fftInBuffer[FFT_BUFFER_SIZE];
extern float32_t fftOutBuffer[FFT_BUFFER_SIZE];
extern uint8_t fftFlag;

void AudioProcess(int16_t *AudioInBuffer, int16_t *AudioOutBuffer)
{
	float32_t SampleIn;
	float32_t SampleProcessed;
	int16_t SampleOut;

	static int16_t fftIndex = 0;

	for(uint32_t SampleIndex = 0; SampleIndex < (AUDIO_BUFFER_SIZE/2); SampleIndex++)
	{
		SampleIn = ((float32_t)AudioInBuffer[SampleIndex]) / 32768.0f;


		SampleProcessed = LowPass_FirstOrder_Update(&LPFilter, SampleIn);
		//sample_processed = sample_in;

		// Fill fft buffer
		fftInBuffer[fftIndex] = SampleProcessed;
		fftIndex++;

		if(fftIndex == FFT_BUFFER_SIZE)
		{
			arm_rfft_fast_f32(&fftHandler, fftInBuffer, fftOutBuffer, 0);

			fftFlag = 1;

			fftIndex = 0;
		}



		SampleOut = (int16_t)(SampleProcessed * 32768.0f);
		AudioOutBuffer[SampleIndex] = SampleOut;

	}
}


