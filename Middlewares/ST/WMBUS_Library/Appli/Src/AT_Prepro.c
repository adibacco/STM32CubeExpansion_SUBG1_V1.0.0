/**
 * @file    AT_Prepro.c
 * @author  MSH RF/IMS-Systems Lab
 * @version V1.0.0
 * @date    04/05/2011
 * @brief   This file provides all the low level API to manage USART Communication.
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
#include "AT_Prepro.h"
/** @defgroup AT_PREPRO
* @brief This file handles addition of new command, respond to AT commands.
* @{
*/
/** @defgroup AT_PREPRO_Private_Types
* @{
*/
struct trie_node 
{
  unsigned flag : 1;               
  uint8_t value;                   
  struct list_node *children;  
  void (*routine_ptr)(void);   
  uint8_t *string_response;    
};
struct list_node
{ 
  struct trie_node *node_ptr; 
  struct list_node *next;
};
typedef struct trie_node trie_node;
typedef struct list_node list_node;
uint8_t CommandLineTerminator = 0x0D; 
uint8_t CommandLineEditor = 0x08;  
uint8_t FirmwareVersion[] = {"Firmware Version"};
uint8_t Echo = 0; 
/**
* @}
*/
/** @defgroup SERIAL_Private_Functions_Prototypes
* @{
*/
trie_node *createNode(void);
trie_node *findCommand(uint8_t *command);
trie_node *findChild(uint8_t value,list_node *Head);
trie_node *addChild(uint8_t value,list_node **Head_ref);
//1.ATS3 for Command line termination character
uint8_t ATS3_Response[] = {"ATS3 <new value> \r\n ATS3? <current value>\r\n"};
void ATS3_Routine(void);
//3.ATS5 Command Line Editing Character
uint8_t ATS5_Response[] = {"ATS5 <new value> \r\n ATS5? <current value> \r\n"};
void ATS5_Routine(void);
//4.ATE for command line Echo
uint8_t ATE_Response[] = {"ATE <new value> \r\nSupported values :-\r\n0  for no Echo\r\n1  for Echo\r\n ATE? <current value> \r\n"};
void ATE_Routine(void);
//9.ATR modem reset
uint8_t ATR_Response[] = {"Resets the modem"};
void ATR_Routine(void);
//10.AT+IFC DTE-DCE flow control 
uint8_t ATIFC_Response[] = {"AT+IFC <new value>\r\n256 : Use RTS\r\n512 : Use CTS\r\n768 : Use RTS and CTS\r\n\r\n AT+IFC? <current value>"};
void ATIFC_Routine(void);
//11.AT+IPR Baud Rate configuration
uint8_t ATIPR_Response[] = {"AT+IPR <new value>\r\nSupported values :-\r\n1200 to 460800 \r\n\r\n AT+IPR? <current value>"};
void ATIPR_Routine(void);

//14.AT/V Firmware Version
uint8_t V_Response[] = {"Firmware Version"};
void V_Routine(void);
  
//15. AT+CMGS for sending data messages
uint8_t ATCMGS_Response[] = {"AT+CMGS <length of the message to be sent>\r\n"};
void ATCMGS_Routine(void);

//17.ATS100
uint8_t ATS100_Response[] = {""};
void ATS100_Routine(void);

//18.ATS101
uint8_t ATS101_Response[] = {""};
void ATS101_Routine(void);

//19.ATS1012
uint8_t ATS102_Response[] = {""};
void ATS102_Routine(void);

//20.ATS103
uint8_t ATS103_Response[] = {""};
void ATS103_Routine(void);

//21.ATS104
uint8_t ATS104_Response[] = {""};
void ATS104_Routine(void);

//22.ATS105
uint8_t ATS105_Response[] = {""};
void ATS105_Routine(void);

//23.ATS106
uint8_t ATS106_Response[] = {""};
void ATS106_Routine(void);

//24.ATS107
uint8_t ATS107_Response[] = {""};
void ATS107_Routine(void);

//25.ATS108
uint8_t ATS108_Response[] = {""};
void ATS108_Routine(void);

//26.ATS109
uint8_t ATS109_Response[] = {""};
void ATS109_Routine(void);

//27.ATS110
uint8_t ATS110_Response[] = {""};
void ATS110_Routine(void);

//28.ATS111
uint8_t ATS111_Response[] = {""};
void ATS111_Routine(void);

//29.ATS112
uint8_t ATS112_Response[] = {""};
void ATS112_Routine(void);

//30.ATS113
uint8_t ATS113_Response[] = {""};
void ATS113_Routine(void);

//31.ATS114
uint8_t ATS114_Response[] = {""};
void ATS114_Routine(void);

//32.ATS115
uint8_t ATS115_Response[] = {""};
void ATS115_Routine(void);

//33.ATS116
uint8_t ATS116_Response[] = {""};
void ATS116_Routine(void);

//34.ATS117
uint8_t ATS117_Response[] = {""};
void ATS117_Routine(void);

//35.ATS118
uint8_t ATS118_Response[] = {""};
void ATS118_Routine(void);


//36.ATS119
uint8_t ATS119_Response[] = {""};
void ATS119_Routine(void);

//37.ATS120
uint8_t ATS120_Response[] = {""};
void ATS120_Routine(void);

//38.ATS121
uint8_t ATS121_Response[] = {""};
void ATS121_Routine(void);

//39.ATS122
uint8_t ATS122_Response[] = {""};
void ATS122_Routine(void);

//40.ATS123
uint8_t ATS123_Response[] = {""};
void ATS123_Routine(void);

//41.ATS124
uint8_t ATS124_Response[] = {""};
void ATS124_Routine(void);

//42.ATS125
uint8_t ATS125_Response[] = {""};
void ATS125_Routine(void);

//43.ATS126
uint8_t ATS126_Response[] = {""};
void ATS126_Routine(void);

//44.ATS127
uint8_t ATS127_Response[] = {""};
void ATS127_Routine(void);

//45.ATS128
uint8_t ATS128_Response[] = {""};
void ATS128_Routine(void);

//46.ATS129
uint8_t ATS129_Response[] = {""};
void ATS129_Routine(void);

//47.ATS130
uint8_t ATS130_Response[] = {""};
void ATS130_Routine(void);

//48.ATS131
uint8_t ATS131_Response[] = {""};
void ATS131_Routine(void);

//49.ATS132
uint8_t ATS132_Response[] = {""};
void ATS132_Routine(void);

//50.ATS133
uint8_t ATS133_Response[] = {""};
void ATS133_Routine(void);

//51.ATS134
uint8_t ATS134_Response[] = {""};
void ATS134_Routine(void);

//52.ATS135
uint8_t ATS135_Response[] = {""};
void ATS135_Routine(void);

//53.ATS136
uint8_t ATS136_Response[] = {""};
void ATS136_Routine(void);

//54.ATS137
uint8_t ATS137_Response[] = {""};
void ATS137_Routine(void);

//55.ATS138
uint8_t ATS138_Response[] = {""};
void ATS138_Routine(void);

//56.ATS139
uint8_t ATS139_Response[] = {""};
void ATS139_Routine(void);

//57.ATS140
uint8_t ATS140_Response[] = {""};
void ATS140_Routine(void);

//58.ATS141
uint8_t ATS141_Response[] = {""};
void ATS141_Routine(void);

//59.ATS142
uint8_t ATS142_Response[] = {""};
void ATS142_Routine(void);

//60.ATS143
uint8_t ATS143_Response[] = {""};
void ATS143_Routine(void);

//61.ATS144
uint8_t ATS144_Response[] = {""};
void ATS144_Routine(void);

//62.ATS145
uint8_t ATS145_Response[] = {""};
void ATS145_Routine(void);

//63.ATS146
uint8_t ATS146_Response[] = {""};
void ATS146_Routine(void);

//64.ATS147
uint8_t ATS147_Response[] = {""};
void ATS147_Routine(void);

//65.ATS148
uint8_t ATS148_Response[] = {""};
void ATS148_Routine(void);

//66.ATS149
uint8_t ATS149_Response[] = {""};
void ATS149_Routine(void);

//67.ATS150
uint8_t ATS150_Response[] = {""};
void ATS150_Routine(void);

//68.ATS151
uint8_t ATS151_Response[] = {""};
void ATS151_Routine(void);

//69.ATS152
uint8_t ATS152_Response[] = {""};
void ATS152_Routine(void);

//70.ATS153
uint8_t ATS153_Response[] = {""};
void ATS153_Routine(void);

//71.ATS154
uint8_t ATS154_Response[] = {""};
void ATS154_Routine(void);

//72.ATS155
uint8_t ATS155_Response[] = {""};
void ATS155_Routine(void);

//73.ATS156
uint8_t ATS156_Response[] = {""};
void ATS156_Routine(void);

//74.ATS157
uint8_t ATS157_Response[] = {""};
void ATS157_Routine(void);

//75.ATS158
uint8_t ATS158_Response[] = {""};
void ATS158_Routine(void);


//76.ATS159
uint8_t ATS159_Response[] = {""};
void ATS159_Routine(void);


//77.ATS160
uint8_t ATS160_Response[] = {""};
void ATS160_Routine(void);


//78.ATS161
uint8_t ATS161_Response[] = {""};
void ATS161_Routine(void);


//79.ATS162
uint8_t ATS162_Response[] = {""};
void ATS162_Routine(void);


//80.ATS163
uint8_t ATS163_Response[] = {""};
void ATS163_Routine(void);


//81.ATS164
uint8_t ATS164_Response[] = {""};
void ATS164_Routine(void);


//82.ATS165
uint8_t ATS165_Response[] = {""};
void ATS165_Routine(void);


//83.ATS166
uint8_t ATS166_Response[] = {""};
void ATS166_Routine(void);


//84.ATS167
uint8_t ATS167_Response[] = {""};
void ATS167_Routine(void);


//85.ATS168
uint8_t ATS168_Response[] = {""};
void ATS168_Routine(void);


//86.ATS169
uint8_t ATS169_Response[] = {""};
void ATS169_Routine(void);


//87.ATS170
uint8_t ATS170_Response[] = {""};
void ATS170_Routine(void);


//88.ATS171
uint8_t ATS171_Response[] = {""};
void ATS171_Routine(void);


//89.ATS172
uint8_t ATS172_Response[] = {""};
void ATS172_Routine(void);


//90.ATS173
uint8_t ATS173_Response[] = {""};
void ATS173_Routine(void);


//91.ATS174
uint8_t ATS174_Response[] = {""};
void ATS174_Routine(void);


//92.ATS175
uint8_t ATS175_Response[] = {""};
void ATS175_Routine(void);


//93.ATS176
uint8_t ATS176_Response[] = {""};
void ATS176_Routine(void);


//94.ATS177
uint8_t ATS177_Response[] = {""};
void ATS177_Routine(void);


//95.ATS178
uint8_t ATS178_Response[] = {""};
void ATS178_Routine(void);


//96.ATS179
uint8_t ATS179_Response[] = {""};
void ATS179_Routine(void);


//97.ATS180
uint8_t ATS180_Response[] = {""};
void ATS180_Routine(void);


//98.ATS181
uint8_t ATS181_Response[] = {""};
void ATS181_Routine(void);


//99.ATS182
uint8_t ATS182_Response[] = {""};
void ATS182_Routine(void);


//100.ATS183
uint8_t ATS183_Response[] = {""};
void ATS183_Routine(void);


//101.ATS184
uint8_t ATS184_Response[] = {""};
void ATS184_Routine(void);


//102.ATS185
uint8_t ATS185_Response[] = {""};
void ATS185_Routine(void);


//103.ATS186
uint8_t ATS186_Response[] = {""};
void ATS186_Routine(void);


//104.ATS187
uint8_t ATS187_Response[] = {""};
void ATS187_Routine(void);


//105.ATS188
uint8_t ATS188_Response[] = {""};
void ATS188_Routine(void);


//106.ATS189
uint8_t ATS189_Response[] = {""};
void ATS189_Routine(void);


//107.ATS190
uint8_t ATS190_Response[] = {""};
void ATS190_Routine(void);


//108.ATS191
uint8_t ATS191_Response[] = {""};
void ATS191_Routine(void);


//109.ATS192
uint8_t ATS192_Response[] = {""};
void ATS192_Routine(void);


//110.ATS193
uint8_t ATS193_Response[] = {""};
void ATS193_Routine(void);


//111.ATS194
uint8_t ATS194_Response[] = {""};
void ATS194_Routine(void);


//112.ATS195
uint8_t ATS195_Response[] = {""};
void ATS195_Routine(void);


//113.ATS196
uint8_t ATS196_Response[] = {""};
void ATS196_Routine(void);


//114.ATS197
uint8_t ATS197_Response[] = {""};
void ATS197_Routine(void);


//115.ATS198
uint8_t ATS198_Response[] = {""};
void ATS198_Routine(void);


//116.ATS199
uint8_t ATS199_Response[] = {""};
void ATS199_Routine(void);


//117.ATS200
uint8_t ATS200_Response[] = {""};
void ATS200_Routine(void);


//118.ATS201
uint8_t ATS201_Response[] = {""};
void ATS201_Routine(void);


//119.ATS202
uint8_t ATS202_Response[] = {""};
void ATS202_Routine(void);


//120.ATS203
uint8_t ATS203_Response[] = {""};
void ATS203_Routine(void);


//121.ATS204
uint8_t ATS204_Response[] = {""};
void ATS204_Routine(void);


//122.ATS205
uint8_t ATS205_Response[] = {""};
void ATS205_Routine(void);


//123.ATS206
uint8_t ATS206_Response[] = {""};
void ATS206_Routine(void);


//124.ATS207
uint8_t ATS207_Response[] = {""};
void ATS207_Routine(void);


//125.ATS208
uint8_t ATS208_Response[] = {""};
void ATS208_Routine(void);


//126.ATS209
uint8_t ATS209_Response[] = {""};
void ATS209_Routine(void);


//127.ATS210
uint8_t ATS210_Response[] = {""};
void ATS210_Routine(void);


//128.ATS211
uint8_t ATS211_Response[] = {""};
void ATS211_Routine(void);


//129.ATS212
uint8_t ATS212_Response[] = {""};
void ATS212_Routine(void);


//130.ATS213
uint8_t ATS213_Response[] = {""};
void ATS213_Routine(void);


//131.ATS214
uint8_t ATS214_Response[] = {""};
void ATS214_Routine(void);

//132.ATS215
uint8_t ATS215_Response[] = {""};
void ATS215_Routine(void);


//133.ATS216
uint8_t ATS216_Response[] = {""};
void ATS216_Routine(void);

//134.ATS217
uint8_t ATS217_Response[] = {""};
void ATS217_Routine(void);


//135.ATS218
uint8_t ATS218_Response[] = {""};
void ATS218_Routine(void);


//136.ATS219
uint8_t ATS219_Response[] = {""};
void ATS219_Routine(void);
/**
* @}
*/
/** @defgroup SERIAL_Private_Variables
* @{
*/
uint8_t string1[] = {"ATD STRING RESPONSE"};
uint8_t string2[] = {"ATE STRING RESPONSE"};
uint8_t string3[] = {"ATS STRING RESPONSE"};

/* Trie Structure Initialisation --------------------------------------------*/
trie_node *ROOT;
/**
* @}
*/

/** @defgroup SERIAL_Private_Functions
* @{
*/
/**
* @brief  This routine will Init the AT command interface
* @param  None.
* @retval None.
*/
void AT_PreProInit(void)
{ 
  trie_node *Command_ptr; 
  ROOT = createNode();
  /*add Command loading to dictionary code here, add ATD */
  addCommand("ATD",(uint8_t*)string1,&routine1);
  
  /* add ATE */
  addCommand("ATE",string2,&routine2);
  /*add ATS */
  addCommand("ATS",string3,&routine3);  
}
/**
* @brief  This routine will carries out command receiving and execution.
* @param  None.
* @retval None.
*/
void AT_PrePro(void)
{
  uint8_t Command[COMMAND_SIZE]; 
  trie_node *Command_ptr; 
  uint8_t *response;  
  int index;
  DisableRx();
  if(Echo){
    SendResponse((uint8_t*)getRxBuffer());
  }
  GetCommand(Command);
  Command_ptr = findCommand(Command);
  
  if(Command_ptr!=NULL)
  {
    index = GetCommandLength(Command);  
    if((RxBuffer_readElement(index)==0x3D)&&(RxBuffer_readElement(index+1)==0x3F))
    {     
      response = Command_ptr->string_response;
      SendResponse(response);
    }
    else
    {
      (*(Command_ptr->routine_ptr))();      
    }
    SendResponse("OK\r\n");
  }
  else
  {
    SendResponse("ERROR\r\n");
  }
  RxBuffer_clear();
  EnableRx();
}
/**
* @brief  This routine will Send the string to the TxBuffer at serial interface which sends it to the DCE
* @param  uint8_t *response:Response String to be sent to the DCE
* @retval None.
*/
void SendResponse(uint8_t *response)
{
  while(*response)
  {
    TxBuffer_addElement(*response);
    response++;
  }
  EnableTx();
}

/**
* @brief  This routine will extract command from Rx string.
* @param  uint8_t *command:string to be loaded with the command extracted from the RxBuffer
* @retval None.
*/
void GetCommand(uint8_t *command)
{
  uint32_t index = RxBuffer_getLength();
  uint8_t element;
  uint32_t iterator;
  iterator = 0;
  while(iterator <= index)
  {
    element = RxBuffer_readElement(iterator);   
    if((element == 0x3F)||(element == 0x3D))
    {
      return;
    }
    else
    {
      command[iterator++] = element;
    }
  }
}
/**
* @brief  This routine will calculate the command length.
* @param  uint8_t *command:command string.
* @retval length of the command.
*/
int GetCommandLength(uint8_t *command)
{
  int lth = 0;
  while(*command)
  {
    lth++;
    command++;
  }
  return lth;
}
/**
* @brief  This routine will calculate the command length.
* @param  uint8_t *command:Command name to be added.
*         uint8_t * response: Command fixed string response
*         void (*routine_ptr)(void)): function pointer to the routine of the command
* @retval None.
*/
void addCommand(uint8_t * command,uint8_t * response,void (*routine_ptr)(void)) 
{
  trie_node *trie_itr,*child;
  trie_itr = ROOT;
  while(*command)
  {
   child = findChild(*command , trie_itr->children);
   if(child!=NULL)
   {
     trie_itr = child;
     command++;
   }
   else
   {
     child = addChild(*command , &(trie_itr->children));
     trie_itr = child;
     command++;
   }
  }   
  trie_itr->flag = 1;  // TRUE = 1
  trie_itr->string_response = response;
  trie_itr->routine_ptr = routine_ptr;
}
/**
* @brief  This routine will allocates memory to a node (creates a dictionary \
  *             node) and returns a pointer to that location in heap memory
* @param  None.
* @retval trie_node*:pointer to a memory location in the heap .
*/
trie_node *createNode(void)
{
  trie_node * temp2 = (trie_node *)malloc(sizeof(trie_node));
  temp2->children = NULL;
  temp2->value = 0;
  temp2->routine_ptr = NULL;
  temp2->string_response = NULL;
  temp2->flag = 0;  
  return temp2;
}
/**
* @brief  This routine will search child in linked list.
* @param  uint8_t *command:Command name in string form
* @retval trie_node*: pointer to the youngest child node in the tree corresponding to the word
*/
trie_node *findCommand(uint8_t *command)
{
  trie_node *temp,*child;
  temp = ROOT;
  while(*command)
  {
    child = findChild(*command , temp->children);
    if(child!=NULL)
    {
      temp = child;
      command++;
    }
    else{
      return NULL;
    }
  }
  if(temp->flag)
  {
    return temp;
  }
  else
  {
    return NULL;
  }
}


/**
* @brief  This routine will search child in linked list.
* @param  uint8_t value:character value to be searched
*         list_node *Head_ref:pointer to the head of the linked list of children nodes
* @retval trie_node*: pointer to the child node with the value as the character  \
  *                   or NULL if the child does no exist
*/
trie_node *findChild(uint8_t value,list_node *Head)
{
  list_node *temp;
  temp = Head;
  while(temp!=NULL)
  {
    if(temp->node_ptr->value == value)
    {
      return temp->node_ptr;
    }
    else{
      temp = temp->next;
    }
  }
  return NULL;
}


/**
* @brief  This routine will add child to linked list.
* @param  uint8_t value:character value to be added
*         list_node **Head_ref:pointer to the head of the linked list to children nodes
* @retval trie_node*: The pointer to the node newly added.
*/
trie_node *addChild(uint8_t value,list_node **Head_ref)
{
  list_node *temp;
  temp = (*Head_ref);
  if((*Head_ref) == NULL)
  {
    (*Head_ref) = (list_node *)malloc(sizeof(list_node));
    (*Head_ref)->node_ptr = createNode();
    (*Head_ref)->node_ptr->value = value;
    (*Head_ref)->next = NULL;
    return ((*Head_ref)->node_ptr);
  }
  else
  {
    while(temp->next!=NULL)
    {
      temp = temp->next;
    }
    temp->next = (list_node *)malloc(sizeof(list_node));
    temp->next->node_ptr = createNode();
    temp->next->node_ptr->value = value;
    temp->next->next = NULL;
    return (temp->next->node_ptr);
  }
}
/**
* @brief  This routine will handles ATS3 Command.
* @param  None.
* @retval None.
*/
void ATS3_Routine(void)
{
  uint8_t response[25];
  if(RxBuffer_readElement(4)==0x3F)
  {
    toString(CommandLineTerminator,response);
    SendResponse(response);
    SendResponse("\r\n");    
  }
  else 
  {
    CommandLineTerminator = RxBuffer_readElement(5);
  }
}
/**
* @brief  This routine will handles ATS5 Command.
* @param  None.
* @retval None.
*/
void ATS5_Routine(void)
{
  uint8_t response[25];
  if(RxBuffer_readElement(4)==0x3F)
  {
    //reply with current value
    toString(CommandLineEditor,response);
    SendResponse(response);
    SendResponse("\r\n");    
  }
  else 
  {
    CommandLineEditor = RxBuffer_readElement(5);
  }
}

/**
* @brief  This routine will handles ATE Command.
* @param  None.
* @retval None.
*/
void ATE_Routine(void)
{
  uint8_t response[25];
  if(RxBuffer_readElement(3)==0x3F)
  {
    toString(Echo,response);
    SendResponse(response);
    SendResponse("\r\n");    
  }
  else {
    Echo = RxBuffer_readElement(4);
  }
}
/**
* @brief  This routine will handles ATR Command.
* @param  None.
* @retval None.
*/
void ATR_Routine(void)
{
}
/**
* @brief  This routine will handles AT+IFC Command.
* @param  None.
* @retval None.
*/
void ATIFC_Routine(void)
{
  uint8_t response[25];
  if(RxBuffer_readElement(6)==0x3F)
  {//ATxx? syntax
    toString(SerialHardwareFlowControl,response);
    SendResponse(response);
    SendResponse("\r\n");    
  }
  else 
  {
    SerialHardwareFlowControl = (RxBuffer_readElement(7)-48)*100 + \
                (RxBuffer_readElement(8)-48)*10 + (RxBuffer_readElement(9)-48);
    USART_ReConfig();
  }
}

/**
* @brief  This routine will handles AT+IPR Command.
* @param  None.
* @retval None.
*/
void ATIPR_Routine(void)
{
  uint8_t response[25];
  if(RxBuffer_readElement(6)==0x3F)
  {
    toString(SerialBaudRate,response);
    SendResponse(response);
    SendResponse("\r\n");    
  }
  else 
  {
    SerialBaudRate = toNumber((uint8_t*)getRxBuffer());
    USART_ReConfig();
  }
}
/**
* @brief  This routine will handles ATV/V Command.
* @param  None.
* @retval None.
*/
void V_Routine(void)
{
  SendResponse(FirmwareVersion);
  SendResponse("\r\n");
}
/**
* @brief  This routine will handles ATS+CMGS Command.
* @param  None.
* @retval None.
*/
void ATCMGS_Routine(void)
{
}
/**
* @brief  This routine will handles ATD Command.
* @param  None.
* @retval None.
*/
void routine1(void)
{
  SendResponse("ATD ROUTINE");
}
/**
* @brief  This routine will handles ATE Command.
* @param  None.
* @retval None.
*/
void routine2(void)
{
  SendResponse("ATE ROUTINE");
}
/**
* @brief  This routine will handles ATS Command.
* @param  None.
* @retval None.
*/
void routine3(void)
{
  SendResponse("ATS ROUTINE");
}
/**
* @brief  This routine will convert the string to uint32_t.
* @param  uint8_t *string: The string.
* @retval uint32_t.
*/
uint32_t toNumber(uint8_t *string)
{
  uint32_t number = 0;
  while(*string){
    number = (*string-48) + number*10;
  }
  return number;
}
    
/**
* @brief  This routine will convert the uint64_t to string
* @param  uint64_t number:
*         uint8_t *string.
* @retval None.
*/
void toString(uint64_t number, uint8_t *string)
{
   uint8_t temp[25];
   uint8_t count = 1 , index , count2 = 0;
   temp[0] = 48 + number%10;
   number = number / 10;
   while(number > 0)
   {
     temp[count++] = 48 + number%10;
     number = number / 10;
   }
   
   for(index = count-1; index > 0 ; index--)
   {
     string[count2++] = temp[index];
   }
   string[count2] = temp[index];
    
}
/**
* @}
*/
/**
* @}
*/
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/  