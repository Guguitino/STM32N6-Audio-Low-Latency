################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/AI/Npu/ll_aton/ecloader.c \
../Middlewares/ST/AI/Npu/ll_aton/ll_aton.c \
../Middlewares/ST/AI/Npu/ll_aton/ll_aton_cipher.c \
../Middlewares/ST/AI/Npu/ll_aton/ll_aton_dbgtrc.c \
../Middlewares/ST/AI/Npu/ll_aton/ll_aton_debug.c \
../Middlewares/ST/AI/Npu/ll_aton/ll_aton_lib.c \
../Middlewares/ST/AI/Npu/ll_aton/ll_aton_lib_sw_operators.c \
../Middlewares/ST/AI/Npu/ll_aton/ll_aton_osal_freertos.c \
../Middlewares/ST/AI/Npu/ll_aton/ll_aton_osal_zephyr.c \
../Middlewares/ST/AI/Npu/ll_aton/ll_aton_profiler.c \
../Middlewares/ST/AI/Npu/ll_aton/ll_aton_reloc_callbacks.c \
../Middlewares/ST/AI/Npu/ll_aton/ll_aton_reloc_network.c \
../Middlewares/ST/AI/Npu/ll_aton/ll_aton_rt_main.c \
../Middlewares/ST/AI/Npu/ll_aton/ll_aton_runtime.c \
../Middlewares/ST/AI/Npu/ll_aton/ll_aton_util.c \
../Middlewares/ST/AI/Npu/ll_aton/ll_sw_float.c \
../Middlewares/ST/AI/Npu/ll_aton/ll_sw_integer.c 

OBJS += \
./Middlewares/ST/AI/Npu/ll_aton/ecloader.o \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton.o \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_cipher.o \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_dbgtrc.o \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_debug.o \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_lib.o \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_lib_sw_operators.o \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_osal_freertos.o \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_osal_zephyr.o \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_profiler.o \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_reloc_callbacks.o \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_reloc_network.o \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_rt_main.o \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_runtime.o \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_util.o \
./Middlewares/ST/AI/Npu/ll_aton/ll_sw_float.o \
./Middlewares/ST/AI/Npu/ll_aton/ll_sw_integer.o 

C_DEPS += \
./Middlewares/ST/AI/Npu/ll_aton/ecloader.d \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton.d \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_cipher.d \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_dbgtrc.d \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_debug.d \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_lib.d \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_lib_sw_operators.d \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_osal_freertos.d \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_osal_zephyr.d \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_profiler.d \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_reloc_callbacks.d \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_reloc_network.d \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_rt_main.d \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_runtime.d \
./Middlewares/ST/AI/Npu/ll_aton/ll_aton_util.d \
./Middlewares/ST/AI/Npu/ll_aton/ll_sw_float.d \
./Middlewares/ST/AI/Npu/ll_aton/ll_sw_integer.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/AI/Npu/ll_aton/%.o Middlewares/ST/AI/Npu/ll_aton/%.su Middlewares/ST/AI/Npu/ll_aton/%.cyclo: ../Middlewares/ST/AI/Npu/ll_aton/%.c Middlewares/ST/AI/Npu/ll_aton/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DAPP_BARE_METAL -DUSE_HAL_DRIVER -DSTM32N657xx -DLL_ATON_PLATFORM=LL_ATON_PLAT_STM32N6 -DLL_ATON_OSAL=LL_ATON_OSAL_BARE_METAL -DLL_ATON_RT_MODE=LL_ATON_RT_ASYNC -DLL_ATON_SW_FALLBACK=1 -DLL_ATON_EB_DBG_INFO -DLL_ATON_DUMP_DEBUG_API -DLL_ATON_DBG_BUFFER_INFO_EXCLUDED=1 -c -I../../../../FSBL/Inc -I../../../../Drivers/CMSIS/DSP/PrivateInclude -I../../../../Drivers/CMSIS/DSP/Include -I../../../../Drivers/BSP/STM32N6570-DK -I../../../../Drivers/BSP/Components/Common -I../../../../Drivers/BSP/Components/wm8904 -I../../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../../Drivers/CMSIS/Include -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Application/Inc" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Application/Src" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Middlewares/ST/AI/Inc" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Middlewares/ST/AI/Npu/ll_aton" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Middlewares/ST/STM32_AI_AudioPreprocessing_Library/Inc" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Middlewares/ST/AI/Npu/Devices/STM32N6XX" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Application/ModelZoo/Inc" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Drivers/BSP/Components/mx66uw1g45g" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Drivers/BSP/STM32N6570-DK" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Drivers/BSP/Components/aps256xx" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/X-CUBE-AI" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/X-CUBE-AI/atonn" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/Dpu" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Application/Additional Drivers" -Og -ffunction-sections -fdata-sections -Wall -flax-vector-conversions -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-AI-2f-Npu-2f-ll_aton

clean-Middlewares-2f-ST-2f-AI-2f-Npu-2f-ll_aton:
	-$(RM) ./Middlewares/ST/AI/Npu/ll_aton/ecloader.cyclo ./Middlewares/ST/AI/Npu/ll_aton/ecloader.d ./Middlewares/ST/AI/Npu/ll_aton/ecloader.o ./Middlewares/ST/AI/Npu/ll_aton/ecloader.su ./Middlewares/ST/AI/Npu/ll_aton/ll_aton.cyclo ./Middlewares/ST/AI/Npu/ll_aton/ll_aton.d ./Middlewares/ST/AI/Npu/ll_aton/ll_aton.o ./Middlewares/ST/AI/Npu/ll_aton/ll_aton.su ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_cipher.cyclo ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_cipher.d ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_cipher.o ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_cipher.su ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_dbgtrc.cyclo ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_dbgtrc.d ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_dbgtrc.o ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_dbgtrc.su ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_debug.cyclo ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_debug.d ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_debug.o ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_debug.su ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_lib.cyclo ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_lib.d ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_lib.o ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_lib.su ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_lib_sw_operators.cyclo ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_lib_sw_operators.d ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_lib_sw_operators.o ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_lib_sw_operators.su ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_osal_freertos.cyclo ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_osal_freertos.d ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_osal_freertos.o ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_osal_freertos.su ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_osal_zephyr.cyclo ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_osal_zephyr.d ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_osal_zephyr.o ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_osal_zephyr.su ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_profiler.cyclo ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_profiler.d ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_profiler.o ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_profiler.su ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_reloc_callbacks.cyclo ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_reloc_callbacks.d ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_reloc_callbacks.o ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_reloc_callbacks.su ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_reloc_network.cyclo ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_reloc_network.d ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_reloc_network.o ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_reloc_network.su ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_rt_main.cyclo ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_rt_main.d ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_rt_main.o ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_rt_main.su ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_runtime.cyclo ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_runtime.d ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_runtime.o ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_runtime.su ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_util.cyclo ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_util.d ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_util.o ./Middlewares/ST/AI/Npu/ll_aton/ll_aton_util.su ./Middlewares/ST/AI/Npu/ll_aton/ll_sw_float.cyclo ./Middlewares/ST/AI/Npu/ll_aton/ll_sw_float.d ./Middlewares/ST/AI/Npu/ll_aton/ll_sw_float.o ./Middlewares/ST/AI/Npu/ll_aton/ll_sw_float.su ./Middlewares/ST/AI/Npu/ll_aton/ll_sw_integer.cyclo ./Middlewares/ST/AI/Npu/ll_aton/ll_sw_integer.d ./Middlewares/ST/AI/Npu/ll_aton/ll_sw_integer.o ./Middlewares/ST/AI/Npu/ll_aton/ll_sw_integer.su

.PHONY: clean-Middlewares-2f-ST-2f-AI-2f-Npu-2f-ll_aton

