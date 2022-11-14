#pragma once

#include "item_bag.h"
#include <vector>

#define MONTH_CARD_EQUIPBAG_GRID 100 //月卡解锁的格子数
//#define PRIVILEGE_EQUIPBAG_GRID 100 //特权解锁的格子数
//#define WING_EQUIP_SMELT_BASE    200 //翅膀装备在熔炼时的基础等级
//#define TOGETHERHIT_SMELT_BASE	 300 //合击装备在熔炼时的基础等级
#define PRIVILEGE_EQUIPBAG_GRID 100 //特权月卡解锁的格子数

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

	//装备熔炼的接口
	void OnEquipSmelt(int type, std::vector<int64_t> &itemIdList);
	void OnExpandCapacity(int rows);

	bool IsCanSmelt(int type, int64_t uid);
	//装备熔炼的回包
	void ReEquipSmelt(int result, int goldNum, std::map<int, int> &itemList);

	void OnActorSmeltEvent(int smeltCount);

	int AppendItem(int id, int count, const char* log, bool showTip = true);
	int AppendItem(ItemData *data, const char* log, bool showTip = true);
	int AppendItem(Item* pItem, const char* log, bool showTip = true);
	int Spaces(){ return capacity_ - static_cast<int>( Count()); } // 剩余空间
	void SetCapacity(int grid) { capacity_ = grid; }

	void OnVipLevelUpdate();
	void UpdataCapacity(int add = 0,int capacity = 0);
private:
	int capacity_;
};
