
#include <LargePlatform.h>

void LargePlatform::init(int BAUDRATE, uint8_t* dxlID, float WIDTH, float R){
  dxlWB.init("",BAUDRATE);
  Serial.begin(BAUDRATE);
  for(int i = 0;i<4;i++){
    dxlWB.ping(dxlID[i]);
    dxlWB.wheelMode(dxlID[i],0);
  }

  this->WIDTH = WIDTH;
  this->R = R;
  this->dxlID = dxlID;
}
void LargePlatform::setVelocity(float linVelocity, float angVelocity){
  float angularRight = (1/(2*R))*(2*linVelocity+angVelocity*WIDTH);
  float angularLeft = (1/(2*R))*(2*linVelocity-angVelocity*WIDTH);
  dxlWB.goalVelocity(dxlID[0],angularRight);  //Velocity Right Side
  dxlWB.goalVelocity(dxlID[1],-angularRight);

  dxlWB.goalVelocity(dxlID[2], -angularLeft);  //Velocity Left Side
  dxlWB.goalVelocity(dxlID[3], angularLeft);
}
float LargePlatform::getRealVelocity(uint8_t id){
  int32_t tempVel = 0;
  dxlWB.itemRead(id,"Present_Velocity",&tempVel);
  delay(5);
  double rotationsPerMinute = tempVel*0.229;
  float realAngular = rotationsPerMinute*3.14/30;
  if(id % 2 == 0){realAngular*=-1;}
  return realAngular;
}
