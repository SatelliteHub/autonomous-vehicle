//**************************************************************//
//  For Convenience install "PID" Library by Brett Beauregard   //
//**************************************************************//

#include <PID_v1.h> // PID Library by Brett Beauregard

// Define Variables we'll be connecting to
double setpoint; // Desired Value
double input; // US Sensor
double output; // Motor

// Insert Here PID Parameters (More info in the Lectures/Need testing)
double Kp = XXXXX, Ki = XXXXX, Kd = XXXXX;

// Specify the links and initial tuning parameters
PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);


// L293D Connection
const int LM1 = 17; // Left Motor 1
const int LM2 = 16; // Left Motor 2
const int RM1 = 6;  // Right Motor 1
const int RM2 = 12; // Right Motor 2

// Sensor Connection
const int LEYE = 2;
const int REYE = 11;

// Ultrasonic Connection
const int UST = 19;
const int USE = 10;


void setup() {
  Serial.begin(9600);

  setpoint = XXXXXXXXXXXXX; // Insert here Distance to activate PID
  myPID.SetMode(AUTOMATIC); // Turn PID On
  

  pinMode(UST, OUTPUT);
  pinMode(USE, INPUT);
}

void loop() {
  int left = digitalRead(LEYE);
  int right = digitalRead(REYE);

  // Paste Here Only Ultrasonic Code from Bronze Demo

  input = distance;
  myPID.Compute(); // Compute PID

  // Print the corresponding Output HERE
  
  // Analog Write here each motors using the Output HERE
}
