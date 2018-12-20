#include <SCServo.h>

int LEDpin = 13;
SMSBL sm;

void setup()
{
  pinMode(LEDpin, OUTPUT);
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  digitalWrite(LEDpin, LOW);
  sm.writeByte(0xfe, SMSBL_LOCK, 0);//打开EPROM保存功能
  sm.writeByte(0xfe, SMSBL_ID, 1);//ID
  delay(50);
  sm.writeWord(0xfe, SMSBL_MIN_ANGLE_LIMIT_L, 0);
  delay(50);
  sm.writeWord(0xfe, SMSBL_MAX_ANGLE_LIMIT_L, 0);
  delay(50);
  sm.writeByte(0xfe, SMSBL_RETURN_DELAY_TIME, 250);//返回延时500us
  delay(50);
  sm.writeByte(0xfe, SMSBL_BAUD_RATE, SMSBL_115200);//波特率115200
  delay(50);
  sm.writeByte(0xfe, SMSBL_LOCK, 1);//关闭EPROM保存功能
  digitalWrite(LEDpin, HIGH);
}

void loop()
{

}
