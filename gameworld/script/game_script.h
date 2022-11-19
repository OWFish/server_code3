#ifndef _GAME_SCRIPT_H_
#define _GAME_SCRIPT_H_

class Entity;

class GameScript :
	public BaseScript
{
public:
	typedef BaseScript Inherited;

	/* 脚本中申请的ActorPacket指针，保存指针以便在角色申请数据包后出现脚本错误从而无法flush数据包的时候回收数据包，
	   如果脚本出错且数据包没有被回收，则会导致整个游戏引擎就此不能正常工作
	*/
	static struct ActorPacket* ScriptActorPacket;

public:
	GameScript();
	~GameScript();

#ifdef _DEBUG
	/*
	* Comments: 保存脚本函数调用性能统计数据到文件
	* Param const char* sFilePath:
	* @Return void:
	*/
	void SaveProfiler(const char* sFilePath);

#endif

	void SetEntity(Entity* et)
	{
		npc_ptr_ = et;
	}
protected:
	/* 下列函数集为覆盖父类的相关处理函数 */
	//创建脚本虚拟机
	virtual lua_State* createLuaVM();
	//注册本地函数库。返回true表示成功。
	virtual bool registLocalLibs();
	//调用脚本的初始化函数。函数返回true表示没有错误发生。本类未提供调用初始化函数的实际功能。
	virtual bool onCallInit();
	//调用脚本的卸载函数。函数返回true表示没有错误发生。本类未提供调用卸载函数的实际功能。
	virtual bool onCallFinal();
	// cal函数执行完执行这个
	virtual void onCallEnd(bool ret);
	// 显示错误信息和报送后台
	virtual void showError(const char* err);
private:
	//把错误信息记录到日志库
	void logError(const char* sError);

protected:
	Entity*			npc_ptr_;	//脚本对象所属的角色对象，例如NPC对象
#ifdef _DEBUG
	LuaProfiler		m_Profiler;		//脚本函数调用性能统计
#endif
};

#endif
