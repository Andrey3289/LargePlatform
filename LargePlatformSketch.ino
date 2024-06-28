
#include <LargePlatform.h>

int BAUDRATE = 1000000;
float WIDTH = 0.35;
float R = 0.08; 
uint8_t dxlID[4] = {1,4,2,3};
LargePlatform platform;

const int bufferSize = 30;
String bufferStr = "";
float linVel = 0;
float angVel = 0;
bool isDrop = 0;
float timerForSending = 0;
float timerForSafety = 0;

void setup() {
  platform.init(BAUDRATE,dxlID,WIDTH,R);
}

void loop() {
  if(Serial.available()>0){
    timerForSafety = millis();
    bufferStr = "";
    linVel = 0;
    angVel = 0;
    int bytes = Serial.available();
    int i = 0;
    for(;i<bytes;i++){
      char data = Serial.read();
      if(data != ':'){bufferStr += data;}
      else{i++;break;}
    }
    linVel = bufferStr.toFloat();
    bufferStr = "";
    for(;i<bytes;i++){
      char data = Serial.read();
      if(data != ':'){bufferStr += data;}
      else{i++;break;}
    }
    angVel = bufferStr.toFloat();
    bufferStr = "";
    for(;i<bytes;i++){
      char data = Serial.read();
      if(data != ':'){bufferStr += data;}
      else{i++;break;}
    }
    isDrop = bufferStr.toFloat();
    platform.setVelocity(linVel,angVel);
  }
  if(millis()-timerForSafety > 1500){
    timerForSafety = millis();
    platform.setVelocity(0,0);
  }
  if(millis()-timerForSending > 100){
    timerForSending = millis();
    bufferStr =  String(platform.getRealVelocity(dxlID[0]))+ ':';
    bufferStr += String(platform.getRealVelocity(dxlID[1]))+ ':';
    bufferStr += String(platform.getRealVelocity(dxlID[2]))+ ':';
    bufferStr += String(platform.getRealVelocity(dxlID[3]))+ ':' + '\0';
    Serial.println(bufferStr);
  }
}
