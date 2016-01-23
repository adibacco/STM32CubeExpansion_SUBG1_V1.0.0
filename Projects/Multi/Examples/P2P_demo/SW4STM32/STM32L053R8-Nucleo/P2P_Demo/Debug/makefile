################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Driver/STM32L0xx_HAL_Driver/subdir.mk
-include Driver/BSP/X-NUCLEO-IDS01Ax/subdir.mk
-include Driver/BSP/STM32L0xx_Nucleo/subdir.mk
-include Driver/BSP/Components/SPIRIT1/SPIRIT1_Driver/SPIRIT1_Util/subdir.mk
-include Driver/BSP/Components/SPIRIT1/SPIRIT1_Driver/SPIRIT1_Library/subdir.mk
-include Driver/BSP/CMSIS/subdir.mk
-include Application/User/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: P2P_Demo.elf

# Tool invocations
P2P_Demo.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -T"C:\Users\adibacco\STM32CubeExpansion_SUBG1_V1.0.0\Projects\Multi\Examples\P2P_demo\SW4STM32\STM32L053R8-Nucleo\P2P_Demo\LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections -lm -o "P2P_Demo.elf" @"objects.list" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary:'
	arm-none-eabi-objcopy -O binary "P2P_Demo.elf" "P2P_Demo.bin"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
