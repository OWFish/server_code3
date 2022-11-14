#pragma once
#include "attr/attribute.h"
#include "item/equip/equip.h"

// tolua_begin
enum TogetherHitSlotType
{
	TogetherHitSlotType_Qian, //Ǭ
	TogetherHitSlotType_Kun,  //��
	TogetherHitSlotType_Zhen, //��
	TogetherHitSlotType_Xun,  //��
	TogetherHitSlotType_Kan,  //��
	TogetherHitSlotType_Li,   //��
	TogetherHitSlotType_Gen,  //��
	TogetherHitSlotType_Dui,  //��
	TogetherHitSlotType_Max
};
//tolua_end

struct TogetherHitEquip
{
	EquipSlotData together_hit_slot[TogetherHitSlotType_Max];
};

class TogetherHitSystem
{
public:
	TogetherHitSystem(Actor* actor);
	~TogetherHitSystem();

	bool Init(DataPacketReader &data);
	void Save(ActorBasicData* data, bool force = false);

	void Destroy();
	Attribute& GetAttr() { return attribute_; }
	ExAttribute& GetExAttr() { return ex_attribute_; }
	ExAttribute& GetSkillExAttr() { return skill_ex_attr_; }
	Attribute& GetPunchAttr() { return punch_attribute_; }
	ExAttribute& GetPunchExAttr() { return punch_ex_attribute_; }

	//�����ϻ�װ��
	bool EquipTogetherHitItem(Equip *item, short slot);

	//���Ϻϻ�װ��������
	void AddTogetherHitEquipAttr(bool isEquip=false);  //trueΪ��װ�����ӵ�����
	//������Ϣ
	void TogetherHitInfoSync();
	void NotifyUpdateEquip(int slot, Equip* item);

	TogetherHitEquip& getTogetherHitEquip(void) { return together_hit_equip_data; }
	void setTogetHerEquipLevel(int pos, int lv);
private:
	Actor*		actor_;
	//int			together_hit_lv;
	ExAttribute skill_ex_attr_;
	ExAttribute ex_attribute_;
	Attribute	attribute_;
	ExAttribute punch_ex_attribute_;
	Attribute	punch_attribute_;
	TogetherHitEquip together_hit_equip_data;
	Equip*      together_hit_equip_[TogetherHitSlotType_Max];
	bool need_save_;
	bool init_finish_;
};