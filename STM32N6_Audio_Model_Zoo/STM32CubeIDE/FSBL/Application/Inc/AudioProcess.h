/*
 * audio_process.h
 *
 *  Created on: Oct 16, 2025
 *      Author: adamg
 */

#ifndef APPLICATION_INC_AUDIO_PROCESS_H_
#define APPLICATION_INC_AUDIO_PROCESS_H_

#include "AudioMain.h"
#include "LowPass_FirstOrder.h"
#include "stdint.h"

#define AUDIO_BUFFER_SIZE 128

void AudioProcess(int16_t *AudioInBuffer, int16_t *AudioOutBuffer, AudioCtx_t *AudioCtx);

#endif /* APPLICATION_INC_AUDIO_PROCESS_H_ */
