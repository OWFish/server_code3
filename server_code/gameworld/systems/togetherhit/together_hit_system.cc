#include "StdAfx.h"
#include "together_hit_system.h"
#include "db/actor_db_data.h"
#include "item/item_pool.h"
#include "item/container/equip_bag.h"
#include "protocol/protos/skill_proto.h"

TogetherHitSystem::TogetherHitSystem(Actor* actor)
: actor_(actor)
, together_hit_equip_()
{
	ex_attribute_.Reset();
	attribute_.Reset();
	punch_attribute_.Reset();
	punch_ex_attribute_.Reset();
	memset(&together_hit_equip_data, 0, sizeof(together_hit_equip_data));
	need_save_ = false;
	init_finish_ = false;
}

TogetherHitSystem::~TogetherHitSystem()
{
	for (int i = 0; i < TogetherHitSlotType_Max; ++i)
	{
		SafeDelete(together_hit_equip_[i]);
	}
}

bool TogetherHitSystem::Init(DataPacketReader &data)
{
	if (!actor_) return false;

	if (!actor_->CheckInitStep(Actor::InitFlagType_Basic))
	{
		OutputMsg(rmError, "init order error. on init together hit.");
		return false;
	}
	if (actor_->CheckInitStep(Actor::InitFlagType_TogetherHit))
		return true;
	if (init_finish_) return true;
	AddTogetherHitEquipAttr();
	//判断数据大小
	if (data.getAvaliableLength() > 0)
	{//没有数据的时候
		if (data.getAvaliableLength() < sizeof(together_hit_equip_data))
		{
			OutputMsg(rmError, "Init together hit equip data failed. data length is wrong;%d, count:%d",
				data.getAvaliableLength(), sizeof(together_hit_equip_data));
			return false;
		}

		data >> together_hit_equip_data;
		bool have_equip = false;
		for (int i = 0; i < TogetherHitSlotType_Max; ++i)
		{
			ItemData* item_data = &(together_hit_equip_data.together_hit_slot[i].equip_data);
			if (item_data->uid != 0)
			{
				together_hit_equip_[i] = (Equip*)ItemPool::instance().CreateItem(item_data);
				have_equip = true;
			}
		}
		if(have_equip) 
		{
			AddTogetherHitEquipAttr();
			actor_->ReCalcAttr();
			actor_->ReCalcExAttr();
		}
	}
	init_finish_ = true;
	actor_->OnFinishInitStep(Actor::InitFlagType_TogetherHit);
	/*
	ScriptValueList arg;
	arg << actor_;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("TogetherHitInit", &arg, &arg, 0);
	*/
	return true;
}

void TogetherHitSystem::Save(ActorBasicData* data, bool force)
{
	if (!actor_) return;

	DBClient* db = ServerInstance()->GetDbClient(actor_->GetServerId());
	if (!db) return;

	if (!force && !need_save_) return;

	DataPacket& pack = db->allocProtoPacket(MAKEINT16(siActor, dcSaveTogHitEquip));
	pack << (ActorId)actor_->GetActorId();
	pack << together_hit_equip_data;
	db->flushProtoPacket(pack);
	OutputMsg(rmTip, "-------------------------------SaveTogetherHitEquip:actor:%d", actor_->GetActorId());

	need_save_ = false;
}

void TogetherHitSystem::Destroy()
{
}

bool TogetherHitSystem::EquipTogetherHitItem(Equip *item, short slot)
{
	if (!item) return false;
	if (item->GetType() != ItemType_TogetherHit)
		return false;

	if (slot != item->GetSubType())
		return false;

	Equip* old = together_hit_equip_[slot];

	if (item->GetUseCond() && (!old || old->GetId() != item->GetUseCond())) 
		return false;

	together_hit_equip_[slot] = item;
	item->WriteData(&together_hit_equip_data.together_hit_slot[slot].equip_data);
	NotifyUpdateEquip(slot, item);

	EquipBag* equip_bag = actor_->GetEquipBag();
	equip_bag->TakeOutItem(item);
	SafeDelete(old);
	//if (old)
		//equip_bag->AddItem(old, true, false);

	AddTogetherHitEquipAttr(true);
	actor_->ReCalcAttr();
	actor_->ReCalcExAttr();

	need_save_ = true;
	return true;
}

void TogetherHitSystem::AddTogetherHitEquipAttr(bool isEquip)
{
	ex_attribute_.Reset();
	attribute_.Reset();
	std::map<int, int> eq_lv_num;//装备等级对应数量
	for (int i = 0; i < TogetherHitSlotType_Max; ++i)
	{
		Equip* equip = together_hit_equip_[i];
		if(!equip)
			continue;
		int lv = equip->GetZhuanShengLevel() * 10000 + equip->GetLevel();
		++eq_lv_num[lv];
		equip->AddExAttr(ex_attribute_);
		equip->AddAttr(attribute_);
	}
	ScriptValueList arg;
	arg << actor_;
	arg << isEquip;
	arg << eq_lv_num.size();
	for (auto it = eq_lv_num.begin(); it != eq_lv_num.end(); ++it)
	{
		arg << it->first + it->second * 10000000;//参数最大16个
	}
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("togetherHitQmAttr", &arg, &arg, 0);
}

void TogetherHitSystem::TogetherHitInfoSync()
{
	if (!actor_) return;
	static Protocol::TogetherHitEquipProto msg;
	for (int i = 0; i < TogetherHitSlotType_Max; ++i)
		msg.equip[i] = together_hit_equip_data.together_hit_slot[i].equip_data;
	actor_->SendData(msg);
}

void TogetherHitSystem::NotifyUpdateEquip(int slot, Equip* item)
{
	if (!actor_ || !item) return;
	static Protocol::TogetherHitEquipItemProto msg;
	msg.slot = slot;
	item->WriteData(&msg.equip);
	actor_->SendData(msg);
}

void TogetherHitSystem::setTogetHerEquipLevel(int pos, int lv) {
	if (pos < 0 || pos >= TogetherHitSlotType_Max) return;
	together_hit_equip_data.together_hit_slot[pos].strength_lv = lv;
	need_save_ = true;
}
