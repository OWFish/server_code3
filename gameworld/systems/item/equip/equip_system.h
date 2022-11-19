#pragma once
#include "equip.h"
#include "attr/attribute.h"

#pragma  pack(push,1)
//tolua_begin

enum OnEquipType
{
	EquipType_Null = 0,//空
	EquipType_Normal = 1,// 普通装备
	EquipType_God = 2,//	神装
};

//tolua_end
#pragma  pack(pop)


struct RoleData;
class Role;
class EquipSystem
{
public:
	EquipSystem(Role* role);
	~EquipSystem();

	enum EquipNotice
	{
		EN_ORANGE_COMPOSE_ID = 5,
		EN_ORANGE_COMPOSE_ZS_ID = 150,
		EN_LEGEND_COMPOSE_ID = 69,

		EN_ORANGE_LVUP_ID = 6,
		EN_ORANGE_ZSUP_ID = 7,
		EN_LEGEND_ZSUP_ID = 70,
	};

	bool Init(RoleData* data);
	void Save(RoleData* data);

	void Destroy();
	const Attribute& GetBattleAttr() { return attribute_; }
	const ExAttribute& GetExAttr() { return ex_attribute_; }
	bool EquipItem(Equip *item, short slot);
	bool EquipGodItem(Equip *item, short slot);
	bool TakeOutEquip(int equiptype, int slot);
	int GetEquipId(short slot);
	int GetEquipQuality(short slot);
	void getEquipLevel(short slot, int &level, int &zsLevel);

	void EquipLevelup(short slot);
	void ReqLevelup(int result, int itemId);

	void EquipCompose(int equipId, short slot);
	void NotifyCompose(int result, int itemId);

	bool GetEquipAttrBySlot(short slot, Attribute &attribute);
	bool GetEquipExAttrBySlot(short slot, ExAttribute &ex_attribute);
private:
	void NotifyUpdateEquip(int slot, Equip* item,int equiptype = 0);
	void CalcAttribute(bool notify);
	void OnEquipEvent(short slot);

private:
	Role*	role_;
	EquipsData* data_;

	Equip* equip_[EquipSlotType_Max];
	Equip* godequip_[EquipSlotType_Dzi];

	Attribute attribute_;
	ExAttribute ex_attribute_;
};