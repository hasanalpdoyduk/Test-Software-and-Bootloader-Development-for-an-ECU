/**
 * Generated 16-bit Bootloader Interface Header File
 * 
 * @file     boot_application_header.h
 * 
 * @brief    Gives boot loader access to the information stored in the header
 *           of an application image.
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


#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "boot_image.h"

#ifndef BOOT_APPLICATION_HEADER_H
#define BOOT_APPLICATION_HEADER_H

enum BOOT_APPLICATION_DETAIL_ID
{
    BOOT_APPLICATION_DETAIL_ID_VERSION_NUMBER = 0x0002
};   

bool BOOT_ApplicationDetailGet(enum BOOT_IMAGE image, enum BOOT_APPLICATION_DETAIL_ID id, uint16_t* dataBuffer, size_t bufferLength);

/* Format of the version number is
 *   0x00 (8-bit) : major (8-bit) : minor (8-bit) : patch (8-bit)
 *   i.e. 0x0001020A is version 1.2.10
 */
bool BOOT_VersionNumberGet(enum BOOT_IMAGE image, uint32_t *versionNumber);

#endif