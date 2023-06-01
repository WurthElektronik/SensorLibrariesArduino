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
 * COPYRIGHT (c) 2019 Würth Elektronik eiSos GmbH & Co. KG
 *
 ***************************************************************************************************
 **/

#ifndef WSEN_PADS_H
#define WSEN_PADS_H

#include "WSEN_PADS_2511020213301.h"

class Sensor_PADS
{

public:
    int init(int address);
    int get_DeviceID();

    int power_down();
    int SW_RESET();
    int oneshot();
	
    int ready_to_read(PADS_state_t *stateTemperature, PADS_state_t *statePressure);
	int Sensor_PADS::temp_ready_to_read();
	int Sensor_PADS::pressure_ready_to_read();

    int read_temperature(float *temperature);
    int read_pressure(float *presure);

    int set_low_noise_mode();
    int set_low_pass_filter();
    int set_low_pass_configuration();

    int set_single_conversion();
    int set_continuous_mode(int ODR);

    int set_FIFO_mode(int fifoMode);
    int get_FIFO_mode(int *mode);
    int read_FIFO_temperature(float *temperature);
    int read_FIFO_pressure(float *presure);
    int get_FIFO_fill_level(int *lvl);

    int ODR;

private:
    uint16_t rawTemp;
    uint32_t rawPres;
    float T_neg;
    int select_ODR();
};

#endif
