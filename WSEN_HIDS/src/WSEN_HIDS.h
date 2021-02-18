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
 * COPYRIGHT (c) 2020 Würth Elektronik eiSos GmbH & Co. KG
 *
 ***************************************************************************************************
 **/

#ifndef WSEN_HIDS_H
#define WSEN_HIDS_H

#include "WSEN_HIDS_2523020210001.h"

class Sensor_HIDS
{

public:
    int init(int address);
    int get_DeviceID();
	
	int ODR;
    int select_ODR();

	void set_single_conversion();
    void set_continuous_mode(int ODR);

	/*get the temperature and Humidity Output data  */

	uint16_t get_H_T_out();
	uint16_t get_T_OUT();

	/*get the calibration parameters */

	uint16_t get_H0_T0_out();
	uint16_t get_H1_T0_out();
	uint16_t get_H0_rh();
	uint16_t get_H1_rh();

	uint16_t get_T1_OUT();
	uint16_t get_T0_OUT();

	/* Temperature and Humidity data available State */

	int8_t get_TempStatus();
	int8_t get_HumStatus();
	
	float get_Humidity();
	float get_Temperature();

};

#endif
