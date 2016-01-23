/**
******************************************************************************
* @file    aes_ctr.c
* @author  System Lab - NOIDA
* @version V1.0.8
* @date    24-Jul-2014
* @brief   This file contains AES routines 
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

#include "aes128.h"
#include "wmbus_appli.h"
#include "stdint.h" 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private funtion prototypes ------------------------------------------------*/

void add_counter(u32 *aCtr);
void bitwise_xor(unsigned char *pIna, unsigned char *pInb, unsigned char *pOut);
u32 decrypt_pdu(u32 *aExp_key, unsigned char *pCipher,int len, \
  unsigned char *pPlain );
void decrypt_pdu_cbc(u32 *aExp_key, unsigned char *pCipher,int len,\
  unsigned char *pPlain);
u32 encrypt_pdu(u32 *aExp_key, unsigned char *pPlain, int len,\
  unsigned char *pCipher);
void encrypt_pdu_cbc(u32 *aExp_key, unsigned char *pPlain, int len,\
  unsigned char *pCipher);
void WMBus_AppliDecrypt(u8 *pKey, unsigned char *pPayload, int length);
uint8_t WMBus_AppliEncrypt(u8 *pKey, unsigned char *pPayload, int length);






/* User's secret key */


/* Expanded key */
u32 aExp_key[AES_EXPKEY_SIZE]={0};

/* plaitext blocks */




/* ciphertext blocks for temporary buffering */
/* Don't make nonce as const because in decryption it needs to reload itself*/
u32 nonce=0x5cb44a05;  
u32 aCtr[4]={0};
u32 aes_out[4]={0};
unsigned char aRemain[16]={0};
unsigned char aTemp[16]={0};
unsigned char aRevBuff[USER_DATA_MAX_LENGHT]={0};
unsigned char aBuff[16]={0};
int g_index;
int n_blocks=0, n_remain=0;

uint8_t CipherBlocklen = 0x00;


/*******************************************************************************
* Function Name  : bitwise_xor
* Description    : For Xor operation of blocks
* Input          : - input_pointer: input block a address
*                  - input_pointer: input block b address 
* Output         : output_pointer: output block address
* Return         : None
*******************************************************************************/
void bitwise_xor(unsigned char *pIna, unsigned char *pInb, unsigned char *pOut)
{
 
  for (; g_index<16; g_index++)
  {
    pOut[g_index] = pIna[g_index] ^ pInb[g_index];
  }
}





/*******************************************************************************
* Function Name  : add_counter
* Description    : It increment counter by one upon encryption of each block
* Input          : - input_pointer: counter address
* Output         : None
* Return         : None
*******************************************************************************/
void add_counter(u32 *aCtr)
{
  int value=0;
  value = aCtr[3] & 0xffffffff;
  value ++;
  aCtr[3] = value & 0xffffffff;
}


/*******************************************************************************
* Function Name  : encrypt_pdu
* Description    : Encrypts the incoming stream
* Input          : - input_pointer: expended key address
*                  - input_pointer: input plain data address
*                  - int: length
* Output         : output_pointer: output pCipher data address
* Return         : None
*******************************************************************************/
u32 encrypt_pdu(u32 *aExp_key, unsigned char *pPlain, int len, unsigned char *pCipher)
{
  int out_len = 0;
  out_len += 4;
  n_blocks = len / 16;
  n_remain = len % 16;
  
  
  
  /*Encryption starts here..................*/
  for ( g_index=0; g_index< n_blocks; g_index++ ) {
    AES_encrypt(aAES_InitnalizationVector_Tx,(u32*)aes_out,aExp_key); 
    bitwise_xor((unsigned char*)(aes_out), &pPlain[g_index*16], &pCipher[g_index*16]);
    add_counter((uint32_t*)aAES_InitnalizationVector_Tx);
    out_len += 16;
  }/*n_blocks have been encrypted, each with different counter value*/
  
  
  for ( g_index=0; g_index<16; g_index++ ) {
    aRemain[g_index] = 0;
  }
  
  /*Storing remaining words in aRemain buffer*/
  for ( g_index=0; g_index<n_remain; g_index++ ) {
    aRemain[g_index] = pPlain[n_blocks*16+g_index];
  }
  
  /*Encryption of the last block starts here*/
  AES_encrypt(/*(u32*)*/aAES_InitnalizationVector_Tx,(u32*)aes_out,(u32*)aExp_key); 
  bitwise_xor((unsigned char*)(aes_out),&aRemain[0], &aTemp[0]);
  
  /*putting remaining result into pCipher buffer*/
  for ( g_index=0; g_index<n_remain; g_index++ ) {
    pCipher[n_blocks*16+g_index] = aTemp[g_index];
  }
  
  out_len += n_remain;
  return nonce;
}


/*******************************************************************************
* Function Name  : decrypt_pdu
* Description    : Decrypts the incoming stream
* Input          : - input_pointer: expended key address
*                  - input_pointer: input pCipher data address
*                  - int: length
* Output         : output_pointer: output plain data address
* Return         : None
*******************************************************************************/
u32 decrypt_pdu(u32 *aExp_key, unsigned char *pCipher,int len, unsigned char *pPlain )
{
  int out_len = 0;
  
  /*Getting the value of Nonce by capturing first word from incoming data*/
  n_blocks = len / 16;
  n_remain = len % 16;
  
  
  /*Decryption starts here..................*/
  for ( g_index=0; g_index< n_blocks; g_index++ ) {
    AES_encrypt(aAES_InitnalizationVector_Rx,(u32*)aes_out,(u32*)aExp_key); 
    bitwise_xor((unsigned char*)(aes_out), &pCipher[g_index*16], &pPlain[g_index*16]);
    add_counter((u32*)aAES_InitnalizationVector_Rx);
    out_len += 16;
  }
  
  
  for ( g_index=0; g_index<16; g_index++ ) {
    aRemain[g_index] = 0;
  }
  
  /*Storing remaining words in aRemain buffer*/
  for ( g_index=0; g_index<n_remain; g_index++ ) {
    aRemain[g_index] = pCipher[n_blocks*16+g_index];
  }
  
  /*Decryption of the last block starts here*/
  AES_encrypt(aAES_InitnalizationVector_Rx,(u32*)aes_out,(u32*)aExp_key);  
  
  /*Notice that AES_encrypt is called for decryption instead of AES_decrypt*/
  bitwise_xor((unsigned char*)(aes_out),&aRemain[0], &aTemp[0]);
  
  /*putting remaining result into pPlain buffer*/
  for ( g_index=0; g_index<n_remain; g_index++ ) {
    pPlain[n_blocks*16+g_index] = aTemp[g_index];
  }
  out_len += n_remain;
  return nonce;
}




/*******************************************************************************
* Function Name  : decrypt_pdu_cbc
* Description    : Decrypts the incoming stream
* Input          : - input_pointer: expended key address
*                  - input_pointer: input pCipher data address
*                  - int: length
* Output         : output_pointer: output plain data address
* Return         : None
*******************************************************************************/
void decrypt_pdu_cbc(u32 *aExp_key, unsigned char *pCipher,int len, unsigned char *pPlain)
{
  n_blocks = len / 16;
  n_remain = len % 16;
  uint8_t atempbuff[16]={0};
  
  /*Decryption starts here..................*/
  memcpy( aRevBuff, pCipher, len );
  for ( g_index=0; g_index<n_blocks; g_index++ )
  {
    for(uint8_t count=0; count<16; count++)
    {
      aBuff[count] = aRevBuff[(g_index*16)+count];
    }
    AES_decrypt(aBuff,(u32*)aes_out,aExp_key);
    memcpy( atempbuff, aes_out, 16 );    
    for(uint8_t count =0; count<4; count++)
    {
      for(uint8_t aCtr =0; aCtr<4;aCtr++)
      {
        aTemp[aCtr+count*4] =   atempbuff[(3-aCtr)+(count*4)];
      }
    }
    
    bitwise_xor(aTemp,&aAES_InitnalizationVector_Rx[0], &pPlain[g_index*16]);
    memcpy( aAES_InitnalizationVector_Rx, aBuff, 16 );
  }/*decription of n_blocks completed*/
}


/*******************************************************************************
* Function Name  : encrypt_pdu_cbc
* Description    : Encrypts the incoming stream
* Input          : - input_pointer: expended key address
*                  - input_pointer: input plain data address
*                  - int: length
* Output         : output_pointer: output pCipher data address
* Return         : None
*******************************************************************************/
void encrypt_pdu_cbc(u32 *aExp_key, unsigned char *pPlain, int len, unsigned char *pCipher)
{
  n_blocks = len / 16;
  n_remain = len % 16;
  uint8_t atempbuff[16]={0};
  CipherBlocklen = 0x00;
  
  /*Encryption starts here..................*/
  for (g_index=0; g_index< n_blocks; g_index++ )
  {
    bitwise_xor((unsigned char*)aAES_InitnalizationVector_Tx, &pPlain[g_index*16], &aTemp[0] );
    AES_encrypt(aTemp,aes_out,aExp_key); 
    memcpy( atempbuff, aes_out, 16 );
    
    for(uint8_t count =0; count<4; count++)
    {
      for(uint8_t aCtr =0; aCtr<4;aCtr++)
      {
        aAES_InitnalizationVector_Tx[aCtr+count*4] =   atempbuff[(3-aCtr)+(count*4)];
      }
    }
    
    for(uint8_t count=0; count<16; count++)
    {
      pCipher[(g_index*16)+count] = aAES_InitnalizationVector_Tx[count];
    }
    CipherBlocklen +=16;
  }/*n_blocks have been encrypted*/ 
  if(n_remain!=0)
  {
    for ( g_index=0; g_index<16; g_index++ ) {
      aRemain[g_index] = 0;
    }
    
    /*Storing remaining words in aRemain buffer*/
    for ( g_index=0; g_index<n_remain; g_index++ )
    {
      aRemain[g_index] = pPlain[n_blocks*16+g_index];
    }
    if(n_remain < 16)
    {
      for ( g_index=n_remain; g_index<16; g_index++ )
      {
        aRemain[g_index] = 0x2F;
      }
    }
    
    /*Encryption of the last block starts here*/ 
    bitwise_xor((unsigned char*)aAES_InitnalizationVector_Tx, &aRemain[0], &aTemp[0] );
    AES_encrypt(aTemp,(u32*)aes_out,(u32*)aExp_key);
    /*putting remaining result into pCipher buffer*/
    memcpy( atempbuff, aes_out, 16 );
    
    for(uint8_t count =0; count<4; count++)
    {
      for(uint8_t aCtr =0; aCtr<4;aCtr++)
      {
        pCipher[n_blocks*16+aCtr+count*4] =   atempbuff[(3-aCtr)+(count*4)];
      }
    }
    
    CipherBlocklen += 16;    
  }
}


/*******************************************************************************
* Function Name  : WMBus_AppliEncrypt
* Description    : Does key expension before encryption starts
*                  and put the data stream back into payload buffer
* Input          : - input_pointer: input payload address
*                  - input pointer: encryption key 
*                  - int: length
* Output         : None
* Return         : None
*******************************************************************************/
uint8_t WMBus_AppliEncrypt(u8 *pKey, unsigned char *pPayload, int length)
{
  /*******************************************************/
  /*                   AES CTR ENCRYPTION                */
  /*******************************************************/       
  
  /* Encryption key scheduling, to be done once */
  AES_keyschedule_enc((u8*)pKey,(u32*)aExp_key); 
  /* encryption starts here*/
  encrypt_pdu_cbc((u32*)aExp_key,pPayload,length,pPayload); 
  return(CipherBlocklen);
}


/*******************************************************************************
* Function Name  : WMBus_AppliDecrypt
* Description    : Does key expension before decryption starts
*                  and put the data stream back into payload buffer
* Input          : - input_pointer: input payload address
*                  - input pointer: encryption key 
*                  - int: length
* Output         : None
* Return         : None
*******************************************************************************/
void WMBus_AppliDecrypt(u8 *pKey, unsigned char *pPayload, int length)
{
  
  /*******************************************************/
  /*                   AES CTR DECRYPTION                */
  /*******************************************************/
  
  /* Decryption key scheduling, to be done once */
  AES_keyschedule_dec((u8*)pKey,(u32*)aExp_key);
  /* decryption */
  decrypt_pdu_cbc((u32*)aExp_key,pPayload,length,pPayload);
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
