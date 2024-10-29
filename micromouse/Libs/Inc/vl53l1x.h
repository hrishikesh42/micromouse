#ifndef VL53L1X_H
#define VL53L1X_H

#include "stm32f4xx_hal.h"

// Define the VL53L1X handle structure
typedef struct {
    I2C_HandleTypeDef* i2cHandle; // Pointer to the I2C handle
} VL53L1X_Handle;

// Function declarations
HAL_StatusTypeDef VL53L1X_Init(VL53L1X_Handle* handle);
HAL_StatusTypeDef VL53L1X_ReadDistance(VL53L1X_Handle* handle, uint16_t* distance);

#endif // VL53L1X_H
