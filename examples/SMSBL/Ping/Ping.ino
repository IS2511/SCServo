#include <SCServo.h>

SMSBL sms;

int LEDpin = 13;
void setup()
{
  pinMode(LEDpin,OUTPUT);
  digitalWrite(LEDpin, HIGH);
	Serial1.begin(115200);
  Serial.begin(115200);
  sms.pSerial = &Serial1;
}

void loop()
{
  int ID = sms.Ping(1);
	if(ID!=-1)
  {
    digitalWrite(LEDpin, LOW);
    Serial.println(ID, DEC);
    delay(10);
   }
   else
   {
    digitalWrite(LEDpin, HIGH);
    delay(2000);
   }
}
