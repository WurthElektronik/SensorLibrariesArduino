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


#include "WSEN_PADS.h"

Sensor_PADS sensor;

//The Output Data Rate in Hz
int ODR = 25;
 int mode;

void setup()
{

  Serial.begin(9600);

  // Initialize the I2C interface
  sensor.init(PADS_ADDRESS_I2C_1);

  // FIFO in the Continous Mode (Mode 2)
  if (WE_FAIL == sensor.set_FIFO_mode(2))
  {
    Serial.print("error: set_FIFO_mode(2). STOP!");
    while(1);
  }
  
  Serial.print("The FIFO is in the Mode ");

if (WE_FAIL == sensor.get_FIFO_mode(&mode))
    {
    Serial.print("error: get_FIFO_mode(). STOP!");
    while(1);
  }
  Serial.println(mode);

  // Before changing the mode to FIFO mode set the bypass mode first
  if (WE_FAIL == sensor.set_FIFO_mode(0)) // Bypass 
      {
    Serial.print("error: set_FIFO_mode(0). STOP!");
    while(1);
  }
  if (WE_FAIL == sensor.set_FIFO_mode(1)) // FIFO
      {
    Serial.print("error: set_FIFO_mode(1). STOP!");
    while(1);
  }
  Serial.print("The FIFO is in the Mode ");
 
  if (WE_FAIL == sensor.get_FIFO_mode(&mode))
    {
    Serial.print("error: get_FIFO_mode(). STOP!");
    while(1);
  }
  Serial.println(mode);
}

void loop()
{
}
