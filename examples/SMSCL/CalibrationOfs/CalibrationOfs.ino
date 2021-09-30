/*
中位校准例子
*/

#include <SCServo.h>

int LEDpin = 13;
SMSCL sm;

void setup()
{
  pinMode(LEDpin, OUTPUT);
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  delay(1000);
}

void loop()
{
  digitalWrite(LEDpin, LOW);
  sm.CalibrationOfs(1);
  digitalWrite(LEDpin, HIGH);
  while(1);
}
