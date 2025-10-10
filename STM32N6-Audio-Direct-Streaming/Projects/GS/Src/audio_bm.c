/**
  ******************************************************************************
  * @file    audio_bm.c
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    02-May-2025
  * @brief
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32n6xx_hal.h"
#include "stm32n6570_discovery.h"
#include "stm32n6570_discovery_xspi.h"
#include "stm32n6570_discovery_audio.h"
#include "app_config.h"
#include "system_clock_config.h"
#include "misc_toolbox.h"
//#include "test.h"
#include "audio_bm.h"

/* Private define ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void IAC_Config(void);
static void MPU_Config(void);
static void Ext_Mem_Config(void);
static void Int_Mem_Config(void);
static void SleepClks_init(void);
static void Error_Handler(void);
static void Record_Init(void);

static void initAudioPlayBack(void);

/* Private variables ---------------------------------------------------------*/
#define BUFFER_SIZE (256)
static int16_t capture_buffer[BUFFER_SIZE];
static int16_t playback_buffer[BUFFER_SIZE];
static int32_t current_playback_half_buffer_to_copy_to;
static int32_t first_half_transfert_callback_flag;

/**
  * @brief  Initializes the system according to the application
  *         system requirement.
  * @param  None
  * @retval None
  */
void init_bm(void)
{
  /* Power on ICACHE */
  MEMSYSCTL->MSCR |= MEMSYSCTL_MSCR_ICACTIVE_Msk;

  /* Set back system and CPU clock source to HSI */
  __HAL_RCC_CPUCLK_CONFIG(RCC_CPUCLKSOURCE_HSI);
  __HAL_RCC_SYSCLK_CONFIG(RCC_SYSCLKSOURCE_HSI);

  HAL_Init();

  SystemClock_Config_Full();

  fuse_vddio();

  MPU_Config();
  Int_Mem_Config();
  Ext_Mem_Config();

  IAC_Config();
  SCB_EnableICache();
  //SCB_EnableDCache(); // /!\ Cette fonction casse tout /!\

  /* BSP inits */
  UART_Config();
  BSP_PB_Init(BUTTON_USER1, BUTTON_MODE_EXTI);
  BSP_PB_Init(BUTTON_TAMP, BUTTON_MODE_EXTI);
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Init(LED_RED);
}

/**
  * @brief  main loop for bare metal implementation.
  * @param  None
  * @retval None
  */

float32_t meanSoundBufferMag(int8_t * buff, int32_t nbOfBytes)
{
	float32_t mean = 0.0f;
	for (int32_t  byteIndex = 0; byteIndex < nbOfBytes; byteIndex++)
	{
		mean += (((float32_t)abs(buff[byteIndex])) / (float32_t) nbOfBytes);
	}
	return mean;
}

void exec_bm(void)
{
  bool cont = true;
  //time_stats_init();

  initAudioCapture();
  initAudioPlayBack();
  startAudioCapture(capture_buffer);

  //printHeader();

  int32_t last_half_playback_buffer = current_playback_half_buffer_to_copy_to;
  int32_t LedCounter = 0;

  while(cont)
  {
    __NOP(); /* to be resilient to gcc optim ... to investigate */

     if (last_half_playback_buffer != current_playback_half_buffer_to_copy_to)
     {
    	 last_half_playback_buffer = current_playback_half_buffer_to_copy_to;
    	 LedCounter += 1;
     }
     if (LedCounter == 10)
     {
    	 LedCounter = 0;
    	 BSP_LED_Toggle(LED_GREEN);
     }

  }
  stopAudioCapture();

  stopAudioPlayBack();

  test_dump();
  my_printf("\n\r# End Processing\n\r");
}

/**
* @brief  Initializes Audio capture from microphone
* @param  None
* @retval None
*/
void initAudioCapture(void)
{
  /* Initialize record */
  Record_Init();
}

/**
* @brief  Starts Audio capture from microphone
* @param  capture_buffer pointer to acquisition buffer
* @retval None
*/
void startAudioCapture(int16_t *capture_buffer)
{
  /* Start record */
  if (BSP_ERROR_NONE != BSP_AUDIO_IN_Record(1, (uint8_t *) capture_buffer,
                                         BUFFER_SIZE * sizeof(int16_t)))
  {
    Error_Handler();
  }

  first_half_transfert_callback_flag = 1;
}

/**
* @brief  Stops Audio Playback
* @param  None
* @retval None
*/
void stopAudioPlayBack(void)
{
  BSP_AUDIO_OUT_Stop(1);
}

/**
* @brief  Stops Audio Capture
* @param  None
* @retval None
*/
void stopAudioCapture(void)
{
  BSP_AUDIO_IN_Stop(1);
}

/**
* @brief  Manage the BSP audio in transfer complete event.
* @param  Instance Audio in instance.
* @retval None.
*/
void BSP_AUDIO_IN_TransferComplete_CallBack(uint32_t Instance)
{

  if (Instance == 1U)
  {
    //AudioCapture_half_buf_cb(&audio_acq_ctx.ring_buff, audio_acq_ctx.acq_buf, 1U);


	assert(first_half_transfert_callback_flag == 0);

    int16_t *half_capture_buff_to_copy_from = &capture_buffer[BUFFER_SIZE/2];
    int16_t *half_playback_buff_to_copy_to = &playback_buffer[current_playback_half_buffer_to_copy_to * BUFFER_SIZE/2];
    printf("Audio IN transfer complete : copying to playback half %d\r\n", current_playback_half_buffer_to_copy_to);
    memcpy(half_playback_buff_to_copy_to, half_capture_buff_to_copy_from, BUFFER_SIZE/2 * sizeof(int16_t));
    printf("Audio IN transfer complete : done \r\n");
  }
}

/**
* @brief  Manage the BSP audio in half transfer complete event.
* @param  Instance Audio in instance.
* @retval None.
*/
void BSP_AUDIO_IN_HalfTransfer_CallBack(uint32_t Instance)
{
	if (Instance == 1U)
	  {
	    //AudioCapture_half_buf_cb(&audio_acq_ctx.ring_buff, audio_acq_ctx.acq_buf, 0U);

	    int16_t *half_capture_buff_to_copy_from = capture_buffer;
	    int16_t *half_playback_buff_to_copy_to = &playback_buffer[current_playback_half_buffer_to_copy_to * BUFFER_SIZE/2];
	    printf("Audio IN half transfer to playback half %d\r\n", current_playback_half_buffer_to_copy_to);
	    memcpy(half_playback_buff_to_copy_to, half_capture_buff_to_copy_from, BUFFER_SIZE/2 * sizeof(int16_t));

	    if (first_half_transfert_callback_flag == 1)
	    {
	    	assert(current_playback_half_buffer_to_copy_to == 0);

	    	/* Start the playback */
	    	printf("Playback starting...\r\n");
			if (BSP_ERROR_NONE != BSP_AUDIO_OUT_Play(0, (uint8_t *)playback_buffer, \
			  BUFFER_SIZE * sizeof(int16_t)))
			{
			  Error_Handler();
			}

	    	first_half_transfert_callback_flag = 0;
	    	printf("Playback starting : done\r\n");
	    }
	    printf("Audio IN half transfer : done \r\n");
	  }
}

/**
  * @brief  Tx Transfer completed callbacks.
  * @param  None.
  * @retval None.
  */
void BSP_AUDIO_OUT_TransferComplete_CallBack(uint32_t Instance)
{
  //AudioCapture_ring_buff_consume_no_cpy(&audio_proc_ctx.audioPlayBackCtx.ring_buff, PLAYBACK_BUFFER_SIZE/2);
	printf("Audio OUT transfer complete\r\n");
	current_playback_half_buffer_to_copy_to = 1;
}

/**
  * @brief  Tx Transfer Half completed callbacks
  * @param  None.
  * @retval None.
  */
void BSP_AUDIO_OUT_HalfTransfer_CallBack(uint32_t Instance)
{
  //AudioCapture_ring_buff_consume_no_cpy(&audio_proc_ctx.audioPlayBackCtx.ring_buff, PLAYBACK_BUFFER_SIZE/2);
	printf("Audio OUT half transfer\r\n");
	current_playback_half_buffer_to_copy_to = 0;
}

/**
* @brief  Manages the BSP audio in error event.
* @param  Instance Audio in instance.
* @retval None.
*/
void BSP_AUDIO_IN_Error_CallBack(uint32_t Instance)
{
  Error_Handler();
}

void BSP_PB_Callback(Button_TypeDef Button)
{
	/*if (BUTTON_USER1 == Button)
  {
    toggle_audio_proc();
  }*/

}

/*==============================================================================
                    private  functions definition
 ============================================================================= */

/**
  * @brief  Playback initialization
  * @param  ctx_ptr play back execution context
  * @retval None
  */
static void initAudioPlayBack(void)
{
   BSP_AUDIO_Init_t AudioInit;

  /* Configure playback */
  AudioInit.Device        = AUDIO_OUT_DEVICE_HEADPHONE;
  AudioInit.SampleRate    = AUDIO_FREQUENCY;
  AudioInit.BitsPerSample = AUDIO_RESOLUTION_16B;
  AudioInit.ChannelsNbr   = 1;
  AudioInit.Volume        = 0; /* not used */

  if (BSP_ERROR_NONE != BSP_AUDIO_OUT_Init(0, &AudioInit))
  {
    Error_Handler();
  }
  current_playback_half_buffer_to_copy_to = 0;
}

static void Int_Mem_Config(void)
{
  RAMCFG_HandleTypeDef hramcfg = {0};

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_CRC_CLK_ENABLE();

#ifdef APP_LP
/*  hramcfg.Instance =  RAMCFG_SRAM2_AXI;
  HAL_RAMCFG_DisableAXISRAM(&hramcfg);
  HAL_RAMCFG_EnableAXISRAM(&hramcfg); */
  hramcfg.Instance =  RAMCFG_SRAM6_AXI;
  HAL_RAMCFG_EnableAXISRAM(&hramcfg);

  __HAL_RCC_CACHEAXIRAM_MEM_CLK_ENABLE();
  __HAL_RCC_AXISRAM6_MEM_CLK_ENABLE();

/*  __HAL_RCC_AXISRAM2_MEM_CLK_DISABLE(); */
  __HAL_RCC_AHBSRAM1_MEM_CLK_DISABLE();
  __HAL_RCC_AHBSRAM2_MEM_CLK_DISABLE();
  __HAL_RCC_BKPSRAM_MEM_CLK_DISABLE();

#else /* APP_LP */

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

#endif 
  /* Allow caches to be activated. Default value is 1, but the current boot sets it to 0 */
  MEMSYSCTL->MSCR |= MEMSYSCTL_MSCR_DCACTIVE_Msk | MEMSYSCTL_MSCR_ICACTIVE_Msk;
}

/**
* @brief  Record initialization
* @param  None
* @retval None
*/
static void Record_Init(void)
{
  BSP_AUDIO_Init_t AudioInit;
  uint32_t         GetData;

  /* Test of state */
  if (BSP_ERROR_NONE != BSP_AUDIO_IN_GetState(1, &GetData)) Error_Handler();
  if (GetData != AUDIO_IN_STATE_RESET) Error_Handler();

  AudioInit.Device        = AUDIO_IN_DEVICE_DIGITAL_MIC;
  AudioInit.SampleRate    = AUDIO_FREQUENCY;
  AudioInit.BitsPerSample = AUDIO_RESOLUTION_16B;
  AudioInit.ChannelsNbr   = 1;
  AudioInit.Volume        = 80; /* Not used */

  if (BSP_ERROR_NONE != BSP_AUDIO_IN_Init(1, &AudioInit))
  {
    Error_Handler();
  }

  /* Test of state */
  if (BSP_ERROR_NONE != BSP_AUDIO_IN_GetState(1, &GetData)) Error_Handler();
  if (GetData != AUDIO_IN_STATE_STOP) Error_Handler();

  /* Test set and get functions */
  if (BSP_ERROR_FEATURE_NOT_SUPPORTED != BSP_AUDIO_IN_SetVolume(1, 10)) Error_Handler();
  /*if (BSP_ERROR_NONE != BSP_AUDIO_IN_SetSampleRate(1, SAI_AUDIO_FREQUENCY_96K)) Error_Handler(); */
  if (BSP_ERROR_NONE != BSP_AUDIO_IN_SetDevice(1, AUDIO_IN_DEVICE_ANALOG_MIC)) Error_Handler();
  if (BSP_ERROR_FEATURE_NOT_SUPPORTED != BSP_AUDIO_IN_SetBitsPerSample(1, AUDIO_RESOLUTION_8B)) Error_Handler();
  if (BSP_ERROR_NONE != BSP_AUDIO_IN_SetBitsPerSample(1, AUDIO_RESOLUTION_16B)) Error_Handler();
  if (BSP_ERROR_FEATURE_NOT_SUPPORTED != BSP_AUDIO_IN_SetBitsPerSample(1, AUDIO_RESOLUTION_24B)) Error_Handler();
  if (BSP_ERROR_FEATURE_NOT_SUPPORTED != BSP_AUDIO_IN_SetBitsPerSample(1, AUDIO_RESOLUTION_32B)) Error_Handler();
  if (BSP_ERROR_FEATURE_NOT_SUPPORTED != BSP_AUDIO_IN_SetChannelsNbr(1, 2)) Error_Handler();
  if (BSP_ERROR_NONE != BSP_AUDIO_IN_SetChannelsNbr(1, 1)) Error_Handler();

  if (BSP_ERROR_FEATURE_NOT_SUPPORTED != BSP_AUDIO_IN_GetVolume(1, &GetData)) Error_Handler();
  if (BSP_ERROR_NONE != BSP_AUDIO_IN_GetSampleRate(1, &GetData)) Error_Handler();
  /*if (GetData != AUDIO_FREQUENCY_96K) Error_Handler();*/
  if (BSP_ERROR_NONE != BSP_AUDIO_IN_GetDevice(1, &GetData)) Error_Handler();
  if (GetData != AUDIO_IN_DEVICE_DIGITAL_MIC) Error_Handler();
  if (BSP_ERROR_NONE != BSP_AUDIO_IN_GetBitsPerSample(1, &GetData)) Error_Handler();
  if (GetData != AUDIO_RESOLUTION_16B) Error_Handler();
  if (BSP_ERROR_NONE != BSP_AUDIO_IN_GetChannelsNbr(1, &GetData)) Error_Handler();
  if (GetData != 1U) Error_Handler();

  /* Set the initial sample rate */
  if (BSP_ERROR_NONE != BSP_AUDIO_IN_SetSampleRate(1, AudioInit.SampleRate)) Error_Handler();
}

static void NPU_SettingsLog(void)
{
    struct mcu_conf sys_conf;
    getSysConf(&sys_conf);
    my_printf("\n\rNPU Runtime configuration...\r\n");
    my_printf(" NPU clock    : %u MHz\r\n", (int)sys_conf.extra[1]/1000000);
    my_printf(" NIC clock    : %u MHz\r\n", (int)sys_conf.extra[2]/1000000);
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

#ifdef USE_EXT_SRAM
  BSP_XSPI_RAM_Init(0);
  BSP_XSPI_RAM_EnableMemoryMappedMode(0);
  MODIFY_REG(XSPI1->CR, XSPI_CR_NOPREF, HAL_XSPI_AUTOMATIC_PREFETCH_DISABLE); /* Hotfix for xspi: no prefetch */
#endif
  
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

static void SleepClks_init(void)
{
  /* Keep all IP's enabled during WFE so they can wake up CPU. Fine tune
     this if you want to save maximum power
     this is specially needed when  LL_ATON_RT_MODE=LL_ATON_RT_ASYNC is used
  */
  LL_BUS_EnableClockLowPower(~0);
  LL_MEM_EnableClockLowPower(~0);
  LL_AHB1_GRP1_EnableClockLowPower(~0);
  LL_AHB2_GRP1_EnableClockLowPower(~0);
  LL_AHB3_GRP1_EnableClockLowPower(~0);
  LL_AHB4_GRP1_EnableClockLowPower(~0);
  LL_AHB5_GRP1_EnableClockLowPower(~0);
  LL_APB1_GRP1_EnableClockLowPower(~0);
  LL_APB1_GRP2_EnableClockLowPower(~0);
  LL_APB2_GRP1_EnableClockLowPower(~0);
  LL_APB4_GRP1_EnableClockLowPower(~0);
  LL_APB4_GRP2_EnableClockLowPower(~0);
  LL_APB5_GRP1_EnableClockLowPower(~0);
  LL_MISC_EnableClockLowPower(~0);
}

/**
* @brief  This function is executed in case of error occurrence.
* @param  None
* @retval None
*/
static void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}
