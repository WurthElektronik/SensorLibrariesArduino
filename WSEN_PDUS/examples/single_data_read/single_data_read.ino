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

  WSEN-PDUS - Read Sensor 


  This example reads the temperature and the pressure from the WSEN-PDUS 2513130810301 sensor.
  
  The data is printed on the serial monitor.

*/

#include "WSEN_PDUS.h"

Sensor_PDUS sensor;

void setup()
{
  delay(1000);
  Serial.begin(9600);

    // Initialize the I2C interface
    sensor.init(PDUS_ADDRESS_I2C);
	
	delay(10);

}


void loop()
{
    float presskPa;
    float tempDeg;

	/* Calculate the pressure and temperature  */
	/* #warning: "use the correct PDUS_Sensor_Type as paramter to achieve correct conversion factor." */
    if (WE_FAIL == sensor.getPresAndTemp(pdus3, &presskPa, &tempDeg))
    {
      Serial.println("Error: getPresAndTemp. Stop!");
      while(1);
    }

    // Print the results on the serial monitor
    Serial.println("Pressure is:");
    Serial.println(presskPa);
    Serial.println("Temperature is:");
    Serial.println(tempDeg);
	delay(1000);
}
