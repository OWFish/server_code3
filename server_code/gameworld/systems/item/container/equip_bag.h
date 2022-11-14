#pragma once

#include "item_bag.h"
#include <vector>

#define MONTH_CARD_EQUIPBAG_GRID 100 //�¿������ĸ�����
//#define PRIVILEGE_EQUIPBAG_GRID 100 //��Ȩ�����ĸ�����
//#define WING_EQUIP_SMELT_BASE    200 //���װ��������ʱ�Ļ����ȼ�
//#define TOGETHERHIT_SMELT_BASE	 300 //�ϻ�װ��������ʱ�Ļ����ȼ�
#define PRIVILEGE_EQUIPBAG_GRID 100 //��Ȩ�¿������ĸ�����

class EquipBag : public ItemBag
{
	friend EquipSystem;
	friend WingSystem;
	friend TogetherHitSystem;
public:
	EquipBag(Actor* actor);
	~EquipBag(){}

	bool Init(DataPacketReader &data);
	bool OnDecomposeEquip(int64_t uid);

	//װ�������Ľӿ�
	void OnEquipSmelt(int type, std::vector<int64_t> &itemIdList);
	void OnExpandCapacity(int rows);

	bool IsCanSmelt(int type, int64_t uid);
	//װ�������Ļذ�
	void ReEquipSmelt(int result, int goldNum, std::map<int, int> &itemList);

	void OnActorSmeltEvent(int smeltCount);

	int AppendItem(int id, int count, const char* log, bool showTip = true);
	int AppendItem(ItemData *data, const char* log, bool showTip = true);
	int AppendItem(Item* pItem, const char* log, bool showTip = true);
	int Spaces(){ return capacity_ - static_cast<int>( Count()); } // ʣ��ռ�
	void SetCapacity(int grid) { capacity_ = grid; }

	void OnVipLevelUpdate();
	void UpdataCapacity(int add = 0,int capacity = 0);
private:
	int capacity_;
};
