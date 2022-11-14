#include "StdAfx.h"
#include "item_pool.h"
#include "item.h"
#include "equip/equip.h"


ItemPool::ItemPool()
: series_(0)
, server_id_(0)
, last_time_(0)
{

}

ItemPool::~ItemPool()
{

}


int64_t ItemPool::allocSeries()
{
	static GameEngine* ge = GetGameEngine();
	ItemSeries series;
	series.llId = 0; //初始化
	//创建序列号
	series.t.time_ = ge->getMiniDateTime();
	series.t.sid_ = (uint16_t)server_id_;
	if (series.t.time_ != (uint64_t)last_time_)
	{
		series_ = 0;
		last_time_ = series.t.time_;
	}
	series.t.series_ = (uint16_t)series_;
	//单位时间内的系列号值递增
	series_++;

	//OutputMsg(rmError, "series :%lld, time:%d,  id:%d", series.llId, series.t.time_, series_);
	return series.llId;
}


Item* ItemPool::CreateItem(ItemData* data)
{
	if (data == NULL) return NULL;

	const ItemConfig *conf = ItemConfigPool::GetItemConfig(data->id);
	if (conf == NULL) return NULL;

	Item *item = NewItem(conf->type);
	item->config_ = conf;
	memcpy(&item->data_, data, sizeof(ItemData));
	if (!item->Init())
	{
		OutputMsg(rmError, "create item failed. init failed. id:%d", conf->id);
		delete item;
		return NULL;
	}

	return item;;
}

Item* ItemPool::NewItem(int type)
{
	switch (type)
	{
	case ItemType_Equip:
	case ItemType_WingEquip:
	case ItemType_TogetherHit:
		return new Equip();
		break;
	default:
		return new Item();
		break;
	}
}

Item* ItemPool::CreateItem(int id, int count)
{
	const ItemConfig *conf = ItemConfigPool::GetItemConfig(id);
	if (conf == NULL) return NULL;
	if (count <= 0)
		return NULL;

	Item *item = NewItem(conf->type);
	item->config_ = conf;
	item->data_.uid = allocSeries();
	item->data_.id = id;
	item->data_.count = count;
	if (!item->Init())
	{
		OutputMsg(rmError, "create item failed. init failed. id:%d", id);
		delete item;
		return NULL;
	}

	return item;
}



