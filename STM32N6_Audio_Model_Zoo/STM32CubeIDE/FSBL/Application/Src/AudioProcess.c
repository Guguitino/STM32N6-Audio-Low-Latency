/*
 * audio_process.c
 *
 *  Created on: Oct 16, 2025
 *      Author: adamg
 */
#include "AudioProcess.h"

#include "preproc_dpu.h"                           /* Preprocessing includes  */
#include "postproc_dpu.h"                          /* Postprocessing includes */

void AudioProcess(int16_t *AudioInBuffer, int16_t *AudioOutBuffer, AudioCtx_t *AudioCtx)
{
	uint8_t *ProcBuff = (uint8_t *) AudioCtx->ProcBuff;
	uint8_t *ProcBuffOvl = (uint8_t *) (&AudioCtx->ProcBuff[AUDIO_ACQ_LEN]);
	uint8_t *AcqBuff = (uint8_t *) (&AudioCtx->ProcBuff[AUDIO_ACQ_OFFSET]);

	/* Audio samples acquisition */
	for (int32_t i = 0; i < AUDIO_BUFFER_SIZE; i++)
	{
		AcqBuff[AudioCtx->AcqIndex] = AudioInBuffer[i];
		AudioCtx->AcqIndex++;
	}
	for (int32_t i = 0; i < AUDIO_BUFFER_SIZE; i++)
	{
		AudioOutBuffer[i] = AudioCtx->AudioOut[AudioCtx->PlaybackIndex];
		AudioCtx->PlaybackIndex++;
	}

	assert(AudioCtx->AcqIndex <= AUDIO_ACQ_LEN);

	if(AudioCtx->AcqIndex == AUDIO_ACQ_LEN)
	{

		/* prepare overlapping samples from previous patch */
		memcpy(ProcBuff,AudioCtx->OvlSamples,AUDIO_ACQ_OFFSET*sizeof(int16_t));


		/* Audio pre processing */
		PreProc_DPU(&AudioCtx->AudioPreProcCtx, ProcBuff, AudioCtx->AIInPtr );

		/* AI processing */
		AiDPUProcess(&AudioCtx->AICtx);

		/* Audio post processing */
		PostProc_DPU(&AudioCtx->AudioPostProcCtx,
				AudioCtx->AudioPreProcCtx.pCplxSpectrum,
				(float32_t *) LL_Buffer_addr_start(AudioCtx->AIOutPtr),
				AudioCtx->AudioOut);

		/* prepare overlapping samples for next patch */
		memcpy(AudioCtx->OvlSamples,ProcBuffOvl,AUDIO_ACQ_OFFSET*sizeof(int16_t));
		AudioCtx->AcqIndex = 0;
		AudioCtx->PlaybackIndex = 0;
	}
}


