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

#include "WSEN_PDUS.h"
#include <stdint.h>


/**
* @brief  Initialize the I2C Interface
* @param  I2C address
* @retval Error Code
*/
int Sensor_PDUS::init(int address)
{
  return I2CInit(address);
}

/**
* @brief  Read the raw pressure and temperature   
* @retval Digital values
*/
 int Sensor_PDUS::get_RawPresAndTemp(uint16_t *rawPres, uint16_t *rawTemp)
 {
    uint8_t data[4] = {0, 0, 0, 0};

    I2C_read(data, 4); // bytesToRead = 4

    *rawPres = data[0]<<8; 
    *rawPres |= data[1];

    *rawTemp = data[2]<<8;
    *rawTemp |= data[3];

    return WE_SUCCESS;

 }


/**
* @brief  Read the pressure and temperature values
* @param  pdus sensor type (i.e. pressure ranges) for internal conversion of pressure and temperature
* @param  Pointer to pressure value
* @param  Pointer to temperature value
* @retval Error code
*/
int Sensor_PDUS::getPresAndTemp(PDUS_Sensor_Type typ, float *presskPa, float *tempDeg)
{ 
  uint16_t rawPres = 0;
  
  uint16_t rawTemp = 0;
  
  float temporary = 0;

  get_RawPresAndTemp(&rawPres, &rawTemp);

  
  /* calculate Temperature */
  temporary = (float)(rawTemp) - T_MIN_VAL_PDUS;
  *tempDeg = ((temporary * 4.272) / (1000));


  /* calculate Pressure */
  /* perform conversion regarding sensor sub-type */
  switch (typ)
  {
  case pdus0:
    temporary = rawPres - P_MIN_VAL_PDUS;
    *presskPa = (((float)temporary * 7.63) / (1000000)) - 0.1;
    break;
  case pdus1:
    temporary = rawPres - P_MIN_VAL_PDUS;
    *presskPa = (((float)temporary * 7.63) / (100000)) - 1;
    break;
  case pdus2:
    temporary = rawPres - P_MIN_VAL_PDUS;
    *presskPa = (((float)temporary * 7.63) / (10000)) - 10;
    break;
  case pdus3:
    temporary = rawPres - P_MIN_VAL_PDUS;
    *presskPa = (((float)temporary * 3.815) / (1000));
    break;
  case pdus4:
    temporary = rawPres - P_MIN_VAL_PDUS;
    *presskPa = (((float)temporary * 4.196) / (100)) -100;
    break;
  default:
    return WE_FAIL;
  }

  return WE_SUCCESS;
}



