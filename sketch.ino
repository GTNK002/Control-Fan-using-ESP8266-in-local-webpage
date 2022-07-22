// please check the video
// https://www.youtube.com/channel/UCTM5Kv1_eWFYq74OKYLDMWw

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "ESP";
const char* password = "123456789";

MDNSResponder mdns;

String Domain = "home";
String switch1name = "Light";
String switch1 = "OFF";
String Fan = "OFF";

ESP8266WebServer server(80);

void handleRoot() {
 server.send(200, "text/html", 
"<!DOCTYPE html>" \
"<html>" \
"<head>" \
"<title>home</title>" \
"</head>" \
"<body>" \
"<h1>Home Automation</h1>" \
"<h2>"+ switch1name +": "+ switch1 +"</h2>" \
"<p><a href=\"/Switch1OFF\"><button class=\"button\">OFF</button></a><a href=\"/Switch1ON\"><button class=\"button\">ON</button></a></p>" \
"<h2>Fan: "+ Fan +"</h2>" \
"<p><a href=\"/FanOFF\"><button class=\"button\">OFF</button></a><a href=\"/FanSpeed1\"><button class=\"button\">Speed1</button></a><a href=\"/FanSpeed2\"><button class=\"button\">Speed2</button></a><a href=\"/FanSpeed3\"><button class=\"button\">Speed3</button></a><a href=\"/FanSpeed4\"><button class=\"button\">Speed4</button></a></p>" \
"</body>" \
"</html>" \
);
}

void switch1ON(){
  switch1 = "ON";
  digitalWrite(D1, LOW);
  handleRoot();
}

void switch1OFF(){
  switch1 = "OFF";
  digitalWrite(D1, HIGH);
  handleRoot();
}

void FanOFF(){
  Fan = "OFF";
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);
  digitalWrite(D8, HIGH);
  handleRoot();
}

void FanSpeed1(){
  Fan = "Speed1";
  digitalWrite(D7, HIGH);
  digitalWrite(D8, HIGH);
  delay(500);
  digitalWrite(D6, LOW);
  handleRoot();
}

void FanSpeed2(){
  Fan = "Speed2";
  digitalWrite(D6, HIGH);
  digitalWrite(D8, HIGH);
  delay(500);
  digitalWrite(D7, LOW);
}

void FanSpeed3(){
  Fan = "Speed3";
  digitalWrite(D8, HIGH);
  delay(500);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  handleRoot();
}

void FanSpeed4(){
  Fan = "Speed4";
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);
  delay(500);
  digitalWrite(D8, LOW);
  handleRoot();
}

void setup(void){
  pinMode(D1, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  digitalWrite(D4, HIGH);
  digitalWrite(D1, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);
  digitalWrite(D8, HIGH);
  
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); 

  if(mdns.begin(Domain)){
    Serial.println("MDNS Started: " + Domain + ".local/");
  }
 
  server.on("/", handleRoot);   
  server.on("/Switch1ON", switch1ON);  
  server.on("/Switch1OFF", switch1OFF);  
  server.on("/FanOFF", FanOFF);  
  server.on("/FanSpeed1", FanSpeed1);  
  server.on("/FanSpeed2", FanSpeed2); 
  server.on("/FanSpeed3", FanSpeed3); 
  server.on("/FanSpeed4", FanSpeed4);     

  server.begin();                 
  Serial.println("HTTP server started");
  digitalWrite(D4, LOW);
}

void loop(void){
  mdns.update();
  server.handleClient();  
}
