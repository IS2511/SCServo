#include <SCServo.h>

SCSCL sc;

byte ID[2];
s16 Position[2];
void setup()
{
  Serial1.begin(1000000);
  sc.pSerial = &Serial1;
  ID[0] = 1;
  ID[1] = 2;
}

void loop()
{
  Position[0] = 300;
  Position[1] = 400;
  sc.SyncWritePos2(ID, 2, Position, 0, 500);//指令:同步写指令, ID:1\2, 目标:300\400, 速度=500/s
  delay(1050);//行程=800-300=500, 加减速约=50ms(负载越大时间越长), 总运行时间=1000+50=1050ms
  Position[0] = 700;
  Position[1] = 800;
  sc.SyncWritePos(ID, 2, Position, 0, 500);//指令:同步写指令, ID:1\2, 目标:700\800, 速度=500/s
  delay(1050);//行程=800-300=500, 加减速约=50ms(负载越大时间越长), 总运行时间=1000+50=1050ms
}
