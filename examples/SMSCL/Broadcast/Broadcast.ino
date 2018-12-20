#include <SCServo.h>

SMSCL sm;

void setup()
{
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
  delay(500);
}

void loop()
{
  //指令:写指令, ID:广播ID, 目标:0, 速度=500/s
  sm.WritePos(0xfe,0,0,500);
  
  //行程=4095-0=4095, 加减速时间约=300ms(负载越大时间越长,不同舵机加减速度不同时间也不同), 总运行时间=8190+300=8490ms
  delay(8490);
  
  //指令:广播写指令, ID:广播ID, 目标:4095, 速度=500/s
  sm.WritePos(0xfe,4095,0,500);
  
  //行程=4095-0=4095, 加减速时间约=300ms(负载越大时间越长,不同舵机加减速度不同时间也不同), 总运行时间=8190+300=8490ms
  delay(8490);
}
