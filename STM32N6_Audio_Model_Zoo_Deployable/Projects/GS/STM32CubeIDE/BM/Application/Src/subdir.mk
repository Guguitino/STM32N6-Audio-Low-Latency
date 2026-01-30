################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/Src/AudioCapture_ring_buff.c \
../Application/Src/AudioMain.c \
../Application/Src/AudioProcess.c \
../Application/Src/LowPass_FirstOrder.c \
../Application/Src/TimerUtils.c \
../Application/Src/cpu_stats.c 

OBJS += \
./Application/Src/AudioCapture_ring_buff.o \
./Application/Src/AudioMain.o \
./Application/Src/AudioProcess.o \
./Application/Src/LowPass_FirstOrder.o \
./Application/Src/TimerUtils.o \
./Application/Src/cpu_stats.o 

C_DEPS += \
./Application/Src/AudioCapture_ring_buff.d \
./Application/Src/AudioMain.d \
./Application/Src/AudioProcess.d \
./Application/Src/LowPass_FirstOrder.d \
./Application/Src/TimerUtils.d \
./Application/Src/cpu_stats.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Src/%.o Application/Src/%.su Application/Src/%.cyclo: ../Application/Src/%.c Application/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DAPP_BARE_METAL -DUSE_HAL_DRIVER -DSTM32N657xx -DLL_ATON_PLATFORM=LL_ATON_PLAT_STM32N6 -DLL_ATON_OSAL=LL_ATON_OSAL_BARE_METAL -DLL_ATON_RT_MODE=LL_ATON_RT_ASYNC -DLL_ATON_SW_FALLBACK=1 -DLL_ATON_EB_DBG_INFO -DLL_ATON_DUMP_DEBUG_API -DLL_ATON_DBG_BUFFER_INFO_EXCLUDED=1 -c -I../../../../FSBL/Inc -I../../../../Drivers/CMSIS/DSP/PrivateInclude -I../../../../Drivers/CMSIS/DSP/Include -I../../../../Drivers/BSP/STM32N6570-DK -I../../../../Drivers/BSP/Components/Common -I../../../../Drivers/BSP/Components/wm8904 -I../../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../../Drivers/CMSIS/Include -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Application/Inc" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Application/Src" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Middlewares/ST/AI/Inc" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Middlewares/ST/AI/Npu/ll_aton" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Middlewares/ST/STM32_AI_AudioPreprocessing_Library/Inc" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Middlewares/ST/AI/Npu/Devices/STM32N6XX" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Application/ModelZoo/Inc" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Drivers/BSP/Components/mx66uw1g45g" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Drivers/BSP/STM32N6570-DK" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Drivers/BSP/Components/aps256xx" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/X-CUBE-AI" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/X-CUBE-AI/atonn" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/Dpu" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Application/Additional Drivers" -Og -ffunction-sections -fdata-sections -Wall -flax-vector-conversions -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-Src

clean-Application-2f-Src:
	-$(RM) ./Application/Src/AudioCapture_ring_buff.cyclo ./Application/Src/AudioCapture_ring_buff.d ./Application/Src/AudioCapture_ring_buff.o ./Application/Src/AudioCapture_ring_buff.su ./Application/Src/AudioMain.cyclo ./Application/Src/AudioMain.d ./Application/Src/AudioMain.o ./Application/Src/AudioMain.su ./Application/Src/AudioProcess.cyclo ./Application/Src/AudioProcess.d ./Application/Src/AudioProcess.o ./Application/Src/AudioProcess.su ./Application/Src/LowPass_FirstOrder.cyclo ./Application/Src/LowPass_FirstOrder.d ./Application/Src/LowPass_FirstOrder.o ./Application/Src/LowPass_FirstOrder.su ./Application/Src/TimerUtils.cyclo ./Application/Src/TimerUtils.d ./Application/Src/TimerUtils.o ./Application/Src/TimerUtils.su ./Application/Src/cpu_stats.cyclo ./Application/Src/cpu_stats.d ./Application/Src/cpu_stats.o ./Application/Src/cpu_stats.su

.PHONY: clean-Application-2f-Src

