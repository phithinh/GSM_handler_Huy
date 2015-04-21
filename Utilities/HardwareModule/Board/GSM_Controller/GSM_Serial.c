#define _GSM_SERIAL_C

/* Includes ------------------------------------------------------------------*/
//#include <general_define.h>
#include <PlatFormType.h>
#include "GSM_Serial_adapt.h"
#include "GSM_Serial.h"
#include "../SIM900/SIM900.h"
#include "GSM_stm32_gpio.h"
#include "TaskGSM.h"
//#include <GSM_stm32f_SerialCom.h>

//#define GSM_WITH_RTOS       /*Used this driver with RTOS*/
//#define GSM_ECHO_MODE       /*Turn on echo mode*/

char GSM_RxBuffer[GSM_RX_BUFFER_SIZE];
uint16 RxCounter = 0;
enumbool fgGSMRxFlag = eFALSE;

/*Remove String Function in irq*/
enumState GSMRemoveStrFuncEn = eDISABLE;/*mode remove string in Rx Buffer*/
enumbool fgGetStrValue = eFALSE;
char* p_sRemoveStr;
uint8* p_StrValue;              /*Used in mode remove string, must be assigned when enable GSMRemoveStrFuncEn*/

extern enumGSMTask     gGSMTask_Index;

/*Alert SMS receive in irq*/
enumState       GSMAlertNewSMSFuncEn = eDISABLE;
enumbool        fgNewSMSReceive = eFALSE;
uint8           bIdxOfNewSMS;/*Idx start from 1*/

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSM_Init
*Description:   Init GSM Module
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
void GSM_Init(void)
{
	GSM_SerialCom_Init_v();
    /*Turn on GSM*/
//    GSM_TurnOn();

//    GSM_Reset();
    GSM_NewSMSAlertFunc(eENABLE);
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSM_IRQHANDLER
*Description:   Interupt functions of Uart receiver
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
void GSM_IRQHANDLER(unsigned char p_data_ub)
{
    uint32 iStrAddr = 0;
    static uint8 bCount = 0;
    char bTempBuff[3];
//    if(!GSM_SerialCom_RxEmpty_b())
//    {
        /* Read one byte from the receive data register */
        GSM_RxBuffer[RxCounter] = (p_data_ub & 0x7F);
        fgGSMRxFlag=eFALSE;
        RxCounter++;
        if ((RxCounter == (GSM_RX_BUFFER_SIZE))||(GSM_RxBuffer[RxCounter-1]==0))
        {/*In case overload buffer and break data, must be reset counter*/
            GSM_ClearRxBuffer();/*Clear all buffer after*/
        }
        
        /*Remove String Function*/
        if (GSMRemoveStrFuncEn)
        {
            if (!fgGetStrValue)
            {
                iStrAddr = (uint32)strstr(GSM_RxBuffer,p_sRemoveStr);
                if (iStrAddr)
                {
                    iStrAddr = iStrAddr - (uint32)GSM_RxBuffer;
                    GSM_ClearRxBuffer();/*Clear all buffer after*/
                    fgGetStrValue = eTRUE;
                }
            }
            else
            {
                iStrAddr = (uint32)strstr(GSM_RxBuffer,",");
                if (iStrAddr)
                {
                    iStrAddr = iStrAddr - (uint32)GSM_RxBuffer;
                    memcpy(bTempBuff,GSM_RxBuffer,iStrAddr);
                    *p_StrValue = atoi(bTempBuff);
                    p_StrValue++;bCount++;
                    fgGetStrValue = eFALSE;
                }
            }
            if (bCount==LIST_SMS_MAX)
            {/*Get full buffer*/
                GSMRemoveStrFuncEn = eDISABLE;/*Turn off function*/
                bCount = 0;
            }
        }
        
        /*Alert New SMS Function*/
        if (GSMAlertNewSMSFuncEn)
        {
            if (!fgNewSMSReceive)
            {
                iStrAddr = (uint32)strstr(GSM_RxBuffer,"+CMTI: \"SM\",");
                if (iStrAddr)
                {
                    GSM_ClearRxBuffer();/*Clear all buffer after*/
                    fgNewSMSReceive = eTRUE;
                    gGSMTask_Index = eGSMTask_ReceiveSMS;
                }
            }
            else
            {
                iStrAddr = (uint32)strstr(GSM_RxBuffer,"\r");
                if (iStrAddr)
                    bIdxOfNewSMS = atoi(GSM_RxBuffer);/*Get index of new SMS*/
            }
        }
//    }
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: 
*Description:   
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
static void GSMSendUartData(char* ch)
{
//    uint8 i;
//
//    for(i=0;i<strlen(ch);i++)
//    {
//        /* e.g. write a character to the USART */
//        GSM_SerialCom_SendData_v(ch[i]);
//
//        /* Loop until the end of transmission */
//        while (!GSM_SerialCom_GetTxFree_b())
//        {}
//    }
    printf(ch);
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSM_TurnOn
*Description:   
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
void GSM_TurnOn(void)
{
    if (GSM_STATUS_OFF== GSM_GetStatusPort_b())
    {
        /*Creat 1s pulse down*/
        GSM_SetOnOffPort_v(Bit_RESET);
        T1Us_DelayMs(2000);
        GSM_SetOnOffPort_v(Bit_SET);
        T1Us_DelayMs(1200);
        GSM_SetOnOffPort_v(Bit_RESET);
        T1Us_DelayMs(2000);
    }
    
    T1Us_DelayMs(50);/*Delay 50ms*/
#ifdef GSM_ECHO_MODE
    _GsmTurnOnEchoMode();/*Turn On Echo Mode*/
#else
    _GsmTurnOffEchoMode();/*Turn Off Echo Mode*/
#endif
    T1Us_DelayMs(50);/*Delay 50ms*/
    
    _GsmSmsTextMode();/*Config module receive SMS in Text Mode*/
    //    vTaskDelay(50);
    T1Us_DelayMs(50);/*Delay 50ms*/
    
    _GsmSaveConfig();/*Save all config*/
    //    vTaskDelay(50);
    T1Us_DelayMs(50);/*Delay 50ms*/
    
    GSM_SetSpeakerVolume(100);
    //    vTaskDelay(50);
    T1Us_DelayMs(50);/*Delay 50ms*/
    
    _GsmTurnOnOperationMode();
    //    vTaskDelay(200);
    T1Us_DelayMs(200);/*Delay 200ms*/
    
    _GsmCheckPIN();
    T1Us_DelayMs(50);/*Delay 200ms*/
    
    _GsmCheckCommunicate();
    T1Us_DelayMs(50);/*Delay 200ms*/
    
    GSM_ClearRxBuffer();/*Clear all buffer*/    
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSM_TurnOff
*Description:   
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
void GSM_TurnOff(void)
{
    if (GSM_STATUS_ON == GSM_GetStatusPort_b())
    {
        /*Creat 1s pulse down*/
        GSM_SetOnOffPort_v(Bit_SET);
        T1Us_DelayMs(2000);
        GSM_SetOnOffPort_v(Bit_RESET);
        T1Us_DelayMs(1200);
        GSM_SetOnOffPort_v(Bit_SET);
        T1Us_DelayMs(2000);
    }
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSM_TurnOn
*Description:   
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
void GSM_Reset(void)
{
    /*Creat 1s pulse down*/
    GSM_SetResetPort_v(Bit_RESET);
    T1Us_DelayMs(200);
    GSM_SetResetPort_v(Bit_SET);
    T1Us_DelayMs(50);
    GSM_SetResetPort_v(Bit_RESET);
    T1Us_DelayMs(200);
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: InitRemoveSringFunction
*Description:   
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
static void InitRemoveSringFunction(char* p_String, uint8* p_Value)
{
    /*reset all value, assigned pointer before use Remove Sring Function*/
    fgGetStrValue = eFALSE;
    p_sRemoveStr = p_String;
    p_StrValue = p_Value;
    /*Enable Remove Sring Function**/
    GSMRemoveStrFuncEn = eENABLE;
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: DisableRemoveSringFunction
*Description:   
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
static void GSM_RemoveSringFunction(enumState eState)
{
    GSMRemoveStrFuncEn = eState;
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSM_ClearRxBuffer
*Description:   Interupt functions of Uart receive
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
static void GSM_ClearRxBuffer(void)
{
    memset(GSM_RxBuffer,0,sizeof(GSM_RxBuffer));
    RxCounter = 0;
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSM_ClearRxBuffer
*Description:   Interupt functions of Uart receive
*Input: bTimeOutByte   Time out between byte of response data(ms)
bTimeOutData    max time out of data
*Output: enumATResponseType
-----------------------------------------------------------------------------*/
static enumATResponseType GSM_WaitResponse(char* AT_Command, uint16 bTimeOutMax)
{
    uint16 bTimerTick = 0;
    uint32 iAddr;
    enumATResponseType blValue = eAT_NONE_RESP;
    
    GSM_ClearRxBuffer();
    fgGSMRxFlag = eTRUE;
    
    while (bTimerTick<bTimeOutMax)
    {/*Loop until over timeout*/
#ifdef GSM_WITH_RTOS
        vTaskDelay(1);/*Delay 1 ms*/
#else
        T1Us_DelayMs(1);
#endif
        bTimerTick++;
        
        if (!fgGSMRxFlag)
        {
            fgGSMRxFlag = eTRUE;
            bTimerTick = 0;
            blValue = eAT_ERROR_RESP;/*Not receive right response*/
        }
    }
    iAddr = (uint32)strstr(GSM_RxBuffer,AT_Command);
    if (iAddr)
    {/*has AT_Command in GSM_RxBuffer*/
        blValue = eAT_SUCCESS_RESP;
    }
    else
    {
        iAddr = (uint32)strstr(GSM_RxBuffer,"OK");
        if (iAddr)
            blValue = eAT_OK_RESP;
    }
    
    return blValue;
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSM_GetNewSMS
*Description:   Check new SMS, if has, will be read
*Input: None
*Output: enumATResponseType  
-----------------------------------------------------------------------------*/
enumbool GSM_GetNewSMS(structSMSMessageInfo* p_strtNewSMS)
{
    if ((fgNewSMSReceive)&&(GSMAlertNewSMSFuncEn==eENABLE))
    {/*New SMS to phone*/
        fgNewSMSReceive = eFALSE;
        GSM_GetSMSByIdx(bIdxOfNewSMS,p_strtNewSMS);
    }
    
    return fgNewSMSReceive;
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSM_NewSMSAlertFunc
*Description:   
*Input: eState  eENABLE or eDISABLE
*Output:   
-----------------------------------------------------------------------------*/
void GSM_NewSMSAlertFunc(enumState eState)
{
    GSMAlertNewSMSFuncEn = eState;
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSM_CheckCommunicate
*Description:   Check communication with SIM900 Module
*Input: None
*Output: enumATResponseType  
-----------------------------------------------------------------------------*/
enumATResponseType GSM_CheckCommunicate(void)
{
    _GsmCheckCommunicate();
    return GSM_WaitResponse("OK",50); /*wait all response in 100ms*/
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSM_CheckSIMOrReady
*Description:   Check SIM Access
*Input: None
*Output: enumSIMPINType
-----------------------------------------------------------------------------*/
enumSIMPINType GSM_CheckSIMOrReady(void)
{
    enumSIMPINType eSIMPINType;
    uint8 bTemp;
    
    GSMSendUartData("AT+CPIN?\r\n");
    bTemp = strlen("+CPIN: ");
    if (GSM_WaitResponse("+CPIN: ",100))
    {
        bTemp += 2;
        if (memcmp(&GSM_RxBuffer[bTemp],"READY",strlen("READY"))==0)
            eSIMPINType = eSIM_READY;
        else if (memcmp(&GSM_RxBuffer[bTemp],"SIM PIN",strlen("SIM PIN"))==0)
            eSIMPINType = eSIM_PIN;
        else
            eSIMPINType = eSIM_ERROR;
    }
    else
        eSIMPINType = eSIM_NOT_PRESENT;
    
    return eSIMPINType;
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSMSendSMS
*Description:   Check SIM Access
*Input: None
*Output: enumATResponseType     -1      eAT_ERROR_RESP
0       eAT_NONE_RESP
>1      index of Send SMS message                               
-----------------------------------------------------------------------------*/
enumATResponseType GSM_SendSMSByPhoneNumber(char* bPhoneNumber, char* bTextString)
{
    enumATResponseType blValue = eAT_NONE_RESP;
    char bEnd[2];
    char SmsIdx[2];/*2 digit, max 99 sms*/
    
    /*Add END_OF_SMS symbol*/
    bEnd[0] = END_OF_SMS;
    bEnd[1] = '\0';
    
    GSMSendUartData("AT+CMGS=\"");
    GSMSendUartData(bPhoneNumber);
    GSMSendUartData("\"\r");
    /*Waiting for '>' response*/
    blValue = GSM_WaitResponse(">",50);
    if (blValue==eAT_SUCCESS_RESP)
    {
        /*Send sms text*/
        GSMSendUartData(bTextString);
        GSMSendUartData(bEnd);
        GSM_WaitResponse("+CMGS: ",50);
        /*Get SMS Index string*/
        memcpy(SmsIdx,&GSM_RxBuffer[strlen("+CMGS: ")],sizeof(SmsIdx));
        /*Change to integer value*/
        blValue = atoi(SmsIdx);
    }
    return blValue;
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSMGetSMS
*Description:   
*Input: None
*Output: enumSMSType
p_strtSMS    pointer to SMS structure
-----------------------------------------------------------------------------*/
enumATResponseType GSM_GetListSMS(enumSMSType eSMSType, structListSMS* p_strtListSms)
{
    enumATResponseType blValue = eAT_NONE_RESP;
    uint16 bTimeTick=0;
    char sSMS_CMGL[] = "+CMGL: ";
    
    memset(p_strtListSms->bListSmsIdx,0,sizeof(p_strtListSms->bListSmsIdx));
    p_strtListSms->eSMSType = eSMSType;
    /*Send AT Command*/
    GSMSendUartData("AT+CMGL=");
    switch (eSMSType)
    {
    case eSMS_UNREAD:
        GSMSendUartData("\"REC UNREAD\"");
        break;
    case eSMS_READ:
        GSMSendUartData("\"REC READ\"");
        break;
    case eSMS_STO_UNSENT:
        GSMSendUartData("\"REC STO UNSENT\"");
        break;
    case eSMS_STO_SENT:
        GSMSendUartData("\"REC STO SENT\"");
        break;    
    case eSMS_ALL:
        GSMSendUartData("\"ALL\"");
        break;      
    }
    GSMSendUartData(CR_LF_SYMBOL);
    
    /*Reset buffer before receive response*/
    GSM_ClearRxBuffer();
    fgGSMRxFlag = eTRUE;
    
    /*Use Remove String Function*/
    InitRemoveSringFunction(sSMS_CMGL,p_strtListSms->bListSmsIdx);
    
    /*Waiting for timeout*/
    while (bTimeTick<500)/*After 500ms, if not receive any char, return Not response*/
    {
#ifdef GSM_WITH_RTOS
        vTaskDelay(1);/*Delay 5 ms*/
#else
        T1Us_DelayMs(1);
#endif
        bTimeTick++;
        
        if (!fgGSMRxFlag)
        {
            fgGSMRxFlag = eTRUE;
            bTimeTick = 0;
        }
    }
    if (p_strtListSms->bListSmsIdx[0])
        blValue = eAT_SUCCESS_RESP;  /*at least one message in SIM memory*/
    
    /*Disable Remove Sring Function**/
    GSM_RemoveSringFunction(eDISABLE);
    
    return blValue;
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSM_GetSMSByIdx
*Description:   
*Input: 
*Output: 
-----------------------------------------------------------------------------*/
enumATResponseType GSM_GetSMSByIdx(uint8 bSMSIdx, structSMSMessageInfo* p_strtSMS)
{
    enumATResponseType eATResponseType = eAT_NONE_RESP;
    char SmsIdx[3];/*2 digit, max 99 sms*/
    uint32 iAddr;
    uint8 bTemp;
    
    if ((bSMSIdx)&&(bSMSIdx<99))
    {
        UnsignIntegerToString(bSMSIdx,SmsIdx);
        /*AT command for read SMS message*/
        GSMSendUartData("AT+CMGR=");
        GSMSendUartData(SmsIdx);
        GSMSendUartData(CR_LF_SYMBOL);
        
        /*waiting for response in 50ms timeout*/
        eATResponseType = GSM_WaitResponse("+CMGR:",500);
        if (eATResponseType==eAT_SUCCESS_RESP)
        {
            /*Clear sms buffer*/
            memset(p_strtSMS,0,sizeof(structSMSMessageInfo));
            
            p_strtSMS->bSMSIdx = bSMSIdx;/*Get SMS Index*/
            
            /*Get SMS Type if required*/
            iAddr = (uint32)strstr(GSM_RxBuffer,",");
            iAddr = iAddr-(uint32)GSM_RxBuffer;
            memset(GSM_RxBuffer,' ',iAddr+1);/*clear old data*/
            
            /*Get SMS Phone Number if required*/
            iAddr = (uint32)strstr(GSM_RxBuffer,"\"");
            bTemp = iAddr-(uint32)GSM_RxBuffer;
            GSM_RxBuffer[bTemp] = ' ';
            iAddr = (uint32)strstr(GSM_RxBuffer,"\"");
            iAddr = iAddr-(uint32)GSM_RxBuffer-1;
            memcpy(p_strtSMS->sPhoneNumber,&GSM_RxBuffer[bTemp+1],iAddr-bTemp);
            memset(GSM_RxBuffer,' ',iAddr+1);/*clear old data*/
            
            /*Get SMS Time date inf if required*/
            iAddr = (uint32)strstr(GSM_RxBuffer,"\"\r\n");
            bTemp = iAddr-(uint32)GSM_RxBuffer +3;
            memset(GSM_RxBuffer,' ',bTemp);/*clear old data*/
            
            /*Get SMS message*/
            iAddr = (uint32)strstr(GSM_RxBuffer,"\r\n");
            iAddr = iAddr-(uint32)GSM_RxBuffer;
            memcpy(p_strtSMS->sSMSText,&GSM_RxBuffer[bTemp],iAddr-bTemp+1);
        }
    }
    else
        eATResponseType = eAT_OUT_OF_DATA; 
    
    return eATResponseType;
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSMDeleteSMSByIndex
*Description:   
*Input: None
*Output: enumSMSType
p_strtSMS    pointer to SMS structure
-----------------------------------------------------------------------------*/
enumATResponseType GSM_DeleteSMSByIndex(uint8 bSMSIdx)
{
    enumATResponseType blValue = eAT_NONE_RESP;
    char SmsIdx[3];/*2 digit, max 99 sms*/
    
    if ((bSMSIdx)&&(bSMSIdx<99))
    {
        UnsignIntegerToString(bSMSIdx,SmsIdx);
        GSMSendUartData("AT+CMGD=");
        GSMSendUartData(SmsIdx);
        GSMSendUartData(CR_LF_SYMBOL);
        blValue = GSM_WaitResponse("OK",50);
    }
    else
        blValue = eAT_OUT_OF_DATA;
    
    return blValue;
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSMDeleteSMSByType
*Description:   Delete All sms has same eSMSType
*Input: None
*Output: int8 return -1 : error
0 : None response
>0 : number of sms has been deleted
-----------------------------------------------------------------------------*/
uint8 GSM_DeleteSMSByType(enumSMSType eSMSType)
{
    uint8 bNum = 1;
    char bData[3];
    
    for(bNum=1;bNum<40;bNum++)
    {
        GSM_DeleteSMSByIndex(bNum);
    }
    return  bNum;
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSMDeleteSMSByType
*Description:   Delete All sms has same eSMSType
*Input: None
*Output: int8 return -1 : error
0 : None response
>0 : number of sms has been deleted
-----------------------------------------------------------------------------*/
enumATResponseType GSM_WritePhoneNumber(char* sPhoneNumber, char* sPhoneName)
{
    uint16      bPhoneIdx = 1;
    char        sPhoneIdx[3];
    enumATResponseType eResult = eAT_NONE_RESP;
    
    do{
        UnsignIntegerToString(bPhoneIdx,sPhoneIdx);
        /*Get Phone number*/
        GSMSendUartData("AT+CPBR=");
        GSMSendUartData(sPhoneIdx);
        GSMSendUartData(CR_LF_SYMBOL);
        eResult = GSM_WaitResponse("+CPBR:",50);
        if (eResult==eAT_OK_RESP)
        {/*just response OK*/
            /*Write phone number as format
            AT+CPBW=X,"00420123456789","Name" */
            GSMSendUartData("AT+CPBW=");
            GSMSendUartData(sPhoneIdx);
            GSMSendUartData(",\"");
            GSMSendUartData(sPhoneNumber);
            GSMSendUartData("\"");
            GSMSendUartData(",129,");/*Unknown Type - IDSN format number*/
            GSMSendUartData("\"");
            GSMSendUartData(sPhoneName);
            GSMSendUartData("\"\r");
            eResult = eAT_SUCCESS_RESP;
            break;
        }
    }while (++bPhoneIdx<PHONE_BOOK_SIZE);
    
    GSM_ClearRxBuffer();/*Clear all buffer after*/
    
    return  eResult;
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSM_DeletePhoneBook
*Description:   get phone book from SIm memory
*Input: None
*Output: int8 return -1 : error
0 : None response
>0 : number of sms has been deleted
-----------------------------------------------------------------------------*/
enumATResponseType GSM_DeletePhonenum(structPhoneNumberInfo *pList)
{
    
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSM_WritePhoneBook
*Description:   Write phone book to SIm memory
*Input: None
*Output: int8 return -1 : error
0 : None response
>0 : number of sms has been deleted
-----------------------------------------------------------------------------*/
enumATResponseType GSM_WritePhoneBook(uint8* pNumPhone, structPhoneNumberInfo *pList)
{
    
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSM_GetPhoneBook
*Description:   get phone book from SIm memory
*Input: None
*Output: int8 return -1 : error
0 : None response
>0 : number of sms has been deleted
-----------------------------------------------------------------------------*/
enumATResponseType GSM_GetPhoneBook(uint8 NumPhone, structPhoneNumberInfo *pList)
{
    
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSMSendSMS
*Description:   Check SIM Access
*Input: None
*Output: enumATResponseType     -1      eAT_ERROR_RESP
0       eAT_NONE_RESP
>1      index of Send SMS message                               
-----------------------------------------------------------------------------*/
enumATResponseType GSM_MakeACallByPhone(char* bPhoneNumber)
{
    enumATResponseType blValue = eAT_NONE_RESP;
    
    GSMSendUartData("ATD");
    GSMSendUartData(bPhoneNumber);
    GSMSendUartData(";\r\n");
    
    blValue = GSM_WaitResponse("OK",50);
    
    return blValue;
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSMSendSMS
*Description:   Check SIM Access
*Input: None
*Output: enumATResponseType     -1      eAT_ERROR_RESP
0       eAT_NONE_RESP
>1      index of Send SMS message                               
-----------------------------------------------------------------------------*/
enumATResponseType GSM_HangUpACall(void)
{
    enumATResponseType blValue = eAT_NONE_RESP;
    
    GSMSendUartData("ATH\r\n");
    
    return blValue;
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GSMSendSMS
*Description:   Check SIM Access
*Input: None
*Output: enumATResponseType     -1      eAT_ERROR_RESP
0       eAT_NONE_RESP
>1      index of Send SMS message                               
-----------------------------------------------------------------------------*/
enumATResponseType GSM_SetSpeakerVolume(uint8 Level)
{
    enumATResponseType blValue = eAT_NONE_RESP;
    char cLevel[4];
    
    if (Level>100)      Level= 100;
    
    IntToString(Level,cLevel);
    
    GSMSendUartData("ATL9");
    GSMSendUartData(CR_LF_SYMBOL);
    GSM_WaitResponse("OK",50);
    
    GSMSendUartData("AT+CLVL=");
    GSMSendUartData(cLevel);
    GSMSendUartData(CR_LF_SYMBOL);
    
    blValue = GSM_WaitResponse("OK",50);
    
    return blValue;
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
