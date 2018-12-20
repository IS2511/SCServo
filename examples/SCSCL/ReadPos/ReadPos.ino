#include <SCServo.h>

SCSCL sc;
int LEDpin = 13;

void setup()
{
	pinMode(LEDpin,OUTPUT);
	digitalWrite(LEDpin, HIGH);
	Serial1.begin(1000000);
  Serial.begin(115200);
  sc.pSerial = &Serial1;
}

void loop()
{
	s16 pos = sc.ReadPos(1);
	if(pos!=-1)
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
