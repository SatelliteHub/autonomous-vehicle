// PRINT SSID AND IP ADRESS HERE
  WiFi.begin(ssid, pass);
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Adress:");
  Serial.println(ip);
  server.begin();




 WiFiClient client = server.available();
  if (client.connected()) { 
    
  }
/* OPTIONAL: TELL USER WHEN GO BUTTON IS PRESSED
      USING IF STATEMENT */
      
    client.write ("Client Connected");
    client.stop();



 
 
 if (c == 'g') {
      while (c != 's') {
        
      }
/* OPTIONAL: TELL USER WHEN GO BUTTON IS PRESSED
          USING IF STATEMENT */
          
          Serial.println ("Go Button Pressed");
          move_forward();


       
       
       
       // Detects when obstacle is within 10 cm dist.
        else if (distance < 10) {
          if (obstacle_seen != 1) {
            Serial.println ("stopping for obstacle at 10cm distance");
          


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
      Serial.println ("Stop Button Pressed");
      stop_all();
      // IF OPTIONAL CODE ABOVE IS USED RESET VARIABLE HERE
    }



        
