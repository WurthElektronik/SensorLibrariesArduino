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

    if (ISDS_getDeviceID(&devID) == WE_SUCCESS)
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
            ISDS_setFifoOutputDataRate(ISDS_fifoOdrOff);
            break;
        }

        case 1:
        {
            ISDS_setFifoOutputDataRate(ISDS_fifoOdr12Hz5);
            break;
        }

        case 2:
        {
            ISDS_setFifoOutputDataRate(ISDS_fifoOdr26Hz);
            break;
        }

        case 3:
        {
            ISDS_setFifoOutputDataRate(ISDS_fifoOdr52Hz);
            break;
        }

        case 4:
        {
            ISDS_setFifoOutputDataRate(ISDS_fifoOdr104Hz);
            break;
        }

        case 5:
        {
            ISDS_setFifoOutputDataRate(ISDS_fifoOdr208Hz);
            break;
        }

        case 6:
        {
            ISDS_setFifoOutputDataRate(ISDS_fifoOdr416Hz);
            break;
        }

        case 7:
        {
            ISDS_setFifoOutputDataRate(ISDS_fifoOdr833Hz);
            break;
        }

        case 8:
        {
            ISDS_setFifoOutputDataRate(ISDS_fifoOdr1k66Hz);
            break;
        }

        case 9:
        {
            ISDS_setFifoOutputDataRate(ISDS_fifoOdr3k33Hz);
            break;
        }

        case 10:
        {
            ISDS_setFifoOutputDataRate(ISDS_fifoOdr6k66Hz);
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
void Sensor_ISDS::power_down()
{
    ISDS_enableBlockDataUpdate(ISDS_disable);
    ISDS_setAccOutputDataRate(ISDS_accOdrOff);
    ISDS_setGyroOutputDataRate(ISDS_gyroOdrOff);
}

/**
   @brief   Configure a software reset procedure
*/
void Sensor_ISDS::SW_RESET()
{
    ISDS_softReset(ISDS_enable);
}

/**
   @brief   Set the mode (high performance, normal or low power)
*/
void Sensor_ISDS::set_Mode(int mode)
{
    ISDS_enableBlockDataUpdate(ISDS_enable);
    ISDS_enableAutoIncrement(ISDS_enable);
    
    /* Accelerometer 16g range */
    ISDS_setAccFullScale(ISDS_accFullScaleSixteenG);

    /* Gyroscope 2000 dps range */
    ISDS_setGyroFullScale(ISDS_gyroFullScale2000dps);

    switch (mode)
    {
        case 2://high performance
        {
            ISDS_setAccOutputDataRate(ISDS_accOdr208Hz);
            ISDS_setGyroOutputDataRate(ISDS_gyroOdr208Hz);
            ISDS_disableAccHighPerformanceMode(ISDS_disable);
            ISDS_disableGyroHighPerformanceMode(ISDS_disable);
            break;   
        }

        case 1://normal
        {
            ISDS_setAccOutputDataRate(ISDS_accOdr208Hz);
            ISDS_setGyroOutputDataRate(ISDS_gyroOdr208Hz);
            ISDS_disableAccHighPerformanceMode(ISDS_enable);
            ISDS_disableGyroHighPerformanceMode(ISDS_enable);
            break;   
        }

        case 0://low power
        default:
        {
            ISDS_setAccOutputDataRate(ISDS_accOdr52Hz);
            ISDS_setGyroOutputDataRate(ISDS_gyroOdr52Hz);
            ISDS_disableAccHighPerformanceMode(ISDS_enable);
            ISDS_disableGyroHighPerformanceMode(ISDS_enable);
            break;
        }
    }
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
    ISDS_state_t tempDrdy;
    if (WE_FAIL == ISDS_isTemperatureDataReady(&tempDrdy))
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
int16_t Sensor_ISDS::get_acceleration_X()
{
    int16_t val;
    if (ISDS_getAccelerationX_int(&val) != WE_SUCCESS)
    {
        val = 0;
    }
    return val;
}

/**
   @brief  Calculate the acceleration along the Y-axis 
   @retval Acceleration in mg
*/
int16_t Sensor_ISDS::get_acceleration_Y()
{
    int16_t val;
    if (ISDS_getAccelerationY_int(&val) != WE_SUCCESS)
    {
        val = 0;
    }
    return val;
}

/**
   @brief  Calculate the acceleration along the Z-axis 
   @retval Acceleration in mg
*/
int16_t Sensor_ISDS::get_acceleration_Z()
{
    int16_t val;
    if (ISDS_getAccelerationZ_int(&val) != WE_SUCCESS)
    {
        val = 0;
    }
    return val;
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
    if (ISDS_getAccelerations_int(X,Y,Z) == WE_FAIL)
    {
        *X = 0;
        *Y = 0;
        *Z = 0;
        return WE_FAIL;
    }
    return WE_SUCCESS;
}

/**
   @brief  Calculate the angular along the X-axis 
   @retval X-axis angular rate in [mdps]
*/
int32_t Sensor_ISDS::get_angular_rate_X()
{
    int32_t val = 0;
    /* Read gyroscope values (alternatively use ISDS_getAngularRates_int() to get values for all three axes in one go) */
    if (ISDS_getAngularRateX_int(&val) != WE_SUCCESS)
    {
        val = 0;
    }
    return val;
}

/**
   @brief  Calculate the angular along the Y-axis 
   @retval y-axis angular rate in [mdps]
*/
int32_t Sensor_ISDS::get_angular_rate_Y()
{
    int32_t val = 0;
    /* Read gyroscope values (alternatively use ISDS_getAngularRates_int() to get values for all three axes in one go) */
    if (ISDS_getAngularRateY_int(&val) != WE_SUCCESS)
    {
        val = 0;
    }
    return val;
}

/**
   @brief  Calculate the angular along the Z-axis 
   @retval z-axis angular rate in [mdps]
*/
int32_t Sensor_ISDS::get_angular_rate_Z()
{
    int32_t val = 0;
    /* Read gyroscope values (alternatively use ISDS_getAngularRates_int() to get values for all three axes in one go) */
    if (ISDS_getAngularRateZ_int(&val) != WE_SUCCESS)
    {
        val = 0;
    }
    return val;
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
        *X = 0;
        *Y = 0;
        *Z = 0;
        return WE_FAIL;
    }
    return WE_SUCCESS;
}

/**
   @brief  Calculate the temperature;
   @retval Temperature in [°C]
*/
float Sensor_ISDS::get_temperature()
{
    int16_t val = 0;
    if (ISDS_getTemperature_int(&val) != WE_SUCCESS)
    {
        val = 0;
    }

    float f = (float)val;
    return f/100.;
}

