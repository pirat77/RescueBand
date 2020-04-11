#include <Arduino.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

void setup() {
  Serial.begin(115200);
  WiFiManager wifiManager;

  // put your setup code here, to run once:
}

float readPulse(){
  float pulse;
  // read from sensors
  return pulse;
}

float readTemprature(){
  float temprature;
  // read from sensors
  return temprature;
}

float readSaturation(){
  float saturation;
  // read from sensors
  return saturation;
}

float readBreathRate(){
  float breathrate;
  // read from sensors
  return breathrate;
}

float calculateEarlyWarningScore(){
  
  float earlyWarningScore;
  float brathrate = readBreathRate();
  float saturation = readSaturation();
  float pulse = readPulse();
  float temprature = readTemprature();
  // calculation process
  // save results
  return earlyWarningScore;
}

void idleSleep(int time){
  // shutdown sensors and wifi
  delay(time);
  // activate sensors and wifi
}

int transformScoreIntoDelay(float warningScore){
  int delay;
  // transformation 1->24h 2-12h 3-6h 4-3h 5-90m 6-45m 7-25m 8-12m 9-6min 10=3min 11-1min 12->1s
  return delay;
}

boolean compareToHistoric(float warningScore){
  // read historic warning score
  // compare and make decision
  // return 
}

void callForHelp(float warningScore){
  // rescue protocol
}

void loop() {
  float warningScore = calculateEarlyWarningScore();
  if (compareToHistoric(warningScore)) {
    callForHelp(warningScore);
  }
  // map earlywWrningScore to interval
  int time = transformScoreIntoDelay(earlyWarningScore);
  idleSleep(time);


  // put your main code here, to run repeatedly:
}