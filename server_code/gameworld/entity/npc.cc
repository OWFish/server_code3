#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

using namespace stream;

Npc::Npc()
{
	//conf_ = NULL;
}

void Npc::InitNPCAi()
{
	/*static AiMgr& aimgr = GetGameEngine()->GetAiMgr();

	if (conf_ && conf_->ai_type_ > 0)
	{
		ai_ptr_ = aimgr.CreateAi(conf_->ai_type_, this);
	}
	*/
}

void Npc::LogicRun(int64_t curr_t)
{
	if (IsInited() == false) return;

	Inherited::LogicRun(curr_t);	// (NPC不执行怪物的这些逻辑检测)
}

void Npc::ResetScript()
{
	// 清空所有的实体消息和实体回调
	ClearAllActMsg();
}

Npc* Npc::GetNpcPtr(char* sceneName, char* npcName)
{
	/*if (sceneName == NULL || npcName == NULL) return NULL;

	static GameEngine* ge = GetGameEngine();
	Npc* npc = NULL;

	if (!STRNCASECMP(sceneName, "SYS", 3))
	{
		npc = ge->GetGlobalNpc();
	}
	else
	{
		FuBen* fb = NULL;
		Scene* scene = NULL;

		static FuBenMgr* fbmgr = ge->GetFuBenMgr();

		if (fbmgr->GetFbPtrBySceneName(sceneName, fb, scene) == false || scene == NULL)
		{
			OutputMsg(rmError, ("func [%s] scene=%s not exist"), __FUNCTION__, sceneName);
			return NULL;
		}

		npc = scene->GetNpc(npcName);
	}

	if (npc == NULL)
	{
		OutputMsg(rmError, ("func [%s] scene=%s NPC=%s not exist"), __FUNCTION__, sceneName, npcName);
	}

	return npc;
	*/
	return nullptr;
}

void Npc::FuncParamProcess(const char* args, char* func, int size, ScriptValueList& va)
{
	if (!args || !func)
		return;

	_STRNCPY_S(func, args, size);

	char* pos = (char*)strchr(func, ',');
	char* ptr = func;

	if (pos)
	{
		ptr = pos + 1;
		*pos = 0;//讲第一个','位置的字符改写为0，使得sFnArgs再第一个','处终止，sFnArgs即是函数名称

		//解出所有以','分隔的参数
		while (va.count() < ScriptValueList::MaxValueCount)
		{
			pos = strchr(ptr, ',');

			if (!pos)
			{
				if (*ptr) va << ptr;

				break;
			}

			*pos = 0;//
			va << ptr;
			//将处理指针调整到次','的后面继续搜索
			ptr = pos + 1;
		}
	}
}

void Npc::Talk(Actor* actor, const char* fn)
{
	/*if (actor == NULL) return;

	if (fn == NULL || fn[0] == 0 || conf_ == NULL)
		return;

	ScriptValueList va;
	char args[1024] = {0};
	// 向参数表中写入玩家对象
	va << actor;
	// 
	va << (int)conf_->id_;

	FuncParamProcess(fn, args, sizeof(args), va);

	Talk(actor, args, va);
	*/
}

void Npc::Talk(Actor* actor, const char* fnName, ScriptValueList& va)
{
	//if (actor == NULL || !fnName) return;

	//if (GetAttriFlag().DenySee)
	//{
	//	CloseDialog(actor);
	//	return;
	//}

	//static GameScript& game_script = GetGameEngine()->GetGlobalNpc()->GetScript();

	//ScriptValueList vr;

	////调用脚本函数，期待返回1个值
	//if (!game_script.Call(fnName, &va, &vr, 1))
	//{
	//	//脚本错误，将以模态对话框的形式呈现给客户端
	//	const RefString& s = game_script.getLastErrorDesc();
	//	actor->SendTipmsg((const char*)s, ttDialog);
	//}
}

//void Npc::CloseDialog(Actor* actor)
//{
//#pragma pack(push, 1)
//	static struct Data
//	{
//		uint8_t sid_;
//		uint8_t pid_;
//		uint8_t succ_;
//		int64_t handle_;
//		Data(): sid_(enDefaultEntitySystemID), pid_(sNpcTalk), succ_(0) {}
//	} data;
//#pragma pack(pop)
//	data.handle_ = entity_handle_;
//
//	actor->SendData(&data, sizeof(data));
//}

void Npc::NPCTalk()
{
	static GameScript& game_script = GetGameEngine()->GetGlobalNpc()->GetScript();

	ScriptValueList paramList, retList;
	paramList << this;

	if (!game_script.Call("NPCTalk", &paramList, &retList, 0))
	{
		OutputMsg(rmError, "NPCTalk(%s) Failed...", GetEntityName());
	}
}


