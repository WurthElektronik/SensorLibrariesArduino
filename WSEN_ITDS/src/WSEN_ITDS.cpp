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

#include "WSEN_ITDS.h"
#include <stdint.h>

/**
   @brief  Initialize the I2C Interface
   @param  I2C address
   @retval Error Code
*/
int Sensor_ITDS::init(int address)
{
    return I2CInit(address);
}

/**
   @brief   Return the device ID for this sensor
   @retval  Value of DEVICE_ID
*/

int Sensor_ITDS::get_DeviceID()
{
    uint8_t devID;

    if (ITDS_getDeviceID(&devID) == WE_SUCCESS)
    {
        return devID;
    }
    return WE_FAIL;
}

/**
   @brief  Set the output data rate 
   @retval Error Code
*/
int Sensor_ITDS::select_ODR()
{
    switch (ODR)
    {
        case 0:
        {
            ITDS_setOutputDataRate(ITDS_odr0);
            break;
        }

        case 1:
        {
            ITDS_setOutputDataRate(ITDS_odr1);
            break;
        }

        case 2:
        {
            ITDS_setOutputDataRate(ITDS_odr2);
            break;
        }

        case 3:
        {
            ITDS_setOutputDataRate(ITDS_odr3);
            break;
        }

        case 4:
        {
            ITDS_setOutputDataRate(ITDS_odr4);
            break;
        }

        case 5:
        {
            ITDS_setOutputDataRate(ITDS_odr5);
            break;
        }

        case 6:
        {
            ITDS_setOutputDataRate(ITDS_odr6);
            break;
        }

        case 7:
        {
            ITDS_setOutputDataRate(ITDS_odr7);
            break;
        }

        case 8:
        {
            ITDS_setOutputDataRate(ITDS_odr8);
            break;
        }

        case 9:
        {
            ITDS_setOutputDataRate(ITDS_odr9);
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
int Sensor_ITDS::power_down()
{
    ODR = 0;
    if (WE_FAIL == ITDS_setBlockDataUpdate(ITDS_enable))
	{
		return WE_FAIL;
	}
	if (WE_FAIL == ITDS_setAutoIncrement(ITDS_enable))
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
int Sensor_ITDS::SW_RESET()
{
    if (WE_FAIL == ITDS_softReset(ITDS_enable))
	{
		return WE_FAIL;
	}
	
	return WE_SUCCESS;
}

/**
   @brief   Set the high performance mode
*/
int Sensor_ITDS::set_High_Performance()
{
    if (WE_FAIL == ITDS_setBlockDataUpdate(ITDS_enable))
	{
		return WE_FAIL;
	}
    if (WE_FAIL == ITDS_setAutoIncrement(ITDS_enable))
	{
		return WE_FAIL;
	}
    if (WE_FAIL == select_ODR())
	{
		return WE_FAIL;
	}
    mode = ITDS_normalMode;

    if (WE_FAIL == ITDS_setOperatingMode(highPerformance))
	{
		return WE_FAIL;
	}
	
	return WE_SUCCESS;
}

/**
   @brief   Set the low mode 
*/
int Sensor_ITDS::set_Low_Mode()
{
    if (WE_FAIL == ITDS_setBlockDataUpdate(ITDS_enable))
	{
		return WE_FAIL;
	}
    if (WE_FAIL == ITDS_setAutoIncrement(ITDS_enable))
	{
		return WE_FAIL;
	}
    if (WE_FAIL == select_ODR())
	{
		return WE_FAIL;
	}
    mode = ITDS_lowPower;
	
     if (WE_FAIL == ITDS_setOperatingMode(normalOrLowPower))
	{
		return WE_FAIL;
	}
	if (WE_FAIL == ITDS_setpowerMode(ITDS_lowPower))
	{
		return WE_FAIL;
	}
	
	return WE_SUCCESS;
}

/**
   @brief   Set the normal mode 
*/
int Sensor_ITDS::set_Normal_Mode()
{
    if (WE_FAIL == ITDS_setBlockDataUpdate(ITDS_enable))
	{
		return WE_FAIL;
	}
    if (WE_FAIL == ITDS_setAutoIncrement(ITDS_enable))
	{
		return WE_FAIL;
	}
    if (WE_FAIL == select_ODR())
	{
		return WE_FAIL;
	}
    mode = ITDS_normalMode;
	
    if (WE_FAIL == ITDS_setOperatingMode(normalOrLowPower))
	{
		return WE_FAIL;
	}
    if (WE_FAIL == ITDS_setpowerMode(ITDS_normalMode))
	{
		return WE_FAIL;
	}
	
	return WE_SUCCESS;
}

/**
  @brief  Get the operating mode
  @retval Error code
*/
int Sensor_ITDS::get_Operating_Mode()
{
    uint8_t opmode;
    if (WE_FAIL == ITDS_getOperatingMode(&opmode))
	{
		return WE_FAIL;
	}
	
    return (int)opmode;
}

/**
  @brief  Get the power mode
  @retval Error code
*/
int Sensor_ITDS::get_Power_Mode()
{
    uint8_t powermode;
    if (WE_FAIL == ITDS_getpowerMode(&powermode))
	{
		return WE_FAIL;
	}
    return (int)powermode;
}

/**
   @brief   Select the acceleration bandwidth for the filtering path
*/
int Sensor_ITDS::set_Bandwidth(int value)
{
    if (WE_FAIL == ITDS_setFilteringCutoff((ITDS_bandwidth)value))
	{
		return WE_FAIL;
	}
	return WE_SUCCESS;
}

/**
   @brief   Set the full scale
*/
int Sensor_ITDS::set_Full_Scale(int value)
{
    full_scale = (ITDS_full_Scale)value;
    if (WE_FAIL == ITDS_setFullScale(full_scale))
	{
		return WE_FAIL;
	}
	
	return WE_SUCCESS;
}

/**
   @brief   Set the low pass filter
*/
int Sensor_ITDS::set_Low_Pass_Filter()
{
    if (WE_FAIL == ITDS_setfilterPath(lowPass))
	{
		return WE_FAIL;
	}
	return WE_SUCCESS;
}

/**
   @brief   Set the high pass filter
*/
int Sensor_ITDS::set_High_Pass_Filter()
{
    if (WE_FAIL == ITDS_setfilterPath(highPass))
	{
		return WE_FAIL;
	}
	return WE_SUCCESS;
}

/**
  @brief  Get the Sensitivity depending on the operating mode and full scale
  @retval Sensitivity float value
*/

float Sensor_ITDS::get_Sensitivity()
{
	/* these factors include already handling of 10 vs. 12 bit resolution and bit shifting */
    if (full_scale == twoG)
    {
		return 0.061f;
    }
    else if (full_scale == fourG)
    {       
		return 0.122f;
    }
    else if (full_scale == eightG)
    {       
		return 0.244f;
    }
    else if (full_scale == sixteenG)
    {
		return 0.488f;
    }
    return 0;
}

/**
   @brief   Check if new acceleration measurement is available 
   @retval  Error Code
*/
int Sensor_ITDS::is_Ready_To_Read()
{
    ITDS_state_t drdy;
    int result = ITDS_getdataReadyState(&drdy);

    if (result == WE_FAIL)
    {
        return WE_FAIL;
    }
    else
    {
        return drdy;
    }
}

/**
   @brief   Check if new temperature measurement is available 
   @retval  Error Code
*/
int Sensor_ITDS::is_Temp_Ready()
{
    ITDS_state_t tempDrdy;                    // values in output register available
    int result = ITDS_getTempDrdy(&tempDrdy); // WE_FAIL or WE_SUCCESS

    if (result == WE_FAIL)
    {
        return WE_FAIL;
    }
    else
    {
        return tempDrdy;
    }
}

/**
   @brief  Calculate the acceleration along the X-axis 
   @retval Acceleration in mg
*/
int Sensor_ITDS::get_acceleration_X(float *acc_x)
{
    int16_t XRawAcc;
    if (WE_FAIL == ITDS_getRawAccelerationX(&XRawAcc))
	{
		return WE_FAIL;
	}
	
    float XAcc = XRawAcc * get_Sensitivity();
	*acc_x = XAcc;
    return WE_SUCCESS;
}

/**
   @brief  Calculate the acceleration along the Y-axis 
   @retval Acceleration in mg
*/
int Sensor_ITDS::get_acceleration_Y(float *acc_y)
{
    int16_t YRawAcc;
    if (WE_FAIL == ITDS_getRawAccelerationY(&YRawAcc))
		{
		return WE_FAIL;
	}

    float YAcc = YRawAcc * get_Sensitivity();
	*acc_y = YAcc;
    return WE_SUCCESS;
}

/**
   @brief  Calculate the acceleration along the Z-axis 
   @retval Acceleration in mg
*/
int Sensor_ITDS::get_acceleration_Z(float *acc_z)
{
    int16_t ZRawAcc;
    if (WE_FAIL == ITDS_getRawAccelerationZ(&ZRawAcc))
		{
		return WE_FAIL;
	}

    float ZAcc = ZRawAcc * get_Sensitivity();
	*acc_z = ZAcc;
    return WE_SUCCESS;
}

/**
   @brief  Calculate the temperature; Formulas according Table 26
   @retval Temperature in °C
*/
int Sensor_ITDS::get_temperature(int *temperature)
{
    uint8_t RawTemp8;
	int Temp;
	
    if (WE_FAIL == ITDS_getTemperature8bit(&RawTemp8))
	{
		return WE_FAIL;
	}

    if (RawTemp8 > 0 && RawTemp8 <= 0x36)
    {
        Temp = (int)RawTemp8 + 25;
    }
    else
    {
        Temp = -255 + (int)RawTemp8 + 25;
    }

	*temperature = Temp;
    return WE_SUCCESS;
}

/**
   @brief  Calculate the temperature in Fahrenheit
   @retval Temperature in Fahrenheit
*/
int Sensor_ITDS::get_temp_Fahrenheit(int *temperature)
{
    int temp_Celsius;
	if (WE_FAIL == get_temperature(&temp_Celsius))
	{
		return WE_FAIL;
	}
	
    int temp_Fahrenheit = temp_Celsius * 1.8 + 32;	
	*temperature = temp_Fahrenheit;
    return WE_SUCCESS;
}

/**
   @brief   Set the FIFO mode
*/

int Sensor_ITDS::set_FIFO_mode(int fifoMode)
{
    if (WE_FAIL == ITDS_setFifoMode((ITDS_Fifo_Mode)fifoMode))
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
  @brief  Get the FIFO mode
  @retval Error code
*/
int Sensor_ITDS::get_FIFO_mode(int *mode)
{
    ITDS_Fifo_Mode fifoMode;
    if (WE_FAIL == ITDS_getFifoMode(&fifoMode))
	{
		return WE_FAIL;
	}
	
	*mode = fifoMode;
    return WE_SUCCESS;
}

/**
  @brief  Get the FIFO fill level
  @retval Error code
*/
int Sensor_ITDS::get_FIFO_Fill_Level(int *lvl)
{
    uint8_t fifoFill;
    if (WE_FAIL == ITDS_getFifoFillLevel(&fifoFill))
	{
		return WE_FAIL;
	}
	
	*lvl = fifoFill;
    return  WE_SUCCESS;
}
