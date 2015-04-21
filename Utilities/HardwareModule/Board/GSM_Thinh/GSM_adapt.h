/*
 * GSM_adapt.h
 *
 *  Created on: Apr 6, 2015
 *      Author: phi thinh
 */

#ifndef GSM_ADAPT_H_
#define GSM_ADAPT_H_

#include "../SIM900/SIM900.h"
#include "../IO/IO.h"
#define PWRKEY_ON SIM900_PWRKEY_ON
#define PWRKEY_OFF SIM900_PWRKEY_OFF

#define GSM_Serial_Init_v()	SIM900_Init()

#define delay_ms(ms)	DelayMs(ms)


#define GSM_SerialSend_v(char_pt)	printf(char_pt)
#endif /* GSM_ADAPT_H_ */
