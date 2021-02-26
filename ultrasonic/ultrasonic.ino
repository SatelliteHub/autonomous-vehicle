const int UST = 19; // Ultrasonic TRIGGER
const int USE = 10; // Ultrasonic ECHO

void setup() {
  Serial.begin(9600);

  pinMode(UST, OUTPUT);
  pinMode(USE, INPUT);
}

void loop() {

  digitalWrite(UST, LOW);
  delayMicroseconds(2);
  digitalWrite(UST, HIGH);
  delayMicroseconds(10);
  digitalWrite(UST, LOW);

  long duration = pulseIn(USE, HIGH);
  // Count when USE is HIGH and stop when USE is low

  int distance = duration / 58;

  Serial.println(distance);

}
