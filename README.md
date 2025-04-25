# Cansat 2025 Ground Station - Sky's Rift Team

A comprehensive Ground Station Software System for Cansat using ESP32, featuring real-time telemetry data visualization, LoRa communication, and a modern web interface. The system implements a robust ground station solution with features including real-time data monitoring, data logging, and a responsive web dashboard.

## About

This is the Ground Station Software component developed by **Sky's Rift** team for the Thailand CANSAT - ROCKET Competition 2025. The Ground Station Software System is designed to provide real-time monitoring and control capabilities for the Cansat payload during the competition, featuring telemetry data visualization, LoRa communication, and a modern web interface.

## Project Overview

This project implements a ground station system that:
- Receives and processes telemetry data via LoRa communication
- Provides real-time data visualization through a web interface
- Implements WebSocket for live data updates
- Features a responsive and modern web dashboard
- Includes data logging capabilities

## Hardware Requirements

- ESP32 Development Board
- LoRa Module (compatible with ESP32)
- Jumper Wires
- USB Cable for programming
- Computer for running the ground station software

## Software Requirements

### ESP32 Firmware
- Arduino IDE or PlatformIO
- Required Libraries:
  - ESP32 board support package
  - LoRa library
  - WebServer library
  - WebSockets library
  - WiFi library

### Web Server
- Node.js (v14 or higher)
- Required npm packages:
  - Express
  - Socket.io
  - Other dependencies (listed in package.json)

## Installation

### ESP32 Firmware Setup
1. Install Arduino IDE or PlatformIO
2. Install required libraries:
   - Open Arduino IDE
   - Go to Tools > Manage Libraries
   - Search and install:
     - LoRa
     - WebServer
     - WebSockets
     - WiFi

3. Clone this repository:
```bash
git clone https://github.com/itertius/Cansat2025.git
```

4. Open `main/main.ino` in Arduino IDE

## Hardware Setup

1. Connect LoRa Module to ESP32:
   - VCC to 3.3V
   - GND to GND
   - SCK to GPIO18
   - MISO to GPIO19
   - MOSI to GPIO23
   - NSS to GPIO5
   - RST to GPIO14
   - DIO0 to GPIO2

2. Connect ESP32 to computer via USB

## Configuration

Key parameters in the code that can be adjusted:
- WiFi credentials in `wwifi.h`
- LoRa frequency and settings in `llora.h`
- Web server port and settings in `wwebserver.h`

## Usage

1. Upload the firmware to ESP32
2. Start the web server
3. Connect to the web interface (default: http://localhost:3000)
4. The system will:
   - Initialize WiFi and LoRa connections
   - Start the web server
   - Begin receiving and displaying telemetry data
   - Provide real-time updates via WebSocket

## Project Structure

```
Cansat2025/
├── main/                 # ESP32 firmware
│   ├── main.ino          # Main firmware file
│   ├── llora.*           # LoRa communication
│   ├── wwifi.*           # WiFi configuration
│   ├── wwebserver.*      # Web server implementation
│   ├── wwebsocket.*      # WebSocket handling
│   └── webpage.*         # Web interface
└── webserver/
    ├── app.js            # Server application
    ├── index.html        # Web interface
    └── styles.css        # Styling
```

## Features

- Real-time telemetry data visualization
- Responsive web dashboard
- LoRa communication
- WebSocket for live updates
- Data logging capabilities
- Modern and intuitive user interface

## Contributing

This project is licensed under GPL-3.0. Any contributions must be made under the same license terms. By contributing, you agree that your contributions will be licensed under the GPL-3.0 license.

## Author

- **Itertius** - [Instagram](https://www.instagram.com/iterrius_te/)

## License

This project is licensed under the GNU General Public License v3.0 (GPL-3.0) - see the [LICENSE](LICENSE) file for details.

GPL-3.0 is a copyleft license that requires anyone who distributes your code or a derivative work to make the source available under the same terms. This license also provides a warranty of title.