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

  WSEN-TIDS - Read Sensor 


  This example reads the temperature from the WSEN-TIDS sensor in
  the single conversion mode.
  
  The SAO pin is here connected to positive supply voltage. 
  
  The temperature is printed on the serial monitor.


*/

#include "WSEN_TIDS.h"

Sensor_TIDS sensor;
int status;

void setup()
{
  delay(5000);
  
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

  // Set single conversion mode
  status = sensor.set_single_conversion();
  if (WE_FAIL == status)
  {
    Serial.println("Error: set_single_conversion(). STOP!");
    while(1);
  }

  // Check if sensor is ready to measure the temperature


  int drdy = sensor.is_ready_to_read();  
  if (WE_FAIL == drdy)
  {
    Serial.println("Error: is_ready_to_read(). STOP!");
    while(1);
  }
  else if (1 == drdy)
  {
    // Read and calculate the temperature
    float myTemperature ;
    status = sensor.read_temperature(&myTemperature);
    if (WE_FAIL == status)
    {
      Serial.println("Error: read_temperature(). STOP!");
      while(1);
    }
    
    // Print the temperature on the serial monitor
    Serial.print("The temperature is: ");
    Serial.print(myTemperature);
    Serial.println(" Celsius");
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
