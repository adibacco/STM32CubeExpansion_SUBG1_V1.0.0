################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/Src/cube_hal_l0.c \
C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/Src/main.c \
C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/Src/spirit1_appli.c \
C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/Src/stm32l0xx_it.c \
C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/Src/system_stm32l0xx.c 

OBJS += \
./Application/User/cube_hal_l0.o \
./Application/User/main.o \
./Application/User/spirit1_appli.o \
./Application/User/stm32l0xx_it.o \
./Application/User/system_stm32l0xx.o 

C_DEPS += \
./Application/User/cube_hal_l0.d \
./Application/User/main.d \
./Application/User/spirit1_appli.d \
./Application/User/stm32l0xx_it.d \
./Application/User/system_stm32l0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/cube_hal_l0.o: C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/Src/cube_hal_l0.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -std=c99 -DSTM32L0 -DUSE_HAL_DRIVER -DSTM32L053xx -DNO_EEPROM -DP2P_DEMO -DSPIRIT1_ST_SHIELD -DUSE_SPIRIT1_DEFAULT -DNUCLEO_L053R8 -DSTM32 -DUSE_STM32L0XX_NUCLEO -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/CMSIS/Include" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/STM32L0xx_HAL_Driver/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/X-NUCLEO-IDS01Ax/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/STM32L0xx_Nucleo" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/Components/spirit1/SPIRIT1_Util/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/main.o: C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/Src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -std=c99 -DSTM32L0 -DUSE_HAL_DRIVER -DSTM32L053xx -DNO_EEPROM -DP2P_DEMO -DSPIRIT1_ST_SHIELD -DUSE_SPIRIT1_DEFAULT -DNUCLEO_L053R8 -DSTM32 -DUSE_STM32L0XX_NUCLEO -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/CMSIS/Include" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/STM32L0xx_HAL_Driver/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/X-NUCLEO-IDS01Ax/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/STM32L0xx_Nucleo" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/Components/spirit1/SPIRIT1_Util/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/spirit1_appli.o: C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/Src/spirit1_appli.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -std=c99 -DSTM32L0 -DUSE_HAL_DRIVER -DSTM32L053xx -DNO_EEPROM -DP2P_DEMO -DSPIRIT1_ST_SHIELD -DUSE_SPIRIT1_DEFAULT -DNUCLEO_L053R8 -DSTM32 -DUSE_STM32L0XX_NUCLEO -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/CMSIS/Include" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/STM32L0xx_HAL_Driver/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/X-NUCLEO-IDS01Ax/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/STM32L0xx_Nucleo" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/Components/spirit1/SPIRIT1_Util/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32l0xx_it.o: C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/Src/stm32l0xx_it.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -std=c99 -DSTM32L0 -DUSE_HAL_DRIVER -DSTM32L053xx -DNO_EEPROM -DP2P_DEMO -DSPIRIT1_ST_SHIELD -DUSE_SPIRIT1_DEFAULT -DNUCLEO_L053R8 -DSTM32 -DUSE_STM32L0XX_NUCLEO -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/CMSIS/Include" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/STM32L0xx_HAL_Driver/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/X-NUCLEO-IDS01Ax/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/STM32L0xx_Nucleo" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/Components/spirit1/SPIRIT1_Util/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/system_stm32l0xx.o: C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/Src/system_stm32l0xx.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -std=c99 -DSTM32L0 -DUSE_HAL_DRIVER -DSTM32L053xx -DNO_EEPROM -DP2P_DEMO -DSPIRIT1_ST_SHIELD -DUSE_SPIRIT1_DEFAULT -DNUCLEO_L053R8 -DSTM32 -DUSE_STM32L0XX_NUCLEO -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/CMSIS/Include" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/STM32L0xx_HAL_Driver/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/X-NUCLEO-IDS01Ax/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/STM32L0xx_Nucleo" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../../../../../Drivers/BSP/Components/spirit1/SPIRIT1_Util/Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/../../../Inc" -I"C:/Users/adibacco/STM32CubeExpansion_SUBG1_V1.0.0/Projects/Multi/Examples/P2P_demo/SW4STM32/STM32L053R8-Nucleo/P2P_Demo/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


