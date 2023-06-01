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

#include "WSEN_ISDS.h"
#include <stdint.h>

/**
   @brief  Initialize the I2C Interface
   @param  I2C address
   @retval Error Code
*/
int Sensor_ISDS::init(int address)
{
    return I2CInit(address);
}

/**
   @brief   Return the device ID for this sensor
   @retval  Value of DEVICE_ID
*/

int Sensor_ISDS::get_DeviceID()
{
    uint8_t devID;

    if (WE_SUCCESS == ISDS_getDeviceID(&devID))
    {
        return devID;
    }
	
    return WE_FAIL;
}

/**
   @brief  Set the output data rate 
   @retval Error Code
*/
int Sensor_ISDS::select_ODR(int ODR)
{
    switch (ODR)
    {
        case 0:
        {
            if (WE_FAIL == ISDS_setFifoOutputDataRate(ISDS_fifoOdrOff))
				{
        return WE_FAIL;
    }
            break;
        }

        case 1:
        {
            if (WE_FAIL == ISDS_setFifoOutputDataRate(ISDS_fifoOdr12Hz5))
				{
        return WE_FAIL;
    }
            break;
        }

        case 2:
        {
            if (WE_FAIL == ISDS_setFifoOutputDataRate(ISDS_fifoOdr26Hz))
				{
        return WE_FAIL;
    }
            break;
        }

        case 3:
        {
            if (WE_FAIL == ISDS_setFifoOutputDataRate(ISDS_fifoOdr52Hz))
				{
        return WE_FAIL;
    }
            break;
        }

        case 4:
        {
            if (WE_FAIL == ISDS_setFifoOutputDataRate(ISDS_fifoOdr104Hz))
				{
        return WE_FAIL;
    }
            break;
        }

        case 5:
        {
            if (WE_FAIL == ISDS_setFifoOutputDataRate(ISDS_fifoOdr208Hz))
				{
        return WE_FAIL;
    }
            break;
        }

        case 6:
        {
            if (WE_FAIL == ISDS_setFifoOutputDataRate(ISDS_fifoOdr416Hz))
				{
        return WE_FAIL;
    }
            break;
        }

        case 7:
        {
            if (WE_FAIL == ISDS_setFifoOutputDataRate(ISDS_fifoOdr833Hz))
				{
        return WE_FAIL;
    }
            break;
        }

        case 8:
        {
            if (WE_FAIL == ISDS_setFifoOutputDataRate(ISDS_fifoOdr1k66Hz))
				
				{
        return WE_FAIL;
    }
            break;
        }

        case 9:
        {
            if (WE_FAIL == ISDS_setFifoOutputDataRate(ISDS_fifoOdr3k33Hz))
				{
        return WE_FAIL;
    }
            break;
        }

        case 10:
        {
            if (WE_FAIL == ISDS_setFifoOutputDataRate(ISDS_fifoOdr6k66Hz))
				{
        return WE_FAIL;
    }
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
int Sensor_ISDS::power_down()
{
    if (WE_FAIL == ISDS_enableBlockDataUpdate(ISDS_disable))
	{
        return WE_FAIL;
    }
    if (WE_FAIL == ISDS_setAccOutputDataRate(ISDS_accOdrOff))
	{
        return WE_FAIL;
    }
    if (WE_FAIL == ISDS_setGyroOutputDataRate(ISDS_gyroOdrOff))
	{
        return WE_FAIL;
    }
	
	return WE_SUCCESS;
}

/**
   @brief   Configure a software reset procedure
*/
int Sensor_ISDS::SW_RESET()
{
    if (WE_FAIL == ISDS_softReset(ISDS_enable))
	{
        return WE_FAIL;
    }
	
	return WE_SUCCESS;
}

/**
   @brief   Set the mode (high performance, normal or low power)
*/
int Sensor_ISDS::set_Mode(int mode)
{
    if (WE_FAIL == ISDS_enableBlockDataUpdate(ISDS_enable))
	{
        return WE_FAIL;
    }
    if (WE_FAIL == ISDS_enableAutoIncrement(ISDS_enable))
	{
        return WE_FAIL;
    }
    
    /* Accelerometer 16g range */
    if (WE_FAIL == ISDS_setAccFullScale(ISDS_accFullScaleSixteenG))
	{
        return WE_FAIL;
    }

    /* Gyroscope 2000 dps range */
    if (WE_FAIL == ISDS_setGyroFullScale(ISDS_gyroFullScale2000dps))
	{
        return WE_FAIL;
    }

    switch (mode)
    {
        case 2://high performance
        {
            if (WE_FAIL == ISDS_setAccOutputDataRate(ISDS_accOdr208Hz))
			{
				return WE_FAIL;
			}
			if (WE_FAIL == ISDS_setGyroOutputDataRate(ISDS_gyroOdr208Hz))
			{
				return WE_FAIL;
			}
			if (WE_FAIL == ISDS_disableAccHighPerformanceMode(ISDS_disable))
			{
				return WE_FAIL;
			}
			if (WE_FAIL == ISDS_disableGyroHighPerformanceMode(ISDS_disable))
			{
				return WE_FAIL;
			}
			break;   
        }

        case 1://normal
        {
            if (WE_FAIL == ISDS_setAccOutputDataRate(ISDS_accOdr208Hz))
			{
				return WE_FAIL;
			}
			if (WE_FAIL == ISDS_setGyroOutputDataRate(ISDS_gyroOdr208Hz))
			{
				return WE_FAIL;
			}
			if (WE_FAIL == ISDS_disableAccHighPerformanceMode(ISDS_enable))
			{
				return WE_FAIL;
			}
			if (WE_FAIL == ISDS_disableGyroHighPerformanceMode(ISDS_enable))
			{
				return WE_FAIL;
			}
            break;   
		}
        

        case 0://low power
        default:
        {
            if (WE_FAIL == ISDS_setAccOutputDataRate(ISDS_accOdr52Hz))
			{
				return WE_FAIL;
			}
			if (WE_FAIL == ISDS_setGyroOutputDataRate(ISDS_gyroOdr52Hz))
			{
				return WE_FAIL;
			}
			if (WE_FAIL == ISDS_disableAccHighPerformanceMode(ISDS_enable))
			{
				return WE_FAIL;
			}
			if (WE_FAIL == ISDS_disableGyroHighPerformanceMode(ISDS_enable))
			{
				return WE_FAIL;
			}
			break;
        }
    }
	
	return WE_SUCCESS;
}

/**
   @brief   Check if new acceleration measurement is available 
   @retval  Error Code
*/
int Sensor_ISDS::is_ACC_Ready_To_Read()
{
    ISDS_state_t drdy;
    if (WE_FAIL == ISDS_isAccelerationDataReady(&drdy))
    {
        return WE_FAIL;
    }
    else
    {
        return drdy;
    }
}

/**
   @brief   Check if new gyroscope measurement is available 
   @retval  Error Code
*/
int Sensor_ISDS::is_Gyro_Ready_To_Read()
{
    ISDS_state_t drdy;
    if (WE_FAIL == ISDS_isGyroscopeDataReady(&drdy))
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
int Sensor_ISDS::is_Temp_Ready()
{
    ISDS_state_t drdy;
    if (WE_FAIL == ISDS_isTemperatureDataReady(&drdy))
    {
        return WE_FAIL;
    }
    else
    {
        return drdy;
    }
}

int Sensor_ISDS::get_StatusRegister(ISDS_status_t *status)
{

    if (WE_FAIL == ISDS_getStatusRegister(status))
    {
        return WE_FAIL;
    }
    else
    {
        return WE_SUCCESS;
    }
}


/**
   @brief  Calculate the acceleration along the X-axis 
   @retval Acceleration in mg
*/
int Sensor_ISDS::get_acceleration_X(int16_t *acc_x)
{
    int16_t val;
    if (WE_FAIL == ISDS_getAccelerationX_int(&val))
    {
        return WE_FAIL;
    }
	
    *acc_x = val;
	return WE_SUCCESS;
}

/**
   @brief  Calculate the acceleration along the Y-axis 
   @retval Acceleration in mg
*/
int Sensor_ISDS::get_acceleration_Y(int16_t *acc_y)
{
    int16_t val;
    if (WE_FAIL == ISDS_getAccelerationY_int(&val))
    {
        return WE_FAIL;
    }
	
    *acc_y = val;
	return WE_SUCCESS;
}

/**
   @brief  Calculate the acceleration along the Z-axis 
   @retval Acceleration in mg
*/
int Sensor_ISDS::get_acceleration_Z(int16_t *acc_z)
{
    int16_t val;
    if (WE_FAIL == ISDS_getAccelerationZ_int(&val))
    {
        return WE_FAIL;
    }
	
    *acc_z = val;
	return WE_SUCCESS;
}

/**
   @brief  Calculate the acceleration along all axes
   @param  X x-axis acceleration
   @param  Y y-axis acceleration
   @param  Z z-axis acceleration
   @retval Error Code
*/
int Sensor_ISDS::get_accelerations(int16_t* X, int16_t* Y, int16_t* Z)
{
    if (WE_FAIL == ISDS_getAccelerations_int(X,Y,Z))
    {
        return WE_FAIL;
    }
    return WE_SUCCESS;
}

/**
   @brief  Calculate the angular along the X-axis 
   @retval X-axis angular rate in [mdps]
*/
int Sensor_ISDS::get_angular_rate_X(int32_t *rate_x)
{
    int32_t val = 0;
    /* Read gyroscope values (alternatively use ISDS_getAngularRates_int() to get values for all three axes in one go) */
    if (WE_FAIL == ISDS_getAngularRateX_int(&val))
    {
        return WE_FAIL;
    }
    *rate_x = val;
	return WE_SUCCESS;
}

/**
   @brief  Calculate the angular along the Y-axis 
   @retval y-axis angular rate in [mdps]
*/
int Sensor_ISDS::get_angular_rate_Y(int32_t *rate_y)
{
    int32_t val = 0;
    /* Read gyroscope values (alternatively use ISDS_getAngularRates_int() to get values for all three axes in one go) */
    if (WE_FAIL == ISDS_getAngularRateY_int(&val))
    {
        return WE_FAIL;
    }
	
    *rate_y = val;
	return WE_SUCCESS;
}

/**
   @brief  Calculate the angular along the Z-axis 
   @retval z-axis angular rate in [mdps]
*/
int Sensor_ISDS::get_angular_rate_Z(int32_t *rate_z)
{
    int32_t val = 0;
    /* Read gyroscope values (alternatively use ISDS_getAngularRates_int() to get values for all three axes in one go) */
    if (WE_FAIL == ISDS_getAngularRateZ_int(&val))
    {
        return WE_FAIL;
    }
	
    *rate_z = val;
	return WE_SUCCESS;

}

/**
   @brief  Calculate the angular rates along all axes
   @param  X x-axis angular rate
   @param  Y y-axis angular rate
   @param  Z z-axis angular rate
   @retval Error Code
*/
int Sensor_ISDS::get_angular_rates(int32_t* X, int32_t* Y, int32_t* Z)
{
    if (ISDS_getAngularRates_int(X,Y,Z) == WE_FAIL)
    {
        return WE_FAIL;
    }
	
    return WE_SUCCESS;
}

/**
   @brief  Calculate the temperature;
   @retval Temperature in [°C]
*/
int Sensor_ISDS::get_temperature(float *temp)
{
    int16_t val = 0;
    if (WE_FAIL == ISDS_getTemperature_int(&val))
    {
        return WE_FAIL;
    }

    float f = (float)val;
	*temp = f/100.0f;
	return WE_SUCCESS;
}

