#ifndef	__GSM_APP_H
#define	__GSM_APP_H
void GSM_app_init(void);
void GSM_app_main(void);
void SMS_Get_proc(void);
void GSM_STATE_CALL_proc(void);

void GSM_InitPhone(void);
void GSM_WritePhoneN(void);
void GSM_Send_SMS_v(unsigned char *p_datap_pub);
#endif
