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
		Vector<T>	append_list_;	//����׷���б�
	public:
		//������ݣ����ݽ��ڵ���flush��tryFlush�Ǳ��ύ�������б���
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
		//��ȡ׷����������
		inline int appendCount()
		{
			return append_list_.count();
		}
		//�ύ��append������ӵ�����
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

