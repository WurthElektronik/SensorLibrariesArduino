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

#include "WSEN_HIDS.h"
#include <stdint.h>

/**
   @brief  Initialize the I2C Interface
   @param  I2C address
   @retval Error Code
*/
int Sensor_HIDS::init(int address)
{
    return I2CInit(address);
}

/**
   @brief   Return the device ID for this sensor
   @retval  Value of DEVICE_ID
*/

int Sensor_HIDS::get_DeviceID()
{
    uint8_t devID;

    if (HIDS_getDeviceID(&devID) == WE_SUCCESS)
    {
        return devID;
    }
	
    return WE_FAIL;
}

/**
   @brief  Set the output data rate 
   @retval Error Code
*/
int Sensor_HIDS::select_ODR()
{
	int status = WE_FAIL;
    switch (ODR)
    {
        case 0:
        {
            status = HIDS_setOdr(oneShot);
            break;
        }

        case 1:
        {
            status = HIDS_setOdr(odr1HZ);
            break;
        }

        case 2:
        {
            status = HIDS_setOdr(odr7HZ);
            break;
        }

        case 3:
        {
            status = HIDS_setOdr(odr12_5HZ);
            break;
        }

        default:
        {
            return WE_FAIL;
        }
    }
	
	if (WE_FAIL == status)
	{
		return WE_FAIL;
	}
	
    return WE_SUCCESS;

}


/*get the temperature and Humidity Output data  */

/**
 * @brief  Read the raw humidity output
 * @param  no parameter.
 * @retval Humidity Output
 */
uint16_t Sensor_HIDS::get_H_T_out()
{
	uint16_t H_T_out = 0;
	H_T_out= HIDS_get_H_T_out();
	return H_T_out;
}

/**
 * @brief  Read the raw temperature output
 * @param  no parameter.
 * @retval Temperature Output
 */
uint16_t Sensor_HIDS::get_T_OUT()
{
	uint16_t T_out = 0;
	T_out= HIDS_get_T_OUT();
	return T_out;
}

/*get the calibration parameters */

/**
 * @brief  Read the H0_T0_out calibration
 * @param  no parameter.
 * @retval H0_T0_out calibration
 */
 
uint16_t Sensor_HIDS::get_H0_T0_out()
{
	uint16_t H0_T0_out = 0;
	H0_T0_out= HIDS_get_H0_T0_out();
	return H0_T0_out;
}

/**
 * @brief  Read the H1_T0_out calibration
 * @param  no parameter.
 * @retval H1_T0_out calibration
 */
 
uint16_t Sensor_HIDS::get_H1_T0_out()
{
	uint16_t H1_T0_out = 0;
	H1_T0_out= HIDS_get_H1_T0_out();
	return H1_T0_out;
}


/**
 * @brief  Read the H0_rh calibration
 * @param  no parameter.
 * @retval H0_rh calibration
 */
 
uint16_t Sensor_HIDS::get_H0_rh()
{
	uint16_t H0_rh = 0;
	H0_rh= HIDS_get_H0_rh();
	return H0_rh;
}

/**
 * @brief  Read the H1_rh calibration
 * @param  no parameter.
 * @retval H1_rh calibration
 */
 
uint16_t Sensor_HIDS::get_H1_rh()
{
	uint16_t H1_rh = 0;
	H1_rh= HIDS_get_H1_rh();
	return H1_rh;
}
/**
 * @brief  Read the T1_OUT calibration
 * @param  no parameter.
 * @retval T1_OUT calibration
 */
 
uint16_t Sensor_HIDS::get_T1_OUT()
{
	uint16_t T1_OUT = 0;
	T1_OUT= HIDS_get_T1_OUT();
	return T1_OUT;
}
/**
 * @brief  Read the T0_OUT calibration
 * @param  no parameter.
 * @retval T0_OUT calibration
 */
 
uint16_t Sensor_HIDS::get_T0_OUT()
{
	uint16_t T0_OUT = 0;
	T0_OUT = HIDS_get_T0_OUT();
	return T0_OUT;
}
/**
* @brief Read the temperature Data availability. Data ready.
* @param  Pointer to the temperature Data availability state and humidity Data availability state.
* @retval Error code
*/
int Sensor_HIDS::get_StatusDrdy(HIDS_state_t *temp_drdy, HIDS_state_t *humidity_drdy)
{

	if (WE_FAIL == HIDS_getStatusDrdy(temp_drdy, humidity_drdy))
	{
		return WE_FAIL;
	}	

	return WE_SUCCESS;
}


/**
* @brief Read the temperature Data availability. Data ready.
* @param  Pointer to the temperature Data availability state
* @retval Error code
*/
int Sensor_HIDS::get_TempStatus()
{	
	HIDS_state_t temp_state;
    if (WE_FAIL == HIDS_getTempStatus(&temp_state))
	{
		return WE_FAIL;
	}
	else
	{
		return (int)temp_state;
	}
}

/**
* @brief Read the humidity Data availability. Data ready.
* @param  Pointer to the humidity Data availability state
* @retval Error code
*/
int Sensor_HIDS::get_HumStatus()
{	
	HIDS_state_t humidity_state;
    if (WE_FAIL == HIDS_getHumStatus(&humidity_state))
	{
		return WE_FAIL;
	}
	else
	{
		return (int)humidity_state;
	}
}


/**
 * @brief  Read the Humidity data
 * @param  no parameter.
 * @retval error code
 */
int Sensor_HIDS::get_Humidity(float *relHum)
{
	float humidity;
	if (WE_FAIL == HIDS_getHumidity(&humidity))
	{
		return WE_FAIL;
	}

	*relHum = humidity;
	return WE_SUCCESS;
}

/**
 * @brief  Read the Temperature data
 * @param  no parameter.
 * @retval Temperature in °C
 */
int Sensor_HIDS::get_Temperature(float *temperature)
{
	float temp;
	if (WE_FAIL == HIDS_getTemperature(&temp))
	{
		return WE_FAIL;
	}
	
	*temperature = temp;
	return WE_SUCCESS;
}

/**
 * @brief  Set the sensor to single conversion mode
 * @param  no parameter.
 * @retval none
 */
int Sensor_HIDS::set_single_conversion()
{
    HIDS_state_t oneShot = HIDS_enable;
    ODR = 0;
    if (WE_FAIL == select_ODR())
	{
		return WE_FAIL;
	}	
	
    if (WE_FAIL == HIDS_enOneShot(oneShot))
	{
		return WE_FAIL;
	}		
	
	return WE_SUCCESS;
}

/**
 * @brief  Set the sensor to continuous mode
 * @param  no parameter.
 * @retval none
 */   
int Sensor_HIDS::set_continuous_mode(int outputDataRate)
{
    //Enable block data update
    if (WE_FAIL == HIDS_setBdu(HIDS_enable))
	{
		return WE_FAIL;
	}	
    ODR = outputDataRate;
    if (WE_FAIL == select_ODR())
	{
		return WE_FAIL;
	}	
    if (WE_FAIL == HIDS_setPowerMode(activeMode))
		{
		return WE_FAIL;
	}		
	
	return WE_SUCCESS;
}