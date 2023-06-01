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

#ifndef WSEN_TIDS_H
#define WSEN_TIDS_H

#include "WSEN_TIDS_2521020222501.h"

class Sensor_TIDS
{

public:
    int init(int address);
    int get_DeviceID();

    int power_down();
    int oneshot();

    int SW_RESET();
    int get_SW_RESET(int *rst);
    
    int read_temperature(float *temp);
    int read_temp_fahrenheit(float *temp);

    int set_single_conversion();
	
    int is_ready_to_read();
	
    int set_continuous_mode(int ODR);
    int set_Temp_High_Limit(uint8_t T_H_Limit);
	int set_Temp_Low_Limit(uint8_t T_L_Limit);
    int get_Temp_High_Limit(uint8_t *limit);
    int get_Temp_Low_Limit(uint8_t *limit);
	int get_Threshold_High_Limit(float *temp);
    int get_Threshold_Low_Limit(float *temp);

    int ODR;

private:
    
    uint16_t rawTemp;
    float T_neg;
    int Select_ODR();
    
};

#endif