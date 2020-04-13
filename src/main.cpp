#include <Arduino.h>
#include <fstream>
#include <string>
#include <vector>
#include <OneWire.h>
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

enum adnotationValue{
  alert = 'Alert',
  verbal = 'Verbal',
  pain = 'Pain',
  unresponsive = 'Unresponsive'
};

int getEnumKeyByStringValue(String myValue){
   for (int i = alert; i = unresponsive+1; i++){
    if (static_cast<String>(adnotationValue(i)) == myValue) 
      return i; 
   }
   return 0;
}

// TODO: extrackt libraries from main.cpp

// TODO: implement UNIX time handling and separate logs for every day

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

 // TODO: implement sensometric funtions (temp done)

float readPulse(){
  float pulse;
  // read from sensors (BPM)
  return pulse;
}

float readSystolicBP(){
  float systolicBP;
  // measure systolicBP (mmHG)
  return systolicBP;
}

float readTemprature(){
  tempSensors.requestTemperatures();
  float temprature = tempSensors.getTempCByIndex(0);
  return temprature;
}

float readSaturation(){
  float saturation;
  // read from sensors (SpO2)
  return saturation;
}

float readBreathRate(){
  float breathrate;
  // read from sensors (breaths/min)
  return breathrate;
}

void saveToLog(int earlyWarningScore){
  File log = SPIFFS.open("/log.csv", "a"); 
      log.print(millis());
      log.print(',');
      log.print(readTemprature());
      log.print(',');
      log.print(readPulse());
      log.print(',');
      log.print(readBreathRate());
      log.print(',');
      log.print(readSaturation());
      log.print(',');
      log.print(readSystolicBP());
      log.print(',');
      log.println(earlyWarningScore);
      log.close();
}

int breathScore(){
  float breathrate = readBreathRate();
  if(breathrate>35) return 3;
  if(breathrate>30) return 2;
  if(breathrate>20) return 1;
  if(breathrate<7) return 3;
  return 0;
}

int saturationScore(){
  float saturation = readSaturation();
  if(saturation<85) return 3;
  if(saturation<89) return 2;
  if(saturation<92) return 1;
  return 0;
}

int pulseScore(){
  float pulse = readPulse();
  if(pulse>129) return 3;
  if(pulse>109) return 2;
  if(pulse>99) return 1;
  if(pulse<50) return 1;
  return 0; 
}

int tempratureScore(){
  float temprature = readTemprature();
  if(temprature>38.9) return 2;
  if(temprature>37.9) return 1;
  if(temprature<36) return 1;
  if(temprature<35) return 2;
  if(temprature<34) return 3;
}

int bPMScore(){ 
  float systolicBP = readSystolicBP();
  if(systolicBP>199) return 2;
  if(systolicBP<100) return 1;
  if(systolicBP<80) return 2;
  if(systolicBP<70) return 3;
  return 0;
}

std::string getLastAdnotation(){
  std::string last_line;
  std::ifstream infile("/adnotations.csv");
  std::string line;
  while (std::getline(infile, line)){
    if (line.c_str() != NULL) last_line = line;
  }
  infile.close();
  return last_line;
}

int adnotationScore(){
  String values[] = {"", "", ""};
  std::string last_adnotation = getLastAdnotation();
  char lineArray[last_adnotation.size() + 1];
  strcpy(lineArray, last_adnotation.c_str());
  int valueID = 0;  
  for (int i = 0; i<last_adnotation.size()+1; i++){
      if (lineArray[i]==',') valueID++;
      else values[valueID] += lineArray[i];
  } 
  return getEnumKeyByStringValue(values[1]);
}

float calculateEarlyWarningScore(){
  int earlyWarningScore = bPMScore() + tempratureScore() + pulseScore() + saturationScore() + breathScore() + adnotationScore();
  saveToLog(earlyWarningScore);
  return earlyWarningScore;
}

int transformScoreIntoDelay(int warningScore){
  switch (warningScore)
  {
  case 0:
    return 21600000;    
  case 1:
    return 10800000;
  case 2: 
    return 3600000;
  case 3:
    return 600000;
  case 4:
    return 300000;
  case 5: 
    return 60000;
  case 6: 
    return 30000;
  case 7:
    return 15000;
  case 8:
    return 5000;
  case 9:
    return 1000;
  case 10:
    return 500;
  case 11:
    return 100;
  case 12:
    return 10;   
  default:
    return 0;
  }
}

void batteryCheck(){
  // TODO: Battery Check

}

boolean compareToHistoric(int warningScore){
  // TODO: asses fluctuation of patients state
  // read historic warning score
  // compare and make decision
  // return 
}

void callForHelp(int warningScore){
  // TODO: search for apropiate caregiver
  // rescue protocol
}

void saveAdnotation(int state, String comment){
  File adnotations = SPIFFS.open("/adnotations.csv", "a"); 
      adnotations.print(millis());
      adnotations.print(',');
      adnotations.print(adnotationValue(state)); 
      adnotations.print(',');
      adnotations.println(comment);
      adnotations.close();
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