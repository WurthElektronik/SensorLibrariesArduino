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
int Sensor_PADS::power_down()
{
  ODR = 0;
  
  if (WE_FAIL == PADS_setBlockDataUpdate(PADS_enable))
  {
	  return WE_FAIL;
  }
  if (WE_FAIL == PADS_setAutoIncrement(PADS_enable))
  {
	  return WE_FAIL;
  }
   if (WE_FAIL == select_ODR())
  {
	  return WE_FAIL;
  }
  
    return WE_SUCCESS;
}

/**
   @brief   Configure a software reset procedure
*/
int Sensor_PADS::SW_RESET()
{
   if (WE_FAIL == PADS_setSwreset(PADS_enable))
   {
	  return WE_FAIL;
  }
  return WE_SUCCESS;
}

/**
   @brief   Enable single data aquisition of temperature and pressure
*/
int Sensor_PADS::oneshot()
{
  if (WE_FAIL == PADS_setBlockDataUpdate(PADS_enable))
  {
	  return WE_FAIL;
  }
  if (WE_FAIL == PADS_setAutoIncrement(PADS_enable))
  {
	  return WE_FAIL;
  }
  if (WE_FAIL == PADS_setSingleConvMode(PADS_enable)) // enable one shot bit
  {
	  return WE_FAIL;
  }

  delay(5);
  
  return WE_SUCCESS;
}


/**
   @brief   Check if new pressure measurement is available based on P_DA and T_DA
   @retval  Error Code
*/

int Sensor_PADS::ready_to_read(PADS_state_t *stateTemperature, PADS_state_t *statePressure)
{
  int result = PADS_getStatusDrdy(stateTemperature, statePressure);
  if(result == WE_FAIL) 
  {
    return WE_FAIL;
  }
  else
  {
    return WE_SUCCESS;
  }  
}


/**
   @brief   Check if new temperature measurement is available based on T_DA only!
   This function must only be called when no pressure data shall be read. use ready_to_read if both temperature and pressure data shall be read.
   @retval  Error Code
*/

int Sensor_PADS::temp_ready_to_read()
{
  PADS_state_t state;
  int result = PADS_getTempStatus(&state);

  if(result == WE_FAIL) 
  { 
    return WE_FAIL;
  } 
  else
  {
    return state;
  }
}



/**
   @brief   Check if new temperature measurement is available based on P_DA only!
	This function must only be called when no temperature data shall be read. use ready_to_read if both temperature and pressure data shall be read.
   @retval  Error Code
*/
int Sensor_PADS::pressure_ready_to_read()
{
  PADS_state_t state;
  int result = PADS_getPresStatus(&state);
  
  if(result == WE_FAIL) 
  {
    return WE_FAIL;
  }
  else
  {
    return state;
  }  
}


/**
   @brief  Read and calculate the temperature
   @retval  temperature in float
*/
int Sensor_PADS::read_temperature(float *temperature)
{
  float float_temp;
  if (WE_FAIL == PADS_getRAWTemperature(&rawTemp))
  {
	return WE_FAIL;
  }  

  if (rawTemp > 32767)
  {
    T_neg = rawTemp - 32768;
    float_temp = (float)(0 - 32768 + T_neg)/100;
  }
  else
  {
    float_temp = (float)rawTemp/100;
  }

  *temperature = float_temp;
  
  return WE_SUCCESS;
}

/**
   @brief  Read and calculate the pressure
   @retval pressure in float
*/
int Sensor_PADS::read_pressure(float *pressure)
{
  float float_pressure;
  if (WE_FAIL == PADS_getPressure(&float_pressure))
  {
	  return WE_FAIL;
  }
  
  *pressure = float_pressure;   
  return WE_SUCCESS;
}

/**
* @brief  Set the power mode of the sensor [Low noise]
* @retval Error code
*/
int Sensor_PADS::set_low_noise_mode()
{
  if (WE_FAIL == PADS_setPowerMode(PADS_lowNoise))
  {
	  return WE_FAIL;
  }
  
  return WE_SUCCESS;
}

/**
* @brief  Set the low pass filter configuration applied only to the pressure data
* @retval Error code
*/

int Sensor_PADS::set_low_pass_configuration()
{
  if (WE_FAIL == PADS_setLowPassFilterConf(lPfilterBW2))
  {
	  return WE_FAIL;
  }
  
  return WE_SUCCESS;
}

/**
* @brief  Set the low pass filter state
* @retval Error code
*/

int Sensor_PADS::set_low_pass_filter()
{
  if (WE_FAIL == PADS_setLowPassFilter(PADS_enable))
    {
	  return WE_FAIL;
  }
  
  return WE_SUCCESS;
}

/**
   @brief   Performing a single measurement of temperature and pressure
*/
int Sensor_PADS::set_single_conversion()
{
  if (WE_FAIL == power_down())
  {
	 return WE_FAIL;
  }
  if (WE_FAIL == oneshot())
  {
	return WE_FAIL;
  }
  
  return WE_SUCCESS;

}

/**
   @brief   Configuring  the sensor in the continuous mode 
            The measurement rate is defined by the user selectable ODR.
*/
int Sensor_PADS::set_continuous_mode(int _ODR)
{
  ODR = _ODR;
  if (WE_FAIL == set_low_noise_mode())
  {
	return WE_FAIL;
  }
  if (WE_FAIL == set_low_pass_configuration())
  {
	return WE_FAIL;
  }
  if (WE_FAIL == select_ODR())
  {
	return WE_FAIL;
  }
  
  return WE_SUCCESS;
}

/**
   @brief   Set the FIFO mode
*/
int Sensor_PADS::set_FIFO_mode(int fifoMode)
{
  if (WE_FAIL == PADS_setFifoMode((PADS_fifo_mode_t)fifoMode))
  {
	return WE_FAIL;
  }
  
  return WE_SUCCESS;
}

/**
  @brief  Get the FIFO mode
  @retval Error code
*/
int Sensor_PADS::get_FIFO_mode(int *mode)
{
  PADS_fifo_mode_t fifoMode;
  if (WE_FAIL == PADS_getFifoMode(&fifoMode))
  {
	return WE_FAIL;
  }
  
  *mode = fifoMode;
  return WE_SUCCESS;

}

/**
   @brief  Read and calculate the temperature in the FIFO buffer
   @retval  temperature in float
*/

int Sensor_PADS::read_FIFO_temperature(float *temperature)
{
  float float_temp;

  if (WE_FAIL == PADS_getFifoRAWTemperature(&rawTemp))
  {
	return WE_FAIL;
  }

  if (rawTemp > 32767)
  {
    T_neg = rawTemp - 32768;
    float_temp = (float)(0 - 32768 + T_neg)/100;
  }
  else
  {
    float_temp = (float)rawTemp/100;
  }

  *temperature = float_temp;
  return WE_SUCCESS;
}

/**
   @brief  Read and calculate the pressure in the FIFO buffer
   @retval  pressure in kPa
*/

int Sensor_PADS::read_FIFO_pressure(float *pressure)
{
  float float_pressure;
  if (WE_FAIL == PADS_getFifoPressure(&float_pressure))
  {
	return WE_FAIL;
  }
  *pressure = float_pressure;
  return WE_SUCCESS;
}

/**
   @brief  Read the fifo fill level
   @retval Error code
*/
int Sensor_PADS::get_FIFO_fill_level(int *lvl)
{
  uint8_t fifoLevel;
  if (WE_FAIL == PADS_getFifoFillLevel(&fifoLevel))
  {
	return WE_FAIL;
  }
  *lvl = fifoLevel;
  return WE_SUCCESS;
}
