//**************************************************************//
//  For Convenience install "PID" Library by Brett Beauregard   //
//**************************************************************//

#include <PID_v1.h> // PID Library by Brett Beauregard

//Define Variables we'll be connecting to
double setpoint; // Desired Value (255)
double input; // US Sensor
double output; // Motor

//PID Parameters
double Kp = 50, Ki = 5, Kd = 1;

//Specify the links and initial tuning parameters
PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

// L293D Connection
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


int right_turn() {
  analogWrite(LM1, 255 - output);
  analogWrite(LM2, 0);
  analogWrite(RM1, 0);
  analogWrite(RM2, 0);
}

int left_turn() {
  analogWrite(LM1, 0);
  analogWrite(LM2, 0);
  analogWrite(RM1, 255 - output);
  analogWrite(RM2, 0);
}

int move_forward() {
  analogWrite(LM1, 255 - output);
  analogWrite(LM2, 0);
  analogWrite(RM1, 255 - output);
  analogWrite(RM2, 0);
}

int stop_all() {
  analogWrite(LM1, 0);
  analogWrite(LM2, 0);
  analogWrite(RM1, 0);
  analogWrite(RM2, 0);
}

int last_distance;

void setup() {
  Serial.begin(9600);

  setpoint = 12; // Distance to activate PID
  myPID.SetMode(AUTOMATIC); // Turn PID On

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

  //************* ULTRASONIC *************//
  int left = digitalRead(LEYE);
  int right = digitalRead(REYE);
  
  digitalWrite(UST, LOW);
  delayMicroseconds(2);
  digitalWrite(UST, HIGH);
  delayMicroseconds(10);
  digitalWrite(UST, LOW);

  float duration = pulseIn(USE, HIGH);
  // Count when USE is HIGH and stop when USE is low

  int distance = duration / 58;

  input = distance;
  myPID.Compute();



  //************* LINE FOLLOWING *************//
  if (left && right) {
    
    // Stop the Vehicle
    
    if (last_distance != distance) {
      
      // Print stuff here…
      // Assign "distance" to "last_distance"
      // Set 100 ms of delay (for Processing)
      
    }
  }
  if (!left && !right) {
    
    // Move the vehicle forward
    
    if (last_distance != distance) {
      
      // Print stuff here…
      // Assign "distance" to "last_distance"
      // Set 100 ms of delay (for Processing)
      
    }
  }

  if (!left && right) {
    
    // Turn the vehicle right
    
    if (last_distance != distance) {
      
      // Print stuff here…
      // Assign "distance" to "last_distance"
      // Set 100 ms of delay (for Processing)
      
    }
  }
  if (left && !right) {
    
    // Turn the vehicle left
    
    if (last_distance != distance) {
      
      // Print stuff here…
      // Assign "distance" to "last_distance"
      // Set 100 ms of delay (for Processing)
      
    }
  }
}
