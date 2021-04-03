#include <Arduino_LSM6DS3.h>
const int motor1A = 17;
const int motor2A = 16;
const int motor3A = 6;
const int motor4A = 12;
String command;

int move_forward() {
  analogWrite(motor1A, 150);
  analogWrite(motor2A, 0);
  analogWrite(motor3A, 150);
  analogWrite(motor4A, 0);
}

void setup() {
  pinMode(motor1A, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor3A, OUTPUT);
  pinMode(motor4A, OUTPUT);

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (true); // halt program
  }
  Serial.println("IMU initialized!");
}

void loop() {
  float aX, aY, aZ;
  float gX, gY, gZ;
  const char * spacer = ", ";

  move_forward();

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
  delay(1000);
}
