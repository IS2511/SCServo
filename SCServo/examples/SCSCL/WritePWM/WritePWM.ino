#include <SCServo.h>

SCSCL sm;

void setup()
{
	Serial1.begin(115200);
	sm.pSerial = &Serial1;
	delay(500);
	sm.pwmMode(0);
}

void loop()
{
	sm.WritePWM(0, 500);
	delay(3000);
	sm.WritePWM(0, 0);
	delay(2000);
	sm.WritePWM(0, -500);
	delay(3000);
	sm.WritePWM(0,0);
	delay(2000);
}
