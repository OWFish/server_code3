#ifndef _ACTOR_EX_H_
#define _ACTOR_EX_H_

/*
* actor�����õ�һЩ�����Ķ��壬��������
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
	size_t		pos_;		//׷�ӱ������ݵ�ǰ��datapacket���е����ݳ���
public:
	//�ύ���ݰ�
	void flush();
	//�������ݰ�
	void rollBack();

	template<typename T>
	inline ActorPacket& operator << (const T value)
	{
		*packet_ << value;
		return *this;
	}
};

#endif

