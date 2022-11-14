#include "StdAfx.h"
#include "attrs_system.h"

AttrsSystem::AttrsSystem(Role* role) : role_(role)
{
	for (int i = asStart; i < asCount; ++i) {
		base_attr_[i].Reset();
		//exa_attr_[i].Reset();
	}
}

AttrsSystem::~AttrsSystem()
{

}
/*
bool ShenBingSystem::Init(RoleData* data)
{
	if (data == NULL)
		return false;

	ScriptValueList arg;
	arg << role_->GetActor();
	arg << role_->GetId();
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("miscSystemInit", &arg, &arg, 0);
	return true;
}
*/

void AttrsSystem::ClearBaseAttr(AttrSystemId attrSysId)
{
	if (attrSysId < asStart || attrSysId >= asCount) return;
	base_attr_[attrSysId].Reset();
}
/*
void AttrsSystem::ClearExaAttr(AttrSystemId attrSysId)
{
	if (attrSysId < asStart || attrSysId >= asCount) return;
	exa_attr_[attrSysId].Reset();
}
*/
void AttrsSystem::AddBaseAttr(AttrSystemId attrSysId, int type, int value)
{
	if (attrSysId <= asStart || attrSysId >= asCount) return;
	if (type < Attribute::atHp || type >= Attribute::atCount) return;
	base_attr_[attrSysId][type] += value;
}
/*
void AttrsSystem::AddExaAttr(AttrSystemId attrSysId, int type, int value)
{
	if (attrSysId <= asStart || attrSysId >= asCount) return;
	if (type < ExAttribute::eatReflectProbability || type >= ExAttribute::eatCount) return;
	exa_attr_[attrSysId][type] += value;
}
*/
void AttrsSystem::AddExaPower(AttrSystemId attrSysId, int value)
{
	if (attrSysId <= asStart || attrSysId >= asCount) return;
	base_attr_[attrSysId].AddExtraPower(value);
}

void AttrsSystem::JoinBaseAttr(Attribute &attr, AttrSystemId attrSysId)
{
	attr += base_attr_[attrSysId];
}

void AttrsSystem::JoinBaseAttr(Attribute &attr, AttrSystemId asfrom, AttrSystemId asto)
{
	for (int i = asfrom; i <= asto; ++i) {
		attr += base_attr_[i];
	}
}

/*
void ShenBingSystem::GetExaAttr(ExAttribute &attr)
{
		attr += exa_attr_;
}

Attribute* ShenBingSystem::GetBaseAttr()
{
	return &base_attr_;
}
*/

Attribute* AttrsSystem::GetBaseAttr(AttrSystemId attrSysId)
{
	if (attrSysId <= asStart || attrSysId >= asCount) return nullptr;
	return &base_attr_[attrSysId];
}
