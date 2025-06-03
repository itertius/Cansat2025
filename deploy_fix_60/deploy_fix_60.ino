#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ESP32Servo.h>

Adafruit_MPU6050 mpu;
Servo deployServo;
int servoPin = 2; // PWM pin connected to the servo signal wire

// Constants
const float Lunch_threshold = -9.0;  // G force threshold from all axis
const float Eject_threshold = 8;   // sqrt(x**2 + y**2)
const int emergency_time = 10000;  // milliseconds
const int normal_eject_delay = 2000; // milliseconds
const int window_size = 10;  // Window size for moving average filter
const unsigned long interval = 100;  // Interval duration in milliseconds

// Global variables
bool Lunch_state = false;
bool Normal_eject = false;
bool Emergency_eject = false;
unsigned long start_time = 0;

float buffer[window_size][4]; // Buffer for storing recent sensor readings
int buffer_index = 0;
void Nomalize_servo(){
      deployServo.write(-90);  // tell servo to go to position in variable 'angle'
}
void Eject() {
   deployServo.write(90);  // tell servo to go to position in variable 'angle'
   delay(3000);
   deployServo.write(-90);
} 
void Check_module(){
    // MPU6050
    if (!mpu.begin()) {
      Serial.println("Failed to find MPU6050 chip");
      while (1) {
        delay(10);
      }
    }
    Serial.println("Found MPU6050");
    // END MPU6050
}


void setup() {
    Serial.begin(115200);
    Wire.begin();
    deployServo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
    Nomalize_servo();
    Check_module();
  // Initialize buffer with zeros
  for (int i = 0; i < window_size; i++) {
    buffer[i][1] = 0;
    buffer[i][2] = 0;
    buffer[i][3] = 0;
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
  


    // float ax_g = ax / 16384.0; // Convert to g
    // float ay_g = ay / 16384.0; // Convert to g
    // float az_g = az / 16384.0; // Convert to g
    
    float ax_g = ax;
    float ay_g = ay;
    float az_g = az;
    // Update buffer
    buffer[buffer_index][1] = ax_g;
    buffer[buffer_index][2] = ay_g;
    buffer[buffer_index][3] = az_g;
    buffer_index = (buffer_index + 1) % window_size;

    // Calculate moving average
    float avg_ax = 0, avg_ay = 0, avg_az = 0;
    for (int i = 0; i < window_size; i++) {
      avg_ax += buffer[i][1];
      avg_ay += buffer[i][2];
      avg_az += buffer[i][3];
    }
    avg_ax /= window_size;
    avg_ay /= window_size;
    avg_az /= window_size;

    float a_xandy = sqrt(avg_ax * avg_ax + avg_ay * avg_ay);

    if (avg_az <= Lunch_threshold && !Lunch_state) {
      Lunch_state = true;
      Serial.println("LUNCH!!!!!");
      Serial.println(avg_az);
      start_time = current_time;
    }
    // Lunch Phase
    if (Lunch_state) {
      if (current_time - start_time > emergency_time) {
        Emergency_eject = true;
        Serial.print("Time: ");
        Serial.print(current_time / 1000.0, 2);
        Eject();
        Serial.println("s - Emergency Eject");

        while (1); // Stop further processing
      } else if ((a_xandy >= Eject_threshold || avg_az <-9) && current_time - start_time > normal_eject_delay) {
        Normal_eject = true;
        Serial.print("Time: ");
        Serial.print(current_time / 1000.0, 2);
        Eject();
        Serial.println("s - Normal Eject");
        Serial.print("a_xandy: ");
        Serial.print(a_xandy);
        Serial.print("g, acceleration_z: ");
        Serial.println(avg_az);
        while (1); // Stop further processing
      }
      Serial.print("Time: ");
      Serial.print(current_time / 1000.0, 2);
      Serial.print("s, a x&y: ");
      Serial.print(a_xandy);
      Serial.println("g"); 
    } else {
      Serial.print("Time: ");
      Serial.print(current_time / 1000.0, 2);
      Serial.println("Nothing");
    //     Serial.print(">ax and y:");
    // Serial.println( sqrt(avg_ax * avg_ax + avg_ay * avg_ay));

    // Serial.print(">az:");
    //   Serial.println(az);
    }
  }
}