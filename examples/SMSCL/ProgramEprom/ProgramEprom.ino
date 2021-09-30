/*
舵机参数编程
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
  digitalWrite(LEDpin, LOW);
  sm.unLockEprom(1);//打开EPROM保存功能
  sm.writeByte(1, SMSBL_ID, 2);//ID
  sm.LockEprom(2);//关闭EPROM保存功能
  digitalWrite(LEDpin, HIGH);
}

void loop()
{

}
