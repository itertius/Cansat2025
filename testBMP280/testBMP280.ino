#include <Wire.h>
#include <Adafruit_BMP280.h>

// สร้างอ็อบเจกต์ BMP280 (โหมด I2C)
Adafruit_BMP280 bmp;

void initBMP(float seaLevelhPa) {
  if (!bmp.begin()) {
    Serial.println("BMP280 Not Found!");
    while (1); // หยุดการทำงานหากไม่เจอเซ็นเซอร์
  }

  Serial.println("BMP280 Found!");
  Serial.println("Initial Reading:");
  
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" °C");

  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure() / 100.0);
  Serial.println(" hPa");

  Serial.print("Altitude = ");
  Serial.print(bmp.readAltitude(seaLevelhPa));
  Serial.println(" m");

  Serial.println("-------------------------");
}

void setup() {
  Serial.begin(9600);
  initBMP(1013.25); // ความดันระดับน้ำทะเลโดยประมาณ (hPa)
}

void loop() {
  Serial.print("Temp: ");
  Serial.print(bmp.readTemperature());
  Serial.println(" °C");

  Serial.print("Press: ");
  Serial.print(bmp.readPressure() / 100.0);
  Serial.println(" hPa");

  Serial.print("Alt: ");
  Serial.print(bmp.readAltitude(1013.25));
  Serial.println(" m");

  Serial.println("-------------------------");
  delay(1000);
}
