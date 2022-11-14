#pragma once

#include <vector>


/***********************************************************
* 物品 基础容器类
* 简化版，只做了当前需要的功能
***********************************************************/


struct ItemData;
class Item;

class BaseContainer
{
public:
	BaseContainer();
	virtual ~BaseContainer();

	static const int MAX_ITEM_COUNT = 1 << 30;

	int GetCountById(int id) const;
	int GetCountById(int64_t uid) const;

protected:
	bool AddItem(Item* item, bool notify = true, bool showTip = true);		//根据已有物品添加
	bool AddItem(ItemData* data, bool notify = true);	//根据物品数据添加 
	bool AddItem(int id, int count, bool showTip = true);					//根据配置id添加

	bool TakeOutItem(Item* item);
	bool DeleteItem(int64_t uid, int count);

	size_t Count() { return item_list_.size(); }

protected:
	virtual void NotifyDelete(int64_t uid, int count){}
	virtual void NotifyAdd(Item *item, bool showTip = true){}	//给客户端加的是否显示提示(橙装相关)
	virtual void NotifyUpdate(int64_t uid, int count, bool showTip = true){}

	virtual void OnAddItem(Item *item) {}

private:
	bool RemoveItem(int index);
	
protected:
	std::vector<Item*> item_list_;
	bool			need_save_;
};