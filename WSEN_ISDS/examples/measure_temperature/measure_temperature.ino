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
 *  WSEN-ISDS - Read Sensor 


  This example reads the temperature in °C 
  from the WSEN-ISDS sensor in the normal mode.
  
  The SAO pin is here connected to the logic high level. 
  
 */

#include "WSEN_ISDS.h"

Sensor_ISDS sensor;
int status;

void setup()
{

  Serial.begin(9600);

  // Initialize the I2C interface
  sensor.init(ISDS_ADDRESS_I2C_1);

  // Reset sensor
  status = sensor.SW_RESET();
  if (WE_FAIL == status)
  {
    Serial.println("Error:  SW_RESET(). Stop!");
    while(1);  
  }


  status = sensor.select_ODR(1);
  if (WE_FAIL == status)
    {
    Serial.println("Error:  select_ODR(). Stop!");
    while(1);  
  }

  // Set high performance mode
  status = sensor.set_Mode(2);
  if (WE_FAIL == status)
  {
    Serial.println("Error:  set_Mode(). Stop!");
    while(1);  
  }
  

}

void loop()
{


  // Check if sensor is ready to measure the temperature
  status = sensor.is_Temp_Ready();
    
  if (WE_FAIL == status)
  {
    Serial.println("Error: is_Temp_Ready(). Stop!");
    while(1);
  }
  else if (1 == status)
  {
    //Print the temperature on the serial monitor
    
    float temperature;
    if (WE_FAIL == sensor.get_temperature(&temperature))
      {
    Serial.println("Error:  get_temperature(). Stop!");
    while(1);  
    }
    Serial.println("Temperature in [°C]: ");
    Serial.println(temperature);
  }
  else
  {
    Serial.println("Sensor not ready.");
  }
  delay(1000);
}
