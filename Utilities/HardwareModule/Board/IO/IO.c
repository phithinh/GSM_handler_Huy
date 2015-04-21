#include "IO.h"

void Init_IO (void)
{
  
GPIO_InitTypeDef  GPIO_InitStructure;
//LED1_init
LED1_RCC_ENABLE;
GPIO_InitStructure.GPIO_Pin = LED1_PIN;
GPIO_InitStructure.GPIO_Mode = LED1_MODE;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(LED1_PORT, &GPIO_InitStructure);
LED1_OFF;

//LED2_init
LED2_RCC_ENABLE;
GPIO_InitStructure.GPIO_Pin = LED2_PIN;
GPIO_InitStructure.GPIO_Mode = LED2_MODE;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(LED2_PORT, &GPIO_InitStructure);
LED2_OFF;

//LED3_init
LED3_RCC_ENABLE;
GPIO_InitStructure.GPIO_Pin = LED3_PIN;
GPIO_InitStructure.GPIO_Mode = LED3_MODE;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(LED3_PORT, &GPIO_InitStructure);
LED3_OFF;

}
