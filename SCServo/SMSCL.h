/*
 * SMSCL.h
 * 飞特SMSCL系列串行舵机接口
 * 日期: 2018.8.2
 * 作者: 谭雄乐
 */

#ifndef _SMSCL_H
#define _SMSCL_H


#define		SMSCL_1M			0
#define		SMSCL_0_5M			1
#define		SMSCL_250K			2
#define		SMSCL_128K			3
#define		SMSCL_115200		4
#define		SMSCL_76800			5
#define		SMSCL_57600			6
#define		SMSCL_38400			7

//内存表定义
//-------EPROM(只读)--------
#define SMSCL_VERSION_L 3
#define SMSCL_VERSION_H 4

//-------EPROM(读写)--------
#define SMSCL_ID 5
#define SMSCL_BAUD_RATE 6
#define SMSCL_RETURN_DELAY_TIME 7
#define SMSCL_RETURN_LEVEL 8
#define SMSCL_MIN_ANGLE_LIMIT_L 9
#define SMSCL_MIN_ANGLE_LIMIT_H 10
#define SMSCL_MAX_ANGLE_LIMIT_L 11
#define SMSCL_MAX_ANGLE_LIMIT_H 12
#define SMSCL_LIMIT_TEMPERATURE 13
#define SMSCL_MAX_LIMIT_VOLTAGE 14
#define SMSCL_MIN_LIMIT_VOLTAGE 15
#define SMSCL_MAX_TORQUE_L 16
#define SMSCL_MAX_TORQUE_H 17
#define SMSCL_ALARM_LED 19
#define SMSCL_ALARM_SHUTDOWN 20
#define SMSCL_COMPLIANCE_P 21
#define SMSCL_COMPLIANCE_D 22
#define SMSCL_COMPLIANCE_I 23
#define SMSCL_PUNCH_L 24
#define SMSCL_PUNCH_H 25
#define SMSCL_CW_DEAD 26
#define SMSCL_CCW_DEAD 27
#define SMSCL_OFS_L 33
#define SMSCL_OFS_H 34
#define SMSCL_MODE 35
#define SMSCL_MAX_CURRENT_L 36
#define SMSCL_MAX_CURRENT_H 37	

//-------SRAM(读写)--------
#define SMSCL_TORQUE_ENABLE 40
#define SMSCL_GOAL_POSITION_L 42
#define SMSCL_GOAL_POSITION_H 43
#define SMSCL_GOAL_TIME_L 44
#define SMSCL_GOAL_TIME_H 45
#define SMSCL_GOAL_SPEED_L 46
#define SMSCL_GOAL_SPEED_H 47
#define SMSCL_LOCK 48

//-------SRAM(只读)--------
#define SMSCL_PRESENT_POSITION_L 56
#define SMSCL_PRESENT_POSITION_H 57
#define SMSCL_PRESENT_SPEED_L 58
#define SMSCL_PRESENT_SPEED_H 59
#define SMSCL_PRESENT_LOAD_L 60
#define SMSCL_PRESENT_LOAD_H 61
#define SMSCL_PRESENT_VOLTAGE 62
#define SMSCL_PRESENT_TEMPERATURE 63
#define SMSCL_REGISTERED_INSTRUCTION 64
#define SMSCL_MOVING 66
#define SMSCL_PRESENT_CURRENT_L 69
#define SMSCL_PRESENT_CURRENT_H 70

#include "SCSerail.h"

class SMSCL : public SCSerail
{
public:
	SMSCL();
	SMSCL(u8 End);
	SMSCL(u8 End, u8 Level);
	
	virtual int WritePos(u8 ID, s16 Position, u16 Time, u16 Speed = 0);//普通写位置指令
	virtual int RegWritePos(u8 ID, s16 Position, u16 Time, u16 Speed = 0);//异步写位置指令
	virtual void SyncWritePos(u8 ID[], u8 IDN, s16 Position, u16 Time, u16 Speed = 0);//同步写位置指令
	virtual int WriteSpe(u8 ID, s16 Speed, u8 ACC = 0);//恒速模式控制指令
	virtual int pwmMode(u8 ID);//PWM输出模式
	virtual int wheelMode(u8 ID);//恒速模式
	virtual int joinMode(u8 ID, u16 minAngle = 0, u16 maxAngle = 1023);//普通伺服模式	
	virtual s16 ReadPos(u8 ID, u8 *Err = NULL);//读位置 , Err not used
	virtual int Recovery(u8 ID);//恢复舵机参数为默认值
	virtual int Reset(u8 ID);//复位舵机
	virtual int unLockEprom(u8 ID);//eprom解锁
	virtual int LockEprom(u8 ID);//eprom加锁
	virtual int WritePWM(u8 ID, s16 pwmOut);//PWM输出模式指令
	virtual int EnableTorque(u8 ID, u8 Enable);//扭力控制指令
	virtual void RegWriteAction();//执行异步写指令
	virtual int ReadLoad(u8 ID);//读输出扭力
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
	int writePos(u8 ID, s16 Position, u16 Time, u16 Speed, u8 Fun);
};

#endif