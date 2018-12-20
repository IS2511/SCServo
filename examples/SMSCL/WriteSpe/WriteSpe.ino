#include <SCServo.h>

SMSCL sm;

void setup()
{
	Serial1.begin(115200);
	sm.pSerial = &Serial1;
	sm.wheelMode(1);
}

void loop()
{
	sm.WriteSpe(1, 3000);
	delay(6000);
	sm.WriteSpe(1, 0);
	delay(6000);
	sm.WriteSpe(1, -3000);
	delay(6000);
	sm.WriteSpe(1, 0);
	delay(6000);
}
