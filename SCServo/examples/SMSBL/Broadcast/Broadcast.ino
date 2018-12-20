#include <SCServo.h>

SMSBL sm;

void setup()
{
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  sm.WritePosEx(0xfe, 0, 50);
  delay(2000);
}

void loop()
{
  sm.WritePosEx(0xfe, 4095, 50, 5);//SM舵机(ID0)以最高50速度(50*0.737=36rpm)，5(5*0.878=4.93度/秒^2)加速度，运行至4095位置
  delay(6000); 
  sm.WritePosEx(0xfe, 0, 50, 5);//SM舵机(ID0)以最高50速度(50*0.737=36rpm)，5(5*0.878=4.93度/秒^2)加速度，运行至0位置
  delay(6000);
}
