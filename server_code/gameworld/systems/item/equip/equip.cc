#include "StdAfx.h"
#include "equip.h"
#include "../item_config.h"
#include "attr/attribute.h"

Equip::~Equip()
{

}


bool Equip::Init()
{
	if (!Item::Init())
		return false;

	auto conf = ItemConfigPool::GetEquipConfig(GetId());
	if (conf == NULL)
	{
		OutputMsg(rmError, "equip init failed, no config:%d", GetId());
		return false;
	}
	equip_config_ = conf;
	{
		ItemAttrData::EquipAttr &equip_attr = data_.attr_data.equip_attr;
		if (equip_attr.attr[0][1] == 0)	// 需要初始化属性
		{
			int i = 0;
			float range = GetRange();

/*****************************/
#define GenerateAttr(type, value) \
	if (value > 0) { \
		int cal_attr = (unsigned int)(range * 100 / 10000 * (value)); \
		if (cal_attr > 0){\
			equip_attr.attr[i][0] = type; \
			equip_attr.attr[i][1] = cal_attr;}\
		++i; \
	}
	//if (equip_attr.attr[i][1] == 0) equip_attr.attr[i][1] = 1; \

	
/****************************/

			GenerateAttr(Attribute::atDef, conf->def)
			GenerateAttr(Attribute::atAtk, conf->atk)
			GenerateAttr(Attribute::atHpMax, conf->hp)
			GenerateAttr(Attribute::atRes, conf->res)
			GenerateAttr(Attribute::atCrit, conf->crit)
			GenerateAttr(Attribute::atTough, conf->tough)

#undef GenerateAttr
			assert(i <= EQUIP_ATTR_COUNT);
		}
	}
	{
		ItemAttrData::EquipAttr &equip_attr = data_.ex_attr_data.equip_attr;
		if (equip_attr.attr[0][1] == 0 && conf->exAttrCountNum && conf->exAttrNum)	// 需要初始化扩展属性
		{
			//随机需要的条数
			int rand_rate = wrand(conf->exAttrCountTotalRate);
			int exattrcount = 0, total_rate = 0;
			for (int i = 0; i < conf->exAttrCountNum; ++i)
			{
				total_rate += conf->exAttrCount[i][1];
				if (total_rate > rand_rate)
				{
					exattrcount = conf->exAttrCount[i][0];
					break;
				}
			}
			//按条数随机属性
			exattrcount = __min(exattrcount, conf->exAttrNum);
			int attr_idx = 0;
			for (int c = 0; c < exattrcount; ++c)
			{
				total_rate = 0;
				rand_rate = wrand(conf->exAttrTotalRate);
				for (int i = 0; i < conf->exAttrNum; ++i)
				{
					total_rate += conf->exAttr[i][2];
					if (total_rate > rand_rate)
					{
						equip_attr.attr[attr_idx][0] = conf->exAttr[i][0];
						equip_attr.attr[attr_idx][1] = conf->exAttr[i][1];
						++attr_idx;
						break;
					}
				}
			}
		}
	}
	return true;
}

void Equip::AddAttr(Attribute& attr)
{
	// 固定属性
	attr.Add(Attribute::atAtk, equip_config_->atk);
	attr.Add(Attribute::atDef, equip_config_->def);
	attr.Add(Attribute::atRes, equip_config_->res);
	attr.Add(Attribute::atCrit, equip_config_->crit);
	attr.Add(Attribute::atTough, equip_config_->tough);
	attr.Add(Attribute::atHpMax, equip_config_->hp);

	for (int i = 0; i < EQUIP_ATTR_COUNT; ++i)
	{
		// 附加属性
		ItemAttrData::EquipAttr &data = data_.attr_data.equip_attr;
		attr.Add((Attribute::AttributeType)data.attr[i][0], data.attr[i][1]);
	}
	attr.Add((Attribute::AttributeType)(equip_config_->base_attr1[0]), equip_config_->base_attr1[1]);
	attr.Add((Attribute::AttributeType)(equip_config_->base_attr2[0]), equip_config_->base_attr2[1]);
	attr.SetExtraPower(attr.GetExtraPower() + equip_config_->ex_power);
}

void Equip::AddExAttr(ExAttribute& ex_attr)
{
	// 特殊属性
	ex_attr.Add(equip_config_->ex_attr1[0], equip_config_->ex_attr1[1]);
	ex_attr.Add(equip_config_->ex_attr2[0], equip_config_->ex_attr2[1]);
	ex_attr.Add(equip_config_->ex_attr3[0], equip_config_->ex_attr3[1]);
	ItemAttrData::EquipAttr &equip_attr = data_.ex_attr_data.equip_attr;
	for (int i = 0; i < EQUIP_ATTR_COUNT; ++i)
	{
		if (equip_attr.attr[i][0] == 0) break;
		ex_attr.Add(equip_attr.attr[i][0], equip_attr.attr[i][1]);
	}
}

float Equip::GetRange()
{
	float range = (float)wrand((unsigned long)(equip_config_->addrangeHigh - equip_config_->addrangeLow)+1) + equip_config_->addrangeLow;
	if (config_->quality != QualityType_Orange)
		return range;

	int newLevel = config_->zs_level * 1000 + config_->level;
	auto legendattr = ItemConfigPool::GetLegendAttrConfig(newLevel);
	if (!legendattr) 
		return range;

	int rate = wrand(100);

	int cur = 0;
	for (std::size_t i = 0; i < (*legendattr).size();++i)
	{
		cur += (*legendattr)[i].rate;
		if (cur < rate) continue;

		range = (float)wrand(((*legendattr)[i].high - (*legendattr)[i].low) + 1) + (*legendattr)[i].low;
		break;
	}
	return range;
}
