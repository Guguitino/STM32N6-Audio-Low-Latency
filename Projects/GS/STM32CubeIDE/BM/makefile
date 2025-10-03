################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middleware/ST/STM32_AI_AudioPreprocessing_Library/Src/subdir.mk
-include Middleware/ST/AI/Npu/ll_aton/subdir.mk
-include Middleware/ST/AI/Npu/Devices/STM32N6XX/subdir.mk
-include Drivers/STM32N6xx_HAL_Driver/Src/subdir.mk
-include Drivers/CMSIS/DSP/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Drivers/BSP/STM32N6570-DK/subdir.mk
-include Drivers/BSP/Components/wm8904/subdir.mk
-include Drivers/BSP/Components/mx66uw1g45g/subdir.mk
-include Drivers/BSP/Components/cs42l51/subdir.mk
-include Drivers/BSP/Components/aps256xx/subdir.mk
-include Application/X-CUBE-AI/models/subdir.mk
-include Application/X-CUBE-AI/atonn/subdir.mk
-include Application/X-CUBE-AI/subdir.mk
-include Application/Src/subdir.mk
-include Application/Dpu/subdir.mk
-include Application/Common/Patch/subdir.mk
-include Application/Common/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := GS_Audio_N6
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
GS_Audio_N6.elf \

MAP_FILES += \
GS_Audio_N6.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
GS_Audio_N6.list \

OBJCOPY_HEX += \
GS_Audio_N6.hex \

OBJCOPY_BIN += \
GS_Audio_N6.bin \


# All Target
all: main-build

# Main-build Target
main-build: GS_Audio_N6.elf secondary-outputs

# Tool invocations
GS_Audio_N6.elf GS_Audio_N6.map: $(OBJS) $(USER_OBJS) /home/adamg/STApps/GS_Audio_N6/STM32N6-GettingStarted-Audio-main/Projects/GS/STM32CubeIDE/STM32N657XX_LRUN.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "GS_Audio_N6.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m55 -T"/home/adamg/STApps/GS_Audio_N6/STM32N6-GettingStarted-Audio-main/Projects/GS/STM32CubeIDE/STM32N657XX_LRUN.ld" --specs=nosys.specs -Wl,-Map="GS_Audio_N6.map" -Wl,--gc-sections -static -Wl,--cmse-implib -Wl,--out-implib=./secure_nsclib.o -L../../../../Middlewares/ST/AI/Lib/GCC/ARMCortexM55 --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

GS_Audio_N6.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "GS_Audio_N6.list"
	@echo 'Finished building: $@'
	@echo ' '

GS_Audio_N6.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "GS_Audio_N6.hex"
	@echo 'Finished building: $@'
	@echo ' '

GS_Audio_N6.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "GS_Audio_N6.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) GS_Audio_N6.bin GS_Audio_N6.elf GS_Audio_N6.hex GS_Audio_N6.list GS_Audio_N6.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
