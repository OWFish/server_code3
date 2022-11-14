#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

#define BASELOGICDEF(X,list) \
						ObjPool<X, 16>* list;\
						X* X::alloc()\
						{\
							return list->Alloc();\
						}\
						void X::free()\
						{\
							list->Free(this);\
						}

#define BASELOGICDEFNOFREE(X,list) \
						ObjPool<X, 16>* list;\
						X* X::alloc()\
						{\
						return list->Alloc();\
						}

#define INITACTMSGMEMPOOL(X, list, name) list = new ObjPool<X, 16>(name);
#define RELEASEACTMSGMEMPOOL(list) delete list;

BASELOGICDEF(AMSkillResult, AMSkillResult_List);
BASELOGICDEFNOFREE(AMScriptEvent, AMScriptEvent_List);
BASELOGICDEF(AMEntityEffect, AMEntityEffect_List);
BASELOGICDEF(AMCommon, AMCommon_List);
BASELOGICDEF(AMCreateMonster, AMCreateMonster_List);
BASELOGICDEF(AMTeleportBaby, AMTeleportBaby_List);
BASELOGICDEF(AMMjUseSkill, AMMjUseSkill_List);
BASELOGICDEF(AMMarkerEffect, AMMarkerEffect_List);
BASELOGICDEF(AMUseSKill, AMUseSkill_List);
BASELOGICDEF(AMJump, AMJump_List);

void InitActMsgMemPool()
{
	INITACTMSGMEMPOOL(AMSkillResult, AMSkillResult_List, "AMSkillResult_List");
	INITACTMSGMEMPOOL(AMScriptEvent, AMScriptEvent_List, "AMScriptEvent_List");
	INITACTMSGMEMPOOL(AMEntityEffect, AMEntityEffect_List, "AMEntityEffect_List");
	INITACTMSGMEMPOOL(AMCommon, AMCommon_List, "AMCommon_List");
	INITACTMSGMEMPOOL(AMCreateMonster, AMCreateMonster_List, "AMCreateMonster_List");
	INITACTMSGMEMPOOL(AMTeleportBaby, AMTeleportBaby_List, "AMTeleportBaby_List");
	INITACTMSGMEMPOOL(AMMjUseSkill, AMMjUseSkill_List, "AMMjUseSkill_List)");
	INITACTMSGMEMPOOL(AMMarkerEffect, AMMarkerEffect_List, "AMMarkerEffect_List");
	INITACTMSGMEMPOOL(AMUseSKill, AMUseSkill_List, "AMUseSKill_List");
	INITACTMSGMEMPOOL(AMJump, AMJump_List, "AMJump_List");
}

void ReleaseActMsgMemPool()
{
	RELEASEACTMSGMEMPOOL(AMSkillResult_List);
	RELEASEACTMSGMEMPOOL(AMScriptEvent_List);
	RELEASEACTMSGMEMPOOL(AMEntityEffect_List);
	RELEASEACTMSGMEMPOOL(AMCommon_List);
	RELEASEACTMSGMEMPOOL(AMCreateMonster_List);
	RELEASEACTMSGMEMPOOL(AMTeleportBaby_List);
	RELEASEACTMSGMEMPOOL(AMMjUseSkill_List);
	RELEASEACTMSGMEMPOOL(AMMarkerEffect_List);
	RELEASEACTMSGMEMPOOL(AMUseSkill_List);
	RELEASEACTMSGMEMPOOL(AMJump_List);
}

void AMSkillResult::process()
{
	/*static EntityMgr* em = GetGameEngine()->GetEntityMgr();

	if (!this_->isAnimal()) return;

	Animal* self = (Animal*)this_;

	SKILLRESULTPARAM skillParam; //技能的参数
	skillParam = ret_;

	skillParam.target_ = self;
	skillParam.src_ = (Animal*)em->GetEntity(sender_);

	if (skillParam.src_ == NULL) return; //已经需要删除了

	MijiEffect mj_info(skillParam.skillid_, skillParam.src_);

	//skillParam.skillid_ = param1_;
	//skillParam.target_x_ = param2_;
	//skillParam.target_y_ = param3_;
	//skillParam.skill_ret_ = (SKILLRESULT*)param4_;
	//skillParam.forceHit_ = param5_;
	//skillParam.criticalDamgeAdd_ = param6_;

	//skillParam.mj_info_ = &mj_info;

	SkillResult& result = self->GetSkillSystem().GetSkillResult();
	result.DoResult(&skillParam, true); //无延迟立刻执行
	*/
}

void AMScriptEvent::process()
{
	ScriptEvent* p = (ScriptEvent*)sp_;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();

	if (!luaScript.Call(p->fn_, &p->args_, NULL, 0))
	{
		OutputMsg(rmError, "OnEntityScriptCallbackMsg error:(%s)", p->fn_);
	}
}

void AMScriptEvent::free()
{
	static GameEngine* ge = GetGameEngine();
	ScriptEvent* p = (ScriptEvent*)sp_;
	ge->FreeScriptEvent((SEventHandle&)(p->handle_));
	AMScriptEvent_List->Free(this);
}

void AMEntityEffect::process()
{
	//if (!this_->isAnimal()) return;

	//Animal* self = (Animal*)this_;

	//if (type_ == efEntity)
	//{
	//	if (target_ == 0)
	//	{
	//		self->AppendEffectToEntity(sender_, type_, eid_, time_);
	//	}
	//	else
	//	{
	//		static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	//		Entity* et = em->GetEntity(target_);

	//		if (et && et->isAnimal())
	//		{
	//			((Animal*)et)->AppendEffectToEntity(sender_, type_, eid_, time_);
	//		}
	//	}
	//}
	//else if (type_ == efScreen)
	//{
	//	self->AppendEffectToScreen(type_, eid_, time_, ex_, ey_, sender_);
	//}
}

void AMCommon::process()
{
//	if (!this_->isAnimal()) return;
//
//	Animal* self = (Animal*)this_;
//
//	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
//
//	switch (msg_)
//	{
//	case AMHPCHANGE:
//		self->ChangeHP((int)val_, true, em->GetEntity(sender_));
//		break;
//
//	case AMQUESTSTATE:
//		/*if (!this_->isNPC()) return;
//
//		if (sender_.GetType() == enActor)
//		{
//		Entity* sender = em->GetEntity(sender_);
//
//		if (sender)
//		((Actor*)sender)->GetQuestSystem().SendNpcQuestState((Npc*)this_);
//		}
//		*/
//		break;
//
//	case AMREUSE:
//		self->Reuse();
//		break;
//
//	case AMTRANSFER:
//		//int x, y;
//		/*self->GetPixPos(x, y);
//		self->GetMoveSystem().BroadcastMove(x, y, false, val_ ? true : false);
//		*/
//		break;
//
//	case AMDEAD:
//		self->OnEntityDeath(sender_);
//		break;
//
//	case AMHIDE:
//	{
//				   /*	Scene* scene = self->GetScene();
//
//					   if (scene) scene->BroadcastDisappear(self, true);
//
//					   if (self->GetType() == enActor)
//					   {
//					   Entity::BabyList& list = ((Actor*)self)->GetOwnedBabyList();
//
//					   for (int i = list.count() - 1; i >= 0; i--)
//					   {
//					   Entity* et = em->GetEntity(list[i].handle_);
//
//					   if (et && et->GetType() == enMonster)
//					   {
//					   scene = et->GetScene();
//
//					   if (scene) scene->BroadcastDisappear(et, true);
//					   }
//					   }
//					   }
//					   }*/
//
//				   break;
//
//	case AMSPEED:
//		/*if (self->GetType() == enMonster)
//		{
//		((Monster*)self)->GetMoveSystem().OnSpeedChange();
//		}
//		*/
//
//		break;
//
//	case AMNPCTALK:
//		if (self->GetType() == enActor)
//		{
//			((Actor*)self)->NpcTalk(sender_, "");
//		}
//
//		break;
//
//	case AMSEDNHPCHANGE:
//	{
//#pragma pack(push, 1)
//						   static struct Data
//						   {
//							   uint8_t sid_;
//							   uint8_t pid_;
//							   int64_t src_;
//							   int64_t handle_;
//							   int hp_;
//							   Data() : sid_(enDefaultEntitySystemID), pid_(sSendHpChange) {}
//						   } data;
//#pragma pack(pop)
//
//						   if (self->GetType() == enActor)
//						   {
//							   Actor* actor = (Actor*)self;
//							   data.hp_ = (int)val_;
//							   data.handle_ = (int64_t)target_;
//							   data.src_ = (int64_t)sender_;
//							   actor->SendData(&data, sizeof(data));
//						   }
//	}
//
//		break;
//
//	case AMSENDCRITICAL:
//	{
//#pragma pack(push, 1)
//						   static struct Data
//						   {
//							   uint8_t sid_;
//							   uint8_t pid_;
//							   uint64_t handle_;
//							   uint64_t src_hdl_;
//							   int hp_;
//							   Data() : sid_(enSkillSystemID), pid_(sCriticalAttack) {}
//						   } data;
//#pragma pack(pop)
//						   data.hp_ = (int)val_;
//						   data.handle_ = target_;
//						   data.src_hdl_ = sender_;
//
//						   if (self->GetType() == enActor)
//						   {
//							   ((Actor*)self)->SendData((char *)&data, sizeof(data));
//						   }
//	}
//		break;
//
//	case AMREFRESHPET:
//		/*if (self->GetType() == enActor)
//		{
//		Actor* actor = (Actor*)self;
//		actor->GetPetSys().RefreshPetAttri();
//		}
//		*/
//
//		break;
//
//	case AMFULLHP:
//		self->SetIntProp(P_HP, self->GetIntProp(P_MAXHP));
//		break;
//
//	case AMPETBATTLE:
//		/*if (self->GetType() == enActor)
//		{
//		((Actor*)self)->GetPetSys().Battle();
//		}
//		*/
//
//		break;
//
//	case AMACCEPTREFRESHQUEST:
//		/*if (self->GetType() == enActor)
//		{
//		Actor* actor = (Actor*)self;
//		actor->GetQuestSystem().ShowAcceptRefresh();
//		}
//		*/
//
//		break;
//
//	case AMFINISHITEMQUEST:
//		/*if (self->GetType() == enActor)
//		{
//		Actor* actor = (Actor*)self;
//		actor->GetQuestSystem().OnQuestEvent(QuestData::qtCollect, (int)val_, (int)target_, FALSE);
//		}
//		*/
//
//		break;
//	case AMADDBABY:
//		/*if (self->GetType() == enActor)
//		{
//		Actor* actor = (Actor*)self;
//		actor->AddBaBy(target_);
//		}
//		*/
//
//		break;
//
//	case AMSENDCOLORCHANGE:
//		/*{
//#pragma pack(push, 1)
//			static struct Data
//			{
//			uint8_t sid_;
//			uint8_t pid_;
//			int64_t handle_;
//			unsigned int rgb_;
//			Data(): sid_(enDefaultEntitySystemID), pid_(sUpdateActorNameClr) {}
//			} data;
//
//			#pragma pack(pop)
//
//			data.handle_ = sender_;
//			data.rgb_ = (unsigned int)val_;
//			self->GetObserverSystem().BroadCast((char*)&data, sizeof(data), true);
//			}
//			*/
//
//		break;
//
//	case AMREFRESHFIGHTVAL:
//		/*if (self->GetType() == enActor)
//		{
//		Actor* actor = (Actor*)self;
//		actor->GetGuildSystem().OnLoginDelay();
//		}
//		*/
//
//		break;
//
//	case AMJUMPSKILL:
//		/*if (self->GetType() == enActor)
//		{
//		Actor* actor = (Actor*)self;
//		actor->GetMoveSystem().SetJumping(false);
//		}
//		*/
//		break;
//
//	}
//	}
}

void AMCreateMonster::process()
{
	/*if (!this_->isAnimal()) return;

	Animal* self = (Animal*)this_;
	Scene* scene = ((Entity*)self)->GetScene();

	if (!scene) return;

	if (posX2_ < posX1_)
		posX2_ = posX1_;

	if (posY2_ < posY1_)
		posY2_ = posY1_;

	int dx = posX2_ - posX1_;
	int dy = posY2_ - posY1_;
	const static MonsterConfPool& pool = *MonsterConfPool::config_;
	MONSTERCONFIG* conf = pool.GetMonsterData(monsterid_);

	if (conf)
	{
		for (int i = 0; i < count_; i++)
		{
			int px = wrand(dx + 1);
			int py = wrand(dy + 1);

			Entity* monster =
			    scene->CreateEntityAndEnter(monsterid_, conf->btEntityType, posX1_ + px, posY1_ + py);

			if (monster != NULL)
			{
				//scene->SetMonsterConfig(monster, -1, monsterid_);
				((Monster*)monster)->SetLiveTIme(liveTime_);
			}
		}
	}

	// TODO:因为调用哪个NPC脚本还不确定，这个先注释掉，具体用到的时候再处理
	//if (callback_ && self->isNPC())	// 是否需要触发脚本
	//{
	//	Npc* npc = (Npc*)this;
	//	ScriptValueList paramList, retList;
	//	paramList << monsterid_;
	//	paramList << param_;

	//	if (!npc->GetScript().Call("OnCreateMonsters", &paramList, &retList, 0))
	//	{
	//		OutputMsg(rmError, ("OnCreateMonsters(%s) Failed..."), self->GetEntityName());
	//	}
	//}
	*/
}

void AMTeleportBaby::process()
{
	/*if (!this_->isAnimal()) return;

	Animal* self = (Animal*)this_;

	if (self->GetType() == enActor)
	{
		static FuBenMgr* fbMgr = GetGameEngine()->GetFuBenMgr();
		Actor* actor = (Actor*)self;
		FuBen* fb = fbMgr->GetFubenPtr((unsigned int)(sender_));

		if (fb)
		{
			actor->TeleportOwnedEntity(fb, sceneID_, posX_, posY_, ownerPosX_, ownerPosY_, transStype_);
		}
	}*/
}

void AMJump::process()
{
	/*if (this_->GetType() != enActor) return;

	Actor* actor = (Actor*)this_;

	//跳跃前删除磁铁的buff。。。
	actor->GetBuffSystem().RemoveByType(bMagnet, AnyBuffGroup);

	actor->GetMoveSystem().InstantMove(pos_x, pos_y, true);
	*/
}

void AMMjUseSkill::process()
{
	/*if (!this_->isAnimal()) return;

	Animal* self = (Animal*)this_;

	if (pet_)
	{
		if (self->GetType() == enActor)
		{
			Actor* actor = (Actor*)self;
#pragma pack(push, 1)
			static struct Data
			{
				uint8_t sid_;
				uint8_t pid_;
				uint8_t flag_;
				int id_;
				int para1_;
				Data(): sid_(enSkillSystemID), pid_(sPetUseSkillEff) {}
			} data;
#pragma pack(pop)
			data.id_ = p1_;
			data.para1_ = p2_;
			data.flag_ = p3_;

			actor->SendData(&data, sizeof(data));
		}
	}
	else
	{
		self->SetTarget(sender_);
		self->GetSkillSystem().UseSkill(p1_, p3_, p4_, false, p2_);
	}
	*/
}

void AMMarkerEffect::process()
{
	/*if (!this_->isAnimal()) return;

	Animal* self = (Animal*)this_;

	if (self->GetType() != enActor) return;

#pragma pack(push, 1)
	static struct Data
	{
		uint8_t sid_;
		uint8_t pid_;
		uint64_t sender_;
		uint64_t handle_;
		uint8_t param1_; //暂时不需要
		int param2_;
		unsigned int param3_;
		Data(): sid_(enDefaultEntitySystemID), pid_(sAddEffect) {}
	} data;
#pragma pack(pop)
	data.sender_ = sender_;
	data.handle_ = self->GetHandle();
	data.param1_ = (uint8_t)p1_;
	data.param2_ = p2_; //特效的类型以及ID
	data.param3_ = (unsigned int)(p3_ < 0 ? MAX_INT : p3_);	// 持续时间

	EntityMgr* em = GetGameEngine()->GetEntityMgr();
	Entity* sender = em->GetEntity(sender_);

	if (!sender || sender->GetType() != enActor) return;

	Actor* actors[2] = {(Actor*)self, (Actor*)sender};

	for (int i = 0; i < 2; i++)
	{
		actors[i]->SendData(&data, sizeof(data));
	}
	*/
}

void AMUseSKill::process()
{
	/*
	if (!this_->isAnimal()) return;
	Animal* self = (Animal*)this_;
	SkillSystem& sys = self->GetSkillSystem();
	if (skill_id_ != sys.GetCurrSkill()) return;

	if (!no_fix_target_)
	{	
		self->SetTarget(target_);
	}
	
	if (x_ == -1)
	{
		self->GetPosition(x_, y_);
	}
	// 这种技能是不消耗，且不判断条件的
	sys.UseSkill(skill_id_, x_, y_, needLearn_, level_);
	sys.ReleaseCurr();
	*/
}

#undef BASELOGICDEF
#undef BASELOGICDEFNOFREE


