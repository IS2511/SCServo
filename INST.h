/*
 * INST.h
 * 飞特串行舵机协议指令定义
 * 日期: 2018.08.2
 * 作者: 谭雄乐
 */

#ifndef _INST_H
#define _INST_H

typedef		char			s8;
typedef		unsigned char	u8;	
typedef		unsigned short	u16;	
typedef		short			s16;
typedef		unsigned long	u32;	
typedef		long			s32;

#define INST_PING 0x01
#define INST_READ 0x02
#define INST_WRITE 0x03
#define INST_REG_WRITE 0x04
#define INST_ACTION 0x05
#define INST_RECOVER 0x06
#define INST_SYNC_WRITE 0x83
#define INST_RESET 0x0a

#endif