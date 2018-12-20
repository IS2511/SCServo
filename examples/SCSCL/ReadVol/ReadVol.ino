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
  int vol = sc.ReadVoltage(1);
	if(vol!=-1)
  {
    digitalWrite(LEDpin, LOW);
    Serial.println(vol, DEC);
    delay(10);
   }
   else
   {
    digitalWrite(LEDpin, HIGH);
    delay(2000);
   }
}
