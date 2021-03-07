import controlP5.*;
import processing.net.*;
ControlP5 cp5;
Client myClient;
String data;

void setup() {
  size(400, 200); //400, 200
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

  // READ STRING FROM ARDUINO AND PLACE IN "data" VARIABLE


  // USING IF STATEMENT PRINT DATA RECEIVED FROM ARDUINO
  
  
}


public void go(int value) {
  if (myClient.active()) {

    // SEND CHARACTER 'g' TO ARDUINO (g STANDS FOR GO)
    
    
  }
}



public void stop(int value) {
  if (myClient.active()) {

    // SEND CHARACTER 's' TO ARDUINO (s STANDS FOR STOP)
    
    
  }
}
