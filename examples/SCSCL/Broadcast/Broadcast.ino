/*
广播写例子在SCS15中测试通过，如果测试其它型号SCS系列舵机请更改合适的位置、速度与延时参数。
*/

#include <SCServo.h>

SCSCL sc;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(1000000);
  sc.pSerial = &Serial1;
  delay(1000);
}

void loop()
{
  sc.WritePos(0xfe, 1000, 0, 1500);//舵机(ID1)以最高速度V=1500步/秒,运行至P1=1000
  delay(754);//[(P1-P0)/V]*1000+100
  
  sc.WritePos(0xfe, 20, 0, 1500);//舵机(ID1)以最高V=1500步/秒,运行至P1=20
  delay(754);//[(P1-P0)/V]*1000+100
}
