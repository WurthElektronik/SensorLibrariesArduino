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
   @retval  Value of DEVICE_ID or error code (-1)
*/
int Sensor_TIDS::get_DeviceID()
{
  uint8_t devID;

  if (WE_SUCCESS == TIDS_getDeviceID(&devID))
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
      if(WE_FAIL == TIDS_setOutputDataRate(TIDS_ODR_200HZ))
	  {
		return WE_FAIL;
      }
      if(WE_FAIL == TIDS_setContinuousMode(TIDS_enable))
	  {
		return WE_FAIL;
      }
      break;
    }

    case 100:
    {
      if(WE_FAIL == TIDS_setOutputDataRate(TIDS_ODR_100HZ))
	  {
		return WE_FAIL;
      }
      if(WE_FAIL == TIDS_setContinuousMode(TIDS_enable))
	  {
		return WE_FAIL;
      }
      break;
    }

    case 50:
    {
      if(WE_FAIL == TIDS_setOutputDataRate(TIDS_ODR_50HZ))
	  {
		return WE_FAIL;
      }
      if(WE_FAIL == TIDS_setContinuousMode(TIDS_enable))
	  {
		return WE_FAIL;
      }
      break;
    }

    case 25:
    {
      if(WE_FAIL == TIDS_setOutputDataRate(TIDS_ODR_25HZ))
	  {
		return WE_FAIL;
      }
      if(WE_FAIL == TIDS_setContinuousMode(TIDS_enable))
	  {
		return WE_FAIL;
      }
      break;
    }

    case 1:
    {
      if(WE_FAIL == TIDS_setContinuousMode(TIDS_enable)) // Low ODR bit is enabled, ODR 1 Hz
	  {
		return WE_FAIL;
	  }
      break;
    }

	/* invalid ODR */
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
   @retval Error Code
*/
int Sensor_TIDS::power_down()
{
  if(WE_FAIL == TIDS_setBlockDataUpdate(TIDS_enable))
  {
      return WE_FAIL;
  }
	
  if(WE_FAIL == TIDS_setAutoIncrement(TIDS_enable))
  {
      return WE_FAIL;
  }
	
  if(WE_FAIL == TIDS_setContinuousMode(TIDS_disable))
  {
      return WE_FAIL;
  }
	
  return WE_SUCCESS;
}

/**
   @brief   Enables single data aquisition of temperature
  @retval Error Code
*/
int Sensor_TIDS::oneshot()
{
  if(WE_FAIL == TIDS_setBlockDataUpdate(TIDS_enable))
  {
      return WE_FAIL;
  }
  
  if(WE_FAIL == TIDS_setAutoIncrement(TIDS_enable))
  {
      return WE_FAIL;
  }
  
  if(WE_FAIL == TIDS_setSingleConvMode(TIDS_enable)) // enable one shot bit
  {
      return WE_FAIL;
  }
  
  return WE_SUCCESS;
}

/**
   @brief   Configuring a software reset procedure
            Necessary before requesting a new temperature
   @retval Error Code
*/
int Sensor_TIDS::SW_RESET()
{
  if(WE_FAIL == TIDS_setSwReset(TIDS_enable))
  {
      return WE_FAIL;
  }
  
  delay(12);
  if(WE_FAIL == TIDS_setSwReset(TIDS_disable))
  {
      return WE_FAIL;
  }
  
  delay(12);
  return WE_SUCCESS;
}

/**
   @brief   Get the software reset state
   @param sw reset register flag
   @retval Error Code
*/
int Sensor_TIDS::get_SW_RESET(int *rst)
{
  TIDS_state_t swRstReg;
  if(WE_FAIL == TIDS_getSwReset(&swRstReg))
  {
      return WE_FAIL;
  }  
  
  *rst =  (int)swRstReg;
  return WE_SUCCESS;
}

/**
   @brief  Read and calculate the temperature in °C
   @param temperature in °C
   @retval Error code
*/
int Sensor_TIDS::read_temperature(float *temp)
{
  float float_temp;
  if(WE_FAIL == TIDS_getRAWTemperature(&rawTemp))
  {
      return WE_FAIL;
  }

  if (rawTemp > 32767)
  {
    T_neg = rawTemp - 32768;
    float_temp = (float)(0 - 32768 + T_neg)/100.0f;
  }
  else
  {
    float_temp = (float)rawTemp/100.0f;
  }

  *temp = float_temp;
  return WE_SUCCESS;
}

/**
   @brief  Read and calculate the temperature in Fahrenheit
   @param temperature in Fahrenheit
   @retval Error code
*/
int Sensor_TIDS::read_temp_fahrenheit(float *temp)
{
  float temp_Celsius;
  if(WE_FAIL == read_temperature(&temp_Celsius))
  {
	return WE_FAIL;
  }
  
  float temp_fahrenheit = temp_Celsius * 1.8f + 32;
  *temp = temp_fahrenheit;
  
  return WE_SUCCESS;
}

/**
   @brief   Performing a single measurement of temperature
   @retval Error code
*/
int Sensor_TIDS::set_single_conversion()
{
  if(WE_FAIL == power_down())
  {
      return WE_FAIL;
  }
	
  if(WE_FAIL == SW_RESET())
  {
	return WE_FAIL;
  }
	
  if(WE_FAIL == oneshot())
  {
	return WE_FAIL;
  }
	
  return WE_SUCCESS;
}

/**
   @brief   Checking if BUSY Bit stays '1' during single measurement
   @retval  Error Code (-1) or DRDY bit ('1' or '0') value
*/
int Sensor_TIDS::is_ready_to_read()
{
  TIDS_state_t state;
  int result = TIDS_getBusyStatus(&state);
  
  if(WE_FAIL == result) 
  {	 
	return WE_FAIL;
  }
  else
  {
    return state;
  }
}

/**
  @brief   Configuring  the sensor in the continuous mode by setting
            the FREERUN bit to '1'

            The measurement rate is defined by the user selectable ODR.
  @param  ODR value
  @retval Error code
*/
int Sensor_TIDS::set_continuous_mode(int _ODR)
{
  ODR = _ODR;
  if(WE_FAIL == power_down())
  {
      return WE_FAIL;
  } 
  if(WE_FAIL == SW_RESET())
  {
      return WE_FAIL;
    } 
  if(WE_FAIL == Select_ODR())  
  {
      return WE_FAIL;
  }
  
  return WE_SUCCESS;
  
}

/**
  @brief  Set temperature high limit
  @param  Temperature High limit as register value
  @retval Error code
*/
int Sensor_TIDS::set_Temp_High_Limit(uint8_t T_H_Limit)
{
  if(WE_FAIL == TIDS_setTempHighLimit(T_H_Limit))
  {
      return WE_FAIL;
  }
  
  return WE_SUCCESS;
}

/**
  @brief  Get temperature high limit
  @param  Temperature limit
  @retval Error code
*/
int Sensor_TIDS::get_Temp_High_Limit(uint8_t *limit)
{
  uint8_t hLimit;
  if(WE_FAIL == TIDS_getTempHighLimit(&hLimit))
  {
      return WE_FAIL;
  }

  *limit = hLimit;  
  return WE_SUCCESS;
}


/**
  @brief  Set temperature low limit
  @param  Temperature low limit as register value
  @retval Error code
*/
int Sensor_TIDS::set_Temp_Low_Limit(uint8_t T_L_Limit)
{
  if(WE_FAIL == TIDS_setTempLowLimit(T_L_Limit))
  {
	  return WE_FAIL;
  }
  
  return WE_SUCCESS;
}

/**
  @brief  Get temperature low limit 
  @param  Temperature limit
  @retval Error code
*/
int Sensor_TIDS::get_Temp_Low_Limit(uint8_t *limit)
{
  uint8_t lLimit;
  if(WE_FAIL == TIDS_getTempLowLimit(&lLimit))
  {
	  return WE_FAIL;
  }
  
  *limit = lLimit;  
  return WE_SUCCESS;
}


/**
  @brief  Get threshold temperature high limit in °C
  @param  Temperature limit
  @retval Error code
*/
int Sensor_TIDS::get_Threshold_High_Limit(float *limit)
{
  uint8_t hLimit;  
  if(WE_FAIL == get_Temp_High_Limit(&hLimit))
  {
	  return WE_FAIL;
  }
  
  float threshold = ((hLimit - 63) * 0.64f);
  *limit = threshold;
  return WE_SUCCESS;
}


/**
  @brief  Get threshold temperature low limit in °C
  @param  Temperature limit
  @retval Error code
*/
int Sensor_TIDS::get_Threshold_Low_Limit(float *limit)
{
  uint8_t lLimit;
  if(WE_FAIL == get_Temp_Low_Limit(&lLimit))
  {
	  return WE_FAIL;
  }
  
  float threshold = ((lLimit - 63) * 0.64f);
  *limit = threshold;
}
