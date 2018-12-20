#include <SCServo.h>

SCSCL sc;

byte ID[2];
void setup()
{
  Serial1.begin(1000000);
  sc.pSerial = &Serial1;
  ID[0] = 1;
  ID[1] = 2;
}

void loop()
{
  sc.SyncWritePos(ID, 2, 300, 0, 500);//指令:同步写指令, ID:1\2, 目标:300, 速度=500/s
  delay(1050);//行程=800-300=500, 加减速时间约=50ms(负载越大时间越长), 总运行时间=1000+50=1050ms
  sc.SyncWritePos(ID, 2, 800, 0, 500);//指令:同步写指令, ID:1\2, 目标:800, 速度=500/s
  delay(1050);//行程=800-300=500, 加减速时间约=50ms(负载越大时间越长), 总运行时间=1000+50=1050ms
}
