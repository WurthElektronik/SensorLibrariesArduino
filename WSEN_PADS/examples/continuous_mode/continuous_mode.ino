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
  the continuous mode. 
  The low-noise configuration and the additional low pass filter are enabled.

  The SAO pin is connected to positive supply voltage.

  The temperature is printed in °C and the pressure in kPa on the serial monitor.


*/

#include "WSEN_PADS.h"

Sensor_PADS sensor;
int status;

//The Output Data Rate in Hz
int ODR = 1;

void setup()
{
  delay(1000);
  Serial.begin(9600);

  // Initialize the I2C interface
  sensor.init(PADS_ADDRESS_I2C_1); 

  // Set the free run mode with given ODR
  if (WE_FAIL == sensor.set_continuous_mode(ODR))
  {
    Serial.print("Error: set_continuous_mode() failed. STOP!");
    while(1);
  }

  // Enable low-noise configuration
  if (WE_FAIL == sensor.set_low_noise_mode())
  {
    Serial.print("Error: set_low_noise_mode() failed. STOP!");
    while(1);
  }

  // Enable the additional low pass filter
  if (WE_FAIL == sensor.set_low_pass_configuration())
  {
    Serial.print("Error: set_low_pass_configuration() failed. STOP!");
    while(1);
  }

}

void loop()
{

  PADS_state_t stateTemperature;
  PADS_state_t statePressure;
  status = sensor.ready_to_read(&stateTemperature, &statePressure);
  if (WE_FAIL == status)
  {
    Serial.print("Error: Sensor DRDY temperature status not readable. STOP!");
    while(1);
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
    if (WE_FAIL == sensor.read_pressure(&pressure))
    {
      Serial.print("Error: read_pressure(). STOP!");
      while(1);
    }
  
    Serial.print("pressure: ");
  
    // Print the pressure on the serial monitor
    Serial.print(pressure);
    Serial.println(" kPa");
  }


  Serial.println("-----------------------");

  // Waiting time between measurement
  int waitMillis = 1000 / ODR;

  // Wait before continuing with the next measurement
  delay(waitMillis);

}
