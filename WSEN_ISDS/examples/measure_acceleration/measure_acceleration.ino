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

  status = sensor.is_ACC_Ready_To_Read();
  if (WE_FAIL == status)
  {
    Serial.println("Error: is_ACC_Ready_To_Read(). Stop!");
    while(1);
  } 
  else if (1 == status)
  {
    int16_t acc_X;
    int16_t acc_Y;
    int16_t acc_Z;

#if 0
    // Get acceleration along X axis in mg
   status = sensor.get_acceleration_X(&acc_X);
   if (WE_FAIL == status)
  {
    Serial.println("Error:  get_acceleration_X(). Stop!");
    while(1);  
  }
    Serial.println("Acceleration along X axis in [mg]: ");
    Serial.println(acc_X);

    // Get acceleration along Y axis in mg
    status = sensor.get_acceleration_Y(&acc_Y);
    if (WE_FAIL == status)
  {
    Serial.println("Error:  get_accel(). Stop!");
    while(1);  
  }
    Serial.println("Acceleration along Y axis in [mg]: ");
    Serial.println(acc_Y);

    // Get acceleration along Z axis in mg
    status = sensor.get_acceleration_Z(&acc_Z);
    if (WE_FAIL == status)
  {
    Serial.println("Error:  get_acceleration_Z(). Stop!");
    while(1);  
  }
    Serial.println("Acceleration along Z axis in [mg]: ");
    Serial.println(acc_Z);
#else
    
    status = sensor.get_accelerations(&acc_X,&acc_Y,&acc_Z);
    if (WE_FAIL == status)
  {
    Serial.println("Error:  get_accelerations(). Stop!");
    while(1);  
  }
    Serial.println("Acceleration along X,Y,Z axis in [mg]: ");
    Serial.print(acc_X);
    Serial.print(" ");
    Serial.print(acc_Y);
    Serial.print(" ");
    Serial.print(acc_Z);
    Serial.println(" ");
#endif
  }
  else /* status == '0' -> data not ready */
  {
    Serial.println("No data in output register.");
  }
  
  delay(250);
}
