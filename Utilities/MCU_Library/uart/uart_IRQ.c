/*
 * uart_IRQ.c
 *
 *  Created on: Nov 5, 2014
 *      Author: Phi Thinh
 */
//interrupt handler

//#include <compiler.h>
#include "../../serial_com/serial_com_adapt.h"
#include <stm32f10x.h>
#include <stm32f10x_usart.h>
#include "uart_cfg.h"
#include "uart_pub.h"
void USART2_IRQHandler(void);
extern UART_HW_CONFIG_ST_DEF uart_Hw_Cofig_st;

//void USART1_IRQHandler(void)
//{
//	UBYTE t_data_ub;
//	if(USART_GetITStatus(COM_SELECT_BASE, USART_IT_RXNE) != RESET){
//		//the uart rx handler will be called at here
//		t_data_ub = (UBYTE)USART_ReceiveData(COM_SELECT_BASE);
//		(uart_Hw_Cofig_st.RX_indication)(t_data_ub);
//	}
//}
void USART2_IRQHandler(void)
{
	UBYTE t_data_ub;
	if(USART_GetITStatus(COM_SELECT_BASE, USART_IT_RXNE) != RESET){
		//the uart rx handler will be called at here
		t_data_ub = (UBYTE)USART_ReceiveData(COM_SELECT_BASE);
		(uart_Hw_Cofig_st.RX_indication)(t_data_ub);
	}
}
