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
 * COPYRIGHT (c) 2021 Würth Elektronik eiSos GmbH & Co. KG
 *
 ***************************************************************************************************
 **/

#include "WSEN_PADS.h"
#include <stdint.h>

/**
   @brief  Initialize the I2C Interface
   @param  I2C address
   @retval Error Code
*/
int Sensor_PADS::init(int address)
{
  return I2CInit(address);
}

/**
   @brief   Return the device ID for this sensor
   @retval  Value of DEVICE_ID
*/
int Sensor_PADS::get_DeviceID()
{
  uint8_t devID;

  if (PADS_getDeviceID(&devID) == WE_SUCCESS)
  {
    return devID;
  }
  return WE_FAIL;
}

/**
   @brief  Set the output data rate 
   @retval Error Code
*/
int Sensor_PADS::select_ODR()
{

  switch (ODR)
  {

    case 200:
    {
      PADS_setOutputDataRate(PADS_ODR_200HZ);
      break;
    }

    case 100:
    {
      PADS_setOutputDataRate(PADS_ODR_100HZ);
      break;
    }

    case 75:
    {
      PADS_setOutputDataRate(PADS_ODR_75HZ);
      break;
    }

    case 50:
    {
      PADS_setOutputDataRate(PADS_ODR_50HZ);
      break;
    }

    case 25:
    {
      PADS_setOutputDataRate(PADS_ODR_25HZ);
      break;
    }

    case 10:
    {
      PADS_setOutputDataRate(PADS_ODR_10HZ);
      break;
    }

    case 1:
    {
      PADS_setOutputDataRate(PADS_ODR_1HZ); // Low ODR bit is enabled, ODR 1 Hz
      break;
    }

    case 0:
    {
      PADS_setOutputDataRate(PADS_ODR_PowerDown);
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
   @brief   Perform the power-down 
*/
void Sensor_PADS::power_down()
{
  ODR = 0;
  PADS_setBlockDataUpdate(PADS_enable);
  PADS_setAutoIncrement(PADS_enable);
  select_ODR();
}

/**
   @brief   Configure a software reset procedure
*/
void Sensor_PADS::SW_RESET()
{
  PADS_setSwreset(PADS_enable);
}

/**
   @brief   Enable single data aquisition of temperature and pressure
*/
void Sensor_PADS::oneshot()
{
  PADS_setBlockDataUpdate(PADS_enable);
  PADS_setAutoIncrement(PADS_enable);
  PADS_setSingleConvMode(PADS_enable); // enable one shot bit

  delay(5);
}

/**
   @brief   Check if new temperature measurement is available based on T_DA 
   @retval  Error Code
*/

int Sensor_PADS::temp_ready_to_read()
{
  PADS_state_t state;
  int result = PADS_getTempStatus(&state);

  if(result == WE_FAIL) { 
    return WE_FAIL;
  } else {
    return state;
  }
}

/**
   @brief   Check if new pressure measurement is available based on P_DA 
   @retval  Error Code
*/

int Sensor_PADS::pressure_ready_to_read()
{
  PADS_state_t state;
  int result = PADS_getPresStatus(&state);
  
  if(result == WE_FAIL) { 
    return WE_FAIL;
  } else {
    return state;
  }
  
}

/**
   @brief  Read and calculate the temperature
   @retval  temperature in float
*/
float Sensor_PADS::read_temperature()
{
  float float_temp;
  PADS_getRAWTemperature(&rawTemp);

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
   @brief  Read and calculate the pressure
   @retval pressure in float
*/
float Sensor_PADS::read_pressure()
{
  float float_pressure;
  PADS_getPressure(&float_pressure);

  return float_pressure;
}

/**
* @brief  Set the power mode of the sensor [Low noise]
* @retval Error code
*/
void Sensor_PADS::set_low_noise_mode()
{
  PADS_setPowerMode(PADS_lowNoise);
}

/**
* @brief  Set the low pass filter configuration applied only to the pressure data
* @retval Error code
*/

void Sensor_PADS::set_low_pass_configuration()
{
  PADS_setLowPassFilterConf(lPfilterBW2);
}

/**
* @brief  Set the low pass filter state
* @retval Error code
*/

void Sensor_PADS::set_low_pass_filter()
{
  PADS_setLowPassFilter(PADS_enable);
}

/**
   @brief   Performing a single measurement of temperature and pressure
*/
void Sensor_PADS::set_single_conversion()
{
  power_down();
  oneshot();
}

/**
   @brief   Configuring  the sensor in the continuous mode 
            The measurement rate is defined by the user selectable ODR.
*/
void Sensor_PADS::set_continuous_mode(int _ODR)
{
  ODR = _ODR;
  set_low_noise_mode();
  set_low_pass_configuration();
  select_ODR();
}

/**
   @brief   Set the FIFO mode
*/
void Sensor_PADS::set_FIFO_mode(int fifoMode)
{
  PADS_setFifoMode((PADS_fifo_mode_t)fifoMode);
}

/**
  @brief  Get the FIFO mode
  @retval Error code
*/
int Sensor_PADS::get_FIFO_mode()
{
  PADS_fifo_mode_t fifoMode;
  PADS_getFifoMode(&fifoMode);
  return fifoMode;
}

/**
   @brief  Read and calculate the temperature in the FIFO buffer
   @retval  temperature in float
*/

float Sensor_PADS::read_FIFO_temperature()
{
  float float_temp;

  PADS_getFifoRAWTemperature(&rawTemp);

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
   @brief  Read and calculate the pressure in the FIFO buffer
   @retval  pressure in kPa
*/

float Sensor_PADS::read_FIFO_pressure()
{
  float float_pressure;
  PADS_getFifoPressure(&float_pressure);

  return float_pressure;
}

/**
   @brief  Read the fifo fill level
   @retval Error code
*/
int Sensor_PADS::get_FIFO_fill_level()
{
  uint8_t fifoLevel;
  PADS_getFifoFillLevel(&fifoLevel);
  return fifoLevel;
}
