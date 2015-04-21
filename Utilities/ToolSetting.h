/******************************************************************************
===============================================================================
SUTECH
Filename: ToolSetting.h
Description:
Layer:
Accessibility:
===============================================================================
******************************************************************************/

#ifndef __TOOLSETTING_H__
#define __TOOLSETTING_H__
#include "MCU_Library\ST_Manufacturer.h"

/*Some Symbols for recogize*/
#define VALID_FW                0x5A5A
#define FW_DECRIP_SYM           0xA1E7

#define FW_VERSION_SIZE 16
#define BL_VERSION_SIZE 16
#define PRODUCT_NAME_SIZE       30

/*List of ToolID of Product*/
#define TOOL_MAIN_ID            0x01
#define TOOL_TAG_ID             0x02
#define TOOL_TEST_HW_ID         0x03
#define TOOL_ADAPTOR_ID         0x04
#define TOOL_CONFIG_ID          0x05
#define TOOL_MAIN_BOOLOADER     0x06
#define TOOL_TAG_BOOLOADER      0x07

/*Define mapping mcu*/
#define MANUFACTURER(n)         n<<26
#define BITS_CORE(n)            n<<24
#define MAIN_SERIES(n)          n<<12
#define SUB_SERIES(n)           n<<16
#define FLASHSIZE(n)            n

#pragma pack(1)
typedef enum _MCUManufacturer{
    /*Defines for Manufacturer*/
    ST             =1,
    TI             =2,
    MICROCHIP      =3,
    RENESAS        =4,
    NXP            =5,
    ATMEL          =6,
}MCUManufacturer;
#pragma pack()
#pragma pack(1)
typedef enum {
    /*Defines for Manufacturer*/
    CORE_8BITS,
    CORE_16BITS,
    CORE_32BITS,
    CORE_64BITS,
}MCUBitsCore;
#pragma pack()
#pragma pack(1)
typedef enum _enumMCUType
{
    eMCU_NONEVALID = 0,
    
    /*ST PRODUCTION ___________-----------------__________________---------------*/
    /*Cortex M3 STM32F103 Series*/
    /*ARM ST Cortex M3 72 MHz,- 32Pins, Flash Size 16KB*/
    eMCU_STM32F103T4 = MANUFACTURER(ST) | BITS_CORE(CORE_32BITS) | MAIN_SERIES(ARM_CORTEX_M3) |  SUB_SERIES(STM32F103Tx) | FLASHSIZE(16),
    /*ARM ST Cortex M3 72 MHz,- 32Pins, Flash Size 32KB*/
    eMCU_STM32F103T6 = MANUFACTURER(ST) | BITS_CORE(CORE_32BITS) | MAIN_SERIES(ARM_CORTEX_M3) |  SUB_SERIES(STM32F103Tx) | FLASHSIZE(32),
    /*ARM ST Cortex M3 72 MHz,- 32Pins, Flash Size 64KB*/
    eMCU_STM32F103T8 = MANUFACTURER(ST) | BITS_CORE(CORE_32BITS) | MAIN_SERIES(ARM_CORTEX_M3) |  SUB_SERIES(STM32F103Tx) | FLASHSIZE(64),
    /*ARM ST Cortex M3 72 MHz,- 32Pins, Flash Size 128KB*/
    eMCU_STM32F103TB = MANUFACTURER(ST) | BITS_CORE(CORE_32BITS) | MAIN_SERIES(ARM_CORTEX_M3) |  SUB_SERIES(STM32F103Tx) | FLASHSIZE(128),
    
    /*ARM ST Cortex M3 72 MHz,- 48Pins, Flash Size 16KB*/
    eMCU_STM32F103C4 = MANUFACTURER(ST) | BITS_CORE(CORE_32BITS) | MAIN_SERIES(ARM_CORTEX_M3) |  SUB_SERIES(STM32F103Cx) | FLASHSIZE(16),
    /*ARM ST Cortex M3 72 MHz,- 48Pins, Flash Size 32KB*/
    eMCU_STM32F103C6 = MANUFACTURER(ST) | BITS_CORE(CORE_32BITS) | MAIN_SERIES(ARM_CORTEX_M3) |  SUB_SERIES(STM32F103Cx) | FLASHSIZE(32),
    /*ARM ST Cortex M3 72 MHz,- 48Pins, Flash Size 64KB*/
    eMCU_STM32F103C8 = MANUFACTURER(ST) | BITS_CORE(CORE_32BITS) | MAIN_SERIES(ARM_CORTEX_M3) |  SUB_SERIES(STM32F103Cx) | FLASHSIZE(64),
    /*ARM ST Cortex M3 72 MHz,- 48Pins, Flash Size 128KB*/
    eMCU_STM32F103CB = MANUFACTURER(ST) | BITS_CORE(CORE_32BITS) | MAIN_SERIES(ARM_CORTEX_M3) |  SUB_SERIES(STM32F103Cx) | FLASHSIZE(128),
    
    /*ARM ST Cortex M3 72 MHz,- 64Pins, Flash Size 16KB*/
    eMCU_STM32F103R4 = MANUFACTURER(ST) | BITS_CORE(CORE_32BITS) | MAIN_SERIES(ARM_CORTEX_M3) |  SUB_SERIES(STM32F103Rx) | FLASHSIZE(16),
    /*ARM ST Cortex M3 72 MHz,- 64Pins, Flash Size 32KB*/
    eMCU_STM32F103R6 = MANUFACTURER(ST) | BITS_CORE(CORE_32BITS) | MAIN_SERIES(ARM_CORTEX_M3) |  SUB_SERIES(STM32F103Rx) | FLASHSIZE(32),
    /*ARM ST Cortex M3 72 MHz,- 64Pins, Flash Size 64KB*/
    eMCU_STM32F103R8 = MANUFACTURER(ST) | BITS_CORE(CORE_32BITS) | MAIN_SERIES(ARM_CORTEX_M3) |  SUB_SERIES(STM32F103Rx) | FLASHSIZE(64),
    /*ARM ST Cortex M3 72 MHz,- 64Pins, Flash Size 128KB*/
    eMCU_STM32F103RB = MANUFACTURER(ST) | BITS_CORE(CORE_32BITS) | MAIN_SERIES(ARM_CORTEX_M3) |  SUB_SERIES(STM32F103Rx) | FLASHSIZE(128),
    /*ARM ST Cortex M3 72 MHz,- 64Pins, Flash Size 256KB*/
    eMCU_STM32F103RC = MANUFACTURER(ST) | BITS_CORE(CORE_32BITS) | MAIN_SERIES(ARM_CORTEX_M3) |  SUB_SERIES(STM32F103Rx) | FLASHSIZE(256),
    /*ARM ST Cortex M3 72 MHz,- 64Pins, Flash Size 384KB*/
    eMCU_STM32F103RD = MANUFACTURER(ST) | BITS_CORE(CORE_32BITS) | MAIN_SERIES(ARM_CORTEX_M3) |  SUB_SERIES(STM32F103Rx) | FLASHSIZE(384),
    /*ARM ST Cortex M3 72 MHz,- 64Pins, Flash Size 512KB*/
    eMCU_STM32F103RE = MANUFACTURER(ST) | BITS_CORE(CORE_32BITS) | MAIN_SERIES(ARM_CORTEX_M3) |  SUB_SERIES(STM32F103Rx) | FLASHSIZE(512),
    /*ARM ST Cortex M3 72 MHz,- 64Pins, Flash Size 768KB*/
    eMCU_STM32F103RF = MANUFACTURER(ST) | BITS_CORE(CORE_32BITS) | MAIN_SERIES(ARM_CORTEX_M3) |  SUB_SERIES(STM32F103Rx) | FLASHSIZE(768),
    /*ARM ST Cortex M3 72 MHz,- 64Pins, Flash Size 1MB*/
    eMCU_STM32F103RG = MANUFACTURER(ST) | BITS_CORE(CORE_32BITS) | MAIN_SERIES(ARM_CORTEX_M3) |  SUB_SERIES(STM32F103Rx) | FLASHSIZE(1024),
    /*___________-----------------__________________---------------ST PRODUCTION*/
    
    eMCU_MAX = 0xFFFFFFFF,
}enumMCUType;
#pragma pack()
#pragma pack(1)
typedef union  
{
    struct{
        uint16                  FLASHSIZE:12;
        uint8                   MAIN_SERIES:4;
        
        uint8                   SUB_SERIES:8;
        
        MCUBitsCore             BITS_CORE:2;
        MCUManufacturer         MANUFACTURER:6;
    }FIELD;    
    enumMCUType TYPE;        
}MCU_TYPE;
#pragma pack()
#pragma pack(1)
enum _enumPRODUCTID
{
    ePRODUCT_BOOTLOADER = 0x0001,
    ePRODUCT_RFBYKE_ID = 0x0101,
    
    ePRODUCT_UNDEN = 0xFFFF,
};
typedef enum _enumPRODUCTID enumPRODUCTID;
#pragma pack()
#pragma pack(1)
typedef struct _structFirmwareDecription
{
    uint16              SYMBOL;
    char                FW_Version[FW_VERSION_SIZE];
    MCU_TYPE            eMCUType;
    enumPRODUCTID       ProductID;
    char                ProductName[PRODUCT_NAME_SIZE];
    uint8               ToolID;
    
    uint8               UniqueID[5];
    char                Reserve[194];
    
    uint16              ToolStatus;     /*Firmware will operate when ToolStatus is Valid (0x5A5A)*/
}structFirmwareDecription;
#pragma pack()

#endif