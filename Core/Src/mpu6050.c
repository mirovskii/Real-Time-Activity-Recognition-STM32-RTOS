#include "mpu6050.h"


static I2C_HandleTypeDef *mpu_i2c;

static float gyro_bias[3] = {0};

HAL_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef *hi2c)
{
	mpu_i2c = hi2c;
    uint8_t data;
    HAL_StatusTypeDef ret;

    /* Wake up device */
    data = 0x00;
    /**
      * @brief  Write an amount of data in blocking mode to a specific memory address
      * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
      *                the configuration information for the specified I2C.
      * @param  DevAddress Target device address: The device 7 bits address value
      *         in datasheet must be shifted to the left before calling the interface
      * @param  MemAddress Internal memory address
      * @param  MemAddSize Size of internal memory address
      * @param  pData Pointer to data buffer
      * @param  Size Amount of data to be sent
      * @param  Timeout Timeout duration
      * @retval HAL status
      */
    ret = HAL_I2C_Mem_Write(mpu_i2c, MPU6050_ADDR, MPU6050_PWR_MGMT_1, 1, &data, 1, HAL_MAX_DELAY);

    if (ret != HAL_OK) return ret; // Check for errors

    // Set accelerometer to ±2g
    data = 0x00;  // AFS_SEL = 0 → ±2g
    ret = HAL_I2C_Mem_Write(mpu_i2c, MPU6050_ADDR, ACCEL_CONFIG, 1, &data, 1, HAL_MAX_DELAY);

    return ret;
}

HAL_StatusTypeDef MPU6050_Read(IMU_Data_t *data) //Read raw accelerometer and gyroscope registers from MPU6050
{ 												 //Convert them into physical units
    uint8_t buf[14];
    int16_t raw_ax, raw_ay, raw_az;
    int16_t raw_gx, raw_gy, raw_gz;

    if (HAL_I2C_Mem_Read(mpu_i2c, MPU6050_ADDR, MPU6050_ACCEL_XOUT, 1, buf, 14, HAL_MAX_DELAY) != HAL_OK)
        return HAL_ERROR;

    // Combine high and low bytes
    raw_ax = (buf[0] << 8) | buf[1];
    raw_ay = (buf[2] << 8) | buf[3];
    raw_az = (buf[4] << 8) | buf[5];

    raw_gx = (buf[8] << 8) | buf[9];
    raw_gy = (buf[10] << 8) | buf[11];
    raw_gz = (buf[12] << 8) | buf[13];

    //Convert accelerometer to g : Raw/16384
    data->ax = raw_ax / ACCEL_SENS_2G;
    data->ay = raw_ay / ACCEL_SENS_2G;
    data->az = raw_az / ACCEL_SENS_2G;
    //Convert gyro to degree/second with removing bias.
    //Sensitivity = Raw/131, Corrected = Measured - bias
    data->gx = (raw_gx / GYRO_SENS_250DPS) - gyro_bias[0];
    data->gy = (raw_gy / GYRO_SENS_250DPS) - gyro_bias[1];
    data->gz = (raw_gz / GYRO_SENS_250DPS) - gyro_bias[2];

    return HAL_OK;
}
void MPU6050_CalibrateGyro(void)
{
    IMU_Data_t data;
    const int samples = 500;

    gyro_bias[0] = 0;
    gyro_bias[1] = 0;
    gyro_bias[2] = 0;

    //Accumulate gyro output
    for (int i = 0; i < samples; i++) {
        MPU6050_Read(&data);
        gyro_bias[0] += data.gx;
        gyro_bias[1] += data.gy;
        gyro_bias[2] += data.gz;
        HAL_Delay(5);
    }
    //Compute average bias
    gyro_bias[0] /= samples;
    gyro_bias[1] /= samples;
    gyro_bias[2] /= samples;
}



