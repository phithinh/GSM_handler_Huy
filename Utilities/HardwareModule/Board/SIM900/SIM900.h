#ifndef	__SIM900__
#define	__SIM900__
#include "stm32f10x.h"
//#include "PlatFormType.h"
#include <Common.h>
#include "../board.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>   
#include "../serial_debug/serial_debug.h"
#include "../IO/IO.h"


#define SIM900_CTRL_PIN                   GPIO_Pin_6  
#define SIM900_CTRL_PORT                  GPIOA
#define SIM900_CTRL_RCC_ENABLE            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE)
#define SIM900_CTRL_MODE			GPIO_Mode_Out_OD  
#define SIM900_CTRL_OFF                    SIM900_CTRL_PORT->BSRR = SIM900_CTRL_PIN
#define SIM900_CTRL_ON                   SIM900_CTRL_PORT->BRR = SIM900_CTRL_PIN     //External HW on module
#define SIM900_CTRL_TOG	                 SIM900_CTRL_PORT->ODR ^= SIM900_CTRL_PIN


#define SIM900_PWRKEY_PIN                   GPIO_Pin_0  
#define SIM900_PWRKEY_PORT                  GPIOB
#define SIM900_PWRKEY_RCC_ENABLE            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE)
#define SIM900_PWRKEY_MODE			GPIO_Mode_Out_PP  
#define SIM900_PWRKEY_ON                    SIM900_PWRKEY_PORT->BSRR = SIM900_PWRKEY_PIN//ON 1s for POWER ON module
#define SIM900_PWRKEY_OFF                   SIM900_PWRKEY_PORT->BRR = SIM900_PWRKEY_PIN
#define SIM900_PWRKEY_TOG	                 SIM900_PWRKEY_PORT->ODR ^= SIM900_PWRKEY_PIN


#define SIM900_NRESET_PIN                   GPIO_Pin_1  
#define SIM900_NRESET_PORT                  GPIOB
#define SIM900_NRESET_RCC_ENABLE            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE)
#define SIM900_NRESET_MODE			GPIO_Mode_Out_PP  
#define SIM900_NRESET_ON                    SIM900_NRESET_PORT->BSRR = SIM900_NRESET_PIN//Reset active
#define SIM900_NRESET_OFF                   SIM900_NRESET_PORT->BRR = SIM900_NRESET_PIN
#define SIM900_NRESET_TOG	             SIM900_NRESET_PORT->ODR ^= SIM900_NRESET_PIN

#define SIM900_DTR_PIN                   GPIO_Pin_8  
#define SIM900_DTR_PORT                  GPIOA
#define SIM900_DTR_RCC_ENABLE            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE)
#define SIM900_DTR_MODE			GPIO_Mode_Out_PP  
#define SIM900_DTR_ON                    SIM900_DTR_PORT->BSRR = SIM900_DTR_PIN
#define SIM900_DTR_OFF                   SIM900_DTR_PORT->BRR = SIM900_DTR_PIN
#define SIM900_DTR_TOG	             SIM900_DTR_PORT->ODR ^= SIM900_DTR_PIN


#define SIM900_RING_IND_PIN                    GPIO_Pin_7
#define SIM900_RING_IND_PORT                   GPIOA
#define	SIM900_RING_IND_MODE		    GPIO_Mode_IPU
#define SIM900_RING_IND_RCC_ENABLE             RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE)       
#define SIM900_RING_IND_STATUS                 GPIO_ReadInputDataBit(SIM900_RING_IND_PORT,SIM900_RING_IND_PIN)

#define SIM900_TX_PIN                   GPIO_Pin_9
#define SIM900_TX_PORT                  GPIOA
#define SIM900_TX_RCC_ENABLE            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE)
#define SIM900_TX_MODE	                GPIO_Mode_AF_PP

#define SIM900_RX_PIN                    GPIO_Pin_5
#define SIM900_RX_PORT                   GPIOB
#define	SIM900_RX_MODE		        GPIO_Mode_IN_FLOATING
#define SIM900_RX_RCC_ENABLE             RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE)       


#define SIM900_USART                       USART1
#define SIM900_USART_RCC_ENABLE            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE)
#define SIM900_BAUD                        9600
#define SIM900_IRQn                      USART1_IRQn
#define SIM900_IRQHandler                USART1_IRQHandler



void SIM900_Init(void);
void SIM900_Init_McuDriver(void);
void SIM900_PWR_ON(void);
void SIM900_NRESET (void);
void SIM900_IRQHandler(void);
uint8 SIM900_Check_AT_Cmd(void);
void SIM900_Buffer_Reset(void);
uint8 SIM900_AT_Rei_Check_CMD(char tmp[],uint8 SizeOftmp,uint8 PosBuffer);
void SIM900_Send_SMS(char NumberPhone[],char Mess[]);
#endif
/////////////////////////////////////////////////////

