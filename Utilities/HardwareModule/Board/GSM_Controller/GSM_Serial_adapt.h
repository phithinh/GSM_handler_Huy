/*
 * GSM_Serial_adapt.h
 *
 *  Created on: Apr 4, 2015
 *      Author: phi thinh
 */

#ifndef GSM_SERIAL_ADAPT_H_
#define GSM_SERIAL_ADAPT_H_

#define GSM_SerialCom_Init_v()	SIM900_Init()//SIM900_Init_McuDriver()

//#ifndef uint8
//#define uint8 unsigned char
//#endif


#define GSM_SerialCom_RxEmpty_b()					(USART_GetITStatus(SIM900_USART, USART_IT_RXNE) != RESET)


#define GSM_SerialCom_SendData_v(p_ch_ub)			USART_SendData(SIM900_USART,  p_ch_ub)
#define GSM_SerialCom_GetTxFree_b()					USART_GetFlagStatus(SIM900_USART, USART_FLAG_TC)


#endif /* GSM_SERIAL_ADAPT_H_ */
