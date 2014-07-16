/* --- Libraries --- */
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>

/* --- Assign a unique ID to the sensors --- */
Adafruit_10DOF dof = Adafruit_10DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(18001);
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);

/* --- Constants --- */
const int baud = 9600;
const int pi = 3.14159;
float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;

/* --- Setup --- */
void setup(void) {
  Serial.begin(baud);
  Serial.println(F("Adafruit 10DOF Tester")); Serial.println("");
  if(!accel.begin()) {
    Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
    while(1);
  }
  if (!mag.begin()) {
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
}

/* --- Loop ---  */
void loop(void) {
  
  // Update IMU Events
  sensors_event_t accel_event;
  sensors_event_t mag_event;
  sensors_event_t bmp_event;
  sensors_vec_t orientation;
  
  // Acceleration
  accel.getEvent(&accel_event);
  if (dof.accelGetOrientation(&accel_event, &orientation)) {
    Serial.println("");
  }
  
  // Magnetics
  mag.getEvent(&mag_event);
  if (dof.magGetOrientation(SENSOR_AXIS_Z, &mag_event, &orientation)) {
    Serial.println(orientation.heading);
  }
  
}
