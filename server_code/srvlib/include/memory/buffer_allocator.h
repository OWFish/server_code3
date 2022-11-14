#ifndef _MSG_ALLOCATOR_H_
#define	_MSG_ALLOCATOR_H_

#include "os_def.h"
#include "x_tick.h"
#include "base_allocator.hpp"
#include "x_lock.h"

class BaseAllocator;

using namespace tick64;
using namespace lock;

class BufferAllocator: public BaseAllocator
{

public:
	static const unsigned int SmallBufferSize	= 64;	//С���ڴ���С
	static const unsigned int MiddleBufferSize	= 256;	//�е��ڴ���С
	static const unsigned int LargeBufferSize	= 1024;	//����ڴ���С

#pragma pack(push, 1)
	typedef struct tagBuffer
	{
		size_t		size_;		//�ڴ����ݶδ�С
		tagBuffer*	prev_buffer_;//ָ����һ���ڴ���ָ��
		int64_t		free_tick_;	//���������ٵ�ʱ��
#ifdef _MEMORY_TRACE_
		tagBuffer*	next_buffer_;//ָ�����¸��ڴ���ָ�룬���ڵ���
		struct
		{
			const char* fn_;		//�����ڴ��Ĵ���λ�ã����ڵ���
			int line_;
		} al, fl;
		bool		used_flag_;	//�Ƿ�ʹ�õı��
#endif
	} BUFFER, *PBUFFER;
#pragma pack(pop)

	struct BufferStatic
	{
		size_t		alloc_size_;
		size_t		free_size_;
	};

	typedef struct tagAllocatorMemoryInfo
	{
		BufferStatic	SmallBuffer;
		BufferStatic	MiddleBuffer;
		BufferStatic	LargeBuffer;
		BufferStatic	SuperBuffer;
	} ALLOCATOR_MEMORY_INFO;

private:
	Mutex				buffer_lock_;			//�ڴ��������
	PBUFFER				last_small_buffer_;		//ָ�����һ�����е�С���ڴ���ָ��
	PBUFFER				last_middle_buffer_;	//ָ�����һ�����е������ڴ���ָ��
	PBUFFER				last_large_buffer_;		//ָ�����һ�����еĴ����ڴ���ָ��
	PBUFFER				last_super_buffer_;		//ָ�����һ�����еĳ����ڴ���ָ��
#ifdef _MEMORY_TRACE_
	PBUFFER				last_alloced_buffer_;	//ָ�����һ����������ڴ��
#endif
	size_t				alloced_small_size_;	//�ѱ������С���ڴ���С
	size_t				alloced_middle_size_;	//�ѱ�����������ڴ���С
	size_t				alloced_large_size_;	//�ѱ�����Ĵ����ڴ���С
	size_t				alloced_super_size_;	//�ѱ�����ĳ����ڴ���С
	size_t				freed_small_size_;		//�ѱ��ͷŵ�С���ڴ���С
	size_t				freed_middle_size_;	//�ѱ��ͷŵ������ڴ���С
	size_t				freed_large_size_;		//�ѱ��ͷŵĴ����ڴ���С
	size_t				freed_super_size_;		//�ѱ��ͷŵĳ����ڴ���С

	bool				mult_thread_;
public:
	BufferAllocator(const char* namestr);
	~BufferAllocator();

#ifndef _MEMORY_TRACE_
	void* AllocBuffer(size_t size);
	void* ReAllocBuffer(void* ptr, size_t new_size);
	void FreeBuffer(void* ptr);
#else
	void* _AllocBuffer(size_t size, const char* fn, int line);
	void* _ReAllocBuffer(void* ptr, size_t new_size, const char* fn, int line);
	void _FreeBuffer(void* ptr, const char* fn, int line);
#endif

	void GetMemoryInfo(BufferAllocator::ALLOCATOR_MEMORY_INFO* pMemoryInfo);
	void CheckFreeBuffers();
	void SetMultiThread(bool flag);
	void GC();
};

#endif

