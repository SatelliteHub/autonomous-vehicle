import controlP5.*;
import processing.net.*;

ControlP5 cp5;
Client myClient;
String data;

void setup() {
  size(400, 200);
  cp5 = new ControlP5(this);
  myClient=new
    Client(this, "ENTER IP ADRESS FROM ARDUINO HERE", 5200);

  cp5.addButton("forward")
    .setValue(0)
    .setPosition(140, 20)
    .setSize(120, 50);
  cp5.addButton("reverse")
    .setValue(0)
    .setPosition(140, 140)
    .setSize(120, 50);
  cp5.addButton("right")
    .setValue(0)
    .setPosition(270, 80)
    .setSize(120, 50);
  cp5.addButton("left")
    .setValue(0)
    .setPosition(10, 80)
    .setSize(120, 50);
  cp5.addButton("stop")
    .setValue(0)
    .setPosition(140, 80)
    .setSize(120, 50);
}

void draw() {
  background (255, 255, 255);
}

public void forward(int value) {
  if (myClient.active()) {
    myClient.write("f");
  }
}

public void reverse(int value) {
  if (myClient.active()) {
    myClient.write("b");
  }
}

public void right(int value) {
  if (myClient.active()) {
    myClient.write("r");
  }
}

public void left(int value) {
  if (myClient.active()) {
    myClient.write("l");
  }
}

public void stop(int value) {
  if (myClient.active()) {
    myClient.write("s");
  }
}
