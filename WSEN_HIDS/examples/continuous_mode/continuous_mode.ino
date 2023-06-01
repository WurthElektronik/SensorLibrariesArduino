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
int status;

void setup()
{
  delay(1000);
  
  Serial.begin(9600);

  // Initialize the I2C interface
  sensor.init(HIDS_ADDRESS_I2C_0);

  //The Output Data Rate One shot mode
  if (WE_FAIL == sensor.set_continuous_mode(ODR))
  {
  Serial.println("Error: set_continuous_mode(). STOP!");
    while(1);  
  }
}

void loop()
{
  HIDS_state_t temp_drdy;
  HIDS_state_t humidity_drdy;

  status = sensor.get_StatusDrdy(&temp_drdy, &humidity_drdy);
  if (WE_FAIL == status)
  {
    Serial.println("Error: get_StatusDrdy(). STOP!");
    while(1);
  }
  else 
  {
    if (0 == humidity_drdy)  
    {
      Serial.println("Sensor is not ready.");
    }
    else
    {
      
      //Print the humidity value on the serial monitor
      float rh;
      if (WE_FAIL == sensor.get_Humidity(&rh))
      {
        Serial.println("Error: get_Humidity(). STOP!");
        while(1);
      }
      else
      {
        Serial.print("The humidity is: ");
        Serial.print(rh);
        Serial.println(" %");
      }
    }

    if (0 == temp_drdy)
    {
      Serial.println("Sensor is not ready.");
    }
    else
    {
      float temperature;
      if (WE_FAIL == sensor.get_Temperature(&temperature))
      {
        Serial.println("Error: get_Temperature. STOP!");
        while(1);
      }
      else
      {
        Serial.print("The temperature is: ");
        Serial.print(temperature);
        Serial.println(" degC");
      }
    }   
  }

  // Waiting time between measurement
  int waitMillis = 1000 / ODR;

  // Wait before continuing with the next measurement
  delay(waitMillis);
}
