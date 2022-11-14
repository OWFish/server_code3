#pragma once
#include "item_config.h"
#include "db/item_data.h"


class Item
{
public:
	enum QualityType
	{
		QualityType_White	= 0,
		QualityType_Green,
		QualityType_Blue,
		QualityType_Violet,
		QualityType_Orange,
		QualityType_Red,

		QualityType_Max 
	};
public:
	friend class ItemPool;
	virtual ~Item();

	virtual bool	Init();

	int64_t GetUId() { return data_.uid; }
	int		GetId() { return data_.id; }
	int		GetType() { return config_->type;}
	int		GetBagType() { return config_->bagtype; }
	int		GetSubType() { return config_->subtype;}
	int		GetJobType() { return config_->job; }
	int		GetLevel() { return config_->level; }
	int		GetQuality() { return config_->quality; }
	int		GetZhuanShengLevel() { return config_->zs_level; }
	int		GetUseCond() { return config_->useCond; }
	bool	isEquip() const { return config_->isEquip(); }
	int		GetCount() { return data_.count; }
	int		GetEquipType() { return config_->equiptype;}

	void	SetCount(int count) { data_.count = count; }
	void	WriteData(DataPacket &pack) { data_.writeData(pack); }
	void	WriteData(void *data) { memcpy(data, &data_, sizeof(ItemData)); }
	void	ReadData(DataPacket &pack) { data_.readData(pack); }
	const ItemData& GetItemData(void) { return data_; }
	ItemData* GetItemDataPtr(void) { return &data_; }
protected:
	Item();

protected:
	ItemData				data_;			// 物品数据
	const ItemConfig*		config_;		// 物品配置
};


