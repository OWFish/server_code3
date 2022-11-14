#ifndef _SCRIPT_VALUE_LIST_H_
#define _SCRIPT_VALUE_LIST_H_

/************************************************************************
*   �ű�ֵ�б������������MaxValueCount��ֵ����������������ű������еĺ������ò���
* ��Ĵ����Լ�����ֵ�б�Ļ�ȡ�����ĳ��ϡ�
************************************************************************/

class ScriptValueList
{
public:
	static const int MaxValueCount = 16;	//�ű�ֵ�б�����洢��ֵ��������

public:
	ScriptValueList()
	{
		count_ = 0;
	}
	ScriptValueList(const ScriptValueList& valList)
	{
		count_ = 0;
		operator = (valList);
	}
	//��ȡ�б��е�ֵ����
	inline int count()
	{
		return count_;
	}
	//���б�ת��ΪScriptValue��������������
	inline operator ScriptValue* ()
	{
		return values_;
	}
	//���һ��ֵ
	template <typename T>
	inline ScriptValueList& operator << (const T val)
	{
		if (count_ < MaxValueCount)
		{
			values_[count_] = val;
			count_++;
		}

		return *this;
	}
	//����һ���б��и�ֵ
	inline ScriptValueList& operator = (const ScriptValueList& valList)
	{
		clear();

		for (int i = valList.count_ - 1; i > -1; --i)
		{
			values_[i] = valList.values_[i];
		}

		count_ = valList.count_;
		return *this;
	}

	inline ScriptValueList& operator += (const ScriptValueList& valList)
	{
		for (int i = 0; i < valList.count_ && count_ < MaxValueCount; i++)
		{
			values_[count_++] = valList.values_[i];
		}

		return *this;
	}

	//���ֵ�б�
	inline void clear()
	{
		for (int i = count_ - 1; i > -1; --i)
		{
			values_[i].clear();
		}

		count_ = 0;
	}
	/* ��ֵ�б��е�ֵѹ��lua�ű��С�
	 * ���б��е�ֵѹ��ű��к��б��ᱻ���
	 */
	void pushArgs(lua_State* L, int count);
	/* ��lua�ű���ȡ������ֵ��ֵ�б��У���������ȡ���˶��ٸ�ֵ��
	 * ����б����Ѿ�����ֵ����֮ǰ��ֵ��������ա�
	 */
	int getResults(lua_State* L, int count);
	/* ��lua�д���Ĳ������浽ֵ�б��С�
	 * �б�ᱻ��գ��Ӷ�����µ�ֵ�б�
	 * �������ض�ȡ�˶��ٸ�����
	 */
	int getArguments(lua_State* L, int idx);

	/* ��ֵ�б��浽���� */
	inline void loadFromStream(stream::BaseStream& stm)
	{
		clear();
		stm.read(&count_, sizeof(count_));

		for (int i = 0; i < count_; ++i)
		{
			values_[i].loadFromStream(stm);
		}
	}

	/* �����ж�ȡֵ�б� */
	inline int64_t saveToStream(stream::BaseStream& stm) const
	{
		int64_t dwPos = stm.getPosition();
		stm.write(&count_, sizeof(count_));

		for (int i = 0; i < count_; ++i)
		{
			values_[i].saveToStream(stm);
		}

		return stm.getPosition() - dwPos;
	}
protected:
	ScriptValue	values_[MaxValueCount];//ֵ�ڴ��
	int			count_;//ֵ����
};

#endif

