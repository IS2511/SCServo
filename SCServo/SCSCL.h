/*
 * SCSCL.h
 * 飞特SCSCL系列串行舵机应用层程序
 * 日期: 2018.8.2
 * 作者: 谭雄乐
 */

#ifndef _SCSCL_H
#define _SCSCL_H


#define		SCSCL_1M		0
#define		SCSCL_0_5M		1
#define		SCSCL_250K		2
#define		SCSCL_128K		3
#define		SCSCL_115200		4
#define		SCSCL_76800		5
#define		SCSCL_57600		6
#define		SCSCL_38400		7

//内存表定义
//-------EPROM(只读)--------
#define SCSCL_VERSION_L 3
#define SCSCL_VERSION_H 4

//-------EPROM(读写)--------
#define SCSCL_ID 5
#define SCSCL_BAUD_RATE 6
#define SCSCL_RETURN_DELAY_TIME 7
#define SCSCL_RETURN_LEVEL 8
#define SCSCL_MIN_ANGLE_LIMIT_L 9
#define SCSCL_MIN_ANGLE_LIMIT_H 10
#define SCSCL_MAX_ANGLE_LIMIT_L 11
#define SCSCL_MAX_ANGLE_LIMIT_H 12
#define SCSCL_LIMIT_TEMPERATURE 13
#define SCSCL_MAX_LIMIT_VOLTAGE 14
#define SCSCL_MIN_LIMIT_VOLTAGE 15
#define SCSCL_MAX_TORQUE_L 16
#define SCSCL_MAX_TORQUE_H 17
#define SCSCL_ALARM_LED 19
#define SCSCL_ALARM_SHUTDOWN 20
#define SCSCL_COMPLIANCE_P 21
#define SCSCL_COMPLIANCE_D 22
#define SCSCL_COMPLIANCE_I 23
#define SCSCL_PUNCH_L 24
#define SCSCL_PUNCH_H 25
#define SCSCL_CW_DEAD 26
#define SCSCL_CCW_DEAD 27
#define SCSCL_OFS_L 33
#define SCSCL_OFS_H 34
#define SCSCL_MODE 35
#define SCSCL_MAX_CURRENT_L 36
#define SCSCL_MAX_CURRENT_H 37	

//-------SRAM(读写)--------
#define SCSCL_TORQUE_ENABLE 40
#define SCSCL_GOAL_POSITION_L 42
#define SCSCL_GOAL_POSITION_H 43
#define SCSCL_GOAL_TIME_L 44
#define SCSCL_GOAL_TIME_H 45
#define SCSCL_GOAL_SPEED_L 46
#define SCSCL_GOAL_SPEED_H 47
#define SCSCL_LOCK 48

//-------SRAM(只读)--------
#define SCSCL_PRESENT_POSITION_L 56
#define SCSCL_PRESENT_POSITION_H 57
#define SCSCL_PRESENT_SPEED_L 58
#define SCSCL_PRESENT_SPEED_H 59
#define SCSCL_PRESENT_LOAD_L 60
#define SCSCL_PRESENT_LOAD_H 61
#define SCSCL_PRESENT_VOLTAGE 62
#define SCSCL_PRESENT_TEMPERATURE 63
#define SCSCL_REGISTERED_INSTRUCTION 64
#define SCSCL_MOVING 66
#define SCSCL_PRESENT_CURRENT_L 69
#define SCSCL_PRESENT_CURRENT_H 70

#include "SCSerail.h"

class SCSCL : public SCSerail
{
public:
	SCSCL();
	SCSCL(u8 End);
	SCSCL(u8 End, u8 Level);
	virtual int WritePos(u8 ID, s16 Position, u16 Time, u16 Speed = 0);//普通写位置指令
	virtual int RegWritePos(u8 ID, s16 Position, u16 Time, u16 Speed = 0);//异步写位置指令
	virtual void SyncWritePos(u8 ID[], u8 IDN, s16 Position, u16 Time, u16 Speed = 0);//同步写位置指令(所有舵机位置为Position)
	virtual void SyncWritePos2(u8 ID[], u8 IDN, u16 Position[], u16 Time, u16 Speed = 0);//同步写位置指令(每个舵机位置通过Position[]指令)
	virtual int pwmMode(u8 ID);//PWM输出模式
	virtual int joinMode(u8 ID, u16 minAngle = 0, u16 maxAngle = 1023);//普通伺服模式	
	virtual s16 ReadPos(u8 ID, u8 *Err = NULL);//读位置 , Err not used
	virtual int Recovery(u8 ID);//复位舵机参数为默认值
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
	virtual int ReadMove(u8 ID);

	virtual int WritePunch(u8 ID,u16 new_punch);
	virtual int WriteP(u8 ID, u8 new_P);
	virtual int WriteI(u8 ID, u8 new_I);
	virtual int WriteD(u8 ID, u8 new_D);
	virtual int WriteMaxTorque(u8 ID, u16 new_torque);
	virtual int ReadPunch(u8 ID);
	virtual int ReadP(u8 ID);
	virtual int ReadI(u8 ID);
	virtual int ReadD(u8 ID);
	virtual int ReadMaxTorque(u8 ID);
	virtual int ReadTorqueEnable(u8 ID);
		
private:
	int writePos(u8 ID, u16 Position, u16 Time, u16 Speed, u8 Fun);
};

#endif