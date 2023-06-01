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

#include "ArduinoPlatform.h"
#include <Wire.h>

int deviceAddress = 0;

/**
 * @brief  Initialize the I2C Interface
 * @param  I2C address
 * @retval Error Code
 */

int I2CInit(int address)
{
	uint32_t timeout = (uint32_t)(TIMEOUT_MS * 1000);  /* timeout in us */
	bool reset_on_timeout = false;
	
    deviceAddress = address;
	Wire.setWireTimeout(timeout, reset_on_timeout);
    Wire.begin();
	
    return WE_SUCCESS;
}


int I2CDeInit(void)
{
    Wire.endTransmission(true);	/* end i2c transmission with stop = true, releasing the interface */
    return WE_SUCCESS;
}

/**
 * @brief  Set I2C bus Address
 * @param  I2C address
 * @retval Set Address
 */

void I2CSetAddress(int address) 
{ 
	deviceAddress = address; 
}

 /**
 * @brief   Read data starting from the addressed register
 * @param  -pointer Data : the address store the data
 *         -NumByteToRead : number of bytes to read     
 * @retval Error Code
 */

int I2C_read(uint8_t *data, int bytesToRead)
{
	Wire.beginTransmission(deviceAddress);
    int n = Wire.requestFrom(deviceAddress, bytesToRead); // request Bytes
	
	if (n != bytesToRead) /* also includes: if n == 0 */
	{
		return WE_FAIL;
	}

	for(int index = 0; index < bytesToRead; index++)
	{
		data[index] = Wire.read();
	}
    
    return WE_SUCCESS;
}
/**         EOF         */
