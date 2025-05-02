# Cansat 2025 - Sky's Rift Team

A comprehensive Cansat system developed for the Thailand CANSAT - ROCKET Competition 2025, featuring deployment software, flight software, ground station software, simulation, and module testing capabilities.

## About

This repository includes Ground Station software, Deployment system, and Flight software for the Thailand CANSAT - ROCKET Competition 2025. The system consists of multiple integrated components working together to ensure reliable and safe operation of the Cansat payload during the competition.

## Repository Structure

This repository is organized into multiple branches, each containing a specific component of the Cansat system:

### Branches
- `master` - Main branch containing project documentation
- `Deployment` - Deployment Software implementation
- `FSW` - Flight Software implementation
- `Ground` - Ground Station Software and web server
- `Simulation` - Flight Simulation Software
- `test` - Module Testing Software

To access different components, switch to the respective branch:
```bash
git checkout <branch-name>
```

## Project Components

### 1. Deployment Software (Deployment branch)
A specialized system using ESP32/Arduino Nano with MPU6050 accelerometer for launch detection and servo-controlled deployment mechanism.

**Key Features:**
- Launch detection using MPU6050
- Normal and emergency ejection mechanisms
- Safety features and timing mechanisms
- Moving average filter for stable readings

### 2. Flight Software (FSW branch)
A comprehensive system using ESP32 for sensor integration, data collection, and deployment control.

**Key Features:**
- Real-time sensor data collection
- Environmental monitoring (BMP280)
- Motion tracking (MPU6050)
- GPS position tracking
- LoRa-based wireless telemetry
- Timed data sampling and transmission

### 3. Ground Station Software (Ground branch)
A modern ground station system featuring real-time telemetry visualization and LoRa communication.

**Key Features:**
- Real-time data visualization
- Web-based dashboard
- LoRa communication
- WebSocket for live updates
- Data logging capabilities

### 4. Flight Simulation Software (Simulation branch)
A 3D visualization and simulation tool for the Thailand CANSAT - ROCKET Competition 2025.

**Key Features:**
- Real-time sensor data visualization
- Flight path simulation
- 3D visualization of Cansat
- Environmental condition simulation
- Performance analysis tools

### 5. Module Testing Software (test branch)
A comprehensive testing system for validating Cansat components.

**Key Features:**
- Component validation
- Performance testing
- Safety checks
- Integration testing
- Detailed logging

## Hardware Requirements

### Common Requirements
- ESP32 Development Board
- Jumper Wires
- Breadboard (optional)
- USB Cable for programming

### Specific Requirements
- **Deployment System:**
  - MPU6050 Accelerometer
  - Servo Motor

- **Flight System:**
  - MPU6050 IMU Sensor
  - BMP280 Pressure/Temperature Sensor
  - GPS Module
  - LoRa Module

- **Ground Station:**
  - LoRa Module
  - Computer for running ground station software

- **Simulation:**
  - Computer with 3D graphics capability
  - Modern web browser

## Software Requirements

### Common Requirements
- Arduino IDE or PlatformIO
- Required Libraries:
  - Wire.h (built-in)
  - SPI.h (built-in)
  - Serial.h (built-in)

### Specific Requirements
- **Deployment System:**
  - Adafruit_MPU6050.h
  - Adafruit_Sensor.h
  - Servo.h

- **Flight System:**
  - Adafruit_BMP280.h
  - Adafruit_MPU6050.h
  - TinyGPSPlus.h
  - LoRa.h

- **Ground Station:**
  - Node.js (v14 or higher)
  - Express
  - Socket.io

- **Simulation:**
  - Three.js
  - WebGL compatible browser
  - Node.js (for local development)

## Installation

1. Clone this repository:
```bash
git clone https://github.com/itertius/Cansat2025.git
```

2. Switch to the desired branch:
```bash
git checkout <branch-name>
```

3. Install required software:
   - Arduino IDE or PlatformIO
   - Node.js (for ground station and simulation)
   - Required libraries (see individual component documentation)

## Contributing

This project is licensed under GPL-3.0. Any contributions must be made under the same license terms. By contributing, you agree that your contributions will be licensed under the GPL-3.0 license.

## Author

- **iterrius** - [Instagram](https://www.instagram.com/iterrius_te/)

## License

This project is licensed under the GNU General Public License v3.0 (GPL-3.0) - see the [LICENSE](LICENSE) file for details.

GPL-3.0 is a copyleft license that requires anyone who distributes your code or a derivative work to make the source available under the same terms. This license also provides a warranty of title.