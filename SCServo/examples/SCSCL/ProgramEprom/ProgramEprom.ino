#include <SCServo.h>

int LEDpin = 13;
SCSCL sc;

void setup()
{
  pinMode(LEDpin, OUTPUT);
  Serial1.begin(1000000);
  sc.pSerial = &Serial1;
  digitalWrite(LEDpin, LOW);
  sc.writeByte(0xfe, SCSCL_LOCK, 0);//打开EPROM保存功能
  sc.writeByte(0xfe, SCSCL_ID, 0);//ID
  delay(50);
  sc.writeWord(0xfe, SCSCL_MIN_ANGLE_LIMIT_L, 300);
  delay(50);
  sc.writeWord(0xfe, SCSCL_MAX_ANGLE_LIMIT_L, 800);
  delay(50);
  sc.writeWord(0xfe, SCSCL_MAX_TORQUE_L, 1000);
  delay(50);
  sc.writeByte(0xfe, SCSCL_BAUD_RATE, SCSCL_1M);
  delay(50);
  sc.writeByte(0xfe, SCSCL_LOCK, 1);//关闭EPROM保存功能
  digitalWrite(LEDpin, HIGH);
}

void loop()
{

}
