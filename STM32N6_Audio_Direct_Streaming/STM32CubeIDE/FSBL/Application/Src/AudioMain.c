/*
 * AudioMain.h
 *
 *  Created on: Oct 17, 2025
 *      Author: adamg
 */
#include "AudioMain.h"

/* USER CODE BEGIN Includes */
#include "main.h"
#include "AudioProcess.h"
#include "TimerUtils.h"
#include "stm32n6570_discovery.h"

#include "arm_math.h"
#include <stdio.h>

extern MDF_HandleTypeDef MdfHandle0;
extern MDF_FilterConfigTypeDef MdfFilterConfig0;
extern DMA_NodeTypeDef Node_GPDMA1_Channel6 __NON_CACHEABLE;
extern DMA_QListTypeDef List_GPDMA1_Channel6;
extern DMA_HandleTypeDef handle_GPDMA1_Channel6;

extern SAI_HandleTypeDef hsai_BlockA1;
extern DMA_NodeTypeDef pNode_GPDMACH0 __NON_CACHEABLE;
extern DMA_QListTypeDef pQueueLinkList_GPDMACH0;
extern DMA_HandleTypeDef handle_GPDMA1_Channel0;

extern TIM_HandleTypeDef htim6;

static __IO uint32_t CaptureHalfBufferCpltFlag;
static __IO uint32_t CaptureBufferCpltFlag;

static int16_t CaptureBuffer[AUDIO_BUFFER_SIZE] __NON_CACHEABLE;
static int16_t PlaybackBuffer[AUDIO_BUFFER_SIZE] __NON_CACHEABLE;

LowPass_FirstOrder LPFilter;

arm_rfft_fast_instance_f32 fftHandler;
float32_t fftInBuffer[FFT_BUFFER_SIZE];
float32_t fftOutBuffer[FFT_BUFFER_SIZE];

uint8_t fftFlag = 0;


extern void SystemClock_Config(void);
extern void PeriphCommonClock_Config(void);
extern void MX_GPIO_Init(void);
extern void MX_GPDMA1_Init(void);
extern void MX_MDF1_Init(void);
extern void SystemIsolation_Config(void);

static void MPU_Config(void);

void print(char *msg, ...);

void AudioMainInit(void)
{
	MPU_Config();

	if (BSP_ERROR_NONE != BSP_LED_Init(LED_RED))
	{
		Error_Handler();
	}
	if (BSP_ERROR_NONE != BSP_LED_Init(LED_GREEN))
	{
		Error_Handler();
	}
}

void AudioMain(void)
{
	TimCtx_t TimCtx6 = {};
	TimCtx6.htim = &htim6;
	TimInit(&TimCtx6);

	MDF_DmaConfigTypeDef dma_config;

	/* Start record */
	CaptureHalfBufferCpltFlag = 0;
	CaptureBufferCpltFlag = 0;

	dma_config.Address    = (uint32_t)&CaptureBuffer[0];
	dma_config.DataLength = AUDIO_BUFFER_SIZE * sizeof(int16_t);
	dma_config.MsbOnly    = ENABLE;
	if (HAL_MDF_AcqStart_DMA(&MdfHandle0, &MdfFilterConfig0, &dma_config) != HAL_OK)
	{
		Error_Handler();
	}

	/* Clear playback buffer */
	for(uint8_t Index = 0; Index < AUDIO_BUFFER_SIZE; Index++)
	{
		PlaybackBuffer[Index] = 0;
	}

	/* Start the playback */
	if (HAL_SAI_Transmit_DMA(&hsai_BlockA1, (uint8_t *) &PlaybackBuffer[0], AUDIO_BUFFER_SIZE) != HAL_OK)
	{
		Error_Handler();
	}

	LowPass_FirstOrder_Init(&LPFilter, 1000.0f, (float32_t)AUDIO_FREQUENCY);

	/* Time measurement demo */
	ExecTimeMeasurement_t TestMes;
	TestMes.TimCtx = &TimCtx6;
	ExecTimeMeasurementStart(&TestMes);
	HAL_Delay(50);
	ExecTimeMeasurementStop(&TestMes);

	print("Time measured : %f ms\r\n", TestMes.TimeElapsed_ms);

	/* Initialize FFT */
	arm_rfft_fast_init_f32(&fftHandler, FFT_BUFFER_SIZE);
	float32_t peakVal = 0.0f;
	uint16_t peakHz = 0;

	/* Initialize non blocking delay for the led */
	NBDelay_t LedDelay = {};
	LedDelay.TimCtx = &TimCtx6;
	NBDelayInit(&LedDelay, 500);

	while (1)
	{


		if(fftFlag)
		{
			peakVal = 0.0f;
			peakHz = 0.0f;

			uint16_t freqIndex = 0;
			for(uint16_t Index = 0;Index < FFT_BUFFER_SIZE; Index += 2)
			{
				float32_t curVal = sqrtf((fftOutBuffer[Index] * fftOutBuffer[Index]) + (fftOutBuffer[Index + 1] + fftOutBuffer[Index + 1]));

				if (curVal > peakVal)
				{
					peakVal = curVal;
					peakHz = (uint16_t) (freqIndex * AUDIO_FREQUENCY/ ((float32_t)FFT_BUFFER_SIZE));
				}
				freqIndex++;
			}
			fftFlag = 0;

			//print("%d\r\n", peakHz);
		}

		if(CaptureHalfBufferCpltFlag == 1)
		{
			int16_t *AudioInBuffer = &CaptureBuffer[0];
			int16_t *AudioOutBuffer = &PlaybackBuffer[0];

			AudioProcess(AudioInBuffer, AudioOutBuffer);
			CaptureHalfBufferCpltFlag  = 0;

		}
		if(CaptureBufferCpltFlag == 1)
		{
			int16_t *AudioInBuffer = &CaptureBuffer[AUDIO_BUFFER_SIZE/2];
			int16_t *AudioOutBuffer = &PlaybackBuffer[AUDIO_BUFFER_SIZE/2];

			AudioProcess(AudioInBuffer, AudioOutBuffer);
			CaptureBufferCpltFlag = 0;
		}

		if(NBDelayHasRunOut(&LedDelay))
		{
//			ExecTimeMeasurementStart(&TestMes);
//			print("Ceci est la ligne 1\r\n");
//			ExecTimeMeasurementStop(&TestMes);
//			print("Time measured : %f ms\r\n", TestMes.TimeElapsed_ms);
			BSP_LED_Toggle(LED_GREEN);
		}
	}

}



void MPU_Config(void)
{
	MPU_Region_InitTypeDef default_config = {0};
	MPU_Attributes_InitTypeDef attr_config = {0};
	uint32_t primask_bit = __get_PRIMASK();
	__disable_irq();

	/* disable the MPU */
	HAL_MPU_Disable();

	/* create an attribute configuration for the MPU */
	attr_config.Attributes = INNER_OUTER(MPU_NOT_CACHEABLE);
	attr_config.Number = MPU_ATTRIBUTES_NUMBER0;

	HAL_MPU_ConfigMemoryAttributes(&attr_config);

	/* Create a non cacheable region */
	/*Normal memory type, code execution allowed */
	default_config.Enable = MPU_REGION_ENABLE;
	default_config.Number = MPU_REGION_NUMBER0;
	default_config.BaseAddress = __NON_CACHEABLE_SECTION_BEGIN;
	default_config.LimitAddress = __NON_CACHEABLE_SECTION_END;
	default_config.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
	default_config.AccessPermission = MPU_REGION_ALL_RW;
	default_config.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	default_config.AttributesIndex = MPU_ATTRIBUTES_NUMBER0;
	HAL_MPU_ConfigRegion(&default_config);

	/* enable the MPU */
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

	/* Exit critical section to lock the system and avoid any issue around MPU mechanisme */
	__set_PRIMASK(primask_bit);
}

///**
// * @brief  Probe the WM8904 audio codec.
// * @param  None
// * @retval None
// */
//static void WM8904_Probe(void)
//{
//	WM8904_IO_t              IOCtx;
//	uint32_t                 wm8904_id;
//	static WM8904_Object_t   WM8904Obj;
//
//	/* Configure the audio driver */
//	IOCtx.Address     = 0x34U;s
//	IOCtx.Init        = BSP_I2C2_Init;
//	IOCtx.DeInit      = BSP_I2C2_DeInit;
//	IOCtx.ReadReg     = BSP_I2C2_ReadReg;
//	IOCtx.WriteReg    = BSP_I2C2_WriteReg;
//	IOCtx.GetTick     = BSP_GetTick;
//
//	if (WM8904_RegisterBusIO(&WM8904Obj, &IOCtx) != WM8904_OK)
//	{
//		Error_Handler();
//	}
//	else if (WM8904_ReadID(&WM8904Obj, &wm8904_id) != WM8904_OK)
//	{
//		Error_Handler();
//	}
//	else if ((wm8904_id & WM8904_ID_MASK) != WM8904_ID)
//	{
//		Error_Handler();
//	}
//	else
//	{
//		Audio_Drv = (AUDIO_Drv_t *) &WM8904_Driver;
//		Audio_CompObj = &WM8904Obj;
//	}
//}
//
///**
// * @brief SAI1 Initialization Function
// * @param None
// * @retval None
// */
//static void MX_SAI1_Init(void)
//{
//
//	/* USER CODE BEGIN SAI1_Init 0 */
//
//	/* USER CODE END SAI1_Init 0 */
//
//	/* USER CODE BEGIN SAI1_Init 1 */
//
//	/* USER CODE END SAI1_Init 1 */
//	hsai_BlockA1.Instance = SAI1_Block_A;
//	hsai_BlockA1.Init.Protocol = SAI_FREE_PROTOCOL;
//	hsai_BlockA1.Init.AudioMode = SAI_MODEMASTER_TX;
//	hsai_BlockA1.Init.DataSize = SAI_DATASIZE_16;
//	hsai_BlockA1.Init.FirstBit = SAI_FIRSTBIT_MSB;
//	hsai_BlockA1.Init.ClockStrobing = SAI_CLOCKSTROBING_FALLINGEDGE;
//	hsai_BlockA1.Init.Synchro = SAI_ASYNCHRONOUS;
//	hsai_BlockA1.Init.OutputDrive = SAI_OUTPUTDRIVE_ENABLE;
//	hsai_BlockA1.Init.NoDivider = SAI_MASTERDIVIDER_ENABLE;
//	hsai_BlockA1.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_1QF;
//	hsai_BlockA1.Init.AudioFrequency = SAI_AUDIO_FREQUENCY_16K;
//	hsai_BlockA1.Init.SynchroExt = SAI_SYNCEXT_DISABLE;
//	hsai_BlockA1.Init.MckOutput = SAI_MCK_OUTPUT_ENABLE;
//	hsai_BlockA1.Init.MonoStereoMode = SAI_MONOMODE;
//	hsai_BlockA1.Init.CompandingMode = SAI_NOCOMPANDING;
//	hsai_BlockA1.Init.TriState = SAI_OUTPUT_NOTRELEASED;
//	hsai_BlockA1.Init.PdmInit.Activation = DISABLE;
//	hsai_BlockA1.FrameInit.FrameLength = 32;
//	hsai_BlockA1.FrameInit.ActiveFrameLength = 16;
//	hsai_BlockA1.FrameInit.FSDefinition = SAI_FS_CHANNEL_IDENTIFICATION;
//	hsai_BlockA1.FrameInit.FSPolarity = SAI_FS_ACTIVE_LOW;
//	hsai_BlockA1.FrameInit.FSOffset = SAI_FS_BEFOREFIRSTBIT;
//	hsai_BlockA1.SlotInit.FirstBitOffset = 0;
//	hsai_BlockA1.SlotInit.SlotSize = SAI_SLOTSIZE_16B;
//	hsai_BlockA1.SlotInit.SlotNumber = 2;
//	hsai_BlockA1.SlotInit.SlotActive = SAI_SLOTACTIVE_0 | SAI_SLOTACTIVE_1;
//	if (HAL_SAI_Init(&hsai_BlockA1) != HAL_OK)
//	{
//		Error_Handler();
//	}
//	/* USER CODE BEGIN SAI1_Init 2 */
//
//	/* USER CODE END SAI1_Init 2 */
//
//}
//
///**
// * @brief  Playback initialization
// * @param  None
// * @retval None
// */
//static void Playback_Init(void)
//{
//	/* Probe the audio codec */
//	WM8904_Probe();
//
//	/* Initialize SAI peripheral */
//	MX_SAI1_Init();
//
//	/* Initialize audio codec */
//	WM8904_Init_t codec_init;
//	codec_init.InputDevice  = WM8904_IN_NONE;
//	codec_init.OutputDevice = WM8904_OUT_HEADPHONE;
//	codec_init.Resolution   = WM8904_RESOLUTION_16B;
//	codec_init.Frequency    = WM8904_FREQUENCY_16K;
//	codec_init.Volume       = 80U;
//	if (Audio_Drv->Init(Audio_CompObj, &codec_init) < 0)
//	{
//		Error_Handler();
//	}
//	if (Audio_Drv->Play(Audio_CompObj) != 0)
//	{
//		Error_Handler();
//	}
//}

/**
 * @brief  MDF acquisition complete callback.
 * @param  hmdf MDF handle.
 * @retval None.
 */
void HAL_MDF_AcqCpltCallback(MDF_HandleTypeDef *hmdf)
{
	CaptureBufferCpltFlag = 1;
}

/**
 * @brief  MDF acquisition half complete callback.
 * @param  hmdf MDF handle.s
 * @retval None.
 */
void HAL_MDF_AcqHalfCpltCallback(MDF_HandleTypeDef *hmdf)
{
	CaptureHalfBufferCpltFlag = 1;
}

///**
// * @brief  Re-directing printf() function to ITM SWV console
// * @retval None.
// */
//int _write(int file, char *ptr, int len)
//{
//    for (int i = 0; i < len; i++) {
//        ITM_SendChar(*ptr++);
//    }
//    return len;
//}

void print(char *msg, ...)
{
	char buff[250];
	va_list args;
	va_start(args, msg);
	vsprintf(buff, msg, args);

	for(int i = 0; i < strlen(buff); i++)
	{
		USART1->TDR = buff[i];
		while(!(USART1->ISR & USART_ISR_TXE))
		{
			//Just waiting
		}
	}
	while(!(USART1->ISR & USART_ISR_TC))
	{
		//Just waiting
	}
}






















