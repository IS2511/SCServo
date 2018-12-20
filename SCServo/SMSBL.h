/*
 * SMSBL.h
 * 飞特SMSBL系列串行舵机应用层程序
 * 日期: 2018.8.2
 * 作者: 谭雄乐
 */

#ifndef _SMSBL_H
#define _SMSBL_H

//波特率定义
#define		SMSBL_1M		0
#define		SMSBL_0_5M		1
#define		SMSBL_250K		2
#define		SMSBL_128K		3
#define		SMSBL_115200	4
#define		SMSBL_76800		5
#define		SMSBL_57600		6
#define		SMSBL_38400		7

//内存表定义
//-------EPROM(只读)--------
#define SMSBL_VERSION_L 0
#define SMSBL_VERSION_H 1
#define SMSBL_MODEL_L 3
#define SMSBL_MODEL_H 4

//-------EPROM(读写)--------
#define SMSBL_ID 5
#define SMSBL_BAUD_RATE 6
#define SMSBL_RETURN_DELAY_TIME 7
#define SMSBL_RETURN_LEVEL 8
#define SMSBL_MIN_ANGLE_LIMIT_L 9
#define SMSBL_MIN_ANGLE_LIMIT_H 10
#define SMSBL_MAX_ANGLE_LIMIT_L 11
#define SMSBL_MAX_ANGLE_LIMIT_H 12
#define SMSBL_LIMIT_TEMPERATURE 13
#define SMSBL_MAX_LIMIT_VOLTAGE 14
#define SMSBL_MIN_LIMIT_VOLTAGE 15
#define SMSBL_MAX_TORQUE_L 16
#define SMSBL_MAX_TORQUE_H 17
#define SMSBL_ALARM_LED 19
#define SMSBL_ALARM_SHUTDOWN 20
#define SMSBL_COMPLIANCE_P 21
#define SMSBL_COMPLIANCE_D 22
#define SMSBL_COMPLIANCE_I 23
#define SMSBL_PUNCH_L 24
#define SMSBL_PUNCH_H 25
#define SMSBL_CW_DEAD 26
#define SMSBL_CCW_DEAD 27
#define SMSBL_MAX_CURRENT_L 28
#define SMSBL_MAX_CURRENT_H 29
#define SMSBL_ANGLE_RESOLVING 30
#define SMSBL_OFS_L 31
#define SMSBL_OFS_H 32
#define SMSBL_MODE 33

//-------SRAM(读写)--------
#define SMSBL_TORQUE_ENABLE 40
#define SMSBL_ACC 41
#define SMSBL_GOAL_POSITION_L 42
#define SMSBL_GOAL_POSITION_H 43
#define SMSBL_GOAL_TIME_L 44
#define SMSBL_GOAL_TIME_H 45
#define SMSBL_GOAL_SPEED_L 46
#define SMSBL_GOAL_SPEED_H 47
#define SMSBL_LOCK 55

//-------SRAM(只读)--------
#define SMSBL_PRESENT_POSITION_L 56
#define SMSBL_PRESENT_POSITION_H 57
#define SMSBL_PRESENT_SPEED_L 58
#define SMSBL_PRESENT_SPEED_H 59
#define SMSBL_PRESENT_LOAD_L 60
#define SMSBL_PRESENT_LOAD_H 61
#define SMSBL_PRESENT_VOLTAGE 62
#define SMSBL_PRESENT_TEMPERATURE 63
#define SMSBL_REGISTERED_INSTRUCTION 64
#define SMSBL_MOVING 66
#define SMSBL_PRESENT_CURRENT_L 69
#define SMSBL_PRESENT_CURRENT_H 70

#include "SCSerail.h"

class SMSBL : public SCSerail
{
public:
	SMSBL();
	SMSBL(u8 End);
	SMSBL(u8 End, u8 Level);
	
	virtual int WritePosEx(u8 ID, s16 Position, u16 Speed, u8 ACC = 0);//普通写位置指令
	virtual int RegWritePosEx(u8 ID, s16 Position, u16 Speed, u8 ACC = 0);//异步写位置指令
	virtual void SyncWritePosEx(u8 ID[], u8 IDN, s16 Position, u16 Speed, u8 ACC = 0);//同步写位置指令	
	virtual int WriteSpe(u8 ID, s16 Speed, u8 ACC = 0);//恒速模式控制指令
	virtual int wheelMode(u8 ID);//恒速模式
	virtual int pwmMode(u8 ID);//PWM输出模式
	virtual int joinMode(u8 ID, u16 minAngle = 0, u16 maxAngle = 1023);//普通伺服模式, for smsbl, min-max angle not used
	virtual s16 ReadPos(u8 ID, u8 *Err = NULL);//读位置
	virtual int Recovery(u8 ID);//恢复舵机参数为默认值
	virtual int Reset(u8 ID);//复位舵机
	virtual int unLockEprom(u8 ID);//eprom解锁
	virtual int LockEprom(u8 ID);//eprom加锁
	virtual int WritePWM(u8 ID, s16 pwmOut);//PWM输出模式指令
	virtual int EnableTorque(u8 ID, u8 Enable);//扭力控制指令
	virtual void RegWriteAction();//执行异步写指令
	virtual int ReadLoad(u8 ID, u8 *Err = NULL);//读输出扭力
	virtual int ReadVoltage(u8 ID);//读电压
	virtual int ReadTemper(u8 ID);//读温度
	virtual int ReadSpeed(u8 ID, u8 *Err = NULL);
	virtual int ReadCurrent(u8 ID, u8 *Err = NULL);
	virtual int ReadMove(u8 ID);

	// return -1 if fail, >=0 if ok
	virtual int WritePunch(u8 ID,u16 new_punch);
	virtual int WriteP(u8 ID, u8 new_P);
	virtual int WriteI(u8 ID, u8 new_I);
	virtual int WriteD(u8 ID, u8 new_D);
	virtual int WriteMaxTorque(u8 ID, u16 new_torque);
	virtual int WriteOfs(u8 ID, s16 Ofs);//中位校准
	virtual int ReadPunch(u8 ID);
	virtual int ReadP(u8 ID);
	virtual int ReadI(u8 ID);
	virtual int ReadD(u8 ID);
	virtual int ReadMaxTorque(u8 ID);	
	virtual int ReadTorqueEnable(u8 ID);
	virtual int ReadOfs(u8 ID, u8 *Err = NULL);

private:
	int writePos(u8 ID, s16 Position, u16 Speed, u8 ACC, u8 Fun);
};

#endif