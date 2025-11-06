/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins
     OTG2_HSDM   ------> USB2_OTG_HS_DM
     OTG1_HSDM   ------> USB1_OTG_HS_DM
     UCPD1_CC1   ------> UCPD1_CC1
     PH0-OSC_IN(PH0)   ------> RCC_OSC_IN
     PC1   ------> I2C1_SDA
     PC4   ------> SDMMC2_D0
     PE8   ------> MDF1_SDI0
     PH3   ------> LTDC_B4
     PH6   ------> LTDC_B5
     OTG2_HSDP   ------> USB2_OTG_HS_DP
     OTG1_HSDP   ------> USB1_OTG_HS_DP
     UCPD1_CC2   ------> UCPD1_CC2
     PH1-OSC_OUT(PH1)   ------> RCC_OSC_OUT
     PC5   ------> SDMMC2_D1
     PE7   ------> MDF1_CKI0
     PD15   ------> LTDC_R2
     PD4   ------> I2C2_SDA
     PB14   ------> LTDC_HSYNC
     PC15-OSC32_OUT(OSC32_OUT)   ------> RCC_OSC32_OUT
     OTG1_ID   ------> USB1_OTG_HS_ID
     PC0   ------> SDMMC2_D2
     PD14   ------> I2C2_SCL
     PB2   ------> LTDC_B2
     PC14-OSC32_IN(OSC32_IN)   ------> RCC_OSC32_IN
     PH9   ------> I2C1_SCL
     PC2   ------> SDMMC2_CK
     PE4   ------> SDMMC2_D3
     PB15   ------> LTDC_G4
     PC3   ------> SDMMC2_CMD
     PE11   ------> LTDC_VSYNC
     PD8   ------> LTDC_R7
     PB0   ------> SAI1_FS_A
     PB7   ------> SAI1_SD_A
     PB6   ------> SAI1_SCK_A
     PH4   ------> LTDC_R4
     PE3   ------> SAI1_SD_B
     PE2   ------> MDF1_CCK0
     PE0   ------> TAMP_IN6
     PP7   ------> XSPIM_P1_IO7
     PP6   ------> XSPIM_P1_IO6
     PP0   ------> XSPIM_P1_IO0
     PD9   ------> LTDC_R1
     PP4   ------> XSPIM_P1_IO4
     PP1   ------> XSPIM_P1_IO1
     PP15   ------> XSPIM_P1_IO15
     PP5   ------> XSPIM_P1_IO5
     PP12   ------> XSPIM_P1_IO12
     PP3   ------> XSPIM_P1_IO3
     PP2   ------> XSPIM_P1_IO2
     PP13   ------> XSPIM_P1_IO13
     PO2   ------> XSPIM_P1_DQS0
     PG7   ------> SAI1_MCLK_A
     PG6   ------> LTDC_B3
     PP11   ------> XSPIM_P1_IO11
     PP8   ------> XSPIM_P1_IO8
     PP14   ------> XSPIM_P1_IO14
     PO3   ------> XSPIM_P1_DQS1
     PO0   ------> XSPIM_P1_NCS1
     PP9   ------> XSPIM_P1_IO9
     PP10   ------> XSPIM_P1_IO10
     PO4   ------> XSPIM_P1_CLK
     PN4   ------> XSPIM_P2_IO2
     CSI_REXT   ------> CSI_REXT
     PA1   ------> LTDC_G2
     PB11   ------> LTDC_G6
     PA15(JTDI)   ------> LTDC_R5
     PN6   ------> XSPIM_P2_CLK
     PN8   ------> XSPIM_P2_IO4
     PN0   ------> XSPIM_P2_DQS0
     PG15   ------> LTDC_B0
     PG1   ------> LTDC_G1
     PB12   ------> LTDC_G5
     PA7   ------> LTDC_B1
     PG0   ------> LTDC_R0
     PN3   ------> XSPIM_P2_IO1
     PN5   ------> XSPIM_P2_IO3
     PN1   ------> XSPIM_P2_NCS1
     CSI_CKP   ------> CSI_CKP
     CSI_D1P   ------> CSI_D1P
     CSI_D0P   ------> CSI_D0P
     PA14(JTCK/SWCLK)   ------> DEBUG_JTCK-SWCLK
     PA2   ------> LTDC_B7
     PG12   ------> LTDC_G0
     PB4(NJTRST)   ------> LTDC_R3
     PG8   ------> LTDC_G7
     PN9   ------> XSPIM_P2_IO5
     PN2   ------> XSPIM_P2_IO0
     CSI_CKN   ------> CSI_CKN
     CSI_D1N   ------> CSI_D1N
     CSI_D0N   ------> CSI_D0N
     PA13(JTMS/SWDIO)   ------> DEBUG_JTMS-SWDIO
     PA8   ------> RCC_MCO_1
     PG13   ------> LTDC_DE
     PA0   ------> LTDC_G3
     PB5(JTDO/TRACESWO)   ------> DEBUG_JTDO-SWO
     PG11   ------> LTDC_R6
     PN10   ------> XSPIM_P2_IO6
     PN11   ------> XSPIM_P2_IO7
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOP_CLK_ENABLE();
  __HAL_RCC_GPIOO_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPION_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : I2C1_SDA_Pin */
  GPIO_InitStruct.Pin = I2C1_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
  HAL_GPIO_Init(I2C1_SDA_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SD_D0_Pin SD_D1_Pin SD_D2_Pin SD_CMD_Pin */
  GPIO_InitStruct.Pin = SD_D0_Pin|SD_D1_Pin|SD_D2_Pin|SD_CMD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  GPIO_InitStruct.Alternate = GPIO_AF11_SDMMC2;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : MIC_D1_Pin PE7 MIC_CK_Pin */
  GPIO_InitStruct.Pin = MIC_D1_Pin|GPIO_PIN_7|MIC_CK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_MDF1;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_B4_Pin LCD_B5_Pin LCD_R4_Pin */
  GPIO_InitStruct.Pin = LCD_B4_Pin|LCD_B5_Pin|LCD_R4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_R2_Pin LCD_R7_Pin LCD_R1_Pin */
  GPIO_InitStruct.Pin = LCD_R2_Pin|LCD_R7_Pin|LCD_R1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : I2C2_SDA_Pin I2C2_SCL_Pin */
  GPIO_InitStruct.Pin = I2C2_SDA_Pin|I2C2_SCL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_HSYNC_Pin LCD_B2_Pin LCD_G4_Pin LCD_G6_Pin
                           LCD_G5_Pin LCD_R3_Pin */
  GPIO_InitStruct.Pin = LCD_HSYNC_Pin|LCD_B2_Pin|LCD_G4_Pin|LCD_G6_Pin
                          |LCD_G5_Pin|LCD_R3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : I2C1_SCL_Pin */
  GPIO_InitStruct.Pin = I2C1_SCL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
  HAL_GPIO_Init(I2C1_SCL_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SD_CK_Pin */
  GPIO_InitStruct.Pin = SD_CK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_SDMMC2;
  HAL_GPIO_Init(SD_CK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SD_D3_Pin */
  GPIO_InitStruct.Pin = SD_D3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  GPIO_InitStruct.Alternate = GPIO_AF11_SDMMC2;
  HAL_GPIO_Init(SD_D3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_VSYNC_Pin */
  GPIO_InitStruct.Pin = LCD_VSYNC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
  HAL_GPIO_Init(LCD_VSYNC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SAI1_FS_A_Pin SAI1_SD_A_Pin SAI1_CLK_A_Pin */
  GPIO_InitStruct.Pin = SAI1_FS_A_Pin|SAI1_SD_A_Pin|SAI1_CLK_A_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_SAI1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : User_Pin */
  GPIO_InitStruct.Pin = User_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(User_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SAI1_SD_B_Pin */
  GPIO_InitStruct.Pin = SAI1_SD_B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_SAI1;
  HAL_GPIO_Init(SAI1_SD_B_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : HEXASPI_IO_7_Pin HEXASPI_IO_6_Pin HEXASPI_IO_0_Pin HEXASPI_IO_4_Pin
                           HEXASPI_IO_1_Pin HEXASPI_IO_15_Pin HEXASPI_IO_5_Pin HEXASPI_IO_12_Pin
                           HEXASPI_IO_3_Pin HEXASPI_IO_2_Pin HEXASPI_IO_13_Pin HEXASPI_IO_11_Pin
                           HEXASPI_IO_8_Pin HEXASPI_IO_14_Pin HEXASPI_IO_9_Pin HEXASPI_IO_10_Pin */
  GPIO_InitStruct.Pin = HEXASPI_IO_7_Pin|HEXASPI_IO_6_Pin|HEXASPI_IO_0_Pin|HEXASPI_IO_4_Pin
                          |HEXASPI_IO_1_Pin|HEXASPI_IO_15_Pin|HEXASPI_IO_5_Pin|HEXASPI_IO_12_Pin
                          |HEXASPI_IO_3_Pin|HEXASPI_IO_2_Pin|HEXASPI_IO_13_Pin|HEXASPI_IO_11_Pin
                          |HEXASPI_IO_8_Pin|HEXASPI_IO_14_Pin|HEXASPI_IO_9_Pin|HEXASPI_IO_10_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF9_XSPIM_P1;
  HAL_GPIO_Init(GPIOP, &GPIO_InitStruct);

  /*Configure GPIO pins : HEXASPI_DQS0_Pin HEXASPI_DQS1_Pin HEXASPI_NCS_Pin HEXASPI_CLK_Pin */
  GPIO_InitStruct.Pin = HEXASPI_DQS0_Pin|HEXASPI_DQS1_Pin|HEXASPI_NCS_Pin|HEXASPI_CLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF9_XSPIM_P1;
  HAL_GPIO_Init(GPIOO, &GPIO_InitStruct);

  /*Configure GPIO pin : SAI1_MCLK_A_Pin */
  GPIO_InitStruct.Pin = SAI1_MCLK_A_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_SAI1;
  HAL_GPIO_Init(SAI1_MCLK_A_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_B3_Pin LCD_B0_Pin LCD_G1_Pin LCD_R0_Pin
                           LCD_G0_Pin LCd_G7_Pin LCD_DE_Pin LCD_R6_Pin */
  GPIO_InitStruct.Pin = LCD_B3_Pin|LCD_B0_Pin|LCD_G1_Pin|LCD_R0_Pin
                          |LCD_G0_Pin|LCd_G7_Pin|LCD_DE_Pin|LCD_R6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : OCTOSPI_IO2_Pin OCTOSPI_CLK_Pin OCTOSPI_IO4_Pin OCTOSPI_DQS_Pin
                           OCTOSPI_IO1_Pin OCTOSPI_IO3_Pin OCTOSPI_NCS_Pin OCTOSPI_IO5_Pin
                           OCTOSPI_IO0_Pin OCTOSPI_IO6_Pin OCTOSPI_IO7_Pin */
  GPIO_InitStruct.Pin = OCTOSPI_IO2_Pin|OCTOSPI_CLK_Pin|OCTOSPI_IO4_Pin|OCTOSPI_DQS_Pin
                          |OCTOSPI_IO1_Pin|OCTOSPI_IO3_Pin|OCTOSPI_NCS_Pin|OCTOSPI_IO5_Pin
                          |OCTOSPI_IO0_Pin|OCTOSPI_IO6_Pin|OCTOSPI_IO7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF9_XSPIM_P2;
  HAL_GPIO_Init(GPION, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_G2_Pin LCD_R5_Pin LCD_B1_Pin LCD_B7_Pin
                           LCD_G3_Pin */
  GPIO_InitStruct.Pin = LCD_G2_Pin|LCD_R5_Pin|LCD_B1_Pin|LCD_B7_Pin
                          |LCD_G3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure the EXTI line attribute */
  HAL_EXTI_ConfigLineAttributes(EXTI_LINE_13, EXTI_LINE_SEC);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
