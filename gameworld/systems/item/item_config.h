#pragma once

#include "config/game_config_data.h"
#include <map>
#include <vector>
#include "db/role_data.h"


struct ItemConfig
{
	int id;
	int type;
	int subtype;
	int bagtype;
	int quality;
	int job;
	int level;
	int zs_level;
	char name[32];
	int useCond;
	int equiptype;
	bool isEquip() const
	{
		return (type == ItemType_Equip || type == ItemType_WingEquip || type == ItemType_TogetherHit || type == ItemType_Imba);
	}
};

struct SmeltEquipRateConfig
{
	int qualityAdd;		//品质提升多少
	int rate;			//概率
};

struct SmeltConfig
{
	//	int quality;
	//	int level;
	//	int zsLevel;
	int stoneId;
	int stoneNum;
	int goldNum;
	std::vector<SmeltEquipRateConfig> equipRateList;
	std::map<int, int> currency;

	bool isEmpty() {
		if (stoneId > 0 && stoneNum > 0) return false;
		if (goldNum > 0) return false;
		if (!equipRateList.empty()) return false;
		if (!currency.empty()) return false;
		return true;
	}
};

struct EquipConfig
{
	int id;
	int hp;
	int atk;
	int def;
	int res;
	int crit;
	int tough;
	float addrangeLow;
	float addrangeHigh;

	int ex_attr1[2];
	int ex_attr2[2];
	int ex_attr3[2];
	int base_attr1[2];
	int base_attr2[2];
	int ex_power;
	int exAttrCountNum;//随机个数的配置数量
	int exAttrCount[EQUIP_ATTR_COUNT][2];//0->count,1->rate
	int exAttrCountTotalRate;
	int exAttrNum;//随机属性的配置数量
	int exAttr[EQUIP_ATTR_COUNT][3];//0->type,1->val,2->rate
	int exAttrTotalRate;
}; 

struct LevelupConfig
{
	int oldEquipId;
	int newEquipId;
	int itemId;
	int count;
};

enum ComposeConfigType
{
	CCT_ORANGE = 1,
	CCT_LEGEND = 2,
};

struct ComposeConfig
{
	int equipId;
	int itemId;
	int count;
	uint8_t type;
};

struct AttrRangeConfig
{
	int low;
	int high;
	int rate;
};


class ItemConfigPool
{
public:
	static bool Load(GameLuaConfig* data);
	static bool LoadEquip(GameLuaConfig* data);
	//static bool LoadSmelt(GameLuaConfig* data);
	static bool LoadSmelt(GameLuaConfig* data, int id);
	static bool LoadLevelup(GameLuaConfig* data);
	static bool LoadCompose(GameLuaConfig* data);
	static bool LoadLegendAttr(GameLuaConfig* data);

	static const ItemConfig* GetItemConfig(int id);
	static const EquipConfig* GetEquipConfig(int id);
	static const SmeltConfig* GetSmeltConfig(int key);
	static const LevelupConfig* GetLevelupConfig(int equipId);
	static const ComposeConfig* GetComposeConfig(int equipId);
	static const std::vector<AttrRangeConfig>* GetLegendAttrConfig(int level);

	static bool Reload();
private:
	static std::map<int, ItemConfig> config_pool_;
	static std::map<int, EquipConfig> equip_config_pool_;
	static std::map<int, SmeltConfig> equip_smelt_pool;
	static std::map<int, LevelupConfig> equip_levelup_pool;
	static std::map<int, ComposeConfig> equip_compose_pool;
	static std::map<int, std::vector<AttrRangeConfig>> legend_attr_pool;

	static GameLuaConfig lua_reader_;
};


