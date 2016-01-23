/**
 * @file   wmbus_networkInit.h
 * @author  MSH RF/IMS-Systems Lab
 * @version V1.0.0
 * @date    05/04/2011
 * @brief   This file contains header for wmbus_NtwkMgmt.c
 * @details
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * THIS SOURCE CODE IS PROTECTED BY A LICENSE.
 * FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED
 * IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
 *
 * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
 */
#ifndef __WMBUS_NTWKMGMT_H
#define __WMBUS_NTWKMGMT_H
/* Includes ------------------------------------------------------------------*/
#include "wmbus_appli.h"
/**
 * @defgroup WMBus_NetworkManagement WMBus Network management layer
 * @brief Configuration and management of WMBus Network management layer.
 * @details See the file <i>@ref wmbus_NetwkMgmt.h</i> for more details.
 * @{
 */
/**
 * @brief  WMBUS  Network Management exported structures
 * @{
 */
typedef struct
{
  WMBusMode_T Mode;
  WMBusChannel_T rfChannel;
  uint8_t opPower;
  uint8_t SleepMode;
  uint8_t Preamblelen;
  uint8_t Postamblelen;
  uint8_t CIField;
  uint8_t Address[6];
  uint16_t ManufacturerID;
  uint8_t Version;
  uint8_t DeviceType;
  uint8_t AccessNum;
  uint8_t Status;
  uint16_t Signature;
  uint32_t TXInterval;
  uint32_t RxTimeout;
  uint8_t  EncryptFlag;
  uint8_t  DecryptFlag;
  uint8_t  CurrentKey[16];
  uint8_t  HardwareRev;
  uint8_t  FirmwareRev;                                         
  uint8_t  ConcentratorID[8];
  /* Serial Port Parameters */
  uint32_t COMSpeed;
  uint8_t flowControlFlag;
  /*SPIRIT Radio Parameters */
  uint8_t params[10];
  uint32_t TimeStamp;
}WMBusNVParam_T;
/**
 *@}
 */
/**
 *@}
 */
#endif  /*__WMBUS_NTWKMGMT_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
