/**
 ***************************************************************************************************
 * This file is part of Sensors SDK:
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
 * COPYRIGHT (c) 2019 Würth Elektronik eiSos GmbH & Co. KG
 *
 ***************************************************************************************************
 **/

#ifndef WSEN_PDUS_H
#define WSEN_PDUS_H

#include "ArduinoPlatform.h"

#define PDUS_ADDRESS_I2C (uint8_t)0x78

  /* the PDUS sensor has no registers to request. It will automatically send up to 4 bytes as any request to it's PDUS_ADDRESS_I2C */

#define P_MIN_VAL_PDUS (uint16_t)3277 /* minimum raw value for pressure */
#define T_MIN_VAL_PDUS (uint16_t)8192 /* minimum raw value for temperature in degree celsius */

  typedef enum
  {
    pdus0, /*2513130810001  Range =  -0.1 to +0.1 kPa */
    pdus1, /*2513130810101  Range =  -1 to +1 kPa */
    pdus2, /*2513130810201  Range =  -10 to +10 kPa */
    pdus3, /*2513130810301  Range =   0 to 100 kPa */
    pdus4, /*2513130810401  Range =  -100 to +1000 kPa */
    pdus5, /*2513130815401  Range =  0 to +1500 kPa */
  } PDUS_Sensor_Type;
  
class Sensor_PDUS
{

public:
   int init(int address);

   int get_RawPresAndTemp(uint16_t *rawPres, uint16_t *rawTemp);
  
   int getPresAndTemp(PDUS_Sensor_Type typ, float *presskPa, float *tempDeg);
};

#endif
