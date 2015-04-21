#include "FlashRW.h"


void SaveSysParameter(SYS_PARAMETER* SYS,uint8 Page)//Page 0-31 chua 1 block size
{
    uint32* psys = (uint32*)SYS;
    uint16  FlashStatus,i;
    static uint32 FwDecripStartAddr;
    FwDecripStartAddr = FW_DECRIP_START_ADDR +(uint32)Page*PAGE_SIZE;
    __disable_irq();
    FLASH_ClearFlag(FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR
                        |FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_OPTERR);
   //SYS->crc = CRC32b((uint8*)SYS,sizeof(SYS_PARAMETER)-sizeof(SYS->crc));
    FLASH_Unlock();
    FlashStatus = FLASH_ErasePage(FwDecripStartAddr);
    if(FLASH_COMPLETE != FlashStatus)
    {
        FLASH_Lock();
        __enable_irq();
        return;
    }
    for(i=0;i<sizeof(SYS_PARAMETER);i+=4)
    {
        FLASH_ProgramWord(FwDecripStartAddr + i, *psys);
        if(*psys!=*(uint32*)(FwDecripStartAddr + i))
        {
            FLASH_Lock();
            __enable_irq();
            return;
        }
        psys++;
    }
    __enable_irq();
}
