#include <SCServo.h>

SCSCL sc;

void setup()
{
  Serial1.begin(1000000);
  sc.pSerial = &Serial1;
  sc.WritePos(0xfe, 0, 1000);
  delay(1000);        
}

void loop()
{
  sc.WritePos(0xfe,300,0,500);//指令:写指令, ID:广播ID, 目标:300, 速度=500/s
  delay(1050);//行程=800-300=500, 加减速时间约=50ms(负载越大时间越长), 总运行时间=1000+50=1050ms
  sc.WritePos(0xfe,800,0,500);//指令:广播写指令, ID:广播ID, 目标:300, 速度=500/s
  delay(1050);//行程=800-300=500, 加减速约=50ms(负载越大时间越长), 总运行时间=1000+50=1050ms
}
