/*
  PID Throttle Control
*/

/* --- Libraries --- */
#include <DualVNH5019MotorShield.h>
#include <PID_v1.h>

/* --- Constants --- */
const int NUM_FANS = 32;
const int INTERVAL = 100;
const int THROTTLE_INPUT_PIN = 0; // potentiometer
const int ENCODER_PIN = 2; // pin 2 is an interrupt
const int ENCODER_INT = 0;
const int POT_MIN = 0;
const int POT_MAX = 1023;
const int RPM_MAX = 3600;
const int RPM_MIN = 1500;
const double P = 1;
const double I = 0;
const double D = 5;
const int BLIPS_PER_REV = 32;
const int BAUD = 38400;
const int CHARS_MAX = 32;

/* --- Variables --- */
double Setpoint, Input, Output;
volatile int Counter = 0;
char Buffer[CHARS_MAX];

/* --- Objects --- */
DualVNH5019MotorShield Motors;
PID Throttle(&Input, &Output, &Setpoint, P, I, D, DIRECT); //Specify the links and initial tuning parameters

void setup() {
  Serial.begin(BAUD);
  Input = 0; // initialize the variables we're linked to
  Setpoint = 0; // initialize the variables we're linked to
  Throttle.SetMode(AUTOMATIC);
  Motors.init();
  attachInterrupt(ENCODER_INT, increment_counter, RISING);
}

void loop() {
  Setpoint = map(analogRead(THROTTLE_INPUT_PIN), POT_MIN, POT_MAX, RPM_MIN, RPM_MAX);
  Input = Counter / (BLIPS_PER_REV * INTERVAL * 10 * 60);
  Throttle.Compute();
  Motors.setM1Speed(Output); // -400 to 400
  sprintf(Buffer, "{'input':%d, 'setpoint':%d', 'output':%d}", Input, Output, Setpoint);
  Serial.println(Buffer);
  Counter = 0;
  delay(INTERVAL);
}

void increment_counter() {
  Counter++;
}
