/*
 * SCSCL.cpp
 * 飞特SCSCL系列串行舵机应用层程序
 * 日期: 2018.8.2
 * 作者: 谭雄乐
 */

#include "SCServo.h"

SCSCL::SCSCL()
{
	End = 1;
}

SCSCL::SCSCL(u8 End):SCSerail(End)
{
}

SCSCL::SCSCL(u8 End, u8 Level):SCSerail(End, Level)
{
}

int SCSCL::EnableTorque(u8 ID, u8 Enable)
{
	return writeByte(ID, SCSCL_TORQUE_ENABLE, Enable);
}


int SCSCL::ReadTorqueEnable(u8 ID)
{
	return readByte(ID, SCSCL_TORQUE_ENABLE);
}


int SCSCL::writePos(u8 ID, u16 Position, u16 Time, u16 Speed, u8 Fun)
{
	flushSCS();
	u8 buf[6];
	Host2SCS(buf+0, buf+1, Position);
	Host2SCS(buf+2, buf+3, Time);
	Host2SCS(buf+4, buf+5, Speed);
	writeBuf(ID, SCSCL_GOAL_POSITION_L, buf, 6, Fun);
	return Ack(ID);
}

//写位置指令
//舵机ID，Position位置，执行时间Time，执行速度Speed
int SCSCL::WritePos(u8 ID, s16 Position, u16 Time, u16 Speed)
{
	return writePos(ID, Position, Time, Speed, INST_WRITE);
}

//异步写位置指令
//舵机ID，Position位置，执行时间Time，执行速度Speed
int SCSCL::RegWritePos(u8 ID, s16 Position, u16 Time, u16 Speed)
{
	return writePos(ID, Position, Time, Speed, INST_REG_WRITE);
}

void SCSCL::RegWriteAction()
{
	writeBuf(0xfe, 0, NULL, 0, INST_ACTION);
}

//写位置指令
//舵机ID[]数组，IDN数组长度，Position位置，执行时间Time，执行速度Speed
void SCSCL::SyncWritePos(u8 ID[], u8 IDN, s16 Position, u16 Time, u16 Speed)
{
	u8 buf[6];
	Host2SCS(buf+0, buf+1, Position);
	Host2SCS(buf+2, buf+3, Time);
	Host2SCS(buf+4, buf+5, Speed);
	snycWrite(ID, IDN, SCSCL_GOAL_POSITION_L, buf, 6);
}

void SCSCL::SyncWritePos2(u8 ID[], u8 IDN, u16 Position[], u16 Time, u16 Speed)
{
    //u8* offbuf[IDN];
    u8 offbuf[IDN][6];
    for(u8 i = 0; i<IDN; i++){
        u8 buf[6];
        Host2SCS(buf+0, buf+1, Position[i]);
        Host2SCS(buf+2, buf+3, Time);
        Host2SCS(buf+4, buf+5, Speed);
        //offbuf[i] = buf;
        memcpy(offbuf[i], buf, 6);
        //writeSCS(offbuf[i], 6);
    }
    snycWrite(ID, IDN, SCSCL_GOAL_POSITION_L, (u8*)offbuf, 6);
}

//读位置，超时返回-1
s16 SCSCL::ReadPos(u8 ID, u8 *Err)
{
	s16 Pos = readWord(ID, SCSCL_PRESENT_POSITION_L);
	if(Pos==-1){
		if(Err){
			*Err = 1;
		}
		return -1;
	}else{
		if(Err){
			*Err = 0;
		}
		return Pos;
	}
	//return readWord(ID, SCSCL_PRESENT_POSITION_L);
}

//PWM输出模式
int SCSCL::WritePWM(u8 ID, s16 pwmOut)
{
	if(pwmOut<0){
		pwmOut = -pwmOut;
		pwmOut |= (1<<10);
	}
	return writeWord(ID, SCSCL_GOAL_TIME_L, pwmOut);
}

//读输出扭力，超时返回-1
int SCSCL::ReadLoad(u8 ID)
{	
	return readWord(ID, SCSCL_PRESENT_LOAD_L);
}

//读电压，超时返回-1
int SCSCL::ReadVoltage(u8 ID)
{	
	return readByte(ID, SCSCL_PRESENT_VOLTAGE);
}

//读温度，超时返回-1
int SCSCL::ReadTemper(u8 ID)
{	
	return readByte(ID, SCSCL_PRESENT_TEMPERATURE);
}

int SCSCL::pwmMode(u8 ID)
{
	u8 bBuf[4];
	bBuf[0] = 0;
	bBuf[1] = 0;
	bBuf[2] = 0;
	bBuf[3] = 0;
	return genWrite(ID, SCSCL_MIN_ANGLE_LIMIT_L, bBuf, 4);	
}

int SCSCL::joinMode(u8 ID, u16 minAngle, u16 maxAngle)
{
	u8 bBuf[4];
	Host2SCS(bBuf, bBuf+1, minAngle);
	Host2SCS(bBuf+2, bBuf+3, maxAngle);
	return genWrite(ID, SCSCL_MIN_ANGLE_LIMIT_L, bBuf, 4);
}

//复位舵机参数为默认值
int SCSCL::Recovery(u8 ID)
{
	flushSCS();
	writeBuf(ID, 0, NULL, 0, INST_RECOVER);
	return Ack(ID);
}

//复位舵机
int SCSCL::Reset(u8 ID)
{
	flushSCS();
	writeBuf(ID, 0, NULL, 0, INST_RESET);
	return Ack(ID);
}

int SCSCL::unLockEprom(u8 ID)
{
	return writeByte(ID, SCSCL_LOCK, 0);//打开EPROM保存功能
}

int SCSCL::LockEprom(u8 ID)
{
	return writeByte(ID, SCSCL_LOCK, 1);//关闭EPROM保存功能
}

int SCSCL::WritePunch(u8 ID, u16 new_punch)          
{
	return writeWord(ID, SCSCL_PUNCH_L, new_punch);	
}

int SCSCL::WriteP(u8 ID, u8 new_P)   
{
    return writeByte(ID,SCSCL_COMPLIANCE_P,new_P);
}               

int SCSCL::WriteI(u8 ID, u8 new_I)   
{
    return writeByte(ID, SCSCL_COMPLIANCE_I, new_I);
}               

int SCSCL::WriteD(u8 ID, u8 new_D)          
{
    return writeByte(ID, SCSCL_COMPLIANCE_D, new_D);
}               

int SCSCL::WriteMaxTorque(u8 ID, u16 new_torque)     
{
	return writeWord(ID, SCSCL_MAX_TORQUE_L, new_torque);	
}

int SCSCL::ReadPunch(u8 ID)       
{ 
	return readWord(ID, SCSCL_PUNCH_L);
}

int SCSCL::ReadP(u8 ID)                   
{
	return readByte(ID,SCSCL_COMPLIANCE_P);
}

int SCSCL::ReadI(u8 ID)
{
	return readByte(ID, SCSCL_COMPLIANCE_I);
}

int SCSCL::ReadD(u8 ID)                  
{
	return readByte(ID, SCSCL_COMPLIANCE_D);
}

int SCSCL::ReadMaxTorque(u8 ID)    
{ 
	return readWord(ID, SCSCL_MAX_TORQUE_L);
}

int SCSCL::ReadSpeed(u8 ID, u8 *Err)
{
	s16 Speed = readWord(ID, SCSCL_PRESENT_SPEED_L);
	if(Speed==-1){
		if(Err){
			*Err = 1;
		}
		return -1;
	}
	if(Err){
		*Err = 0;
		if(Speed&(1<<15)){
			Speed = -(Speed&~(1<<15));
		}
	}
	return Speed;
}

int SCSCL::ReadMove(u8 ID)
{
	return readByte(ID, SCSCL_MOVING);
}