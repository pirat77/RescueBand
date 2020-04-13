#include <sensors.h>
#include <DallasTemperature.h>

// TODO: implement sensometric funtions (temp done)

float readTemperature(DallasTemperature tempSensors){
  tempSensors.requestTemperatures();
  float temprature = tempSensors.getTempCByIndex(0);
  return temprature;
}

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