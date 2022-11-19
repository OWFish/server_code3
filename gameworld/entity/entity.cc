#include "StdAfx.h"

#include "entity.h"
#include "game_engine.h"
#include "protocol/protos/base_proto.h"


Entity::Entity() : msg_timer_(&GameEngine::global_var_->time_caller_alloc_)
, dest_pos_(-1, -1)
, bit_state_(0)
, is_init_(false)
{
	entity_name_[0] = 0;

	entity_handle_ = 0;
	master_handle_ = 0;
	inited_ = false;
	target_handle_ = 0;
	target_npc_handle_ = 0;
	title_[0] = 0;
	maxFollowDistSqrt_ = 0;
	entity_node_ = NULL;
	killer_ = 0;
	origin_pos = Point(0,0);
	//use_teleport_ = true;
}

Entity::~Entity()
{
	entity_name_[0] = 0;
	inited_ = false;

	title_[0] = 0;

	//move_dest_x_ = move_dest_y_ = -1;
}

bool Entity::Init(void* data, size_t size)
{
	return true;
}

void Entity::OnDestroy()
{
	//dynamicVar_.clear();
	ClearAllActMsg();
}

void Entity::ClearAllActMsg()
{
	// 显式的调用一次，已确保所有的实体消息本清除掉
	msg_timer_.ClearAllCaller();

}

int64_t Entity::PostActMsg(ActMsg* msg, int64_t delay, bool callInDestroy,
                           int64_t interv, int count)
{
	int myType = GetType();

	if (myType == enTransfer) return 0;	// 传送门是不执行logicrun的，所以如果给传送门增加msg，会导致越来越多，相当于内存泄露

	int64_t ret = 0;
	static GameEngine* ge = GetGameEngine();

	msg->this_ = this;

	if (delay > 0)
	{
		delay += ge->getTickCount();
		ret = msg_timer_.AddTimeCaller(&S_ProcessActMsg, &FreeActMsg, (void*)msg, delay,
		                               count, interv, callInDestroy);
	}
	else
	{
		msg_timer_.AddNext(&S_ProcessActMsg, &FreeActMsg, (void*)msg, callInDestroy);
	}

	return ret;
}

////设置实体的方向
//void Entity::SetDir(int dir)
//{
//	if (attri_flag_.DenyTurnDir) return;
//
//	//如果是非法面向, 则随机面向
//	if (dir < 0 || dir >= DIR_STOP)
//	{
//		dir = wrand(100000) % DIR_STOP;
//	}
//
//	SetIntProp(P_DIR, dir);
//}

//int Entity::GetTargetDir(Entity* et)
//{
//	if (et == NULL || et == this) return DIR_STOP;
//
//	int x,  y;
//	et->GetPixPos(x, y); //目标的位置
//
//	int sx,  sy;
//	GetPixPos(sx, sy);
//
//	return Entity::GetDir(sx, sy, x, y);
//}

void Entity::SetEntityName(const char* name)
{
	if (name == NULL) return;

	_STRNCPY_A(entity_name_, name);

	//if ((GetType() == enMonster || GetType() == enGatherMonster) && !((Monster*)this)->IsActorModel() && !is_pet_ && !is_fightpet_) // 人形怪不用去掉
	//{
	//	size_t nLen = strlen(entity_name_);

	//	//这里屏蔽怪物的最后的数字
	//	if (nLen > 1 && entity_name_[nLen - 1] >= '0' && entity_name_[nLen - 1] <= '9')
	//	{
	//		entity_name_[nLen - 1] = 0;
	//	}

	//}

	//SetShowName(entity_name_);
}

//void Entity::SetTitle(char* name)
//{
//	if (name == NULL) return;
//
//	_STRNCPY_A(title_, name);
//}

Entity* Entity::GetTarget() const
{
	static EntityMgr *em = GetGameEngine()->GetEntityMgr();
	return em->GetEntity(target_handle_);
}


void Entity::SetTarget(Entity* target)
{
	if (!target)
	{
		target_handle_ = 0;
		return;
	}
	target_handle_ = target->GetHandle();
}

uint64_t Entity::GetSummitHandle() {
	auto hdl = GetHandle();
	return (uint64_t)hdl.GetType() << 32 | hdl.GetIndex();
}

//
//int Entity::GetDir(int x1, int y1, int x2, int y2)
//{
//	//return x1 > x2 ? DIR_LEFT : (x1 == x2 ? DIR_STOP : DIR_RIGHT);
//	int dir = DIR_UP;
//	int disX = x2 - x1;
//	int disY = y2 - y1;
//
//	if (disX > 0)
//	{
//		if (disY > 0)
//		{
//			dir = DIR_DOWN_RIGHT;
//		}
//		else if (disY == 0)
//		{
//			dir = DIR_RIGHT;
//		}
//		else
//		{
//			dir = DIR_UP_RIGHT;
//		}
//	}
//	else if (disX == 0)
//	{
//		if (disY > 0)
//		{
//			dir = DIR_DOWN;
//		}
//		else if (disY == 0)
//		{
//			dir = DIR_STOP;
//		}
//		else
//		{
//			dir = DIR_UP;
//		}
//	}
//	else
//	{
//		if (disY > 0)
//		{
//			dir = DIR_DOWN_LEFT;
//		}
//		else if (disY == 0)
//		{
//			dir = DIR_LEFT;
//		}
//		else
//		{
//			dir = DIR_UP_LEFT;
//		}
//	}
//
//	return dir;
//}
//
//
//bool Entity::Teleport(FuBen* fb, int sid, int x, int y)
//{
//	/*//只能在本副本内传送，不能跨副本
//	int ownerX, ownerY;
//	GetPosition(ownerX, ownerY);
//
//	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
//
//	bool bRet = mgr->EnterFuBen(this, fb, sid, x, y, -1, -1, true);
//
//	if (bRet && GetType() == enActor)
//	{
//		// 传送宝宝
//	}
//
//	return bRet;
//	*/
//	return false;
//}
//
//bool Entity::TelportSceneByName(const char* sSceneName, int nPosX, int nPosY)
//{
//	/*if (sSceneName == NULL)
//		return false;
//
//	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
//
//	Scene* pScene = GetScene();  // 场景指针
//
//	if (pScene && strcmp(sSceneName, pScene->GetSceneName()) == 0)//本身就在这个场景
//	{
//		return pScene->EnterScene(this, nPosX, nPosY);
//	}
//
//	FuBen* pFb = NULL;      // 副本的指针
//
//	if (mgr->GetFbPtrBySceneName(sSceneName, pFb, pScene))
//	{
//		if (pFb && pScene)
//		{
//			int nOwnerPosX, nOwnerPosY;
//			GetPosition(nOwnerPosX, nOwnerPosY);
//
//			FuBen* oldfb = GetFuBen();
//			bool bRet = pFb->Enter(this, pScene->GetSceneId(), nPosX, nPosY);
//
//			if (bRet && GetType() == enActor)
//			{
//				if (oldfb && oldfb != pFb)
//				{
//					((Actor*)this)->OnExitFuben(oldfb->GetFbId(), oldfb->GetHandle(), xfwTeleport);
//				}
//
//				((Actor*)this)->PostTeleportOwnedEntity(pFb, pScene->GetSceneId(), nPosX, nPosY, nOwnerPosX, nOwnerPosY, etsOther);
//			}
//
//			return bRet;
//		}
//	}
//
//	OutputMsg(rmWaning, (" TelportSceneByName fail, no sSceneName =%s"), sSceneName);
//	return false;
//	*/
//	return false;
//}
//
////传送到场景的默认点
//bool Entity::TelportSceneDefaultPoint(const char* sSceneName, int nPointID)
//{
//	/*FuBen* pFb = NULL;     //副本的指针
//	Scene* pScene = NULL;  //场景指针
//	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
//
//	if (mgr->GetFbPtrBySceneName(sSceneName, pFb, pScene))
//	{
//		if (pFb && pScene)
//		{
//			int nPosX = 0;
//			int nPosY = 0;
//
//			if (pScene->GetAreaCenter(nPosX, nPosY, nPointID) == false)
//			{
//				OutputMsg(rmWaning, ("No default point in the scene"));
//				return false;
//			}
//
//			int nOwnerPosX, nOwnerPosY;
//			GetPosition(nOwnerPosX, nOwnerPosY);
//
//			FuBen* oldfb = GetFuBen();
//			bool bRet = pFb->Enter(this, pScene->GetSceneId(), nPosX, nPosY);
//
//			if (bRet && GetType() == enActor)
//			{
//				if (oldfb && oldfb != pFb)
//				{
//					((Actor*)this)->OnExitFuben(oldfb->GetFbId(), oldfb->GetHandle(), xfwTeleport);
//				}
//
//				((Actor*)this)->PostTeleportOwnedEntity(pFb, pScene->GetSceneId(), nPosX, nPosY, nOwnerPosX, nOwnerPosY, etsOther);
//			}
//
//			return bRet;
//		}
//	}
//
//	OutputMsg(rmWaning, (" TelportSceneDefaultPoint fail, no sSceneName =%s,pointID=%d"), sSceneName, nPointID);
//	return false;
//	*/
//	return false;
//}

void Entity::BeforeLogicRun(int64_t curr_t)
{
}

void Entity::LogicRun(int64_t curr_t)
{
	msg_timer_.Run(curr_t);
}

void Entity::AfterLogicRun(int64_t curr_t)
{
}

//bool Entity::IsInSameScreen(Entity* et)
//{
//	return false;
//	/*
//	if (!et) return false;
//
//	if (GetScene() != et->GetScene()) return false;
//
//	int myX = 0, myY = 0;
//	GetPosition(myX, myY);
//
//	int youX = 0, youY = 0;
//	et->GetPosition(youX, youY);
//
//	return IsSameScreen(myX, myY, youX, youY);
//	*/
//}

bool Entity::DelActMsgOnDeath(void* data)
{
	ActMsg* msg = (ActMsg*)data;
	return msg->delOnDeath_;
}

void Entity::OnEntityDeath(EntityHandle killer)
{
	/*msg_timer_.RemoveAllIf(&DelActMsgOnDeath);

	//加到死亡列表中
	Scene* sc = GetScene();

	if (sc)
	{
		sc->AddDeathEntity(this);
	}
	*/
}

void Entity::OnEnterScene()
{
	SetTarget(NULL);	// 清掉目标，
}

int64_t Entity::PostScriptEvent(int64_t delay, int64_t interval, int count,
                                const char* func, const ScriptValueList& args)
{
	SEventHandle scbhandle;
	int64_t ret = 0;
	static GameEngine* ge = GetGameEngine();

	if (!func) return 0;

	if (count <= 0) count = 1;

	ScriptEvent* sp = ge->AllocScriptEvent(scbhandle);

	if (!sp) return 0;

	AMScriptEvent* msg = AMScriptEvent::alloc();
	sp->handle_ = scbhandle;
	sp->args_ << this;
	sp->args_ += args;
	_STRNCPY_A(sp->fn_, func);


	msg->sp_ = (void*)sp;

	if (delay > 0 || count > 1)
	{
		delay += ge->getTickCount();
		ret = msg_timer_.AddTimeCaller(&S_ProcessActMsg, &FreeActMsg, (void*)msg, delay,
		                               count, interval, false);
	}
	else
	{
		msg_timer_.AddNext(&S_ProcessActMsg, &FreeActMsg, (void*)msg);
	}

	return ret;
}

void Entity::CancelScriptTimer(int64_t handle)
{
	msg_timer_.RemoveTimeCaller(handle);
}

void Entity::PostEntityDeadMsg()
{
	AMCommon* msg = AMCommon::alloc();
	msg->msg_ = AMCommon::AMDEAD;
	msg->delOnDeath_ = true;
	msg->sender_ = killer_;
	PostActMsg(msg, 0, true);
}
//
//bool Entity::CanSee(Entity* et)
//{
//	return true;
//	/*if (!et) return false;
//
//	if (et->GetScene() != this->GetScene()) return false;
//
//	bool canSee = true;
//
//	if (attri_flag_.CanSeeHideActor) return true; //如果能看到隐身的，就返回true
//
//	int myType = GetType();
//	int etType = et->GetType();
//
//	if (et->isAnimal())
//	{
//		//如果目标不可见的话
//		if (et->GetAttriFlag().DenySee && myType == enActor)
//			return false;
//
//		if (myType == enActor && (etType == enActor || et->IsPet()))
//		{
//			Actor* me = (Actor*)this;
//			Actor* other = NULL;
//			if (et->IsPet()&& !et->is_fightpet_)
//			{
//				other = ((Monster*)et)->GetMaster();
//				if (!other) return false;
//				if(me == other)
//					return true;
//			}
//			else if (etType == enActor)
//			{
//				other = (Actor*)et;
//			}
//
//			if (me->deny_see_actor_ || !me->can_see_ || (other && !other->can_see_))
//			{
//				return false;
//			}
//		}
//		else if (etType == enMonster && myType == enActor)
//		{
//			Monster* monster = (Monster*)et;
//			if (monster->quest_owner_)
//			{
//				if (monster->quest_owner_ == GetHandle())
//					return true;
//				else
//					return false;
//			}
//		}
//		if (((Animal*)et)->GetBuffSystem().Exists(bHide))
//		{
//			canSee = false;
//
//			//能看到队友
//			if (myType == enActor && etType == enActor)
//			{
//				Team* team = ((Actor*)this)->GetCurrentTeam();
//
//				if (team != NULL && team == ((Actor*)et)->GetCurrentTeam())
//				{
//					return true;
//				}
//			}
//
//			//宝宝能够看到他的主人
//			else if (myType == enMonster && etType == enActor)
//			{
//				if (((Monster*)this)->GetOwner() == et->GetHandle())
//				{
//					return true;
//				}
//			}
//
//			else if (myType == enActor && etType == enMonster)
//			{
//				// 主人能看见宠物和拥有的怪物
//				if (this == ((Monster*)et)->GetMaster() || GetHandle() == ((Monster*)et)->GetOwner())
//				{
//					return true;
//				}
//			}
//		}
//		else
//		{
//			// 如果宠物的主人隐身，其他人也看不到宠物
//			if (myType == enActor && etType == enMonster)
//			{
//				Actor* actor = ((Monster*)et)->GetMaster();
//
//				if (this == actor)
//				{
//					return true;
//				}
//
//				if (actor && actor->GetBuffSystem().Exists(bHide))
//				{
//					Team* team = ((Actor*)this)->GetCurrentTeam();
//					return team != NULL && team == ((Actor*)actor)->GetCurrentTeam();
//				}
//			}
//		}
//	}
//	else if (etType == enDropBag && myType == enActor)
//	{
//		Actor* actor = (Actor*)this;
//		ActorId aid = actor->GetActorId();
//		DropBag* bag = (DropBag*)et;
//		Scene* scene = actor->GetScene();
//
//		if (!scene) return false;
//
//		SceneConfig* sceneConf = scene->GetSceneConf();
//
//		if (aid != bag->killer_id_ && sceneConf && !sceneConf->cansee_other_drop_)
//		{
//			canSee = false;
//		}
//
//	}
//
//	return canSee;
//	*/
//}


//
//void Entity::SetAttriFlag(const EntityFlags flag)
//{
//	attri_flag_ = flag;
//
//	if (isAnimal())
//	{
//		Animal* an = (Animal*)this;
//
//		if (flag.DenyBeAttack)
//			an->AddState(esStateAttackedForbid);
//		else
//			an->RemoveState(esStateAttackedForbid);
//
//		if (flag.DenySee)
//		{
//			an->AddState(esStateHide);
//			//通知隐身
//			AMCommon* msg = AMCommon::alloc();
//			msg->msg_ = AMCommon::AMHIDE;
//			msg->delOnDeath_ = true;
//			an->PostActMsg(msg);
//		}
//		else
//		{
//			//加入当前状态判断
//			if (an->HasState(esStateHide))
//			{
//				an->RemoveState(esStateHide);
//				//通知现身
//				an->CollectOperate(EntityOPCollector::coEndHide);
//			}
//		}
//	}
//}


//void Entity::OnHpChange(const int oldValue, const int value)
//{
//	if (!isAnimal()) return;
//
//	Animal* animal = (Animal*)this;
//
//	if (value == 0)
//	{
//		animal->AddState(esStateDeath);
//		PostEntityDeadMsg();
//	}
//	else if (oldValue == 0)
//	{
//		if (animal->HasState(esStateDeath))
//		{
//			animal->RemoveState(esStateDeath);
//		}
//	}
//
//	if ((animal->GetType() != enNpc && value == 0) || (oldValue == 0 && animal->GetType() == enActor))
//	{
//		animal->PostCheckPropertyMsg();
//	}
//}
//
//void Entity::SetStoneEffect(int id)
//{
//	//SetIntProp(P_STONE_EFFECT, id);
//}
//
//void Entity::SetStageEffect(int id)
//{
//	SetIntProp(P_STAGE_EFFECT, id);
//}
//
//void Entity::SetStrongEffect(int id)
//{
//	SetIntProp(P_STRONG_EFFECT, id);
//}
//
//bool Entity::IsPet()
//{
//	return (GetType() == enMonster && is_pet_);
//}
//

void Entity::FreeActMsg(void* data)
{
	ActMsg* msg = (ActMsg*)data;
	msg->free();
}

void Entity::S_ProcessActMsg(void* data, int* count)
{
	ActMsg* msg = (ActMsg*)data;
	msg->process();
}

//获取一个bool 标记位，免得写很多垃圾代码
inline bool GetBitFlag(unsigned int val, int bit) { return (val & (0x1 << bit)) ? true : false; }
//设置一个bit位
inline unsigned int SetBitFlag(unsigned int& val, int bit, bool flag)
{
	unsigned int newValue;

	if (flag)
	{
		newValue = (unsigned int)(0x1 << bit);
		val |= newValue;
	}
	else
	{
		newValue = (unsigned int)(~(0x1 << bit));
		val &= newValue;
	}

	return val;
}

bool Entity::HasBitState(int sid)
{
	if (sid < 0 || sid >= ebsMaxStateCount) return false;

	return GetBitFlag(bit_state_, sid);
}

bool Entity::InSafeArea() {
	auto scene = GetScene();
	if (scene) {
		return scene->HasAreaAttr(aaSaft, GetPosition());
	}
	return false;
}

bool Entity::AddBitState(int sid)
{
	if (sid < 0 || sid >= ebsMaxStateCount) return false;

	if (HasBitState(sid)) return false;  //已经有这个状态了

	SetBitFlag(bit_state_, sid, true);

	return true;
}

bool Entity::RemoveBitState(int sid)
{
	if (sid < 0 || sid >= ebsMaxStateCount) return false;

	if (!HasBitState(sid)) return false;   //没有这个状态

	SetBitFlag(bit_state_, sid, false);

	return true;
}

void Entity::CreateAppearData(DataPacket& appearPack)
{
	appearPack.setLength(0);
	static Protocol::EntityAppearProto msg;
	msg.Reset();

	msg.hdl = GetHandle();
	msg.type = GetType();
	msg.id = GetId();
	msg.master_hdl = GetMasterHandle();
	const Point &pos = GetPosition();
	msg.x = pos.x;
	msg.y = pos.y;
	int headID = GetHeadID();
	msg.headimageid = headID;

	appearPack.writeBuf(&msg, sizeof(msg));
}

//void Entity::OnPropertyChange(int pid, int oldVal, int newVal)
//{
	/*switch (pid)
	{
	case P_SPEED:
		if (isAnimal())
		{
			((Animal*)this)->CollectOperate(EntityOPCollector::coSpeed);
		}
		break;

	case P_HP:
		OnHpChange(oldVal, newVal);
		break;
	
	case P_MAXHP:
		OnMaxHpChange(oldVal, newVal);
		break;

	case P_ATTACK_SPEED:
		//重新计算技能cd
		if (isAnimal())
		{
			((Animal*)this)->GetSkillSystem().ReCalcSkillCd(oldVal, newVal);
		}
		break;

	default:
		break;
	}
	*/
//}

Entity* Entity::GetMaster()
{
	return GetGameEngine()->GetEntityMgr()->GetEntity(master_handle_); 
}

