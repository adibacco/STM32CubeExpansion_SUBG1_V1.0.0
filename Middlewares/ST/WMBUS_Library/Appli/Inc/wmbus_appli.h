/**
******************************************************************************
* @file    wmbus_appli.h
* @author  System Lab - NOIDA
* @version V1.0.8
* @date    24-Jul-2014
* @brief  This file contains header for wmbus_appli.c.
*
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
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
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WMBUS_APPLI_H
#define __WMBUS_APPLI_H
/* Includes ------------------------------------------------------------------*/
#include "cube_hal.h"
#include "wmbus_linkServices.h"
#include "wmbus_phydatamem.h"
#include <stdlib.h>

/** @defgroup
* @brief This file contains header for WMBus application.
* @{
*/
/** @defgroup WMBUS_APPLI_Exported_Defines
* @{
*/
#define DATA_PAYLOAD_LENGTH    240
#define KEY_LENGTH 16
#define MAX_DATA_TO_VCOM 260
/**
* @}
*/
/** @defgroup WMBUS_APPLI_Exported_Types
* @{
*/
/* Uncomment to enable the adaquate RTC Clock Source */
/* #define RTC_CLOCK_SOURCE_LSI */
#define RTC_CLOCK_SOURCE_LSE
#ifdef RTC_CLOCK_SOURCE_LSI
  #define RTC_ASYNCH_PREDIV  0x7F
  #define RTC_SYNCH_PREDIV   0x0130
#endif

#ifdef RTC_CLOCK_SOURCE_LSE
  #define RTC_ASYNCH_PREDIV  0x7F
  #define RTC_SYNCH_PREDIV   0x00FF
#endif

typedef struct
{
  uint16_t VALIDITY:1;/*!<Validity bit*/
  uint16_t GROUP_ID:6;/*!<Group ID 6 bits*/
  uint16_t SERIAL_NUM:9;/*!<SERIAL Number 9 bits*/
}SerialNum_t;
typedef struct 
{
  SerialNum_t SerialNum;/*!<Serial Number of Device*/
  uint8_t DeviceType;/*!<Device Type: meter/other*/
  uint8_t KeyType;/*!<database keytype*/
  uint8_t Status;/*!<status of device*/
  uint8_t TimeStamp[6];/*!<Time at which a packet is transmitted or received*/
  uint8_t Payload[DATA_PAYLOAD_LENGTH];/*!<Data to be transmitted or received*/
  uint8_t EncrypKey[16];/*!<Encryption Key*/
  uint64_t MeterID;/*!<Meter ID*/  
  float RSSI_field; /*RSSI of the last payload received*/
}WMBusDatabaseFrame_t;
struct DataBaseList
{
  WMBusDatabaseFrame_t MeterDataFrame;/*!<Database of meters*/
  struct DataBaseList *next;
};
typedef struct
{
  uint8_t EnKey[16];/*!<Encription Key*/
  uint8_t KeyType;/*!<Type of Encription Key */
  uint8_t keySeqNum;/*!<Sequence Number*/
}EncryptionKey_t;

typedef enum
{
  DATA_COMM_MODE=0x00,/*!<Data Communication mode*/
  INSTALL_MODE/*!<Install mode*/
}WMBusOperationMode_t;

typedef struct
{
  uint8_t GroupID;/*!<Device Group ID*/
  uint64_t MeterID;/*!<Meter ID*/
}MeterDatabase_t;

typedef struct{
  uint8_t MeterMFR[5];/*!<Meter Manufacturer Identification*/
  uint8_t A_Filed[13];/*!<A field of packet*/    
  uint8_t DeviceType[3];/*!<Device Type*/
  uint8_t TimeStamp[6];/*!<Time of packet reception/transmission*/
  uint8_t Payload[DATA_PAYLOAD_LENGTH];/*!<Actual Data*/
  uint8_t length;/*!<length of packet*/
  
  uint8_t installed;
}DisplayFrame_t;

/*Some Application State Variables*/

/**
* @}
*/
/** @defgroup WMBUS_APPLI_Exported_Variables
* @{
*/
extern SpiritBool bNewdatareceived;
extern uint8_t aWMBusPayloadBuff[];
extern WMBusOperationMode_t WMBusOperationMode;
extern SpiritBool bLinkAttrChanged;
extern uint8_t aAES_InitnalizationVector_Tx[16];
extern uint8_t aAES_InitnalizationVector_Rx[16];
extern uint8_t CipherBlocklen;

/**
* @}
*/

/** @defgroup WMBUS_APPLI_Exported_FunctionsPrototype
* @{
*/
void Appli_RadioPowerON(void);
void Appli_RadioPowerOFF(void);
void Appli_RadioStandBy(void);
void HAL_RTC_MspDeInit(RTC_HandleTypeDef *phrtc);
void HAL_RTC_MspInit(RTC_HandleTypeDef *phrtc);
void RTC_Init(void);
void WMBus_AppliIndicaCallback(Indication_t *pIndic, LastEventLog_t LastEvent);
void WMBus_AppliInit(void);
LINK_STATUS WMBus_AppliPowerOn(void);
LINK_STATUS WMBus_AppliSendMeterData(uint8_t *pBuff, uint8_t length);
LINK_STATUS WMBus_appliSendMeterInstallationRequest(void);
void WMBus_AppliTxDataSentHandler(LINK_STATUS status, LastEventLog_t LastEvent);
WMBusDeviceType_T WMBus_GetWMBusDeviceType(void);
SpiritBool WMBus_SetBoardMnfID(uint8_t *pBuff);

/**
* @}
*/
#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
