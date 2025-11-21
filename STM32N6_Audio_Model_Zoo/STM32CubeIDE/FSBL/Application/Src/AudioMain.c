/*
 * AudioMain.h
 *
 *  Created on: Oct 17, 2025
 *      Author: adamg
 */
#include "AudioMain.h"

/* USER CODE BEGIN Includes */
#include "main.h"
#include "stm32n6xx_hal_ramcfg.h"
#include "AudioProcess.h"
#include "TimerUtils.h"
#include "stm32n6570_discovery.h"
#include "stm32n6570_discovery_bus.h"
#include "logging.h"
#include "misc_toolbox.h"
#include "wm8904.h"
#include "audio.h"
#include "LowPass_FirstOrder.h"

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

static AUDIO_Drv_t *Audio_Drv = NULL;
static void *Audio_CompObj;

static __IO uint32_t CaptureHalfBufferCpltFlag;
static __IO uint32_t CaptureBufferCpltFlag;

static int16_t CaptureBuffer[AUDIO_BUFFER_SIZE] __NON_CACHEABLE;
static int16_t PlaybackBuffer[AUDIO_BUFFER_SIZE] __NON_CACHEABLE;

AudioAcqCtx_t AudioAcqCtx;
AudioPlayBackCtx_t AudioPlayBackCtx;
AudioProcCtx_t AudioProcCtx;

LowPass_FirstOrder LPFilter;

extern void SystemClock_Config(void);
extern void PeriphCommonClock_Config(void);
extern void MX_GPIO_Init(void);
extern void MX_GPDMA1_Init(void);
extern void MX_MDF1_Init(void);
extern void SystemIsolation_Config(void);

static void AudioProcess(AudioAcqCtx_t *AudioAcqCtx, AudioProcCtx_t *AudioProcCtx, AudioPlayBackCtx_t *AudioPlayBackCtx);
static void Int_Mem_Config(void);
static void Ext_Mem_Config(void);
static void IAC_Config(void);
static void MPU_Config(void);
static void WM8904_Probe(void);
static void Playback_Init(void);
static void InitAudioCapture(AudioAcqCtx_t *AudioAcqCtx);
static void InitAudioPlayback(AudioPlayBackCtx_t *AudioPlayBackCtx);
void InitAudioProc(AudioProcCtx_t *AudioProcCtx);
void displaySystemSetting(void);
static void NPU_SettingsLog(void);

void AudioMainInit(void)
{
	  /* Power on ICACHE */
	  MEMSYSCTL->MSCR |= MEMSYSCTL_MSCR_ICACTIVE_Msk;

	MPU_Config();
	Int_Mem_Config(); //MX -> RAMCFG ?
	Ext_Mem_Config(); //MX -> XSPI2 classic configuration ?
	NPU_Config();
	IAC_Config();

	if (BSP_ERROR_NONE != BSP_LED_Init(LED_RED))
	{
		Error_Handler();
	}
	if (BSP_ERROR_NONE != BSP_LED_Init(LED_GREEN))
	{
		Error_Handler();
	}

	displaySystemSetting();
}

void AudioMain(void)
{
	TimCtx_t TimCtx6 = {};
	TimCtx6.htim = &htim6;
	TimInit(&TimCtx6);

	/* Start record */
	CaptureHalfBufferCpltFlag = 0;
	CaptureBufferCpltFlag = 0;

	InitAudioCapture(&AudioAcqCtx);
	InitAudioProc(&AudioProcCtx);
	InitAudioPlayback(&AudioPlayBackCtx);

	Playback_Init();

	MDF_DmaConfigTypeDef dma_config;
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

	/* Initialize non blocking delay for the led */
	NBDelay_t LedDelay = {};
	LedDelay.TimCtx = &TimCtx6;
	NBDelayInit(&LedDelay, 500);

	while (1)
	{

		if(CaptureHalfBufferCpltFlag == 1)
		{
			int16_t *AudioInBuffer = &CaptureBuffer[0];
			int16_t *AudioOutBuffer = &PlaybackBuffer[0];

			AudioCapture_ring_buff_feed(&AudioAcqCtx.ring_buff, (uint8_t *)AudioInBuffer, AUDIO_BUFFER_SIZE/2);
			AudioCapture_ring_buff_consume((uint8_t *)AudioOutBuffer, &AudioPlayBackCtx.ring_buff, AUDIO_BUFFER_SIZE/2);

			CaptureHalfBufferCpltFlag  = 0;

		}
		if(CaptureBufferCpltFlag == 1)
		{
			int16_t *AudioInBuffer = &CaptureBuffer[AUDIO_BUFFER_SIZE/2];
			int16_t *AudioOutBuffer = &PlaybackBuffer[AUDIO_BUFFER_SIZE/2];

			AudioCapture_ring_buff_feed(&AudioAcqCtx.ring_buff, (uint8_t *)AudioInBuffer, AUDIO_BUFFER_SIZE/2);
			AudioCapture_ring_buff_consume((uint8_t *)AudioOutBuffer, &AudioPlayBackCtx.ring_buff, AUDIO_BUFFER_SIZE/2);

			CaptureBufferCpltFlag = 0;
		}

		if (AudioAcqCtx.ring_buff.availableSamples >= AUDIO_ACQ_LEN)
		{
			AudioProcess(&AudioAcqCtx, &AudioProcCtx, &AudioPlayBackCtx);
		}

		if(NBDelayHasRunOut(&LedDelay))
		{
			BSP_LED_Toggle(LED_GREEN);
		}
	}

}

static void AudioProcess(AudioAcqCtx_t *AudioAcqCtx, AudioProcCtx_t *AudioProcCtx, AudioPlayBackCtx_t *AudioPlayBackCtx)
{
	uint8_t *ProcBuffer = (uint8_t *) AudioProcCtx->ProcBuffer;
	uint8_t *ProcBufferOvl = (uint8_t *) (&AudioProcCtx->ProcBuffer[AUDIO_ACQ_LEN]);
	uint8_t *AcqBuffer = (uint8_t *) (&AudioProcCtx->ProcBuffer[AUDIO_ACQ_OFFSET]);

	/* prepare overlapping samples from previous patch */
	memcpy(ProcBuffer, ProcBufferOvl, AUDIO_ACQ_OFFSET*sizeof(int16_t));

	AudioCapture_ring_buff_consume(AcqBuffer, &AudioAcqCtx->ring_buff, AUDIO_ACQ_LEN);

	/* Audio pre processing */
	PreProc_DPU(&AudioProcCtx->AudioPreCtx, ProcBuffer, AudioProcCtx->AIInputPtr );

	/* AI processing */
	AiDPUProcess(&AudioProcCtx->AICtx);

	PostProc_DPU(&AudioProcCtx->AudioPostCtx, AudioProcCtx->AudioPreCtx.pCplxSpectrum,
			(float32_t *) LL_Buffer_addr_start(AudioProcCtx->AIOutputPtr), AudioProcCtx->AudioOut);

	AudioCapture_ring_buff_feed(&AudioPlayBackCtx->ring_buff, &AudioProcCtx->AudioOut[AUDIO_OUT_FIRST], AUDIO_ACQ_LEN);
}

static void Int_Mem_Config(void)
{
  RAMCFG_HandleTypeDef hramcfg = {0};

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_CRC_CLK_ENABLE();

  RCC->MEMENR |= RCC_MEMENR_AXISRAM3EN | RCC_MEMENR_AXISRAM4EN | RCC_MEMENR_AXISRAM5EN | RCC_MEMENR_AXISRAM6EN;
  RCC->MEMENR |= RCC_MEMENR_CACHEAXIRAMEN;
  hramcfg.Instance =  RAMCFG_SRAM2_AXI;
  HAL_RAMCFG_EnableAXISRAM(&hramcfg);
  hramcfg.Instance =  RAMCFG_SRAM3_AXI;
  HAL_RAMCFG_EnableAXISRAM(&hramcfg);
  hramcfg.Instance =  RAMCFG_SRAM4_AXI;
  HAL_RAMCFG_EnableAXISRAM(&hramcfg);
  hramcfg.Instance =  RAMCFG_SRAM5_AXI;
  HAL_RAMCFG_EnableAXISRAM(&hramcfg);
  hramcfg.Instance =  RAMCFG_SRAM6_AXI;
  HAL_RAMCFG_EnableAXISRAM(&hramcfg);

  __HAL_RCC_CACHEAXIRAM_MEM_CLK_ENABLE();
  __HAL_RCC_AXISRAM2_MEM_CLK_ENABLE();
  __HAL_RCC_AXISRAM3_MEM_CLK_ENABLE();
  __HAL_RCC_AXISRAM4_MEM_CLK_ENABLE();
  __HAL_RCC_AXISRAM5_MEM_CLK_ENABLE();
  __HAL_RCC_AXISRAM6_MEM_CLK_ENABLE();

  /* Allow caches to be activated. Default value is 1, but the current boot sets it to 0 */
  MEMSYSCTL->MSCR |= MEMSYSCTL_MSCR_DCACTIVE_Msk | MEMSYSCTL_MSCR_ICACTIVE_Msk;
}

/**
* @brief  external memories configuration (Flash & RAM).
* @param  None.
* @retval None.
*/
static void Ext_Mem_Config(void)
{
  BSP_XSPI_NOR_Init_t Flash;
  Flash.InterfaceMode = MX66UW1G45G_OPI_MODE;
  Flash.TransferRate = MX66UW1G45G_DTR_TRANSFER;

  if(BSP_XSPI_NOR_Init(0, &Flash) != BSP_ERROR_NONE)
  {
    __BKPT(0);
  }
  BSP_XSPI_NOR_EnableMemoryMappedMode(0);
  MODIFY_REG(XSPI2->CR, XSPI_CR_NOPREF, HAL_XSPI_AUTOMATIC_PREFETCH_DISABLE); /* Hotfix for xspi: no prefetch */
}

static void IAC_Config(void)
{
/* Configure IAC to trap illegal access events */
  __HAL_RCC_IAC_CLK_ENABLE();
  __HAL_RCC_IAC_FORCE_RESET();
  __HAL_RCC_IAC_RELEASE_RESET();
}

static void MPU_Config(void)
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

/**
 * @brief  Probe the WM8904 audio codec.
 * @param  None
 * @retval None
 */
static void WM8904_Probe(void)
{
	WM8904_IO_t              IOCtx;
	uint32_t                 wm8904_id;
	static WM8904_Object_t   WM8904Obj;

	/* Configure the audio driver */
	IOCtx.Address     = 0x34U;
	IOCtx.Init        = BSP_I2C2_Init;
	IOCtx.DeInit      = BSP_I2C2_DeInit;
	IOCtx.ReadReg     = BSP_I2C2_ReadReg;
	IOCtx.WriteReg    = BSP_I2C2_WriteReg;
	IOCtx.GetTick     = BSP_GetTick;

	if (WM8904_RegisterBusIO(&WM8904Obj, &IOCtx) != WM8904_OK)
	{
		Error_Handler();
	}
	else if (WM8904_ReadID(&WM8904Obj, &wm8904_id) != WM8904_OK)
	{
		Error_Handler();
	}
	else if ((wm8904_id & WM8904_ID_MASK) != WM8904_ID)
	{
		Error_Handler();
	}
	else
	{
		Audio_Drv = (AUDIO_Drv_t *) &WM8904_Driver;
		Audio_CompObj = &WM8904Obj;
	}
}

static void Playback_Init(void)
{
	/* Probe the audio codec */
	WM8904_Probe();

	/* Initialize SAI peripheral */
	//MX_SAI1_Init();

	/* Initialize audio codec */
	WM8904_Init_t codec_init;
	codec_init.InputDevice  = WM8904_IN_NONE;
	codec_init.OutputDevice = WM8904_OUT_HEADPHONE;
	codec_init.Resolution   = WM8904_RESOLUTION_16B;
	codec_init.Frequency    = WM8904_FREQUENCY_16K;
	codec_init.Volume       = 80U;
	if (Audio_Drv->Init(Audio_CompObj, &codec_init) < 0)
	{
		Error_Handler();
	}
	if (Audio_Drv->Play(Audio_CompObj) != 0)
	{
		Error_Handler();
	}
}

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

static void InitAudioCapture(AudioAcqCtx_t *AudioAcqCtx)
{
	AudioAcqCtx->ring_buff.nbSamples = ((PATCH_LENGTH / AUDIO_BUFFER_SIZE) + 1 ) \
			* AUDIO_BUFFER_SIZE ;
	AudioAcqCtx->ring_buff.readSampleIndex  = 0 ;
	AudioAcqCtx->ring_buff.writeSampleIndex = 0 ;
	AudioAcqCtx->ring_buff.nbBytesPerSample = 2;
	AudioAcqCtx->ring_buff.nbFrames = 2;

	AudioCapture_ring_buff_alloc(&AudioAcqCtx->ring_buff);
}

static void InitAudioPlayback(AudioPlayBackCtx_t *AudioPlayBackCtx)
{
	AudioPlayBackCtx->ring_buff.nbSamples = PATCH_LENGTH * 4;
	AudioPlayBackCtx->ring_buff.readSampleIndex  = 0 ;
	AudioPlayBackCtx->ring_buff.writeSampleIndex = 0 ;
	AudioPlayBackCtx->ring_buff.nbFrames = 1;
	AudioPlayBackCtx->ring_buff.nbBytesPerSample = 2;

	AudioCapture_ring_buff_alloc(&AudioPlayBackCtx->ring_buff);
}

/**
 * @brief  Initializes all Audio processing
 * @param  proc_ctx_ptr pointer to processing context
 * @retval None
 */
void InitAudioProc(AudioProcCtx_t *AudioProcCtx)
{
  struct npu_model_info *pxInfo;

  /* get the AI model */
  AiDPULoadModel( &AudioProcCtx->AICtx, CTRL_X_CUBE_AI_MODEL_NAME );
  pxInfo     = &AudioProcCtx->AICtx.net_exec_ctx->info;
  AudioProcCtx->AIInputPtr = (int8_t *) LL_Buffer_addr_start(pxInfo->in_bufs[0]);
  AudioProcCtx->AIOutputPtr = pxInfo->out_bufs[0] ;

  /* clear input samples array ( get silence on first overlayed patch */
  memset(AudioProcCtx->ProcBuffer,0,PATCH_LENGTH*sizeof(int16_t));
  /* Audio Preprocessing init */
  PreProc_DPUInit(&AudioProcCtx->AudioPreCtx);
  /* Audio Postprocessing init */
  PostProc_DPUInit(&AudioProcCtx->AudioPostCtx);
  /* transfer quantization parametres included in AI model to the Audio DPU   */
  AudioProcCtx->AudioPreCtx.output_Q_offset    = AudioProcCtx->AICtx.input_Q_offset;
  AudioProcCtx->AudioPreCtx.output_Q_inv_scale =
            (PREPROC_FLOAT_T) AudioProcCtx->AICtx.input_Q_inv_scale;
  AudioProcCtx->AudioPreCtx.quant.output_Q_inv_scale = AudioProcCtx->AudioPreCtx.output_Q_inv_scale;
  AudioProcCtx->AudioPreCtx.quant.output_Q_offset = AudioProcCtx->AudioPreCtx.output_Q_offset;
  //AudioProcCtx->cnt = 0;
}

/**
* @brief  Displays System Settings
* @param  None
* @retval None
*/
void displaySystemSetting(void)
{
  my_printf("\n\r");
  my_printf(SEPARATION_LINE);
  my_printf("        System configuration (%s)\n\r",APP_CONF_STR);
  my_printf(SEPARATION_LINE);
  printf("\n\rLog Level: %s\n\n\r", getLogLevelStr(LOG_LEVEL));
  systemSettingLog();
  NPU_SettingsLog();
}

static void NPU_SettingsLog(void)
{
    struct mcu_conf sys_conf;
    getSysConf(&sys_conf);
    my_printf("\n\rNPU Runtime configuration...\r\n");
    my_printf(" NPU clock    : %u MHz\r\n", (int)sys_conf.extra[1]/1000000);
    my_printf(" NIC clock    : %u MHz\r\n", (int)sys_conf.extra[2]/1000000);
}




















