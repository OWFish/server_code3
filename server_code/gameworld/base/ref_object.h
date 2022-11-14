#pragma once

//�������ű�ʹ�õĶ���Ļ���
//���ü����������Զ������࣬��ֹ�Դ������delete������ʱӦ������release��
class ObjectRef
{
public:
	ObjectRef()
	{
		ref_ = 0;
	}
	virtual ~ObjectRef()
	{
	}

	//�������ü����������������Ӻ�����ü�����
	virtual int addRef()
	{
		ref_++;
		return ref_;
	}

	//�������ü������������ؼ��ٺ�����ü����������������Ϊ0�������ٶ����Լ�
	virtual int release()
	{
		int r = --ref_;

		if (r <= 0)
			destroy();

		return r;
	}

	/*
	* Comments: ����ʵ��
	* @Return void:
	*/
	virtual void destroy() = 0;

	inline int getRef() const
	{
		return ref_;
	}
private:
	int ref_;						// ���ü���������ʱ����Ϊ1
};


