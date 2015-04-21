#ifndef	__IO__
#define __IO__
#include "stm32f10x.h"
//#include "PlatFormType.h"
#include "../../../../Source/Project/Common.h"
#define LED1_PIN                   GPIO_Pin_15  
#define LED1_PORT                  GPIOA
#define LED1_RCC_ENABLE            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE)
#define LED1_MODE	           GPIO_Mode_Out_PP  
#define LED1_ON                    LED1_PORT->BSRR = LED1_PIN
#define LED1_OFF                   LED1_PORT->BRR = LED1_PIN
#define LED1_TOG	           LED1_PORT->ODR ^= LED1_PIN


#define LED2_PIN                   GPIO_Pin_3  
#define LED2_PORT                  GPIOB
#define LED2_RCC_ENABLE            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE)
#define LED2_MODE			GPIO_Mode_Out_PP  
#define LED2_ON                    LED2_PORT->BSRR = LED2_PIN
#define LED2_OFF                   LED2_PORT->BRR = LED2_PIN
#define LED2_TOG	             LED2_PORT->ODR ^= LED2_PIN


#define LED3_PIN                   GPIO_Pin_4  
#define LED3_PORT                  GPIOB
#define LED3_RCC_ENABLE            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE)
#define LED3_MODE			GPIO_Mode_Out_PP  
#define LED3_ON                    LED3_PORT->BSRR = LED3_PIN
#define LED3_OFF                   LED3_PORT->BRR = LED3_PIN
#define LED3_TOG	             LED3_PORT->ODR ^= LED3_PIN

void Init_IO (void);

#endif
