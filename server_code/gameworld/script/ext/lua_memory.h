#ifndef _LUA_MEMORY_H_
#define _LUA_MEMORY_H_

/************************************************************************
*						    �ű��ڴ������
*                 Ŀǰ��ʵ�ַ�ʽ�ǲ��õ����Ķѽ����ڴ����
************************************************************************/

namespace luamemory
{
	void Initialize();
	void Realease();
	//LUA������ڴ����뺯��
	void* luaAlloc(void *ud, void* ptr, size_t osize, size_t newsize);
	void GC();
	void printState();
}

#endif

