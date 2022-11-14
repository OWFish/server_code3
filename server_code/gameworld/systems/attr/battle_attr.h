#ifndef _BATTLE_ATTRIBUTE_H_
#define _BATTLE_ATTRIBUTE_H_

#include "attribute.h"

struct AttrPower
{
	double power;
	int relateType;
	double relatePower;
};

// ���Լ�����
class BattleAttribute
{
public:
	BattleAttribute();
	~BattleAttribute();

	static AttrPower attr_power[Attribute::atCount];
	static bool LoadAttrPowerConfig(GameConfigData* data);

	double Get(int type) { if (type < 0 || type >= Attribute::atCount) return 0; return final_attrs_[(Attribute::AttributeType)type]; }
	// ֻ�����޸ĵ�ǰhp��mp
	void SetHp(double v) { final_attrs_.Set(Attribute::atHp, v); }
	void SetMp(double v) { final_attrs_.Set(Attribute::atMp, v); }
	void SetNp(double v) { final_attrs_.Set(Attribute::atNeiGong, v); }
	double operator[](Attribute::AttributeType type) { return final_attrs_[type]; }
	double GetPower() const { return power_; }
	void SetPower(double power) { power_ = power; }

	void CalcBattleAttribute(const Attribute& attrs, BYTE job);
	void SetBattleAttribute(Attribute& attrs);

	void CalcPower(); // ��ս�������Էֿ����㣬��Ϊ���Ի�����ʱ����
	void GetAttrData(double data[]) const;	//����������Լ�
	void GMSet(int type, double value);
	Attribute& GetFinalAttrs() { return final_attrs_; }
private:
	Attribute   final_attrs_;	//�������� ���������
	Attribute   basic_attrs_;	//�������� ����ǰ����
	double			power_;			//ս��
};


#endif
