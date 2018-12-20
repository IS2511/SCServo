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
  int T = sm.ReadTemper(1);
	if(T!=-1)
	{
    digitalWrite(LEDpin, LOW);
    Serial.println(T, DEC);
    delay(10);
  }
  else
  {
    digitalWrite(LEDpin, HIGH);
    delay(2000);    
  }
}
