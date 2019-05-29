#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <DHT.h>  // Including library for dht
#include <ThingSpeak.h>;
const char* ssid = "******"; //Your Network SSID
const char* password = "*****"; //Your Network Password
int val;
int gaspin = A0; //LDR Pin Connected at A0 Pin
#define DHTPIN 0          //pin where the dht11 is connected
DHT dht(DHTPIN, DHT11);
WiFiClient client;
unsigned long myChannelNumber = ######; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "########"; //Your Write API Key
void setup()
{
Serial.begin(9600);
delay(10);
// Connect to WiFi network
WiFi.begin(ssid, password);
ThingSpeak.begin(client); 
}
void loop() 
{
val = analogRead(gaspin); //Read Analog values and Store in val variable
Serial.println(val); //Print on Serial Monitor
float h = dht.readHumidity();
Serial.println(h);
float t = dht.readTemperature();
Serial.println(t);
delay(1000);
ThingSpeak.writeField(myChannelNumber, 1,val, myWriteAPIKey);
ThingSpeak.writeField(myChannelNumber, 2,t, myWriteAPIKey);
ThingSpeak.writeField(myChannelNumber, 3,h, myWriteAPIKey);//Update in ThingSpeak
delay(100);
}
