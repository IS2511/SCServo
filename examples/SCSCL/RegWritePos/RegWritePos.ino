#include <SCServo.h>

SCSCL sm;

void setup()
{
  Serial1.begin(1000000);
  sm.pSerial = &Serial1;
}

void loop()
{
  sm.RegWritePos(1, 300, 0, 500);//指令:异步写指令, ID:1, 目标:300, 速度=500/s
  sm.RegWritePos(2, 300, 0, 500);//指令:异步写指令, ID:2, 目标:300, 速度=500/s
  sm.RegWriteAction();//执行异步写指令
  delay(1050);//行程=800-300=500, 加减速时间约=50ms(负载越大时间越长), 总运行时间=1000+50=1050ms
  
  sm.RegWritePos(1, 0, 0, 500);//指令:异步写指令, ID:1, 目标:800, 速度=500/s
  sm.RegWritePos(2, 0, 0, 500);//指令:异步写指令, ID:2, 目标:800, 速度=500/s
  sm.RegWriteAction();//执行异步写指令
  delay(1050);//行程=800-300=500, 加减速时间约=50ms(负载越大时间越长), 总运行时间=1000+50=1050ms
}
