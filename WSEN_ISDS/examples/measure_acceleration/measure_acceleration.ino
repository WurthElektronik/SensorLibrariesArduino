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

  WSEN-ISDS - Read Sensor 


  This example reads the acceleration values along all axes
  from the WSEN-ISDS sensor in the high performance mode.
  
  The SAO pin is here connected to the logic high level. 
  The initialization by the ODR and the full scale needs to 
  be performed at first.
  The acceleration values are printed on the serial monitor.


*/

#include "WSEN_ISDS.h"

Sensor_ISDS sensor;

void setup()
{

  Serial.begin(9600);

  // Initialize the I2C interface
  sensor.init(ISDS_ADDRESS_I2C_1);

  // Reset sensor
  sensor.SW_RESET();

  // Set FIFO ODR to 26Hz
  sensor.select_ODR(2);

  // Set high performance mode
  sensor.set_Mode(2);

}

void loop()
{
  if (ISDS_enable == sensor.is_ACC_Ready_To_Read())
  {    
    int16_t acc_X;
    int16_t acc_Y;
    int16_t acc_Z;

    #if 0
    // Get acceleration along X axis in mg
    acc_X = sensor.get_acceleration_X();
    Serial.println("Acceleration along X axis in [mg]: ");
    Serial.println(acc_X);

    // Get acceleration along Y axis in mg
    acc_Y = sensor.get_acceleration_Y();
    Serial.println("Acceleration along Y axis in [mg]: ");
    Serial.println(acc_Y);

    // Get acceleration along Z axis in mg
    acc_Z = sensor.get_acceleration_Z();
    Serial.println("Acceleration along Z axis in [mg]: ");
    Serial.println(acc_Z);
    #else
    sensor.get_accelerations(&acc_X,&acc_Y,&acc_Z);
    Serial.println("Acceleration along X,Y,Z axis in [mg]: ");
    Serial.print(acc_X);
    Serial.print(" ");
    Serial.print(acc_Y);
    Serial.print(" ");
    Serial.print(acc_Z);
    Serial.println(" ");
    #endif
  }
  else
  {
    Serial.println("No data in output register.");
  }
  delay(250);
}
