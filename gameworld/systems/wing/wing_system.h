#pragma once
#include "attr/attribute.h"
#include "item/equip/equip.h"


struct RoleData;
class Role;
class WingSystem
{
public:
	WingSystem(Role* role);
	~WingSystem();

	bool Init(RoleData* data);
	//void Save(RoleData* data);

	void Destroy();
	const Attribute& GetBattleAttr() { return attribute_; }
	const Attribute& GetTempAttr() { return temp_attribute_; }
	void ClearAttr();
	void AddAttr(int type, int value);
	void AddTempAttr(int type, int value);
	const WingsData* GetWingData();

	//设置等级
	void SetLevel(int level);
	//设置经验
	void SetExp(int exp);
	//设置星级
	void SetStar(int star);
	//设置开启状态
	void SetOpenStatus(int status);
	//设置清空经验时间
	void setWingCTime(unsigned int ctime);
	//翅膀提升丹
	void setWingPill(int idx, int count);
	//穿戴翅膀装备
	//bool EquipWingItem(Equip *item, short slot);
	//获取翅膀装备的类型
	static int GetWingSlotType(int slot);
	//加上翅膀装备的属性
	//void AddWingEquipAttr();
	//更新翅膀信息
	void WingInfoSync();
	//1秒定时器
	void On1sTick(int64_t curr_t);
	//更新翅膀属性
	void callUpdateAttr(void);
private:
	void NotifyUpdateWingEquip(int slot, Equip* item);
	void CalcAttribute(bool notify);

private:
	Role*	role_;
	WingsData*  wingData_;
	//WingsEquip* wing_equip_data;
	//Equip*      wing_equip_[WingSlotType_Max];
	Attribute attribute_;
	Attribute temp_attribute_;
};