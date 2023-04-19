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
  if (ISDS_enable == sensor.is_Gyro_Ready_To_Read())
  {
    int32_t gyro_X;
    int32_t gyro_Y;
    int32_t gyro_Z;
    #if 0
    // Get X-axis angular rate in [mdps]
    gyro_X = sensor.get_angular_rate_X();
    Serial.println("Angular rate in X axis in [mdps]: ");
    Serial.println(gyro_X);

    // Get Y-axis angular rate in [mdps]
    gyro_Y = sensor.get_angular_rate_Y();
    Serial.println("Angular rate in  Y axis in [mdps]: ");
    Serial.println(gyro_Y);

    // Get Z-axis angular rate in [mdps]
    gyro_Z = sensor.get_angular_rate_Z();
    Serial.println("Angular rate in  Z axis in [mdps]: ");
    Serial.println(gyro_Z);
    #else
    sensor.get_angular_rates(&gyro_X,&gyro_Y,&gyro_Z);
    Serial.println("Angular rate in X,Y,Z axis in [mdps]: ");
    Serial.print(gyro_X);
    Serial.print(" ");
    Serial.print(gyro_Y);
    Serial.print(" ");
    Serial.print(gyro_Z);
    Serial.println(" ");
    #endif
  }
  else
  {
    Serial.println("No data in output register.");
  }
  delay(250);
}
