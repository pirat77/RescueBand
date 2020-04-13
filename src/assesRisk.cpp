#include <assesRisk.h>
#include <sensors.h>
#include <DallasTemperature.h>

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

int tempratureScore(DallasTemperature tempSensors){
  float temprature = readTemperature(tempSensors);
  if(temprature>38.9) return 2;
  if(temprature>37.9) return 1;
  if(temprature<36) return 1;
  if(temprature<35) return 2;
  if(temprature<34) return 3;
  return 0;
}

int bPMScore(){ 
  float systolicBP = readSystolicBP();
  if(systolicBP>199) return 2;
  if(systolicBP<100) return 1;
  if(systolicBP<80) return 2;
  if(systolicBP<70) return 3;
  return 0;
}

