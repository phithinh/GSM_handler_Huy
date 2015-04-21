#define __EEPROMDRIVER_C__

/*==============================================================================
INCLUDED FILES
==============================================================================*/
#include "EEPROMDriver.h"

extern SPI_TypeDef* COM_SPI[SPIn];

/*******************************************************************************
* Function Name  : SPIDataGet
* Description    : Gets a data element from the SSI receive FIFO.
* Input          : iSPIBase specifies the SPI module base address.
*                  p_iData is a pointer to a storage location for data that was
*                  received over the SPI interface.
* Output         : iData
*******************************************************************************/
void SPIDataGet(SPI_TypeDef* SPIx, uint32 *p_iData)
{
    /* Wait for SPI2 data reception */
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)
    {
        ;
    }

    (*p_iData) = SPI_I2S_ReceiveData(SPIx);
}

/*******************************************************************************
* Function Name  : SPIDataPut
* Description    : Puts a data element into the SSI transmit FIFO.
*                  iSPIBase specifies the SPI module base address.
*                  iData is the data to be transmitted over the SSI interface.
* Output         : None
*******************************************************************************/
void SPIDataPut(SPI_TypeDef* SPIx, uint32 iData)
{
    /* Wait for SPI1 Tx buffer empty */
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET)
    {
        ;
    }

    SPI_I2S_SendData(SPIx, (uint16)(iData & 0xFF));

    while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) != RESET)
    {
        ;
    }
}

/*******************************************************************************
* Function Name  : SPIDataGetNonBlocking
* Description    : Gets a data element from the SPI receive FIFO
* Input          : iSPIBase specifies the SPI module base address.
*                  p_iData is a pointer to a storage location for data that was
*                  received over the SPI interface.
* Output         : Returns the number of elements read from the SPI receive FIFO.
*               If there is no data in the FIFO, then this function  returns a
*               zero.
*******************************************************************************/
uint32 SPIDataGetNonBlocking(SPI_TypeDef* SPIx, uint32 *p_iData)
{
    uint32 iNumberByte;
    if (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == SET)
    {
        (*p_iData) = SPI_I2S_ReceiveData(SPIx);
        iNumberByte = 1;
    }
    else
    {
        iNumberByte = 0;
    }
    return iNumberByte;
}


/*******************************************************************************
* Function Name  : EEPROM_HwInit
* Description    : init for epprom interface
* Input          : None
* Output         : enumbool eTRUE : init successful
*******************************************************************************/
enumbool EEPROM_HwInit(void)
{
    enumbool blRetcode;
    SPI_InitTypeDef strtSPIStructure;

    /* RF module init */
    EepromSpiStructureInit(&strtSPIStructure);
    UserSpiInit(EEPROM_MODULE,&strtSPIStructure);

    //
    // Wait for the device to be ready to receive an instruction.
    //
    blRetcode = EEPROM_IdleWait(MAX_BUSY_POLL_IDLE);

    //
    // If the device didn't report that it was idle, assume it isn't there
    // and return an error.
    //
    return(blRetcode);
}

/*******************************************************************************
* Function Name  : EEPROM_StatusGet
* Description    : Reads the serial flash device status register,
    This function reads the serial flash status register and returns the value.
* Input          : None
* Output         : the current contents of the serial flash device status register.
*******************************************************************************/
uint8 EEPROM_StatusGet(void)
{
    uint32 iStatus;

    //
    // Assert the chip select for the serial flash.
    //
    EEPROM_CS_LOW();

    //
    // Send the status register read instruction and read back a dummy byte.
    //
    SPIDataPut(COM_SPI[EEPROM_MODULE], INSTR_READ_STATUS);
    SPIDataGet(COM_SPI[EEPROM_MODULE], &iStatus);

    //
    // Write a dummy byte then read back the actual status.
    //
    SPIDataPut(COM_SPI[EEPROM_MODULE], 0xFF);
    SPIDataGet(COM_SPI[EEPROM_MODULE], &iStatus);

    //
    // Deassert the chip select for the serial flash.
    //
    EEPROM_CS_HIGH();

    //
    // Return the status read.
    //
    return((uint8)(iStatus & 0xFF));
}

//*****************************************************************************
//
// Empties the SSI receive FIFO of any data it may contain.
//
// \return None.
//
//*****************************************************************************
static void EEPROM_RxFlush(void)
{
    uint32 iDummy;

    while(SPIDataGetNonBlocking(COM_SPI[EEPROM_MODULE], &iDummy))
    {
        //
        // Spin until there is no more data to read.
        //
    }

    return;
}
//*****************************************************************************
//
// Write an instruction to the serial flash.
//
// \param ucInstruction is the instruction code that is to be sent.
// \param bData is a pointer to optional instruction data that will be sent
// following the instruction code provided in \e bInstruction.  This parameter
// is ignored if \e usLen is 0.
// \param usLen is the length of the optional instruction data.
//
// This function writes an instruction to the serial flash along with any
// provided instruction-specific data.  On return, the flash chip select
// remains asserted allowing an immediate call to EEPROM_InstructionRead().
// To finish an instruction and deassert the chip select, a call must be made
// to EEPROM_InstructionEnd() after this call.
//
// It is assumed that the caller has already determined that the serial flash
// is not busy and is able to accept a new instruction at this point.
//
//*****************************************************************************
void EEPROM_InstructionWrite(uint8 bInstruction,
                                    uint8 *bData,
                                    uint16 usLen)
{
    uint32 iLoop;
    uint32 iDummy;

    //
    // Throw away any data that may be sitting in the receive FIFO.
    //
    EEPROM_RxFlush();

    //
    // Assert the chip select for the serial flash.
    //
    EEPROM_CS_LOW();

    //
    // Send the instruction byte and receive a dummy byte to pace the
    // transaction.
    //
    SPIDataPut(COM_SPI[EEPROM_MODULE], bInstruction);
    SPIDataGet(COM_SPI[EEPROM_MODULE], &iDummy);

    //
    // Send any optional bytes.
    //
    for(iLoop = 0; iLoop < (unsigned long)usLen; iLoop++)
    {
        SPIDataPut(COM_SPI[EEPROM_MODULE], bData[iLoop]);
        SPIDataGet(COM_SPI[EEPROM_MODULE], &iDummy);
    }
}

//*****************************************************************************
//
// Write additional data following an instruction to the serial flash.
//
// \param bData is a pointer to data that will be sent to the device.
// \param usLen is the length of the data to send.
//
// This function writes a block of data to the serial flash device.  Typically
// this will be data to be written to a flash page.
//
// It is assumed that EEPROM_InstructionWrite() has previously been called to
// set the device chip select and send the initial instruction to the device.
//
//*****************************************************************************
void EEPROM_InstructionDataWrite(uint8 *bData, uint16 usLen)
{
    uint32 iLoop;
    uint32 iDummy;

    //
    // Send the data to the device.
    //
    for(iLoop = 0; iLoop < (uint32)usLen; iLoop++)
    {
        SPIDataPut(COM_SPI[EEPROM_MODULE], bData[iLoop]);
        SPIDataGet(COM_SPI[EEPROM_MODULE], &iDummy);
    }
}


//*****************************************************************************
//
// Read data from the serial flash following the write portion of an
// instruction.
//
// \param bData is a pointer to storage for the bytes read from the serial
// flash.
// \param iLen is the number of bytes to read from the device.
//
// This function read a given number of bytes from the device.  It is assumed
// that the flash chip select is already asserted on entry and that an
// instruction has previously been written using a call to
// EEPROM_InstructionWrite().
//
//*****************************************************************************
void EEPROM_InstructionRead(uint8 *bData, uint32 iLen)
{
    uint32 iData;
    uint32 iLoop;

    //
    // For each requested byte...
    //
    for(iLoop = 0; iLoop < iLen; iLoop++)
    {
        //
        // Write dummy data.
        //
        SPIDataPut(COM_SPI[EEPROM_MODULE], 0xFF);

        //
        // Get a byte back from the SSI controller.
        //
        SPIDataGet(COM_SPI[EEPROM_MODULE], &iData); /* read data frm rx fifo */

        //
        // Stash it in the caller's buffer.
        //
        bData[iLoop] = (uint8)(iData & 0xFF);
    }
}

//*****************************************************************************
//
// Finish an instruction by deasserting the serial flash chip select.
//
// This function must be called following EEPROM_InstructionWrite() and,
// depending upon the instruction, EEPROM_InstructionRead() to complete the
// instruction by deasserting the chip select to the serial flash device.
//
//*****************************************************************************
void EEPROM_InstructionEnd(void)
{
    //
    // Pull CS high to deassert it and complete the previous instruction.
    //
    EEPROM_CS_HIGH();
}

/*------------------------------------------------------------------------------
*Engineer     : KhaVo
*Historical   : 1. Mar 31 2011
*Function name: EEPROM_IdleWait
*Descrtiption : Waits for the flash device to report that it is idle.
*Input        : None
*Output       : None
------------------------------------------------------------------------------*/
//*****************************************************************************
//
//
//
// \param iMaxRetries is the maximum number of times the serial flash device
// should be polled before we give up and report an error.  If this value is
// 0, the function continues polling indefinitely.
//
// This function polls the serial flash device and returns when either the
// maximum number of polling attempts is reached or the device reports that it
// is no longer busy.
//
// \return Returns \e true if the device reports that it is idle before the
// specified number of polling attempts is exceeded or \e false otherwise.
//
//*****************************************************************************
enumbool EEPROM_IdleWait(uint32 iMaxRetries)
{
    uint32 iDelay;
    enumbool blBusy;

    //
    // Wait for the device to be ready to receive an instruction.
    //
    iDelay = iMaxRetries;

    do
    {
        blBusy = EEPROM_IsBusy();

        //
        // Increment our counter.  If we have waited too long, assume the
        // device is not present.
        //
        iDelay--;
    }
    while(blBusy && (iDelay || (!(iMaxRetries))));

    //
    // If we get here and we're still busy, we need to return false to indicate
    // a problem.
    //
    return((enumbool)!blBusy);
}

//*****************************************************************************
//
// Sends a command to the flash to enable program and erase operations.
//
// This function sends a write enable instruction to the serial flash device
// in preparation for an erase or program operation.
//
// \return Returns \b true if the instruction was accepted or \b false if
// write operations could not be enabled.
//
//*****************************************************************************
enumbool EEPROM_WriteEnable(void)
{
    enumbool blRetcode;
    uint8 bStatus;

    //
    // Issue the instruction we need to write-enable the chip.
    //
    EEPROM_InstructionWrite(INSTR_WRITE_ENABLE, (uint8 *)0, 0);
    EEPROM_InstructionEnd();

    //
    // Wait for the instruction to complete.
    //
    blRetcode = EEPROM_IdleWait(MAX_BUSY_POLL_IDLE);

    //
    // Is the flash idle?
    //
    if(blRetcode)
    {
        //
        // Read the status and make sure that the Write Enable Latch bit is
        // set (indicating that a write may proceed).
        //
        bStatus = EEPROM_StatusGet();
        if ((bStatus & STATUS_WRITE_ENABLE_LATCH))
        {
            blRetcode = eTRUE;
        }
        else
        {
            blRetcode = eFALSE;
        }
    }

    //
    // Tell the caller how we got on.
    //
    return(blRetcode);
}


//*****************************************************************************
//
//! Determines if the serial flash is able to accept a new instruction.
//!
//! This function reads the serial flash status register and determines whether
//! or not the device is currently busy.  No new instruction may be issued to
//! the device if it is busy.
//!
//! \return Returns \b true if the device is busy and unable to receive a new
//! instruction or \b false if it is idle.
//
//*****************************************************************************
static enumbool EEPROM_IsBusy(void)
{
    uint8 bStatus;
    enumbool blReturn;
    //
    // Get the flash status.
    //
    bStatus = EEPROM_StatusGet();

    //
    // Is the busy bit set?
    //
    if ((bStatus & STATUS_BUSY))
    {
        blReturn = eTRUE;
    }
    else
    {
        blReturn = eFALSE;
    }
    return blReturn;
}