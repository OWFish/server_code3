#ifndef _SCRIPT_VALUE_LIST_H_
#define _SCRIPT_VALUE_LIST_H_

/************************************************************************
*   脚本值列表中最多允许保存MaxValueCount个值。此类适用于在与脚本交互中的函数调用参数
* 表的传递以及返回值列表的获取操作的场合。
************************************************************************/

class ScriptValueList
{
public:
	static const int MaxValueCount = 16;	//脚本值列表允许存储的值数量上限

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
	//获取列表中的值数量
	inline int count()
	{
		return count_;
	}
	//将列表转换为ScriptValue数组的运算符重载
	inline operator ScriptValue* ()
	{
		return values_;
	}
	//添加一个值
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
	//从另一个列表中赋值
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

	//清空值列表
	inline void clear()
	{
		for (int i = count_ - 1; i > -1; --i)
		{
			values_[i].clear();
		}

		count_ = 0;
	}
	/* 将值列表中的值压入lua脚本中。
	 * 将列表中的值压入脚本中后，列表不会被清空
	 */
	void pushArgs(lua_State* L, int count);
	/* 从lua脚本中取出返回值到值列表中，函数返回取出了多少个值。
	 * 如果列表中已经存在值，则之前的值将不会清空。
	 */
	int getResults(lua_State* L, int count);
	/* 将lua中传入的参数保存到值列表中。
	 * 列表会被清空，从而存放新的值列表
	 * 函数返回读取了多少个参数
	 */
	int getArguments(lua_State* L, int idx);

	/* 将值列表保存到流中 */
	inline void loadFromStream(stream::BaseStream& stm)
	{
		clear();
		stm.read(&count_, sizeof(count_));

		for (int i = 0; i < count_; ++i)
		{
			values_[i].loadFromStream(stm);
		}
	}

	/* 从流中读取值列表 */
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
	ScriptValue	values_[MaxValueCount];//值内存块
	int			count_;//值数量
};

#endif

