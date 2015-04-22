/*
 * GSM_app.c
 *
 *  Created on: Apr 7, 2015
 *      Author: phi thinh
 */
#include "GSM_drv.h"
#include "../../../serial_com/serial_com.h"

#include "string_user.h"
#include "GSM_app.h"
#include "../IO/IO.h"
#include "../../../FlashRW/FlashRW.h"
#include "../../../MemoryMap.h"

unsigned char GSM_mater2_phone_ub[1024];
//const char GSM_master_defaut_phone_ub[] = "+841283573315";
const char GSM_master_defaut_phone_ub[] = "+84906558678";


#define RELAY_SMS_OFFSET	6
#define RELAY_COM_OFFSET	2
#define GSM_WAITING_THRO	10000
unsigned char l_set_phone_flag = 0, l_account_checking_trigger = 0;
signed long l_delay_time_set_phone = 0;
signed long l_gsm_busy_counter = 0;
unsigned char gsm_appl_request_ub[21];

void GSM_app_init(void){
	  GSM_Init_v();
	  GSM_InitPhone();
}
void GSM_app_main(void){
	GSM_AThandle();
	SMS_Get_proc();
	GSM_STATE_CALL_proc();

    /* There is issue when handle GSM, it can't response after receive immediately, hence
     * the timer is set to delay 3s before sending response
     * */
    if (l_set_phone_flag){
      if ((T1Us_Tick1Ms- l_delay_time_set_phone)>3000){
        SMS_Sending((char *)GSM_master_defaut_phone_ub, "setting phone number is done");
		GSM_WritePhoneN();
        l_set_phone_flag = 0;
      }
    }

    /*
     * Checking busy flag
     * 	- Due to there is a bug in GSM driver, this code to make sure the GSM is always available
     * 	- If the busy gsm flag is set during 5 seconds, gsm will be reset
     *
     * */
    if(GSM_WaitUART() && (GSM_STATE_DEFAULT== GSM_SpecificState )){
    	l_gsm_busy_counter = T1Us_Tick1Ms;
    } else {
    	if ((T1Us_Tick1Ms - l_gsm_busy_counter)>GSM_WAITING_THRO){
            Msg_send_reset();
            Call_data_reset();
            SMS_data_reset();
            GSM_reset_default();
            SMS_Delete_all();
            GSM_app_init();
    	}
    }

    /*
     * account checking
     *
     * */
    if (l_account_checking_trigger){
    	if ((T1Us_Tick1Ms - l_delay_time_set_phone)>1000){
    		if(GSM_account_checking_trigger_v()){
    			l_account_checking_trigger = 0;
    		}
    	}
    }
    if (account_checking_st.rx_indication_ub){
    	account_checking_st.rx_indication_ub = 0;
    	GSM_Send_SMS_v((unsigned char *)account_checking_st.account_checking_res_sb);
    }
}
/*
 *  - This method shall be polled at infinitive loop
 *  - It will be called when a sms which was come from GSM module
 *  - This method shall check the content of message
 *  	1. message = "relay x x...x" x means the number of relay which
 *  	are requested to on, this method will send this request to serial port 2
 *  	to relay board, with the content as below:
 *  	"<r xxxxxxxxxxxxxxxx>" x means the status of 16 relays (1 on, 0 off)
 *  	e.g.: message = "r 2 5"  means that it requests relay 2 and 5 on
 *  	relay board request will be as "<r 0100100000000000>"
 *
 *  	2. message = "status", should send a request "<s>" to relay board to get
 *  	current status
 *  	3. message = "phone +84xxxxxxxxxx", request to store the new master number,
 *  	"pppp" is pin number, "xxxxxxxxxx" is phone number
 *  	4. message = "cancel", request to suppress relay control
 *
 *
 * */

extern signed long T1Us_Tick1Ms;
void SMS_Get_proc(void) {
	char* data_ptr;
	char* nums_ptr;
    char t_char_ub;
	unsigned char t_index_ub;
	unsigned char t_set_relay_ub;
	unsigned char *t_ms_char_pub;

	if (SMS_Received.SMS_finished) {
		unsigned char t_Sim_Mem_idx_ub;
		if (GSM_WaitUART()) {
			t_Sim_Mem_idx_ub = SMS_Received.Sim_Mem_idx;
			data_ptr = SMS_Received.Data;
			nums_ptr = SMS_Received.Phone_nums;
			//validating phone number
			if( (String_cmp(nums_ptr, (char*)GSM_master_defaut_phone_ub))||(String_cmp(nums_ptr, (char *)GSM_mater2_phone_ub))){

				if ((String_N_cmp(data_ptr, "relay",5))||(String_N_cmp(data_ptr, "Relay",5))){
					gsm_appl_request_ub[0] = '<';
					gsm_appl_request_ub[1] = 'r';
					gsm_appl_request_ub[2] = ' ';
					gsm_appl_request_ub[19] = '>';
					gsm_appl_request_ub[20] = 0;

					//clear all relay status
					for(t_index_ub = 3; t_index_ub<19; t_index_ub++){
						gsm_appl_request_ub[t_index_ub] = '0';
					}
					//read the relay status from coming message

					// !This code will search the requested relay in the message content
					// and update to frame request which is sent to relay board
					t_set_relay_ub = 0;
					t_ms_char_pub = (unsigned char *)data_ptr + RELAY_SMS_OFFSET;
					do {
                      LED2_ON;//Huy
						if((' ' == *t_ms_char_pub)||(*t_ms_char_pub==0)){
							if ((t_set_relay_ub<=16)&&(t_set_relay_ub>0)){
								gsm_appl_request_ub[t_set_relay_ub+RELAY_COM_OFFSET] = '1';
							}
							t_set_relay_ub = 0;
						} else {
							if(t_set_relay_ub!=0){
								t_set_relay_ub*=10;	//shift 1 dec
							}
							t_set_relay_ub += *t_ms_char_pub - '0';
						}
					}while (*(t_ms_char_pub++)!=0);
                    LED2_OFF;//Huy
					//send relay request
					serial_com_send_v(20,(char*)gsm_appl_request_ub);

				} else if ((String_N_cmp(data_ptr, "status",6))||(String_N_cmp(data_ptr, "Status",6))){
					gsm_appl_request_ub[0] = '<';
					gsm_appl_request_ub[1] = 's';
					gsm_appl_request_ub[2] = '>';
					//send relay request
					serial_com_send_v(3,(char*)gsm_appl_request_ub);
				} else if ((String_N_cmp(data_ptr, "phone",5))||((String_N_cmp(data_ptr, "Phone",5)))){
					for(t_index_ub = 0; t_index_ub<14; t_index_ub++){
                        t_char_ub = *(data_ptr+6+t_index_ub);
                        if((t_char_ub != '+')&& (!((t_char_ub>='0')&&(t_char_ub<='9')))){
                            GSM_mater2_phone_ub[t_index_ub] = 0;
                            break;
                        }else {
                            GSM_mater2_phone_ub[t_index_ub] = t_char_ub;
                        }
					}
                    l_set_phone_flag = 1; //to inform that it is done
                    l_delay_time_set_phone = T1Us_Tick1Ms;
				} else if ((String_N_cmp(data_ptr, "cancel",6))||((String_N_cmp(data_ptr, "Cancel",6)))){
					serial_com_send_v(3,"<c>");
				} else if (String_N_cmp(data_ptr, "*101#",5)){
					l_account_checking_trigger = 1;
                    l_delay_time_set_phone = T1Us_Tick1Ms;
				} else {

				}
			}
		}
		//SMS_Delete (t_Sim_Mem_idx_ub);
		SMS_Delete_all();
		SMS_data_reset();
	}
}

void GSM_STATE_CALL_proc(void) {
	if (Call_Rx.Ringing) {
		if (GSM_WaitUART()) {
			GSM_PutROM("ATH\r\0");
			Command_return_Process();
			if ((String_cmp(Call_Rx.phone_nums+1, (char*)GSM_master_defaut_phone_ub+3))||(String_cmp(Call_Rx.phone_nums+1, (char *)GSM_mater2_phone_ub+3))) {
				serial_com_send_v(3,"<s>");
            }
			Call_data_reset();
		}
	}
}
void GSM_Send_SMS_v(unsigned char *p_datap_pub){
	//validating the master phone nummber
	if (String_cmp((char *)GSM_mater2_phone_ub,"+84")){
		SMS_Sending((char *)GSM_mater2_phone_ub, (char *)p_datap_pub);
	}else{
		SMS_Sending((char *)GSM_master_defaut_phone_ub, (char *)p_datap_pub);
	}
}

/*	*
 * @Function Name:	 GSM_InitPhone()
 * @Decription:		Load new phone number into Master phone
 *				if config-key is put down, reset password and phone number
 */
void GSM_InitPhone(void) {
	memcpy(GSM_mater2_phone_ub,(uint32*)FW_DECRIP_START_ADDR,1024);
}
/*	*
 * @Function Name:	 GSM_WirtePhoneN()
 * @Decription:		Load new phone number into Master phone
 *				max 10byte
 */
void GSM_WritePhoneN(void) {
	//save into EEPROM
	SaveSysParameter((SYS_PARAMETER*)GSM_mater2_phone_ub,0);
}
