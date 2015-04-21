/*------------------------Ultilities.c-----------------------------------------
*Author : Hai Tran
*Date Creat : 25 Oct 2013
*Version V0.1:
- 25/11/2013 : Release first version.
- 27/11/2013 : * Creat 2 type function to get firmware decription
1. In Source, 
------------------------------------------------------------------------------*/

#define _ULTILITIES_C

/* Includes ------------------------------------------------------------------*/
#include "Utilities.h"
#include <stdio.h>
void UpdateFirmwareDecription( structFirmwareDecription* pFWDecrip );
void DisableTimeOut(TIMEOUT* pT);



extern const structFirmwareDecription g_strtFirmwareDecription;
uint8 MapTable5bitsTo6bits[]={29,9,10,11,12,13,14,17,18,19,20,21,22,25,26,27,28,36,37,38,39,41,42,43,44,45,50,51,52,53,54,55};
uint32 Map5bitsTo6bits(uint32 iDataIn)
{
    uint8 b5bits,i=0;
    uint32 i6bits;
    uint32 iDataOut=0;
    /*5bits has 32 value map to 6bits has 64value*/
    do
    {
        b5bits = iDataIn&0x0000001F;
        iDataIn = iDataIn >>5; 
        i6bits = MapTable5bitsTo6bits[b5bits]<<(6*i);
        iDataOut += i6bits;
        i++;
    }while (i<5);
    i6bits = (iDataIn)&0x03;
    iDataOut |=(i6bits<<30);
    
    return iDataOut;
}

/*******************************************************************************
* Function Name  : RfAL_CreatRandomNum
* Description    : creat a random number
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/ 
uint32 gf_CreatRandomNum(void)
{ 
    static uint32 OldNum;
    static uint8 Index;
    uint32 RandomNum;
    uint32 Temp1, Temp2;
    static uint32 Addr;
    Addr = Addr + (((OldNum)>>Index)&0xfff); /*Ram memory from 0x20000000 to 0x20000FFF*/
    
    Index++;
    Index = Index%8;
    
    do
    {
        if ((Addr>0x2000FFFF)|(Addr<0x20000000))
        {
            Addr = 0x20000000 + (((OldNum)>>Index)&0xfff);
        }
        
        RandomNum +=  *(uint32*)Addr;
        Temp1 = RandomNum>>16;
        Temp2 = RandomNum&0xFFFF;
        RandomNum = (Temp1+Temp2) + (Temp1*Temp2);
        Addr = Addr + (((OldNum)>>Index)&0xff); 
        Index++;
        Index = (Index)%8;
        
    }while ((RandomNum==0)||(RandomNum==0xFFFFFFFF)||(RandomNum==OldNum));
    OldNum = RandomNum;
    
    return RandomNum;
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: UnsignIntegerToString
*Description:   change unsigned integer to string
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
void UnsignIntegerToString(uint8 bInteger, char* pString)
{
    pString[1] = (bInteger>=10)?(bInteger%10 +'0'):(0);
    pString[0] = (bInteger>=10)?(bInteger/10 +'0'):(bInteger+'0');
    if (bInteger>10)
        pString[2] = 0;
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: str_replace
*Description:   
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
void str_replace(char *orig, char* result, char *rep, char *with)
{
    char *ins;    // the next insert point
    char *tmp;    // varies
    uint16 len_rep;  // length of rep
    uint16 len_with; // length of with
    uint16 len_front; // distance between rep and end of last rep
    uint16 count;    // number of replacements
    
    if (!orig)
        result =  NULL;
    if (!rep || !(len_rep = strlen(rep)))
        result =  NULL;
    if (!(ins = (char* )strstr(orig, rep))) 
        result =  NULL;
    if (!with)
        with = "";
    len_with = strlen(with);
    
    if (result!=NULL)
    {
        for (count = 0; tmp = (char* )strstr(ins, rep); ++count) {
            ins = tmp + len_rep;
        }
        
        // first time through the loop, all the variable are set correctly
        // from here on,
        //    tmp points to the end of the result string
        //    ins points to the next occurrence of rep in orig
        //    orig points to the remainder of orig after "end of rep"
        //        tmp = result = (char* )malloc(strlen(orig) + (len_with - len_rep) * count + 1);
        tmp = result;
        if (!result)
            result =  NULL;
        
        while (count--) {
            ins = (char* )strstr(orig, rep);
            len_front = ins - orig;
            tmp = (char* )strncpy(tmp, orig, len_front) + len_front;
            tmp = (char* )strcpy(tmp, with) + len_with;
            orig += len_front + len_rep; // move to next "end of rep"
        }
        strcpy(tmp, orig);
    }
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: ToHexString
*Description:   
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
void ToHexString(uint16 iData, char* HexString, enumbool eNible)
{
    uint8 bData;
    uint8 i=0,j;
    
    if (iData<=0xFF)
        if ((eNible)&(iData<=0x0F))
            j = 0;
        else 
            j = 1;
    else
        if ((eNible)&((iData>>8)<=0x0F))
            j = 2;
        else 
            j = 3;
        
        do
        {
            bData = (iData>>((j-i)*4))&0x0F;
            if (bData<=9)
                HexString[i]=bData+'0';
            else if (bData==10)
                HexString[i]='A';
            else if (bData==11)
                HexString[i]='B';
            else if (bData==12)
                HexString[i]='C';  
            else if (bData==13)
                HexString[i]='D';
            else if (bData==14)
                HexString[i]='E';
            else if (bData==15)
                HexString[i]='F';
        }while (i++<j);
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: HexStringToInt
*Description:
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
enumbool StringToInt(enumTypeNumeral eNumeral, uint16* pData, char* pString)
{
    uint16 iData=0;
    uint8 bData;
    uint8 i=0;
    enumbool Ret = eTRUE;
    
    switch (eNumeral)
    {
    case eHEXADECIMAL:
        do
        {
            iData<<=4;
            if ((pString[i]<='9')&(pString[i]>='0'))
                bData = pString[i]-'0';
            else if ((pString[i]=='A')|(pString[i]=='a'))
                bData = 10;
            else if ((pString[i]=='B')|(pString[i]=='b'))
                bData = 11;
            else if ((pString[i]=='C')|(pString[i]=='c'))
                bData = 12;
            else if ((pString[i]=='D')|(pString[i]=='d'))
                bData = 13;
            else if ((pString[i]=='E')|(pString[i]=='e'))
                bData = 14;
            else if ((pString[i]=='F')|(pString[i]=='f'))
                bData = 15;
            else
            {
                Ret = eFALSE;
                break;
            }
            iData|=bData;
        }while (pString[++i]!=0);
        *pData = iData;
        break;
    case  eDECIMAL:
        *pData = 0;
        do
        {
            *pData *=10;
            if ((pString[i]<='9')&&(pString[i]>='0'))
                *pData += pString[i] - '0';
            else
            {
                Ret = eFALSE;
                break;
            }
        }while(pString[++i]!=0);
    }
    return Ret;
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: IntToString
*Description:   change 16bit number to string
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
void IntToString(sint16 iData, char* pStr)
{
    uint16 Temp;
    uint8 i=0,j=0;
    char str[5];
    
    Temp = abs(iData);
    while (eTRUE)
    {
        str[i]='0'+ Temp%10;
        if (Temp/10)
        {
            str[i++]='0'+ Temp%10;
            Temp = Temp/10;
        }
        else
            break;
    }
    if (iData<0)
    {
        pStr[j++]='-';
        i++;
    }
    do
    {
        pStr[j]=str[i-j];
    }while (j++<i);
    pStr[j]=0;/*Add Null character*/
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: LowerCase
*Description:   change string to lower case
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
void LowerCase(char* pNum)
{
    uint16 i = 0;
    char Temp;
    
    do
    {
        Temp = pNum[i];
        if ((Temp>='A')&&(Temp<='Z'))
            pNum[i] = Temp + 32;
    }while (pNum[++i]!=0);
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: UpperCase
*Description:   change string to upper case
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
void UpperCase(char* pNum)
{
    uint16 i = 0;
    char Temp;
    
    do
    {
        Temp = pNum[i];
        if ((Temp>='a')&&(Temp<='z'))
            pNum[i] = Temp - 32;
    }while (pNum[++i]!=0);
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GetStringByBreakChar
*Description:   get small string in pIn,  
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
void GetStringByBreakChar(char* pIn,
                          char* pOut,
                          uint8 bStrSize,
                          char* BreakChar)
{
    uint32 iAddr;
    uint8  bLen;
    
    iAddr = (uint32)strstr(pIn,BreakChar);
    if (iAddr)
    {
        memcpy(pOut,pIn,(iAddr-(uint32)pIn));
    }
    else
    {
        bLen = strlen(pIn);
        if (bLen>bStrSize)
            memcpy(pOut,pIn,bStrSize);
        else
            strcpy(pOut,pIn);
    }
}

#define NUM_FW_VERSION_GROUP    3 /*Major Minor Build*/
#define NUM_DIGIT_IN_GROUP      2
enumbool IsValidVersion(uint8* strFWVersion)
{
    //Firmware version for mat Vxx.xx.xx
    enumbool blResult;
    uint32 iGroup;
    uint32 iDigit;
    if ((strFWVersion[0] == 'F')
        &&(strFWVersion[1] == 'W')
            &&(strFWVersion[2] == '_')
                &&(strFWVersion[3] == 'V'))
    {
        blResult = eTRUE;
        iGroup = 0;
        while ((iGroup < NUM_FW_VERSION_GROUP) && (blResult == eTRUE))
        {
            iDigit = 0;
            while ((iDigit < NUM_DIGIT_IN_GROUP) && (blResult == eTRUE))
            {
                if ((strFWVersion[iGroup* (NUM_DIGIT_IN_GROUP + 1) + iDigit + 4] < '0')
                    ||(strFWVersion[iGroup* (NUM_DIGIT_IN_GROUP + 1) + iDigit + 4] > '9'))
                {
                    blResult = eFALSE;
                }
                iDigit++;
            }
            iGroup++;
        }
    }
    else
    {
        blResult = eFALSE;
    }
    return blResult;
}
/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: WriteToFlashMemory
*Description:  write amount of data to Flash Memory  
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
structFirmwareDecription* GetFirmwareDecription( void )
{
    return (structFirmwareDecription*)&g_strtFirmwareDecription;
}
/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: UpdateFirmwareDecription
*Description:  write amount of data to Flash Memory  
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
void UpdateFirmwareDecription( structFirmwareDecription* pFWDecrip )
{
    uint8 Buffer[1024];
    uint32 FlashPage, FlashAddr;
    structFirmwareDecription *pFW;
    
    FlashAddr = (uint32)GetFirmwareDecription();
    /*Get page address of firmware decription*/
    FlashPage = (FlashAddr - FLASH_BASE_ADDR)/1024;
    
    memcpy(Buffer,(uint32*)(FLASH_BASE_ADDR+FlashPage*1024),1024);

    FLASH_Unlock();
    FLASH_ErasePage(FLASH_BASE_ADDR+(uint32)FlashPage*1024);
    FLASH_Lock();
    /*Get Buffer Firmware Decrip*/
    pFW = (structFirmwareDecription *)&Buffer[FlashAddr-FLASH_BASE_ADDR - FlashPage*1024];
    /*Appky new value*/
    memcpy(pFW,pFWDecrip,sizeof(structFirmwareDecription));    
    /*Write back to flash*/
    WriteToFlashMemory(FLASH_BASE_ADDR+FlashPage*1024,
                       (uint32*)Buffer,
                       sizeof(Buffer)/4);
}
/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: GetJumpedFirmwareVersion
*Description:    
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
uint8* GetJumpedFirmwareVersion( void )
{
    structFirmwareDecription* pFW;
    uint32 FlashSize, EndFlash;
    
    pFW = GetFirmwareDecription();
    FlashSize = pFW->eMCUType.FIELD.FLASHSIZE;
    EndFlash = FLASH_BASE_ADDR + FlashSize*1024 - 1;
    pFW = (structFirmwareDecription*)(EndFlash - sizeof(structFirmwareDecription) + 1);
    if (pFW->SYMBOL==FW_DECRIP_SYM)
    return (uint8*)pFW->FW_Version;
    else
        return Null;
}


void JumpToFirmWare(uint32 iFwStartAddr)
{
    uint32 iJumpAddress;
    fFunction fpFirmware;
    iJumpAddress = *(volatile unsigned long*)(iFwStartAddr + 4);
    fpFirmware = (fFunction) iJumpAddress;
    __set_MSP(*(volatile unsigned long*) iFwStartAddr);
    fpFirmware();
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: EraseFlashMemory
*Description:  Erase flash sector base on memory type (Firmware or Bootloader)  
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
void EraseFlashMemory( uint8 FlashType )
{
    uint8 PageIdx=0,EndPage;    
    uint16 FlashSize;
    structFirmwareDecription* pFW;
    
    
    if (FlashType==BOOTLOADER_TYPE)
    {/*Bootloader from sector 0 to sector 15*/
        FLASH_Unlock();
        for (PageIdx=0;PageIdx<16;PageIdx++)
            FLASH_ErasePage(FLASH_BASE_ADDR+(uint32)PageIdx*1024);
        FLASH_Lock();
    }
    else if (FlashType==FIRMWARE_TYPE)
    {/*Firmware from sectoc 16, one sector 1K*/
        pFW = GetFirmwareDecription();
        FlashSize = pFW->eMCUType.FIELD.FLASHSIZE;
        FLASH_Unlock();
        for (PageIdx=16;PageIdx<FlashSize;PageIdx++)
            FLASH_ErasePage(FLASH_BASE_ADDR+(uint32)PageIdx*1024);
        FLASH_Lock();
    }
    
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: WriteToFlashMemory
*Description:  write amount of data to Flash Memory  
*Input: None
*Output: None
-----------------------------------------------------------------------------*/
void WriteToFlashMemory(uint32 iFlashAddr, uint32* piData, uint16 WordSize)
{
    FLASH_Unlock();
    
    FLASH_ClearFlag(FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR|FLASH_FLAG_EOP);
    for (uint16 i=0;i<WordSize;i++)
    {
        FLASH_ProgramWord(iFlashAddr,*piData);
        iFlashAddr+=4;
        piData += 1;
    }
    FLASH_Lock();
}

/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: InitTimeOut
*Description:  Init for Timeout, set StartTime, ReachTime, acept for time counter
*Input: TIMEOUT *, uint16 Time
*Output: None
-----------------------------------------------------------------------------*/
void InitTimeOut(TIMEOUT* pT,uint16 Time)
{
    pT->iStart = T1Us_Tick1Ms;
    pT->iReach = pT->iStart + Time;
    pT->Over = eFALSE;
    pT->RUNNING = eTRUE;
    pT->ENABLE = eTRUE;
}
/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: DisableTimeOut
*Description:  Disable a TIMEOUT function
*Input: TIMEOUT *
*Output: None
-----------------------------------------------------------------------------*/
void DisableTimeOut(TIMEOUT* pT)
{
    pT->ENABLE = eFALSE;
}
/*-----------------------------------------------------------------------------
*Engineer: 
*Historical: 
*Function name: IsReachTimeout
*Description:  return eTRUE if timer is reach timeout
*Input: TIMEOUT *, uint16 Time
*Output: eTRUE or eFALSE
-----------------------------------------------------------------------------*/
enumbool IsReachTimeout(TIMEOUT* pT,uint16 Time)
{
    if ((pT->ENABLE)&&(Time))
    {
        if (pT->RUNNING==eFALSE)
        {
            pT->iStart = T1Us_Tick1Ms;
            pT->iReach = pT->iStart + Time;
            pT->Over = eFALSE;
            pT->RUNNING = eTRUE;
        }
        if ((pT->iReach > pT->iStart)||(pT->Over))
        {
            if (T1Us_Tick1Ms>=pT->iReach)
            {
                pT->RUNNING = eFALSE;
                return eTRUE;
            }
        }
        else
        {
            if (T1Us_Tick1Ms < pT->iReach)
                pT->Over = eTRUE;
        }
    }
    return eFALSE;
}
