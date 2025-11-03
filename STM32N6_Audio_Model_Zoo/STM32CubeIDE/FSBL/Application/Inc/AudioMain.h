/*
 * AudioMain.h
 *
 *  Created on: Oct 17, 2025
 *      Author: adamg
 */

#ifndef APPLICATION_INC_AUDIOMAIN_H_
#define APPLICATION_INC_AUDIOMAIN_H_

#include "preproc_dpu.h"
#include "postproc_dpu.h"
#include "ai_dpu.h"

#define AUDIO_BUFFER_SIZE 128
#define AUDIO_ACQ_LEN CTRL_X_CUBE_AI_ACQ_LENGTH

#if (CTRL_X_CUBE_AI_SPECTROGRAM_COL_OVL > 0)
#define AUDIO_ACQ_OFFSET  ((CTRL_X_CUBE_AI_SPECTROGRAM_COL_OVL*2 -1)*CTRL_X_CUBE_AI_SPECTROGRAM_HOP_LENGTH+CTRL_X_CUBE_AI_SPECTROGRAM_WINDOW_LENGTH)
#else
#define AUDIO_ACQ_OFFSET  (CTRL_X_CUBE_AI_SPECTROGRAM_WINDOW_LENGTH-CTRL_X_CUBE_AI_SPECTROGRAM_HOP_LENGTH)
#endif

typedef struct{
	int16_t ProcBuff[PATCH_LENGTH];
	int16_t AudioOut[PATCH_LENGTH];
	int32_t AcqIndex;
	int32_t PlaybackIndex;
	int16_t OvlSamples[AUDIO_ACQ_OFFSET];
	AudioPreProcCtx_t AudioPreProcCtx;
	AudioPostProcCtx_t AudioPostProcCtx;
	AIProcCtx_t AICtx;
	int8_t *AIInPtr;
	const LL_Buffer_InfoTypeDef * AIOutPtr;

}AudioCtx_t;

void AudioMainInit(AudioCtx_t *AudioCtx);
void AudioMain(AudioCtx_t *AudioCtx);

#endif /* APPLICATION_INC_AUDIOMAIN_H_ */
