################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/adamg/STApps/GS_Audio_N6/STM32N6-GettingStarted-Audio-main/Projects/X-CUBE-AI/atonn/ai_io_buffers.c \
/home/adamg/STApps/GS_Audio_N6/STM32N6-GettingStarted-Audio-main/Projects/X-CUBE-AI/atonn/ai_wrapper_ATON.c 

OBJS += \
./Application/X-CUBE-AI/atonn/ai_io_buffers.o \
./Application/X-CUBE-AI/atonn/ai_wrapper_ATON.o 

C_DEPS += \
./Application/X-CUBE-AI/atonn/ai_io_buffers.d \
./Application/X-CUBE-AI/atonn/ai_wrapper_ATON.d 


# Each subdirectory must supply rules for building sources it contributes
Application/X-CUBE-AI/atonn/ai_io_buffers.o: /home/adamg/STApps/GS_Audio_N6/STM32N6-GettingStarted-Audio-main/Projects/X-CUBE-AI/atonn/ai_io_buffers.c Application/X-CUBE-AI/atonn/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DSTM32N657xx -DARM_MATH_CM55 -DUSE_FULL_ASSERT -DUSE_FULL_LL_DRIVER -DVECT_TAB_SRAM -DLL_ATON_PLATFORM=LL_ATON_PLAT_STM32N6 -DLL_ATON_OSAL=LL_ATON_OSAL_BARE_METAL -DLL_ATON_RT_MODE=LL_ATON_RT_ASYNC -DLL_ATON_SW_FALLBACK -DLL_ATON_EB_DBG_INFO -DLL_ATON_DUMP_DEBUG_API -DLL_ATON_DBG_BUFFER_INFO_EXCLUDED=1 -DAPP_BARE_METAL -c -I../../Inc -I../../../Dpu -I../../../Common -I../../../X-CUBE-AI/atonn -I../../../X-CUBE-AI -I../../../../Drivers/CMSIS/Core/Include -I../../../../Drivers/CMSIS/DSP/Include -I../../../../Drivers/CMSIS/DSP/PrivateInclude -I../../../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../../../Drivers/CMSIS/Device/ST/STM32N6xx/Include/Templates -I../../../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../../../Middlewares/ST/ThreadX/ports/cortex_m55/gnu/inc -I../../../../Middlewares/ST/ThreadX/common/inc -I../../../../Middlewares/ST/AI/Inc -I../../../../Middlewares/ST/AI/Npu/Devices/STM32N6XX -I../../../../Middlewares/ST/AI/Npu/ll_aton -I../../../../Middlewares/ST/STM32_AI_AudioPreprocessing_Library/Inc -I../../../../Drivers/BSP/Components/mx66uw1g45g -I../../../../Drivers/BSP/STM32N6570-DK -O0 -ffunction-sections -fdata-sections -Wall -flax-vector-conversions -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/X-CUBE-AI/atonn/ai_wrapper_ATON.o: /home/adamg/STApps/GS_Audio_N6/STM32N6-GettingStarted-Audio-main/Projects/X-CUBE-AI/atonn/ai_wrapper_ATON.c Application/X-CUBE-AI/atonn/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DSTM32N657xx -DARM_MATH_CM55 -DUSE_FULL_ASSERT -DUSE_FULL_LL_DRIVER -DVECT_TAB_SRAM -DLL_ATON_PLATFORM=LL_ATON_PLAT_STM32N6 -DLL_ATON_OSAL=LL_ATON_OSAL_BARE_METAL -DLL_ATON_RT_MODE=LL_ATON_RT_ASYNC -DLL_ATON_SW_FALLBACK -DLL_ATON_EB_DBG_INFO -DLL_ATON_DUMP_DEBUG_API -DLL_ATON_DBG_BUFFER_INFO_EXCLUDED=1 -DAPP_BARE_METAL -c -I../../Inc -I../../../Dpu -I../../../Common -I../../../X-CUBE-AI/atonn -I../../../X-CUBE-AI -I../../../../Drivers/CMSIS/Core/Include -I../../../../Drivers/CMSIS/DSP/Include -I../../../../Drivers/CMSIS/DSP/PrivateInclude -I../../../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../../../Drivers/CMSIS/Device/ST/STM32N6xx/Include/Templates -I../../../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../../../Middlewares/ST/ThreadX/ports/cortex_m55/gnu/inc -I../../../../Middlewares/ST/ThreadX/common/inc -I../../../../Middlewares/ST/AI/Inc -I../../../../Middlewares/ST/AI/Npu/Devices/STM32N6XX -I../../../../Middlewares/ST/AI/Npu/ll_aton -I../../../../Middlewares/ST/STM32_AI_AudioPreprocessing_Library/Inc -I../../../../Drivers/BSP/Components/mx66uw1g45g -I../../../../Drivers/BSP/STM32N6570-DK -O0 -ffunction-sections -fdata-sections -Wall -flax-vector-conversions -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-X-2d-CUBE-2d-AI-2f-atonn

clean-Application-2f-X-2d-CUBE-2d-AI-2f-atonn:
	-$(RM) ./Application/X-CUBE-AI/atonn/ai_io_buffers.cyclo ./Application/X-CUBE-AI/atonn/ai_io_buffers.d ./Application/X-CUBE-AI/atonn/ai_io_buffers.o ./Application/X-CUBE-AI/atonn/ai_io_buffers.su ./Application/X-CUBE-AI/atonn/ai_wrapper_ATON.cyclo ./Application/X-CUBE-AI/atonn/ai_wrapper_ATON.d ./Application/X-CUBE-AI/atonn/ai_wrapper_ATON.o ./Application/X-CUBE-AI/atonn/ai_wrapper_ATON.su

.PHONY: clean-Application-2f-X-2d-CUBE-2d-AI-2f-atonn

