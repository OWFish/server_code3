#ifndef _INTERNAL_MESSAGE_H_
#define _INTERNAL_MESSAGE_H_

/************************************************************************/
/* 程序内部通信消息结构                                                 */
/************************************************************************/

struct APPINTERNALMSG
{
	unsigned int msg_;	//消息号
	size_t	p1_;//消息参数1
	size_t	p2_;//消息参数2
	size_t	p3_;//消息参数3
	size_t	p4_;//消息参数4
};

#endif

