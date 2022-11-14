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
		Mutex	*lock_;//������
	public:
		LockList(Mutex *lock = NULL):Inherited()
		{
			lock_ = lock;
		}
		//��ȡ�б�������
		inline Mutex* getLock(){ return lock_; }
		//�����б������󣬺������ؾɵ��б���
		Mutex* setLock(Mutex *lock)
		{
			Mutex *pOldLock = lock_;
			lock_ = lock;
			return pOldLock;
		}
		//���б����
		inline void lock()
		{
			assert(lock_);
			if ( lock_ ) lock_->Lock();
		}

		//���б����
		inline void unlock()
		{
			if ( lock_ ) lock_->Unlock();
		}
	};
};

#endif

