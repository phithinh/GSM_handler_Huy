
#ifndef	__GSM_DRV_H
#define __GSM_DRV_H
#include "stdio.h"
//#define 	PWRKEY	PAout(0)

#ifdef GSM_DRV
enum{
	GSM_STATE_DEFAULT = 1,
	GSM_STATE_SMS_SEND	 ,
	GSM_STATE_CALL		 ,
	GSM_STATE_SMS_READ	 ,
}GSM_SpecificState;
#else
extern enum{
	GSM_STATE_DEFAULT = 1,
	GSM_STATE_SMS_SEND	 ,
	GSM_STATE_CALL		 ,
	GSM_STATE_SMS_READ	 ,
}GSM_SpecificState;
#endif

#define 	MSG_data		(char)(0)
#define		MSG_nums		(char)(1)
#define		MSG_mem_idx		(char)(3)

typedef struct
{
	char Header[3];
	char Offset_time[2];
	char Cylinder1[2];
	char Cylinder2[2];
	char Cylinder3[2];
	char CRC_mes;
}UART_Message;
typedef struct
{
	char Data[512];
	char Data_start;
	char Data_cnt;
	char LF_cnt;
	char Data_rdy; 
	char *buf_ptr;
}GSM_data;
typedef struct
{
	char phone_nums[14];
	char *pointer;
	char Ringing;
	char qoute_cnt;
	char Start_frame;
}Call_income;
typedef struct
{
	char Sim_Mem_idx;//positsion of message in sim memmory
	char Data[512];
	char *Data_ptr;
	char Phone_nums[14];
	char *Phone_nums_ptr;
	char SMS_finished;
	char qoute_cnt;
	char LF_cnt;
}SMS_Rx;
typedef struct
{
	char LF_cnt;
	char send_rdy;
	char data_return[32];
	char* data_ptr;
	char send_finish;
    unsigned char response_er_indicate;
}Msg_send;

void GSM_Init_v(void);
void GSM_InitSIM(void);
void GSM_MCU_Drv_Init(void);
unsigned char Power_up_GSM(void);
void GSM_reset_default(void) ;
//void GSM_WritePhoneN(char* pn);
//void GSM_WritePass(char* pass);
void GSM_AThandle(void);
void GSM_IRQ_Handler(unsigned char p_data_ub) ;
char GSM_WaitUART(void);
char GSM_WaitSendReady(void);
char GSM_WaitSendFinish(void);
char GSM_STATE_DEFAULT_Status_ck(char* status);
void Command_return_Process(void);
void SMS_Delete(char mem_index);
void SMS_Delete_all(void);
void GSM_SMSphone(void);
void SMS_Sending(char* sdt, char* msg);
void GSM_PutROM(char* x);
char* GSM_Get_default_data(void);
void GSM_set_status(unsigned int status);
void Call_data_reset(void);
char Msg_send_rdy_status(void);
char Msg_send_finish(void);
char* Msg_sent_data_get(void);
void Msg_send_reset(void);
void SMS_data_reset(void);
char* SMS_msg_get(char data);
char* GSM_STATE_CALL_getdata(void);

void GSM_StaMachine_df_to_sms_send_v(void);
void GSM_StaMachine_sms_send_to_df_v(void);
void GSM_StaMachine_df_to_sms_read_v(void);
void GSM_StaMachine_sms_read_to_df_v(void);
void GSM_StaMachine_df_to_getting_call_v(void);
void GSM_StaMachine_getting_call_to_df_v(void);
void GSM_reset(void);

#ifdef GSM_DRV
Call_income Call_Rx;
SMS_Rx SMS_Received;
#else
extern Call_income Call_Rx;
extern SMS_Rx SMS_Received;
#endif

#endif

