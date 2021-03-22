#include <WiFiNINA.h>

// Wi-Fi Connection ****** SECURITY WARNING ******
char ssid[] = " "; // DO NOT UPLOAD SSID ON GITLAB
char pass[] = " "; // DO NOT UPLOAD PASSWORD ON GITLAB
WiFiServer server(5200);

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


int right_turn() { // TURN RIGHT
  analogWrite(LM1, 255);
  analogWrite(LM2, 0);
  analogWrite(RM1, 0);
  analogWrite(RM2, 155);
}

int left_turn() { // TURN LEFT
  analogWrite(LM1, 0);
  analogWrite(LM2, 155);
  analogWrite(RM1, 255);
  analogWrite(RM2, 0);
}

int move_forward() { // MOVE STRAIGHT
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

int obstacle_seen; // For Message when Obstacle is seen
int last_connected; // For Message for Last Connection
int go_button_state; // For Message when Go But. is H/L

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

  WiFi.begin(ssid, pass);
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address:");
  Serial.println(ip);
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client.connected()) {
    if (last_connected != 1) {
      //Serial.println("Client Connected");
      client.write("Client Connected\n");
      last_connected = 1;
    }
    char c = client.read();

    // 'g' for GO command and 's' for STOP command
    if (c == 'g') {
      while (c != 's') {
        if (go_button_state != 1) {
          //Serial.println("GO");
          client.write("GO\n");
          go_button_state = 1;
        }

        // Ultrasonic
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
        
        // Detects when obstacle is further 10 cm dist.
        if (distance > 10) {

          if (left && right) {
            stop_all();
            if (obstacle_seen != 0) {
              client.write("No Obstacle\n");
              obstacle_seen = 0;
              delay(100);
            }
          }
          if (!left && !right) {
            move_forward();
            if (obstacle_seen != 0) {
              client.write("No Obstacle\n");
              obstacle_seen = 0;
              delay(100);
            }

          }
          if (!left && right) {
            right_turn();
            if (obstacle_seen != 0) {
              client.write("No Obstacle\n");
              obstacle_seen = 0;
              delay(100);
            }
          }
          if (left && !right) {
            left_turn();
            if (obstacle_seen != 0) {
              client.write("No Obstacle\n");
              obstacle_seen = 0;
              delay(100);
            }
          }
        }
        // Detects when obstacle is within 10 cm dist.
        else if (distance <= 10) {
          if (obstacle_seen != 1) {
            //Serial.println("Stopping for Obstacle at 10cm Distance");
            client.write("Stopping for Obstacle at 10cm Distance\n");
            obstacle_seen = 1;
            delay(100);
          }
          stop_all();
        }
        c = client.read();
      }
      //Serial.println("STOP");
      client.write("STOP\n");
      stop_all();
      go_button_state = 0;
      last_connected = 1;
    }
    else if (c == 's') {
      //Serial.println("STOP");
      client.write("STOP\n");
      stop_all();
      go_button_state = 0;
      last_connected = 1;
    }
  }
}
