#include "StdAfx.h"
#include "battle_attr.h"

AttrPower BattleAttribute::attr_power[Attribute::atCount] = { 0 };

BattleAttribute::BattleAttribute()
:final_attrs_()
,power_(0)
{
}

BattleAttribute::~BattleAttribute()
{
}

void BattleAttribute::CalcBattleAttribute(const Attribute& attrs, BYTE job)
{
	final_attrs_ = attrs;
	switch (job)
	{
	case JobType_Warrior:
		final_attrs_[Attribute::atHpMax] += final_attrs_[Attribute::atJob1HpEx];
		final_attrs_[Attribute::atAtk] += final_attrs_[Attribute::atJob1AtkEx];
		final_attrs_[Attribute::atDef] += final_attrs_[Attribute::atJob1DefEx];
		final_attrs_[Attribute::atRes] += final_attrs_[Attribute::atJob1ResEx];
		break;
	case JobType_Mage:
		final_attrs_[Attribute::atHpMax] += final_attrs_[Attribute::atJob2HpEx];
		final_attrs_[Attribute::atAtk] += final_attrs_[Attribute::atJob2AtkEx];
		final_attrs_[Attribute::atDef] += final_attrs_[Attribute::atJob2DefEx];
		final_attrs_[Attribute::atRes] += final_attrs_[Attribute::atJob2ResEx];
		break;
	case JobType_Taoist:
		final_attrs_[Attribute::atHpMax] += final_attrs_[Attribute::atJob3HpEx];
		final_attrs_[Attribute::atAtk] += final_attrs_[Attribute::atJob3AtkEx];
		final_attrs_[Attribute::atDef] += final_attrs_[Attribute::atJob3DefEx];
		final_attrs_[Attribute::atRes] += final_attrs_[Attribute::atJob3ResEx];
		break;
	default:
		break;
	}
	final_attrs_[Attribute::atHpMax] = floor(final_attrs_[Attribute::atHpMax] * (1 + final_attrs_[Attribute::atHpEx] / 10000.0));
	final_attrs_[Attribute::atAtk] = floor(final_attrs_[Attribute::atAtk] * (1 + final_attrs_[Attribute::atAtkEx] / 10000.0));
	final_attrs_[Attribute::atDef] = floor(final_attrs_[Attribute::atDef] * (1 + final_attrs_[Attribute::atDefEx] / 10000.0));
	final_attrs_[Attribute::atRes] = floor(final_attrs_[Attribute::atRes] * (1 + final_attrs_[Attribute::atResEx] / 10000.0));
	final_attrs_[Attribute::atNeiGongMax] = floor(final_attrs_[Attribute::atNeiGongMax] * (1 + final_attrs_[Attribute::atNeiGongEx] / 10000.0));
	final_attrs_.SetExtraPower(attrs.GetExtraPower());
}

void BattleAttribute::SetBattleAttribute(Attribute& attrs)
{
	final_attrs_ = attrs;
	final_attrs_.SetExtraPower(attrs.GetExtraPower());
}


void BattleAttribute::GetAttrData(double data[]) const 	//获得属性集
{
	final_attrs_.GetValues(data);
}

void BattleAttribute::CalcPower()
{
	// todo 战力计算
	power_ = 0;
	for (int i = Attribute::atHp; i < Attribute::atCount; ++i) {
		auto &t = attr_power[i];
		power_ += final_attrs_[i] * t.power / 100 + final_attrs_[i] * final_attrs_[t.relateType] * t.relatePower / 100;
	}
	power_ += final_attrs_.GetExtraPower();
	power_ = floor(power_);
}

void BattleAttribute::GMSet(int type, double value)
{
	final_attrs_.Set((Attribute::AttributeType)type, value);
}

bool BattleAttribute::LoadAttrPowerConfig(GameConfigData* data)
{
	if (!data->openGlobalTable("AttrPowerConfig"))
	{
		OutputMsg(rmError, ("can't open Attr Power table"));
		return false;
	}

	if (data->enumTableFirst())
	{
		//int nIdx = 0;
		do {
			int type, relateType, ndef = 0;
			double power, relatePower, ddef = 0.0;

			type = data->getFieldInt("type");
			power = data->getFieldNumber("power",&ddef);
			relateType = data->getFieldInt("relate_type", &ndef);
			relatePower = data->getFieldNumber("relate_power", &ddef);

			if (type >= 0 && type < Attribute::atCount) {
				attr_power[type].power = power;
				attr_power[type].relateType = relateType;
				attr_power[type].relatePower = relatePower;
			}

		} while (data->enumTableNext());
	}
	else
	{
		OutputMsg(rmError, "------------------------Attr Power is null");
	}

	data->closeTable();

	return true;
}
