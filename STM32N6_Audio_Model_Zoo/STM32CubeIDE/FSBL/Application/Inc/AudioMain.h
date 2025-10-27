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

typedef struct{
	int16_t ProcBuff[PATCH_LENGTH];
	int16_t AudioOut[PATCH_LENGTH];
	AudioPreProcCtx_t AudioPreProcCtx;
	AudioPostProcCtx_t AudioPostProcCtx;
	AIProcCtx_t AICtx;
	int8_t *AIInPtr;
	const LL_Buffer_InfoTypeDef * AIOutPtr;

}AudioCtx_t;

void AudioMainInit(AudioCtx *AudioCtx);
void AudioMain(AudioCtx *AudioCtx);

#endif /* APPLICATION_INC_AUDIOMAIN_H_ */
