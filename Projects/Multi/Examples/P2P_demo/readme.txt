/**
  @page Point-to-Point example

  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    Point-to-Point Example/readme.txt
  * @author  System LAB - NOIDA
  * @version V1.0.0
  * @date    10-Apr-2015
  * @brief   Description of the Point-to-Point example.
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

This example is to demonstrate Point-to-Point communication using Spirit1 driver and STM32Cube firmware. 


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

  - P2P_Demo/Src/main.c                  Main program
  - P2P_Demo/Src/system_stm32l0xx.c      STM32L0xx system clock configuration file
  - P2P_Demo/Src/stm32l0xx_it.c          Interrupt handlers
  - P2P_Demo/Inc/stm32l0xx_it.h          Interrupt handlers header file
  - P2P_Demo/Inc/stm32l0xx_hal_conf.h    HAL configuration file

@par Folders not included in project

  - Utilities									---- Part of Native release 
  - Middlewares\ST                                              		---- Part of Native release 
  - Adafruit_Shield								---- Part of Native release 
  - Components									---- Part of Native release 
  
@par Driver used in project

  - Drivers\BSP\Components\spirit1					---- Spirit1 driver
  - Drivers\BSP\X-NUCLEO-IDS01Ax	                ---- Spirit1 expansion board BSP

@par Hardware and Software environment

  - This example runs on STM32L0xx devices.

  - This example has been tested with STM32L053R8-Nucleo RevC board with RF expansion  daughter
   board:
   1. SPIRIT1 Expansion Board
  
  The example can be easily tailored to any other supported device and development board.

  - STM32L053-Nucleo RevC Set-up
      user need to plug the RF expansion  daughter board on top of the  CN11 and CN12 
      connectors of the STM32L053-Nucleo. 
      
  - For P2P application demonstration two Spirit1 expansion boards are required to be connected to two nucleo boards.
    
  - Operating frequency is supported for this Point-to-Point demo:
    => 433 MHz, 868 MHz and 915 MHz 

  - User can select desired P2P features in spirit1_appli.h file located @ P2P_Demo/Inc


	/*  Platform definition : Uncomment the used expansion board */
	#define X_NUCLEO_IDS01A4		
	// #define X_NUCLEO_IDS01A5		

	#if defined(X_NUCLEO_IDS01A4)
         	#define USE_SPIRIT1_868MHz
	#elif defined(X_NUCLEO_IDS01A5)
         	#define USE_SPIRIT1_915MHz
	#else
	#error SPIRIT1 Expansion Board is undefined or unsupported
	#endif

	/*  Uncomment the Link Layer features to be used */
	// #define USE_AUTO_ACK		
	// #define USE_AUTO_ACK_PIGGYBACKING	
	// #define USE_AUTO_RETRANSMISSION

	#if defined(USE_AUTO_ACK)&& defined(USE_AUTO_ACK_PIGGYBACKING)&& defined(USE_AUTO_RETRANSMISSION) 
	#define USE_STack_PROTOCOL
    
	/* LLP configuration parameters */
	#define EN_AUTOACK                      S_ENABLE
	#define EN_PIGGYBACKING             	S_ENABLE
	#define MAX_RETRANSMISSIONS         	PKT_N_RETX_2

	#else
	#define USE_BASIC_PROTOCOL
	#endif

	/*  Uncomment the system Operating mode */
	//#define USE_LOW_POWER_MODE

	#if defined (USE_LOW_POWER_MODE)
	#define LPM_ENABLE
	#define MCU_STOP_MODE
	//#define MCU_SLEEP_MODE
	//#define RF_STANDBY
	#endif
   
    
  - Connect the board to PC through USB - mini connector of nucleo board.
  
  - Flash the board for desired configuration as explained above.
  

@par How to use it ?

To use this example, the following steps have to be followed:
 - Open project file.
 - Rebuild all the project and load the image into the target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
