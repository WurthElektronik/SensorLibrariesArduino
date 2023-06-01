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

  // Set FIFO ODR to 26Hz
  status = sensor.select_ODR(2);
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
  status = sensor.is_Gyro_Ready_To_Read();
 if (WE_FAIL == status)
  {
    Serial.println("Error: is_Gyro_Ready_To_Read(). Stop!");
    while(1);
  } 
  else if (1 == status)
  {
    int32_t gyro_X;
    int32_t gyro_Y;
    int32_t gyro_Z;
#if 0
    // Get X-axis angular rate in [mdps]
   
    status = sensor.get_angular_rate_X(&gyro_X);
    if (WE_FAIL == status)
    {
    Serial.println("Error:  get_angular_rate_X(). Stop!");
    while(1);  
  }
    Serial.println("Angular rate in X axis in [mdps]: ");
    Serial.println(gyro_X);

    // Get Y-axis angular rate in [mdps]
    status = sensor.get_angular_rate_Y(&gyro_Y);
    if (WE_FAIL == status)
    {
    Serial.println("Error:  get_angular_rate_Y(). Stop!");
    while(1);  
  }
    Serial.println("Angular rate in  Y axis in [mdps]: ");
    Serial.println(gyro_Y);

    // Get Z-axis angular rate in [mdps]
    status = sensor.get_angular_rate_Z(&gyro_Z);
    if (WE_FAIL == status)
    {
    Serial.println("Error:  get_angular_rate_Z(). Stop!");
    while(1);  
  }
    Serial.println("Angular rate in  Z axis in [mdps]: ");
    Serial.println(gyro_Z);
#else
    status = sensor.get_angular_rates(&gyro_X,&gyro_Y,&gyro_Z);
    if (WE_FAIL == status)
    {
    Serial.println("Error:  get_angular_rates(). Stop!");
    while(1);  
  }
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
