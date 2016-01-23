################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/startup_stm32l053xx.s 

OBJS += \
./Driver/BSP/CMSIS/startup_stm32l053xx.o 


# Each subdirectory must supply rules for building sources it contributes
Driver/BSP/CMSIS/startup_stm32l053xx.o: C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Drivers/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/startup_stm32l053xx.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo %cd%
	arm-none-eabi-as -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


