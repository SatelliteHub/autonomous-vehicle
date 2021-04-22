#include <Arduino_LSM6DS3.h>
#include <WiFiNINA.h>

// Wi-Fi Connection ****** SECURITY WARNING ******
char ssid[] = " "; // DO NOT UPLOAD SSID ON GITLAB
char pass[] = " "; // DO NOT UPLOAD PASSWORD ON GITLAB
WiFiServer server(5200);

int speed_limit = 0;
int motor_limit = 255;

// Define Variables we'll be connecting to
double setpoint; // Desired Value
double input; // US Sensor
double output; // Motor

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
  analogWrite(LM1, motor_limit);
  analogWrite(LM2, 0);
  analogWrite(RM1, 0);
  analogWrite(RM2, 0);
}

int left_turn() { // RIGHT WHEEL FORWARD
  analogWrite(LM1, 0);
  analogWrite(LM2, 0);
  analogWrite(RM1, motor_limit);
  analogWrite(RM2, 0);
}

int move_forward() { // ALL WHEEL FORWARD
  analogWrite(LM1, motor_limit);
  analogWrite(LM2, 0);
  analogWrite(RM1, motor_limit);
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

  WiFi.begin(ssid, pass);
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address:");
  Serial.println(ip);
  server.begin();
}


void loop() {
  WiFiClient client = server.available();
  if (client.connected()) {

    char c = client.read();
    if (c == 'h') {
      speed_limit = 100;
      while (c != 'm' && c != 's') {
        float aX, aY, aZ;
        float gX, gY, gZ;
        const char * spacer = ", ";
        
        int v, vX, vY, vZ;
        int dt = 10;
  
        // IR Sensor
        int left = digitalRead(LEYE);
        int right = digitalRead(REYE);
  
        long duration = 0;
        int distance = 0;
  
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
  
        if (distance > 10) {
  
          // Determine IMU Values
          if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
            IMU.readAcceleration(aX, aY, aZ);
            IMU.readGyroscope(gX, gY, gZ);
  
            vX += 50 * abs((aX * dt));
            vY += 50 * abs((aY * dt));
            //vZ = abs(10*(aZ * dt));
  
            v = sqrt(vX * vX + vY * vY);
  
            int reduce_motor_limit = 255;
  
            motor_limit = reduce_motor_limit;
  
            Serial.print(v); Serial.print(spacer);
  
            delay(100);
          }
  
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
        else if (distance <= 10) {
          stop_all();
        }
        break;
      }
      c = client.read();
    }











    else if (c == 'm') {
      while (c != 'f' && c != 's') {
        speed_limit = 3;
        float aX, aY, aZ;
        float gX, gY, gZ;
        const char * spacer = ", ";
        
        int v, vX, vY, vZ;
        int dt = 10;
        
        // IR Sensor
        int left = digitalRead(LEYE);
        int right = digitalRead(REYE);
  
        long duration = 0;
        int distance = 0;
  
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
  
        if (distance > 10) {
  
          // Determine IMU Values
          if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
            IMU.readAcceleration(aX, aY, aZ);
            IMU.readGyroscope(gX, gY, gZ);
  
            vX += 50 * abs((aX * dt));
            vY += 50 * abs((aY * dt));
            //vZ = abs(10*(aZ * dt));
  
            v = sqrt(vX * vX + vY * vY);
  
            int reduce_motor_limit = 100;
  
            motor_limit = reduce_motor_limit;
  
            Serial.print(v); Serial.print(spacer);
  
            delay(100);
          }
  
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
        else if (distance <= 10) {
          stop_all();
        }
        break;
      }
      c = client.read();
    }










    else if (c == 's') {
      while (c != 'f' && c != 'm') {
        speed_limit = 0;
        float aX, aY, aZ;
        float gX, gY, gZ;
        const char * spacer = ", ";
        
        int v, vX, vY, vZ;
        int dt = 10;
        
        // IR Sensor
        int left = digitalRead(LEYE);
        int right = digitalRead(REYE);
  
        long duration = 0;
        int distance = 0;
  
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
  
        if (distance > 10) {
  
          // Determine IMU Values
          if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
            IMU.readAcceleration(aX, aY, aZ);
            IMU.readGyroscope(gX, gY, gZ);
  
            vX += 50 * abs((aX * dt));
            vY += 50 * abs((aY * dt));
            //vZ = abs(10*(aZ * dt));
  
            v = sqrt(vX * vX + vY * vY);
  
            int reduce_motor_limit = 0;
  
            motor_limit = reduce_motor_limit;
  
            Serial.print(v); Serial.print(spacer);
  
            delay(100);
          }
  
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
        else if (distance <= 10) {
          stop_all();
        }
        break;
      }
      c = client.read();
    }
  }
}
