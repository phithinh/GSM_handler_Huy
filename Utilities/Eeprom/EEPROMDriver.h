
#ifndef __EEPROMDRIVER_H__
#define __EEPROMDRIVER_H__


#include "Common.h"

/*==============================================================================
*                                 CONSTANTS
*=============================================================================*/
#define EEPROM_WITH_RTOS        1

#define EEPROM_SPI_CLK_RATE            (10000000)
#define EEPROM_SPI_CLKS_PER_MS         (EEPROM_SPI_CLK_RATE / 1000)
#define EEPROM_STATUS_READS_PER_MS     (EEPROM_SPI_CLKS_PER_MS / 16)


#define MAX_BUSY_POLL_IDLE              100
#define MAX_BUSY_POLL_PROGRAM_PAGE      (EEPROM_STATUS_READS_PER_MS * 5)

//*****************************************************************************
//
// Labels for the instructions supported by the Serial EEPROM part.
//
//*****************************************************************************
#define INSTR_WRITE_ENABLE      0x06
#define INSTR_WRITE_DISABLE     0x04
#define INSTR_READ_STATUS       0x05
#define INSTR_WRITE_STATUS      0x01
#define INSTR_READ_DATA         0x03
#define INSTR_PAGE_PROGRAM      0x02
//*****************************************************************************
//
// Status register bit definitions
//
//*****************************************************************************
#define STATUS_BUSY                 0x01
#define STATUS_WRITE_ENABLE_LATCH   0x02
#define STATUS_BLOCK_PROTECT_0      0x04
#define STATUS_BLOCK_PROTECT_1      0x08
#define STATUS_REGISTER_PROTECT     0x80


/*==============================================================================
*                                 GLOBAL VARIABLES
==============================================================================*/

#ifdef __EEPROMDRIVER_C__

/*MCU/Hardware independent*/
static enumbool EEPROM_IsBusy(void);
static void EEPROM_RxFlush(void);
#else

#endif

/*==============================================================================
*                                 PROTOTYPES
==============================================================================*/
enumbool EEPROM_HwInit(void);

/*MCU/Hardware independent*/
enumbool EEPROM_IdleWait(uint32 iMaxRetries);

void EEPROM_InstructionWrite(uint8 bInstruction,
                                    uint8 *bData,
                                    uint16 usLen);
void EEPROM_InstructionDataWrite(uint8 *bData, uint16 usLen);
void EEPROM_InstructionRead(uint8 *bData, uint32 iLen);
void EEPROM_InstructionEnd(void);
uint8 EEPROM_StatusGet(void);
enumbool EEPROM_WriteEnable(void);
#endif
