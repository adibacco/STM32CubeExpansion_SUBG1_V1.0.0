/**
******************************************************************************
* @file AT_Prepro.h.c
* @author IMS Systems Lab
* @version V1.1.0
* @date 10/15/2011
* @brief This file is the contains header for AT_Prepro.c
******************************************************************************
* @copy
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
* <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
*/
#ifndef __AT_PREPRO_H
#define __AT_PREPRO_H
/* Includes ------------------------------------------------------------------*/
#include "Serial.h"
#include <stdlib.h>
/**
 * @defgroup SAT_PREPRO  AT Command Parser layer Exported defines
 * @{
 */
#define RESPONSE_SIZE 50
#define COMMAND_SIZE 25
/**
 *@}
 */

/**
 * @brief  AT_PREPRO  AT Command Parser layer exported variables
 * @{
 */
extern uint8_t CommandLineTerminator; 
extern uint8_t CommandLineEditor;  

/**
 * @}
 */

/** @defgroup AT_Prepro_Exported_Functions         AT Command Parser layer
 * @{
 */
extern void AT_PreProInit(void);
extern void AT_PrePro(void);
extern void SendResponse(uint8_t *response);
extern void GetCommand(uint8_t *command);
extern int GetCommandLength(uint8_t *command);
extern void addCommand(uint8_t * command,uint8_t * response,void(*routine_ptr)(void));
extern void toString(uint64_t number, uint8_t *string);
extern uint32_t toNumber(uint8_t *string);
void routine1(void);
void routine2(void);
void routine3(void);
/**
 * @}
 */

#endif /* __AT_PREPRO_H */
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/