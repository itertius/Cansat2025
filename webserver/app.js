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
    defaultMarker.bindPopup(`ตำแหน่งที่ ${count_marker} | เวลา : <br>Latitude: ${lat}<br>Longitude: ${lon}`).openPopup();
}

function updateMarker(lat, lon) {
    if (!mapInit) return;
    count_marker++;
    const mark = L.marker([lat, lon]).addTo(map);
    mark.bindPopup(`ตำแหน่งที่ ${count_marker} | เวลา : <br>Latitude: ${lat}<br>Longitude: ${lon}`).openPopup();
}

function updateMap(lat, lon) {
    if (!mapInit) return;
    map.panTo([lat, lon]);
    updateMarker(lat, lon);
}
// ----- //


function updateModuleData(data) {
    const type = data[0];
    switch (type) {
        case 0: // BMP280
            // BMP280 == 0 : ["0" , "temp" , "press", "alt"]
            console.log("temp", data[1], "°C");
            console.log("press", data[2], "hPa");
            console.log("alt", data[3], "m");
            break
        case 1: // GY
            // GY == 1 : ["1" , "ax" , "ay" , "az" , "gx" , "gy" , "gz"]
            console.log("ax", data[1], "g");
            console.log("ay", data[2], "g");
            console.log("az", data[3], "g");
            console.log("gx", data[4], "°/s");
            console.log("gy", data[5], "°/s");
            console.log("gz", data[6], "°/s");
            break;
        case 2: // GPS
            // GPS == 2 : ["2" , "lat" , "lon" , "alt"]
            console.log("lat", data[1], "°");
            console.log("lon", data[2], "°");
            console.log("alt", data[3], "m");
            updateMap(data[1], data[2]);
            break;
        default:
            console.error("Unknown Module Type");
    }
}

function updateStatus(data) {
    const status = data[0];
    switch (status) {
        case 1:
            console.log("Launch Status");
            break;
        case 2:
            console.log("In Flight Status");
            break;
        case 3:
            console.log("Landed Status");
            break;
        case 4:
            console.log("Error Status");
            break;
        default:
            console.error("Unknown Status");
    }
    switch (status) {
        case 5:
            console.log("Ejected");
            break;
        case 6:
            console.log("Not Ejected");
            break;
        default:
            console.error("Unknown Status");
    }
}

async function main() {
    // Create Data Stream
    console.log("Data Stream Tester");
    dataStreamTester();
    console.log(dataStream);

    // Initialize map with default coordinates
    if (!mapInit) {
        const lat = 14.543041376992788; // Default latitude
        const lon = 100.91039848853733; // Default longitude
        initMap(lat, lon);
    }
    console.log("Map Initialized");

    // Data Stream Tester
    for (let i = 0; i < dataStream.length; i++) {
        const type = dataStream[i][0];
        const data = dataStream[i][1];
        switch (type) {
            case 0: // Module Data 
                updateModuleData(data);
                break;
            case 1: // Status
                updateStatus(data);
                break;
            default:
                console.error("Unknown Data Type");
        }
        await new Promise(resolve => setTimeout(resolve, 5000)); // delay for 5 s
    }
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