/******************************************************************************
===============================================================================
INNOVA ELECTRONICS VIETNAM
Filename:       EEPROMDriver.c
Description:    Common routine to Read/Erase EEPROM
Layer:
Accessibility:
===============================================================================
******************************************************************************/

#define __EEPROMINTEFACE_C__

/*==============================================================================
INCLUDED FILES
==============================================================================*/
#include "EEPROMInterface.h"
uint8 buffer[128];
/*------------------------------------------------------------------------------
*Engineer     : KhaVo
*Historical   : 1. Mar 31 2011
*Function name: EEPROM_HwInit
*Descrtiption : Hardware configura/Initalize for EEPROM (SPI + GPIO)
*Input        : None
*Output       : Device ready: TRUE, otherwise: FALSE
------------------------------------------------------------------------------*/
enumbool EEPROM_Init(void)
{
    return EEPROM_HwInit();
}
//*****************************************************************************
//
//! Reads a block of serial flash into a buffer.
//!
//! \param iAddress is the serial flash address of the first byte to be read.
//! \param iLength is the number of bytes of data to read.
//! \param pucDst is a pointer to storage for the data read.
//!
//! This function reads a contiguous block of data from a given address in the
//! serial flash device into a buffer supplied by the caller.
//!
//! \return Returns the number of bytes read.
//
//*****************************************************************************
uint32 EEPROM_Read(uint32 iAddress, uint32 iLength,
                   uint8 *p_bDst)
{
    enumbool blRetcode;
    uint8 p_bBuffer[3];
    if ((iAddress >= EEPROM_START_ADDR) && (iAddress + iLength <= EEPROM_END_ADDR  + 1))
    {
        //
        // Wait for the flash to be idle.
        //
        blRetcode = EEPROM_IdleWait(MAX_BUSY_POLL_IDLE);

        //
        // If the device is not idle, return an error.
        //
        if(!blRetcode)
        {
            iLength = (0);
        }
        else
        {
            //
            // Send the read instruction and start address.
            //
            p_bBuffer[0] = (uint8)((iAddress >> 8) & 0xFF);
            p_bBuffer[1] = (uint8)(iAddress & 0xFF);
            EEPROM_InstructionWrite(INSTR_READ_DATA, p_bBuffer, 2);

            //
            // Read back the data.
            //
            EEPROM_InstructionRead(p_bDst, iLength);

            //
            // Tell the flash device we have read everything we need.
            //
            EEPROM_InstructionEnd();

            //
            // Return the number of bytes read.
            //

        }
    }
    else
    {
        iLength = 0;
    }
    return(iLength);
}

//*****************************************************************************
//
//! Writes a block of data to the serial flash device.
//!
//! \param iAddress is the first serial flash address to be written.
//! \param iLength is the number of bytes of data to write.
//! \param p_bSrc is a pointer to the data which is to be written.
//!
//! This function writes a block of data into the serial flash device at the
//! given address.  It is assumed that the area to be written has previously
//! been erased.
//!
//! \return Returns the number of bytes written.
//
//*****************************************************************************
uint32 EEPROM_Write(uint32 iAddress, uint32 iLength,
                    uint8 *p_bSrc)
{
    enumbool blRetcode;
    uint32 iLeft, iStart, iPageLeft;
    uint8 p_bBuffer[3];
    uint8 *p_bStart;

    if ((iAddress >= EEPROM_START_ADDR) && (iAddress + iLength <= EEPROM_END_ADDR  + 1))
    {
        //
        // Wait for the flash to be idle.
        //
        blRetcode = EEPROM_IdleWait(MAX_BUSY_POLL_IDLE);

        //
        // If the device is not idle, return an error.
        //
        if(!blRetcode)
        {
        }
        else
        {
            //
            // Get set up to start writing pages.
            //
            iStart = iAddress;
            iLeft = iLength;
            p_bStart = p_bSrc;

            //
            // Keep writing pages until we have nothing left to write.
            //
            while(iLeft)
            {
                //
                // How many bytes do we have to write in the current page?
                //
                iPageLeft = EEPRROM_PAGE_SIZE - (iStart & (EEPRROM_PAGE_SIZE - 1));

                //
                // How many bytes can we write in the current page?
                //
                iPageLeft = (iPageLeft >= iLeft) ? iLeft : iPageLeft;

                //
                // Enable write operations.
                //
                if(!EEPROM_WriteEnable())
                {
                    //
                    // If we can't write enable the device, exit, telling the caller
                    // how many bytes we've already written.
                    //
                    iLength = iLength - iLeft;
                    break;
                }
                else
                {

                    //
                    // Write a chunk of data into one flash page.
                    //
                    p_bBuffer[0] = (uint8)((iStart >> 8) & 0xFF);
                    p_bBuffer[1] = (uint8)(iStart & 0xFF);
                    EEPROM_InstructionWrite(INSTR_PAGE_PROGRAM, p_bBuffer, 2);
                    EEPROM_InstructionDataWrite(p_bStart, iPageLeft);
                    EEPROM_InstructionEnd();
#ifdef EEPROM_WITH_RTOS
                    vTaskDelay(5);/*Delay 5 ms*/
#else
                    T1Us_DelayMs(5);
#endif
                    //
                    // Wait for the page write to complete.
                    //
                    blRetcode = EEPROM_IdleWait(MAX_BUSY_POLL_PROGRAM_PAGE);
                    if(!blRetcode)
                    {
                        //
                        // If we timed out waiting for the program operation to finish,
                        // exit, telling the caller how many bytes we've already written.
                        //
                        iLength = iLength - iLeft;
                    }
                    else
                    {
                        //
                        // Update our pointers and counters for the next page.
                        //
                        iLeft -= iPageLeft;
                        iStart += iPageLeft;
                        p_bStart += iPageLeft;
                    }
                }
            }

            //
            // If we get here, all is well and we wrote all the required data.
            //
        }
    }
    else
    {
        iLength = 0;
    }
    return(iLength);
}

/*------------------------------------------------------------------------------
*Engineer     : KhaVo
*Historical   : 1. May 11 2011
*Function name: EEPROM_ErasePage
*Descrtiption :
*Input        : None
*Output       : None
------------------------------------------------------------------------------*/
void EEPROM_ErasePage(uint32 PageNumber)
{
    uint32 iByteAddr;
    uint8 bBuffer[EEPRROM_PAGE_SIZE];

    memset(bBuffer, 0xFF, EEPRROM_PAGE_SIZE);
    iByteAddr = PageNumber * EEPRROM_PAGE_SIZE;
    EEPROM_Write(iByteAddr, EEPRROM_PAGE_SIZE, bBuffer);
}
#if EEPROM_TEST_EN
/*------------------------------------------------------------------------------
*Engineer     : KhaVo
*Historical   : 1. Mar 31 2011
*Function name:
*Descrtiption :
*Input        : None
*Output       : None
------------------------------------------------------------------------------*/
void EEPROM_Test(void)
{
    uint8 bRomStatus;
    uint32 iLength;
    
    uint16 usAddress = 0;
	
//    EEPROM_HwInit();
    EEPROM_WriteEnable();
    bRomStatus = EEPROM_StatusGet();
    for (int i = 0; i < sizeof(buffer); i++)
    {
        buffer[i] = (uint8)(i & 0xFF);
    }
    iLength = EEPROM_Write(usAddress, sizeof(buffer), buffer);
    bRomStatus = EEPROM_StatusGet();
    memset(buffer, 0, sizeof(buffer));
    iLength = EEPROM_Read(usAddress, sizeof(buffer), buffer);
}
#endif