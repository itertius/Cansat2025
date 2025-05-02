import csv
from datetime import datetime, timedelta
import random

# Configuration
start_time = datetime.strptime("2024-03-20T10:00:00.000Z", "%Y-%m-%dT%H:%M:%S.000Z")
num_seconds = 50  # Number of seconds of data to generate
output_file = "./log1.csv"

# Status messages (indexed by second)
status_messages = ["Launch", "In Flight", "Landed", "ERROR", "Ejected", "Not Ejected"]

# Write to CSV
with open(output_file, mode="w", newline="") as file:
    writer = csv.writer(file)
    writer.writerow(["cmd", "time", "module", "data1", "data2", "data3", "data4", "data5", "data6"])

    for i in range(num_seconds):
        timestamp = start_time + timedelta(seconds=i)
        iso_time = timestamp.strftime("%Y-%m-%dT%H:%M:%S.000Z")

        temp = round(25.3 - 0.1 * i, 1)
        pressure = round(1013.25 - 0.05 * i, 2)
        altitude = 100 + 5 * i
        writer.writerow([0, iso_time, "BMP280", temp, pressure, altitude])

        # GY-521 data
        accel_x = round(0.01 + 0.01 * i, 2)
        accel_y = round(0.02 + 0.01 * i, 2)
        accel_z = round(0.98 - 0.01 * i, 2)
        gyro_x = round(0.1 + 0.1 * i, 1)
        gyro_y = round(0.2 + 0.1 * i, 1)
        gyro_z = round(0.3 + 0.1 * i, 1)
        writer.writerow([0, iso_time, "GY-521", accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z])

        # GPS data
        lat = round(13.7563 + 0.0001 * i, 4)
        lon = round(100.5018 + 0.0001 * i, 4)
        writer.writerow([0, iso_time, "GPS", lat, lon, altitude])

        # Status message if available
        if i < len(status_messages):
            writer.writerow([1, iso_time, "status", status_messages[i]])

print(f"Generated {output_file}")

