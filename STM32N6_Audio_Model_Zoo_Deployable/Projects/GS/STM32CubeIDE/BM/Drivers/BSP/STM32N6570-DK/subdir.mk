################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32N6570-DK/stm32n6570_discovery.c \
../Drivers/BSP/STM32N6570-DK/stm32n6570_discovery_bus.c \
../Drivers/BSP/STM32N6570-DK/stm32n6570_discovery_xspi.c 

OBJS += \
./Drivers/BSP/STM32N6570-DK/stm32n6570_discovery.o \
./Drivers/BSP/STM32N6570-DK/stm32n6570_discovery_bus.o \
./Drivers/BSP/STM32N6570-DK/stm32n6570_discovery_xspi.o 

C_DEPS += \
./Drivers/BSP/STM32N6570-DK/stm32n6570_discovery.d \
./Drivers/BSP/STM32N6570-DK/stm32n6570_discovery_bus.d \
./Drivers/BSP/STM32N6570-DK/stm32n6570_discovery_xspi.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32N6570-DK/%.o Drivers/BSP/STM32N6570-DK/%.su Drivers/BSP/STM32N6570-DK/%.cyclo: ../Drivers/BSP/STM32N6570-DK/%.c Drivers/BSP/STM32N6570-DK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DAPP_BARE_METAL -DUSE_HAL_DRIVER -DSTM32N657xx -DLL_ATON_PLATFORM=LL_ATON_PLAT_STM32N6 -DLL_ATON_OSAL=LL_ATON_OSAL_BARE_METAL -DLL_ATON_RT_MODE=LL_ATON_RT_ASYNC -DLL_ATON_SW_FALLBACK=1 -DLL_ATON_EB_DBG_INFO -DLL_ATON_DUMP_DEBUG_API -DLL_ATON_DBG_BUFFER_INFO_EXCLUDED=1 -c -I../../../../FSBL/Inc -I../../../../Drivers/CMSIS/DSP/PrivateInclude -I../../../../Drivers/CMSIS/DSP/Include -I../../../../Drivers/BSP/STM32N6570-DK -I../../../../Drivers/BSP/Components/Common -I../../../../Drivers/BSP/Components/wm8904 -I../../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../../Drivers/CMSIS/Include -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Application/Inc" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Application/Src" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Middlewares/ST/AI/Inc" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Middlewares/ST/AI/Npu/ll_aton" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Middlewares/ST/STM32_AI_AudioPreprocessing_Library/Inc" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Middlewares/ST/AI/Npu/Devices/STM32N6XX" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Application/ModelZoo/Inc" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Drivers/BSP/Components/mx66uw1g45g" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Drivers/BSP/STM32N6570-DK" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Drivers/BSP/Components/aps256xx" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/X-CUBE-AI" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/X-CUBE-AI/atonn" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/Dpu" -I"/home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency2/STM32N6_Audio_Model_Zoo_Deployable/Projects/GS/STM32CubeIDE/FSBL/Application/Additional Drivers" -Og -ffunction-sections -fdata-sections -Wall -flax-vector-conversions -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32N6570-2d-DK

clean-Drivers-2f-BSP-2f-STM32N6570-2d-DK:
	-$(RM) ./Drivers/BSP/STM32N6570-DK/stm32n6570_discovery.cyclo ./Drivers/BSP/STM32N6570-DK/stm32n6570_discovery.d ./Drivers/BSP/STM32N6570-DK/stm32n6570_discovery.o ./Drivers/BSP/STM32N6570-DK/stm32n6570_discovery.su ./Drivers/BSP/STM32N6570-DK/stm32n6570_discovery_bus.cyclo ./Drivers/BSP/STM32N6570-DK/stm32n6570_discovery_bus.d ./Drivers/BSP/STM32N6570-DK/stm32n6570_discovery_bus.o ./Drivers/BSP/STM32N6570-DK/stm32n6570_discovery_bus.su ./Drivers/BSP/STM32N6570-DK/stm32n6570_discovery_xspi.cyclo ./Drivers/BSP/STM32N6570-DK/stm32n6570_discovery_xspi.d ./Drivers/BSP/STM32N6570-DK/stm32n6570_discovery_xspi.o ./Drivers/BSP/STM32N6570-DK/stm32n6570_discovery_xspi.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32N6570-2d-DK

