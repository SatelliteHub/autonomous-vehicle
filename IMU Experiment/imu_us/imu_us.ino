#include <Arduino_LSM6DS3.h>

// Ultrasonic Connection
const int UST = 15;
const int USE = 10;

void setup() {
  pinMode(UST, OUTPUT);
  pinMode(USE, INPUT);

  Serial.begin(9600);
  while (!Serial) {
    Serial.println("LSM6DS3 IMU initialization…");
  }
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (true); // halt program
  }
  Serial.println("IMU initialized");
}


void loop() {
  float aX, aY, aZ;
  float gX, gY, gZ;
  const char * spacer = ", ";
  
  long duration = 0;
  int distance = 0;
  
  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
    IMU.readAcceleration(aX, aY, aZ);
    IMU.readGyroscope(gX, gY, gZ);
    Serial.print(aX); Serial.print(spacer);
    Serial.print(aY); Serial.print(spacer);
    Serial.print(aZ); Serial.print(spacer);
    Serial.print(gX); Serial.print(spacer);
    Serial.print(gY); Serial.print(spacer);
    Serial.println(gZ);
    delay(1000);
  }

  // Ultrasonic Sensor
  while (distance == 0) {
    digitalWrite(UST, LOW);
    delayMicroseconds(2);
    digitalWrite(UST, HIGH);
    delayMicroseconds(10);
    digitalWrite(UST, LOW);
    
    duration = pulseIn(USE, HIGH);
    distance = duration / 58;
    
    Serial.println(distance);
    Serial.println(" cm.");
  }
}
