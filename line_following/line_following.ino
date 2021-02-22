// L293D Connection
const int motor1A = 17;
const int motor2A = 16;
const int motor3A = 6;
const int motor4A = 12;

// Sensor Connection
const int LEYE = 2;
const int REYE = 11;


int LWF() { // LEFT WHEEL FORWARD
  analogWrite(motor1A, 250);
  analogWrite(motor2A, 0);
  analogWrite(motor3A, 0);
  analogWrite(motor4A, 0);
}

int RWF() { // RIGHT WHEEL FORWARD
  analogWrite(motor1A, 0);
  analogWrite(motor2A, 0);
  analogWrite(motor3A, 250);
  analogWrite(motor4A, 0);
}

int AWF() { // ALL WHEEL FORWARD
  analogWrite(motor1A, 250);
  analogWrite(motor2A, 0);
  analogWrite(motor3A, 250);
  analogWrite(motor4A, 0);
}

int STOP() { // STOP BUGGY
  analogWrite(motor1A, 0);
  analogWrite(motor2A, 0);
  analogWrite(motor3A, 0);
  analogWrite(motor4A, 0);
}

void setup() {
  Serial.begin(9600);

  pinMode(LEYE, INPUT);
  pinMode(REYE, INPUT);

  pinMode(motor1A, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor3A, OUTPUT);
  pinMode(motor4A, OUTPUT);

}

void loop() {
  int left = digitalRead(LEYE);
  int right = digitalRead(REYE);

  if (left && right) {
    STOP();

  }
  if (!left && !right) {
    AWF();

  }

  if (!left && right) {
    LWF();

  }
  if (left && !right) {
    RWF();

  }

}
