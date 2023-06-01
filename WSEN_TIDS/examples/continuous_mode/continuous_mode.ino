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

  WSEN-TIDS - Read Sensor


  This example reads the temperature from the WSEN-TIDS sensor in
  the continuous mode. 
  

  The SAO pin is connected to positive supply voltage.

  The temperature is printed on the serial monitor in °C.


*/

#include "WSEN_TIDS.h"

Sensor_TIDS sensor;
int status;

//The Output Data Rate in Hz
int ODR = 25;

void setup()
{
  delay(1000);
  Serial.begin(9600);

  // Initialize the I2C interface
  sensor.init(TIDS_ADDRESS_I2C_1);

  //Perform a software reset
  status = sensor.SW_RESET();
  if (WE_FAIL == status)
  {
    Serial.println("Error: SW_RESET(). STOP!");
    while(1);
  }

  // Set the free run mode with given ODR
  status = sensor.set_continuous_mode(ODR);
  if (WE_FAIL == status)
  {
    Serial.println("Error: set_continuous_mode(). STOP!");
    while(1);
  }
}

void loop()
{

  // Read and calculate the temperature
  float temperature; 
  
  status = sensor.read_temperature(&temperature);
  if (WE_FAIL == status)
  {
    Serial.println("Error: read_temperature(). STOP!");
    while(1);
  }

  // Print the temperature on the serial monitor
  Serial.print(temperature);
  Serial.println(" degC");

  // Waiting time between measurement
  int waitMillis = 1000 / ODR;

  // Wait before continuing with the next measurement
  delay(waitMillis);
}
