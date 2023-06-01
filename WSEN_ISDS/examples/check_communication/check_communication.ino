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

/*
 * WSEN-ITDS  communication check
 * 
 * Initializing and reading the device ID for this sensor
 * 
 * The SAO pin is here connected to the logic high level.
 * 
 */

#include "WSEN_ISDS.h"

Sensor_ISDS sensor;
int status;

void setup()
{
  delay(5000);

  Serial.begin(9600);

  // Initialize the I2C interface
  sensor.init(ISDS_ADDRESS_I2C_1);

  // Get the device ID for this sensor
  int sensor_ID = sensor.get_DeviceID();
  if (WE_FAIL == sensor_ID)
  {
    Serial.println("Error: get_DeviceID(). Stop!");
    while(1);
  }
  
  Serial.print("Sensor ID: ");

  // Print the device ID in hexadecimal on the serial monitor
  Serial.print(sensor_ID, HEX);
  Serial.println();

  // Check if the determined device ID matches the correct device ID (->0x6A) of this sensor
  if (sensor_ID == ISDS_DEVICE_ID_VALUE)
  {
    Serial.println("Communication successful !");
  }
  else
  {
    Serial.println("No communication with the device !");
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
}
