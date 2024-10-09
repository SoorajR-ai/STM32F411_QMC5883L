
#include "qmc.h"

I2C_HandleTypeDef *_QMC_i2c_port;


uint8_t QMC_init(I2C_HandleTypeDef *hi2c_device){
	_QMC_i2c_port = hi2c_device;
	HAL_StatusTypeDef status = HAL_I2C_IsDeviceReady(hi2c_device, QMC_ADDR<<1, 1, 100);
	if(status==HAL_OK){
		uint8_t mode_data = 0x01;
		if(HAL_I2C_Mem_Write(hi2c_device, QMC_ADDR<<1, 0x0B, I2C_MEMADD_SIZE_8BIT, &mode_data, 1, 100)==HAL_OK){
			uint8_t config_data = 0x01 | 0x0c | 0x10 | 0x00;
			if(HAL_I2C_Mem_Write(hi2c_device, QMC_ADDR<<1, 0x09, 1, &config_data, 1, 100)==HAL_OK){
				return 1;
			}
		}

	}
	return 0;
}


xyz QMC_readXYZ(){
	uint8_t rawData[6];
	xyz data;
	if (HAL_I2C_Mem_Read(_QMC_i2c_port, QMC_ADDR<<1, 0x00, I2C_MEMADD_SIZE_8BIT, rawData, 6, HAL_MAX_DELAY) == HAL_OK) {
		data.x = (int16_t)(rawData[0] | (rawData[1] << 8));
		data.y = (int16_t)(rawData[2] | (rawData[3] << 8));
		data.z = (int16_t)(rawData[4] | (rawData[5] << 8));

		return data;
	}
	data.x = 0;
	data.y = 0;
	data.z = 0;

	return data;
}

int16_t QMC_getAzimuth(){
	xyz data = QMC_readXYZ();
	int16_t a = atan2(data.y,data.x)*180.0/PI;
	return a<0? 360+a:a;
}

/*
Segment	  Bearing Value 	Direction

0		   	0°          	North
1			22.5°			North-East
2			45°				East
3			67.5°			South-East
4			90°				South
5			112.5°			South-West
6			135°			West
7			157.5°			North-West
8			180°			South
9			202.5°			South-East
10			225°			East
11			247.5°			North-East
12			270°			North
13			292.5°			North-West
14			315°			West
15			337.5°			South-West

*/

uint8_t QMC_getBearing() {
    float a = QMC_getAzimuth() / 22.5;
    float r = a - (int)a;
    uint8_t segmentIndex = 0;
    segmentIndex = (r >= 0.5) ? (uint8_t)ceil(a) : (uint8_t)floor(a);
    return segmentIndex % 16;
}

