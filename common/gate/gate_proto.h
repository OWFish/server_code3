#ifndef _GATE_PROTO_H_
#define _GATE_PROTO_H_

/********************************************************
*   网关与内部服务器通信协议以及基础数据结构定义
**********************************************************/

#define	GW_OPEN					1				//打开新用户会话，当客户端连接到网关时网关向服务器发送此消息
#define	GW_CLOSE				2				//关闭用户会话，当客户端与网关的链接断开时网关向服务器发送此消息
//#define	GW_CHECKSERVER			3				//网关回应服务器的心跳包消息
//#define	GW_CHECKCLIENT			4				//服务器向网关发送心跳包消息
#define	GW_DATA					5				//网关转发用户通信数据到服务器，服务器向网关发送用户通信数据也使用此消息
#define GW_CHANNEL				6				//同步频道的信息
#define	GW_TEST					1026			// 用于测试网关和服务器之间的链路是否丢包
#define GW_CMD					1027

enum
{
    ccAddUser = 1,	// 增加用户
    ccDelUser = 2,	// 删除用户
    ccBroadCast = 3, // 广播
};


#endif


