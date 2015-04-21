#ifndef UART_PUB_H_
#define UART_PUB_H_

#include <stm32f10x.h>
#include <stm32f10x_usart.h>

typedef struct{
	void (* RX_indication)(unsigned char p_data);
}UART_HW_CONFIG_ST_DEF;
typedef enum 
{
  COM1 = 0,
  COM2 = 1,
  COM3 = 2
} COM_TypeDef;   
/**
 * @brief Definition for COM port1, connected to USART1
 */
#define USART_COM1					USART1
#define USART_COM1_CLK				RCC_APB2Periph_USART1
#define USART_COM1_TX_PIN			GPIO_Pin_9
#define USART_COM1_TX_GPIO_PORT		GPIOA
#define USART_COM1_TX_GPIO_CLK		RCC_APB2Periph_GPIOA
#define USART_COM1_RX_PIN			GPIO_Pin_10
#define USART_COM1_RX_GPIO_PORT		GPIOA
#define USART_COM1_RX_GPIO_CLK		RCC_APB2Periph_GPIOA
#define USART_COM1_IRQn				USART1_IRQn

/**
 * @brief Definition for COM port2, connected to USART2
 */
#define USART_COM2					USART2
#define USART_COM2_CLK				RCC_APB1Periph_USART2
#define USART_COM2_TX_PIN			GPIO_Pin_2
#define USART_COM2_TX_GPIO_PORT		GPIOA
#define USART_COM2_TX_GPIO_CLK		RCC_APB2Periph_GPIOA
#define USART_COM2_RX_PIN			GPIO_Pin_3
#define USART_COM2_RX_GPIO_PORT		GPIOA
#define USART_COM2_RX_GPIO_CLK		RCC_APB2Periph_GPIOA
#define USART_COM2_IRQn				USART2_IRQn

/**
 * @brief Definition for COM port3, connected to USART2
 */
#define USART_COM3					USART3
#define USART_COM3_CLK				RCC_APB1Periph_USART3
#define USART_COM3_TX_PIN			GPIO_Pin_10
#define USART_COM3_TX_GPIO_PORT		GPIOB
#define USART_COM3_TX_GPIO_CLK		RCC_APB2Periph_GPIOB
#define USART_COM3_RX_PIN			GPIO_Pin_11
#define USART_COM3_RX_GPIO_PORT		GPIOB
#define USART_COM3_RX_GPIO_CLK		RCC_APB2Periph_GPIOB
#define USART_COM3_IRQn				USART3_IRQn

void USART_init_v(void);
void USART_COMInit_v(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct);
#endif

