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

/*

  WSEN-HIDS - Read Sensor


  This example reads the humidity and temperature from the WSEN-HIDS sensor in
  the continuous mode. 
  

  The temperature and humidity are printed on the serial monitor.


*/

#include "WSEN_HIDS.h"

Sensor_HIDS sensor;

//The Output Data Rate in Hz
int ODR = 1;

void setup()
{
  delay(5000);
  
  Serial.begin(9600);

  // Initialize the I2C interface
  sensor.init(HIDS_ADDRESS_I2C_0);

  //The Output Data Rate One shot mode
  sensor.set_continuous_mode(ODR);
}

void loop()
{

  Serial.print("The humidity is: ");
  //Print the humidity value on the serial monitor
  Serial.print(sensor.get_Humidity());
  Serial.println(" %");

  Serial.print("The temperature is: ");
  Serial.print(sensor.get_Temperature());
  Serial.println(" degC");

  // Waiting time between measurement
  int waitMillis = 1000 / ODR;

  // Wait before continuing with the next measurement
  delay(waitMillis);
}
