#pragma once

#include "base_container.h"


class Actor;
struct ActorBasicData;


#define MAX_PACKET_ITEMS_SIZE  300
class ItemBag : public BaseContainer
{
	friend class Actor;
	friend FuWenSystem;
public:
	ItemBag(Actor *actor);
	~ItemBag();
	
	bool Init(DataPacketReader &data);
	void Save(ActorBasicData* data, bool force = false);
	void OnEnterGame();

	int GetType(){ return bag_type_; }
	bool AppendItem(int id, int count, const char* log, bool showTip = true);
	Item* GetItem(int64_t uid);
	int64_t FindItemUid(int id);

	void GMClear();
protected:
	bool CostItem(int64_t uid, int count);
	virtual void NotifyDelete(int64_t uid, int count);
	virtual void NotifyAdd(Item* item, bool showTip = true);
	virtual void NotifyUpdate(int64_t uid, int count, bool showTip = true);
	virtual void OnAddItem(Item *item);

	int FindItem(int id);
	
	
protected:
	int bag_type_;
	Actor *actor_;
public:
	std::string db_buf_; //·Ö°üµÄbuf
	std::vector<bool> buf_index_; //bufindex
};
