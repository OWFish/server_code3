#ifndef _LIB_THREAD_H_
#define _LIB_THREAD_H_

/******************************************************************
 *  - ��Ҫ���� -
 *	ʵ���̵߳Ļ�����װ������֧����ͣ���ָ��̣߳��ȴ��߳��Լ���
 *	���߳����ȼ��Ȼ���������
 *****************************************************************/
#ifndef _MSC_VER
#include "pthread.h"
#endif

namespace thread
{
class BaseThread
{
private:
#ifdef _MSC_VER
	static void CALLBACK ThreadRoutine(BaseThread* thread_ptr);
#else
	static void* ThreadRoutine(void* thread_ptr);
#endif
protected:
	//terminated���������ж��ֳ��Ƿ���������ֹ���
	inline bool terminated()
	{
		return terminated_;
	}
	//�߳����ﴦ�����̺���������Ӧ���̳д˺���
	virtual void OnRoutine();
	//�߳�������ֹ���֪ͨ����
	virtual void OnTerminated();
public:
	BaseThread();
	virtual ~BaseThread();

#ifdef _MSC_VER
	//��ȡ�߳̾��
	inline void* getHandle()
	{
		return thread_;
	}
	//��ȡ�߳�ID
	inline unsigned long getThreadId()
	{
		return thread_id_;
	}
#endif
	//�ָ��̵߳�ִ�У�����ֵ��ʾ�̵߳����λָ��������߳�����ָ����ٴβ��ָܻ�ִ�С�
	//������-1���ʾ�ָ��߳�ʧ�ܣ�����0��ʾ�߳��Ѿ���ȫ�ָ�ִ�С�
	virtual int Start();
	virtual void Stop();
#ifdef _MSC_VER
	//��ȡ�߳����ȼ�,ʧ�ܻ᷵��THREAD_PRIORITY_ERROR_RETURN�����򷵻�ֵ��ʾ�߳����ȼ�
	int getPriority();
	//�����߳����ȼ����ɹ��򷵻�true
	bool setPriority(int priority);
#endif
	//�ȴ��߳�ִ����ϣ�wait_time������ʾ�ȴ�������������INFINITE��ʾ���޵ȴ���
	//ע�⣬���ô˺������߳��ڴ��߳�ִ����Ϻ��һֱ��������״̬
	//����wait_alert��ʾ�����߳��������ڼ��Ƿ�������뾯��״̬��������windows��Ч)
#ifdef _MSC_VER
	int waitFor(unsigned int wait_time = INFINITE, bool wait_alert = true);
#else
	int waitFor();
#endif
	//����̵߳���ֹ���
	void terminate();
private:
#ifdef _MSC_VER
	void*			thread_;			//�߳̾��
	unsigned long	thread_id_;			//�߳�ID
#else
	pthread_t		thread_id_;
#endif
	bool			terminated_;		//�߳���ֹ��ǣ��������߳�����ѭ����Ӧ��ͨ������terminated�����ж��߳��Ƿ���������ֹ���
};
};

#endif

