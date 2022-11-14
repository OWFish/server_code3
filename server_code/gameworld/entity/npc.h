#ifndef _NPC_H_
#define _NPC_H_

class Npc:
	public Entity
{
public:
	typedef Entity Inherited;

public:
	Npc();
	virtual ~Npc() {}

	void InitNPCAi();

	//初始化
	bool Init(void* data, size_t size)
	{
		return Inherited::Init(data, size);
	}
	//删除的一些内存消耗操作

	//处理LogicRun，实现对脚本的内存定时回收
	void LogicRun(int64_t curr_t);
	virtual int GetId() { return 0; } // todo 现在没用， npc需要重构
public:
	//inline void SetConfig(NpcConfig* conf) { conf_ = conf; }
	//inline NpcConfig* GetConfig() { return conf_; }
	/*
	* Comments: 用户与NPC对话并执行指定的函数，如果脚本函数返回字符串，那么脚本返回值将发给客户端呈现
	* Param Actor* pActor: 对话的玩家对象
	* Param const char* sFnName: 函数名称
	* @Return void:
	*/
	void Talk(Actor* pActor, const char* sFnName);

	void Talk(Actor* pActor, const char* sFnName, ScriptValueList& va);

	//用户点击NPC的处理函数，默认是调用main函数
	inline void Click(Actor* actor)
	{
		Talk(actor, "npcMain");
	}

	//发送消息，关闭npc的对话窗口
	//void CloseDialog(Actor* pActor);

	/*
	* Comments: NPC发言
	* @Return void:
	*/
	void NPCTalk();

	/*
	* Comments: 重新刷一遍脚本
	* @Return void:
	* @Remark: 增加此接口用于重新刷一次NPC脚本。主要针对NPC复用。考虑到当前已经处于内测阶段，保证稳定性为主。以后可以考虑
	*		   不用reloadScript，而是call Uninitialize和Initialize接口。
	*/
	virtual void ResetScript();

	/*
	* Comments: 通过场景和NPC的名字获取NPC的指针
	* Param char * sSceneName:场景的名字
	* Param char * sNpcName:npc的名字
	* @Return CNpc *:返回NPC的指针
	*/
	static Npc* GetNpcPtr(char* sSceneName, char* sNpcName);
protected:
	/*
	* Comments:函数的参数处理，约定的格式为函数名字,参数1，参数2，处理完以后va 中包含参数1，参数2
	* Param const char*  str:输出的函数的名字 格式为函数名字,参数1，参数2
	* Param CScriptValueList & va: 参数列表
	* Param char *  & pFunc:函数的名字
	* Param nOutBuffSize: pFunc这个字符串缓冲的长度
	* @Return void:
	*/
	void FuncParamProcess(const char*  str, char* pFunc, int nOutBuffSize, ScriptValueList& va);

//protected:
	//npcConfig*		conf_;			//npc的配置信息
};

#endif

