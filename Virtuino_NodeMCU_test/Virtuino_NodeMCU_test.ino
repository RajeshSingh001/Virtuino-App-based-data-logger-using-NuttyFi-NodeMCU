#include <ESP8266WiFi.h>
#include "Virtuino_ESP_WifiServer.h"

const char* ssid = "ESPServer_RAJ";    
const char* password = "RAJ@12345";

WiFiServer server(8000);                      // Server port

Virtuino_ESP_WifiServer virtuino(&server);

 int storedValue=0;
 int counter =0;
 long storedTime=0;
 int FIRST_SMOKE;
 int SECOND_SMOKE;
 float THIRD_SMOKE;
 float FOUR_SMOKE;
void setup() 
{
   //----- Virtuino settings
  virtuino.DEBUG=true;                         // set this value TRUE to enable the serial monitor status
  virtuino.password="1234";                    // Set a password to your web server for more protection 
                                               // avoid special characters like ! $ = @ # % & * on your password. Use only numbers or text characters

  Serial.begin(9600);                          // Enable this line only if DEBUG=true
  delay(10);

  //----- NodeMCU module settings
  //----- prepare GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);
  
  //----  1. Settings as Station - Connect to a WiFi network
  Serial.println("Connecting to "+String(ssid));
  WiFi.mode(WIFI_STA);                       // Config module as station only.
  WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED)
   {
     delay(500);
     Serial.print(".");
    }
   Serial.println("");
   Serial.println("WiFi connected");
   Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Server started");
}

void loop()
{
  virtuino.run();
  int LEFT=virtuino.vDigitalMemoryRead(0);              // Read virtual memory 0 from Virtuino app 
   int RIGHT=virtuino.vDigitalMemoryRead(1);              // Read virtual memory 0 from Virtuino app 
   int STRAIGHT=virtuino.vDigitalMemoryRead(2);              // Read virtual memory 0 from Virtuino app 
    int BACKWARD=virtuino.vDigitalMemoryRead(3);              // Read virtual memory 0 from Virtuino app 
     int STOP=virtuino.vDigitalMemoryRead(4);              // Read virtual memory 0 from Virtuino app 
    if(LEFT==HIGH)
    {
     Serial.print(10);
     Serial.print('\n');  
     }
      if(RIGHT==HIGH)
    {
     Serial.print(20);
     Serial.print('\n');  
     }
      if(STRAIGHT==HIGH)
    {
     Serial.print(30);
     Serial.print('\n');  
     }
      if(BACKWARD==HIGH)
    {
     Serial.print(40);
     Serial.print('\n');  
     }
      if(STOP==HIGH)
    {
     Serial.print(50);
     Serial.print('\n');  
     }
   serial_event();
//   Serial.print(SECOND_SMOKE);
//   Serial.println(SECOND_SMOKE);
   FIRST_SMOKE=102;
   SECOND_SMOKE=101;
   THIRD_SMOKE=30.03;
   FOUR_SMOKE=78.13;
   virtuino.vMemoryWrite(4,FIRST_SMOKE);
   virtuino.vMemoryWrite(5,SECOND_SMOKE);
   virtuino.vMemoryWrite(6,THIRD_SMOKE);
   virtuino.vMemoryWrite(7,FOUR_SMOKE);
   long t= millis();       // read the time
    if (t>storedTime+5000)
    {
      counter++;            // increase counter by 1
      if (counter>20) counter=0;    // limit = 20
      storedTime = t; 
      virtuino.vMemoryWrite(12,counter);      // write counter to virtual pin V12
    }
  }

void serial_event()
{
  if (Serial.available()<1)  return;
  char S=Serial.read();
  if (S!='\r')                 return;
   FIRST_SMOKE=Serial.parseInt();
   SECOND_SMOKE=Serial.parseInt();
}



 


