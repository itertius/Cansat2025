#include "webpage.h"

const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>


html, body {
    margin: 0;
    padding: 0;
    width: 100%;
    height: 100%;
    font-family: "Prompt", sans-serif;
    background-color: whitesmoke;
}

.parent {
    display: grid;
    grid-template-columns: repeat(4, 1fr);
    grid-template-rows: repeat(6, 1fr);
    gap: 5px;
    width: 100%;
    height: 100%;
}

.head {
    display: flex;
    grid-column: span 4 / span 4;
    background-color: lightblue;
    font-size: x-large;
    font-weight: bold;
    background-color: #050019;
    color: whitesmoke;
}

.head-left, .head-right {
    flex: 1;
    padding: 10px;
    display: flex;
    align-items: center;   /* vertical center */
    justify-content: center; /* horizontal center */
    text-align: center;
}

#runtime {
    margin: 0 10px;
}

.foot {
    display: flex;
    grid-column: span 4 / span 4;
    grid-column-start: 1;
    grid-row-start: 6;
    justify-content: space-between; /* Centered content for the footer */
    align-items: center;
    font-weight: bold;
    background-color: #050019;
    color: whitesmoke;
    padding: 0.5%;
}

.foot-left, .foot-center, .foot-right {
    padding: 0.5%;
}

.foot-left {
    text-align: left;
}

.foot-center {
    text-align: center;
    flex: 1;
    font-size: x-large;
}

.foot-right {
    text-align: right;
}

.c-map {
    grid-column: span 2 / span 2;
    grid-row: span 3 / span 3;
    grid-column-start: 1;
    grid-row-start: 2;
    background-color: lightcoral;
}

.bmp, .gyro, .gps {
    font-size: 1.5vw; /* Adjust this value as needed */
    /* display: flex; */
    align-items: center;
    /* justify-items: center; */
    /* text-align: center; */
    padding: 0.5%;
    background-color: #08021d;
    color: whitesmoke;
}

.plot-bmp, .plot-gy {
    color: whitesmoke;
    background-color: #08021d;
}

.bmp {
    grid-column: span 2 / span 2;
    grid-column-start: 3;
    grid-row-start: 2;
}

.gyro {
    grid-column: span 2 / span 2;
    grid-column-start: 3;
    grid-row-start: 5;
}

.gps {
    grid-column: span 2 / span 2;
    grid-column-start: 1;
    grid-row-start: 5;
}


.plot-bmp {
    grid-row: span 2 / span 2;
    grid-column-start: 3;
    grid-row-start: 3;
}

.plot-gy {
    grid-row: span 2 / span 2;
    grid-column-start: 4;
    grid-row-start: 3;
}

#map {
    width: 100%;
    height: 100%;
}

.title {
    text-align: center; /* Centers the title */
    font-weight: bold;
}

.content {
    align-items: center;
    padding-left: 15%;
}

.content-lr {
    display: flex;
    justify-content: space-around;
}

.content-left {
    text-align: left; /* Align content to the left */
}

.content-right {
    text-align: left; /* Align content to the right */
}

.footer {
    text-align: center; /* Center the footer content */
}

.btn {
    background-color: transparent; 
    color: whitesmoke; 
    border: 2px solid #fff4f4;
    border-radius: 8px;
    padding: 4px 8px;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: medium;
    cursor: pointer;
}
  
.btn:hover {
    background-color: #362e56;
    color: white;
}

#gps-chart {
    background-color: lightcyan;
}

#module-chart {
    background-color: lightgreen;
}

#gps-chart, #module-chart {
    width: 100%;
    height: 100%;
}
    </style>
    <link rel="stylesheet" href="https://unpkg.com/leaflet@1.9.4/dist/leaflet.css" integrity="sha256-p4NxAoJBhIIN+hmNHrzRCf9tD/miZyoHS5obTRR9BMY=" crossorigin="" />
    <script src="https://unpkg.com/leaflet@1.9.4/dist/leaflet.js" integrity="sha256-20nQCchB9co0qIjJZRGuk2/Z9VM+kNiyxNV1lvTlZBo=" crossorigin=""></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/4.4.1/chart.min.js" integrity="sha512-L0Shl7nXXzIlBSUUPpxrokqq4ojqgZFQczTYlGjzONGTDAcLremjwaWv5A+EDLnxhQzY5xUZPWLOLqYRkY0Cbw==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>
    <link href="https://fonts.googleapis.com/css2?family=Prompt:wght@300;400;500;600&display=swap" rel="stylesheet">
    <link rel="icon" type="image/x-icon" href="https://i.ibb.co/FkQXT9gr/Sky-s-Rift-logo.png">
    <title>Sky's Rift Webserver</title>
</head>

<body>

<div class="parent">

    <div class="head">
        <div class="head-left">
            <span id="time"></span>
        </div>
        <div class="head-right">
            Runtime :<span id="runtime">0</span>sec<br>
        </div>
    </div>
     
    <div class="c-map">
        <div id="map"></div>
    </div>
    
    <div class="bmp">
        <div class="title">🌡️ BMP280</div>
    
        <div class="content">
            <div class="temp">
                Temperature : <span id="temp">0</span> °C
            </div>
            <div class="press">
                Pressure : <span id="press">0</span> hPa
            </div>
            <div class="bmp-alt">
                BMP280 Altitude : <span id="bmp-alt">0</span> m
            </div>
        </div>

        <div class="footer">
            <button class="btn" id="bmp-log" onclick="DownloadModuleLog('BMP280')">📤 Download BMP280 Log</button>
        </div>

    </div>
    
    <div class="gyro">
        <div class="title">🧨 GY-521</div>

        <div class="content-lr">
            <div class="content-left">
                <div class="ax">
                    X : <span id="ax">0</span> g
                </div>
                <div class="ay">
                    Y : <span id="ay">0</span> g
                </div>
                <div class="az">
                    Z : <span id="az">0</span> g
                </div>
            </div>
            <div class="content-right">
                <div class="gx">
                    X : <span id="gx">0</span> °/s
                </div>
                <div class="gy">
                    Y : <span id="gy">0</span> °/s
                </div>
                <div class="gz">
                    Z : <span id="gz">0</span> °/s
                </div>
            </div>
        </div>
        
        <div class="footer">
            <button class="btn" id="gy-log" onclick="DownloadModuleLog('GY-521')">📤 Download GY-521 Log</button>
        </div>
        
    </div>

    
    <div class="gps">
        <div class="title">🧭 GY-NEO6MV2 (GPS)</div>
    
        <div class="content">
            <div class="position">ตำแหน่งที่ : <span id="pos">0</span></div>
            <div class="lat">Latitude : <span id="lat">0</span></div>
            <div class="lng">Longitude : <span id="lon">0</span></div>
            <div class="gps-alt">Altitude : <span id="gps-alt">0</span> m</div>
        </div>
    
        <div class="footer">
            <button class="btn" id="gps-log" onclick="DownloadModuleLog('GPS')">📤 Download GPS Log</button>
        </div>

    </div>
    

    <div class="plot-bmp">
        <canvas id="module-chart"></canvas>
    </div>
    <div class="plot-gy">
        <canvas id="gps-chart"></canvas>
    </div>

    <div class="foot">
        <div class="foot-left">
            <div class="title">Status</div>
            <div class="launch">
                Launch : <span id="launch">🔴</span>
            </div>

            <div class="flight">
                In Flight : <span id="flight">🔴</span>
            </div>

            <div class="deploy">
                Deployment : <span id="deploy">🔴</span>
            </div>

            <div class="land">
                Landed : <span id="land">🔴</span>
            </div>
        </div>

        <div class="foot-center">
            <span>Copyright @ Sky's Rift</span>
        </div>
        
        <div class="foot-right">
            <button class="btn" id="log" onclick="Download()">📤 Download Log</button>
        </div>
    </div>

</div>
    

</body>
<script src="app.js"></script>
<!-- <script>main();</script> -->
<script>
// This is a web server for Sky's Rift Team in CANSAT - ROCKET Competition 2025 //


// Data Stream //
// Description: This is a data stream that contains information about the sensors and their data.

// [ "type" , "time" , 
// if type == 0 : [ "module_name" , "module_data" ] 
// if type == 1 : [ "status" , "alt" ]

// Module Data Stream
// [ "module_type" , "data" , ... ]
// BMP280 == 0 : ["0" , "temp" , "press", "alt"]
// GY == 1 : ["1" , "ax" , "ay" , "az" , "gx" , "gy" , "gz"]
// GPS == 2 : ["2" , "lat" , "lon" , "alt"]

// Status Stream
// [ "status" ]

// Status
// 1 : Launch
// 2 : In Flight
// 3 : Landed
// 4 : Error
// 5 : Ejected
// 6 : Not_Ejected

// Log //
// csv format
// if command == 0 ; command, module, data ...
// if command == 1 ; command, status

// ----- //


// Main Code
// Author: iterrius
// Description: Main code for the web server. It includes the main function for initializing the map, updating data, and handling status updates.

const dataStream = [];

// Map funtion //
let mapInit = false;
let count_marker = 0;
let map = null;
let marker = null;

function initMap(lat, lon) {
    if (mapInit) return;
    mapInit = true;
    map = L.map('map', { center: [lat, lon], zoom: 18, zoomControl: false });
    L.tileLayer('http://{s}.google.com/vt/lyrs=s&x={x}&y={y}&z={z}', {
        maxZoom: 22,
        attribution: "Sky's Rift",
        subdomains: ['mt0', 'mt1', 'mt2', 'mt3']
    }).addTo(map);
    // default marker
    count_marker++;
    const defaultMarker = L.marker([lat, lon]).addTo(map);
    defaultMarker.bindPopup(`ตำแหน่งที่ ${count_marker} | เวลา : ${run} sec<br>Latitude: ${lat}<br>Longitude: ${lon}`).openPopup();
}

function updateMarker(lat, lon) {
    if (!mapInit) return;
    count_marker++;
    const mark = L.marker([lat, lon]).addTo(map);
    mark.bindPopup(`ตำแหน่งที่ ${count_marker} | เวลา : ${run} <br>Latitude: ${lat}<br>Longitude: ${lon}`).openPopup();
}

function updateMap(lat, lon) {
    if (!mapInit) return;
    map.panTo([lat, lon]);
    updateMarker(lat, lon);
}
// ----- //

// Module Function //
function updateModuleData(data) {
    const type = data[0];
    switch (type) {
        case 0: // BMP280
            // BMP280 == 0 : ["0" , "temp" , "press", "alt"]
            console.log("temp", data[1], "°C");
            console.log("press", data[2], "hPa");
            console.log("alt", data[3], "m");
            document.getElementById("temp").innerHTML = data[1];
            document.getElementById("press").innerHTML = data[2];
            document.getElementById("bmp-alt").innerHTML = data[3];

            updateModuleChart(type, data[1], data[2], data[3]);
            break
        case 1: // GY
            // GY == 1 : ["1" , "ax" , "ay" , "az" , "gx" , "gy" , "gz"]
            console.log("ax", data[1], "g");
            console.log("ay", data[2], "g");
            console.log("az", data[3], "g");
            console.log("gx", data[4], "°/s");
            console.log("gy", data[5], "°/s");
            console.log("gz", data[6], "°/s");
            document.getElementById("ax").innerHTML = data[1];
            document.getElementById("ay").innerHTML = data[2];
            document.getElementById("az").innerHTML = data[3];
            document.getElementById("gx").innerHTML = data[4];
            document.getElementById("gy").innerHTML = data[5];
            document.getElementById("gz").innerHTML = data[6];

            updateModuleChart(type, data[1], data[2], data[3], data[4], data[5], data[6]);
            break;
        case 2: // GPS
            // GPS == 2 : ["2" , "lat" , "lon" , "alt"]
            console.log("lat", data[1], "°");
            console.log("lon", data[2], "°");
            console.log("alt", data[3], "m");
            let position = count_marker+1;
            document.getElementById("pos").innerHTML = position;
            document.getElementById("lat").innerHTML = data[1];
            document.getElementById("lon").innerHTML = data[2];
            document.getElementById("gps-alt").innerHTML = data[3];
            updateMap(data[1], data[2]);

            updateGPSChart(data[1], data[2], data[3]);
            break;
        default:
            console.error("Unknown Module Type");
    }
}
// ----- //

// Status function //
function updateStatus(data) {
    const status = data[0];
    switch (status) {
        case 1:
            console.log("Launch Status");
            document.getElementById("launch").innerHTML = "🟢";
            document.getElementById("flight").innerHTML = "🟡";
            break;
        case 2:
            console.log("In Flight Status");
            break;
        case 3:
            console.log("Landed Status");
            document.getElementById("flight").innerHTML = "🟢";
            document.getElementById("land").innerHTML = "🟢";
            break;
        case 4:
            console.log("ERROR Status");
            break
        default:
            console.error("Unknown Status");
    }
    switch (status) {
        case 5:
            console.log("Ejected");
            document.getElementById("deploy").innerHTML = "🟢";
            break;
        case 6:
            console.log("Not Ejected");
            break;
        default:
            console.error("Unknown Status");
    }
}
// ----- //

// Module Data Plot function //
const mtx = document.getElementById("module-chart").getContext("2d");
const moduleChart = new Chart(mtx, {
    type: "line",
    data: {
        labels: [],
        datasets: [
            // BMP280 Data
            {
                label: "Temperature (°C)",
                data: [],
                borderColor: 'rgb(255, 99, 132)',
                backgroundColor: 'rgba(255, 99, 132, 0.2)',
                tension: 0.1,
                yAxisID: 'y'
            },
            {
                label: "Pressure (hPa)",
                data: [],
                borderColor: 'rgb(54, 162, 235)',
                backgroundColor: 'rgba(54, 162, 235, 0.2)',
                tension: 0.1,
                yAxisID: 'y1'
            },
            {
                label: "BMP Altitude (m)",
                data: [],
                borderColor: 'rgb(75, 192, 192)',
                backgroundColor: 'rgba(75, 192, 192, 0.2)',
                tension: 0.1,
                yAxisID: 'y2'
            },
            // GY-521 Acceleration Data
            {
                label: "Acceleration X (g)",
                data: [],
                borderColor: 'rgb(255, 159, 64)',
                backgroundColor: 'rgba(255, 159, 64, 0.2)',
                tension: 0.1,
                yAxisID: 'y3'
            },
            {
                label: "Acceleration Y (g)",
                data: [],
                borderColor: 'rgb(153, 102, 255)',
                backgroundColor: 'rgba(153, 102, 255, 0.2)',
                tension: 0.1,
                yAxisID: 'y3'
            },
            {
                label: "Acceleration Z (g)",
                data: [],
                borderColor: 'rgb(255, 159, 243)',
                backgroundColor: 'rgba(255, 159, 243, 0.2)',
                tension: 0.1,
                yAxisID: 'y3'
            },
            // GY-521 Gyro Data
            {
                label: "Gyro X (°/s)",
                data: [],
                borderColor: 'rgb(255, 159, 64)',
                backgroundColor: 'rgba(255, 159, 64, 0.2)',
                tension: 0.1,
                yAxisID: 'y4',
                borderDash: [5, 5]
            },
            {
                label: "Gyro Y (°/s)",
                data: [],
                borderColor: 'rgb(153, 102, 255)',
                backgroundColor: 'rgba(153, 102, 255, 0.2)',
                tension: 0.1,
                yAxisID: 'y4',
                borderDash: [5, 5]
            },
            {
                label: "Gyro Z (°/s)",
                data: [],
                borderColor: 'rgb(255, 159, 243)',
                backgroundColor: 'rgba(255, 159, 243, 0.2)',
                tension: 0.1,
                yAxisID: 'y4',
                borderDash: [5, 5]
            }
        ]
    },
    options: {
        animation: false,
        responsive: true,
        interaction: {
            mode: 'index',
            intersect: false,
        },
        scales: {
            x: {
                type: 'time',
                time: {
                    unit: 'second',
                    displayFormats: {
                        second: 'HH:mm:ss'
                    }
                },
                title: {
                    display: true,
                    text: 'Time'
                }
            },
            y: {
                type: 'linear',
                display: true,
                position: 'left',
                title: {
                    display: true,
                    text: 'Temperature (°C)'
                }
            },
            y1: {
                type: 'linear',
                display: true,
                position: 'right',
                title: {
                    display: true,
                    text: 'Pressure (hPa)'
                },
                grid: {
                    drawOnChartArea: false
                }
            },
            y2: {
                type: 'linear',
                display: true,
                position: 'right',
                title: {
                    display: true,
                    text: 'Altitude (m)'
                },
                grid: {
                    drawOnChartArea: false
                }
            },
            y3: {
                type: 'linear',
                display: true,
                position: 'right',
                title: {
                    display: true,
                    text: 'Acceleration (g)'
                },
                grid: {
                    drawOnChartArea: false
                }
            },
            y4: {
                type: 'linear',
                display: true,
                position: 'right',
                title: {
                    display: true,
                    text: 'Angular Velocity (°/s)'
                },
                grid: {
                    drawOnChartArea: false
                }
            }
        }
    }
});
// ----- //

// Module Data Update Function //
function updateModuleChart(type, temp, press, alt, ax, ay, az, gx, gy, gz) {
    const now = new Date();
    
    // Add new data points
    moduleChart.data.labels.push(now);
    
    // Push data based on sensor type
    switch (type) {
        case 0: // BMP280 data
            dataStream.push({
                time: now,
                temp: parseFloat(temp),
                press: parseFloat(press), 
                alt: parseFloat(alt)
            });
            // Update BMP280 chart data
            moduleChart.data.datasets[0].data.push({x: now, y: parseFloat(temp)}); // Temperature
            moduleChart.data.datasets[1].data.push({x: now, y: parseFloat(press)}); // Pressure
            moduleChart.data.datasets[2].data.push({x: now, y: parseFloat(alt)}); // Altitude
            break;
            
        case 1: // GY-521 data
            dataStream.push({
                time: now,
                ax: parseFloat(ax),
                ay: parseFloat(ay),
                az: parseFloat(az),
                gx: parseFloat(gx),
                gy: parseFloat(gy),
                gz: parseFloat(gz)
            });
            // Update GY-521 chart data
            moduleChart.data.datasets[3].data.push({x: now, y: parseFloat(ax)}); // Accel X
            moduleChart.data.datasets[4].data.push({x: now, y: parseFloat(ay)}); // Accel Y
            moduleChart.data.datasets[5].data.push({x: now, y: parseFloat(az)}); // Accel Z
            moduleChart.data.datasets[6].data.push({x: now, y: parseFloat(gx)}); // Gyro X
            moduleChart.data.datasets[7].data.push({x: now, y: parseFloat(gy)}); // Gyro Y
            moduleChart.data.datasets[8].data.push({x: now, y: parseFloat(gz)}); // Gyro Z
            break;
    }

    // Keep only last 100 points
    if (moduleChart.data.labels.length > 100) {
        moduleChart.data.labels.shift();
        moduleChart.data.datasets.forEach(dataset => {
            dataset.data.shift();
        });
    }

    moduleChart.update('none'); // Update without animation
}
// ----- //

// GPS Plot function //
const gpx = document.getElementById("gps-chart").getContext("2d");
const gpsChart = new Chart(gpx, {
    type: 'scatter',
    data: {
        datasets: [
            {
                label: "GPS Path",
                data: [],
                borderColor: 'rgb(75, 192, 192)',
                backgroundColor: 'rgba(75, 192, 192, 0.2)',
                pointRadius: 5,
                showLine: true,
                lineTension: 0.1
            },
            {
                label: "Current Position",
                data: [],
                borderColor: 'rgb(255, 99, 132)',
                backgroundColor: 'rgba(255, 99, 132, 0.5)',
                pointRadius: 8,
                showLine: false
            }
        ]
    },
    options: {
        responsive: true,
        maintainAspectRatio: false,
        scales: {
            x: {
                type: 'linear',
                position: 'bottom',
                title: {
                    display: true,
                    text: 'Longitude'
                },
                min: 100.0,
                max: 101.0
            },
            y: {
                type: 'linear',
                position: 'left',
                title: {
                    display: true,
                    text: 'Latitude'
                },
                min: 13.0,
                max: 14.0
            }
        },
        plugins: {
            tooltip: {
                callbacks: {
                    label: function(context) {
                        const data = context.raw;
                        return [
                            `Latitude: ${data.y.toFixed(6)}°`,
                            `Longitude: ${data.x.toFixed(6)}°`,
                            `Altitude: ${data.altitude?.toFixed(2) || 'N/A'}m`
                        ];
                    }
                }
            }
        }
    }
});
// ----- //

// GPS Update Function //
function updateGPSChart(lat, lng, alt) {
    const newPoint = {
        x: parseFloat(lng),
        y: parseFloat(lat),
        altitude: parseFloat(alt)
    };

    // Update path dataset
    gpsChart.data.datasets[0].data.push(newPoint);

    // Update current position dataset
    gpsChart.data.datasets[1].data = [newPoint];

    // Keep only last 100 points in the path
    if (gpsChart.data.datasets[0].data.length > 100) {
        gpsChart.data.datasets[0].data.shift();
    }

    // Update chart bounds if needed
    const xScale = gpsChart.scales.x;
    const yScale = gpsChart.scales.y;
    
    if (newPoint.x < xScale.min) xScale.min = newPoint.x - 0.1;
    if (newPoint.x > xScale.max) xScale.max = newPoint.x + 0.1;
    if (newPoint.y < yScale.min) yScale.min = newPoint.y - 0.1;
    if (newPoint.y > yScale.max) yScale.max = newPoint.y + 0.1;

    gpsChart.update('none');
}
// ----- //

// Clock function //
function Clock() {
    setInterval(() => {
      const now = new Date();
      const utcOffset = 7;
      const utc7 = new Date(now.getTime() + utcOffset * 60 * 60 * 1000);

      const pad = n => String(n).padStart(2, '0');
      const months = ["Jan", "Feb", "Mar", "Apr", "May", "Jun",
                      "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"];

      const formatted = `UTC+7 ${pad(utc7.getUTCDate())}-${months[utc7.getUTCMonth()]}-${String(utc7.getUTCFullYear()).slice(2)} ` +
                        `${pad(utc7.getUTCHours())}:${pad(utc7.getUTCMinutes())}:${pad(utc7.getUTCSeconds())}`;

      document.getElementById('time').textContent = formatted;
    }, 1000);
}
// ----- //

// Runtime function //
var run = 1;
function Runtime() {
    setInterval(() => {
        document.getElementById('runtime').textContent = run;
        run++;
    }, 1000)
}
// function Runtime(time) {
//     document.getElementById('runtime').textContent = time;
// }
// ----- //

// Log function //
// Log //
// if command == 0 ; command, module, data ...
// if command == 1 ; command, status
const logData = ["cmd,time,module,data1,data2,data3,data4,data5,data6"];

function Log(dataArr) {
    const cmd = dataArr[0];
    const data = dataArr[1];

    const now = new Date();
    const utcOffset = 7;
    const utc7 = new Date(now.getTime() + utcOffset * 60 * 60 * 1000).toISOString();

    let line = "";

    if (cmd === 0) {
        let moduleType = "";
        switch (data[0]) {
            case 0:
                moduleType = "BMP280";
                break
            case 1:
                moduleType = "GY-521";
                break
            case 2:
                moduleType = "GPS";
                break
        }
        line = `0,${utc7},${moduleType},${data.slice(1).join(",")}`;
    } else if (cmd === 1) {
        let statusName = "";
        switch (data[0]) {
            case 1:
                statusName = "Launch";
                break
            case 2:
                statusName = "In Flight";
                break
            case 3:
                statusName = "Landed";
                break
            case 4:
                statusName = "ERROR";
                break
            case 5:
                statusName = "Ejected";
                break
            case 6:
                statusName = "Not Ejected";
                break
        }
        line = `1,${utc7},status,${statusName}`;
    }

    logData.push(line);
}
// ----- //

// Download funcion //
function Download() {
    const csvContent = logData.join("\n");
    const blob = new Blob([csvContent], { type: 'text/csv;charset=utf-8;' });
    const url = URL.createObjectURL(blob);

    const a = document.createElement('a');
    a.href = url;
    a.download = "log.csv";
    a.style.display = "none";
    document.body.appendChild(a);
    a.click();
    document.body.removeChild(a);
}
// ----- //

// Download Module Log //
function DownloadModuleLog(filter) {
    const filteredData = logData.filter(row => {
        const rowArray = row.split(",");
        const moduleType = rowArray[2];
        return moduleType === filter;
    });

    let csvContent = "cmd,time,module,data1,data2,data3,data4,data5,data6\n";

    filteredData.forEach(row => {
        csvContent += row + "\n";
    });

    const blob = new Blob([csvContent], { type: 'text/csv;charset=utf-8;' });
    const url = URL.createObjectURL(blob);

    const a = document.createElement('a');
    a.href = url;
    a.download = `${filter}_log.csv`;
    a.style.display = "none";
    document.body.appendChild(a);
    a.click();
    document.body.removeChild(a);
}
// ----- //

// WebSockets Protocol //
let socket = null;

function setupWebSocket() {
    socket = new WebSocket('ws://localhost:8080'); // ws://your_esp32_ip.8080
    socket.onopen = function() {
        console.log('WebSocket connection established');
    };
    socket.onmessage = function(event) {
        const msg = JSON.parse(event.data);
        const cmd = msg[0];
        const time = msg[1];

        Runtime(time);
        Log(msg[2]);

        switch (cmd) {
            case 0:
                updateModuleData(data[2]);
                break;
            case 1:
                updateStatus(data[2]);
                break;
            default:
                console.error("Unknown Data Type");
        }
    };
    socket.onerror = function(error) {
        console.error('WebSocket error:', error);
    }

    socket.onclose = function() {
        console.log('WebSocket connection closed');
    };
}

// Main function //
function main() {
    // Create Data Stream
    // console.log("Data Stream Tester");
    // dataStreamTester();
    // console.log(dataStream);

    // Initialize map with default coordinates
    if (!mapInit) {
        const lat = 14.543041376992788; // Default latitude
        const lon = 100.91039848853733; // Default longitude
        initMap(lat, lon);
        document.getElementById("pos").innerHTML = "1";
        document.getElementById("lat").innerHTML = lat;
        document.getElementById("lon").innerHTML = lon;
    }
    console.log("Map Initialized");

    Clock();

    setupWebSocket();

    // Data Stream Tester
    // for (let i = 0; i < dataStream.length; i++) {
    //     const type = dataStream[i][0];
    //     // const Ctime = dataStream[i][1];
    //     const data = dataStream[i][1];
    //     // Runtime(Ctime);
    //     Log(dataStream[i]);
    //     switch (type) {
    //         case 0: // Module Data 
    //             updateModuleData(data);
    //             break;
    //         case 1: // Status
    //             updateStatus(data);
    //             break;
    //         default:
    //             console.error("Unknown Data Type");
    //     }
    //     await new Promise(resolve => setTimeout(resolve, 5000)); // delay for 5 s
    // }
    // ----- //
}
// ----- //

// Data Stream Tester //
// Author: iterrius
// Description: This function is used to test the data stream by generating random data for each type of sensor.
function dataStreamTester() {
    for (let i = 0; i < 100; i++) {
        const type = Math.floor(Math.random() * 4); // 0 to 3
    
        switch (type) {
            case 0:
                // Structure: [0, [0, float, float, int]]
                // BMP280 == 0 : ["0" , "temp" , "press", "alt"]
                dataStream.push([
                    0,
                    [0,
                        +(Math.random() * 100).toFixed(2),
                        +(Math.random() * 1100).toFixed(2),
                        Math.floor(Math.random() * 200)
                    ]
                ]);
                break;
            case 1:
                // Structure: [0, [1, float, float, float, float, float, float]]
                // GY == 1 : ["1" , "ax" , "ay" , "az" , "gx" , "gy" , "gz"]
                dataStream.push([
                    0,
                    [1,
                        +(Math.random() * 10).toFixed(2),
                        +(Math.random() * 10).toFixed(2),
                        +(Math.random() * 10).toFixed(2),
                        +(Math.random() * 1).toFixed(2),
                        +(Math.random() * 1).toFixed(2),
                        +(Math.random() * 1).toFixed(2)
                    ]
                ]);
                break;
            case 2:
                // Structure: [0, [2, float, float, int]]
                // GPS == 2 : ["2" , "lat" , "lon" , "alt"]
                dataStream.push([
                    0,
                    [2,
                        +(Math.random() * 100).toFixed(12),
                        +(Math.random() * 200).toFixed(12),
                        Math.floor(Math.random() * 200)
                    ]
                ]);
                break;
            case 3:
                // Structure: [1, [1, int]]
                dataStream.push([
                    1,
                    [
                        Math.floor(Math.random() * 6) + 1,
                    ]
                ]);
                break;
        }
    }
}
// ----- //
</script>
<script>main();</script>
</html>
)=====";