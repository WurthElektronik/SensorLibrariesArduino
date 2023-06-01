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

  WSEN-PADS - Read from FIFO buffer 

  This example reads the temperature and the pressure from the FIFO buffer in
  the continous mode. 

  The temperature is printed in °C and the pressure in kPa on the serial monitor


*/

#include "WSEN_PADS.h"

Sensor_PADS sensor;

//The Output Data Rate in Hz
int ODR = 25;

void setup()
{
  Serial.begin(9600);

  // Initialize the I2C interface
  sensor.init(PADS_ADDRESS_I2C_1);

  // Set the continous mode 2
  if (WE_FAIL == sensor.set_FIFO_mode(2))
  {
    Serial.println("set_FIFO_mode() failed. STOP!");
    while(1);
  }
  
}

void loop()
{
  Serial.println("Temperature: ");

  // Calculate the temperature and print it on the serial monitor
  float temperature;
  sensor.read_FIFO_temperature(&temperature);  
  Serial.print("Temperature deg. C: ");
  Serial.println(temperature);
  

  // Calculate the temperature and print it on the serial monitor
  Serial.print("Pressure: ");
  float pressure;
  sensor.read_FIFO_pressure(&pressure);
  Serial.println(pressure);

  Serial.print("fill level:");

  // Get the number of data sets stored in the FIFO
  int level;
  sensor.get_FIFO_fill_level(&level);
  Serial.println(level);

  
  Serial.println("-------");

  // Waiting time between measurement
  int waitMillis = 1000 / ODR;

  // Wait before continuing with the next measurement
  delay(1000 / ODR);
}
