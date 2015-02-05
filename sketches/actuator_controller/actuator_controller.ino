/*
  Electronic Throttle Controller
  BREE504 Instrumentation and Control
  Author: Trevor Stanhope
  Version: 0.5
*/

const int INPUT_READ_PIN = 0;
const int INPUT_WRITE_PIN = 5;
const int OUTPUT_READ_PIN = 1;
const int OUTPUT_WRITE_PIN = 6;

const int BAUD = 9600;
const int INTERVAL = 50;
const int BUFFER_SIZE = 16;

char buffer[BUFFER_SIZE];
int input_read = 0;
int output_read = 0;
int input_write = 0;
int output_write = 0;

void setup() {
  pinMode(INPUT_READ_PIN, INPUT);
  pinMode(OUTPUT_READ_PIN, INPUT);
  pinMode(INPUT_WRITE_PIN, OUTPUT);
  pinMode(OUTPUT_WRITE_PIN, OUTPUT);
  Serial.begin(BAUD);
}

void loop() {
  // Input
  input_read = analogRead(INPUT_READ_PIN);
  input_write = map(input_read, 0, 1023, 0, 255);
  analogWrite(INPUT_WRITE_PIN, input_write);
  
  // Output
  output_read = analogRead(OUTPUT_READ_PIN);
  output_write = map(output_read, 0, 1023, 0, 255);
  analogWrite(OUTPUT_WRITE_PIN, output_write);
  delay(INTERVAL);
}
