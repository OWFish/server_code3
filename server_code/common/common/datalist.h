#ifndef _CONFIG_DATA_DEF_H_
#define _CONFIG_DATA_DEF_H_

//���ݶ�ȡ��ʱ���һЩ���������ݽṹ
//����ṹ�����Ϸ���������ݵ�һЩ����
template <class T>
struct DataList
{
	DataList<T>()
	{
		data_ = NULL;
		count_ = 0;
	}
	T* data_;
	int count_;
	//inline operator T* () const { return data_; }
	inline T* GetDataPtr(int nIndex)
	{
		if (data_ && nIndex >= 0 && nIndex < count_)
		{
			return data_ + nIndex;
		}
		else
		{
			return NULL;
		}
	}
};

template <class T, int MAX_NUM = 16>
struct StaticDataList
{
	StaticDataList<T, MAX_NUM>()
	{
		count_ = 0;
	}
	~StaticDataList(){
		count_ = 0;
	}
	T data_[MAX_NUM];
	int count_;
	//inline operator T* () const { return data_; }
	inline T* GetDataPtr(int nIndex)
	{
		if (nIndex >= 0 && nIndex < count_ && nIndex < MAX_NUM)
		{
			return &data_[nIndex];
		}
		else
		{
			return NULL;
		}
	}
};

#endif

