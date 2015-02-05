const int ACTUATOR_PWM_PIN = 5; // Digital Pin #5 for PWM output
const int ACTUATOR_POSITION_PIN = 0; // Analog Pin #0 for analog input
const int BAUD = 9600; // Bits per second
const int MAX_POSITION = 255; // extend all the way
const int MIN_POSITION = 0; // retract fully;

int actuator_position;

void setup() {
  pinMode(ACTUATOR_PWM_PIN, OUTPUT);
  pinMode(ACTUATOR_POSITION_PIN, INPUT);
  Serial.begin(BAUD);
}

void loop() {
  
  // Extend fully
  analogWrite(ACTUATOR_PWM_PIN, MAX_POSITION);
  delay(1000); // wait 1000 ms
  actuator_position = analogRead(ACTUATOR_POSITION_PIN);
  Serial.println(actuator_position);
  
  // Retract fully
  analogWrite(ACTUATOR_PWM_PIN, MIN_POSITION);
  delay(1000);
  actuator_position = analogRead(ACTUATOR_POSITION_PIN);
  Serial.println(actuator_position);
   
  // Sweep Open
  for(int i = 0; i < 255; i++) {
    analogWrite(ACTUATOR_PWM_PIN, i);
    delay(50); 
    Serial.println(actuator_position);
  }
}
