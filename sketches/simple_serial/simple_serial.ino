int POT_PIN = 0;
int BAUD = 9600;
int val = 0;

void loop() {
  Serial.begin(BAUD);
}

void setup() {
  val = analogRead(POT_PIN);
  Serial.println(val);
  delay(100);
}
