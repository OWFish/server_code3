#include "StdAfx.h"
#include "base_container.h"
#include "db/item_data.h"
#include "item/item.h"
#include "item/item_config.h"
#include "item/item_pool.h"


BaseContainer::BaseContainer()
: need_save_(false)
{

}

BaseContainer::~BaseContainer()
{
	for (std::size_t i = 0; i < item_list_.size(); ++i)
	{
		SafeDelete(item_list_[i]);
	}
}


bool BaseContainer::AddItem(Item* item, bool notify, bool showTip)
{
	if (!item) return false;
	item_list_.push_back(item);

	OnAddItem(item);

	if (notify)
		NotifyAdd(item, showTip);
	need_save_ = true;

	return true;
}

bool BaseContainer::AddItem(ItemData* data, bool notify)
{
	Item *item = ItemPool::instance().CreateItem(data);

	return AddItem(item, notify);
}

bool BaseContainer::AddItem(int id, int count, bool showTip)
{
	return AddItem(ItemPool::instance().CreateItem(id, count), true, showTip);
}

bool BaseContainer::TakeOutItem(Item* item)
{
	for (std::size_t i = 0; i < item_list_.size(); ++i)
	{
		if (item_list_[i] == item)
		{ 
			item_list_[i] = item_list_[item_list_.size() - 1];
			item_list_.pop_back();
			NotifyDelete(item->GetUId(), item->GetCount());
			need_save_ = true;
			return true;
		}

	}
	return false;
}

bool BaseContainer::DeleteItem(int64_t uid, int count)
{
	for (std::size_t i = 0; i < item_list_.size(); ++i)
	{
		Item *item = item_list_[i];
		if (item->GetUId() == uid)
		{
			int cnt = item->GetCount();
			if (cnt < count)
				return false;

			if (cnt == count)
			{
				RemoveItem((int)i);
				NotifyDelete(uid, count);
			}
			else
			{
				item->SetCount(cnt - count);
				NotifyUpdate(uid, cnt - count);
			}
			
			need_save_ = true;
			return true;
		}
	}
	return false;
}

bool BaseContainer::RemoveItem(int index)
{
	delete item_list_[index];
	item_list_[index] = item_list_[item_list_.size()-1];
	item_list_.pop_back();

	return true;
}

int BaseContainer::GetCountById(int id) const
{
	int count = 0;
	for (std::size_t i = 0; i < item_list_.size(); ++i)
	{
		Item *item = item_list_[i];
		if (item->GetId() == id)
		{
			count = count + item->GetCount();
		}
	}
	return count;
}

int BaseContainer::GetCountById(int64_t uid) const
{
	for (std::size_t i = 0; i < item_list_.size(); ++i)
	{
		Item *item = item_list_[i];
		if (item->GetUId() == uid)
		{
			return item->GetCount();
		}
	}
	return 0;
}





