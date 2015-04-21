#define _MAIN_BOARD_SM_C  

/* Includes ------------------------------------------------------------------*/
#include "MainboardSm.h"
#include <stdio.h>


/*structure for User Led Module*/
GPIO_TypeDef* GPIO_PORT[LEDn] = {LED1_GPIO_PORT, LED2_GPIO_PORT, LED3_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN, LED3_PIN};
const uint32_t GPIO_CLK[LEDn] = {LED1_GPIO_CLK, LED2_GPIO_CLK, LED3_GPIO_CLK};

/*structure for USART Module*/
USART_TypeDef* COM_USART[COMn] = {USER_USART1_MODULE,USER_USART2_MODULE,USER_USART3_MODULE}; 

GPIO_TypeDef* COM_TX_PORT[COMn] = {USER_USART1_TX_GPIO_PORT,
USER_USART2_TX_GPIO_PORT,
USER_USART3_TX_GPIO_PORT};

GPIO_TypeDef* COM_RX_PORT[COMn] = {USER_USART1_RX_GPIO_PORT,
USER_USART2_RX_GPIO_PORT,
USER_USART3_RX_GPIO_PORT};

const uint32_t COM_USART_CLK[COMn] = {USER_USART1_CLK,
USER_USART2_CLK,
USER_USART3_CLK};

const uint32_t COM_TX_PORT_CLK[COMn] = {USER_USART1_TX_GPIO_CLK,
USER_USART2_TX_GPIO_CLK,
USER_USART3_TX_GPIO_CLK};

const uint32_t COM_RX_PORT_CLK[COMn] = {USER_USART1_RX_GPIO_CLK,
USER_USART2_RX_GPIO_CLK,
USER_USART3_RX_GPIO_CLK};

const uint16_t COM_TX_PIN[COMn] = {USER_USART1_TX_PIN,
USER_USART2_TX_PIN,
USER_USART3_TX_PIN};

const uint16_t COM_RX_PIN[COMn] = {USER_USART1_RX_PIN,
USER_USART2_RX_PIN,
USER_USART3_RX_PIN};

const uint16_t COM_TX_PIN_SOURCE[COMn] = {USER_USART1_TX_SOURCE,
USER_USART2_TX_SOURCE,
USER_USART3_TX_SOURCE};

const uint16_t COM_RX_PIN_SOURCE[COMn] = {USER_USART1_RX_SOURCE,
USER_USART2_RX_SOURCE,
USER_USART3_RX_SOURCE};

const uint16_t COM_TX_AF[COMn] = {USER_USART1_TX_AF,
USER_USART2_TX_AF,
USER_USART3_TX_AF};

const uint16_t COM_RX_AF[COMn] = {USER_USART1_RX_AF,
USER_USART2_RX_AF,
USER_USART3_RX_AF};

/*structure for SPI Module*/
SPI_TypeDef* COM_SPI[SPIn] = {USER_SPI1_MODULE,USER_SPI2_MODULE};
const uint32_t COM_SPI_CLK[SPIn] = {
    USER_SPI1_CLK,
    USER_SPI2_CLK};
const uint16_t COM_SPI_AF[SPIn] = {
    USER_SPI1_AF,
    USER_SPI2_AF};
/*structure for SPI SCK Pins*/
GPIO_TypeDef* COM_SPI_SCK_PORT[SPIn] = {
    USER_SPI1_SCK_PORT,
    USER_SPI2_SCK_PORT};
const uint32_t COM_SPI_SCK_CLK[SPIn] = {
    USER_SPI1_SCK_CLK,
    USER_SPI2_SCK_CLK};
const uint16_t COM_SPI_SCK_PIN[SPIn] = {
    USER_SPI1_SCK_PIN,
    USER_SPI2_SCK_PIN};
const uint16_t COM_SPI_SCK_PIN_SOURCE[SPIn] = {
    USER_SPI1_SCK_SOURCE,
    USER_SPI2_SCK_SOURCE};

/*structure for SPI MISO Pins*/
GPIO_TypeDef* COM_SPI_MISO_PORT[SPIn] = {
    USER_SPI1_MISO_PORT,
    USER_SPI2_MISO_PORT};
const uint32_t COM_SPI_MISO_CLK[SPIn] = {
    USER_SPI1_MISO_CLK,
    USER_SPI2_MISO_CLK};
const uint16_t COM_SPI_MISO_PIN[SPIn] = {
    USER_SPI1_MISO_PIN,
    USER_SPI2_MISO_PIN};
const uint16_t COM_SPI_MISO_PIN_SOURCE[SPIn] = {
    USER_SPI1_MISO_SOURCE,
    USER_SPI2_MISO_SOURCE};

/*structure for SPI MOSI Pins*/
GPIO_TypeDef* COM_SPI_MOSI_PORT[SPIn] = {
    USER_SPI1_MOSI_PORT,
    USER_SPI2_MOSI_PORT};
const uint32_t COM_SPI_MOSI_CLK[SPIn] = {
    USER_SPI1_MOSI_CLK,
    USER_SPI2_MOSI_CLK};
const uint16_t COM_SPI_MOSI_PIN[SPIn] = {
    USER_SPI1_MOSI_PIN,
    USER_SPI2_MOSI_PIN};
const uint16_t COM_SPI_MOSI_PIN_SOURCE[SPIn] = {
    USER_SPI1_MOSI_SOURCE,
    USER_SPI2_MOSI_SOURCE};

/*structure for SPI CS0 Pins*/
GPIO_TypeDef* COM_SPI_CS0_PORT[SPIn] = {
    USER_SPI1_CS0_PORT,
    USER_SPI2_CS0_PORT};
const uint32_t COM_SPI_CS0_CLK[SPIn] = {
    USER_SPI1_CS0_CLK,
    USER_SPI2_CS0_CLK};
const uint16_t COM_SPI_CS0_PIN[SPIn] = {
    USER_SPI1_CS0_PIN,
    USER_SPI2_CS0_PIN};

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: 
*Description:
*Input: 
*Output: 
-----------------------------------------------------------------------------*/
void UserLedInit(Led_TypeDef Led)
{
#ifdef LED_DEBUG
    GPIO_InitTypeDef  GPIO_InitStructure;
    uint8 i;
    
    for (i=0;i<LEDn;i++)
    {
        if (Led&(1<<i))
        {
#ifdef STM32F4XX
    /* Enable the GPIO_LED Clock */
            RCC_AHB1PeriphClockCmd(GPIO_CLK[i], ENABLE);
    
    
    /* Configure the GPIO_LED pin */
            GPIO_InitStructure.GPIO_Pin = GPIO_PIN[i];
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIO_PORT[i], &GPIO_InitStructure);
    
#else /*STM32F1xx*/    
    /* Enable the GPIO_LED Clock */
            RCC_APB2PeriphClockCmd(GPIO_CLK[i], ENABLE);
    
    /* Configure the GPIO_LED pin */
            GPIO_InitStructure.GPIO_Pin = GPIO_PIN[i];
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(GPIO_PORT[i], &GPIO_InitStructure);
    
#endif
            UserLedOff(i);
#endif
}
    }
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: 
*Description:   
*Input: Specifies the Led to be set on.
*Output: 
-----------------------------------------------------------------------------*/
void UserLedOn(Led_TypeDef Led)
{
    uint8 i;
    for (i=0;i<LEDn;i++)
    {
        if (Led&(1<<i))
        {
#ifdef LED_DEBUG
    
#ifdef STM32F4XX
            GPIO_PORT[i]->BSRRH = GPIO_PIN[i];
#else
            GPIO_PORT[i]->BRR = GPIO_PIN[i];/*Clear bit*/
#endif
    
#endif
}
    }
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: 
*Description:   
*Input: Specifies the Led to be set off.
*Output: 
-----------------------------------------------------------------------------*/
void UserLedOff(Led_TypeDef Led)
{    
    uint8 i;
    for (i=0;i<LEDn;i++)
    {
        if (Led&(1<<i))
        {
#ifdef STM32F4XX
            GPIO_PORT[i]->BSRRL = GPIO_PIN[i];
#else
            GPIO_PORT[i]->BSRR = GPIO_PIN[i];/*Set bit*/
#endif
}
    }
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: 
*Description:   
*Input: Specifies the Led to be toggled
*Output: 
-----------------------------------------------------------------------------*/
void UserLedToggle(Led_TypeDef Led)
{
    uint8 i;
    for (i=0;i<LEDn;i++)
    {
        if (Led&(1<<i))
        {
#ifdef LED_DEBUG
            GPIO_PORT[i]->ODR ^= GPIO_PIN[i];
#endif
}
    }
}



/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: 
*Description:   
*Input: @Button : Specifies the Button to be read
*Output: value of button
-----------------------------------------------------------------------------*/
void UserUsartInit(USART_TypeDef *xUART, USART_InitTypeDef* USART_InitStruct)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USER_USART_TypeDef COM;
    uint8 i = 0;
    
    while (i<COMn)
    {
        if (COM_USART[i]==xUART)
        {
            COM = (USER_USART_TypeDef)i;
            break;
        }
        i++;
    }
    
#ifdef STM32F4XX
    /* Enable GPIO clock */
    RCC_AHB1PeriphClockCmd(COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM], ENABLE);
    
    if (COM == USER_USART1)
    {
        /* Enable UART clock */
        RCC_APB2PeriphClockCmd(COM_USART_CLK[COM], ENABLE);
    }
    else
    {
        /* Enable UART clock */
        RCC_APB1PeriphClockCmd(COM_USART_CLK[COM], ENABLE);
    }
    
    /* Connect PXx to USARTx_Tx*/
    GPIO_PinAFConfig(COM_TX_PORT[COM], COM_TX_PIN_SOURCE[COM], COM_TX_AF[COM]);
    
    /* Connect PXx to USARTx_Rx*/
    GPIO_PinAFConfig(COM_RX_PORT[COM], COM_RX_PIN_SOURCE[COM], COM_RX_AF[COM]);
    
    /* Configure USART Tx as alternate function  */
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    
    GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[COM];
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStructure);
    
    /* Configure USART Rx as alternate function  */
    //    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];
    GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStructure);
    
#else
    /* Enable GPIO clock */
    RCC_APB2PeriphClockCmd(COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM], ENABLE);
    
    if (COM == USER_USART1)
    {
        /* Enable UART clock */
        RCC_APB2PeriphClockCmd(COM_USART_CLK[COM], ENABLE);
    }
    else
    {
        /* Enable UART clock */
        RCC_APB1PeriphClockCmd(COM_USART_CLK[COM], ENABLE);
    }
    
    /* Configure USART Tx as alternate function  */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[COM];
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStructure);
    
    /* Configure USART Rx as alternate function  */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];
    GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStructure);
    
#endif
    
    /* USART configuration */
    USART_Init(COM_USART[COM], USART_InitStruct);
    
    /* Enable USART */
    USART_Cmd(COM_USART[COM], ENABLE);
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: UserSpi1StructureInit
*Description:   
*Input: @Button : Specifies the Button to be read
*Output: value of button
-----------------------------------------------------------------------------*/
void UserSpi1StructureInit(SPI_InitTypeDef *pSPI_InitStructure)
{
    /*SPI configuration*/
    pSPI_InitStructure->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    pSPI_InitStructure->SPI_Mode = SPI_Mode_Master;
    pSPI_InitStructure->SPI_DataSize = SPI_DataSize_8b;
    pSPI_InitStructure->SPI_CPOL = SPI_CPOL_Low;
    pSPI_InitStructure->SPI_CPHA = SPI_CPHA_1Edge;
    pSPI_InitStructure->SPI_NSS = SPI_NSS_Soft;
    //clock APB2  = 168Mhz/2 = 84Mhz 
    //-->> SPI_CLK = 84M/64 = 1.3Mhz
    pSPI_InitStructure->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    pSPI_InitStructure->SPI_FirstBit = SPI_FirstBit_MSB;
    pSPI_InitStructure->SPI_CRCPolynomial = 7;
}


/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: UserSpi1StructureInit
*Description:   
*Input: @Button : Specifies the Button to be read
*Output: value of button
-----------------------------------------------------------------------------*/
void UserSpi2StructureInit(SPI_InitTypeDef *pSPI_InitStructure)
{
    /*SPI configuration*/
    pSPI_InitStructure->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    pSPI_InitStructure->SPI_Mode = SPI_Mode_Master;
    pSPI_InitStructure->SPI_DataSize = SPI_DataSize_8b;
    pSPI_InitStructure->SPI_CPOL = SPI_CPOL_Low;
    pSPI_InitStructure->SPI_CPHA = SPI_CPHA_1Edge;
    pSPI_InitStructure->SPI_NSS = SPI_NSS_Soft;
    //clock APB2  = 168Mhz/2 = 84Mhz 
    //-->> SPI_CLK = 84M/64 = 1.3Mhz
    pSPI_InitStructure->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
    pSPI_InitStructure->SPI_FirstBit = SPI_FirstBit_MSB;
    pSPI_InitStructure->SPI_CRCPolynomial = 7;
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: 
*Description:   
*Input: @Button : Specifies the Button to be read
*Output: value of button
-----------------------------------------------------------------------------*/
void UserSpiInit(USER_SPI_TypeDef COM, SPI_InitTypeDef *pSPI_InitStructure) 
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
#ifdef STM32F4XX
    /*Enable clock for GPIO pins*/
    RCC_AHB1PeriphClockCmd(COM_SPI_SCK_CLK[COM] 
                           | COM_SPI_MISO_CLK[COM] 
                               | COM_SPI_MOSI_CLK[COM] 
                                   | COM_SPI_CS0_CLK[COM] , ENABLE);
    /*Enable clock for SPI Module*/
    if (COM_SPI[COM]==SPI1)
        RCC_APB2PeriphClockCmd(COM_SPI_CLK[COM], ENABLE);
    else
        RCC_APB1PeriphClockCmd(COM_SPI_CLK[COM], ENABLE);
    
    /*Config Output type for SCK Pins*/
    GPIO_InitStructure.GPIO_Pin = COM_SPI_SCK_PIN[COM];
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(COM_SPI_SCK_PORT[COM], &GPIO_InitStructure);
    
    /*Config Output type for MOSI Pins*/
    GPIO_InitStructure.GPIO_Pin = COM_SPI_MOSI_PIN[COM];
    GPIO_Init(COM_SPI_MOSI_PORT[COM], &GPIO_InitStructure);
    
    /*Config Input type for MISO Pins*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin = COM_SPI_MISO_PIN[COM];
    GPIO_Init(COM_SPI_MISO_PORT[COM], &GPIO_InitStructure);
    /*Config alternate function for SPI Module*/
    GPIO_PinAFConfig(COM_SPI_SCK_PORT[COM],COM_SPI_SCK_PIN_SOURCE[COM],COM_SPI_AF[COM]);/*SCK Pins*/
    GPIO_PinAFConfig(COM_SPI_MISO_PORT[COM],COM_SPI_MISO_PIN_SOURCE[COM],COM_SPI_AF[COM]);/*MISO Pins*/
    GPIO_PinAFConfig(COM_SPI_MOSI_PORT[COM],COM_SPI_MOSI_PIN_SOURCE[COM],COM_SPI_AF[COM]);/*MOSI Pins*/
    
#else
    /*Enable clock for GPIO pins*/
    RCC_APB2PeriphClockCmd(COM_SPI_SCK_CLK[COM] 
                           | COM_SPI_MISO_CLK[COM] 
                               | COM_SPI_MOSI_CLK[COM] 
                                   | COM_SPI_CS0_CLK[COM] , ENABLE);
    /*Enable clock for SPI Module*/
    if (COM_SPI[COM]==SPI1)
        RCC_APB2PeriphClockCmd(COM_SPI_CLK[COM], ENABLE);
    else
        RCC_APB1PeriphClockCmd(COM_SPI_CLK[COM], ENABLE);
    
    /*Config Output type for SCK Pins*/
    GPIO_InitStructure.GPIO_Pin = COM_SPI_SCK_PIN[COM];
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(COM_SPI_SCK_PORT[COM], &GPIO_InitStructure);
    
    /*Config Output type for MOSI Pins*/
    GPIO_InitStructure.GPIO_Pin = COM_SPI_MOSI_PIN[COM];
    GPIO_Init(COM_SPI_MOSI_PORT[COM], &GPIO_InitStructure);
    
    /*Config Input type for MISO Pins*/
    GPIO_InitStructure.GPIO_Pin = COM_SPI_MISO_PIN[COM];
    GPIO_Init(COM_SPI_MISO_PORT[COM], &GPIO_InitStructure);
    
#endif
    
    /*Reset SPI Interface*/
    SPI_I2S_DeInit(COM_SPI[COM]);
    
    /*SPI configuration*/
    SPI_Init(COM_SPI[COM], pSPI_InitStructure);
    
    /*Enable SPI1*/
    SPI_Cmd(COM_SPI[COM], ENABLE);
}

///*-----------------------------------------------------------------------------
//*Engineer: 
//*Historical: 
//*Function name: 
//*Description:   
//*Input: @Button : Specifies the Button to be read
//*Output: value of button
//-----------------------------------------------------------------------------*/
//void Realtime_Init(void)
//{
//    RTC_InitTypeDef strtRTC_Init;
//    /*Enable LSI RC clock, LSI not accuracy than LSE OSC*/
//    RCC_LSICmd(ENABLE);
//    /*Select clock source from LSI*/
//    PWR_BackupAccessCmd(ENABLE);
//    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
//    RCC_RTCCLKCmd(ENABLE);
//    
//    RTC_WriteProtectionCmd(DISABLE);
//    RTC_WaitForSynchro();
//    /*Config clock, struct RTC for module*/
//    RTC_StructInit(&strtRTC_Init);
//    RTC_Init(&strtRTC_Init);
//}

//void SetTimeDateInfo(RTC_TimeTypeDef* p_strtTimeInfo,RTC_DateTypeDef* p_strtDateInfo)
//{
//    RTC_SetTime(RTC_Format_BCD, p_strtTimeInfo);
//    RTC_SetDate(RTC_Format_BCD, p_strtDateInfo);
//}
//
//void GetTimeDateInfo(RTC_TimeTypeDef* p_strtTimeInfo,RTC_DateTypeDef* p_strtDateInfo)
//{
//    RTC_GetTime(RTC_Format_BCD, p_strtTimeInfo);
//    RTC_GetDate(RTC_Format_BCD, p_strtDateInfo);
//}


/*******************************************************************************
* Function Name  : T1Us_DelayUs
* Description    : T1Us_DelayUs
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void T1Us_DelayUs(unsigned long Us)
{
    uint16      StartValue,WaittingValue;
    uint16 Timer;
    
    if (Us<1000)
    {
        StartValue = TIMER_BASE_1US->CNT;
        WaittingValue = 0;
        
        while(WaittingValue<Us)
        {
            Timer = TIMER_BASE_1US->CNT;
            if (Timer>=StartValue)
                WaittingValue = Timer - StartValue;
            else
                WaittingValue = 1000 - StartValue + Timer;
        }
    }
}

/*******************************************************************************
* Function Name  : T1Us_DelayUs
* Description    : T1Us_DelayUs
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void T1Us_DelayMs(unsigned long Ms)
{
    uint32      WaittingValue;
    
    if ((MAX_VALUE_32b-T1Us_Tick1Ms)>Ms)
    {
        WaittingValue=T1Us_Tick1Ms+Ms;
        while (T1Us_Tick1Ms<WaittingValue);
    }
    else
    {
        WaittingValue = T1Us_Tick1Ms;
        while (T1Us_Tick1Ms>=WaittingValue);
        WaittingValue = MAX_VALUE_32b-WaittingValue;
        WaittingValue = Ms-WaittingValue;
        while (T1Us_Tick1Ms<WaittingValue);
    }
}

/*******************************************************************************
* Function Name  : TimerDelayBaseUs_Init
* Description    : TimerDelayBaseUs_Init
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TimerDelayBaseUs_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    
    RCC_APB1PeriphClockCmd(TIMER_BASE_1US_CLK,ENABLE);
    
#ifdef STM32F4XX
    /* Time Base configuration */
    /*Used for SYSCLK 168Mhz*/
    TIM_TimeBaseStructure.TIM_Prescaler = 83;//tao xung clock 1Mhz  
#else
    /* Time Base configuration */
    /*Used for SYSCLK 72 Mhz*/
    /*Clock for APB1 is 72 Mhz
    
    /*Used for SYSCLK 8 Mhz*/
    /*Clock for APB1 is 8 Mhz
    */
    TIM_TimeBaseStructure.TIM_Prescaler = 7;//tao xung clock 1Mhz
#endif
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 999;//1ms ngat 1 lan
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
    TIM_TimeBaseInit(TIMER_BASE_1US, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIMER_BASE_1US, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIMER_BASE_1US, ENABLE);  
    
    NVIC_InitTypeDef NVIC_InitStructure;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
    NVIC_InitStructure.NVIC_IRQChannel = TIMER_BASE_1US_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    
}

uint32 T1Us_Tick1Ms = 0;
uint16 T1Us_Tick1s = 0;

/*******************************************************************************
* Function Name  : TimerBase1UsIrqHandler
* Description    : iterupt function for timer base 1Us
* Input          : None
* Output         : None
*******************************************************************************/
void TimerBase1UsIrqHandler(void)
{
    TIM_ClearFlag(TIMER_BASE_1US,TIM_IT_Update);
    T1Us_Tick1Ms ++;
    if (T1Us_Tick1Ms%1000==0)
        T1Us_Tick1s ++;
}


/*******************************************************************************
* Function Name  : KeyInit
* Description    : init for input
* Input          : None
* Output         : None
*******************************************************************************/
/*Functions for Key and relay*/
void KeyInit(enumKeyIn eKey)
{
    uint8 i;
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    for (i=0;i<3;i++)
    {
        switch (eKey&(1<<i))
        {
#ifdef STM32F4XX
        case eKEY_IN1:
            /* Enable the GPIO_LED Clock */
            RCC_AHB1PeriphClockCmd(KEYIN1_GPIO_CLK, ENABLE);
            /* Configure the GPIO_LED pin */
            GPIO_InitStructure.GPIO_Pin = KEYIN1_PIN;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(KEYIN1_GPIO_PORT, &GPIO_InitStructure);
            break;
        case eKEY_IN2:
            /* Enable the GPIO_LED Clock */
            RCC_AHB1PeriphClockCmd(KEYIN2_GPIO_CLK, ENABLE);
            /* Configure the GPIO_LED pin */
            GPIO_InitStructure.GPIO_Pin = KEYIN2_PIN;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(KEYIN2_GPIO_PORT, &GPIO_InitStructure);
            break;
        case eKEY_IN3:
            /* Enable the GPIO_LED Clock */
            RCC_AHB1PeriphClockCmd(KEYIN3_GPIO_CLK, ENABLE);
            /* Configure the GPIO_LED pin */
            GPIO_InitStructure.GPIO_Pin = KEYIN3_PIN;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(KEYIN3_GPIO_PORT, &GPIO_InitStructure);
            break;
#else
        case eKEY_IN1:
            /* Enable the GPIO_LED Clock */
            RCC_APB2PeriphClockCmd(KEYIN1_GPIO_CLK, ENABLE);
            /* Configure the GPIO_LED pin */
            GPIO_InitStructure.GPIO_Pin = KEYIN1_PIN;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(KEYIN1_GPIO_PORT, &GPIO_InitStructure);
            break;
        case eKEY_IN2:
            /* Enable the GPIO_LED Clock */
            RCC_APB2PeriphClockCmd(KEYIN2_GPIO_CLK, ENABLE);
            /* Configure the GPIO_LED pin */
            GPIO_InitStructure.GPIO_Pin = KEYIN2_PIN;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(KEYIN2_GPIO_PORT, &GPIO_InitStructure);
            break;
        case eKEY_IN3:
            /* Enable the GPIO_LED Clock */
            RCC_APB2PeriphClockCmd(KEYIN3_GPIO_CLK, ENABLE);
            /* Configure the GPIO_LED pin */
            GPIO_InitStructure.GPIO_Pin = KEYIN3_PIN;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(KEYIN3_GPIO_PORT, &GPIO_InitStructure);
            break;
#endif
        }
    }
}
uint32 iReadKeyInTiming=0;

void SetKeyInTiming(uint32 iValue)
{
    iReadKeyInTiming = iValue;
}

/*******************************************************************************
* Function Name  : ReadKeyIn
* Description    : return IO value of pin
* Input          : eKey : enum of key in
* Output         : enumIOValue
*******************************************************************************/
enumIOValue ReadKeyIn(enumKeyIn eKey)
{
    enumbool eStatus = eFALSE;
    static enumIOValue eKeyValue;
    static enumbool eOldStatusArr[3];
    static uint32 iStartTime=0;
    
    if (T1Us_Tick1Ms>(uint32)(iStartTime + iReadKeyInTiming))
    {
        iStartTime = T1Us_Tick1Ms;
        switch (eKey)
        {
        case eKEY_IN1:
            if ((KEYIN1_GPIO_PORT->IDR & KEYIN1_PIN) == Bit_RESET)   eStatus = eTRUE;
            break;
            
        case eKEY_IN2:
            if ((KEYIN2_GPIO_PORT->IDR & KEYIN2_PIN) == Bit_RESET)   eStatus = eTRUE;
            break;
            
        case eKEY_IN3:
            if ((KEYIN3_GPIO_PORT->IDR & KEYIN3_PIN) == Bit_RESET)   eStatus = eTRUE;
            break;
        }
        
        if ((eStatus!=eOldStatusArr[eKey])&&(eStatus==eTRUE))
            eKeyValue = eIOVal_OFF_TO_ON;   /*Transition from off to on of Key*/
        else if ((eStatus!=eOldStatusArr[eKey])&&(eStatus==eFALSE))
            eKeyValue = eIOVal_ON_TO_OFF;   /*Transition from off to on of Key*/
        else if (eStatus==eTRUE)
            eKeyValue = eIOVal_ON;          /*Key still on*/
        else
            eKeyValue = eIOVal_OFF;         /*Key still off*/
        
        eOldStatusArr[eKey] = eStatus;
    }
    
    return eKeyValue;
}

/*******************************************************************************
* Function Name  : ReadKeyIn
* Description    : return IO value of pin
* Input          : eKey : enum of key in
* Output         : enumIOValue
*******************************************************************************/
void RelayInit(enumRelayOut eRelay)
{
    uint8 i;
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    for (i=0;i<3;i++)
    {
        switch (eRelay&(1<<i))
        {
#ifdef STM32F4XX
        case eRELAY_OUT1:
            /* Enable the GPIO_LED Clock */
            RCC_AHB1PeriphClockCmd(RELAY1_GPIO_CLK, ENABLE);
            /* Configure the GPIO_LED pin */
            GPIO_InitStructure.GPIO_Pin = RELAY1_PIN;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(RELAY1_GPIO_PORT, &GPIO_InitStructure);
            WriteRelayState(eRELAY_OUT1,eLOW_LEVEL);
            break;
        case eRELAY_OUT2:
            /* Enable the GPIO_LED Clock */
            RCC_AHB1PeriphClockCmd(RELAY2_GPIO_CLK, ENABLE);
            /* Configure the GPIO_LED pin */
            GPIO_InitStructure.GPIO_Pin = RELAY2_PIN;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(RELAY2_GPIO_PORT, &GPIO_InitStructure);
            WriteRelayState(eRELAY_OUT2,eLOW_LEVEL);
            break;
        case eRELAY_OUT3:
            /* Enable the GPIO_LED Clock */
            RCC_AHB1PeriphClockCmd(RELAY3_GPIO_CLK, ENABLE);
            /* Configure the GPIO_LED pin */
            GPIO_InitStructure.GPIO_Pin = RELAY3_PIN;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(RELAY3_GPIO_PORT, &GPIO_InitStructure);
            WriteRelayState(eRELAY_OUT3,eLOW_LEVEL);
            break;
#else
        case eRELAY_OUT1:
            /* Enable the GPIO_LED Clock */
            RCC_APB2PeriphClockCmd(RELAY1_GPIO_CLK, ENABLE);
            /* Configure the GPIO_LED pin */
            GPIO_InitStructure.GPIO_Pin = RELAY1_PIN;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(RELAY1_GPIO_PORT, &GPIO_InitStructure);
            WriteRelayState(eRELAY_OUT1,eLOW_LEVEL);
            break;
        case eRELAY_OUT2:
            /* Enable the GPIO_LED Clock */
            RCC_APB2PeriphClockCmd(RELAY2_GPIO_CLK, ENABLE);
            /* Configure the GPIO_LED pin */
            GPIO_InitStructure.GPIO_Pin = RELAY2_PIN;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(RELAY2_GPIO_PORT, &GPIO_InitStructure);
            WriteRelayState(eRELAY_OUT2,eLOW_LEVEL);
            break;
        case eRELAY_OUT3:
            /* Enable the GPIO_LED Clock */
            RCC_APB2PeriphClockCmd(RELAY3_GPIO_CLK, ENABLE);
            /* Configure the GPIO_LED pin */
            GPIO_InitStructure.GPIO_Pin = RELAY3_PIN;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(RELAY3_GPIO_PORT, &GPIO_InitStructure);
            WriteRelayState(eRELAY_OUT3,eLOW_LEVEL);
            break;
#endif
        }
    }
}

/*******************************************************************************
* Function Name  : ReadRelayState
* Description    : return IO value of relay
* Input          : eRelay : enum of relay
* Output         : enumbool
*******************************************************************************/
enumbool ReadRelayState(enumRelayOut eRelay)
{
    enumbool eStatus=eFALSE;
    
    switch (eRelay)
    {
    case eRELAY_OUT1:
        if ((RELAY1_GPIO_PORT->IDR & RELAY1_PIN) == Bit_SET)   eStatus = eTRUE;
        break;
    case eRELAY_OUT2:
        if ((RELAY2_GPIO_PORT->IDR & RELAY2_PIN) == Bit_SET)   eStatus = eTRUE;
        break;
    case eRELAY_OUT3:
        if ((RELAY3_GPIO_PORT->IDR & RELAY3_PIN) == Bit_SET)   eStatus = eTRUE;
        break;
    }
    return eStatus;
}

/*******************************************************************************
* Function Name  : ToggleRelay
* Description    : return IO value of relay
* Input          : eRelay : enum of relay
* Output         : enumbool
*******************************************************************************/
void ToggleRelay(enumRelayOut eRelay)
{
    switch (eRelay)
    {
    case eRELAY_OUT1:
        RELAY1_GPIO_PORT->ODR ^= RELAY1_PIN;
        break;
    case eRELAY_OUT2:
        RELAY2_GPIO_PORT->ODR ^= RELAY2_PIN;
        break;
    case eRELAY_OUT3:
        RELAY3_GPIO_PORT->ODR ^= RELAY3_PIN;
        break;   
    }
}

void WriteRelayState(enumRelayOut eRelay,enumBusStatus eState)
{
    
    switch (eRelay)
    {
#ifdef STM32F4XX
    case eRELAY_OUT1:
        if (eState == eHIGH_LEVEL)
            RELAY1_GPIO_PORT->BSRRL = RELAY1_PIN;
        else
            RELAY1_GPIO_PORT->BSRRH = RELAY1_PIN;
        break;
    case eRELAY_OUT2:
        if (eState == eHIGH_LEVEL)
            RELAY2_GPIO_PORT->BSRRL = RELAY2_PIN;
        else
            RELAY2_GPIO_PORT->BSRRH = RELAY2_PIN;
        break;
    case eRELAY_OUT3:
        if (eState == eHIGH_LEVEL)
            RELAY3_GPIO_PORT->BSRRL = RELAY3_PIN;
        else
            RELAY3_GPIO_PORT->BSRRH = RELAY3_PIN;
        break;  
#else
    case eRELAY_OUT1:
        if (eState == eHIGH_LEVEL)
            RELAY1_GPIO_PORT->BSRR = RELAY1_PIN;
        else
            RELAY1_GPIO_PORT->BRR = RELAY1_PIN;
        break;
    case eRELAY_OUT2:
        if (eState == eHIGH_LEVEL)
            RELAY2_GPIO_PORT->BSRR = RELAY2_PIN;
        else
            RELAY2_GPIO_PORT->BRR = RELAY2_PIN;
        break;
    case eRELAY_OUT3:
        if (eState == eHIGH_LEVEL)
            RELAY3_GPIO_PORT->BSRR = RELAY3_PIN;
        else
            RELAY3_GPIO_PORT->BRR = RELAY3_PIN;
        break;  
#endif 
    }
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
