import controlP5.*;
import processing.net.*;
ControlP5 cp5;
Client myClient;
String data;
String last_data = " ";
byte buffer = 10;

void setup() {
  size(400, 200);
  cp5 = new ControlP5(this);
  myClient = new
    Client(this, "ENTER IP ADRESS FROM ARDUINO HERE / DO NOT UPLOAD ON GITLAB", 5200); 

  cp5.addButton("go")
    .setValue(0)
    .setPosition(10, 80)
    .setSize(120, 50)
    ;

  cp5.addButton("stop")
    .setValue(0)
    .setPosition(270, 80)
    .setSize(120, 50)
    ;
}

void draw() {
  background (255, 255, 255);

  fill(0, 102, 153);
  data = myClient.readStringUntil(buffer);
  textSize(20);
  textAlign(CENTER);
  text(last_data, 200, 180); // Printing in the GUI

  if (data != null) {
    println(data); // Diagnostic Printing in the Console
    last_data = data;
  }
}

// GO Button
public void go(int value) {
  if (myClient.active()) {
    myClient.write("g");
    println("Go Button Pressed"); // Diagnostic Printing in the Console
  }
}

// STOP Button
public void stop(int value) {
  if (myClient.active()) {
    myClient.write("s");
    println("Stop Button Pressed"); // Diagnostic Printing in the Console
  }
}
