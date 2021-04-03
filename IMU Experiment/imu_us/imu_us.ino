#include <Arduino_LSM6DS3.h>
const int LM1 = 17;
const int LM2 = 16;
const int RM1 = 6;
const int RM2 = 12;

// Sensor Connection
const int LEYE = 2;
const int REYE = 11;

// Ultrasonic Connection
const int UST = 19;
const int USE = 10;

int right_turn() { // LEFT WHEEL FORWARD
  analogWrite(LM1, 255);
  analogWrite(LM2, 0);
  analogWrite(RM1, 0);
  analogWrite(RM2, 0);
}

int left_turn() { // RIGHT WHEEL FORWARD
  analogWrite(LM1, 0);
  analogWrite(LM2, 0);
  analogWrite(RM1, 255);
  analogWrite(RM2, 0);
}

int move_forward() { // ALL WHEEL FORWARD
  analogWrite(LM1, 255);
  analogWrite(LM2, 0);
  analogWrite(RM1, 255);
  analogWrite(RM2, 0);
}

int stop_all() { // STOP BUGGY
  analogWrite(LM1, 0);
  analogWrite(LM2, 0);
  analogWrite(RM1, 0);
  analogWrite(RM2, 0);
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (true); // halt program
  }
  Serial.println("IMU initialized!");

  pinMode(LEYE, INPUT);
  pinMode(REYE, INPUT);

  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

  pinMode(UST, OUTPUT);
  pinMode(USE, INPUT);
}

void loop() {
  float aX, aY, aZ;
  float gX, gY, gZ;
  const char * spacer = ", ";
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
    IMU.readAcceleration(aX, aY, aZ);
    IMU.readGyroscope(gX, gY, gZ);
    Serial.print(aX); Serial.print(spacer);
    Serial.print(aY); Serial.print(spacer);
    Serial.print(aZ); Serial.print(spacer);
    Serial.print(gX); Serial.print(spacer);
    Serial.print(gY); Serial.print(spacer);
    Serial.println(gZ);
  }
  // IR Sensor
  int left = digitalRead(LEYE);
  int right = digitalRead(REYE);

  // Ultrasonic Sensor
  digitalWrite(UST, LOW);
  delayMicroseconds(2);
  digitalWrite(UST, HIGH);
  delayMicroseconds(10);
  digitalWrite(UST, LOW);


  long duration = pulseIn(USE, HIGH);
  int distance = duration / 58;

  Serial.print(distance);
  Serial.println(" cm.");
  delay(1000);
}
