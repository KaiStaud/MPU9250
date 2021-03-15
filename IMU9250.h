/*
 * IMU9250.h
 *
 *  Created on: Mar 14, 2021
 *      Author: kai-s
 */

#ifndef IMU_IMU9250_H_
#define IMU_IMU9250_H_
#include "stm32f4xx_hal.h" // Include this header to avoid errors from /Drivers
#include "stm32f4xx_hal_i2c.h" // ST's HAL Drivers!

class IMU9250 {
public:
	IMU9250();
	void Initialize();

	/* Polling Functions */
	float getAccX();
	float getAccY();
	float getAccZ();
	float getGyroX();
	float getGyroY();
	float getGyroZ();
	float getTemp();

	void Reset();
private:
	uint16_t readDWord(uint8_t startAddr); // Read two bytes

};

#endif /* IMU_IMU9250_H_ */
