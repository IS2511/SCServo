#include <SCServo.h>

SCSCL sc;

void setup()
{
  Serial1.begin(1000000);
  sc.pSerial = &Serial1;
}

void loop()
{
  sc.WritePos(1, 1023, 2000);//舵机(ID1),运行至1023位置,运行时间T=2100ms
  delay(2100); 
  sc.WritePos(1, 0, 2000);//舵机(ID1),运行至0位置,运行时间T=2100ms
  delay(2100);
}
