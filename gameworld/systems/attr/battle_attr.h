#ifndef _BATTLE_ATTRIBUTE_H_
#define _BATTLE_ATTRIBUTE_H_

#include "attribute.h"

struct AttrPower
{
	double power;
	int relateType;
	double relatePower;
};

// 属性计算类
class BattleAttribute
{
public:
	BattleAttribute();
	~BattleAttribute();

	static AttrPower attr_power[Attribute::atCount];
	static bool LoadAttrPowerConfig(GameConfigData* data);

	double Get(int type) { if (type < 0 || type >= Attribute::atCount) return 0; return final_attrs_[(Attribute::AttributeType)type]; }
	// 只可以修改当前hp和mp
	void SetHp(double v) { final_attrs_.Set(Attribute::atHp, v); }
	void SetMp(double v) { final_attrs_.Set(Attribute::atMp, v); }
	void SetNp(double v) { final_attrs_.Set(Attribute::atNeiGong, v); }
	double operator[](Attribute::AttributeType type) { return final_attrs_[type]; }
	double GetPower() const { return power_; }
	void SetPower(double power) { power_ = power; }

	void CalcBattleAttribute(const Attribute& attrs, BYTE job);
	void SetBattleAttribute(Attribute& attrs);

	void CalcPower(); // 将战力与属性分开计算，因为属性会有临时属性
	void GetAttrData(double data[]) const;	//获得最终属性集
	void GMSet(int type, double value);
	Attribute& GetFinalAttrs() { return final_attrs_; }
private:
	Attribute   final_attrs_;	//最终属性 计算后属性
	Attribute   basic_attrs_;	//基础属性 计算前属性
	double			power_;			//战力
};


#endif
