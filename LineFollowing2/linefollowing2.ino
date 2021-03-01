// L293D Connection
const int LM1 = 17; // LEFT MOTOR 1 = 1A
const int LM2 = 16; // LEFT MOTOR 2 = 2A
const int RM1 = 6;  // RIGHT MOTOR 1 = 3A
const int RM2 = 12; // RIGHT Motor 2 = 4A

//Ultrasonic sensor connections 
const int UST = 19; //Trigger pin 
const int USE = 10; //Echo pin 

// IR Sensor Connection
const int LEYE = 2; // LEFT IR SENSOR
const int REYE = 11; // RIGHT IR SENSOR


int right_turn() { // TURN RIGHT
  analogWrite(LM1, 250);
  analogWrite(LM2, 0);
  analogWrite(RM1, 0);
  analogWrite(RM2, 150);
}

int left_turn() { // TURN LEFT
  analogWrite(LM1, 0);
  analogWrite(LM2, 150);
  analogWrite(RM1, 250);
  analogWrite(RM2, 0);
}

int move_forward() { // MOVE STRAIGHT
  analogWrite(LM1, 250);
  analogWrite(LM2, 0);
  analogWrite(RM1, 250);
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
  int left = digitalRead(LEYE);
  int right = digitalRead(REYE);

  digitalWrite(UST, LOW);
  delayMicroseconds(2);
  digitalWrite(UST, HIGH);
  delayMicroseconds(10);
  digitalWrite(UST, LOW);

  long duration = pulseIn(USE, HIGH);
  // Count when USE is HIGH and stop when USE is low

  int distance = duration / 58;

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

  if (distance <= 10) { 
    stop_all(); 
    Serial.println("Stopping for obstacle at "); 
    Serial.println(distance); 
    Serial.println("cm distance");  
  }

}
