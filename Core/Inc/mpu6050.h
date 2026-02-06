#ifndef MPU6050_H
#define MPU6050_H

#include "stm32g0xx_hal.h"

/* I2C address (HAL expects 8-bit) */
/*Primary address length arranged as 7 bit
  Last bit represent the read/write operations*/

#define MPU6050_ADDR        (0x68 << 1)

/* Registers */
#define MPU6050_WHO_AM_I    0x75
#define MPU6050_PWR_MGMT_1  0x6B
#define MPU6050_ACCEL_XOUT  0x3B
#define MPU6050_GYRO_XOUT   0x43
#define ACCEL_CONFIG        0x1C

/* Sensitivity */
#define ACCEL_SENS_2G      16384.0f
#define GYRO_SENS_250DPS   131.0f

typedef struct {
    float ax, ay, az;
    float gx, gy, gz;
} IMU_Data_t;

typedef struct {
    float gyro_rms;
    float tilt;
    float ax, ay, az;
    float air_time;
    float avg_gx;
    float avg_gy;
    float avg_gz;
} Feature_t;


HAL_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef MPU6050_Read(IMU_Data_t *data);

void MPU6050_CalibrateGyro(void);

#endif
