#pragma once

#include "item_bag.h"
#include <vector>


class Depot : public ItemBag
{
public:
	Depot(Actor* actor);
	~Depot(){}

	enum DepotType
	{
		OrangeEquip=0,//橙色装备
		FuwenItem,//符文
		Heirloom,//传世装备
	};
	bool Init(DataPacketReader &data);

	void PickItemToBag(int64_t uid);
	void PickAllItem(int type);

	bool AppendItem(int id, int count, const char* log);

	size_t GetCount(void) { return Count(); }

private:
	bool init_finish_;
};
