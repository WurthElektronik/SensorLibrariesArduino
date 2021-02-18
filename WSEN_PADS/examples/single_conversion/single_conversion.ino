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

  WSEN-PADS - Read Sensor


  This example reads the temperature and the pressure from the WSEN-PADS sensor in
  the single conversion mode. 
  The low-noise configuration and the additional low pass filter are enabled.

  The SAO pin is connected to positive supply voltage.

  The temperature is printed in °C and the pressure in kPa on the serial monitor.


*/

#include "WSEN_PADS.h"

Sensor_PADS sensor;

void setup()
{
  delay(5000);
  Serial.begin(9600);

  // Initialize the I2C interface
  sensor.init(PADS_ADDRESS_I2C_1);

  // Set single conversion mode
  sensor.set_single_conversion();

  // Check if sensor is ready to measure the temperature
  if (sensor.temp_ready_to_read() & sensor.pressure_ready_to_read())
  {
    // Read and calculate the temperature
    float myTemperature = sensor.read_temperature();
    Serial.print("The temperature is: ");

    // Print the temperature on the serial monitor
    Serial.print(myTemperature);
    Serial.println(" Celsius");

    // Read and calculate the pressure
    float myPressure = sensor.read_pressure();
    Serial.print("The pressure is: ");

    // Print the temperature on the serial monitor in kPa
    Serial.print(myPressure);
    Serial.println(" kPa");
  }
  else
  {
    Serial.print("Sensor is not ready.");
  }
}

void loop()
{
  // put your main code here, to run iteratively
}

