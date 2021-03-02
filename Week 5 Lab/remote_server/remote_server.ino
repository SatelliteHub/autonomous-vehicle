// ARDUINO SERVER

#include <WiFiNINA.h>

char ssid[] = "ENTER HERE SSID";
char pass[] = "ENTER HERE PASSWORD";
WiFiServer server(5200);

// L293D Connection
const int LM1 = 17; // LEFT MOTOR 1 = 1A
const int LM2 = 16; // LEFT MOTOR 2 = 2A
const int RM1 = 6;  // RIGHT MOTOR 1 = 3A
const int RM2 = 12; // RIGHT Motor 2 = 4A

int left_turn() { // LEFT WHEEL FORWARD
  analogWrite(LM1, 250);
  analogWrite(LM2, 0);
  analogWrite(RM1, 0);
  analogWrite(RM2, 0);
}

int right_turn() { // TURN RIGHT
  analogWrite(LM1, 0);
  analogWrite(LM2, 0);
  analogWrite(RM1, 250);
  analogWrite(RM2, 0);
}

int move_forward() { // MOVE FORWARD
  analogWrite(LM1, 250);
  analogWrite(LM2, 0);
  analogWrite(RM1, 250);
  analogWrite(RM2, 0);
}

int move_backward() { // MOVE BACKWARD
  analogWrite(LM1, 0);
  analogWrite(LM2, 250);
  analogWrite(RM1, 0);
  analogWrite(RM2, 250);
}

int stop_all() { // STOP BUGGY
  analogWrite(LM1, 0);
  analogWrite(LM2, 0);
  analogWrite(RM1, 0);
  analogWrite(RM2, 0);
}

void setup() {
  Serial.begin(9600);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

  WiFi.begin(ssid, pass);
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address:");
  Serial.println(ip);
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client.connected()) {
    Serial.println("Client Connected");
    char c = client.read();
    if (c == 'f') {
      move_forward();
    }
    if (c == 'b') {
      move_backward();
    }
    if (c == 'r') {
      right_turn();
    }
    if (c == 'l') {
      left_turn();
    }
    if (c == 's') {
      stop_all();
    }
  }
}
