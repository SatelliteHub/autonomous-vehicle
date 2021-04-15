#include <Arduino_LSM6DS3.h>
#include <PID_v1.h> // PID Library by Brett Beauregard

// Define Variables we'll be connecting to
double setpoint; // Desired Value
double input; // US Sensor
double output; // Motor

// PID Parameters
double Kp = 20, Ki = 5, Kd = 1;

// Specify the links and initial tuning parameters
PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

// L293D Connection
const int LM1 = 17;
const int LM2 = 16;
const int RM1 = 6;
const int RM2 = 12;

// IR Sensor Connection
const int LEYE = 2;
const int REYE = 11;

// Ultrasonic Connection
const int UST = 15;
const int USE = 10;

int right_turn() { // LEFT WHEEL FORWARD
  analogWrite(LM1, 255 - output);
  analogWrite(LM2, 0);
  analogWrite(RM1, 0);
  analogWrite(RM2, 0);
}

int left_turn() { // RIGHT WHEEL FORWARD
  analogWrite(LM1, 0);
  analogWrite(LM2, 0);
  analogWrite(RM1, 255 - output);
  analogWrite(RM2, 0);
}

int move_forward() { // ALL WHEEL FORWARD
  analogWrite(LM1, 255 - output);
  analogWrite(LM2, 0);
  analogWrite(RM1, 255 - output);
  analogWrite(RM2, 0);
}

int stop_all() { // STOP BUGGY
  analogWrite(LM1, 0);
  analogWrite(LM2, 0);
  analogWrite(RM1, 0);
  analogWrite(RM2, 0);
}

int distance; // Distance between the Obstacle and Vehicle
int last_distance; // Last Recorded Distance

void setup() {
  setpoint = 15; // Distance to activate PID
  myPID.SetMode(AUTOMATIC); // Turn PID On
  myPID.SetTunings(Kp, Ki, Kd); /// Adjust PID Values
  
  pinMode(LEYE, INPUT);
  pinMode(REYE, INPUT);

  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  
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

  // IR Sensor
  int left = digitalRead(LEYE);
  int right = digitalRead(REYE);
  
  long duration = 0;
  int distance = 0;

  // Determine IMU Values
  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
    IMU.readAcceleration(aX, aY, aZ);
    IMU.readGyroscope(gX, gY, gZ);
    Serial.print(aX); Serial.print(spacer);
    Serial.print(aY); Serial.print(spacer);
    Serial.print(aZ); Serial.print(spacer);
    Serial.print(gX); Serial.print(spacer);
    Serial.print(gY); Serial.print(spacer);
    Serial.println(gZ);
    delay(10);
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
    input = distance; // Input Distance for PID
    
    Serial.print(distance);
    Serial.println(" cm");
  }

  myPID.Compute(); // Compute PID

  if (left && right) {
    stop_all();
  }

  if (!left && !right) {
    move_forward();
  }

  if (!left && right) {
    right_turn();
  }

  if (left && !right) {
    left_turn();
  }

}
