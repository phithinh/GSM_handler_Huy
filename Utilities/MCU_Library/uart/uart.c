
//#include <compiler.h>
#include "../../serial_com/serial_com_adapt.h"
#include <stm32f10x.h>
#include <stm32f10x_usart.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <misc.h>

#include "uart_cfg.h"
#include "uart_pub.h"

#define COM_RX_INT


USART_TypeDef* COM_USART[COMn] = {USART_COM1, USART_COM2, USART_COM3}; 

GPIO_TypeDef* COM_TX_PORT[COMn] = {USART_COM1_TX_GPIO_PORT, USART_COM2_TX_GPIO_PORT, USART_COM3_TX_GPIO_PORT};
 
GPIO_TypeDef* COM_RX_PORT[COMn] = {USART_COM1_RX_GPIO_PORT, USART_COM2_RX_GPIO_PORT, USART_COM3_RX_GPIO_PORT};
 
const ULONG COM_USART_CLK[COMn] = {USART_COM1_CLK, USART_COM2_CLK, USART_COM3_CLK};

const ULONG COM_TX_PORT_CLK[COMn] = {USART_COM1_TX_GPIO_CLK, USART_COM2_TX_GPIO_CLK, USART_COM3_TX_GPIO_CLK};
 
const ULONG COM_RX_PORT_CLK[COMn] = {USART_COM1_RX_GPIO_CLK, USART_COM2_RX_GPIO_CLK, USART_COM3_RX_GPIO_CLK};

const UWORD COM_TX_PIN[COMn] = {USART_COM1_TX_PIN, USART_COM2_TX_PIN, USART_COM3_TX_PIN};

const UWORD COM_RX_PIN[COMn] = {USART_COM1_RX_PIN, USART_COM2_RX_PIN, USART_COM3_RX_PIN};

const ULONG COM_IRQn[COMn] = { USART1_IRQn, USART2_IRQn, USART3_IRQn};

//**
//  * @brief  Configures COM port.
//  * @param  COM: Specifies the COM port to be configured.
//  *   This parameter can be one of following parameters:    
//  *     @arg COM1
//  *     @arg COM2  
//  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure that
//  *   contains the configuration information for the specified USART peripheral.
//  * @retval None
//  *
void USART_COMInit_v(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd(COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM] | RCC_APB2Periph_AFIO, ENABLE);

  /* Enable UART clock */
  if (COM == COM1)
  {
    RCC_APB2PeriphClockCmd(COM_USART_CLK[COM], ENABLE); 
  }
  else
  {
    RCC_APB1PeriphClockCmd(COM_USART_CLK[COM], ENABLE);
  }

  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[COM];
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStructure);

  /* Configure USART Rx as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];
  GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStructure);
  /* USART configuration */
  USART_Init(COM_USART[COM], USART_InitStruct);

#ifdef COM_RX_INT
	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = COM_IRQn[COM];
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable USARTz Receive and Transmit interrupts */
	USART_ITConfig(COM_USART[COM], USART_IT_RXNE, ENABLE);
#endif
	/* Enable USART */
	USART_Cmd(COM_USART[COM], ENABLE);
}


void USART_init_v(void)
{
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 19200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_COMInit_v(COM_SELECT_ID, &USART_InitStructure);
}
