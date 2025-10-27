/*
 * audio_process.c
 *
 *  Created on: Oct 16, 2025
 *      Author: adamg
 */
#include "AudioProcess.h"

#include "preproc_dpu.h"

void AudioProcess(int16_t *AudioInBuffer, int16_t *AudioOutBuffer, AudioCtx_t *AudioCtx)
{

	PreProc_DPU_f16(&AudioCtx->AudioPreProcCtx, AudioInBuffer, AudioCtx->AIInPtr);
}


