# Flight Simulation Software - Sky's Rift Team

A 3D visualization and simulation tool for the Thailand CANSAT - ROCKET Competition 2025, featuring real-time sensor data visualization and flight path simulation.

## About

This project provides a web-based 3D simulation environment for visualizing Cansat flight data, including sensor readings, flight path, and real-time status updates. The simulation helps in analyzing and understanding the behavior of the Cansat during its mission.

## Features

- **3D Visualization**
  - Real-time 3D rendering of Cansat flight path
  - Terrain visualization
  - Dynamic camera controls
  - Smooth animations

- **Sensor Data Display**
  - BMP280 Sensor Data
    - Temperature
    - Pressure
    - Altitude
  - GY-521 IMU Data
    - 3-axis Acceleration
    - 3-axis Gyroscope
  - GPS Data
    - Latitude
    - Longitude
    - Altitude

- **Data Processing**
  - CSV data import and processing
  - Real-time data interpolation
  - Flight status tracking
  - Time-based data visualization

## Project Structure

```
.
├── app.js              # Main application logic and 3D visualization
├── index.html          # Web interface and layout
├── styles.css          # Styling for the web interface
├── generate.py         # Data generation script
├── log.csv             # Sample flight data
└── README.md           # Project documentation
```

## Technologies Used

- **Frontend**
  - Three.js for 3D rendering
  - HTML5 and CSS3
  - JavaScript (ES6+)

- **Data Processing**
  - Python for data generation
  - CSV data format

## Installation

1. Clone the repository:
```bash
git clone -b Simulation https://github.com/itertius/Cansat2025.git
```

2. Install dependencies:
   - No additional dependencies required for the web interface
   - For data generation, ensure Python is installed

3. Run the simulation:
   - Open `index.html` in a modern web browser
   - For data generation, run `python generate.py`

## Usage

1. Open the web interface in your browser
2. The simulation will automatically load and display:
   - 3D visualization of the Cansat
   - Real-time sensor data
   - Flight path
   - Current status

3. Interact with the visualization:
   - Use mouse to rotate the view
   - Scroll to zoom in/out
   - Pan to move the camera

## Data Format

The simulation accepts CSV data with the following format:
- Time-based sensor readings
- GPS coordinates
- IMU data
- Environmental data

## Contributing

This project is licensed under GPL-3.0. Any contributions must be made under the same license terms. By contributing, you agree that your contributions will be licensed under the GPL-3.0 license.

## License

This project is licensed under the GNU General Public License v3.0 (GPL-3.0) - see the [LICENSE](LICENSE) file for details.

## Author

- **iterrius** - [Instagram](https://www.instagram.com/iterrius_te/)

## Acknowledgments

- Three.js community for the excellent 3D visualization library
- The Cansat competition organizers for providing the platform
- All contributors and supporters of the project
