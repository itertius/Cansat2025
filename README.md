# Cansat 2025 - Sky's Rift Team

A specialized Module Testing Software System for Cansat using ESP32/Arduino Nano, designed to ensure reliable testing and validation of various Cansat components. The system implements comprehensive testing procedures with safety features and detailed logging capabilities.

## About

This is the module testing software component developed by **Sky's Rift** team for the Thailand CANSAT - ROCKET Competition 2025. The Module Testing Software System is designed to facilitate thorough testing and validation of Cansat components, ensuring reliability and performance during the competition.

## Project Overview

This project implements a testing system that:
- Provides comprehensive module testing capabilities
- Implements safety protocols and validation checks
- Features detailed logging and monitoring
- Includes automated test procedures

## Hardware Requirements

- ESP32 Development Board
- Various Cansat components to be tested
- Jumper Wires
- Breadboard (optional)
- USB cable for programming

## Software Requirements

- Arduino IDE
- Required Libraries:
  - Core Libraries:
    - Wire.h (built-in)
    - SPI.h (built-in)
    - Serial.h (built-in)
  - Sensor Libraries:
    - Adafruit_MPU6050
    - Adafruit_Sensor
    - Adafruit_BMP280
    - TinyGPSPlus
  - Communication Libraries:
    - LoRa

## Installation

1. Install Arduino IDE
2. Install required libraries:
   - Open Arduino IDE
   - Go to Tools > Manage Libraries
   - Search and install any required libraries

3. Clone this repository:
```bash
git clone https://github.com/itertius/Cansat2025.git
```

4. Open the appropriate test module file in Arduino IDE

## Hardware Setup

1. Connect the Cansat components according to the specific test module requirements
2. Ensure proper power supply connections
3. Connect the programming interface (USB cable)

## Configuration

Key parameters in the code that can be adjusted:
- Test duration settings
- Threshold values for various tests
- Logging intervals
- Safety parameters

## Usage

1. Upload the code to your board
2. Open Serial Monitor (baud rate as specified in the code)
3. The system will:
   - Initialize and perform self-checks
   - Execute the specified test procedures
   - Log results and provide feedback
   - Implement safety protocols as needed

## Test Modules

The software includes various test modules for:
- Component validation
- Performance testing
- Safety checks
- Integration testing

## Safety Features

- Automatic safety checks
- Error detection and handling
- Emergency protocols
- Detailed logging for analysis

## Contributing

This project is licensed under GPL-3.0. Any contributions must be made under the same license terms. By contributing, you agree that your contributions will be licensed under the GPL-3.0 license.

## Author

- **Itertius** - [Instagram](https://www.instagram.com/iterrius_te/)

## License

This project is licensed under the GNU General Public License v3.0 (GPL-3.0) - see the [LICENSE](LICENSE) file for details.

GPL-3.0 is a copyleft license that requires anyone who distributes your code or a derivative work to make the source available under the same terms. This license also provides a warranty of title.