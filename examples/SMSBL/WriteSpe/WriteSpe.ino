/*
恒速模式例子在SMS40BL中测试通过，舵机出厂速度单位V=0为停止状态
*/

#include <SCServo.h>

SMSBL sm;

void setup()
{
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  delay(1000);
  sm.WheelMode(1);//恒速模式
}

void loop()
{
  sm.WriteSpe(1, 80, 100);//舵机(ID1)以最高速度V=80(50*80步/秒)，加速度A=100(100*100步/秒^2)，旋转
  delay(2000);
  sm.WriteSpe(1, 0, 100);//舵机(ID1)以加速度A=100(100*100步/秒^2)，停止旋转(V=0)
  delay(2000);
  sm.WriteSpe(1, -80, 100);//舵机(ID1)以最高速度V=-80(-50*80步/秒)，加速度A=100(100*100步/秒^2)，反向旋转
  delay(2000);
  sm.WriteSpe(1, 0, 100);//舵机(ID1)以加速度A=100(100*100步/秒^2)，停止旋转(V=0)
  delay(2000);
}
