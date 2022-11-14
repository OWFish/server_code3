#ifndef _ACTOR_EX_H_
#define _ACTOR_EX_H_

/*
* actor类里用的一些辅助的定义，放在这里
*/
#ifdef _MSC_VER
#define NetDataStruct(s,p,str) __pragma(pack(push, 1))\
static struct Data\
{\
	uint8_t sid_;\
	uint8_t pid_;\
	str;\
	Data(): sid_(s), pid_(p) {}\
} data;\
__pragma(pack(pop))
#else
#define NetDataStruct(s,p,str) _Pragma("pack(push, 1)")\
static struct Data\
{\
	uint8_t sid_;\
	uint8_t pid_;\
	str;\
	Data(): sid_(s), pid_(p) {}\
} data;\
_Pragma("pack(pop)")
#endif

struct ActorPacket
{
	DataPacket* packet_;
	size_t		pos_;		//追加本次数据的前，datapacket已有的数据长度
public:
	//提交数据包
	void flush();
	//撤销数据包
	void rollBack();

	template<typename T>
	inline ActorPacket& operator << (const T value)
	{
		*packet_ << value;
		return *this;
	}
};

#endif

