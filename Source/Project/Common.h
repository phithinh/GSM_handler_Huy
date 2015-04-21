/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMON_H
#define __COMMON_H

    
/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#include "stm32f10x_conf.h"
#include "../../Utilities/PlatFormType.h"
#include "../../Utilities/MemoryMap.h"
#include "../../Utilities/ToolSetting.h"
#include "../../Utilities/HardwareModule/HardwareProfile.h"
#include "../../Source/APP/Utilities/Utilities.h"

/* Uncomment SERIAL_DEBUG to enables retarget of printf to  serial port (COM1 on STM32 evalboard) 
for debug purpose */   
#define SERIAL_DEBUG

#define LED_DEBUG    


/*--------------------Extern public variables---------------------------------*/
extern signed long T1Us_Tick1Ms;
extern uint16 T1Us_Tick1s;

/*-------------------- Declare Common Structure ------------------------------*/
typedef enum
{
    eTagComand_None = 0,
    eTagComand_WriteRFUniqueID = 0x01,
    eTagComand_GetRFUniqueID,
    eTagComand_GetTAGVoltageSuply,
    eTagComand_SendString,
    eTagComand_GetTAGAddr,
    eTagComand_GetUSERAddr,
    
    eTagComand_Undentificed = 0xFF,
}enumTagComand;

struct _structTagDataFrame
{
    enumTagComand   eTagCommand;
    uint8           Data[255];
};
typedef struct _structTagDataFrame structTagDataFrame;
#endif /* __COMMON_H */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

