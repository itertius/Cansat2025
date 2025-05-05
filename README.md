# Flight Software - Sky's Rift Team

A comprehensive Flight Software System for Cansat using ESP32, featuring sensor integration, data collection, and deployment control. The system includes MPU6050 accelerometer for launch detection, BMP280 for environmental monitoring, GPS for position tracking, and LoRa for wireless communication.

## About

This is the flight software developed by **Sky's Rift** team for the Thailand CANSAT - ROCKET Competition 2025. The Flight Software System is designed to manage all aspects of the Cansat payload during the competition, including sensor data collection, deployment control, and telemetry transmission.

## Project Overview

This Flight Software System implements:
- Real-time sensor data collection and processing
- Environmental monitoring with BMP280 (temperature, pressure, altitude)
- Motion tracking with MPU6050 (acceleration and gyroscope)
- GPS position tracking (latitude, longitude, altitude)
- LoRa-based wireless telemetry transmission
- Timed data sampling and transmission
- Data packet formatting and transmission

## Hardware Requirements

- ESP32 Development Board
- MPU6050 IMU Sensor
- BMP280 Pressure/Temperature Sensor
- GPS Module
- LoRa Module
- Jumper Wires
- Breadboard (optional)

## Software Requirements

- Arduino IDE
- Required Libraries:
  - Built-in Libraries:
    - Wire.h
    - SPI.h
  - External Libraries:
    - Adafruit BMP280 Library
    - Adafruit MPU6050 Library
    - Adafruit Unified Sensor Library
    - TinyGPSPlus Library
    - LoRa Library
  - Custom Libraries:
    - bmp.h/cpp (uses Adafruit_BMP280)
    - mpu.h/cpp (uses Adafruit_MPU6050)
    - gps.h/cpp (uses TinyGPSPlus)
    - llora.h/cpp (uses LoRa)

## Installation

1. Install Arduino IDE
2. Install required libraries:
   - Open Arduino IDE
   - Go to Tools > Manage Libraries
   - Search and install:
     - LoRa

3. Clone this branch:
```bash
git clone -b FSW https://github.com/itertius/Cansat2025.git
```

4. Open `main/main.ino` in Arduino IDE

## Hardware Setup

1. Connect BMP280:
   - VCC to 3.3V
   - GND to GND
   - SCL to SCL
   - SDA to SDA

2. Connect MPU6050:
   - VCC to 3.3V
   - GND to GND
   - SCL to SCL
   - SDA to SDA

3. Connect GPS Module:
   - VCC to 3.3V
   - GND to GND
   - TX to RX
   - RX to TX

4. Connect LoRa Module:
   - VCC to 3.3V
   - GND to GND
   - SCK to SCK
   - MISO to MISO
   - MOSI to MOSI
   - NSS to pin 10
   - RST to pin 9
   - DIO0 to pin 2

## Configuration

Key parameters in the code that can be adjusted:
- `b_interval`: BMP280 data sampling interval (1000ms)
- `m_interval`: MPU6050 data sampling interval (500ms)
- `g_interval`: GPS data sampling interval (5000ms)
- `sl`: Sea level pressure for altitude calculation (1013.5 hPa)

## Usage

1. Upload the code to your ESP32
2. Open Serial Monitor (115200 baud)
3. The system will:
   - Initialize all sensors
   - Sample data at configured intervals:
     - BMP280: Temperature, pressure, altitude
     - MPU6050: Acceleration (x,y,z) and gyroscope (x,y,z)
     - GPS: Latitude, longitude, altitude
   - Format and transmit data via LoRa

## Features

- Real-time sensor data collection
- GPS position tracking
- IMU-based motion tracking
- Pressure and temperature measurements
- LoRa-based wireless communication
- Timed data sampling
- Data packet formatting

## Contributing

This project is licensed under GPL-3.0. Any contributions must be made under the same license terms. By contributing, you agree that your contributions will be licensed under the GPL-3.0 license.

## Author

- **iterrius** - [Instagram](https://www.instagram.com/iterrius_te/)

## License

This project is licensed under the GNU General Public License v3.0 (GPL-3.0) - see the [LICENSE](LICENSE) file for details.

GPL-3.0 is a copyleft license that requires anyone who distributes your code or a derivative work to make the source available under the same terms. This license also provides a warranty of title.
