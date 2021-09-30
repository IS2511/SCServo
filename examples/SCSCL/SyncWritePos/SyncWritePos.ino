/*
同步写例子在SCS15中测试通过，如果测试其它型号SCS系列舵机请更改合适的位置、速度与延时参数。
*/

#include <SCServo.h>

SCSCL sc;

byte ID[2];
u16 Position[2];
u16 Speed[2];

void setup()
{
  Serial1.begin(1000000);
  sc.pSerial = &Serial1;
  delay(1000);
  ID[0] = 1;
  ID[1] = 2;
}

void loop()
{
  Position[0] = 1000;
  Position[1] = 1000;
  Speed[0] = 1500;
  Speed[1] = 1500;
  sc.SyncWritePos(ID, 2, Position, 0, Speed);//舵机((ID1/ID2))以最高速度V=1500步/秒,运行至P1=1000
  delay(754);//[(P1-P0)/V]*1000+100

  Position[0] = 20;
  Position[1] = 20;
  Speed[0] = 1500;
  Speed[1] = 1500;
  sc.SyncWritePos(ID, 2, Position, 0, Speed);//舵机((ID1/ID2))以最高速度V=1500步/秒,运行至P1=20
  delay(754);//[(P1-P0)/V]*1000+100
}
