#ifndef         _ULTILITIES_H
#define         _ULTILITIES_H
#include "Common.h"
#pragma pack(1)
typedef enum  _enumTypeNumeral
{
    eBINARY=1,
    eOCTAL,
    eDECIMAL,
    eHEXADECIMAL
}enumTypeNumeral;
#pragma pack()

uint32 Map5bitsTo6bits(uint32 iDataIn);
uint32 gf_CreatRandomNum(void);
void UnsignIntegerToString(uint8 bInteger, char* pString);
void str_replace(char *orig, char* result, char *rep, char *with);
void ToHexString(uint16 iData, char* HexString, enumbool eNible);
enumbool StringToInt(enumTypeNumeral eNumeral, uint16* pData, char* pString);
void IntToString(sint16 iData, char* pStr);
void LowerCase(char* pNum);
void UpperCase(char* pNum);
void GetStringByBreakChar(char* pIn,
                          char* pOut,
                          uint8 bStrSize,
                          char* BreakChar);
enumbool IsValidVersion(uint8* strFWVersion);
structFirmwareDecription* GetFirmwareDecription( void );
uint8* GetJumpedFirmwareVersion( void );
void JumpToFirmWare(uint32 iFwStartAddr);
void EraseFlashMemory( uint8 FlashType );
void WriteToFlashMemory(uint32 iFlashAddr, uint32* piData, uint16 WordSize);
void InitTimeOut(TIMEOUT* pT,uint16 Time);
enumbool IsReachTimeout(TIMEOUT* pT,uint16 Time);
#endif /*_ULTILITIES_H*/