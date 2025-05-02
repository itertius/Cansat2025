// Global variables
let scene, camera, renderer;
let cansat, terrain, flightLine;
let flightPath;
let t = 0;
let sensorData = {
    bmp280: { temp: [], press: [], alt: [], time: [] },
    gy521: { ax: [], ay: [], az: [], gx: [], gy: [], gz: [], time: [] },
    gps: { lat: [], lng: [], alt: [], time: [] }
};
let currentTime = 0;
let maxTime = 0;
let statusData = [];
let isDataLoaded = false;
let lastStatus = '';

// Initialize the scene
function init() {
    // Scene setup
    scene = new THREE.Scene();
    scene.background = new THREE.Color(0xffffff);
    camera = new THREE.PerspectiveCamera(60, window.innerWidth / window.innerHeight, 1, 1000);
    renderer = new THREE.WebGLRenderer({ canvas: document.getElementById('cansat'), antialias: true });
    renderer.setSize(window.innerWidth, window.innerHeight);
    camera.position.set(0, 50, 100);

    // Add lights
    setupLights();
    
    // Create objects
    createTerrain();
    createCanSat();
    createDefaultFlightPath();

    // Load and process CSV data
    loadCSVData();

    // Handle window resize
    window.addEventListener('resize', onWindowResize);
}

// Setup lighting
function setupLights() {
    const light = new THREE.DirectionalLight(0xffffff, 1);
    light.position.set(50, 100, 50);
    scene.add(light);
}

// Create terrain
function createTerrain() {
    const terrainGeometry = new THREE.PlaneGeometry(200, 200, 64, 64);
    terrainGeometry.rotateX(-Math.PI / 2);
    for (let i = 0; i < terrainGeometry.attributes.position.count; i++) {
        const y = Math.random() * 10;
        terrainGeometry.attributes.position.setY(i, y);
    }
    terrainGeometry.computeVertexNormals();
    const terrainMaterial = new THREE.MeshStandardMaterial({ color: 0x228b22, wireframe: false });
    terrain = new THREE.Mesh(terrainGeometry, terrainMaterial);
    scene.add(terrain);
}

// Create CanSat object
function createCanSat() {
    const cansatGeometry = new THREE.SphereGeometry(1.5, 16, 16);
    const cansatMaterial = new THREE.MeshStandardMaterial({ color: 0xff0000 });
    cansat = new THREE.Mesh(cansatGeometry, cansatMaterial);
    scene.add(cansat);
}

// Create default flight path
function createDefaultFlightPath() {
    const pathPoints = [
        new THREE.Vector3(-80, 20, -80),
        new THREE.Vector3(-40, 40, -20),
        new THREE.Vector3(0, 60, 0),
        new THREE.Vector3(40, 30, 40),
        new THREE.Vector3(80, 10, 80)
    ];
    createFlightPathFromPoints(pathPoints);
}

// Create flight path from points
function createFlightPathFromPoints(points) {
    if (flightLine) {
        scene.remove(flightLine);
    }

    flightPath = new THREE.CatmullRomCurve3(points);
    const flightGeometry = new THREE.TubeGeometry(flightPath, 100, 0.2, 8, false);
    const flightMaterial = new THREE.MeshBasicMaterial({ color: 0xffff00 });
    flightLine = new THREE.Mesh(flightGeometry, flightMaterial);
    scene.add(flightLine);
}

// Load and process CSV data
function loadCSVData() {
    fetch('log1.csv')
        .then(response => response.text())
        .then(csvData => {
            processCSVData(csvData);
            createFlightPathFromGPSData();
            isDataLoaded = true;
        })
        .catch(error => {
            console.error('Error loading CSV:', error);
            // Keep default flight path if CSV loading fails
            isDataLoaded = true;
        });
}

// Process CSV data
function processCSVData(csvData) {
    const lines = csvData.split('\n');
    let startTime = null;

    for (let i = 1; i < lines.length; i++) { // Skip header
        const line = lines[i].trim();
        if (!line) continue;

        const values = line.split(',');
        if (values.length < 4) continue;

        const cmd = parseInt(values[0]);
        const time = new Date(values[1]).getTime();
        const module = values[2];

        if (startTime === null) {
            startTime = time;
        }
        const relativeTime = (time - startTime) / 1000; // Convert to seconds

        if (cmd === 0) {
            switch (module) {
                case "BMP280":
                    if (values.length >= 6) {
                        sensorData.bmp280.temp.push({ time: relativeTime, value: parseFloat(values[3]) });
                        sensorData.bmp280.press.push({ time: relativeTime, value: parseFloat(values[4]) });
                        sensorData.bmp280.alt.push({ time: relativeTime, value: parseFloat(values[5]) });
                    }
                    break;
                case "GY-521":
                    if (values.length >= 9) {
                        sensorData.gy521.ax.push({ time: relativeTime, value: parseFloat(values[3]) });
                        sensorData.gy521.ay.push({ time: relativeTime, value: parseFloat(values[4]) });
                        sensorData.gy521.az.push({ time: relativeTime, value: parseFloat(values[5]) });
                        sensorData.gy521.gx.push({ time: relativeTime, value: parseFloat(values[6]) });
                        sensorData.gy521.gy.push({ time: relativeTime, value: parseFloat(values[7]) });
                        sensorData.gy521.gz.push({ time: relativeTime, value: parseFloat(values[8]) });
                    }
                    break;
                case "GPS":
                    if (values.length >= 6) {
                        sensorData.gps.lat.push({ time: relativeTime, value: parseFloat(values[3]) });
                        sensorData.gps.lng.push({ time: relativeTime, value: parseFloat(values[4]) });
                        sensorData.gps.alt.push({ time: relativeTime, value: parseFloat(values[5]) });
                    }
                    break;
            }
        } else if (cmd === 1 && module === "status") {
            statusData.push({ time: relativeTime, status: values[3] });
        }
    }

    maxTime = Math.max(
        ...sensorData.gps.time,
        ...sensorData.bmp280.time,
        ...sensorData.gy521.time
    );
}

// Create flight path from GPS data
function createFlightPathFromGPSData() {
    if (sensorData.gps.lat.length === 0) {
        console.warn('No GPS data available, using default flight path');
        return;
    }

    const points = [];
    for (let i = 0; i < sensorData.gps.lat.length; i++) {
        // Convert GPS coordinates to local coordinates
        const x = (sensorData.gps.lng[i].value - sensorData.gps.lng[0].value) * 100000;
        const z = (sensorData.gps.lat[i].value - sensorData.gps.lat[0].value) * 100000;
        const y = sensorData.gps.alt[i].value;
        points.push(new THREE.Vector3(x, y, z));
    }

    if (points.length > 0) {
        createFlightPathFromPoints(points);
    } else {
        console.warn('No valid points for flight path, using default');
    }
}

// Handle window resize
function onWindowResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
}

// Update sensor data display
function updateSensorDisplay(time) {
    // Update BMP280 data
    const bmpData = getInterpolatedData(sensorData.bmp280, time);
    if (bmpData) {
        document.getElementById('temp').textContent = bmpData.temp.toFixed(1);
        document.getElementById('press').textContent = bmpData.press.toFixed(2);
        document.getElementById('alt').textContent = bmpData.alt.toFixed(1);
        
        // Log BMP280 data
        console.log(`[${formatTime(time)}] BMP280: Temp=${bmpData.temp.toFixed(1)}°C, Press=${bmpData.press.toFixed(2)}hPa, Alt=${bmpData.alt.toFixed(1)}m`);
    }

    // Update GY-521 data
    const gyData = getInterpolatedData(sensorData.gy521, time);
    if (gyData) {
        document.getElementById('ax').textContent = gyData.ax.toFixed(2);
        document.getElementById('ay').textContent = gyData.ay.toFixed(2);
        document.getElementById('az').textContent = gyData.az.toFixed(2);
        document.getElementById('gx').textContent = gyData.gx.toFixed(1);
        document.getElementById('gy').textContent = gyData.gy.toFixed(1);
        document.getElementById('gz').textContent = gyData.gz.toFixed(1);
        
        // Log GY-521 data
        console.log(`[${formatTime(time)}] GY-521: Accel=[${gyData.ax.toFixed(2)},${gyData.ay.toFixed(2)},${gyData.az.toFixed(2)}]g, Gyro=[${gyData.gx.toFixed(1)},${gyData.gy.toFixed(1)},${gyData.gz.toFixed(1)}]°/s`);
    }

    // Update GPS data
    const gpsData = getInterpolatedData(sensorData.gps, time);
    if (gpsData) {
        document.getElementById('lat').textContent = gpsData.lat.toFixed(4);
        document.getElementById('lng').textContent = gpsData.lng.toFixed(4);
        document.getElementById('gpsalt').textContent = gpsData.alt.toFixed(1);
        
        // Log GPS data
        console.log(`[${formatTime(time)}] GPS: Lat=${gpsData.lat.toFixed(4)}°, Lng=${gpsData.lng.toFixed(4)}°, Alt=${gpsData.alt.toFixed(1)}m`);
    }

    // Update status
    const status = getCurrentStatus(time);
    if (status) {
        document.getElementById('status').textContent = status;
        // Log status changes
        if (status !== lastStatus) {
            console.log(`[${formatTime(time)}] Status: ${status}`);
            lastStatus = status;
        }
    }
}

// Format time for logging
function formatTime(seconds) {
    const minutes = Math.floor(seconds / 60);
    const remainingSeconds = Math.floor(seconds % 60);
    const milliseconds = Math.floor((seconds % 1) * 1000);
    return `${minutes.toString().padStart(2, '0')}:${remainingSeconds.toString().padStart(2, '0')}.${milliseconds.toString().padStart(3, '0')}`;
}

// Get interpolated data for a given time
function getInterpolatedData(sensor, time) {
    if (!sensor || !sensor.time || sensor.time.length === 0) return null;

    // Find the two closest data points
    let prevIndex = -1;
    let nextIndex = -1;

    for (let i = 0; i < sensor.time.length; i++) {
        if (sensor.time[i] <= time) {
            prevIndex = i;
        }
        if (sensor.time[i] >= time) {
            nextIndex = i;
            break;
        }
    }

    if (prevIndex === -1) return null;
    if (nextIndex === -1) nextIndex = prevIndex;

    // If we have exact match, return that
    if (prevIndex === nextIndex) {
        return sensor[prevIndex];
    }

    // Interpolate between the two points
    const prevTime = sensor.time[prevIndex];
    const nextTime = sensor.time[nextIndex];
    const factor = (time - prevTime) / (nextTime - prevTime);

    const result = {};
    for (const key in sensor) {
        if (key !== 'time' && sensor[key][prevIndex] !== undefined) {
            result[key] = sensor[key][prevIndex] + 
                         (sensor[key][nextIndex] - sensor[key][prevIndex]) * factor;
        }
    }

    return result;
}

// Get current status
function getCurrentStatus(time) {
    if (!statusData || statusData.length === 0) return "No Status Data";

    for (let i = statusData.length - 1; i >= 0; i--) {
        if (statusData[i].time <= time) {
            return statusData[i].status;
        }
    }

    return "Unknown";
}

// Animation loop
function animate() {
    requestAnimationFrame(animate);
    
    if (!isDataLoaded || !flightPath) {
        return; // Skip animation until data is loaded
    }

    if (maxTime > 0) {
        currentTime += 0.001 * maxTime;
        if (currentTime > maxTime) currentTime = 0;
        t = currentTime / maxTime;
    } else {
        t += 0.001;
        if (t > 1) t = 0;
    }

    try {
        const pos = flightPath.getPointAt(t);
        cansat.position.copy(pos);
        camera.lookAt(cansat.position);
        
        // Update sensor data display
        updateSensorDisplay(currentTime);
    } catch (error) {
        console.error('Error in animation:', error);
        createDefaultFlightPath();
    }
    
    renderer.render(scene, camera);
}

// Start the application
init();
animate();