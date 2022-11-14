#ifndef _GLOBAL_VAR_MGR_H_
#define _GLOBAL_VAR_MGR_H_

/****************************************
	提供给脚本保存全局数据的组件
*****************************************/

#include "timer.h"

class GlobalVarMgr
{
public:
	/*
	* Comments:从db读取数据
	* @Return void:
	*/
	void Load();

	/*
	* Comments:定期检查
	* @Return void:
	*/
	void RunOne(int64_t now_t);

	//存盘
	void Save();

	inline void Destroy()
	{
		var_.clear();
	}

	//获取变量对象
	inline CLVariant& GetVar()
	{
		return var_;
	}

public:
	GlobalVarMgr();
	~GlobalVarMgr();
private:
	CLVariant var_;
	bool inited_;	//是否已经读入数据
	Timer timer_;	//
};

#endif

