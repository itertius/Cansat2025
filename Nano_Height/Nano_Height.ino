#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;
const int duration = 180;
const unsigned long interval = 100;
int heightArray[duration];
bool state = false;
int index = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  if (!bmp.begin()) {
    Serial.println("Failed to find BMP280 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("Found BMP280");
}

void loop() {
  static unsigned long previous_time = 0;
  unsigned long current_time = millis();

  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F;
  float altitude = bmp.readAltitude(1013.25);

  if (state) {
    for (int i = 0; i < duration; i++) {
      Serial.print("Second "); Serial.print(i + 1); Serial.print(": ");
      Serial.println(heightArray[i]);
    }
  }

  if (current_time - previous_time >= interval && !state) {
    sensors_event_t a, g, temp;
    heightArray[index] = altitude;
    index++;
  }
  else {
    state = true;
  }
}
