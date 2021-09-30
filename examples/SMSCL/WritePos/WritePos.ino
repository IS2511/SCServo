/*
普通写例子在SMS60中测试通过，如果测试其它型号SMS系列舵机请更改合适的位置、速度与延时参数。
*/

#include <SCServo.h>

SMSCL sm;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  delay(1000);
}

void loop()
{
  sm.WritePosEx(1, 4095, 2250, 50);//舵机(ID1)以最高速度V=2250步/秒，加速度A=50(50*100步/秒^2)，运行至P1=4095位置
  delay(2270);//[(P1-P0)/V]*1000+[V/(A*100)]*1000

  sm.WritePosEx(1, 0, 2250, 50);//舵机(ID1)以最高速度V=2250步/秒，加速度A=50(50*100步/秒^2)，运行至P0=0位置
  delay(2270);//[(P1-P0)/V]*1000+[V/(A*100)]*1000
}