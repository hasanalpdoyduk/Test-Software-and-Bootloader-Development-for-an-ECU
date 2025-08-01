/**
 * Generated 16-bit Bootloader Interface Header File
 * 
 * @file     boot_private.h
 * 
 * @brief    Private header file used for different internal components of the 
 *           bootloader.  Not intended for external users.
 *
 * @skipline @version    16-bit Bootloader - 1.26.0
 *
 * @skipline             Device : dsPIC33EV128GM104
*/
/*
    (c) [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS "AS IS." 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef BOOT_PRIVATE_H
#define BOOT_PRIVATE_H

#include "boot_config.h" 
#define MINIMUM_WRITE_BLOCK_SIZE 8u


#define SIZE_OF_CMD_STRUCT_0 11
struct __attribute__((__packed__)) CMD_STRUCT_0{
    uint8_t cmd;
    uint16_t dataLength;
    uint32_t unlockSequence;
    uint32_t address;
};

struct __attribute__((__packed__)) CMD_STRUCT_0_WITH_PAYLOAD{
    uint8_t cmd;
    uint16_t dataLength;
    uint32_t unlockSequence;
    uint32_t address;
    uint8_t data[BOOT_CONFIG_MAX_PACKET_SIZE - SIZE_OF_CMD_STRUCT_0];
};

struct __attribute__((__packed__)) GET_VERSION_RESPONSE{
    uint8_t cmd;
    uint16_t dataLength;
    uint32_t unlockSequence;
    uint32_t address;
    //---
    uint16_t version;
    uint16_t maxPacketLength;
    uint16_t unused1;
    uint16_t deviceId;
    uint16_t unused2;
    uint16_t eraseSize;
    uint16_t writeSize;
    uint32_t unused3;
    uint32_t userRsvdStartSddress;
    uint32_t userRsvdEndSddress;
};   
    
struct __attribute__((__packed__)) RESPONSE_TYPE_0{
    uint8_t cmd;
    uint16_t dataLength;
    uint32_t unlockSequence;
    uint32_t address;
    //---
    uint8_t success;
};
struct __attribute__((__packed__)) RESPONSE_TYPE_0_2_PAYLOAD{
    uint8_t cmd;
    uint16_t dataLength;
    uint32_t unlockSequence;
    uint32_t address;
    //---
    uint8_t success;
    uint16_t data;
};
struct __attribute__((__packed__)) RESPONSE_TYPE_0_WITH_PAYLOAD{
    uint8_t cmd;
    uint16_t dataLength;
    uint32_t unlockSequence;
    uint32_t address;
    //---
    uint8_t success;    
    uint8_t data[BOOT_CONFIG_MAX_PACKET_SIZE - SIZE_OF_CMD_STRUCT_0 - 1u];
}; 
struct __attribute__((__packed__)) GET_MEMORY_ADDRESS_RANGE_RESPONSE{
    uint8_t  cmd;
    uint16_t dataLength;  
    uint32_t unlockSequence; 
    uint32_t address; 
     uint8_t success; 
    //---
    uint32_t programFlashStart; 
    uint32_t programFlashEnd; 
};

#endif
