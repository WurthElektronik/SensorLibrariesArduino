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
 *  WSEN-ITDS - Read Sensor 


  This example reads the temperature in °C 
  from the WSEN-ITDS sensor in the normal mode.
  
  The SAO pin is here connected to the logic high level. 
  
 */

#include "WSEN_ITDS.h"

Sensor_ITDS sensor;
int status;

void setup()
{

  Serial.begin(9600);

  //The Output Data Rate mode 6 (200hz)
  sensor.ODR = 6;

  // Initialize the I2C interface
  sensor.init(ITDS_ADDRESS_I2C_1);

  // Set the sensor to normal mode
  sensor.set_Normal_Mode();

}

void loop()
{
    // Check if sensor is ready to measure the temperature

  status = -1;
  status = sensor.is_Temp_Ready();
    
  if (WE_FAIL == status)
  {
    Serial.println("Error: Sensor status register read failed.");
  }
  else if (0 == status)
  {
    Serial.println("Error: Sensor not ready.");
  }
  else
  {
    //Print the temperature on the serial monitor
    int temperature_degC = sensor.get_temperature();
    Serial.print("T= ");
    Serial.print(temperature_degC);
    Serial.println(" deg C");
  }

  delay(1000);
}
