# Real-Time Human Activity Recognition System with IMU & RTOS

This project implements a motion-based game control system that identifies human activities (walking, running, sitting, standing, jumping) in real-time. The system uses an IMU sensor attached to the user's leg and transmits control commands wirelessly via Bluetooth.

[Hardware of System](hardware_of_system.png)

## Key Engineering Highlights
- [cite_start]**Microcontroller:** STM32 Nucleo-G070RB[cite: 2797].
- [cite_start]**Operating System:** **FreeRTOS** was utilized to manage concurrent tasks (Sensor Data Acquisition, Feature Extraction, and Motion Classification)[cite: 2797, 3444].
- [cite_start]**Sensors & Connectivity:** - **MPU6050** (Accelerometer + Gyroscope) via **I2C**[cite: 2802, 3117].
  - [cite_start]**HC-05 Bluetooth Module** via **UART** for wireless interaction[cite: 2802, 3448].
- [cite_start]**Robustness Engineering:** Developed a specialized logic to distinguish "Running" from "Jumping" by implementing an **Air-Time Counter** and threshold-based AND conditions[cite: 3456, 3462].

## System Architecture & RTOS Tasks
[cite_start]The software architecture is divided into three prioritized FreeRTOS tasks to ensure deterministic real-time behavior[cite: 3444]:

1. [cite_start]**IMU Task:** High-priority task reading raw acceleration and angular velocity at a fixed 200Hz rate[cite: 3444, 3445].
2. [cite_start]**Feature Task:** Processes raw data to calculate Gyro RMS and Average values over a sliding window[cite: 3444, 3446].
3. [cite_start]**Classifier Task:** Implements the decision logic to trigger commands (WALKING, JUMPING, TURN LEFT/RIGHT) based on extracted features[cite: 3444, 3447].

[Pin Configurations](pin_configurations.png)

## Performance & Testing
- [cite_start]**Experimental Results:** The system achieved **100% accuracy** in detecting Sitting, Walking, Jumping, and Turning motions[cite: 3500].
- [cite_start]**Challenge Solved:** Reduced false jump detections during continuous running by analyzing "Free-Fall" moments (acceleration magnitude near zero) for 6 consecutive cycles[cite: 3462, 3463].

[Running-Jumping Error from Terminal](terminal.png)
[Accuracy Test](accuracy_test.png)

## Tech Stack
- **Languages/IDE:** C, STM32CubeIDE.
- **Middleware:** FreeRTOS.
- [cite_start]**Communication:** I2C (400kHz Fast Mode), UART (115200 baud)[cite: 2997, 3076].
