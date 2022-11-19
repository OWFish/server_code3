#include "StdAfx.h"
#include "mijisystem.h"
#include "entity/role/role.h"
#include "attr/ex_attr.h"


MiJiSystem::MiJiSystem(Role* role)
{
	memset(miji_list_, 0, sizeof(MiJiData)* MiJiType_Max);
	role_ = role;
	attribute_.Reset();
}

MiJiSystem::~MiJiSystem()
{
}

bool MiJiSystem::Init()
{
	// 不能随role一起初始化
	return true;
}


void MiJiSystem::OnDeath()
{

}

void MiJiSystem::OnDamage()
{

}

void MiJiSystem::ChangeMiJi(int oldId, int newId, bool refresh, int param1, int param2, int param3, int power)
{
	if (oldId == newId) return;

	{
		int id = oldId / 10;
		int level = oldId % 10;
		if (id >= MiJiType_Max || id < 0)
			return;
		if (level > MAX_MIJI_LEVEL || level < 0)
			return;

		if (miji_list_[id].miji[level].enable)
		{
			miji_list_[id].count -= 1;
			miji_list_[id].miji[level].enable = false;
			miji_list_[id].miji[level].param1 = 0;
			miji_list_[id].miji[level].param2 = 0;
			miji_list_[id].miji[level].param3 = 0;
			miji_list_[id].miji[level].power = 0;
		}
	}

	{
		int id = newId / 10;
		int level = newId % 10;
		if (id >= MiJiType_Max || id < 0)
			return;
		if (level > MAX_MIJI_LEVEL || level < 0)
			return;

		if (miji_list_[id].miji[level].enable == false)
		{
			miji_list_[id].count += 1;
			miji_list_[id].miji[level].enable = true;
			miji_list_[id].miji[level].param1 = param1;
			miji_list_[id].miji[level].param2 = param2;
			miji_list_[id].miji[level].param3 = param3;
			miji_list_[id].miji[level].power = power;
		}
	}

	if (refresh)
		Refresh();
}

void MiJiSystem::Refresh()
{
	CalcAttribute();
	role_->CalcAttributes();
	role_->CalcExAttributes();
}

MiJiData::Skill& MiJiData::GetAffectedMiJi()
{
	if (count == 0)
		return miji[0];

	int level = 0;
	int found = 0;
	for (int i = 0; i < MAX_MIJI_LEVEL && found < count; ++i)
	{
		if (miji[i].enable)
		{
			level = i;
			found++;
		}
	}
	return miji[level];
}

void MiJiSystem::CalcAttribute()
{
	attribute_.Reset();
	attribute_[Attribute::atHpMax] = miji_list_[MiJiType_Hp].GetAffectedMiJi().param1;
	attribute_[Attribute::atAtk] = miji_list_[MiJiType_Atk].GetAffectedMiJi().param1;
	attribute_[Attribute::atDef] = miji_list_[MiJiType_Def].GetAffectedMiJi().param1;
	attribute_[Attribute::atRes] = miji_list_[MiJiType_Def].GetAffectedMiJi().param2;
	attribute_[Attribute::atCrit] = miji_list_[MiJiType_CritRate].GetAffectedMiJi().param1;
	attribute_[Attribute::atCritEnhance] = miji_list_[MiJiType_CritEnhance].GetAffectedMiJi().param1;
	attribute_[Attribute::atDamageReduction] = miji_list_[MiJiType_DamageDec].GetAffectedMiJi().param1;
	attribute_[Attribute::atAtkEx] = miji_list_[MiJiType_Pierce].GetAffectedMiJi().param1;
	attribute_[Attribute::atRegeneration] = miji_list_[MiJiType_Regeneration].GetAffectedMiJi().param1;
	attribute_[Attribute::atPenetrate] = miji_list_[MiJiType_Penetrate].GetAffectedMiJi().param1;

	int power = 0;
	for (auto i = 0; i < MiJiType_Max; ++i)
		power += miji_list_[i].GetAffectedMiJi().power;

	attribute_.SetExtraPower(power);

	//todo 如果有多个影响特殊属性的模块,需要统一在creature里和并所有的特殊属性
	ex_attribute_.Reset();
	ex_attribute_[ExAttribute::eatReflectProbability] = miji_list_[MiJiType_Reflect].GetAffectedMiJi().param1;
	ex_attribute_[ExAttribute::eatReflectRate] = miji_list_[MiJiType_Reflect].GetAffectedMiJi().param2;
	ex_attribute_[ExAttribute::eatIgnoreReflect] = miji_list_[MiJiType_Pierce].GetAffectedMiJi().enable;
	ex_attribute_[ExAttribute::eatGodBlessProbability] = miji_list_[MiJiType_Revive].GetAffectedMiJi().param1;
	ex_attribute_[ExAttribute::eatGodBlessRate] = miji_list_[MiJiType_Revive].GetAffectedMiJi().param2;
	ex_attribute_[ExAttribute::eatDeathCurseProbability] = miji_list_[MiJiType_DeathCurse].GetAffectedMiJi().param1;
	ex_attribute_[ExAttribute::eatDeathCurseDamageIncrease] = miji_list_[MiJiType_DeathCurse].GetAffectedMiJi().param2;
	ex_attribute_[ExAttribute::eatDeathCurseTime] = miji_list_[MiJiType_DeathCurse].GetAffectedMiJi().param3;
	ex_attribute_[ExAttribute::eatMiss] = miji_list_[MiJiType_LuckyMiss].GetAffectedMiJi().param1;
	//	MiJiType_KuangLu,//狂怒
	ex_attribute_[ExAttribute::eatMiJiKNHpPer] = miji_list_[MiJiType_KuangLu].GetAffectedMiJi().param1;
	ex_attribute_[ExAttribute::eatMiJiKNHpSubPer] = miji_list_[MiJiType_KuangLu].GetAffectedMiJi().param2;
	ex_attribute_[ExAttribute::eatMiJiKNDamPer] = miji_list_[MiJiType_KuangLu].GetAffectedMiJi().param3;
	// MiJiType_ZhuHun,//追魂
	ex_attribute_[ExAttribute::eatMiJiZHDamPer] = miji_list_[MiJiType_ZhuHun].GetAffectedMiJi().param1;
	ex_attribute_[ExAttribute::eatMiJiZHTime] = miji_list_[MiJiType_ZhuHun].GetAffectedMiJi().param2;
	//	MiJiType_BuQu,//不屈
	ex_attribute_[ExAttribute::eatMiJiBQHpPer] = miji_list_[MiJiType_BuQu].GetAffectedMiJi().param1;
	ex_attribute_[ExAttribute::eatMiJiBQBuffId] = miji_list_[MiJiType_BuQu].GetAffectedMiJi().param2;
	ex_attribute_[ExAttribute::eatMiJiBQHpTime] = miji_list_[MiJiType_BuQu].GetAffectedMiJi().param3;
}