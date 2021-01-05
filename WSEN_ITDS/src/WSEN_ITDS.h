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
 * COPYRIGHT (c) 2019 Würth Elektronik eiSos GmbH & Co. KG
 *
 ***************************************************************************************************
 **/

#ifndef WSEN_ITDS_H
#define WSEN_ITDS_H

#include "WSEN_ITDS_2533020201601.h"

class Sensor_ITDS
{

public:
    int init(int address);
    int get_DeviceID();
    void power_down();
    void SW_RESET();

    void set_High_Performance();
    void set_Low_Mode();
    void set_Normal_Mode();
    int get_Operating_Mode();
    int get_Power_Mode();

    void set_Bandwidth(int value);
    void set_Full_Scale(int value);
    void set_Low_Pass_Filter();
    void set_High_Pass_Filter();

    float get_Sensitivity();
    int is_Ready_To_Read();
    int is_Temp_Ready();
    float get_acceleration_X();
    float get_acceleration_Y();
    float get_acceleration_Z();
    int get_temperature();
    int get_temp_Fahrenheit();

    void set_FIFO_mode(int fifoMode);
    int get_FIFO_mode();
    int get_FIFO_Fill_Level();

    int ODR;
    int select_ODR();

private:
    ITDS_power_mode mode;
    ITDS_full_Scale full_scale;
};

#endif
