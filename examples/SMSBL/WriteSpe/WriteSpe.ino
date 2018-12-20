#include <SCServo.h>

SMSBL sm;

void setup()
{
	Serial1.begin(115200);
	sm.pSerial = &Serial1;
	sm.wheelMode(1);
}

void loop()
{
	sm.WriteSpe(1, 50, 5);
	delay(6000);
	sm.WriteSpe(1, 0, 5);
	delay(6000);
	sm.WriteSpe(1, -50, 5);
	delay(6000);
	sm.WriteSpe(1, 0, 5);
	delay(6000);
}
