/**
 ***************************************************************************************************
 * This file is part of WE Sensors SDK:
 * https://www.we-online.com/sensors
 *
 * THE SOFTWARE INCLUDING THE SOURCE CODE IS PROVIDED “AS IS”. YOU ACKNOWLEDGE THAT WÜRTH ELEKTRONIK
 * EISOS MAKES NO REPRESENTATIONS AND WARRANTIES OF ANY KIND RELATED TO, BUT NOT LIMITED
 * TO THE NON-INFRINGEMENT OF THIRD PARTIES’ INTELLECTUAL PROPERTY RIGHTS OR THE
 * MERCHANTABILITY OR FITNESS FOR YOUR INTENDED PURPOSE OR USAGE. WÜRTH ELEKTRONIK EISOS DOES NOT
 * WARRANT OR REPRESENT THAT ANY LICENSE, EITHER EXPRESS OR IMPLIED, IS GRANTED UNDER ANY PATENT
 * RIGHT, COPYRIGHT, MASK WORK RIGHT, OR OTHER INTELLECTUAL PROPERTY RIGHT RELATING TO ANY
 * COMBINATION, MACHINE, OR PROCESS IN WHICH THE PRODUCT IS USED. INFORMATION PUBLISHED BY
 * WÜRTH ELEKTRONIK EISOS REGARDING THIRD-PARTY PRODUCTS OR SERVICES DOES NOT CONSTITUTE A LICENSE
 * FROM WÜRTH ELEKTRONIK EISOS TO USE SUCH PRODUCTS OR SERVICES OR A WARRANTY OR ENDORSEMENT
 * THEREOF
 *
 * THIS SOURCE CODE IS PROTECTED BY A LICENSE.
 * FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED
 * IN THE ROOT DIRECTORY OF THIS DRIVER PACKAGE.
 *
 * COPYRIGHT (c) 2023 Würth Elektronik eiSos GmbH & Co. KG
 *
 ***************************************************************************************************
 **/

#ifndef ARDUINOPLATFORM_H
#define ARDUINOPLATFORM_H

#define TIMEOUT_MS (uint16_t)100		/* 100ms */

/**         Includes         **/

#include <stdint.h>
#include <stdlib.h>

#include <Arduino.h>
#include <stdbool.h>

#define WE_SUCCESS 0
#define WE_FAIL -1

//Use SDA1 and SCL1 on Arduino Due
#if defined(__SAM3X8E__)
#define Wire Wire1
#endif

/**         Functions definition         **/

#ifdef __cplusplus
extern "C"
{
#endif

void I2CSetAddress(int address);
int I2CInit(int address);
int ReadReg(uint8_t RegAdr, int NumByteToRead, uint8_t *Data);
int WriteReg(uint8_t RegAdr, int NumByteToWrite, uint8_t *Data);
int I2C_read(uint8_t *data, int bytesToRead);

#ifdef __cplusplus
}
#endif

#endif /* ARDUINOPLATFORM_H */
