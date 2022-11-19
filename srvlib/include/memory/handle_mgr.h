#ifndef _HANDLE_MGR_H_
#define _HANDLE_MGR_H_

#include "os_def.h"
#include <stdint.h>

namespace memory
{

//template <typename TAG>
class Handle
{
public:
	union
	{		
		struct
		{
			unsigned int index_ : 21; // index into resource array ��Դ���������
			unsigned int magic_ : 11; // magic number to check     ��Ҫ����ħ����
		};
		unsigned int handle_;
	};

public:
	const static int MAX_INDEX = (1 << 21) - 1;
	const static int MAX_MAGIC = (1 << 11) - 1;
	Handle(void) : handle_(0) { }
	Handle(unsigned int handle)
	{
		handle_ = handle ;   //
	}

	void Init(unsigned int index)
	{
		assert(index <= (unsigned int)MAX_INDEX);
		index_ = index;
		magic_ = wrand(MAX_MAGIC) + 1;	//magic_���ܵ���0���������handle==0
	}

	inline void Update()
	{
		++magic_;

		if (handle_ == 0) ++magic_;
	}

	inline bool IsNull(void) const
	{
		return (!handle_);
	}
	inline unsigned int GetIndex(void) const
	{
		return (index_);
	}
	inline unsigned int GetHandle(void) const
	{
		return (handle_);
	}
	inline static unsigned int GetMaxIndex()
	{
		return MAX_INDEX;
	}
	operator unsigned int (void) const
	{
		return (handle_);
	}
	inline Handle& operator = (const unsigned int h)
	{
		handle_ = h;
		return *this;
	}
};


//һ��64λ��handleֵ��֧�ָ��������ֵ��ħ������Ӧ�õ���Ҫ��������ڴ�ĵط�
//template <typename TAG>
class Handle64
{
public:
	union
	{
		struct
		{
			unsigned int index_ : 32; // index into resource array ��Դ���������
			unsigned short magic_ : 16; // magic number to check     ��Ҫ����ħ����
			unsigned short rev_ : 16;
		};
		int64_t handle_;
	};

public:

	Handle64(void) : handle_(0) { }
	Handle64(int64_t nHandle)
	{
		handle_ = nHandle ;   //
	}

	void Init(unsigned int index)
	{
		assert(index <= GetMaxIndex());

		index_ = index;
		magic_ = wrand(0xffff) + 1;
	}

	inline void Update()
	{
		++magic_;

		if (handle_ == 0) ++magic_;
	}

	inline bool IsNull(void) const
	{
		return (!handle_);
	}
	inline unsigned int GetIndex(void) const
	{
		return (index_);
	}
	inline int64_t GetHandle(void) const
	{
		return (handle_);
	}
	inline static unsigned GetMaxIndex()
	{
		return 0xffffffff ;
	}
	inline operator int64_t (void) const
	{
		return (handle_);
	}
	inline Handle64& operator = (const int64_t v)
	{
		handle_ = v;
		return *this;
	}
	inline Handle64& operator = (const Handle64 v)
	{
		handle_ = v.handle_;
		return *this;
	}
};


template <typename DATA, typename HDL, int ONE_TIME_COUNT = 1024>
class HandleMgr :
	public AllocatorCounterItem
{
public:

	typedef AllocatorCounterItem Inherited;
	struct tagHandle
	{
		HDL handle_;
		bool using_flag_;
	};

private:
	const static int BUFF_SIZE = sizeof(DATA) + sizeof(tagHandle);
	struct DataBlock
	{
		DataBlock*	prev_;
	}*		data_block_;
public:

#ifndef _MEMORY_TRACE_
	DATA* AllocHandle(HDL& handle)
#else
#define AllocHandle(handle) _AllocHandle(handle,__FILE__, __LINE__)
#define Free(ptr) _Free(ptr, __FILE__, __LINE__)
	DATA* _AllocHandle(HDL& handle, const char* file_name, int line)
#endif
	{
		void* result = NULL;
		int count = free_list_.count();

		if (count <= 0)
		{
			count = all_list_.size() <= 0 ? ONE_TIME_COUNT : all_list_.size() * 2;	//ÿ��double

			if (unsigned(all_list_.size() + count) > HDL::GetMaxIndex())
			{
				count = HDL::GetMaxIndex() - all_list_.size();

				if (count <= 0)
				{
					return NULL;
				}
			}

#ifndef _MEMORY_TRACE_
			size_t allocsize = sizeof(DataBlock) + BUFF_SIZE * count;
#else
			size_t allocsize = sizeof(DataBlock) + (BUFF_SIZE + sizeof(AllocBuffHead)) * count;
#endif
			DataBlock* block_ptr = (DataBlock*)malloc(allocsize);
#ifdef _MEMORY_TRACE_
			alloc_total_ += allocsize;
#endif
			//������ָ��ȫ����ӵ������б���
			result = (void*)(block_ptr + 1);

			int max_size = all_list_.size() + count;

			if (free_list_.max_size() < max_size)
				free_list_.reserve(max_size);

			int index = all_list_.size();
			void** list = free_list_;

			for (int i = 0; i < count; ++i)
			{
				tagHandle* hdl_ptr = NULL;
				list[i] = result;
#ifdef _MEMORY_TRACE_
				AllocBuffHead* hdr = (AllocBuffHead*)result;
				hdr->using_flag_ = false;
				hdr->buff_size_ = BUFF_SIZE;
				hdl_ptr = (tagHandle*)((char*)result + sizeof(AllocBuffHead));
				result = (void*)((char*)result + BUFF_SIZE + sizeof(AllocBuffHead));
#else
				hdl_ptr = (tagHandle*)result;
				result = (void*)((char*)result + BUFF_SIZE);
#endif
				hdl_ptr->handle_ = 0;
				hdl_ptr->handle_.Init(index);
				hdl_ptr->using_flag_ = false;
				index++;
			}

			all_list_.addArray(free_list_, count); //�Ѿ�����ļ�¼��
			//������ڴ�����һ���ڴ��
			block_ptr->prev_ = data_block_;
			data_block_ = block_ptr;
		}

		//�����б��е����һ������
		count--;
		result = free_list_[count];
		free_list_.trunc(count);
#ifdef _MEMORY_TRACE_
		used_count_ += BUFF_SIZE;
#endif

#ifdef _MEMORY_TRACE_
		AllocBuffHead* hdr = (AllocBuffHead*)result;
#ifdef _MSC_VER
		assert(hdr->using_flag_ == false);
#endif

		hdr->using_flag_ = true;
		hdr->al_.fn_ = file_name;
		hdr->al_.line_ = line;
		result =  hdr + 1;
#endif
		tagHandle* hdl_ptr = (tagHandle*)result;
		hdl_ptr->handle_.Update();//index���䣬��magicnum
		result = (void*)((char*)result + sizeof(tagHandle));
		DATA* pd = (DATA*)result;
		new(pd)DATA();	//���캯��
		handle = hdl_ptr->handle_;
		hdl_ptr->using_flag_ = true;
		return pd;
	}

#ifndef _MEMORY_TRACE_
	void Free(DATA* ptr)
#else
	void _Free(DATA* ptr, const char* file_name, int line)
#endif
	{
		if (ptr == NULL) return;

		tagHandle* hdl_ptr = (tagHandle*)ptr;
		hdl_ptr--;

		//����Ƿ�Ϸ�
		if (GetPtr(hdl_ptr->handle_) == NULL)
		{
			return;
		}

#ifndef _MEMORY_TRACE_
		SavePtr(hdl_ptr);
#else
		SavePtr(hdl_ptr, file_name, line);
#endif
	}

#ifndef _MEMORY_TRACE_
	void Free(HDL handle)
#else
	void _Free(HDL handle, const char* file_name, int line)
#endif
	{
		tagHandle* hdl_ptr = (tagHandle*)GetPtr(handle);

		if (hdl_ptr == NULL)
		{
			return;
		}

		hdl_ptr--;
#ifndef _MEMORY_TRACE_
		SavePtr(hdl_ptr);
#else
		SavePtr(hdl_ptr, file_name, line);
#endif
	}

	//����handle��ȡָ��
	DATA* GetPtr(HDL handle)
	{
		//��֤�����ָ���ǲ�����������ȥ��
		int index = handle.GetIndex();

		if (index < 0 || index >= all_list_.size())
		{
			return NULL;
		}

		void* save_ptr = all_list_[index];
#ifdef _MEMORY_TRACE_
		tagHandle* hdl_ptr = (tagHandle*)((char*)save_ptr + sizeof(AllocBuffHead));
#else
		tagHandle* hdl_ptr = (tagHandle*)save_ptr;
#endif
		HDL& h = hdl_ptr->handle_;

		if (h.index_ != handle.index_ || h.magic_ != handle.magic_ || !hdl_ptr->using_flag_)	//handle�����ǲ��Ϸ���
		{
			return NULL;
		}

		return (DATA*)((char*)hdl_ptr + sizeof(tagHandle));
	}

	bool ReNew(HDL& handle)
	{
		// �����Ч��
		if (!GetPtr(handle)) return false;

		handle.Update();
		int index = handle.GetIndex();
		void* save_ptr = all_list_[index];
#ifdef _MEMORY_TRACE_
		tagHandle* hdl_ptr = (tagHandle*)((char*)save_ptr + sizeof(AllocBuffHead));
#else
		tagHandle* hdl_ptr = (tagHandle*)save_ptr;
#endif
		hdl_ptr->handle_ = handle;	// ���³��µ�handle
		return true;
	}

	HandleMgr(const char* namestr)
		: Inherited(namestr)
	{
		data_block_ = NULL;
	}
	~HandleMgr()
	{
#ifdef _MEMORY_TRACE_

		for (int i = 0; i < all_list_.size(); i++)
		{
			AllocBuffHead* hdr = (AllocBuffHead*)(all_list_[i]);

			if (hdr->using_flag_)
			{
				char err[1024];
				SNPRINTFA(err, sizeof(err) - 1, " %s check memory leaks(size:%d)��alloc��%s(%d)\n",
					__FUNCTION__, (int)hdr->buff_size_, hdr->al_.fn_, hdr->al_.line_);
				OutputWatchFile(err, "err.log");
			}
			
#ifdef _MSC_VER
			assert(hdr->using_flag_ == false);//�ڴ�й¶��
#endif
		}

#endif
		DataBlock* block_ptr, *prev;
		block_ptr = data_block_;
		int block_count = 0;

		while (block_ptr)
		{
			prev = block_ptr->prev_;
			free(block_ptr);
			block_ptr = prev;
			block_count++;
		}

		data_block_ = NULL;
#ifdef _MEMORY_TRACE_
		size_t free_size = free_list_.count() * (BUFF_SIZE + sizeof(AllocBuffHead)) + block_count * sizeof(DataBlock);
		if (free_size != alloc_total_)
		{
			char err[1024];
			SNPRINTFA(err, sizeof(err) - 1, "%s:%s:%d memory error,free size:%lld, alloc_size:%lld\n",
				__FUNCTION__, __FILE__, __LINE__, (long long int)free_size, (long long int)alloc_total_);
			OutputWatchFile(err, "err.log");
		}
#ifdef _MSC_VER
		assert(free_size == alloc_total_); //�򵥵ļ���Ƿ��ڴ�й¶
#endif

#else
		assert(free_list_.count()*BUFF_SIZE + block_count * sizeof(DataBlock) == alloc_total_); //�򵥵ļ���Ƿ��ڴ�й¶
#endif
	}

	//public:
	//#ifdef _MEMORY_TRACE_
	//	virtual int Log(char* buf, int num){ return sprintf(buf,"alloc total:%d,used:%d",alloc_total_,used_count); }
	//#endif
private:
#ifndef _MEMORY_TRACE_
	void SavePtr(tagHandle* hdl_ptr)
#else
	void SavePtr(tagHandle* hdl_ptr, const char* file_name, int line)
#endif
	{
		//�ĵ�magicnum
		hdl_ptr->using_flag_ = false;
		hdl_ptr->handle_.Update();

		void* save_ptr = (void*) hdl_ptr;
#ifdef _MEMORY_TRACE_
		AllocBuffHead* hdr = (AllocBuffHead*)save_ptr;
		hdr--;

		if (!hdr->using_flag_)
		{
			printf(" %sFree the buff that had be release before(size:%d)��alloc��%s(%d)��free��%s(%d)\n",
			       __FUNCTION__, (int)hdr->buff_size_, hdr->al_.fn_, hdr->al_.line_,
			       hdr->fl_.fn_, hdr->fl_.line_);
		}
#ifdef _MSC_VER
		assert(hdr->using_flag_);//�����û���ظ��ͷ�
#endif

		hdr->using_flag_ = false;
		hdr->fl_.fn_ = file_name;
		hdr->fl_.line_ = line;
		save_ptr = hdr;
#endif
		DATA* data_ptr = (DATA*)(++hdl_ptr);
		data_ptr->~DATA();
		free_list_.add(save_ptr);
#ifdef _MEMORY_TRACE_
		used_count_ -= BUFF_SIZE;
#endif
	}
protected:
	container::Vector<void*> free_list_;
	container::Vector<void*> all_list_;//���з�����ڴ涼���������¼
};
};

#endif
