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