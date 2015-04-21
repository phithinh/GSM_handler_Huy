/******************************************************************************
===============================================================================
SUTECH
Filename: MemoryMap.h
Description: Internal, external flash layout
Layer:
Accessibility:
===============================================================================
******************************************************************************/

#ifndef __MEMORYMAP_H__
#define __MEMORYMAP_H__

#define FIRMWARE_TYPE        1
#define BOOTLOADER_TYPE      2

/*Config for firmware type : Firm Or Bootloader*/
//#define FIRMWARE_NON_BOOT_SOURCE
//#define FIRMWARE_WITH_BOOT_SOURCE
//#define BOOTLOADER_SOURCE

#define FLASH_BASE_ADDR                 (0x08000000)
#define FLASH_BASE_END_ADDR             (0x0800FFFF)    /*Flash size 64KB*/
#define PAGE_SIZE                       (0x400)//1kb per Page

#ifdef FIRMWARE_NON_BOOT_SOURCE
/*Define for firmware not use Bootloader*/
#define FW_START_ADDR                   FLASH_BASE_ADDR
#define FW_END_ADDR                     FLASH_BASE_END_ADDR
#define FW_SIZE                         FLASH_BASE_END_ADDR - FLASH_BASE_ADDR + 1

#define FW_DECRIP_SIZE                  0x400//65k byte for Log
#define FW_DECRIP_START_ADDR            (FLASH_BASE_END_ADDR - FW_DECRIP_SIZE + 1)
#define FW_DECRIP_END_ADDR              FLASH_BASE_END_ADDR

#define FLASH_START_ADDR                FW_START_ADDR
#endif/*FIRMWARE_WITH_BOOT_SOURCE*/

#ifdef BOOTLOADER_SOURCE
/*Define for bootloader firmware*/
#define BOOTLOADER_SIZE                 0x00004000/*16KB bootloader*/
#define BOOTLOADER_START_ADDR           FLASH_BASE_ADDR
#define BOOTLOADER_END_ADDR             FLASH_BASE_ADDR + BOOTLOADER_SIZE - 1

#define FW_DECRIP_SIZE                  0x400
#define FW_DECRIP_START_ADDR            (FLASH_BASE_END_ADDR - FW_DECRIP_SIZE + 1)
#define FW_DECRIP_END_ADDR              FLASH_BASE_END_ADDR

#define FW_START_ADDR                   BOOTLOADER_END_ADDR + 1
#define FW_END_ADDR                     FLASH_BASE_END_ADDR

#define FLASH_START_ADDR                BOOTLOADER_START_ADDR

#endif/*BOOTLOADER_SOURCE*/

#ifdef FIRMWARE_WITH_BOOT_SOURCE
/*Define for firmware use Bootloader*/
#define BOOTLOADER_SIZE                 0x00004000/*16KB bootloader*/
#define BOOTLOADER_START_ADDR           FLASH_BASE_ADDR
#define BOOTLOADER_END_ADDR             FLASH_BASE_ADDR + BOOTLOADER_SIZE - 1

#define FW_START_ADDR                   BOOTLOADER_END_ADDR + 1
#define FW_END_ADDR                     FLASH_BASE_END_ADDR
#define FW_SIZE                         FW_END_ADDR - FW_START_ADDR + 1

#define FW_DECRIP_SIZE                  0x400
#define FW_DECRIP_START_ADDR            (FLASH_BASE_END_ADDR - FW_DECRIP_SIZE + 1)
#define FW_DECRIP_END_ADDR              FLASH_BASE_END_ADDR

#define FLASH_START_ADDR                FW_START_ADDR

#endif/*FIRMWARE_WITH_BOOT_SOURCE*/

#endif/*__MEMORYMAP_H__*/