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

	//���õȼ�
	void SetLevel(int level);
	//���þ���
	void SetExp(int exp);
	//�����Ǽ�
	void SetStar(int star);
	//���ÿ���״̬
	void SetOpenStatus(int status);
	//������վ���ʱ��
	void setWingCTime(unsigned int ctime);
	//���������
	void setWingPill(int idx, int count);
	//�������װ��
	//bool EquipWingItem(Equip *item, short slot);
	//��ȡ���װ��������
	static int GetWingSlotType(int slot);
	//���ϳ��װ��������
	//void AddWingEquipAttr();
	//���³����Ϣ
	void WingInfoSync();
	//1�붨ʱ��
	void On1sTick(int64_t curr_t);
	//���³������
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