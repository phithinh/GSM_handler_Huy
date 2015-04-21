/*
 * GSM_stm32f_SerialCom.c
 *
 *  Created on: Mar 28, 2015
 *      Author: phi thinh
 */

#include <general_define.h>
#include <GSM_stm32f_SerialCom_cfg.h>
#include <GSM_stm32f_SerialCom.h>

#include <uart_pub.h>

void GSM_SerialCom_Init_v(void){
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	void USART_COMInit_v(GSM_UART, &USART_InitStruct);
}
BOOL GSM_SerialCom_RxEmpty_b(void){
	return (USART_GetITStatus(GSM_COM_UART, USART_IT_RXNE) != RESET);
}

void GSM_SerialCom_SendData_v(UBYTE p_ch_ub[]){
	USART_SendData(GSM_COM_UART, (uint8_t) p_ch_ub);
}
BOOL GSM_SerialCom_GetTxFree_b(void){
	return USART_GetFlagStatus(GSM_COM_UART, USART_FLAG_TC);
}
