void setup() {
  pinMode(5, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println('t');
  analogWrite(5, 255);
  delay(1000);
  analogWrite(5, 0);
  delay(1000);
}


