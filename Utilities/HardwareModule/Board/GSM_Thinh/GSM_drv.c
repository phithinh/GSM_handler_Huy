#define GSM_DRV
#include "GSM_adapt.h"

#include "GSM_drv.h"
#include "string_user.h"

////////////////////////////////////////////////// ////////////////

const unsigned char CharacterArray[] = { '0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
//unsigned int GSM_SpecificState;
GSM_data GSM_Rx;
Msg_send Msg_send_data;
char GSM_SerialBusy_b = 0;

char Master_phone[14] = "+84906558678";
char Master_phone2[12] = "0906558678";
//char pass_word[4];
const char GSM_PassDefault[] = "1234";
const char GSM_PhoneNDefault[] = "0906558678";
const char SMS_rx[] = { '+', 'C', 'M', 'T', 'I', ':', ' ', '"', 'S', 'M', '"' };
const char RING[] = { 'R', 'I', 'N', 'G' };


/*
 * Calling the init for gsm controller module
 * */
void GSM_Init_v(void){
	GSM_MCU_Drv_Init();
	Msg_send_reset();
	Call_data_reset();
	SMS_data_reset();
	GSM_reset_default();
	delay_ms(300);
}


void GSM_InitSIM(void) {
	GSM_PutROM("ATZ\r\0");
	Command_return_Process();
	GSM_PutROM("ATE0\r\0");
	Command_return_Process();
	GSM_PutROM("AT+CLIP=1\r\0");
	Command_return_Process();
	GSM_PutROM("AT&W\r\0");
	Command_return_Process();
	GSM_PutROM("AT+CMGF=1\r\0");
	Command_return_Process();
	GSM_PutROM("AT+CNMI=2,1,0,0,0\r\0");
	Command_return_Process();
	GSM_PutROM("AT+CSAS\r\0");
	Command_return_Process();
}

void GSM_MCU_Drv_Init(void) {
	//
	//initiation powerkey port
	//use Port A8 
//	GSM_PowerKey_Init_v();

	//
	//GSM state init
	//
	GSM_SpecificState = GSM_STATE_DEFAULT;
	GSM_Rx.buf_ptr = GSM_Rx.Data;
	Call_Rx.pointer = Call_Rx.phone_nums;
	SMS_Received.Data_ptr = SMS_Received.Data;
	SMS_Received.Phone_nums_ptr = SMS_Received.Phone_nums;
	//
	//usart init
	GSM_Serial_Init_v();
}
unsigned char Power_up_GSM(void) {
	unsigned short retry;
	do {
		GSM_reset_default();
		PWRKEY_ON;
		delay_ms(10);
		PWRKEY_OFF;
		delay_ms(3500);
		PWRKEY_ON;
		retry = 0;
		do {
			retry++;
			delay_ms(10);
			if (retry > 100)
				break;
		} while (!GSM_Get_default_data());

	} while (String_cmp(GSM_Get_default_data(), "RDY\0") != 1);
	return 0;	//power up successfull
}

void GSM_AThandle(void) {
	char u8aTmp[2];
	u8aTmp[1] = 0;
	if (GSM_Rx.Data_rdy == 1) {
		switch (GSM_SpecificState) {
		case GSM_STATE_DEFAULT:
			if (String_cmp(GSM_Rx.Data, "RING\0")) {
                GSM_PutROM("AT+CLCC\r\0");
				GSM_StaMachine_df_to_getting_call_v();
			} else if (String_cmp(GSM_Rx.Data, "+CMTI")) {
				SMS_Received.Sim_Mem_idx = GSM_Rx.Data[12];
				GSM_PutROM("AT+CMGR=\0");	//OK ko co Mess
				u8aTmp[0] = SMS_Received.Sim_Mem_idx;
				GSM_PutROM(u8aTmp);
				u8aTmp[0] = 0x0D;
				GSM_PutROM(u8aTmp);

				GSM_StaMachine_df_to_sms_read_v();
			} else if (String_cmp(GSM_Rx.Data, "RDY\0")) {
				GSM_SerialBusy_b = 0;
			} else if (String_cmp(GSM_Rx.Data, "+CUSD")) {
				GSM_account_checking_v();
				GSM_reset();
			}
			break;
		case GSM_STATE_SMS_READ:
			if (String_cmp(GSM_Rx.Data, "+CMGR")) {
				GSM_SMSphone();
			} else if (String_cmp(GSM_Rx.Data, "OK")) {
				SMS_Received.SMS_finished = 1;
				GSM_StaMachine_sms_read_to_df_v();
			//} else if (String_cmp(GSM_Rx.Data, "AT+CMGR")) {

				//Todo: unknown
			//} else if (String_cmp(GSM_Rx.Data, "AT+CMGD")) {

				//Todo: unknown
			} else {
				Str_copy(GSM_Rx.Data, SMS_Received.Data);
			}
			break;
		}
		GSM_Rx.buf_ptr = GSM_Rx.Data;
		GSM_Rx.Data_start = 0;
		GSM_Rx.Data_rdy = 0;
		GSM_Rx.Data_cnt = 0;
	}
}

void GSM_IRQ_Handler(unsigned char p_data_ub) {
	if ((GSM_SpecificState == GSM_STATE_DEFAULT) || (GSM_SpecificState == GSM_STATE_SMS_READ)) {
		switch (p_data_ub) {
		case 0x0A: { //\n
			GSM_Rx.LF_cnt++;
			GSM_SerialBusy_b = 0;
			//if (GSM_Rx.Data_start == 0 && GSM_Rx.Data_rdy == 0) {
				//GSM_Rx.Data_start = 1;
				//return;
			//}
			break;
		}
		case 0x0D:
			if (GSM_Rx.Data_start == 1 && GSM_Rx.Data_rdy == 0) {
				*GSM_Rx.buf_ptr = '\0';
				if (GSM_Rx.Data_cnt != 0) {
					GSM_Rx.Data_start = 0;
					GSM_Rx.Data_rdy = 1;
					GSM_SerialBusy_b = 0;	//Todo: receiving is done Thinh 09 April 2015
				}
			}
			GSM_SerialBusy_b = 1;
			return;
		default:
			//if (GSM_Rx.Data_start == 1 && GSM_Rx.Data_rdy == 0) {
				GSM_Rx.Data_cnt++;
				*GSM_Rx.buf_ptr = p_data_ub;
				GSM_Rx.buf_ptr++;
			//}
			GSM_Rx.Data_start = 1;
			GSM_SerialBusy_b = 1;
			break;
		}
		GSM_AThandle();
	} // end GSM default status, temp = 'LF' at this moment
	else if (GSM_SpecificState == GSM_STATE_CALL) //processing for the furture interrupt
	{
		if (p_data_ub == 0x0A && Call_Rx.Start_frame == 0) {
			Call_Rx.pointer = Call_Rx.phone_nums;
			Call_Rx.Start_frame = 1;
			return;
		} else if (p_data_ub == 0x0A && Call_Rx.Start_frame == 1) {
			Call_Rx.Start_frame = 0;
			Call_Rx.Ringing = 1;
			GSM_SerialBusy_b = 0;
			//ConsolePutROMString("ATH\r\0");
			GSM_StaMachine_getting_call_to_df_v();
			return;
		}
		if (Call_Rx.Start_frame == 1) {
			if (p_data_ub == '"') {
				Call_Rx.qoute_cnt++;
				return;
			}
			if (Call_Rx.qoute_cnt == 1) {
				*Call_Rx.pointer = p_data_ub;
				Call_Rx.pointer++;
				return;
			} else if (Call_Rx.qoute_cnt >= 2) {
				return;
			}
		}
	} else if (GSM_SpecificState == GSM_STATE_SMS_SEND) {
		switch (p_data_ub) {
		case 0x0A:
			Msg_send_data.LF_cnt++;
           // if (String_N_cmp("ERROR", Msg_send_data.data_return,5)){
             //   Msg_send_data.response_er_indicate = 1;
           // } else 
              if (Msg_send_data.LF_cnt == 5){
				Msg_send_data.send_finish = 1;
            }
            
            //Msg_send_data.data_ptr=Msg_send_data.data_return;
            //Array_reset(Msg_send_data.data_return);
			break;
		case 0x0D:
			break;
		case ' ':
			break;
		case '>':
			Msg_send_data.send_rdy = 1;
			break;
		default:
			if (Msg_send_data.send_finish == 0) {
				*Msg_send_data.data_ptr = p_data_ub;
				Msg_send_data.data_ptr++;
                
                if (String_N_cmp("ERROR", Msg_send_data.data_return,5)){
                  Msg_send_data.response_er_indicate = 1;
                }
			}
			break;
		}
		return;
	}
	return;
}

/****************************************************************************************/
/*
 Function Name:	GSM_WaitUART(void)
 Decription:		Wait for UART is ready, return 1
 If time out return 0
 */
/****************************************************************************************/
char GSM_WaitUART(void) {
	unsigned int i = 0;
	do {
		i++;
		if (GSM_SerialBusy_b == 0)
			return (1);	//UART driver is ready
		delay_ms(10);
	} while (i < 50);
	return (0);	//time out
}
/****************************************************************************************/
/*
 Function Name:	GSM_WaitSendReady(void)
 Decription:		Wait for Module Sim releses that can send message, return 1
 If time out return 0
 */
/****************************************************************************************/
char GSM_WaitSendReady(void) {
	unsigned int i = 0;
	do {
		i++;
		if (Msg_send_rdy_status() == 1)
			return (1);	// can send message
		delay_ms(10);
	} while (i < 50);
	return (0);	//time out
}
/****************************************************************************************/
/*
 Function Name:	GSM_WaitSendFinish(void)
 Decription:		Wait for sending is finish, return 1
 If time out return 0
 */
/****************************************************************************************/
char GSM_WaitSendFinish(void) {
	unsigned int i = 0;
	do {
		i++;
		if ((Msg_send_finish() == 1)||(Msg_send_data.response_er_indicate))
			return (1);	// message is send
		delay_ms(10);
	} while (i < 50);
	return (0);	//time out
}
char GSM_STATE_DEFAULT_Status_ck(char* status) {
//	char temp=0;
	unsigned long timeout;
	while (GSM_Get_default_data() == 0) {
		timeout++;
		delay_ms(10);
		if (timeout > 200)
			return (0x0F);
	}
	return (String_cmp(GSM_Get_default_data(), status));
}
void Command_return_Process(void) {
	switch (GSM_STATE_DEFAULT_Status_ck("OK\0")) {
	case 1: {
		GSM_reset_default();
		return;
	}
	case 0: {
		GSM_reset_default();
		//GLCD_Print57(7,50,"NotOKcmd\0");
		return;
	}
	case 0x0F: {
		GSM_reset_default();
		//GLCD_Print57(7,50,"Timeout\0");
		return;
	}
	}
}
void SMS_Delete(char mem_index) {
	char u8aTmp[2];
	GSM_PutROM("AT+CMGD=\0");
	u8aTmp[0] = mem_index;
	u8aTmp[1] = 0;
	GSM_PutROM(u8aTmp);
	u8aTmp[0] = 0x0D;	//<CR>
	GSM_PutROM(u8aTmp);
	Command_return_Process();
}

void SMS_Delete_all(void) {
	//GSM_PutROM("AT+CMGD=\"ALL\"\r");
	GSM_PutROM("AT+CMGD=1,4\r");
	Command_return_Process();
}
void GSM_SMSphone(void) {
	u8 i, j;
	i = 0;
	j = 0;
	while (i < 3) {
		if (GSM_Rx.Data[j++] == '"')
			i++;
	}
	for (i = 0; GSM_Rx.Data[j + i] != '"'; i++) {
		SMS_Received.Phone_nums[i] = GSM_Rx.Data[j + i];
	}
}
void SMS_Sending(char* sdt, char* msg) {
	char u8aTmp[2];
    unsigned char t_retry_ub=0;
	u8aTmp[1] = 0;
	if (GSM_WaitUART()&& (GSM_STATE_DEFAULT == GSM_SpecificState)) {
        do{
            GSM_StaMachine_df_to_sms_send_v();

            GSM_PutROM("AT+CMGS=\0");

            u8aTmp[0] = (0x22);	//"
            GSM_PutROM(u8aTmp);
            GSM_PutROM(sdt);
            u8aTmp[0] = (0x22);	//"
            GSM_PutROM(u8aTmp);

            u8aTmp[0] = (0x0D);	//"
            GSM_PutROM(u8aTmp);

            if (GSM_WaitSendReady()) {
                GSM_PutROM(msg); //send message
                u8aTmp[0] = 0x1A; //ESC
                GSM_PutROM(u8aTmp);
            }
            (void) GSM_WaitSendFinish();
            t_retry_ub++;
        }while((Msg_send_data.response_er_indicate)&& (t_retry_ub<5));
        GSM_StaMachine_sms_send_to_df_v();
	}
}

void GSM_PutROM(char* x) {
	//
	GSM_SerialSend_v(x);
}

//----------------------------------------------------------------------------------------------
char* GSM_Get_default_data(void) {
	if (GSM_SpecificState == GSM_STATE_DEFAULT && GSM_Rx.Data_rdy == 1
			&& GSM_SerialBusy_b == 0) //default buff data ready
		return (GSM_Rx.Data);
	else
		return (0);
}
void GSM_set_status(unsigned int status) {
	GSM_SpecificState = status;
}
char Msg_send_rdy_status(void) {
	return (Msg_send_data.send_rdy);
}
char Msg_send_finish(void) {
	return (Msg_send_data.send_finish);
}
char* Msg_sent_data_get(void) {
	if (Msg_send_data.send_finish == 0)
		return (0);
	else {
		return (Msg_send_data.data_return);
	}
}
char* SMS_msg_get(char data) {
	if (SMS_Received.SMS_finished) {
		switch (data) {
		case MSG_data :
			return (SMS_Received.Data);
		case MSG_nums :
			return (SMS_Received.Phone_nums);
		case MSG_mem_idx :
			return (&(SMS_Received.Sim_Mem_idx));
		default:
			break;
		}
	}
	return (0);
}
char* GSM_STATE_CALL_getdata(void) {
	if (Call_Rx.Ringing)
		return (Call_Rx.phone_nums);
	else
		return (0);
}
void GSM_account_checking_v(void){
	unsigned char t_index_ub=0;
	unsigned char t_char_ub = 0;
	unsigned char t_start_char_index_ub;
	while (t_char_ub!='"'){
		t_char_ub = GSM_Rx.Data[t_index_ub++];
		if(t_char_ub == '\r') return;
	}
	t_start_char_index_ub = t_index_ub;

	t_char_ub = GSM_Rx.Data[t_index_ub];
	while (t_char_ub!='"'){
		t_char_ub = GSM_Rx.Data[++t_index_ub];
		if(t_char_ub == '\r') return;
	}
	account_checking_st.lenght_ub = t_index_ub - t_start_char_index_ub;
	Str_N_copy((char *)&GSM_Rx.Data[t_start_char_index_ub], (char *)account_checking_st.account_checking_res_sb, account_checking_st.lenght_ub);
	account_checking_st.rx_indication_ub = 1;
}
unsigned char GSM_account_checking_trigger_v(void){
	if ((GSM_SpecificState == GSM_STATE_DEFAULT)&&(GSM_SerialBusy_b == 0)){
		GSM_PutROM("ATD*101#;\r\n");
		return 1;
	}
	return 0;
}
//-------------------------------------------------------------------------------------------
void GSM_StaMachine_df_to_sms_send_v(void){
	if (GSM_STATE_DEFAULT == GSM_SpecificState){
		GSM_SpecificState = GSM_STATE_SMS_SEND;
		GSM_reset();
		Msg_send_reset();
	} else {
		GSM_SpecificState = GSM_STATE_DEFAULT;
		GSM_reset();
		SMS_data_reset();
		Msg_send_reset();
		Call_data_reset();
	}
}
void GSM_StaMachine_sms_send_to_df_v(void){
	if (GSM_STATE_SMS_SEND == GSM_SpecificState){
		GSM_SpecificState = GSM_STATE_DEFAULT;
		GSM_reset();
		Msg_send_reset();
	} else {
		GSM_SpecificState = GSM_STATE_DEFAULT;
		GSM_reset();
		SMS_data_reset();
		Msg_send_reset();
		Call_data_reset();
	}
}

void GSM_StaMachine_df_to_sms_read_v(void){
	if (GSM_STATE_DEFAULT == GSM_SpecificState){
		GSM_SpecificState = GSM_STATE_SMS_READ;
		GSM_reset();
		SMS_data_reset();
	} else {
		GSM_SpecificState = GSM_STATE_DEFAULT;
		GSM_reset();
		SMS_data_reset();
		Msg_send_reset();
		Call_data_reset();
	}
}

void GSM_StaMachine_sms_read_to_df_v(void){
	if (GSM_STATE_SMS_READ == GSM_SpecificState){
		GSM_SpecificState = GSM_STATE_DEFAULT;
		GSM_reset();
	} else {
		GSM_SpecificState = GSM_STATE_DEFAULT;
		GSM_reset();
		SMS_data_reset();
		Msg_send_reset();
		Call_data_reset();
	}
}

void GSM_StaMachine_df_to_getting_call_v(void){
	if (GSM_STATE_DEFAULT == GSM_SpecificState){
		GSM_SpecificState = GSM_STATE_CALL;
		GSM_reset();
		Call_data_reset();
	} else {
		GSM_SpecificState = GSM_STATE_DEFAULT;
		GSM_reset();
		SMS_data_reset();
		Msg_send_reset();
		Call_data_reset();
	}
}

void GSM_StaMachine_getting_call_to_df_v(void){
	if (GSM_STATE_CALL == GSM_SpecificState){
		GSM_SpecificState = GSM_STATE_DEFAULT;
		GSM_reset();
	} else {
		GSM_SpecificState = GSM_STATE_DEFAULT;
		GSM_reset();
		SMS_data_reset();
		Msg_send_reset();
		Call_data_reset();
	}
}
//-------------------------------------------------------------------------------------------
void SMS_data_reset(void) {
	SMS_Received.LF_cnt = 0;
	SMS_Received.SMS_finished = 0;
	SMS_Received.qoute_cnt = 0;
	SMS_Received.Sim_Mem_idx = 0;
	SMS_Received.Data_ptr = SMS_Received.Data;
	SMS_Received.Phone_nums_ptr = SMS_Received.Phone_nums;
	Array_reset(SMS_Received.Data);
	Array_reset(SMS_Received.Phone_nums);
}

void Msg_send_reset(void) {
	Msg_send_data.data_ptr = Msg_send_data.data_return;
	Msg_send_data.LF_cnt = 0;
	Msg_send_data.send_rdy = 0;
	Msg_send_data.send_finish = 0;
    Msg_send_data.response_er_indicate = 0;
	Array_reset(Msg_send_data.data_return);
}
void Call_data_reset(void) {
	Call_Rx.qoute_cnt = 0;
	Call_Rx.Ringing = 0;
	Call_Rx.Start_frame = 0;
	Call_Rx.pointer = Call_Rx.phone_nums;
	Array_reset(Call_Rx.phone_nums);
}

void GSM_reset_default(void) {
	GSM_SpecificState = GSM_STATE_DEFAULT;
	GSM_Rx.buf_ptr = GSM_Rx.Data;
	GSM_Rx.Data_cnt = 0;
	GSM_Rx.LF_cnt = 0;
	GSM_Rx.Data_rdy = 0;
    GSM_SerialBusy_b = 0;
}
void GSM_reset(void) {
	GSM_Rx.buf_ptr = GSM_Rx.Data;
	GSM_Rx.Data_cnt = 0;
	GSM_Rx.LF_cnt = 0;
	GSM_Rx.Data_rdy = 0;
    GSM_SerialBusy_b = 0;
}
