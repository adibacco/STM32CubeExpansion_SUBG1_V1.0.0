################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Drivers/BSP/Components/spirit1/SPIRIT1_Util/Src/SPIRIT1_Util.c 

OBJS += \
./Driver/BSP/Components/SPIRIT1/SPIRIT1_Driver/SPIRIT1_Util/SPIRIT1_Util.o 

C_DEPS += \
./Driver/BSP/Components/SPIRIT1/SPIRIT1_Driver/SPIRIT1_Util/SPIRIT1_Util.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/BSP/Components/SPIRIT1/SPIRIT1_Driver/SPIRIT1_Util/SPIRIT1_Util.o: C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Drivers/BSP/Components/spirit1/SPIRIT1_Util/Src/SPIRIT1_Util.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -std=c99 -DSTM32L0 -DUSE_HAL_DRIVER -DSTM32L053xx -DNO_EEPROM -DP2P_DEMO -DSPIRIT1_ST_SHIELD -DUSE_SPIRIT1_DEFAULT -DNUCLEO_L053R8 -DSTM32 -DUSE_STM32L0XX_NUCLEO -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/CMSIS/Include" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/STM32L0xx_HAL_Driver/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/X-NUCLEO-IDS01Ax/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/STM32L0xx_Nucleo" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/Components/spirit1/SPIRIT1_Util/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


