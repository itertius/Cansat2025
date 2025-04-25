# Deployment Software - Sky's Rift Team

A specialized Deployment Software System for Cansat using ESP32/Arduino Nano, featuring MPU6050 accelerometer for launch detection and servo-controlled deployment mechanism. The system implements a robust deployment algorithm with safety features including emergency ejection, normal ejection based on acceleration thresholds, and a moving average filter for stable readings.

## About

This is the deployment software component developed by **Sky's Rift** team for the Thailand CANSAT - ROCKET Competition 2025. The Deployment Software System is designed to ensure reliable and safe deployment of the Cansat payload during the competition, featuring launch detection, acceleration monitoring, and controlled deployment mechanisms with both normal and emergency ejection capabilities.

## Project Overview

This project implements a deployment system that:
- Detects launch using MPU6050 accelerometer
- Implements both normal and emergency ejection mechanisms
- Uses a servo motor for deployment control
- Includes safety features and timing mechanisms

## Hardware Requirements

- ESP32 or Arduino Nano
- MPU6050 Accelerometer
- Servo Motor
- Jumper Wires
- Breadboard (optional)

## Software Requirements

- Arduino IDE
- Required Libraries:
  - Wire.h (built-in)
  - Adafruit_MPU6050
  - Adafruit_Sensor
  - Servo.h

## Installation

1. Install Arduino IDE
2. Install required libraries:
   - Open Arduino IDE
   - Go to Tools > Manage Libraries
   - Search and install:
     - Adafruit MPU6050
     - Adafruit Unified Sensor
     - Servo

3. Clone this repository:
```bash
git clone https://github.com/itertius/Cansat2025.git
```

4. Open `main/main.ino` in Arduino IDE

## Hardware Setup

1. Connect MPU6050:
   - VCC to 3.3V/5V
   - GND to GND
   - SCL to SCL (A5 on Nano)
   - SDA to SDA (A4 on Nano)

2. Connect Servo:
   - Signal wire to pin 3
   - VCC to 5V
   - GND to GND

## Configuration

Key parameters in the code that can be adjusted:
- `Launch_threshold`: G-force threshold for launch detection
- `Eject_threshold`: Threshold for normal ejection
- `emergency_time`: Time before emergency ejection
- `normal_eject_delay`: Delay before normal ejection
- `window_size`: Size of moving average filter

## Usage

1. Upload the code to your board
2. Open Serial Monitor (115200 baud)
3. The system will:
   - Initialize and calibrate
   - Wait for launch detection
   - Monitor acceleration
   - Trigger deployment based on conditions

## Simulation Links

- [Deployment Simulation (ESP32) v.1](https://wokwi.com/projects/427472783870630913)
- [Deployment Simulation (Arduino Nano) v.1](https://wokwi.com/projects/427820968778860545)
- [Deployment Simulation (Arduino Nano) v.2](https://wokwi.com/projects/427820968778860545)

## Safety Features

- Emergency ejection after timeout
- Moving average filter for stable readings
- Multiple deployment conditions
- Safety checks and error handling

## Contributing

This project is licensed under GPL-3.0. Any contributions must be made under the same license terms. By contributing, you agree that your contributions will be licensed under the GPL-3.0 license.

## Author

- **iterrius** - [Instagram](https://www.instagram.com/iterrius_te/)

## License

This project is licensed under the GNU General Public License v3.0 (GPL-3.0) - see the [LICENSE](LICENSE) file for details.

GPL-3.0 is a copyleft license that requires anyone who distributes your code or a derivative work to make the source available under the same terms. This license also provides a warranty of title.
