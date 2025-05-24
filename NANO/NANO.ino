#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Servo.h>

Adafruit_MPU6050 mpu;
Servo deployServo;
int servoPin = 9; // PWM pin connected to the servo signal wire

// Constants
const float Launch_threshold = -9.0;  // G-force threshold from Z-axis
const float Eject_threshold = 6.93;   // sqrt(x^2 + y^2) | 8.0 = 54.6 degrees || 7.83 = 53 degrees || 6.93 = 45 degree || 9.8 = 90 degree || 8.84 = 60 degree || 9.21 = 70 degree
const float freefall_threshold = 2;   // sqrt(ax² + ay² + az²) | < 2 = freefall
const int emergency_time = 10000;     // milliseconds
const int normal_eject_delay = 2000;  // milliseconds
const int window_size = 10;           // Window size for moving average filter
const unsigned long interval = 100;   // Interval duration in milliseconds

// Buffer index constants
const int AX = 0;
const int AY = 1;
const int AZ = 2;

// Global variables
bool Launch_state = false;
bool Normal_eject = false;
bool Emergency_eject = false;
unsigned long start_time = 0;

float buffer[window_size][3]; // Buffer for storing recent X, Y, Z accelerations
int buffer_index = 0;
float buffer_a[window_size][3];
int buffer_index_a = 0;

void Normalize_servo() {
  deployServo.write(90);  // Set servo to 0 degrees
}

void Eject() {
  deployServo.write(0);  // Move servo to 180 degrees
  delay(3000);
  deployServo.write(90);    // Return servo to 0 degrees
}

void Check_module() {
  // MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
  }
  Serial.println("Found MPU6050");
}

void E_Eject() {
  Serial.println("** SAFETY-EJECTING **");
  deployServo.write(0);
  delay(500);
  deployServo.write(90);
  delay(500);
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  deployServo.attach(servoPin);  // Attach the servo to the defined pin
  Normalize_servo();
  Check_module();

  // Initialize buffer with zeros
  for (int i = 0; i < window_size; i++) {
    buffer[i][AX] = 0;
    buffer[i][AY] = 0;
    buffer[i][AZ] = 0;
  }

  for (int i=0; i < window_size; i++) {
    buffer_a[i][AX] = 0;
    buffer_a[i][AY] = 0;
    buffer_a[i][AZ] = 0;
  }
}

void loop() {
  static unsigned long previous_time = 0;
  unsigned long current_time = millis();
  
  if (current_time - previous_time >= interval) {
    previous_time = current_time;
    
    // Read sensor data
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    float ax = a.acceleration.x;
    float ay = a.acceleration.y;
    float az = a.acceleration.z;

    // Update buffer
    buffer[buffer_index][AX] = ax;
    buffer[buffer_index][AY] = ay;
    buffer[buffer_index][AZ] = az;
    buffer_index = (buffer_index + 1) % window_size;

    buffer_a[buffer_index_a][AX] = ax;
    buffer_a[buffer_index_a][AY] = ay;
    buffer_a[buffer_index_a][AZ] = az;
    buffer_index_a = (buffer_index_a + 1) % window_size;

    // Calculate moving average
    float avg_ax = 0, avg_ay = 0, avg_az = 0;
    for (int i = 0; i < window_size; i++) {
      avg_ax += buffer[i][AX];
      avg_ay += buffer[i][AY];
      avg_az += buffer[i][AZ];
    }
    avg_ax /= window_size;
    avg_ay /= window_size;
    avg_az /= window_size;

    float avg_total_ax = 0, avg_total_ay = 0, avg_total_az = 0;
    for (int i=0; i < window_size; i++) {
      avg_total_ax +=buffer_a[i][AX];
      avg_total_ay +=buffer_a[i][AY];
      avg_total_az +=buffer_a[i][AZ];
    }
    avg_total_ax /= window_size;
    avg_total_ay /= window_size;
    avg_total_az /= window_size;

    float a_xandy = sqrt(avg_ax * avg_ax + avg_ay * avg_ay);
    float total_a = sqrt(avg_total_ax * avg_total_ax + avg_total_ay * avg_total_ay + avg_total_az * avg_total_az);
    
    if (avg_az <= Launch_threshold && !Launch_state) {
      Launch_state = true;
      Serial.println("LAUNCH!!!!!");
      Serial.print("avg_az: ");
      Serial.println(avg_az);
      start_time = current_time;
    }

    // Launch Phase
    if (Launch_state) {   
      Serial.print("Time: ");
      Serial.print(current_time / 1000.0, 2);
      Serial.print("s, a_xandy: ");
      Serial.print(a_xandy);
      Serial.print("m/s, avg_az : ");
      Serial.print(avg_az);
      Serial.print("g, total_a: ");
      Serial.print(total_a);
      Serial.println("m/s");

      if (Normal_eject || Emergency_eject) {
        // E_Eject();
      }
      else {
      if (current_time - start_time > emergency_time) {
        Emergency_eject = true;
        Eject();
        Serial.print("Time: ");
        Serial.print(current_time / 1000.0, 2);
        Serial.println("s - Emergency Eject");
        Serial.print("Time: ");
        Serial.print(current_time / 1000.0, 2);
        Serial.print("s, a_xandy: ");
        Serial.print(a_xandy);
        Serial.print("m/s, avg_az : ");
        Serial.print(avg_az);
        Serial.print("g, total_a: ");
        Serial.print(total_a);
        Serial.println("m/s");
        // while (1); // Stop further processing
      }
      else if ((a_xandy >= Eject_threshold || total_a < freefall_threshold) && current_time - start_time > normal_eject_delay) {
        Normal_eject = true;
        Eject();
        
        Serial.print("Time: ");
        Serial.print(current_time / 1000.0, 2);
        Serial.print("s - Normal Eject");
        if (a_xandy >= Eject_threshold) {
          Serial.println("| >= 45 degree");
        }
        else if (avg_az < -9) {
          Serial.println("| < G-force");
        }
        else if (total_a < freefall_threshold) {
          Serial.println("| freefall");
        }
        Serial.print("Time: ");
        Serial.print(current_time / 1000.0, 2);
        Serial.print("s, a_xandy: ");
        Serial.print(a_xandy);
        Serial.print("m/s, avg_az : ");
        Serial.print(avg_az);
        Serial.print("g, total_a: ");
        Serial.print(total_a);
        Serial.println("m/s");
        // while (1); // Stop further processing
      }
      }
    } else {
      Serial.print("Nano - ");
      Serial.print("Time: ");
      Serial.print(current_time / 1000.0, 2);
      Serial.print("s - Waiting for launch...");
      Serial.print(" | Time: ");
      Serial.print(current_time / 1000.0, 2);
      Serial.print("s, a_xandy: ");
      Serial.print(a_xandy);
      Serial.print("g, avg_az: ");
      Serial.println(avg_az);
    }
  }
}
