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



/*
 * WSEN-TIDS  
 * 
 * Check if a software reset procedure works
 * 
 * 
 */

#include "WSEN_TIDS.h"

Sensor_TIDS sensor;
int status;

void setup()
{

  Serial.begin(9600);

  // Initialize the I2C interface
  sensor.init(TIDS_ADDRESS_I2C_1);

  // Configure a whole reset procedure -> disable software reset at the end
  if (WE_FAIL == sensor.SW_RESET())
  {
    Serial.println("Error: get_SW_RESET(). STOP!");
    while(1);  
  }

  // Success = 0
  int rst;
  status = sensor.get_SW_RESET(&rst);
  if (WE_FAIL == status)
  {
    Serial.println("Error: get_SW_RESET(). STOP!");
    while(1);  
  }

  Serial.println(status);
  
}

void loop()
{
  // put your main code here, to run repeatedly:
}
