/*
 * GSM_stm32f_SerialCom.h
 *
 *  Created on: Mar 28, 2015
 *      Author: phi thinh
 */

#ifndef GSM_STM32F_SERIALCOM_H_
#define GSM_STM32F_SERIALCOM_H_


void GSM_SerialCom_Init_v(void);
BOOL GSM_SerialCom_RxEmpty_b(void);
void GSM_SerialCom_SendData_v(UBYTE p_ch_ub[]);
BOOL GSM_SerialCom_GetTxFree_b(void);

#endif /* GSM_STM32F_SERIALCOM_H_ */
