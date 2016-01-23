/**
 * @file    wmbus_networkInit.c
 * @author  MSH RF/IMS Systems Lab
 * @version V1.0.0
 * @date    September 20, 2011
 * @brief   This file includes routines for WMBus Network initilization.
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
/* Includes ------------------------------------------------------------------*/
#include "wmbus_NtwkMgmt.h"
/** @defgroup WMBUS_NTWKMGMT
* @brief This file is the interface between WMBus appli and Phy layer
* @{
*/
/** @defgroup WMBUS_NTWKMGMT_Private_Functions
* @{
*/
/**
* @brief  This function initilize the stack for Installation mode
* @param  Param:None. 
* @retval None:
*                       
*/
void WMBus_InstallModeHandler(void)
{
  // Update the confoguration herer
#ifdef DEVICE_TYPE_METER
  //Configure the 
#else
  //
#endif
}
/**
* @brief  This function will handle the incoming access demand requests.
* @param  Param:None. 
* @retval None:
*                       
*/
void WMBus_IncomingAccessDemandReqHandler(void)//for Concentrator Only
{
  //Check the Validity of the metering device
  //To allow the metering device add the device to database
  // Send the response to the metering device(to link layer)
}
/**
 *@}
 */
/**
 *@}
 */
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/