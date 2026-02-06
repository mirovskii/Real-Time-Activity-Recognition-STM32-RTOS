# Real-Time Human Activity Recognition System with IMU & RTOS

This project implements a motion-based game control system that identifies human activities (walking, running, sitting, standing, jumping) in real-time. The system uses an IMU sensor attached to the user's leg and transmits control commands wirelessly via Bluetooth.

[Hardware of System](hardware_of_system.png)

## Key Engineering Highlights
- **Microcontroller:** STM32 Nucleo-G070RB.
- **Operating System:** **FreeRTOS** was utilized to manage concurrent tasks (Sensor Data Acquisition, Feature Extraction, and Motion Classification).
- **Sensors & Connectivity:** - **MPU6050** (Accelerometer + Gyroscope) via **I2C**.
- **HC-05 Bluetooth Module** via **UART** for wireless interaction.
- **Robustness Engineering:** Developed a specialized logic to distinguish "Running" from "Jumping" by implementing an **Air-Time Counter** and threshold-based AND conditions.

## System Architecture & RTOS Tasks
The software architecture is divided into three prioritized FreeRTOS tasks to ensure deterministic real-time behavior:

1. **IMU Task:** High-priority task reading raw acceleration and angular velocity at a fixed 200Hz rate.
2. **Feature Task:** Processes raw data to calculate Gyro RMS and Average values over a sliding window.
3. **Classifier Task:** Implements the decision logic to trigger commands (WALKING, JUMPING, TURN LEFT/RIGHT) based on extracted features.

[Pin Configurations](pin_configurations.png)

## Performance & Testing
- **Experimental Results:** The system achieved **100% accuracy** in detecting Sitting, Walking, Jumping, and Turning motions.
- **Challenge Solved:** Reduced false jump detections during continuous running by analyzing "Free-Fall" moments (acceleration magnitude near zero) for 6 consecutive cycles.

[Running-Jumping Error from Terminal](terminal.png)

[Accuracy Test](accuracy_test.png)

## Tech Stack
- **Languages/IDE:** C, STM32CubeIDE.
- **Middleware:** FreeRTOS.
- **Communication:** I2C (400kHz Fast Mode), UART (115200 baud).
