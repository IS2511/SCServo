#include <SCServo.h>

SMSBL sm;

void setup()
{
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  sm.RegWritePosEx(1, 0, 50);
  sm.RegWritePosEx(2, 0, 50);
  sm.RegWriteAction();
  delay(2000);
}

void loop()
{
	sm.RegWritePosEx(1, 4095, 50, 5);
	sm.RegWritePosEx(2, 4095, 50, 5);
	sm.RegWriteAction();
	delay(6000);
	sm.RegWritePosEx(1, 0, 50, 5);
	sm.RegWritePosEx(2, 0, 50, 5);
	sm.RegWriteAction();
	delay(6000);
}
