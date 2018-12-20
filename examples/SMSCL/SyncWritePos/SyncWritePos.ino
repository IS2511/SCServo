#include <SCServo.h>

SMSCL sm;

byte ID[2];
void setup()
{
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  ID[0] = 1;
  ID[1] = 2;
}

void loop()
{
  //指令:同步写指令, ID:1\2, 目标:0, 速度=500/s
  sm.SyncWritePos(ID, 2, 0, 0, 500);
  
  //行程=4095-0=4095, 加减速时间约=300ms(负载越大时间越长,不同舵机加减速度不同时间也不同), 总运行时间=8190+300=8490ms
  delay(8490);
  
  //指令:同步写指令, ID:1\2, 目标:4095, 速度=500/s
  sm.SyncWritePos(ID, 2, 4095, 0, 500);
  
  //行程=4095-0=4095, 加减速时间约=300ms(负载越大时间越长,不同舵机加减速度不同时间也不同), 总运行时间=8190+300=8490ms
  delay(8490);
}
