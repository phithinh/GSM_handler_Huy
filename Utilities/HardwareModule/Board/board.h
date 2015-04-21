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
#include "../../../Source/Project/Common.h"
//#include <Board\board.h>
#include "Task/Task.h"
#include "IO/IO.h"
#include "SIM900/SIM900.h"
#define DelayMs(delay)   T1Us_DelayMs(delay)
void HardWareTest(void);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////







#endif
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
