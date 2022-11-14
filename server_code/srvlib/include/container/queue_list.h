#ifndef _MBASE_QUEUELIST_H_
#define _MBASE_QUEUELIST_H_

#include "lock_list.h"
#include "container/vector.h"

namespace container
{
	template <typename T>
	class QueueList :
		public LockList<T>
	{
	public:
		typedef LockList<T> Inherited;
		typedef QueueList<T> ListClass;
	private:
		Vector<T>	append_list_;	//数据追加列表
	public:
		//添加数据，数据将在调用flush或tryFlush是被提交到自身列表中
		inline void append(const T& data)
		{
			this->lock();
			append_list_.add(data);
			this->unlock();
		}
		inline void appendList(Vector<T> &list)
		{
			this->lock();
			append_list_.addArray(list, list.count());
			this->unlock();
		}
		inline void appendArray(T* data, int length)
		{
			this->lock();
			append_list_.addArray(data, length);
			this->unlock();
		}
		//获取追加数据数量
		inline int appendCount()
		{
			return append_list_.count();
		}
		//提交由append调用添加的数据
		inline void flush()
		{
			this->lock();
			if ( append_list_.count() > 0 )
			{
				this->addList(append_list_);
				append_list_.trunc(0);
			}
			this->unlock();
		}
	};
};

#endif

