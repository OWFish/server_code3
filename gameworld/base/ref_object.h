#pragma once

//导出给脚本使用的对象的基类
//引用计数生命期自动管理类，禁止对此类调用delete，不用时应当调用release。
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

	//增加引用计数，函数返回增加后的引用计数。
	virtual int addRef()
	{
		ref_++;
		return ref_;
	}

	//减少引用计数，函数返回减少后的引用计数。如果计数减少为0则函数销毁对象自己
	virtual int release()
	{
		int r = --ref_;

		if (r <= 0)
			destroy();

		return r;
	}

	/*
	* Comments: 销毁实体
	* @Return void:
	*/
	virtual void destroy() = 0;

	inline int getRef() const
	{
		return ref_;
	}
private:
	int ref_;						// 引用计数，构造时必须为1
};


