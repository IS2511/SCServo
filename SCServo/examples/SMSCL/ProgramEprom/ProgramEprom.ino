#include <SCServo.h>

int LEDpin = 13;
SMSCL sm;

void setup()
{
  pinMode(LEDpin, OUTPUT);
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  digitalWrite(LEDpin, LOW);
  sm.writeByte(0xfe, SMSCL_LOCK, 0);//打开EPROM保存功能
  sm.writeByte(0xfe, SMSCL_ID, 1);//ID
  delay(50);
  sm.writeWord(0xfe, SMSCL_MIN_ANGLE_LIMIT_L, 0);
  delay(50);
  sm.writeWord(0xfe, SMSCL_MAX_ANGLE_LIMIT_L, 0);
  delay(50);
  sm.writeWord(0xfe, SMSCL_MAX_TORQUE_L, 1000);
  delay(50);
  sm.writeByte(0xfe, SMSCL_BAUD_RATE, SMSCL_115200);
  delay(50);
  sm.writeByte(0xfe, SMSCL_LOCK, 1);//关闭EPROM保存功能
  digitalWrite(LEDpin, HIGH);
}

void loop()
{

}
