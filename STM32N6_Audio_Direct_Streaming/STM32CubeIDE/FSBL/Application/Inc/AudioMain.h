/*
 * AudioMain.h
 *
 *  Created on: Oct 17, 2025
 *      Author: adamg
 */

#ifndef APPLICATION_INC_AUDIOMAIN_H_
#define APPLICATION_INC_AUDIOMAIN_H_

#define AUDIO_FREQUENCY 16000
#define FFT_BUFFER_SIZE 2048

#include <stdio.h>
#include <stdarg.h>

void AudioMainInit(void);
void AudioMain(void);

#endif /* APPLICATION_INC_AUDIOMAIN_H_ */
