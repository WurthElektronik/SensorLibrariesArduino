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

  WSEN-ITDS - Read Sensor 


  This example reads the acceleration values along all axes
  from the WSEN-ITDS sensor in the high performance mode.
  
  The SAO pin is here connected to the logic high level. 
  The initialization by the ODR and the full scale needs to 
  be performed at first.
  The acceleration values are printed on the serial monitor.


*/

#include "WSEN_ITDS.h"

Sensor_ITDS sensor;
int status;

void setup()
{

  delay(5000);
  Serial.begin(9600);

  // Initialize the I2C interface
  sensor.init(ITDS_ADDRESS_I2C_1);

  //The Output Data Rate mode 6 (200hz)
  sensor.ODR = 6;

  // Set high performance mode
  status = 0;
  status = sensor.set_High_Performance();
  if (status == WE_FAIL)
  {
    Serial.println("Sensor config failed. high performance. STOP.");
    while(1);    
  }

  // Set the full scale to 16g
  status = 0;
  status = sensor.set_Full_Scale(3);
  if (status == WE_FAIL)
  {
    Serial.println("Sensor config failed. Full scale. STOP.");
    while(1);    
  }

}

void loop()
{
    status = 0;
    status = sensor.is_Ready_To_Read();

    if (WE_FAIL == status)
    {
      Serial.println("Sensor DRDY bit read error. STOP.");
      while(1);
    }
  
    if (ITDS_enable == status)
    {
      // Get acceleration along X axis in mg
      float acc_X = 0.0f;
      if (WE_FAIL == sensor.get_acceleration_X(&acc_X))
      {
        Serial.println("Sensor read error at acc x. STOP.");
        while(1);
      }
      else
      {   
        Serial.println("Acceleration along X axis: ");
        Serial.println(acc_X);
      }
  
      float acc_Y = 0.0f;
      // Get acceleration along Y axis in mg1
          if (WE_FAIL == sensor.get_acceleration_Y(&acc_Y))
      {
        Serial.println("Sensor read error at acc y. STOP.");
        while(1);
      }
      else
      {   
        Serial.println("Acceleration along Y axis: ");
        Serial.println(acc_Y);
      }
  
      // Get acceleration along Z axis in mg
      float acc_Z = 0.0f;
      if (WE_FAIL == sensor.get_acceleration_Z(&acc_Z))
      {
        Serial.println("Sensor read error at acc z. STOP.");
        while(1);
      }
      else
      {
        Serial.println("Acceleration along Z axis: ");
        Serial.println(acc_Z);
      }
  }
  else
  {
    Serial.println("No data in output register.");
  }
  delay(1000);
}
