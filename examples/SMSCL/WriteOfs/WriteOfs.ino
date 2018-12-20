#include <SCServo.h>

int LEDpin = 13;
SMSCL sm;

void setup()
{
  pinMode(LEDpin, OUTPUT);
  Serial.begin(115200);
  sm.pSerial = &Serial;
}

void loop()
{
  digitalWrite(LEDpin, LOW);
  sm.unLockEprom(1);//(ID1)解锁EPROM
  sm.WriteOfs(1, -1000);//Ofs:0~2047/-1~-2047
  sm.LockEprom(1);//(ID1)加锁EPROM
  digitalWrite(LEDpin, HIGH);
  while(1);
}
