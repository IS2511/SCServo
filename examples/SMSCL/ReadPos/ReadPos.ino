#include <SCServo.h>

SMSCL sm;
int LEDpin = 13;

void setup()
{
	pinMode(LEDpin,OUTPUT);
	digitalWrite(LEDpin, HIGH);
	Serial1.begin(115200);
  Serial.begin(115200);
  sm.pSerial = &Serial1;
}

void loop()
{
  u8 Err;
	s16 pos = sm.ReadPos(1, &Err);
	if(Err==0)
	{
	  digitalWrite(LEDpin, LOW);
		Serial.println(pos, DEC);
    delay(10);
	}
	else
	{
		digitalWrite(LEDpin, HIGH);
    delay(2000);
	}
}
