/*
 * serial_com.h
 *
 *  Created on: Apr 28, 2014
 *      Author: TV
 *  Description:
 *  		declaration of API function of serial communacation
 */

#ifndef SERIAL_COM_H_
#define SERIAL_COM_H_

#define COM_SERIAL_SPEC_CHAR_START	('<')
#define COM_SERIAL_SPEC_CHAR_END	('>')


#define COM_SERIAL_RX_TIME_OUT	1000 //100ms
#define COM_SERIAL_TX_TIME_OUT	1000

#define SERIAL_COM_MAX_RX_BF		50
#define SERIAL_COM_MAX_TX_BF		50

extern signed long T1Us_Tick1Ms;
#define tick_count	T1Us_Tick1Ms

#ifdef SERIAL_COM_APPL

struct {
	signed long timerstamp;
	unsigned char data_ub[SERIAL_COM_MAX_RX_BF];
	unsigned char sent_index_ub;
	unsigned char error_flag_ub;
	unsigned char done_flag_ub;
}serial_com_receiving_context_st;
struct {
	signed long timerstamp;
	unsigned char data_ub[SERIAL_COM_MAX_TX_BF];
	unsigned char sent_index_ub;
	unsigned char sent_length_ub;
	unsigned char error_flag_ub;
}serial_com_sending_context_st;

unsigned short l_serial_com_requested_relay_uw;
unsigned char l_serial_com_requested_relay_flag_b;


enum{
	SERIAL_COM_STATE_UNINIT = 0,
	SERIAL_COM_STATE_IDLE,
	SERIAL_COM_STATE_RECEIVING,
	SERIAL_COM_STATE_SENDING,
}serial_com_state;

//local function
void serial_com_sm_receiving_idle_v(void);
void serial_com_sm_sending_idle_v(void);
void serial_com_sm_idle_receiving_v(void);
void serial_com_sm_idle_sending_v(void);
void serial_com_sm_goto_idle_v(void);
#else
extern struct {
	signed long timerstamp;
	unsigned char data_ub[SERIAL_COM_MAX_RX_BF];
	unsigned char sent_index_ub;
	unsigned char error_flag_ub;
	unsigned char done_flag_ub;
}serial_com_receiving_context_st;
extern struct {
	signed long timerstamp;
	unsigned char data_ub[SERIAL_COM_MAX_TX_BF];
	unsigned char sent_index_ub;
	unsigned char sent_length_ub;
	unsigned char error_flag_ub;
}serial_com_sending_context_st;

extern unsigned short l_serial_com_requested_relay_uw;
extern unsigned char l_serial_com_requested_relay_flag_b;
#endif

void serial_com_init_v(void);
void serial_com_main(void);
void serial_com_send_v(unsigned char lenght, char * p_ch_ub);

void serial_com_isrq_hanlder(unsigned char p_data_ub);
#undef SERIAL_COM_APPL
#endif /* SERIAL_COM_APPL_H_ */

