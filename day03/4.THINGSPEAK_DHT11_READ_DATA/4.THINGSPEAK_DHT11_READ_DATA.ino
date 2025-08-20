#include <WiFi.h> // Install the WiFi library
#include "ThingSpeak.h" // always include thingspeak header file after 

// Network Parameters
char* ssid = "MY_SSID"; // your network SSID (name) 
char* pass ="MY_PASSWORD" ; // your network password
WiFiClient client;
int field[2] = {1,2};

// ThingSpeak information
unsigned long channelNumber = ******; //6 digit channel number 
const char * readAPIKey = "****************"; //16 char API Key 
void setup() {
Serial.begin(115200); // Initialize serial 
while (!Serial) {// wait for serial port to connect. Needed for Leonardo native USB port only
}
WiFi.mode(WIFI_STA);
ThingSpeak.begin(client); // Initialize ThingSpeak
// Connect or reconnect to WiFi
if(WiFi.status() != WL_CONNECTED){
Serial.print("Attempting to connect to SSID: ");
Serial.println(ssid);
while(WiFi.status() != WL_CONNECTED){
WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
Serial.print(".");
delay(5000); 
}
Serial.println("\nConnected");
}
}


void loop() {
Serial.println("Waiting...");
int x = ThingSpeak.readMultipleFields(channelNumber, readAPIKey);
if(x == 200)
{
float t = ThingSpeak.getFieldAsFloat(field[1]); // Field 1
float h = ThingSpeak.getFieldAsFloat(field[2]); // Field 2
Serial.println("TEMPERATURE : " + String(t));
Serial.println("HUMIDITY : " + String(h));
}
else{
Serial.println("Problem reading channel. HTTP error code " + String(x)); 
}
Serial.println();
delay(20000); // no need to fetch too often
}
