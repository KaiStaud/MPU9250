/*
 * IMU9250.cpp
 *
 *  Created on: Mar 14, 2021
 *      Author: kai-s
 */

#include "IMU9250.h"
#include "stdint.h"
#include "main.h"
IMU9250::IMU9250() {
	// TODO Auto-generated constructor stub

}

void IMU9250::Initialize()
{
	uint8_t sleep_setup_data[2] = {0x6B,0x00}; // Power Management Register, Sleep Register
	uint8_t gyro_setup_data[2] = {0x1B,0x00}; // Set Gyro to 250°/sec Full Scale Range
	uint8_t acc_setup_data[2] = {0x1C,0x00}; // set Accelerometer to 2g/sec Full Scale Range
	uint8_t enable_sensors[2] = {0x6C,0x00};
	Reset();
	// Disable Sleep Settings
	HAL_I2C_Master_Transmit(&hi2c1, 0xD0 ,sleep_setup_data , 2, 10);
	// added: Enable Sensors
	HAL_I2C_Master_Transmit(&hi2c1, 0xD0 ,enable_sensors , 2, 10);
	// Configure Gyroscope
	HAL_I2C_Master_Transmit(&hi2c1, 0xD0,gyro_setup_data , 2, 10);
	// Configure Accelerometer
	HAL_I2C_Master_Transmit(&hi2c1, 0xD0,acc_setup_data , 2, 10);

}

void IMU9250::Reset()
{
	uint8_t reset[2] = {0x6B,0x80};
	HAL_I2C_Master_Transmit(&hi2c1, 0xD0,reset , 2, 10);
	HAL_Delay(10);
}
/*
uint16_t IMU9250::getAccX()
{
uint8_t register_request[2] = {0x3F}; // Z_High + Z_Low
uint8_t acc_data[2]; // Store high and low bytes
// Ask Device for Data from Address
HAL_I2C_Master_Transmit(&hi2c1, 0xD0,register_request , 1, 10);
// Start actually reading from device
HAL_I2C_Master_Receive(&hi2c1, 0xD0, acc_data, 2, 10);
// Convert to g depending on Full Scale Range:
uint8_t msb = acc_data[0];
uint8_t lsb = acc_data[1];
return (msb<<8 | lsb); // show compiler this is a long int
}
*/

/*
 * @ brief: Returns the acceleration of the x- axis
 * @ param: none
 * @ return: acceleration in m/s²
 */
float IMU9250::getAccX()
{
	return readDWord(0x3B) * 9.81/ 16384.0;
}

/*
 * @ brief: Returns the acceleration of the y- axis
 * @ param: none
 * @ return: acceleration in m/s²
 */
float IMU9250::getAccY()
{
	return readDWord(0x3D) * 9.81 / 16384.0;
}
/*
 * @ brief: Returns the acceleration of the z- axis
 * @ param: none
 * @ return: acceleration in m/s²
 */
float IMU9250::getAccZ()
{
	return readDWord(0x3F)*9.81 / 16384.0;
}

/*
 * @ brief: Returns the rotational acceleration of the x- axis
 * @ param: none
 * @ return: rotational acceleration in deg/s²
 */
float IMU9250::getGyroX()
{
	return readDWord(0x43)/131.0;
}

/*
 * @ brief: Returns the rotational acceleration of the y- axis
 * @ param: none
 * @ return: rotational acceleration in deg/s²
 */
float IMU9250::getGyroY()
{
	return readDWord(0x45)/131.0;
}

/*
 * @ brief: Returns the rotational acceleration of the z- axis
 * @ param: none
 * @ return: rotational acceleration in deg/s²
 */
float IMU9250::getGyroZ()
{
	return readDWord(0x47)/131.0;
}

float IMU9250::getTemp()
{
}

/*
 * @ brief: Returns a 16 bit double word from a single read
 * @ param: address from the first register
 * @ return: 16-bit value, constructed of the two single bytes
 */
uint16_t IMU9250::readDWord(uint8_t startAddr)
{
	uint8_t data[2]; // Store high and low bytes
	// Ask Device for Data from Address
	HAL_I2C_Master_Transmit(&hi2c1, 0xD0,&startAddr, 1, 10);
	// Start actually reading from device
	HAL_I2C_Master_Receive(&hi2c1, 0xD0, data, 2, 10);
	// Shift  msb 	and    lsb    in position
	return (data[0]<<8 | data[1]);
}
