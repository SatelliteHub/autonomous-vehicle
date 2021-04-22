import controlP5.*;
import processing.net.*;
ControlP5 cp5;
Client myClient;
int velocity;
int last_velocity;

String data;
String last_data = " ";
byte buffer = 10;

void setup() {
  size(400, 200);
  cp5 = new ControlP5(this);
  myClient=new
    //********** SECURITY WARNING **********
    // DO NOT UPLOAD IP ADDRESS ON GITLAB
    Client(this, " ", 5200); 

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
  velocity = myClient.read();
  textSize(20);
  textAlign(LEFT);
  text("Speed: ~", 10, 30); 
  textAlign(RIGHT);
  text(last_velocity, 130, 30);
  text(" cm/s", 190, 30);

  fill(0, 102, 153);
  //data = myClient.readStringUntil(buffer);
  textSize(20);
  textAlign(CENTER);
  text(last_data, 200, 180);

  if (velocity != -1 && velocity <= 20) {
    last_velocity = velocity;
    //println(last_velocity);
    last_data = "Obstacle in Proximity";
  }
}

// GO Button
public void go(int value) {
  if (myClient.active()) {
    myClient.write("g");
    last_data = "GO";
  }
}

// STOP Button
public void stop(int value) {
  if (myClient.active()) {
    myClient.write("s");
    last_data = "STOP";
  }
}
