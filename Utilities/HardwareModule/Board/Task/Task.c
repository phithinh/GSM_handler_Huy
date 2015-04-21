#include "stm32f10x.h"
//#include "PlatFormType.h"
//#include "Common.h"
//#include "Task.h"
#include "../board.h"

_StrFlagTick       StrFlagTick;
_StrFlagEvent      StrFlagEvent;
signed long T1Us_Tick1Ms = 0;
uint32 T1Us_Tick10Us = 0;
uint16 T1Us_Tick1s = 0;
void FlagTickReset (void)
{
//  uint8 count=0;
//  uint8* p;
//  p=&StrFlagTick.FlagLogicInputTick;
//  for(count = 0; count++ ; sizeof(StrFlagTick))
//  {
//  *p = 0;
//  p++;
//  }
}
void TimerBase10UsIrqHandler(void)
{
 
//  TIM_ClearFlag(TIMER_BASE_10US,TIM_IT_Update);
  TIMER_BASE_10US->SR = (uint16_t)~TIM_IT_Update;
  T1Us_Tick10Us++;
  if(T1Us_Tick10Us%100 == 0)
    T1Us_Tick1Ms ++;
  if(T1Us_Tick10Us%GSMMONITORINGTASKTIME==0) {
    StrFlagTick.GSMMonitoringTaskFlag= eTRUE;
  }
  if(T1Us_Tick10Us%GSMBUFFERHANDLERTIME==0)  
  {
    StrFlagTick.GSMBufferHandlerFlag=eTRUE;
  }


}
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
        StartValue = TIMER_BASE_10US->CNT;
        WaittingValue = 0;

        while(WaittingValue<Us)
        {
            Timer = TIMER_BASE_10US->CNT;
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
* Function Name  : TimerBase1UsIrqHandler
* Description    : iterupt function for timer base 1Us
* Input          : None
* Output         : None
*******************************************************************************/

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

    RCC_APB1PeriphClockCmd(TIMER_BASE_10US_CLK,ENABLE);

//     Time Base configuration 
//    Used for SYSCLK 72 Mhz
//    Clock for APB1 is 72 Mhz
//
//    Used for SYSCLK 8 Mhz
//    Clock for APB1 is 8 Mhz
 
    TIM_TimeBaseStructure.TIM_Prescaler =  SystemCoreClock/1000000-1;

    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = TIMER_BASE_PERIOD;//
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
    TIM_TimeBaseInit(TIMER_BASE_10US, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIMER_BASE_10US, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIMER_BASE_10US, ENABLE);

    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = TIMER_BASE_10US_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}



