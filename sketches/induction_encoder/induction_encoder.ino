const int ENCODER_PIN = 2; // pin D2
const int ENCODER_INT = 1; // pin D2
const int ANALOG_PIN = 0;
const int INTERVAL = 1000; // milliseconds
const int BAUD = 9600;
const int BLIPS_PER_REV = 32;

int a = millis();
int b = millis();
volatile int RPM = 0;
volatile int BLIPS = 0;

void setup() {
  pinMode(ANALOG_PIN, INPUT);
  digitalWrite(ENCODER_PIN, LOW);
  Serial.begin(BAUD);
  attachInterrupt(ENCODER_INT, counter, CHANGE);
}

void loop() {
  int val = analogRead(ANALOG_PIN);
  //digitalRead(ENCODER_PIN);
  Serial.println(val);
  BLIPS = 0;
  a = millis();
  delay(INTERVAL);
  b = millis();
}

void counter() {
  BLIPS++;
}
