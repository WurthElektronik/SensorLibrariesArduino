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

#ifndef WSEN_ISDS_H
#define WSEN_ISDS_H

#include "WSEN_ISDS_2536030320001.h"

class Sensor_ISDS
{

public:
    int init(int address);
    int get_DeviceID();
    void power_down();
    void SW_RESET();
    int select_ODR(int ODR);

    void set_Mode(int mode);

    float get_Sensitivity();
    int is_ACC_Ready_To_Read();
    int is_Gyro_Ready_To_Read();
    int is_Temp_Ready();
    int16_t get_acceleration_X();
    int16_t get_acceleration_Y();
    int16_t get_acceleration_Z();
    int get_accelerations(int16_t* X, int16_t* Y, int16_t* Z);
	int32_t get_angular_rate_X();
    int32_t get_angular_rate_Y();
    int32_t get_angular_rate_Z();
    int get_angular_rates(int32_t* X, int32_t* Y, int32_t* Z);
    float get_temperature();

private:
};

#endif
