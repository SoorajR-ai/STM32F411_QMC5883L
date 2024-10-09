#ifndef QMC5883L_QMC_H_
#define QMC5883L_QMC_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include <math.h>

#define QMC_ADDR 0x0D

extern I2C_HandleTypeDef *_QMC_i2c_port; // Change this to a pointer

#define PI 3.1415926535897932384626433832795


typedef struct{
	int16_t x;
	int16_t y;
	int16_t z;
}xyz;

uint8_t QMC_init(I2C_HandleTypeDef *hi2c_device);

xyz QMC_readXYZ();

int16_t QMC_getAzimuth();

uint8_t QMC_getBearing();


#endif
