/*
 * AudioMain.h
 *
 *  Created on: Oct 17, 2025
 *      Author: adamg
 */

#include <stdio.h>
#include <stdarg.h>
#include "AudioCapture_ring_buff.h"

#include "dpu_config.h"
#include "preproc_dpu.h"
#include "postproc_dpu.h"
#include "ai_dpu.h"

#ifndef APPLICATION_INC_AUDIOMAIN_H_
#define APPLICATION_INC_AUDIOMAIN_H_

#define AUDIO_BUFFER_SIZE 128
#define AUDIO_FREQUENCY 16000
#define FFT_BUFFER_SIZE 2048

#define AUDIO_ACQ_LEN     (CTRL_X_CUBE_AI_ACQ_LENGTH)
#if (CTRL_X_CUBE_AI_SPECTROGRAM_COL_OVL > 0)
#define AUDIO_ACQ_OFFSET  ((CTRL_X_CUBE_AI_SPECTROGRAM_COL_OVL*2 -1)*CTRL_X_CUBE_AI_SPECTROGRAM_HOP_LENGTH+CTRL_X_CUBE_AI_SPECTROGRAM_WINDOW_LENGTH)
#else
#define AUDIO_ACQ_OFFSET  (CTRL_X_CUBE_AI_SPECTROGRAM_WINDOW_LENGTH-CTRL_X_CUBE_AI_SPECTROGRAM_HOP_LENGTH)
#endif
#define AUDIO_OUT_FIRST   (CTRL_X_CUBE_AI_SPECTROGRAM_COL_OVL*CTRL_X_CUBE_AI_SPECTROGRAM_HOP_LENGTH)


typedef struct
{
	AudioCapture_ring_buff_t ring_buff;
}AudioAcqCtx_t;

typedef struct
{
	AudioCapture_ring_buff_t ring_buff;
}AudioPlayBackCtx_t;

typedef struct
{
	int16_t ProcBuffer[PATCH_LENGTH];
	int16_t AudioOut[PATCH_LENGTH];
	AudioPreProcCtx_t AudioPreCtx;
	AudioPostProcCtx_t AudioPostCtx;

  AIProcCtx_t AICtx;
  int8_t * AIInputPtr;
  const LL_Buffer_InfoTypeDef * AIOutputPtr;
}AudioProcCtx_t;

void AudioMainInit(void);
void AudioMain(void);

#endif /* APPLICATION_INC_AUDIOMAIN_H_ */
