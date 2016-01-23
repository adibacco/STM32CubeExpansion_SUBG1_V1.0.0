/**
******************************************************************************
* @file    wmbus_appli.c
* @author  System Lab - NOIDA
* @version V1.0.7
* @date    25-May-2014
* @brief  This file includes routines for WMBus application Layer.
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
/* Includes ------------------------------------------------------------------*/
#include "wmbus_appli.h"
#include "wmbus_phydatamem.h"
#include "aes128.h"
#include "radio_shield_config.h"
#include "radio_hal.h"
#include "cube_hal.h"

/** @defgroup WMBUS_APPLI
* @brief This file is the interface between WMBus user interface and Link layer
* @{
*/
#pragma pack(1)
/** @defgroup WMBUS_APPLI_Private_Define
* @{
*/

/**
* @}
*/

/** @defgroup WMBUS_APPLI_Private_Variables
* @{
*/
SpiritBool bNewdatareceived = S_FALSE;
SpiritBool bAckReceived = S_FALSE;
SpiritBool bInstallationReqSent = S_FALSE;
SpiritBool bInstallationConfirmSent = S_FALSE;
static volatile SpiritBool bAccessDemandReqTransmitted = S_FALSE;
static volatile SpiritBool bValidDataReqReceived = S_FALSE;
static volatile SpiritBool bTimeoutOcurred =S_FALSE;
SpiritBool bLinkAttrChanged = S_FALSE;
SpiritBool bNewUserDataRequestRxd = S_FALSE;
SpiritBool bACKTransmitted = S_FALSE;
SpiritBool bNRDataTransmitted = S_FALSE;
WMBusOperationMode_t WMBusOperationMode = INSTALL_MODE;
uint8_t aindicationPayload[USER_DATA_MAX_LENGHT] = {0x00};
uint8_t aDataToUSB[MAX_DATA_TO_VCOM] = {0x00};
/*Initialization vctr in the Meter Side*/
uint8_t aAES_InitnalizationVector_Tx[16]={0};
/*Initialization vctr in the Concentrator Side*/
uint8_t aAES_InitnalizationVector_Rx[16]={0};
Indication_t gindicFrame;
static volatile LastEventLog_t AppliLastEvent;
RTC_HandleTypeDef RtcHandle;



#ifndef CLI
RTC_InitTypeDef RTC_InitStructVal=
{
  /*Calender Configuartion*/
  .HourFormat = RTC_HOURFORMAT_24,
  .AsynchPrediv = RTC_ASYNCH_PREDIV,
  .SynchPrediv = RTC_SYNCH_PREDIV
};

RTC_TimeTypeDef RTC_TimeStructVal = 
{
  /* Set the Default Time */
  .Hours = 0x08,           
  .Minutes = 0x00 ,          
  .Seconds = 0x57 ,          
  .SubSeconds = 0x57 ,     
  .TimeFormat = RTC_HOURFORMAT12_AM,       
  .DayLightSaving = RTC_DAYLIGHTSAVING_NONE, 
  .StoreOperation =   RTC_STOREOPERATION_RESET
}; 

RTC_DateTypeDef RTC_DateStructVal =
{
  /* Set the Date */
  .WeekDay = RTC_WEEKDAY_MONDAY,
  .Month = RTC_MONTH_JANUARY,  
  .Date = 0x01,
  .Year = 0x14, 
};
#endif

struct DataBaseList *pRootDataBase;
/**
* @}
*/

/** @defgroup WMBUS_APPLI_Private_FunctionPrototypes
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

/** @defgroup WMBUS_APPLI_Private_Functions
* @{
*/


/**
* @brief  This function will send Meter Data to concentrator.
* @param  Param:uint8_t *pBuff, uint8_t length. 
* @retval LINK_STATUS.
*                       
*/
LINK_STATUS WMBus_AppliSendMeterData(uint8_t *pBuff, uint8_t length)
{
  LINK_STATUS status = LINK_STATUS_UNKNOWN_ERROR;
  int32_t value = 0;
  Request_t request = {0};
  uint8_t aRequestPayload[5] = {0};
  /*M A CC SN FN BC*/
  
#ifdef AES_CBC_ENABLE 
  int32_t tempAttr = 0;
  WMBus_LinkGetAttribute(LINK_ATTR_ID_MFR_ID, (int32_t*)&(tempAttr));
  
  aAES_InitnalizationVector_Tx[0]   = (uint8_t)(tempAttr>>8);
  aAES_InitnalizationVector_Tx[1] = (uint8_t)(tempAttr);
  WMBus_LinkGetAttribute(LINK_ATTR_ID_IDENTIFICATION, &tempAttr);
  aAES_InitnalizationVector_Tx[5] = (uint8_t)tempAttr;
  aAES_InitnalizationVector_Tx[4] = (uint8_t)(tempAttr>>8);
  aAES_InitnalizationVector_Tx[3] = (uint8_t)(tempAttr>>16);
  aAES_InitnalizationVector_Tx[2] = (uint8_t)(tempAttr>>24);
  WMBus_LinkGetAttribute(LINK_ATTR_ID_METER_VERSION, &tempAttr);
  aAES_InitnalizationVector_Tx[6] = (uint8_t)tempAttr;
  WMBus_LinkGetAttribute(LINK_ATTR_ID_METER_TYPE, &tempAttr);  
  aAES_InitnalizationVector_Tx[7] = (uint8_t)tempAttr;
  /*AES IV chaged to test aes cbc*/
  aAES_InitnalizationVector_Tx[8] = (uint8_t)accNum;
  aAES_InitnalizationVector_Tx[9] = (uint8_t)accNum;
  aAES_InitnalizationVector_Tx[10] = (uint8_t)accNum;
  aAES_InitnalizationVector_Tx[11] = (uint8_t)accNum;
  aAES_InitnalizationVector_Tx[12] = (uint8_t)accNum;
  aAES_InitnalizationVector_Tx[13] = (uint8_t)accNum;
  aAES_InitnalizationVector_Tx[14] = (uint8_t)accNum;
  aAES_InitnalizationVector_Tx[15] = (uint8_t)accNum;

  WMBus_AppliEncrypt(aMeter_EnKey, pBuff, length);
#endif
  
  if(LINK_STATUS_SUCCESS == WMBus_LinkGetAttribute(LINK_ATTR_ID_MODE, &value))
  {
    switch((WMBusMode_T)value)
    {
    case S1_MODE:
    case S1m_MODE:  
    case T1_MODE:
    case N1_MODE:
      {
        request.frame.data_field.header.accessNum = accNum;
        request.frame.data_field.header.status_field = 0x00;
        request.frame.data_field.header.config_word = 0x0150;
        request.frame.data_field.payload       = pBuff;
        request.frame.data_field.capacity      = USER_DATA_MAX_LENGHT;
#ifdef AES_CBC_ENABLE        
        request.frame.data_field.size          = CipherBlocklen;
        request.frame.data_field.header.config_word = 0x0150;
#else       
        
        request.frame.data_field.size          = length;
#endif
        /* Prepare the frame for transmission  */
        request.frame.c_field                 = LINK_SEND_NOREPLY_USER_DATA;
        request.frame.ci_field                = 0x7A;
        
        request.retries = 1;
        /**************** Non-Block Mode Example Starts here    *****************/
        bNRDataTransmitted = S_FALSE;
        status = WMBus_LinkServicesRequestsCallbackMode(&request, WMBus_AppliTxDataSentHandler);
        /**************** Non-Block Mode Example Ends here    *****************/
        while(S_FALSE == bNRDataTransmitted);
        break;
      }
    case S2_MODE:
    case R2_MODE:
    case T2_MODE:
    case N2_MODE:
      {
        request.frame.data_field.payload       = aRequestPayload;
        request.frame.data_field.capacity      = sizeof(aRequestPayload);
        request.frame.data_field.size          = 0;
        
        Indication_t indication;
        indication.RxTimeout = 2000;/* Milliseconds*/
        indication.frame.data_field.payload    = aindicationPayload;
        indication.frame.data_field.capacity   = sizeof(aindicationPayload);
        indication.frame.data_field.size       = 0;
        
        /* Set number of request retries  */
        request.retries = 3;
        /* Prepare the frame for transmission  */
        request.frame.c_field                 = LINK_REQUEST_RESPOND_ACCESS_DEMAND;
        request.frame.ci_field                = 0x8A;
        /**************** Non-Block Mode Example Starts here    *****************/
        bAckReceived = S_FALSE;
        bAccessDemandReqTransmitted = S_FALSE;
        if(LINK_STATUS_SUCCESS == WMBus_LinkServicesRequestsCallbackMode(&request,\
          WMBus_AppliTxDataSentHandler))
        {
          while(S_FALSE == bAccessDemandReqTransmitted);

          status = WMBus_LinkServicesIndicationCallbackMode(&indication,\
            WMBus_AppliIndicaCallback);
          while((S_FALSE == bAckReceived)&&(S_FALSE == bTimeoutOcurred));
          if(S_TRUE == bTimeoutOcurred)/*retry*/
          {
            bTimeoutOcurred = S_FALSE;
          }
          if(S_TRUE == bAckReceived)
          {
            Response_t response;
            bTimeoutOcurred = S_FALSE;
            bAckReceived = S_FALSE;
            bNewUserDataRequestRxd = S_FALSE;
            status = WMBus_LinkServicesIndicationCallbackMode(&indication,\
              WMBus_AppliIndicaCallback);
            while((S_FALSE == bNewUserDataRequestRxd)&&(S_FALSE == bTimeoutOcurred));
            if(S_TRUE == bNewUserDataRequestRxd)
            {
              gindicFrame.status = LINK_STATUS_SUCCESS;
              gindicFrame.serviceType = LINK_SERVICE_TYPE_REQUEST_RESPOND;
              
              response.frame.data_field.header.accessNum = accNum;
              response.frame.data_field.header.status_field = 0x00;
              response.frame.data_field.header.config_word = 0x0150;
              response.frame.data_field.payload   = pBuff; 
              response.frame.data_field.capacity  = sizeof(pBuff);
#ifdef AES_CBC_ENABLE       
              response.frame.data_field.size          = CipherBlocklen;
              response.frame.data_field.header.config_word = 0x0150;
#else
              response.frame.data_field.size      = length;
#endif
              response.positive = S_TRUE;
              
              response.frame.c_field                 = LINK_RESPOND_USER_DATA;
              response.frame.ci_field                = 0x7A;
              
              /*  Transmit the response with the meter usage  */
              if ((status = WMBus_LinkServicesResponseCallbackMode(&gindicFrame,\
                &response,WMBus_AppliTxDataSentHandler)) == LINK_STATUS_SUCCESS)
              {
                /* Transmitted response  */
                status = LINK_STATUS_SUCCESS;
              }
            }
          }
        }
        /**************** Non-Block Mode Example Ends here    *****************/
      }
      break;    
    case ALL_MODE:
      break;
    default:
      ;
    }
  }
  else
  {
    return LINK_STATUS_INVALID_ATTR;
  }
  return status;
}

/**
* @brief  This function will init the link layer after power on
* @param  Param:None. 
* @retval LINK_STATUS.
*                       
*/
LINK_STATUS WMBus_AppliPowerOn(void)
{
  /* Start the radio with default Link and Phy settings */
  LINK_STATUS status = WMBus_LinkServicesInit();  
  /* IRQ GPIO */
  SGpioInit xGpioIRQ=
  {
    SPIRIT_GPIO_3,
    SPIRIT_GPIO_MODE_DIGITAL_OUTPUT_LP,
    SPIRIT_GPIO_DIG_OUT_IRQ
  };
  /* Spirit IRQ config */
  SpiritGpioInit(&xGpioIRQ);
  
  /* IRQ GPIO */
  SGpioInit xGpioIRQ2=
  {
    SPIRIT_GPIO_0,
    SPIRIT_GPIO_MODE_DIGITAL_OUTPUT_LP,
    SPIRIT_GPIO_DIG_OUT_TX_RX_MODE
  };
  /* Spirit IRQ config */
  SpiritGpioInit(&xGpioIRQ2); 
  return status;
}

/**
* @brief  This function will init the WMBUS application.
* @param  Param:None. 
* @retval None:
*                       
*/
void WMBus_AppliInit(void)
{
#ifndef CLI
  /*
  RTC_Init();
  HAL_RTC_SetDate(&RtcHandle, &RTC_DateStructVal, FORMAT_BCD);
  HAL_RTC_SetTime(&RtcHandle, &RTC_TimeStructVal, FORMAT_BCD);
  */
#endif
  /*  Init Meter database */
  WMBus_AppliPowerOn();
}

/**
* @brief  This function will handle the install Meter request.
* @param  Param:None. 
* @retval LINK_STATUS:
*                       
*/
LINK_STATUS WMBus_appliSendMeterInstallationRequest(void)
{
  LINK_STATUS status= LINK_STATUS_UNKNOWN_ERROR;
  Request_t request = {0x00};
  uint8_t aRequestPayload[5] = {0x00};
  Indication_t indication = {0x00};
  
  request.frame.data_field.payload       = aRequestPayload;
  request.frame.data_field.capacity      = sizeof(aRequestPayload);
  request.frame.data_field.size          = 0;
  /* Set number of request retries*/
  request.retries = 3;
  /* Prepare the frame for transmission , For S1, S1m and T1 mode */
  request.frame.c_field                 = LINK_PRIMARY_INSTALLATION_REQ;
  request.frame.ci_field                = 0x7A;
  
  /* Set receive timeout  */
  WMBus_LinkGetAttribute(LINK_ATTR_ID_RX_TIMEOUT,&indication.RxTimeout);
  
  indication.frame.data_field.payload    = aindicationPayload;
  indication.frame.data_field.capacity   = sizeof(aindicationPayload);
  indication.frame.data_field.size       = 0;
  
  /***********  Non-Block Mode Installation Request Starts Here    ************/
  bInstallationReqSent  = S_FALSE;
  if(LINK_STATUS_SUCCESS == WMBus_LinkServicesRequestsCallbackMode(&request, WMBus_AppliTxDataSentHandler))
  {
    while(S_FALSE == bInstallationReqSent);
    
    status = WMBus_LinkServicesIndicationCallbackMode(&indication, WMBus_AppliIndicaCallback);

    while(( CONFIRM_INSTALLATION_RXD != AppliLastEvent.event)&&(S_FALSE == bTimeoutOcurred));
    
    
    if(CONFIRM_INSTALLATION_RXD == AppliLastEvent.event)
    {
      SW2_PUSHED = 1;
      RadioShieldLedOn(RADIO_SHIELD_LED);
    }
    if(S_TRUE == bTimeoutOcurred)
    {
      bTimeoutOcurred = S_FALSE;
      BSP_LED_Toggle(LED2);
    }
  }
  return status;
}

/**
* @brief  This function will return the WMBus device type.
* @param  Param:None. 
* @retval WMBusDeviceType_t: As shown below
*                     0x01 -> METER
*                     0x02 -> OTHER,
*                     0x03 -> ROUTER,
*                     0x04 -> SNIFFER, 
*                     0xFF -> NOT_CONFIGURED
*                       
*/
WMBusDeviceType_T WMBus_GetWMBusDeviceType(void)
{
  int32_t value = 0;
  if(LINK_STATUS_SUCCESS == WMBus_LinkGetAttribute(LINK_ATTR_ID_DEV_TYPE, &value))
  {
    return (WMBusDeviceType_T)value;
  }
  return NOT_CONFIGURED;
}

/**
* @brief  This function handles the data transmissiom.
* @param  LINK_STATUS status, LastEventLog_t LastEvent.
* @retval None
*/
void WMBus_AppliTxDataSentHandler(LINK_STATUS status, LastEventLog_t LastEvent)
{
  AppliLastEvent.event =  LastEvent.event;
  AppliLastEvent.globalTic =  LastEvent.globalTic;
  
  if(LINK_STATUS_SUCCESS == status)
  {
    /* The data transmitted successfully*/
    if(AppliLastEvent.event == CONFIRM_INSTALLATION_SENT)
    {
      bInstallationConfirmSent = S_TRUE;
    }
    else if(AppliLastEvent.event == PRIMARY_INSTALLATION_REQ_TXD)
    {
      bInstallationReqSent = S_TRUE;
    }
    else if(AppliLastEvent.event == REQUEST_RESPOND_ACCESS_DEMAND_TXD)
    {
      bAccessDemandReqTransmitted = S_TRUE;
    }  
    else if(CONFIRM_ACK_SENT == AppliLastEvent.event)
    {
      bACKTransmitted = S_TRUE;
    }
    else if(REQUEST_RESPOND_CLASS2_DATA_TXD == AppliLastEvent.event)
    {
      /*bACKTransmitted = S_FALSE;*/
    }
    else if(SEND_NOREPLY_USER_DATA_TXD == AppliLastEvent.event)
    {
      bNRDataTransmitted = S_TRUE;
    }
  } 
}

/**
* @brief  This function is called after invoking the indication service.
* @param  Indication_t: This indicates type of request and associated data.
* @retval None
*/
void WMBus_AppliIndicaCallback(Indication_t *pIndic, LastEventLog_t LastEvent)
{
  AppliLastEvent.event =  LastEvent.event;
  AppliLastEvent.globalTic =  LastEvent.globalTic;
  gindicFrame.frame.data_field.payload = aindicationPayload;
  gindicFrame.frame.data_field.capacity = sizeof(aindicationPayload);
  if(LINK_STATUS_PHY_ERROR_TIMEOUT == pIndic->status)
  {
#ifdef CLI
    WMBus_AppliRxDataHandler(NULL);
#endif
    bTimeoutOcurred =S_TRUE;
  }
  else
  {   
    bValidDataReqReceived = S_TRUE;
    switch(pIndic->frame.c_field &0x4F)
    {
    case LINK_PRIMARY_INSTALLATION_REQ:
      memcpy(&gindicFrame.frame,&pIndic->frame,10);
      gindicFrame.frame.data_field.header.accessNum = pIndic->frame.data_field.header.accessNum;
      gindicFrame.frame.data_field.header.status_field = pIndic->frame.data_field.header.status_field;
      gindicFrame.frame.data_field.header.config_word = pIndic->frame.data_field.header.config_word;
      gindicFrame.frame.RSSI_field = pIndic->frame.RSSI_field;
      gindicFrame.frame.data_field.size = pIndic->frame.data_field.size;
      memcpy(gindicFrame.frame.data_field.payload,pIndic->frame.data_field.payload,pIndic->frame.data_field.size);
      break;
    case LINK_REQUEST_RESPOND_ACCESS_DEMAND:
      memcpy(&gindicFrame.frame,&pIndic->frame,10);
      gindicFrame.frame.data_field.header.accessNum = pIndic->frame.data_field.header.accessNum;
      gindicFrame.frame.data_field.header.status_field = pIndic->frame.data_field.header.status_field;
      gindicFrame.frame.data_field.header.config_word = pIndic->frame.data_field.header.config_word;
      gindicFrame.frame.RSSI_field = pIndic->frame.RSSI_field;
      gindicFrame.frame.data_field.size = pIndic->frame.data_field.size;
      memcpy(gindicFrame.frame.data_field.payload,pIndic->frame.data_field.payload,pIndic->frame.data_field.size);
      break;
    case LINK_REQUEST_RESPOND_CLASS2_DATA:
      memcpy(&gindicFrame.frame,&pIndic->frame,10);
      gindicFrame.frame.data_field.header.accessNum = pIndic->frame.data_field.header.accessNum;
      gindicFrame.frame.data_field.header.status_field = pIndic->frame.data_field.header.status_field;
      gindicFrame.frame.data_field.header.config_word = pIndic->frame.data_field.header.config_word;
      gindicFrame.frame.RSSI_field = pIndic->frame.RSSI_field;
      gindicFrame.frame.data_field.size = pIndic->frame.data_field.size;
      memcpy(gindicFrame.frame.data_field.payload,pIndic->frame.data_field.payload,pIndic->frame.data_field.size);
      bNewUserDataRequestRxd = S_TRUE;
      break;
    case LINK_CONFIRM_INSTALLATION:
      RadioShieldLedOn(RADIO_SHIELD_LED);
      break;
    case LINK_CONFIRM_ACK:
      bAckReceived = S_TRUE;
      break;
    default:
      ;
    }
  }
}

/*################################RTC#########################################*/
/** RTC Configuration
*/
void RTC_Init(void)
{
  /*##-1- Configure the RTC peripheral #######################################*/
  /* Configure RTC prescaler and RTC data registers */
  /* RTC configured as follow:
  - Hour Format    = Format 24
  - Asynch Prediv  = Value according to source clock
  - Synch Prediv   = Value according to source clock
  - OutPut         = Output Disable
  - OutPutPolarity = High Polarity
  - OutPutType     = Open Drain */
  RtcHandle.Instance = RTC; 
  RtcHandle.Init.HourFormat = RTC_HOURFORMAT_24;
  RtcHandle.Init.AsynchPrediv = RTC_ASYNCH_PREDIV;
  RtcHandle.Init.SynchPrediv = RTC_SYNCH_PREDIV;
  RtcHandle.Init.OutPut = RTC_OUTPUT_DISABLE;
  RtcHandle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  RtcHandle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;  
  HAL_RTC_Init(&RtcHandle);
}

/**
* @brief RTC MSP Initialization 
*        This function configures the hardware resources used in this example: 
*           - Peripheral's clock enable
* @param phrtc: RTC handle pointer
* @note  Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to select 
*        the RTC clock source; in this case the Backup domain will be reset in  
*        order to modify the RTC Clock source, as consequence RTC registers (including 
*        the backup registers) and RCC_CSR register are set to their reset values.  
* @retval None
*/
void HAL_RTC_MspInit(RTC_HandleTypeDef *phrtc)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;
  
  /*##-1- Configue LSE or LSI as RTC clock soucre ############################*/ 
#ifdef RTC_CLOCK_SOURCE_LSE
  RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;
  
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
  
#elif defined (RTC_CLOCK_SOURCE_LSI) 
  
  RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_OFF;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
#else
#error Please select the RTC Clock source inside the main.h file
#endif /*RTC_CLOCK_SOURCE_LSE*/
  
  /*##-2- Enable RTC peripheral Clocks #######################################*/ 
  /* Enable RTC Clock */ 
  __HAL_RCC_RTC_ENABLE(); 
}

/**
* @brief RTC MSP De-Initialization 
*        This function freeze the hardware resources used in this example:
*          - Disable the Peripheral's clock
* @param phrtc: RTC handle pointer
* @retval None
*/
void HAL_RTC_MspDeInit(RTC_HandleTypeDef *phrtc)
{
  /*##-1- Reset peripherals ##################################################*/
  __HAL_RCC_RTC_DISABLE();     
}
/*############################################################################*/

/**
* @brief  This function will set the MFR ID(MFR+Identification field).
* @param  uint8_t *buff: The MFR ID in array format. 
* @retval SpiritBool:Returns S_TRUE if the operation succesful S_FALSE otherwise.
*                       
*/
SpiritBool WMBus_SetBoardMnfID(uint8_t *buff)
{
  uint32_t value;  
  value =(uint32_t)*buff++;
  value = value<<8;
  value |=(uint8_t)*buff++;
  if(LINK_STATUS_SUCCESS != WMBus_LinkSetAttribute(LINK_ATTR_ID_MFR_ID, value))
    return S_FALSE;  
  value =(uint32_t)*buff++;
  value = value<<8;
  value |=(uint8_t)*buff++;
  value = value<<8;
  value |=(uint8_t)*buff++;
  value = value<<8;
  value |=(uint8_t)*buff++;  
  if(LINK_STATUS_SUCCESS != WMBus_LinkSetAttribute(LINK_ATTR_ID_IDENTIFICATION, value))
    return S_FALSE;
  value =(uint32_t)*buff++;
  if(LINK_STATUS_SUCCESS != WMBus_LinkSetAttribute(LINK_ATTR_ID_METER_VERSION, value))
    return S_FALSE;
  value =(uint32_t)*buff++;
  if(LINK_STATUS_SUCCESS != WMBus_LinkSetAttribute(LINK_ATTR_ID_METER_TYPE, value))
    return S_FALSE;
  bLinkAttrChanged = S_TRUE;
  return S_TRUE;
}

/**
* @brief  This function will turn on the radio and waits till it enters the Ready state.
* @param  Param:None. 
* @retval None
*                       
*/
void Appli_RadioPowerON(void)
{
  WMBus_LinkRadioPowerOn();
}


/**
* @brief  This function will Shut Down the radio.
* @param  Param:None. 
* @retval None
*                       
*/
void Appli_RadioPowerOFF(void)
{
  WMBus_LinkRadioPowerOff();
}


/**
* @brief  This function will put the radio in standby state.
* @param  Param:None. 
* @retval None
*                       
*/
void Appli_RadioStandBy(void)
{
  WMBus_LinkRadioStandby();
}




/**
* @}
*/

/**
* @}
*/
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
