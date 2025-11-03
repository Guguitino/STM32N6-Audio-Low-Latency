/**
  ******************************************************************************
  * @file    network.h
  * @author  STEdgeAI
  * @date    2025-10-29 12:43:45
  * @brief   Minimal description of the generated c-implemention of the network
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */
#ifndef LL_ATON_DEFAULT_H
#define LL_ATON_DEFAULT_H

/******************************************************************************/
#define LL_ATON_DEFAULT_C_MODEL_NAME        "Default"
#define LL_ATON_DEFAULT_ORIGIN_MODEL_NAME   "ssd_mobilenet_v2_fpnlite_035_192_int8"

/************************** USER ALLOCATED IOs ********************************/
// No user allocated inputs
// No user allocated outputs

/************************** INPUTS ********************************************/
#define LL_ATON_DEFAULT_IN_NUM        (1)    // Total number of input buffers
// Input buffer 1 -- Input_2_out_0
#define LL_ATON_DEFAULT_IN_1_ALIGNMENT   (32)
#define LL_ATON_DEFAULT_IN_1_SIZE_BYTES  (110592)

/************************** OUTPUTS *******************************************/
#define LL_ATON_DEFAULT_OUT_NUM        (3)    // Total number of output buffers
// Output buffer 1 -- Transpose_550_out_0
#define LL_ATON_DEFAULT_OUT_1_ALIGNMENT   (32)
#define LL_ATON_DEFAULT_OUT_1_SIZE_BYTES  (30760)
// Output buffer 2 -- Transpose_564_out_0
#define LL_ATON_DEFAULT_OUT_2_ALIGNMENT   (32)
#define LL_ATON_DEFAULT_OUT_2_SIZE_BYTES  (61520)
// Output buffer 3 -- Identity_1_out_0
#define LL_ATON_DEFAULT_OUT_3_ALIGNMENT   (32)
#define LL_ATON_DEFAULT_OUT_3_SIZE_BYTES  (61520)

#endif /* LL_ATON_DEFAULT_H */
