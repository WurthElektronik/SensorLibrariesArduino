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
 * COPYRIGHT (c) 2021 Würth Elektronik eiSos GmbH & Co. KG
 *
 ***************************************************************************************************
 **/

#include "WSEN_TIDS.h"

/**
   @brief  Initialize the I2C Interface
   @param  I2C address
   @retval Error Code
*/
int Sensor_TIDS::init(int address)
{
  return I2CInit(address);
}

/**
   @brief   Returns the device ID for this sensor
   @retval  Value of DEVICE_ID
*/
int Sensor_TIDS::get_DeviceID()
{
  uint8_t devID;

  if (TIDS_getDeviceID(&devID) == WE_SUCCESS)
  {
    return devID;
  }
  return WE_FAIL;
}

/**
   @brief  Setting up the output data rate for the continuous mode
   @retval Error Code
*/
int Sensor_TIDS::Select_ODR()
{

  switch (ODR)
  {
    case 200:
    {
      TIDS_setOutputDataRate(TIDS_ODR_200HZ);
      TIDS_setContinuousMode(TIDS_enable);
      break;
    }

    case 100:
    {
      TIDS_setOutputDataRate(TIDS_ODR_100HZ);
      TIDS_setContinuousMode(TIDS_enable);
      break;
    }

    case 50:
    {
      TIDS_setOutputDataRate(TIDS_ODR_50HZ);
      TIDS_setContinuousMode(TIDS_enable);
      break;
    }

    case 25:
    {
      TIDS_setOutputDataRate(TIDS_ODR_25HZ);
      TIDS_setContinuousMode(TIDS_enable);
      break;
    }

    case 1:
    {
      TIDS_setContinuousMode(TIDS_enable); // Low ODR bit is enabled, ODR 1 Hz
      break;
    }

    default:
    {
      return WE_FAIL;
    }
  }
  return WE_SUCCESS;
}

/**
   @brief   Performing the power-down (by setting the bit FREERUN
            in the CTRL register to '0')
*/
void Sensor_TIDS::power_down()
{
  TIDS_setBlockDataUpdate(TIDS_enable);
  TIDS_setAutoIncrement(TIDS_enable);
  TIDS_setContinuousMode(TIDS_disable);
}

/**
   @brief   Enables single data aquisition of temperature
*/
void Sensor_TIDS::oneshot()
{
  TIDS_setBlockDataUpdate(TIDS_enable);
  TIDS_setAutoIncrement(TIDS_enable);
  TIDS_setSingleConvMode(TIDS_enable); // enable one shot bit

  delay(5);
}

/**
   @brief   Configuring a software reset procedure
            Necessary before requesting a new temperature
*/
void Sensor_TIDS::SW_RESET()
{
  TIDS_setSwReset(TIDS_enable);
  delay(12);
  TIDS_setSwReset(TIDS_disable);
  delay(12);
}

/**
   @brief   Get the software reset state
   @retval Error Code
*/
int Sensor_TIDS::get_SW_RESET()
{
  TIDS_state_t swRstReg;
  TIDS_getSwReset(&swRstReg);
  return swRstReg;
}

/**
   @brief  Read and calculate the temperature in °C
   @retval temperature in °C
*/
float Sensor_TIDS::read_temperature()
{
  float float_temp;
  TIDS_getRAWTemperature(&rawTemp);

  if (rawTemp > 32767)
  {
    T_neg = rawTemp - 32768;
    float_temp = (float)(0 - 32768 + T_neg)/100;
  }
  else
  {
    float_temp = (float)rawTemp/100;
  }

  return float_temp;
}

/**
   @brief  Read and calculate the temperature in Fahrenheit
   @retval temperature in Fahrenheit
*/
float Sensor_TIDS::read_temp_fahrenheit()
{
  float temp_Celsius = read_temperature();
  float temp_fahrenheit = temp_Celsius * 1.8 + 32;
  return temp_fahrenheit;
}

/**
   @brief   Performing a single measurement of temperature

*/
void Sensor_TIDS::set_single_conversion()
{
  power_down();
  SW_RESET();
  oneshot();
}

/**
   @brief   Checking if BUSY Bit stays '1' during single measurement
   @retval  Error Code
*/
int Sensor_TIDS::is_ready_to_read()
{
  TIDS_state_t state;
  int result = TIDS_getBusyStatus(&state);

 if(result == WE_FAIL) { 
  return WE_FAIL;
  } else {
    return state;
  }

}

/**
   @brief   Configuring  the sensor in the continuous mode by setting
            the FREERUN bit to '1'

            The measurement rate is defined by the user selectable ODR.
*/
void Sensor_TIDS::set_continuous_mode(int _ODR)
{
  ODR = _ODR;
  power_down();
  SW_RESET();
  Select_ODR();
}

/**
  @brief  Set temperature high limit
  @param  Temperature High limit as register value
  @retval None
*/
void Sensor_TIDS::set_Temp_High_Limit(uint8_t T_H_Limit)
{
  TIDS_setTempHighLimit(T_H_Limit);
}

/**
  @brief  Get temperature high limit
  @retval Error code
*/
int Sensor_TIDS::get_Temp_High_Limit()
{
  uint8_t hLimit;
  TIDS_getTempHighLimit(&hLimit);
  return hLimit;
}

/**
  @brief  Get threshold temperature high limit in °C
  @retval Error code
*/
float Sensor_TIDS::get_Threshold_High_Limit()
{
  uint8_t hLimit = get_Temp_High_Limit();
  float threshold = (hLimit - 63) * 0.64;
  return threshold;
}

/**
  @brief  Set temperature low limit
  @param  Temperature low limit as register value
  @retval None
*/
void Sensor_TIDS::set_Temp_Low_Limit(uint8_t T_L_Limit)
{
  TIDS_setTempLowLimit(T_L_Limit);
}

/**
  @brief  Get temperature low limit 
  @retval Error code
*/
int Sensor_TIDS::get_Temp_Low_Limit()
{
  uint8_t lLimit;
  TIDS_getTempLowLimit(&lLimit);
  return lLimit;
}

/**
  @brief  Get threshold temperature low limit in °C
  @retval Error code
*/
float Sensor_TIDS::get_Threshold_Low_Limit()
{
  uint8_t lLimit = get_Temp_Low_Limit();
  float threshold = (lLimit - 63) * 0.64;
  return threshold;
}
