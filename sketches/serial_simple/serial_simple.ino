#include <DualVNH5019MotorShield.h>
const int POT_PIN = 0; // Desired reference signal (convert to RPM)
const int ENCODER_PIN = 2; // Output RPM
const int ENCODER_INT = 0;
const int BAUD = 9600;
const int INTERVAL = 1000; // milliseconds
const int RPM_MIN = 1500;
const int RPM_MAX = 3600;
const int CHARS = 32;
const float KP = 1.0;
const float KI = 0.0;
const float KD = 0.0;

int VAL = 0;
int REF = 0;
int ACTUAL = 0;
int STEPS_PER_REV = 32;
int P = 0;
int I = 0;
int D = 0;
char BUFFER[CHARS];
int POWER = 0;
volatile int COUNTER = 0;
DualVNH5019MotorShield motors; // takes -400 to 400

void setup() {
  Serial.begin(BAUD);
  attachInterrupt(ENCODER_INT, increment_counter, RISING); // when there's a voltage change on pin 2, add one to COUNTER
  motors.init();
}

void loop() {
  VAL = analogRead(POT_PIN);
  REF = map(VAL, 0, 1024, RPM_MIN, RPM_MAX); // convert (0 - 1024) into (1500 - 3600)
  ACTUAL = COUNTER / (STEPS_PER_REV * INTERVAL * 60000); // convert counter value to RPM
  sprintf(BUFFER, "{'rpm':%d, 'ref':%d}", ACTUAL, REF);
  D = P - REF - ACTUAL;
  P = REF - ACTUAL;
  I = 0;
  /*
  CODE GOES HERE FOR OUTPUTTING TO ACTUATOR
  */
  POWER = KP * P + KI * I + KD * D;
  motors.setM1Speed(POWER);
  sprintf(BUFFER, "{'rpm':%d, 'ref':%d}", ACTUAL, REF);
  Serial.println(BUFFER);
  delay(INTERVAL);
  COUNTER = 0;
}

void increment_counter() {
  COUNTER++;
}

