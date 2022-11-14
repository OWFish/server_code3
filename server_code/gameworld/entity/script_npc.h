#ifndef _SCRIPT_NPC_H_
#define _SCRIPT_NPC_H_

// 此宏开关用于控制是否使用缓存的Lua二进制字节码加载以提高NPC创建速度
// 关闭此宏就直接加载脚本文件 
//#define USE_LUA_BIN_CODE // 然而并没有用到，因为conf_是空

class ScriptNpc : public Npc
{
	typedef Npc Inherited;
public:
	ScriptNpc();
	virtual ~ScriptNpc() {}

public:
	//初始化
	bool Init(void* data, size_t size)
	{
		return Inherited::Init(data, size);
	}
	//删除的一些内存消耗操作
	void OnDestroy();

	//处理LogicRun，实现对脚本的内存定时回收
	void LogicRun(int64_t curr_t);

	virtual void ResetScript();

	//获取脚本对象
	inline GameScript& GetScript()
	{
		return script_;
	}
	/*
	* Comments: 加载/重新加载NPC脚本
	* Param const char* sPath: 脚本文件路径，可以是绝对路径或基于程序运行目录的相对路径
	* Param bool boReload:是否重新读取
	* @Return bool: 返回加载脚本是否成功
	*/
	bool LoadScript(const char* sPath = NULL, bool boReload = false);

	//调用npc脚本的一个函数
	bool Call(const char* sFnName);

private:
	GameScript		script_;		//脚本对象
	Timer			script_gc_timer_;	//脚本垃圾收集定时器（动态时间）

	//Optimization
	size_t			script_len_;	// 脚本的长度，避免在分析文本的时候频繁resize内存
};

#endif