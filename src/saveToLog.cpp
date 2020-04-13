#include <Arduino.h>
#include <saveToLog.h>
#include <fstream>
#include <ESP8266WiFi.h> 
#include <sensors.h>

enum adnotationValue{
  alert = 'Alert',
  verbal = 'Verbal',
  pain = 'Pain',
  unresponsive = 'Unresponsive',
  outofspace = 'outofspace'
};

int getEnumKeyByStringValue(String myValue){
   for (int i = alert; i = outofspace; i++){
    if (static_cast<String>(adnotationValue(i)) == myValue){return i;}  
   }
   return 0;
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

void saveToLog(int earlyWarningScore, float temperature, float pulse, float breath, float saturation, float systolicBP){
  File log = SPIFFS.open("/log.csv", "a"); 
      log.print(millis());
      log.print(',');
      log.print(temperature);
      log.print(',');
      log.print(pulse);
      log.print(',');
      log.print(breath);
      log.print(',');
      log.print(saturation);
      log.print(',');
      log.print(systolicBP);
      log.print(',');
      log.println(earlyWarningScore);
      log.close();
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