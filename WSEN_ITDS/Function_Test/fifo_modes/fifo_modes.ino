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

#include "WSEN_ITDS.h"

Sensor_ITDS sensor;

//The Output Data Rate 
int ODR = 3;

void setup()
{

  Serial.begin(9600);

  // Initialize the I2C interface
  sensor.init(ITDS_ADDRESS_I2C_1);

  // FIFO in the Continous Mode (Mode 6)
  if (WE_FAIL == sensor.set_FIFO_mode(6))
  {
    Serial.println("Error: set_FIFO_mode(6). STOP!");
    while(1);
  }
  
  
  int mode;
  if (WE_FAIL == sensor.get_FIFO_mode(&mode))
  {
    Serial.println("Error: get_FIFO_mode(). STOP!");
    while(1);
  }
  
  Serial.print("The FIFO is in the Mode ");
  Serial.println(mode);

  // Before changing the mode to FIFO mode set the bypass mode first
  if (WE_FAIL == sensor.set_FIFO_mode(0)) // Bypass 
   {
    Serial.println("Error: set_FIFO_mode(0). STOP!");
    while(1);
  }
  if (WE_FAIL == sensor.set_FIFO_mode(1)) // FIFO
   {
    Serial.println("Error: set_FIFO_mode(1). STOP!");
    while(1);
  }
  
  if (WE_FAIL == sensor.get_FIFO_mode(&mode))
  {
    Serial.println("Error: get_FIFO_mode(). STOP!");
    while(1);
  }
    
  Serial.print("The FIFO is in the Mode ");
  Serial.println(mode);
}

void loop()
{
  // put your main code here, to run repeatedly:
}
