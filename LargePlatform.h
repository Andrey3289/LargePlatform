

#include <Arduino.h>
#include <DynamixelWorkbench.h>

class LargePlatform{
public:
  void init(int BAUDRATE, uint8_t* dxlID, float WIDTH, float R);
  void setVelocity(float linVelocity, float angVelocity);
  float getRealVelocity(uint8_t id);
  float WIDTH,R;
  uint8_t* dxlID;
  DynamixelWorkbench dxlWB;

};
