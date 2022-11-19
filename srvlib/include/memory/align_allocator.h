#ifndef _ALIGN_ALLOCATOR_H_
#define _ALIGN_ALLOCATOR_H_

/************************************************************************
* 适用于小内存的频繁分配的场景，同时为了性能牺牲了部分内存空间
************************************************************************/

using namespace lock;

#define GetAlignIdx(t) (t % align_ == 0 ? (t / align_ - 1) : (t / align_))

class AlignAllocator : public BaseAllocator
{
	struct FreeNode
	{
		FreeNode* next_;
		int size_;
	};

	struct Header
	{
		FreeNode* first_;
		int total_;
		int free_;
		Header()
		{
			total_ = free_ = 0;
			first_ = NULL;
		}
	};
public:
	AlignAllocator(const char* name, int max_size, int align);
	virtual ~AlignAllocator();

public:
#ifndef _MEMORY_TRACE_
	virtual void* AllocBuffer(size_t count);
	virtual void* ReAllocBuffer(void* src, size_t count);
	virtual void FreeBuffer(void* ptr);
#else
	virtual void* _AllocBuffer(size_t count, const char*, int);
	virtual void* _ReAllocBuffer(void* src, size_t newsize, const char* fn, int line);
	virtual void _FreeBuffer(void* ptr, const char*, int);
#endif

	void Init(int max_size, int align);
	void GC();
	void SetMultiThread(bool flag) { mult_thread_ = flag; }
	void SetGCRest(int rest) { rest_ = rest; }

private:
	int	max_size_;
	int	align_;
	Header*	heads_;
	int	hdrCnt_;
	int rest_;

	// 支持加锁，可以多线程安全
	bool mult_thread_;
	Mutex buffer_lock_;
};

#endif	//end _ALIGN_ALLOCATOR_H_
