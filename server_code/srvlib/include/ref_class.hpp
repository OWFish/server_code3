#ifndef _REF_CLASS_HPP_
#define _REF_CLASS_HPP_

/************************************************************************

					 �Զ����������ڵ����ü�������ʵ����

	 ��ģ��ĺ����ṩ�����ü������ܵ�ʵ�֣�ʹ��ʱֱ�ӽ�������Ϊģ�����ʵ
 ����CRefObject��CMTRefObject���ɡ�ʵ���ڹ���ʱ���ü���Ϊ0�������ü�����
 Ϊ0ʱ���Զ�����ʵ����ʵ��ԭ��ͬ��COM�ӿڶ�������ü�����

   �Լ��������ʹ�ñ����ϸ���ѭ��ȡָ�������addRef������ʱrelease��

   ���ü���ʵ�ַ�ʽ�Ƕ��̰߳�ȫ�ġ����ڴ�����ԭ�ӱ������ķ�ʽʵ�֣�������
 ���� �����õ�ʱ�����ס�����Ա��ڶ��������֮�䱣�ֻ���һ���ԡ�������Ӳ
 ��ʵ�ֵġ�

   ͨ�������ʹ��CRefObject������Զ�������Ķ������ù��ܣ������ֱ��ʹ��
 CRefObjectImplģ����Ӧ��ע������ϸ�ڣ�
   ����ʹ��һ������ʵ��ǰ�������addRef()�����Ա��������ü�����
   ���ڽ����һ������ʵ��ʹ�ú�������release�����Ա�������ü�����
   �ﲻ��ʹ��delete����һ������ʵ���࣬��ȷ�������ǵ���release������ã�
   �ﱻʵ����������ֻ��ʹ��new��malloc������ڴ����й��죬���ܶԾֲ���
 �����ָ�����Ա�Ķ���ʹ�����ü���ʵ�֡�

***********************************************************************/
#ifndef _MSC_VER
#include "x_lock.h"
using namespace lock;
#endif

namespace misc
{
#ifdef _MSC_VER
typedef long COUNTTYPE;
#else
typedef int COUNTTYPE;
#endif
template <typename T>
class RefObjectImpl : public T
{
public:
	RefObjectImpl(): T()
	{
		m_nRefer = 0;
	}
	//�������ü��������������������ú�����ü���ֵ
	inline void addRef()
	{
#ifdef _MSC_VER
		InterlockedIncrement(&m_nRefer);
#else
		lock_.Lock();
		m_nRefer++;
		lock_.Unlock();
#endif
	}
	//�������ü������������ؼ������ú�����ü���ֵ
	//���������ú����ü���Ϊ0���Զ����ٶ�������
	inline void release()
	{
#ifdef _MSC_VER
		long n = InterlockedDecrement(&m_nRefer);
#else
		lock_.Lock();
		m_nRefer--;
		int n = m_nRefer;
		lock_.Unlock();
#endif

		if (n <= 0)
			finallRelease();
	}
protected:
	virtual void finallRelease()
	{
		delete this;
	}
private:
	COUNTTYPE	m_nRefer;	//���ü���
#ifndef _MSC_VER
	Mutex lock_;
#endif
};

template <typename T>
class RefObject
{
protected:
	RefObjectImpl<T>*	m_ptr;//����ʵ�ֶ���
public:
	RefObject()
	{
		m_ptr = NULL;
	}
	RefObject(RefObject<T>& obj)
	{
		m_ptr = obj.m_ptr;

		if (m_ptr)
			m_ptr->addRef();
	}
	RefObject(RefObjectImpl<T>* pObj)
	{
		m_ptr = pObj;

		if (m_ptr)
			m_ptr->addRef();
	}
	virtual ~RefObject()
	{
		if (m_ptr) m_ptr->release();
	}

	//�ṩ��ģ��ʵ�������͵�ת������
	inline operator T* ()
	{
		return m_ptr;
	}
	inline operator const T* () const
	{
		return m_ptr;
	}
	//��ȡ˽��ʵ�ֶ���ָ��
	inline RefObjectImpl<T>* raw_ptr()
	{
		return m_ptr;
	}
	inline const RefObjectImpl<T>* raw_ptr() const
	{
		return m_ptr;
	}

	//���ظ�ֵ���㺯����ʵ�ֶ��������
	inline void operator = (RefObject<T>& obj)
	{
		if (&obj != NULL)
		{
			if (obj.m_ptr == m_ptr)
				return;

			//������Ϊ��һ�������ʵ�����������ټ��ٵ�ǰʵ�������á�
			//��˷�ֹobj�����Լ������ü���Ϊ1�ڵ���release�����ɾ���������ڴ��������⡣
			if (obj.m_ptr) obj.m_ptr->addRef();

			if (m_ptr) m_ptr->release();

			m_ptr = obj.m_ptr;
		}
		else if (m_ptr)
		{
			m_ptr->release();
			m_ptr = NULL;
		}
	}
	//���ظ�ֵ���㺯����ʵ�ֶ��������
	inline void operator = (RefObjectImpl<T>* pObj)
	{
		if (pObj != NULL)
		{
			if (pObj == m_ptr)
				return;

			if (pObj) pObj->addRef();

			if (m_ptr) m_ptr->release();

			m_ptr = pObj;
		}
		else if (m_ptr)
		{
			m_ptr->release();
			m_ptr = NULL;
		}
	}
	//��������Բ��������
	inline bool operator == (const RefObject<T>& obj) const
	{
		return obj.m_ptr == m_ptr;
	}
	inline void operator == (const RefObjectImpl<T>* pObj) const
	{
		return pObj == m_ptr;
	}
	inline void operator == (const int n) const
	{
		if (n == 0)
			return m_ptr == NULL;
		else return m_ptr != NULL;
	}
	//���ز����Բ��������
	inline bool operator != (const RefObject<T>& obj) const
	{
		return obj.m_ptr != m_ptr;
	}
	inline bool operator != (const RefObjectImpl<T>* pObj) const
	{
		return pObj != m_ptr;
	}
	inline void operator != (const int n) const
	{
		if (n == 0)
			return m_ptr != NULL;
		else return m_ptr == NULL;
	}
	inline bool operator !() const
	{
		return m_ptr == NULL;
	}
};
};


#endif

