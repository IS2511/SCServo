/*
 * SMSCL.cpp
 * 飞特SMSCL系列串行舵机接口
 * 日期: 2017.11.21
 * 作者: 谭雄乐
 */



#include "SCServo.h"

SMSCL::SMSCL()
{
	End = 0;
}

SMSCL::SMSCL(u8 End):SCSerail(End)
{
}

SMSCL::SMSCL(u8 End, u8 Level):SCSerail(End, Level)
{
}

int SMSCL::EnableTorque(u8 ID, u8 Enable)
{
	return writeByte(ID, SMSCL_TORQUE_ENABLE, Enable);
}

int SMSCL::ReadTorqueEnable(u8 ID)
{
	return readByte(ID, SMSCL_TORQUE_ENABLE);
}


int SMSCL::writePos(u8 ID, s16 Position, u16 Time, u16 Speed, u8 Fun)
{
	if(Position<0){
		Position = -Position;
		Position |= (1<<15);
	}
	flushSCS();
	u8 buf[6];
	Host2SCS(buf+0, buf+1, Position);
	Host2SCS(buf+2, buf+3, Time);
	Host2SCS(buf+4, buf+5, Speed);
	writeBuf(ID, SMSCL_GOAL_POSITION_L, buf, 6, Fun);
	return Ack(ID);
}

//写位置指令
//舵机ID，Position位置，执行时间Time，执行速度Speed
int SMSCL::WritePos(u8 ID, s16 Position, u16 Time, u16 Speed)
{
	return writePos(ID, Position, Time, Speed, INST_WRITE);
}

//异步写位置指令
//舵机ID，Position位置，执行时间Time，执行速度Speed
int SMSCL::RegWritePos(u8 ID, s16 Position, u16 Time, u16 Speed)
{
	return writePos(ID, Position, Time, Speed, INST_REG_WRITE);
}

void SMSCL::RegWriteAction()
{
	writeBuf(0xfe, 0, NULL, 0, INST_ACTION);
}

//写位置指令
//舵机ID[]数组，IDN数组长度，Position位置，执行时间Time，执行速度Speed
void SMSCL::SyncWritePos(u8 ID[], u8 IDN, s16 Position, u16 Time, u16 Speed)
{
	if(Position<0){
		Position = -Position;
		Position |= (1<<15);
	}
	u8 buf[6];
	Host2SCS(buf+0, buf+1, Position);
	Host2SCS(buf+2, buf+3, Time);
	Host2SCS(buf+4, buf+5, Speed);
	snycWrite(ID, IDN, SMSCL_GOAL_POSITION_L, buf, 6);
}

//读位置，超时返回Err=1
s16 SMSCL::ReadPos(u8 ID, u8 *Err)
{
	s16 curPos = readWord(ID, SMSCL_PRESENT_POSITION_L);
	if(curPos==-1){
		if(Err){
			*Err = 1;
		}
		return -1;
	}
	if(curPos&(1<<15)){
		curPos = -(curPos&~(1<<15));
	}
	if(Err){
		*Err = 0;
	}
	
	return curPos;
}

//恒速控制指令
int SMSCL::WriteSpe(u8 ID, s16 Speed, u8 ACC)
{
	if(Speed<0){
		Speed = -Speed;
		Speed |= (1<<15);
	}
	return writeWord(ID, SMSCL_GOAL_TIME_L, Speed);
}

//PWM输出模式
int SMSCL::WritePWM(u8 ID, s16 pwmOut)
{
	if(pwmOut<0){
		pwmOut = -pwmOut;
		pwmOut |= (1<<15);
	}
	return writeWord(ID, SMSCL_GOAL_SPEED_L, pwmOut);
}

//读输出扭力，超时返回-1
int SMSCL::ReadLoad(u8 ID)
{	
	return readWord(ID, SMSCL_PRESENT_LOAD_L);
}

//读电压，超时返回-1
int SMSCL::ReadVoltage(u8 ID)
{	
	return readByte(ID, SMSCL_PRESENT_VOLTAGE);
}

//读温度，超时返回-1
int SMSCL::ReadTemper(u8 ID)
{	
	return readByte(ID, SMSCL_PRESENT_TEMPERATURE);
}

int SMSCL::wheelMode(u8 ID)
{
	return writeByte(ID, SMSCL_MODE, 1);
}

int SMSCL::pwmMode(u8 ID)
{
	return writeByte(ID, SMSCL_MODE, 2);		
}

int SMSCL::joinMode(u8 ID, u16 minAngle, u16 maxAngle)
{
	return writeByte(ID, SMSCL_MODE, 0);
}

//恢复舵机参数为默认值
int SMSCL::Recovery(u8 ID)
{
	flushSCS();
	writeBuf(ID, 0, NULL, 0, INST_RECOVER);
	return Ack(ID);
}

//复位舵机
int SMSCL::Reset(u8 ID)
{
	flushSCS();
	writeBuf(ID, 0, NULL, 0, INST_RESET);
	return Ack(ID);
}


int SMSCL::WriteOfs(u8 ID, s16 Ofs)
{
	if(Ofs<0){
		Ofs = -Ofs;
		Ofs |= (1<<15);
	}
	return writeWord(ID, SMSCL_OFS_L, Ofs);	
}

int SMSCL::unLockEprom(u8 ID)
{
	return writeByte(ID, SMSCL_LOCK, 0);//打开EPROM保存功能
}

int SMSCL::LockEprom(u8 ID)
{
	return writeByte(ID, SMSCL_LOCK, 1);//关闭EPROM保存功能
}

int SMSCL::WritePunch(u8 ID, u16 new_punch)
{
	return writeWord(ID, SMSCL_PUNCH_L, new_punch);	
}

int SMSCL::WriteP(u8 ID, u8 new_P)
{
    return writeByte(ID, SMSCL_COMPLIANCE_P, new_P);
}               

int SMSCL::WriteI(u8 ID, u8 new_I)
{
    return writeByte(ID, SMSCL_COMPLIANCE_I, new_I);
}               

int SMSCL::WriteD(u8 ID, u8 new_D)    
{
    return writeByte(ID, SMSCL_COMPLIANCE_D, new_D);
}

int SMSCL::WriteMaxTorque(u8 ID, u16 new_torque)
{
	return writeWord(ID, SMSCL_MAX_TORQUE_L, new_torque);	
}

int SMSCL::ReadOfs(u8 ID, u8 *Err)
{
	s16 Ofs = readWord(ID, SMSCL_OFS_L);
	if(Ofs==-1){
		if(Err){
			*Err = 1;
		}
		return -1;
	}
	if(Err){
		*Err = 0;
		if(Ofs&(1<<15)){
			Ofs = -(Ofs&~(1<<15));
		}
	}
	return Ofs;
}

int SMSCL::ReadSpeed(u8 ID, u8 *Err)
{
	s16 Speed = readWord(ID, SMSCL_PRESENT_SPEED_L);
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

int SMSCL::ReadCurrent(u8 ID, u8 *Err)
{
	s16 Current = readWord(ID, SMSCL_PRESENT_CURRENT_L);
	if(Current==-1){
		if(Err){
			*Err = 1;
		}
		return -1;
	}
	if(Err){
		*Err = 0;
		if(Current&(1<<15)){
			Current = -(Current&~(1<<15));
		}
	}
	return Current;
}

int SMSCL::ReadMove(u8 ID)
{
	return readByte(ID, SMSCL_MOVING);
}

int SMSCL::ReadPunch(u8 ID)
{
	return readWord(ID, SMSCL_PUNCH_L);
}

int SMSCL::ReadP(u8 ID)
{
	return readByte(ID, SMSCL_COMPLIANCE_P);
}

int SMSCL::ReadI(u8 ID)
{
	return readByte(ID, SMSCL_COMPLIANCE_I);
}

int SMSCL::ReadD(u8 ID)
{
	return readByte(ID, SMSCL_COMPLIANCE_D);
}

int SMSCL::ReadMaxTorque(u8 ID)
{ 
	return readWord(ID, SMSCL_MAX_TORQUE_L);
}