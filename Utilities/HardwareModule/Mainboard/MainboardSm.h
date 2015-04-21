/**
******************************************************************************
* @file    stm324xg_eval.h
* @author  MCD Application Team
* @version V1.0.0
* @date    30-September-2011
* @brief   This file contains definitions for STM324xG_EVAL's Leds, push-buttons
*          and COM ports hardware resources.
******************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
******************************************************************************  
*/ 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAINBOARDSM_H
#define __MAINBOARDSM_H

/* Includes ------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#ifdef STM32F4XX
#include "stm32f4xx.h"
#elif STM32F10X_MD
#include "stm32f10x.h"
#endif

#include "PlatFormType.h"
#include "Common.h"

/*type enum for GPIO*/
typedef enum 
{
    USER_LED1 = 1<<0,
    USER_LED2 = 1<<1,
    USER_LED3 = 1<<2,
    
    USER_LED_ALL = 0x7F,
} Led_TypeDef;


typedef enum 
{
    USER_USART1 = 0,
    USER_USART2 = 1,
    USER_USART3 = 2,
} USER_USART_TypeDef;

typedef enum 
{
    USER_SPI1 = 0,
    USER_SPI2 = 1,
} USER_SPI_TypeDef;

#ifdef STM32F4XX
/* Define led pins -----------------------------------------------------------*/
#define LEDn                             3
#define LED1_PIN                         GPIO_Pin_0
#define LED1_GPIO_PORT                   GPIOB
#define LED1_GPIO_CLK                    RCC_AHB1Periph_GPIOB  

#define LED2_PIN                         GPIO_Pin_1
#define LED2_GPIO_PORT                   GPIOB
#define LED2_GPIO_CLK                    RCC_AHB1Periph_GPIOB  

#define LED3_PIN                         GPIO_Pin_5
#define LED3_GPIO_PORT                   GPIOB
#define LED3_GPIO_CLK                    RCC_AHB1Periph_GPIOB  
#else
#ifdef STM_64PIN        /*Define for Hardware Use STM32F103 64pins*/
/* Define led pins -----------------------------------------------------------*/
#define LEDn                             3
#define LED1_PIN                         GPIO_Pin_0
#define LED1_GPIO_PORT                   GPIOB
#define LED1_GPIO_CLK                    RCC_APB2Periph_GPIOB  

#define LED2_PIN                         GPIO_Pin_1
#define LED2_GPIO_PORT                   GPIOB
#define LED2_GPIO_CLK                    RCC_APB2Periph_GPIOB  

#define LED3_PIN                         GPIO_Pin_2
#define LED3_GPIO_PORT                   GPIOB
#define LED3_GPIO_CLK                    RCC_APB2Periph_GPIOB  

#else
#define LEDn                             3
#define LED1_PIN                         GPIO_Pin_5
#define LED1_GPIO_PORT                   GPIOB
#define LED1_GPIO_CLK                    RCC_APB2Periph_GPIOB  

#define LED2_PIN                         GPIO_Pin_6
#define LED2_GPIO_PORT                   GPIOB
#define LED2_GPIO_CLK                    RCC_APB2Periph_GPIOB  

#define LED3_PIN                         GPIO_Pin_7
#define LED3_GPIO_PORT                   GPIOB
#define LED3_GPIO_CLK                    RCC_APB2Periph_GPIOB  
#endif
#endif
/* Define Usart pins ---------------------------------------------------------*/ 
#define COMn                             3

#ifdef STM32F4XX
/*define Usart 1 pins*/  
#define USER_USART1_MODULE                 USART1
#define USER_USART1_CLK                    RCC_APB2Periph_USART1
#define USER_USART1_TX_PIN                 GPIO_Pin_9
#define USER_USART1_TX_GPIO_PORT           GPIOA
#define USER_USART1_TX_GPIO_CLK            RCC_AHB1Periph_GPIOA
#define USER_USART1_TX_SOURCE              GPIO_PinSource9
#define USER_USART1_TX_AF                  GPIO_AF_USART1
#define USER_USART1_RX_PIN                 GPIO_Pin_10
#define USER_USART1_RX_GPIO_PORT           GPIOA
#define USER_USART1_RX_GPIO_CLK            RCC_AHB1Periph_GPIOA
#define USER_USART1_RX_SOURCE              GPIO_PinSource10
#define USER_USART1_RX_AF                  GPIO_AF_USART1
#define USER_USART1_IRQn                   USART1_IRQn

/*define Usart 2 pins*/  
#define USER_USART2_MODULE                 USART2
#define USER_USART2_CLK                    RCC_APB1Periph_USART2
#define USER_USART2_TX_PIN                 GPIO_Pin_2
#define USER_USART2_TX_GPIO_PORT           GPIOA
#define USER_USART2_TX_GPIO_CLK            RCC_AHB1Periph_GPIOA
#define USER_USART2_TX_SOURCE              GPIO_PinSource2
#define USER_USART2_TX_AF                  GPIO_AF_USART2
#define USER_USART2_RX_PIN                 GPIO_Pin_3
#define USER_USART2_RX_GPIO_PORT           GPIOA
#define USER_USART2_RX_GPIO_CLK            RCC_AHB1Periph_GPIOA
#define USER_USART2_RX_SOURCE              GPIO_PinSource3
#define USER_USART2_RX_AF                  GPIO_AF_USART2
#define USER_USART2_IRQn                   USART2_IRQn

/*define Usart 3 pins*/  
#define USER_USART3_MODULE                 USART3
#define USER_USART3_CLK                    RCC_APB1Periph_USART3
#define USER_USART3_TX_PIN                 GPIO_Pin_10
#define USER_USART3_TX_GPIO_PORT           GPIOB
#define USER_USART3_TX_GPIO_CLK            RCC_AHB1Periph_GPIOB
#define USER_USART3_TX_SOURCE              GPIO_PinSource10
#define USER_USART3_TX_AF                  GPIO_AF_USART3
#define USER_USART3_RX_PIN                 GPIO_Pin_11
#define USER_USART3_RX_GPIO_PORT           GPIOB
#define USER_USART3_RX_GPIO_CLK            RCC_AHB1Periph_GPIOB
#define USER_USART3_RX_SOURCE              GPIO_PinSource11
#define USER_USART3_RX_AF                  GPIO_AF_USART3
#define USER_USART3_IRQn                   USART3_IRQn

#else   /*For STM32F1xx*/
/*define Usart 1 pins*/  
#define USER_USART1_MODULE                 USART1
#define USER_USART1_CLK                    RCC_APB2Periph_USART1
#define USER_USART1_TX_PIN                 GPIO_Pin_9
#define USER_USART1_TX_GPIO_PORT           GPIOA
#define USER_USART1_TX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define USER_USART1_TX_SOURCE              GPIO_PinSource9
#define USER_USART1_TX_AF                  GPIO_Remap_USART1
#define USER_USART1_RX_PIN                 GPIO_Pin_10
#define USER_USART1_RX_GPIO_PORT           GPIOA
#define USER_USART1_RX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define USER_USART1_RX_SOURCE              GPIO_PinSource10
#define USER_USART1_RX_AF                  GPIO_Remap_USART1
#define USER_USART1_IRQn                   USART1_IRQn

/*define Usart 2 pins*/  
#define USER_USART2_MODULE                 USART2
#define USER_USART2_CLK                    RCC_APB1Periph_USART2
#define USER_USART2_TX_PIN                 GPIO_Pin_2
#define USER_USART2_TX_GPIO_PORT           GPIOA
#define USER_USART2_TX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define USER_USART2_TX_SOURCE              GPIO_PinSource2
#define USER_USART2_TX_AF                  GPIO_Remap_USART2
#define USER_USART2_RX_PIN                 GPIO_Pin_3
#define USER_USART2_RX_GPIO_PORT           GPIOA
#define USER_USART2_RX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define USER_USART2_RX_SOURCE              GPIO_PinSource3
#define USER_USART2_RX_AF                  GPIO_Remap_USART2
#define USER_USART2_IRQn                   USART2_IRQn

/*define Usart 3 pins*/  
#define USER_USART3_MODULE                 USART3
#define USER_USART3_CLK                    RCC_APB1Periph_USART3
#define USER_USART3_TX_PIN                 GPIO_Pin_10
#define USER_USART3_TX_GPIO_PORT           GPIOB
#define USER_USART3_TX_GPIO_CLK            RCC_APB2Periph_GPIOB
#define USER_USART3_TX_SOURCE              GPIO_PinSource10
#define USER_USART3_TX_AF                  GPIO_FullRemap_USART3
#define USER_USART3_RX_PIN                 GPIO_Pin_11
#define USER_USART3_RX_GPIO_PORT           GPIOB
#define USER_USART3_RX_GPIO_CLK            RCC_APB2Periph_GPIOB
#define USER_USART3_RX_SOURCE              GPIO_PinSource11
#define USER_USART3_RX_AF                  GPIO_FullRemap_USART3
#define USER_USART3_IRQn                   USART3_IRQn

#endif


/* Define SPI Interface ------------------------------------------------------*/ 
#define SPIn                          2
extern SPI_TypeDef* COM_SPI[SPIn];

#ifdef STM32F4XX
/*Define SPI1 Module +++++++++++++++++++++++++++++++++++++++++++*/
#define USER_SPI1_MODULE              SPI1
#define USER_SPI1_CLK                 RCC_APB2Periph_SPI1          
#define USER_SPI1_AF                  GPIO_AF_SPI1

#define USER_SPI1_SCK_CLK             RCC_AHB1Periph_GPIOA
#define USER_SPI1_SCK_PIN             GPIO_Pin_5
#define USER_SPI1_SCK_PORT            GPIOA
#define USER_SPI1_SCK_SOURCE          GPIO_PinSource5

#define USER_SPI1_MISO_CLK            RCC_AHB1Periph_GPIOA
#define USER_SPI1_MISO_PIN            GPIO_Pin_6
#define USER_SPI1_MISO_PORT           GPIOA
#define USER_SPI1_MISO_SOURCE         GPIO_PinSource6

#define USER_SPI1_MOSI_CLK            RCC_AHB1Periph_GPIOA
#define USER_SPI1_MOSI_PIN            GPIO_Pin_7
#define USER_SPI1_MOSI_PORT           GPIOA
#define USER_SPI1_MOSI_SOURCE         GPIO_PinSource7

#define USER_SPI1_CS0_CLK             RCC_AHB1Periph_GPIOA
#define USER_SPI1_CS0_PIN             GPIO_Pin_4
#define USER_SPI1_CS0_PORT            GPIOA

/*Define SPI2 Module +++++++++++++++++++++++++++++++++++++++++++*/
#define USER_SPI2_MODULE              SPI2
#define USER_SPI2_CLK                 RCC_APB1Periph_SPI2
#define USER_SPI2_AF                  GPIO_AF_SPI2

#define USER_SPI2_SCK_CLK             RCC_AHB1Periph_GPIOB
#define USER_SPI2_SCK_PIN             GPIO_Pin_13
#define USER_SPI2_SCK_PORT            GPIOB
#define USER_SPI2_SCK_SOURCE          GPIO_PinSource13

#define USER_SPI2_MISO_CLK            RCC_AHB1Periph_GPIOB
#define USER_SPI2_MISO_PIN            GPIO_Pin_14
#define USER_SPI2_MISO_PORT           GPIOB
#define USER_SPI2_MISO_SOURCE         GPIO_PinSource14

#define USER_SPI2_MOSI_CLK            RCC_AHB1Periph_GPIOB
#define USER_SPI2_MOSI_PIN            GPIO_Pin_15
#define USER_SPI2_MOSI_PORT           GPIOB
#define USER_SPI2_MOSI_SOURCE         GPIO_PinSource15

#define USER_SPI2_CS0_CLK             RCC_AHB1Periph_GPIOB
#define USER_SPI2_CS0_PIN             GPIO_Pin_12
#define USER_SPI2_CS0_PORT            GPIOB

#else   /*For STM32F1xx*/

/*Define SPI1 Module +++++++++++++++++++++++++++++++++++++++++++*/
#define USER_SPI1_MODULE              SPI1
#define USER_SPI1_CLK                 RCC_APB2Periph_SPI1          
#define USER_SPI1_AF                  GPIO_Remap_SPI1

#define USER_SPI1_SCK_CLK             RCC_APB2Periph_GPIOA
#define USER_SPI1_SCK_PIN             GPIO_Pin_5
#define USER_SPI1_SCK_PORT            GPIOA
#define USER_SPI1_SCK_SOURCE          GPIO_PinSource5

#define USER_SPI1_MISO_CLK            RCC_APB2Periph_GPIOA
#define USER_SPI1_MISO_PIN            GPIO_Pin_6
#define USER_SPI1_MISO_PORT           GPIOA
#define USER_SPI1_MISO_SOURCE         GPIO_PinSource6

#define USER_SPI1_MOSI_CLK            RCC_APB2Periph_GPIOA
#define USER_SPI1_MOSI_PIN            GPIO_Pin_7
#define USER_SPI1_MOSI_PORT           GPIOA
#define USER_SPI1_MOSI_SOURCE         GPIO_PinSource7

#define USER_SPI1_CS0_CLK             RCC_APB2Periph_GPIOA
#define USER_SPI1_CS0_PIN             GPIO_Pin_4
#define USER_SPI1_CS0_PORT            GPIOA

/*Define SPI2 Module +++++++++++++++++++++++++++++++++++++++++++*/
#define USER_SPI2_MODULE              SPI2
#define USER_SPI2_CLK                 RCC_APB1Periph_SPI2
#define USER_SPI2_AF                  GPIO_Remap_SPI1

#define USER_SPI2_SCK_CLK             RCC_APB2Periph_GPIOB
#define USER_SPI2_SCK_PIN             GPIO_Pin_13
#define USER_SPI2_SCK_PORT            GPIOB
#define USER_SPI2_SCK_SOURCE          GPIO_PinSource13

#define USER_SPI2_MISO_CLK            RCC_APB2Periph_GPIOB
#define USER_SPI2_MISO_PIN            GPIO_Pin_14
#define USER_SPI2_MISO_PORT           GPIOB
#define USER_SPI2_MISO_SOURCE         GPIO_PinSource14

#define USER_SPI2_MOSI_CLK            RCC_APB2Periph_GPIOB
#define USER_SPI2_MOSI_PIN            GPIO_Pin_15
#define USER_SPI2_MOSI_PORT           GPIOB
#define USER_SPI2_MOSI_SOURCE         GPIO_PinSource15

#define USER_SPI2_CS0_CLK             RCC_APB2Periph_GPIOB
#define USER_SPI2_CS0_PIN             GPIO_Pin_12
#define USER_SPI2_CS0_PORT            GPIOB
#endif

/* Define hardware config for RF Module --------------------------------------*/
#define SPI_RF_MODULE                   USER_SPI1
#define RfSpiStructureInit              UserSpi1StructureInit

#define nrf24l01_CSN_IOPORT     	USER_SPI1_CS0_PORT
#define nrf24l01_CSN_IOPIN		USER_SPI1_CS0_PIN
#define nrf24l01_CSN_CLOCK              USER_SPI1_CS0_CLK

#ifdef STM32F4XX
#define nrf24l01_CE_IOPORT		GPIOA
#define nrf24l01_CE_IOPIN	        GPIO_Pin_0
#define nrf24l01_CE_CLOCK               RCC_AHB1Periph_GPIOA

#define nrf24l01_IRQ_IOPORT		GPIOA
#define nrf24l01_IRQ_IOPIN		GPIO_Pin_1
#define nrf24l01_IRQ_CLOCK              RCC_AHB1Periph_GPIOA
#define nrf24l01_IRQ_EXTI_LINE          EXTI_Line1
#define nrf24l01_IRQ_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOA
#define nrf24l01_IRQ_EXTI_PIN_SOURCE    EXTI_PinSource1
#define nrf24l01_IRQ_EXTI_IRQn          EXTI1_IRQn 

#else
#ifdef STM_64PIN        /*Define for Hardware Use STM32F103 64pins*/
#define nrf24l01_CE_IOPORT		GPIOA
#define nrf24l01_CE_IOPIN	        GPIO_Pin_0
#define nrf24l01_CE_CLOCK               RCC_APB2Periph_GPIOA

#define nrf24l01_IRQ_IOPORT		GPIOA
#define nrf24l01_IRQ_IOPIN		GPIO_Pin_1
#define nrf24l01_IRQ_CLOCK              RCC_APB2Periph_GPIOA
#define nrf24l01_IRQ_EXTI_LINE          EXTI_Line1
#define nrf24l01_IRQ_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOA
#define nrf24l01_IRQ_EXTI_PIN_SOURCE    EXTI_PinSource1
#define nrf24l01_IRQ_EXTI_IRQn          EXTI1_IRQn
#else
#define nrf24l01_CE_IOPORT		GPIOB
#define nrf24l01_CE_IOPIN	        GPIO_Pin_0
#define nrf24l01_CE_CLOCK               RCC_APB2Periph_GPIOB

#define nrf24l01_IRQ_IOPORT		GPIOB
#define nrf24l01_IRQ_IOPIN		GPIO_Pin_1
#define nrf24l01_IRQ_CLOCK              RCC_APB2Periph_GPIOB
#define nrf24l01_IRQ_EXTI_LINE          EXTI_Line1
#define nrf24l01_IRQ_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOB
#define nrf24l01_IRQ_EXTI_PIN_SOURCE    EXTI_PinSource1
#define nrf24l01_IRQ_EXTI_IRQn          EXTI1_IRQn
#endif
#endif
/*-------------------- Declare for RTC Driver --------------------------------*/
/*Defaut value for time, date..*/
#define mDEFAULT_SEC    0
#define mDEFAULT_MIN    0
#define mDEFAULT_HOUR   0

#define mDEFAULT_DAY            18
#define mDEFAULT_WEEK           RTC_Weekday_Thursday
#define mDEFAULT_MONTH          RTC_Month_October
#define mDEFAULT_YEAR           12      /*Thursday 18 October 2012*/

/*-------------------- Declare for Timer Functions ---------------------------*/
#define TIMER_BASE_1US                  TIM3
#define TIMER_BASE_1US_CLK              RCC_APB1Periph_TIM3
#define TIMER_BASE_1US_IRQ              TIM3_IRQn
#define TimerBase1UsIrqHandler          TIM3_IRQHandler

/*-------------------- Declare for irDA Functions ---------------------------*/
        /*irDA Timer Delay*/
#define TIMER_IrDA_DELAY_CLK            RCC_APB1Periph_TIM2
#define TIMER_IrDA_DELAY                TIM2



#ifdef STM32F4XX
#define USER_IRDA_OUTPUT_GPIO_CLK       RCC_AHB1Periph_GPIOA
#define USER_IRDA_OUTPUT_PIN            GPIO_Pin_2
#define USER_IRDA_OUTPUT_GPIO_PORT      GPIOA

/*Macro for latch Output*/
#define IRDA_LED_OFF                    USER_IRDA_OUTPUT_GPIO_PORT->BSRRH = USER_IRDA_OUTPUT_PIN
#define IRDA_LED_ON                     USER_IRDA_OUTPUT_GPIO_PORT->BSRRL = USER_IRDA_OUTPUT_PIN
#else

#define USER_IRDA_OUTPUT_GPIO_CLK       RCC_APB2Periph_GPIOA
#define USER_IRDA_OUTPUT_PIN            GPIO_Pin_2
#define USER_IRDA_OUTPUT_GPIO_PORT      GPIOA

/*Macro for latch Output*/
#define IRDA_LED_OFF                    USER_IRDA_OUTPUT_GPIO_PORT->BSRR = USER_IRDA_OUTPUT_PIN
#define IRDA_LED_ON                     USER_IRDA_OUTPUT_GPIO_PORT->BRR = USER_IRDA_OUTPUT_PIN
#endif

#ifdef STM32F4XX
#define USER_IRDA_INPUT_GPIO_CLK        RCC_AHB1Periph_GPIOA
#define USER_IRDA_INPUT_PIN             GPIO_Pin_3
#define USER_IRDA_INPUT_GPIO_PORT       GPIOA

#define IRDA_USART_MODULE               USART2
#define IRDA_USART_CLK                  RCC_APB1Periph_USART2
#define IRDA_USART_RX_SOURCE            GPIO_PinSource3
#define IRDA_USART_RX_AF                GPIO_AF_USART2
#define IRDA_USART_IRQn                 USART2_IRQn

#else
#define USER_IRDA_INPUT_GPIO_CLK        RCC_APB2Periph_GPIOA
#define USER_IRDA_INPUT_PIN             GPIO_Pin_3
#define USER_IRDA_INPUT_GPIO_PORT       GPIOA

#define IRDA_USART_MODULE               USART2
#define IRDA_USART_CLK                  RCC_APB1Periph_USART2
#define IRDA_USART_RX_SOURCE            GPIO_PinSource3
#define IRDA_USART_RX_AF                GPIO_AF_USART2
#define IRDA_USART_IRQn                 USART2_IRQn
#endif

/*-------------------- Declare for Key In IO pins ----------------------------*/
typedef enum _enumKeyIn{
    eKEY_IN1 = 0,
    eKEY_IN2 = 1,
    eKEY_IN3 = 2,
    eNONE_KEY  = 0xFF,
}enumKeyIn;
typedef enum _enumIOValue
{
    eIOVal_ON_TO_OFF,
    eIOVal_OFF_TO_ON,
    eIOVal_ON,
    eIOVal_OFF,
}enumIOValue;
#ifdef STM32F4XX
#define KEYIN1_PIN                         GPIO_Pin_3
#define KEYIN1_GPIO_PORT                   GPIOC
#define KEYIN1_GPIO_CLK                    RCC_AHB1Periph_GPIOC  

#define KEYIN2_PIN                         GPIO_Pin_4
#define KEYIN2_GPIO_PORT                   GPIOC
#define KEYIN2_GPIO_CLK                    RCC_AHB1Periph_GPIOC  

#define KEYIN3_PIN                         GPIO_Pin_5
#define KEYIN3_GPIO_PORT                   GPIOC
#define KEYIN3_GPIO_CLK                    RCC_AHB1Periph_GPIOC  

#else

#ifdef STM_64PIN        /*Define for Hardware Use STM32F103 64pins*/
#define KEYIN1_PIN                         GPIO_Pin_3
#define KEYIN1_GPIO_PORT                   GPIOC
#define KEYIN1_GPIO_CLK                    RCC_APB2Periph_GPIOC

#define KEYIN2_PIN                         GPIO_Pin_4
#define KEYIN2_GPIO_PORT                   GPIOC
#define KEYIN2_GPIO_CLK                    RCC_APB2Periph_GPIOC 

#define KEYIN3_PIN                         GPIO_Pin_5
#define KEYIN3_GPIO_PORT                   GPIOC
#define KEYIN3_GPIO_CLK                    RCC_APB2Periph_GPIOC
#else
#define KEYIN1_PIN                         GPIO_Pin_13
#define KEYIN1_GPIO_PORT                   GPIOB
#define KEYIN1_GPIO_CLK                    RCC_APB2Periph_GPIOB 

#define KEYIN2_PIN                         GPIO_Pin_14
#define KEYIN2_GPIO_PORT                   GPIOB
#define KEYIN2_GPIO_CLK                    RCC_APB2Periph_GPIOB  

#define KEYIN3_PIN                         GPIO_Pin_15
#define KEYIN3_GPIO_PORT                   GPIOB
#define KEYIN3_GPIO_CLK                    RCC_APB2Periph_GPIOB
#endif
#endif

/*------------------ Declare for Relay Out IO pins ---------------------------*/
typedef enum _enumRelayOut{
    eNONE_RELAY = 0,
    eRELAY_OUT1 = 0x01,
    eRELAY_OUT2 = 0x02,
    eRELAY_OUT3 = 0x04,
}enumRelayOut;

#ifdef STM32F4XX
#define RELAY1_PIN                         GPIO_Pin_0
#define RELAY1_GPIO_PORT                   GPIOC
#define RELAY1_GPIO_CLK                    RCC_AHB1Periph_GPIOC  

#define RELAY2_PIN                         GPIO_Pin_1
#define RELAY2_GPIO_PORT                   GPIOC
#define RELAY2_GPIO_CLK                    RCC_AHB1Periph_GPIOC  

#define RELAY3_PIN                         GPIO_Pin_2
#define RELAY3_GPIO_PORT                   GPIOC
#define RELAY3_GPIO_CLK                    RCC_AHB1Periph_GPIOC  
#else

#ifdef STM_64PIN        /*Define for Hardware Use STM32F103 64pins*/
#define RELAY1_PIN                         GPIO_Pin_0
#define RELAY1_GPIO_PORT                   GPIOC
#define RELAY1_GPIO_CLK                    RCC_APB2Periph_GPIOC

#define RELAY2_PIN                         GPIO_Pin_1
#define RELAY2_GPIO_PORT                   GPIOC
#define RELAY2_GPIO_CLK                    RCC_APB2Periph_GPIOC  

#define RELAY3_PIN                         GPIO_Pin_2
#define RELAY3_GPIO_PORT                   GPIOC
#define RELAY3_GPIO_CLK                    RCC_APB2Periph_GPIOC
#else
#define RELAY1_PIN                         GPIO_Pin_10
#define RELAY1_GPIO_PORT                   GPIOB
#define RELAY1_GPIO_CLK                    RCC_APB2Periph_GPIOB 

#define RELAY2_PIN                         GPIO_Pin_11
#define RELAY2_GPIO_PORT                   GPIOB
#define RELAY2_GPIO_CLK                    RCC_APB2Periph_GPIOB  

#define RELAY3_PIN                         GPIO_Pin_12
#define RELAY3_GPIO_PORT                   GPIOB
#define RELAY3_GPIO_CLK                    RCC_APB2Periph_GPIOB
#endif
#endif

#ifdef STM32F4XX

#else
#ifdef STM_64PIN        /*Define for Hardware Use STM32F103 64pins*/

#else
#define RS485_DETECT_PIN                       GPIO_Pin_0
#define RS485_DETECT_GPIO_PORT                 GPIOA
#define RS485_DETECT_GPIO_CLK                  RCC_APB2Periph_GPIOA

#define RS485_BUSY_PIN                         GPIO_Pin_1
#define RS485_BUSY_GPIO_PORT                   GPIOA
#define RS485_BUSY_GPIO_CLK                    RCC_APB2Periph_GPIOA 
#endif
#endif
/*--------------------Prototype for functions---------------------------------*/
void UserLedInit(Led_TypeDef Led);
void UserLedOn(Led_TypeDef Led);
void UserLedOff(Led_TypeDef Led);
void UserLedToggle(Led_TypeDef Led);

void UserUsartInit(USER_USART_TypeDef COM, USART_InitTypeDef* USART_InitStruct);

void UserSpi1StructureInit(SPI_InitTypeDef *pSPI_InitStructure);
void UserSpi2StructureInit(SPI_InitTypeDef *pSPI_InitStructure);
void UserSpiInit(USER_SPI_TypeDef COM, SPI_InitTypeDef *pSPI_InitStructure);

//void Realtime_Init(void);
//void SetTimeDateInfo(RTC_TimeTypeDef* p_strtTimeInfo,RTC_DateTypeDef* p_strtDateInfo);
//void GetTimeDateInfo(RTC_TimeTypeDef* p_strtTimeInfo,RTC_DateTypeDef* p_strtDateInfo);

void T1Us_DelayUs(unsigned long Us);
void T1Us_DelayMs(unsigned long Ms);
void TimerDelayBaseUs_Init(void);

/*Functions for Key and relay*/
void KeyInit(enumKeyIn eKey);
enumIOValue ReadKeyIn(enumKeyIn eKey);
void RelayInit(enumRelayOut eRelay);
enumbool ReadRelayState(enumRelayOut eRelay);
void ToggleRelay(enumRelayOut eRelay);
void WriteRelayState(enumRelayOut eRelay,enumBusStatus eState);

#endif
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
