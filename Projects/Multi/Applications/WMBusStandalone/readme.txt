/**
  @page WMBusStandalone example

  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    WMBusExample/readme.txt
  * @author  System LAB - NOIDA
  * @version V1.0.0
  * @date    10-Apr-2015
  * @brief   Description of the WMBus example.
  ******************************************************************************
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  @endverbatim

@par Example Description

This example is a part of the WMBus Library package using STM32Cube firmware. 

This is a demo implementation of the standard WMBUS protocol. It takes in account the physical and data link layers
defined by the standard.

The example shows how to configure the packets in order to transmit or receive WMBUS packets.


At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick. The user is 
provided with the SystemClock_Config()function to configure the system clock (SYSCLK).


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on the the SysTick ISR. Thus if HAL_Delay() is called from a peripheral ISR process, the SysTick interrupt 
      must have higher priority (numerically lower) than the peripheral interrupt, Otherwise the caller ISR process 
      will be blocked. To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function or statically
      define it in the HAL configuration file through the "TICK_INT_PRIORITY" define.

@note The application needs to ensure that the SysTick time base is set to 1 millisecond
      to have correct HAL configuration.
   


@par Directory contents

  - WMBusExample/Src/main.c                  Main program
  - WMBusExample/Src/system_stm32l0xx.c      STM32L0xx system clock configuration file
  - WMBusExample/Src/stm32l0xx_it.c          Interrupt handlers
  - WMBusExample/Inc/main.h                  Main program header file
  - WMBusExample/Inc/stm32l0xx_it.h          Interrupt handlers header file
  - WMBusExample/Inc/stm32l0xx_hal_conf.h    HAL configuration file

 
@par Driver used in project

  - Drivers\BSP\Components\spirit1				---- Spirit1 driver
  - Drivers\BSP\X-NUCLEO-IDS01Ax				---- Spirit1 Expansion Board BSP

@par Hardware and Software environment

  - This example runs on STM32L0xx devices.

  - This example has been tested with STM32L053R8-Nucleo RevC board with RF Expansion daughter
   board:
   1. SPIRIT1 Expansion Board - X-NUCLEO-IDS01A4 
   
  
  The example can be easily tailored to any other supported device and development board.

  - STM32L053-Nucleo RevC Set-up
      user need to plug the RF expansion daughter board on top of the  CN11 and CN12 
      connectors of the STM32L053-Nucleo. 
      
  - For WMBus application demonstration two Spirit1 expanion boards are required to be connected to two nucleo boards.
  
  - One Spirit1 Expansion Board + nucleo is programmed as meter 
    
  - Another side, STEVAL-IKR001Vx is used as Concentrator or data collector
   
  - Operating frequency is supported for this WMBus demo is:
    => 868 MHz 

  
  - User can select desired frequency by defining:
    => DEVICE_BAND_868MHz : Supports S/T/R modes of WMBus
  
  - Desired WMBus features can be selected in rf_hal.h file by changing below section of code:
  
    /* Wireless Meter Bus Specific Configuration----------------------------------*/

	#define TX_OUTPUT_POWER ((float)3.0)/* Between [-3.0 , +27.0] if the RF board 
	has an external PA. Otherwise between [-30.0 , +13.0].*/
	#define RX_TIMEOUT ((uint32_t)1000)

	/* Private macro -------------------------------------------------------------*/
	#define     DEVICE_BAND_868MHz
    
    
	#ifdef DEVICE_BAND_868MHz
	#define DEVICE_WMBUS_MODE S1_MODE    /*S1_MODE/ S1m_MODE/ S2_MODE/ T1_MODE/\
                                              T2_MODE/ R2_MODE*/
	#define DEVICE_WMBUS_CHANNEL CHANNEL_1 
	#define WMBUS_FRAME_FORMAT FRAME_FORMAT_A
	#endif

	#define  DEVICE_TYPE_METER  
    
	#ifdef DEVICE_TYPE_METER
	#define DEVICE_TYPE         METER
	#define DEVICE_METER_TYPE   (0x03)
	#endif

	/*  Uncomment the system Operating mode */
	#define USE_LOW_POWER_MODE

	#if defined (USE_LOW_POWER_MODE)
	#define LPM_ENABLE
	#define MCU_STOP_MODE
	//#define MCU_SLEEP_MODE
	#define RF_STANDBY
	#endif


  /*------------------------------------------------------------------------------*/
    
  - Connect the board to PC through USB - mini connector of nucleo board.
  
  - Flash the board for desired configuration as explained above.
  

@par How to use it ?

To use this example, the following steps have to be followed:
 - Open project file.
 - Rebuild all the project and load the image into the target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
