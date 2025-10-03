################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
/home/adamg/STApps/GS_Audio_N6/STM32N6-GettingStarted-Audio-main/Drivers/CMSIS/Device/ST/STM32N6xx/Source/Templates/gcc/startup_stm32n657xx.s 

C_SRCS += \
/home/adamg/STApps/GS_Audio_N6/STM32N6-GettingStarted-Audio-main/Drivers/CMSIS/Device/ST/STM32N6xx/Source/Templates/system_stm32n6xx_fsbl.c 

OBJS += \
./Drivers/CMSIS/startup_stm32n657xx.o \
./Drivers/CMSIS/system_stm32n6xx_fsbl.o 

S_DEPS += \
./Drivers/CMSIS/startup_stm32n657xx.d 

C_DEPS += \
./Drivers/CMSIS/system_stm32n6xx_fsbl.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/startup_stm32n657xx.o: /home/adamg/STApps/GS_Audio_N6/STM32N6-GettingStarted-Audio-main/Drivers/CMSIS/Device/ST/STM32N6xx/Source/Templates/gcc/startup_stm32n657xx.s Drivers/CMSIS/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m55 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -c -I../../Inc -I../../ThreadX -I../../../../Middlewares/ST/ThreadX/ports/cortex_m55/gnu/inc -I../../../../Middlewares/ST/ThreadX/common/inc -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
Drivers/CMSIS/system_stm32n6xx_fsbl.o: /home/adamg/STApps/GS_Audio_N6/STM32N6-GettingStarted-Audio-main/Drivers/CMSIS/Device/ST/STM32N6xx/Source/Templates/system_stm32n6xx_fsbl.c Drivers/CMSIS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DSTM32N657xx -DARM_MATH_CM55 -DUSE_FULL_ASSERT -DUSE_FULL_LL_DRIVER -DVECT_TAB_SRAM -DLL_ATON_PLATFORM=LL_ATON_PLAT_STM32N6 -DLL_ATON_OSAL=LL_ATON_OSAL_BARE_METAL -DLL_ATON_RT_MODE=LL_ATON_RT_ASYNC -DLL_ATON_SW_FALLBACK -DLL_ATON_EB_DBG_INFO -DLL_ATON_DUMP_DEBUG_API -DLL_ATON_DBG_BUFFER_INFO_EXCLUDED=1 -DAPP_BARE_METAL -c -I../../Inc -I../../../Dpu -I../../../Common -I../../../X-CUBE-AI/atonn -I../../../X-CUBE-AI -I../../../../Drivers/CMSIS/Core/Include -I../../../../Drivers/CMSIS/DSP/Include -I../../../../Drivers/CMSIS/DSP/PrivateInclude -I../../../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../../../Drivers/CMSIS/Device/ST/STM32N6xx/Include/Templates -I../../../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../../../Middlewares/ST/ThreadX/ports/cortex_m55/gnu/inc -I../../../../Middlewares/ST/ThreadX/common/inc -I../../../../Middlewares/ST/AI/Inc -I../../../../Middlewares/ST/AI/Npu/Devices/STM32N6XX -I../../../../Middlewares/ST/AI/Npu/ll_aton -I../../../../Middlewares/ST/STM32_AI_AudioPreprocessing_Library/Inc -I../../../../Drivers/BSP/Components/mx66uw1g45g -I../../../../Drivers/BSP/STM32N6570-DK -O0 -ffunction-sections -fdata-sections -Wall -flax-vector-conversions -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS

clean-Drivers-2f-CMSIS:
	-$(RM) ./Drivers/CMSIS/startup_stm32n657xx.d ./Drivers/CMSIS/startup_stm32n657xx.o ./Drivers/CMSIS/system_stm32n6xx_fsbl.cyclo ./Drivers/CMSIS/system_stm32n6xx_fsbl.d ./Drivers/CMSIS/system_stm32n6xx_fsbl.o ./Drivers/CMSIS/system_stm32n6xx_fsbl.su

.PHONY: clean-Drivers-2f-CMSIS

