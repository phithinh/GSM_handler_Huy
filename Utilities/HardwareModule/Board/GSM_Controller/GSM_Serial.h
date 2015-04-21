#ifndef _GSM_SERIAL_H
#define _GSM_SERIAL_H

typedef enum{
	GSM_STATUS_ON = 0,
	GSM_STATUS_OFF = 1
}GSM_Status_em_tdf;

typedef enum{
    eAT_OUT_OF_DATA = -2,
    eAT_ERROR_RESP = -1,
    eAT_NONE_RESP = 0,
    eAT_OK_RESP = 1,
    eAT_SUCCESS_RESP = 2,
        
}enumATResponseType;

typedef enum{
    eSIM_NOT_PRESENT,
    eSIM_READY, /*Ready for use*/
    eSIM_PIN,   /*Waiting PIN to be given*/
    eSIM_PUK,   /*Waiting for SIM PUK to be given*/
    ePH_SIM_PIN,
    ePH_SIM_PUK,
    eSIM_PIN2,
    eSIM_PUK2,
    
    eSIM_ERROR
}enumSIMPINType;

typedef enum{
    eSMS_UNREAD,        /*SMS unread*/
    eSMS_READ,          /*SMS read*/
    eSMS_STO_UNSENT,    /*SMS storage not sent*/
    eSMS_STO_SENT,      /*SMS sent*/
    
    eSMS_ALL            /*all type SMS*/
}enumSMSType;

typedef enum{
    ePHONE_CONTROL = 1<<0,        /*SMS unread*/
    ePHONE_RECEIVE = 1<<1,
    
}enumPhonePermissionType;

#define PHONE_NUM_SIZE          20
#define SMS_TEXT_SIZE           160
#define GSM_RX_BUFFER_SIZE      SMS_TEXT_SIZE+80
typedef struct _structSMSMessageInfo
{
    uint8               bSMSIdx;        /*Idx of SMS save on SIM*/
    char                sPhoneNumber[PHONE_NUM_SIZE];
    char                sSMSText[SMS_TEXT_SIZE];
}structSMSMessageInfo;

#define LIST_SMS_MAX    20
typedef struct _structListSMS
{
    enumSMSType         eSMSType;
    uint8               bListSmsIdx[LIST_SMS_MAX];
}structListSMS;

#define PHONE_NAME_SIZE  15
#define PHONE_BOOK_SIZE  5
typedef struct _structPhoneNumberInfo
{
    uint8               bPhoneBookIdx; /*Index of Phone number in SIM*/
    char                sPhoneNumber[PHONE_NUM_SIZE];
    char                sPhoneName[PHONE_NAME_SIZE];
}structPhoneNumberInfo;/*Not save on SIM, save on Memory*/

#define USED_GSM_UART



#define CR_SYMBOL               '\r'
#define LF_SYMBOL               '\n'
#define CR_LF_SYMBOL            "\r\n"
#define END_OF_SMS              0x1A /*symbol <CTRL+Z>*/
#define ESC_SYMBOL              0x1B 
        
/*AT */
#define _GsmCheckCommunicate();         GSMSendUartData("AT\r\n");
#define _GsmCheckPIN();                 GSMSendUartData("AT+CPIN?\r\n");
#define _GsmTurnOnEchoMode();           GSMSendUartData("ATE1\r\n");   
#define _GsmTurnOffEchoMode();          GSMSendUartData("ATE0\r\n");
#define _GsmSaveConfig();               GSMSendUartData("AT&W\r\n");
#define _GsmSmsTextMode();              GSMSendUartData("AT+CMGF=1\r\n");
#define _GsmTurnOnOperationMode();      GSMSendUartData("AT+CFUN=1\r\n");

#define _GSMStatusIsOff()               GPIO_ReadInputDataBit(GSM_STATUS_GPIO_PORT,GSM_STATUS_PIN)==GSM_STATUS_OFF


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
#ifdef _GSM_SERIAL_C
static void GSMSendUartData(char* ch);
static void InitRemoveSringFunction(char* p_String, uint8* p_Value);
static void GSM_RemoveSringFunction(enumState eState);
static enumATResponseType GSM_WaitResponse(char* AT_Command, uint16 bTimeOutMax);
static void GSM_ClearRxBuffer(void);

void GSM_Init(void);
void GSM_TurnOn(void);
void GSM_TurnOff(void);
void GSM_Reset(void);

void GSM_NewSMSAlertFunc(enumState eState);
enumbool GSM_GetNewSMS(structSMSMessageInfo* p_strtNewSMS);

enumATResponseType GSM_GetListSMS(enumSMSType eSMSType, structListSMS* p_strtListSms);
enumATResponseType GSM_GetSMSByIdx(uint8 bSMSIdx, structSMSMessageInfo* p_strtSMS);
enumATResponseType GSM_CheckCommunicate(void);
enumATResponseType GSM_SendSMSByPhoneNumber(char* bPhoneNumber, char* bTextString);
enumATResponseType GSM_DeleteSMSByIndex(uint8 bSMSIdx);

uint8 GSM_DeleteSMSByType(enumSMSType eSMSType);
enumATResponseType GSM_WritePhoneNumber(char* sPhoneNumber, char* sPhoneName);

enumATResponseType GSM_DeletePhonenum(structPhoneNumberInfo *pList);
enumATResponseType GSM_WritePhoneBook(uint8* pNumPhone, structPhoneNumberInfo *pList);
enumATResponseType GSM_GetPhoneBook(uint8 NumPhone, structPhoneNumberInfo *pList);

enumATResponseType GSM_MakeACallByPhone(char* bPhoneNumber);
enumATResponseType GSM_HangUpACall(void);
enumATResponseType GSM_SetSpeakerVolume(uint8 Level);
#else
extern void GSM_Init(void);
extern void GSM_TurnOn(void);
extern void GSM_TurnOff(void);
extern void GSM_Reset(void);

extern void GSM_NewSMSAlertFunc(enumState eState);
extern enumbool GSM_GetNewSMS(structSMSMessageInfo* p_strtNewSMS);

extern enumATResponseType GSM_GetListSMS(enumSMSType eSMSType, structListSMS* p_strtListSms);
extern enumATResponseType GSM_GetSMSByIdx(uint8 bSMSIdx, structSMSMessageInfo* p_strtSMS);
extern enumATResponseType GSM_CheckCommunicate(void);
extern enumATResponseType GSM_SendSMSByPhoneNumber(char* bPhoneNumber, char* bTextString);
extern enumATResponseType GSM_DeleteSMSByIndex(uint8 bSMSIdx);

extern uint8 GSM_DeleteSMSByType(enumSMSType eSMSType);
extern enumATResponseType GSM_WritePhoneNumber(char* sPhoneNumber, char* sPhoneName);

extern enumATResponseType GSM_DeletePhonenum(structPhoneNumberInfo *pList);
extern enumATResponseType GSM_WritePhoneBook(uint8* pNumPhone, structPhoneNumberInfo *pList);
extern enumATResponseType GSM_GetPhoneBook(uint8 NumPhone, structPhoneNumberInfo *pList);

extern enumATResponseType GSM_MakeACallByPhone(char* bPhoneNumber);
extern enumATResponseType GSM_HangUpACall(void);
extern enumATResponseType GSM_SetSpeakerVolume(uint8 Level);
#endif

void GSM_IRQHANDLER(unsigned char p_data_ub);
enumSIMPINType GSM_CheckSIMOrReady(void);
#endif /* _GSM_SERIAL_H */  


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
