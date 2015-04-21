/* Includes ========================================;==========================*/

#define __MAIN_SHP_C_

#include "Common.h"
#include "../../Utilities/HardwareModule/Board/board.h"

#include "../../Utilities/serial_com/serial_com.h"
//#include "../../Utilities/HardwareModule/Board/GSM_Controller/TaskGSM.h"
//#include <Board\Task\Task.h>
//#include <Board\SIM900\SIM900.h>
#include "../../Utilities/HardwareModule/Board/GSM_Thinh/GSM_app.h"
void assert_failed(uint8_t* file, uint32_t line);
extern _StrFlagEvent        StrFlagEvent;
extern _StrFlagTick         StrFlagTick;
//////////////////////////////////////////////////////////////////////////
////prototype
void System_Init(void); 
void GSMMonitoringTask(void);
void GSMBufferHandlerTask(void);
/*-----------------------------------------------------------------------------
*Function name: main
*Description: main program
*Input: 
*Output: 
-----------------------------------------------------------------------------*/
extern  uint8 SIM900_Rei_Buffer[1024]; 
extern char Sim900Tmp0[];
extern char Sim900SMSIncoming[];
extern char Sim900Tmp1[];

void main( void )
{
  
  SystemCoreClockUpdate();
  System_Init(); 
 // TaskGSM_Init();
  GSM_app_init();
  serial_com_init_v();
  ///////////////////////////////////
  
  
  while (1)
  
    {
        GSM_app_main();
        serial_com_main();
      GSMMonitoringTask();
//      GSMBufferHandlerTask();
//      TaskGSMProcess();

    }
  
}


void System_Init(void)
{
TimerDelayBaseUs_Init();//Timer 3
/* Disable JTAG for use LED*/
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
FlagTickReset();
Init_IO();
//SIM900_Init();
}
/////////////////////////////////////////////////////////////
void GSMMonitoringTask(void)
{

  if(StrFlagTick.GSMMonitoringTaskFlag == eTRUE)
  {
    LED1_TOG;
    //Check AT cmd
//    if(SIM900_Rei_Buffer[1023]==1)
//    {
//      StrFlagTick.GSMMonitoringTaskFlag = eFALSE;
//      return;
//    }
//    SIM900_Buffer_Reset();
//    printf("AT\r");
//    DelayMs(200);
//    if(SIM900_AT_Rei_Check_CMD(Sim900Tmp0,8,0)==0)
//    {
//     SIM900_PWR_ON();
//     SIM900_NRESET ();
//    }
//    SIM900_Buffer_Reset();

    StrFlagTick.GSMMonitoringTaskFlag = eFALSE;
  }

}

//void GSMBufferHandlerTask(void)
//{
//    if(StrFlagTick.GSMBufferHandlerFlag == eTRUE)
//  {
////SMS Rei
//    if(SIM900_AT_Rei_Check_CMD(Sim900SMSIncoming,17,0))
//    {
//
//      while(!SIM900_AT_Rei_Check_CMD(Sim900Tmp1,18,0))
//      {
//        LED3_TOG;
//        SIM900_Buffer_Reset();
//        printf("AT+CMGD=1,4\r");
//        DelayMs(200);
//        DelayMs(200);
//      }
//
//      SIM900_Buffer_Reset();
//      LED1_TOG;
//   }
//  StrFlagTick.GSMBufferHandlerFlag = eFALSE;
//  }
//}
////////////////////////////////////////////////////////////////////////////////
/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: 
*Description:
*Input: 
*Output: 
-----------------------------------------------------------------------------*/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  
  /*Reset system*/
  NVIC_SystemReset();
}


