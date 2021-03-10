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

int obstacle_seen; //For Message when Obstacle is seen

// OPTIONAL MESSAGE VARIABLE
int last_connected;
int go_button_state;



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
  Serial.print("IP Adress:");
  Serial.println(ip);
  server.begin();


}

void loop() {
  WiFiClient client = server.available();
  if (client.connected()) {


    /* OPTIONAL: TELL USER WHEN GO BUTTON IS PRESSED
      USING IF STATEMENT */
    client.write ("Client Connected");
    client.stop();

    char c = client.read(); // Read char from Processing

    // 'g' for GO command and 's' for STOP command
    if (c == 'g') {
      while (c != 's') {

        client.write("Go Button Pressed");
        move_forward();

        /* OPTIONAL: TELL USER WHEN GO BUTTON IS PRESSED
          USING IF STATEMENT */



        int left = digitalRead(LEYE);
        int right = digitalRead(REYE);





        // INSERT HERE THE ULTRASONIC CODE
        digitalWrite(UST, LOW);
        delayMicroseconds(2);
        digitalWrite(UST, HIGH);
        delayMicroseconds(10);
        digitalWrite(UST, LOW);

        long duration = pulseIn(USE, HIGH); //Count when USE is high and stops when USE is low

        int distance = duration / 58;


        // Detects when obstacle is further 10 cm dist.
        if (distance > 10) {






          // INSERT HERE THE LINE FOLLOWING CODE
          if (!left && !right) {
            move_forward();
          }

          if (left && right) {
            stop_all();
          }

          if (!left && right) {
            right_turn();
          }

          if (left && !right) {
            left_turn();
          }







        }
        // Detects when obstacle is within 10 cm dist.
        else if (distance < 10) {
          if (obstacle_seen != 1) {

            client.write("stopping for obstacle at 10cm distance");

            // TELEMETRY:
            // PRINT TO PROCESSING CONSOLE THE MESSAGE
            // (MESSAGE EXAMPLE ON BLACKBOARD > BRZE CH)


            // CHANGE THE VARIABLE VALUE TO 1


          }
          stop_all();
        }
        c = client.read();
      }
      stop_all();

      // IF OPTIONAL CODE ABOVE IS USED RESET VARIABLE HERE

    }
    else if (c == 's') {
      client.write("Stop Button Pressed");
      stop_all();
      // IF OPTIONAL CODE ABOVE IS USED RESET VARIABLE HERE
    }
  }
}
