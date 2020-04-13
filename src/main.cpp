#include <Arduino.h>
#include <assesRisk.h>
#include <fstream>
#include <saveToLog.h>
#include <string>
#include <sensors.h>
#include <OneWire.h>
#include <timeUNIX.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#define PULSE_ECHO 1
#define TEMPRATURE_ECHO 2
#define SATURATION_ECHO 3
#define BREATHRATE_ECHO 4
#define SYSTOLICBP_ECHO 5
#define LED_OUTPUT 6

OneWire oneWire(TEMPRATURE_ECHO);
DallasTemperature tempSensors(&oneWire);
uint32_t timeUNIX;
uint32_t last_NTP;

void setup() {
  Serial.begin(115200);
  pinMode(PULSE_ECHO, INPUT);
  pinMode(TEMPRATURE_ECHO, INPUT);
  pinMode(SATURATION_ECHO, INPUT);
  pinMode(BREATHRATE_ECHO, INPUT); 
  pinMode(SYSTOLICBP_ECHO, INPUT); 
  pinMode(LED_OUTPUT, OUTPUT);

  // TODO: find apropiate wifi library
  WiFiManager wifiManager;

  tempSensors.setWaitForConversion(true);
  tempSensors.begin();  
}

float calculateEarlyWarningScore(){
  int earlyWarningScore = bPMScore() + tempratureScore(tempSensors) + pulseScore() + saturationScore() + breathScore() + adnotationScore();
  saveToLog(earlyWarningScore, readTemperature(tempSensors), readPulse(), readBreathRate(), readSaturation(), readSystolicBP());
  return earlyWarningScore;
}

void batteryCheck(){
  // TODO: Battery Check

}

boolean compareToHistoric(int warningScore){
  // TODO: asses fluctuation of patients state
  // read historic warning score
  // compare and make decision
  // return 
  return true;
}

void callForHelp(int warningScore){
  // TODO: search for apropiate caregiver
  // rescue protocol
}

void loop() {
  int warningScore = calculateEarlyWarningScore();
  if (compareToHistoric(warningScore)) {
    callForHelp(warningScore);
  }
  int timeInterval = transformScoreIntoDelay(warningScore);
  batteryCheck();
  if(timeInterval<60000){
    delay(timeInterval);
  } else {ESP.deepSleep(timeInterval);}
}