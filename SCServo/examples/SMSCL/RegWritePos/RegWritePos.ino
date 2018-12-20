#include <SCServo.h>

SMSCL sm;

void setup()
{
  Serial1.begin(115200);
  sm.pSerial = &Serial1;
}

void loop()
{
  sm.RegWritePos(1, 0, 0, 500);//指令:异步写指令, ID:1, 目标:0, 速度=500/s
  sm.RegWritePos(2, 0, 0, 500);//指令:异步写指令, ID:2, 目标:0, 速度=500/s
  sm.RegWriteAction();//执行异步写指令
  
  //行程=4095-0=4095, 加减速调节时间约=300ms(负载越大时间越长,不同舵机加减速度不同时间也不同), 总运行时间=8190+300=8490ms
  delay(8490);
  
  sm.RegWritePos(1, 4095, 0, 500);//指令:异步写指令, ID:1, 目标:4095, 速度=500/s
  sm.RegWritePos(2, 4095, 0, 500);//指令:异步写指令, ID:2, 目标:4095, 速度=500/s
  sm.RegWriteAction();//执行异步写指令
  
  //行程=4095-0=4095, 加减速调节时间约=300ms(负载越大时间越长,不同舵机加减速度不同时间也不同), 总运行时间=8190+300=8490ms
  delay(8490);
}
