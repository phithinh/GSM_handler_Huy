/******************************************************************************
===============================================================================
INNOVA ELECTRONICS VIETNAM
Filename: EEPROMDriver.h
Description:
Layer:  Driver
Accessibility:
===============================================================================
******************************************************************************/

#ifndef __EEPROMINTERFACE_H__
#define __EEPROMINTERFACE_H__

#include "Common.h"
#include "EEPROMDriver.h"

/*==============================================================================
*                                 CONSTANTS
*=============================================================================*/
#define EEPROM_TEST_EN 1

#define EEPROM_START_ADDR   0x00000000
#define EEPROM_END_ADDR     0x0000FFFF

//*****************************************************************************
//
// Block, sector, page and chip sizes for the supported device.  Some of the
// code here assumes (reasonably) that these are all powers of two.
//
//*****************************************************************************
#define EEPRROM_PAGE_SIZE       128
/*==============================================================================
*                                 GLOBAL VARIABLES
==============================================================================*/

#ifdef __EEPROMINTERFACE_C__
#else

#endif

/*==============================================================================
*                                 PROTOTYPES
==============================================================================*/
enumbool EEPROM_Init(void);
uint32 EEPROM_Read(uint32 iAddress, uint32 iLength,
                   uint8 *p_bDst);
uint32 EEPROM_Write(uint32 iAddress, uint32 iLength,
                    uint8 *p_bSrc);
void EEPROM_ErasePage(uint32 PageNumber);
#if EEPROM_TEST_EN
void EEPROM_Test(void);
#endif
#endif
