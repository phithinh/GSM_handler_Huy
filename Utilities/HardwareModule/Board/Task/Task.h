#ifndef	__TASK__
#define __TASK__
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
/*-------------------- Declare for Timer Functions ---------------------------*/
#define TIMER_BASE_10US                  TIM3
#define TIMER_BASE_10US_CLK              RCC_APB1Periph_TIM3
#define TIMER_BASE_10US_IRQ              TIM3_IRQn
#define TimerBase10UsIrqHandler          TIM3_IRQHandler
#define TIMER_BASE_PERIOD                      9//10us
////////////////////////////////////////////////////////
#define GSMMONITORINGTASKTIME        100000
#define GSMBUFFERHANDLERTIME          5000
typedef struct
{
uint8 GSMMonitoringTaskFlag;
uint8 GSMBufferHandlerFlag;

} _StrFlagTick;

typedef struct
{
uint8 EventFlag;
}_StrFlagEvent;


void T1Us_DelayUs(unsigned long Us);
void T1Us_DelayMs(unsigned long Ms);
void TimerDelayBaseUs_Init(void);
void FlagTickReset (void);
void TimerBase10UsIrqHandler(void);
#endif