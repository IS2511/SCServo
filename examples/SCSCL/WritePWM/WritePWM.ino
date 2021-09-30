/*
电机模式例子
*/

#include <SCServo.h>

SCSCL sc;

void setup()
{
  Serial1.begin(1000000);
  sc.pSerial = &Serial1;
  delay(1000);
  sc.PWMMode(1);
}

void loop()
{
  sc.WritePWM(1, 500);
  delay(2000);
  sc.WritePWM(1, 0);
  delay(2000);
  sc.WritePWM(1, -500);
  delay(2000);
  sc.WritePWM(1,0);
  delay(2000);
}
