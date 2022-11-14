#ifndef _MBASE_LOCKLIST_H_
#define _MBASE_LOCKLIST_H_

#include "container/vector.h"
#include "x_lock.h"

namespace container
{
	using namespace lock;

	template <typename T>
	class LockList :
		public Vector<T>
	{
	public:
		typedef Vector<T> Inherited;
		typedef LockList<T> ListClass;
	private:
		Mutex	*lock_;//数据锁
	public:
		LockList(Mutex *lock = NULL):Inherited()
		{
			lock_ = lock;
		}
		//获取列表锁对象
		inline Mutex* getLock(){ return lock_; }
		//设置列表锁对象，函数返回旧的列表锁
		Mutex* setLock(Mutex *lock)
		{
			Mutex *pOldLock = lock_;
			lock_ = lock;
			return pOldLock;
		}
		//对列表加锁
		inline void lock()
		{
			assert(lock_);
			if ( lock_ ) lock_->Lock();
		}

		//对列表解锁
		inline void unlock()
		{
			if ( lock_ ) lock_->Unlock();
		}
	};
};

#endif

