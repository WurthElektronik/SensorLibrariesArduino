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
void Sensor_ITDS::power_down()
{
    ODR = 0;
    ITDS_setBlockDataUpdate(ITDS_enable);
    ITDS_setAutoIncrement(ITDS_enable);
    select_ODR();
}

/**
   @brief   Configure a software reset procedure
*/
void Sensor_ITDS::SW_RESET()
{
    ITDS_softReset(ITDS_enable);
}

/**
   @brief   Set the high performance mode
*/
void Sensor_ITDS::set_High_Performance()
{
    ITDS_setBlockDataUpdate(ITDS_enable);
    ITDS_setAutoIncrement(ITDS_enable);
    select_ODR();
    mode = ITDS_normalMode;

    ITDS_setOperatingMode(highPerformance);
}

/**
   @brief   Set the low mode 
*/
void Sensor_ITDS::set_Low_Mode()
{
    ITDS_setBlockDataUpdate(ITDS_enable);
    ITDS_setAutoIncrement(ITDS_enable);
    select_ODR();
    mode = ITDS_lowPower;
    ITDS_setOperatingMode(normalOrLowPower);
    ITDS_setpowerMode(ITDS_lowPower);
}

/**
   @brief   Set the normal mode 
*/
void Sensor_ITDS::set_Normal_Mode()
{

    ITDS_setBlockDataUpdate(ITDS_enable);
    ITDS_setAutoIncrement(ITDS_enable);
    select_ODR();
    mode = ITDS_normalMode;
    ITDS_setOperatingMode(normalOrLowPower);
    ITDS_setpowerMode(ITDS_normalMode);
}

/**
  @brief  Get the operating mode
  @retval Error code
*/
int Sensor_ITDS::get_Operating_Mode()
{
    uint8_t opmode;
    ITDS_getOperatingMode(&opmode);
    return opmode;
}

/**
  @brief  Get the power mode
  @retval Error code
*/
int Sensor_ITDS::get_Power_Mode()
{
    uint8_t powermode;
    ITDS_getpowerMode(&powermode);
    return powermode;
}

/**
   @brief   Select the acceleration bandwidth for the filtering path
*/
void Sensor_ITDS::set_Bandwidth(int value)
{
    ITDS_setFilteringCutoff((ITDS_bandwidth)value);
}

/**
   @brief   Set the full scale
*/
void Sensor_ITDS::set_Full_Scale(int value)
{
    full_scale = (ITDS_full_Scale)value;
    ITDS_setFullScale(full_scale);
}

/**
   @brief   Set the low pass filter
*/
void Sensor_ITDS::set_Low_Pass_Filter()
{
    ITDS_setfilterPath(lowPass);
}

/**
   @brief   Set the high pass filter
*/
void Sensor_ITDS::set_High_Pass_Filter()
{
    ITDS_setfilterPath(highPass);
}

/**
  @brief  Get the Sensitivity depending on the operating mode and full scale
  @retval Sensitivity float value
*/

float Sensor_ITDS::get_Sensitivity()
{
    const int isLowPower = (get_Operating_Mode() == normalOrLowPower) & (get_Power_Mode() == ITDS_lowPower);

    if (full_scale == twoG)
    {

        if (isLowPower)
        {
            return 0.976;
        }
        else
        {
            return 0.244;
        }
    }
    else if (full_scale == fourG)
    {
        if (isLowPower)
        {
            return 1.952;
        }
        else
        {
            return 0.488;
        }
    }
    else if (full_scale == eightG)
    {
        if (isLowPower)
        {
            return 3.904;
        }
        else
        {
            return 0.976;
        }
    }
    else if (full_scale == sixteenG)
    {

        if (isLowPower)
        {
            return 7.808;
        }
        else
        {
            return 1.952;
        }
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
float Sensor_ITDS::get_acceleration_X()
{
    int16_t XRawAcc;
    ITDS_getRawAccelerationX(&XRawAcc);
    int XShift = 0;
    if (mode == ITDS_lowPower)
    {
        XShift = XRawAcc / 16;
    }
    else
    {
        XShift = XRawAcc / 4;
    }

    float XAcc = XShift * get_Sensitivity();
    return XAcc;
}

/**
   @brief  Calculate the acceleration along the Y-axis 
   @retval Acceleration in mg
*/
float Sensor_ITDS::get_acceleration_Y()
{
    int16_t YRawAcc;
    ITDS_getRawAccelerationY(&YRawAcc);
    int YShift = 0;
    if (mode == ITDS_lowPower)
    {
        YShift = YRawAcc / 16;
    }
    else
    {
        YShift = YRawAcc / 4;
    }
    float YAcc = YShift * get_Sensitivity();
    return YAcc;
}

/**
   @brief  Calculate the acceleration along the Z-axis 
   @retval Acceleration in mg
*/
float Sensor_ITDS::get_acceleration_Z()
{
    int16_t ZRawAcc;
    ITDS_getRawAccelerationZ(&ZRawAcc);
    int ZShift = 0;
    if (mode == ITDS_lowPower)
    {
        ZShift = ZRawAcc / 16;
    }
    else
    {
        ZShift = ZRawAcc / 4;
    }
    float ZAcc = ZShift * get_Sensitivity();
    return ZAcc;
}

/**
   @brief  Calculate the temperature; Formulas according Table 26
   @retval Temperature in °C
*/
int Sensor_ITDS::get_temperature()
{
    uint8_t RawTemp8;
    ITDS_getTemperature8bit(&RawTemp8);
    int Temp;

    if (RawTemp8 > 0 && RawTemp8 <= 0x36)
    {
        Temp = (int)RawTemp8 + 25;
    }
    else
    {
        Temp = -255 + (int)RawTemp8 + 25;
    }

    return Temp;
}

/**
   @brief  Calculate the temperature in Fahrenheit
   @retval Temperature in Fahrenheit
*/
int Sensor_ITDS::get_temp_Fahrenheit()
{
    int temp_Celsius = get_temperature();
    int temp_Fahrenheit = temp_Celsius * 1.8 + 32;
    return temp_Fahrenheit;
}

/**
   @brief   Set the FIFO mode
*/

void Sensor_ITDS::set_FIFO_mode(int fifoMode)
{
    ITDS_setFifoMode((ITDS_Fifo_Mode)fifoMode);
    select_ODR();
}

/**
  @brief  Get the FIFO mode
  @retval Error code
*/
int Sensor_ITDS::get_FIFO_mode()
{
    ITDS_Fifo_Mode fifoMode;
    ITDS_getFifoMode(&fifoMode);
    return fifoMode;
}

/**
  @brief  Get the FIFO fill level
  @retval Error code
*/
int Sensor_ITDS::get_FIFO_Fill_Level()
{
    uint8_t fifoFill;
    ITDS_getFifoFillLevel(&fifoFill);
    return fifoFill;
}
