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
int status;


void setup()
{

  PADS_state_t stateTemperature;
  PADS_state_t statePressure;
  
  delay(1000);
  Serial.begin(9600);

  // Initialize the I2C interface
  sensor.init(PADS_ADDRESS_I2C_1);

  // Set single conversion mode
  if (WE_FAIL == sensor.set_single_conversion())
  {
    Serial.print("Error: set_single_conversion(). STOP!");
    while(1);
  }

  status = sensor.ready_to_read(&stateTemperature, &statePressure);
  if (WE_FAIL == status)
  {
    Serial.print("Error: Sensor DRDY temperature not readable.");
  }
  else if (0 == stateTemperature)
  {
   Serial.print("Error: temperature DRDY = 0.");
  }
  else
  {
  
    // Read and calculate the temperature
    float temperature;
    sensor.read_temperature(&temperature);
  
    Serial.print("temperature: ");
  
    // Print the temperature on the serial monitor
    Serial.print(temperature);
    Serial.println(" degC");
  
  }

  if (0 == statePressure)
  {
    Serial.print("Error: pressure DRDY = 0.");
  }
  else
  {
    // Read and calculate the pressure
    float pressure;
    sensor.read_pressure(&pressure);
  
    Serial.print("pressure: ");
  
    // Print the pressure on the serial monitor
    Serial.print(pressure);
    Serial.println(" kPa");
  }
}

void loop()
{
  // put your main code here, to run iteratively
}
