/*
同步写例子在SMS60中测试通过，如果测试其它型号SMS系列舵机请更改合适的位置、速度与延时参数。
*/

#include <SCServo.h>
SMSCL sm;

byte ID[2];
s16 Position[2];
u16 Speed[2];
byte ACC[2];

void setup()
{
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  delay(1000);
  ID[0] = 1;
  ID[1] = 2;
  Speed[0] = 2250;
  Speed[1] = 2250;
  ACC[0] = 50;
  ACC[1] = 50;
}

void loop()
{
  Position[0] = 4095;
  Position[1] = 4095;
  sm.SyncWritePosEx(ID, 2, Position, Speed, ACC);//舵机(ID1/ID2)以最高速度V=2250步/秒，加速度A=50(50*100步/秒^2)，运行至P1=4095位置
  delay(2270);//((P1-P0)/V)*1000+(V/(A*100))*1000

  Position[0] = 0;
  Position[1] = 0;
  sm.SyncWritePosEx(ID, 2, Position, Speed, ACC);//舵机(ID1/ID2)以最高速度V=2250步/秒，加速度A=50(100*100步/秒^2)，运行至P0=0位置
  delay(2270);//((P1-P0)/V)*1000+(V/(A*100))*1000
}
