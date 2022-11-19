#pragma once

#include "db/store_data.h"

class StoreSystem
{
public:
	StoreSystem(Actor *actor);
	~StoreSystem();

	const static int maxItemNum = 6;

	typedef std::vector<StoreItemData> StoreItemList;

	bool Init(DataPacketReader &data);
	void Save(ActorBasicData* data, bool force = false);
	void OnEnterGame();

	const StoreItemData* GetStoreItemData(int id);
	StoreItemList& GetStoreItemList(){ return item_list_; }

	void GiveStoreItem(int id, int& itemId, int& itemCount);
	void AddStoreItem(int id, int itemId, int count, int currencyType, int currency, int discount);
	void StoreDataSync(int refreshCount);
	void StoreClearList();
private:

protected:
	Actor *actor_;

	StoreItemList item_list_;

	bool need_save_;
	bool init_finish_;
};