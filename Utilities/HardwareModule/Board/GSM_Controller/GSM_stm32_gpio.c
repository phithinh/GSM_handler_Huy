/*
 * GSM_stm32_gpio.c
 *
 *  Created on: Mar 28, 2015
 *      Author: phi thinh
 */

//#include <general_define.h>
//#include <digital_out_pub.h>
//#include <digital_in_pub.h>
#include <PlatFormType.h>
#include "GSM_stm32_gpio.h"
#include "../SIM900/SIM900.h"

BOOL GSM_GetStatusPort_b(void){
//	return digital_in_read(GSM_STATUS_PORT);
	return SIM900_RING_IND_STATUS;
}
void GSM_SetResetPort_v(BOOL p_state_b){
//	digital_out_set_v(GSM_RESET_PORT, p_state_b);
	if (p_state_b){
		SIM900_NRESET_ON;
	} else {
		SIM900_NRESET_OFF;
	}
}
void GSM_SetOnOffPort_v(BOOL p_state_b){
//	digital_out_set_v(GSM_ONOFF_PORT, p_state_b);
	if (p_state_b){
		SIM900_PWRKEY_ON;
	} else {
		SIM900_PWRKEY_OFF;
	}

}
