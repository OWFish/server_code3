#include "StdAfx.h"
#include "skill_config.h"


std::map<int, SkillConfig> SkillConfigPool::skill_config_pool_;
std::map<int, EffectConfig> SkillConfigPool::effect_config_pool_;
std::map<int, int> SkillConfigPool::skill_power_pool;
std::map<int, SkillBreakConf> SkillConfigPool::break_conf_pool_;
std::map<int, ImbaSkillReviseCfgList> SkillConfigPool::imba_revise_pool_;
std::map<int, GWSkillReviseMap> SkillConfigPool::gw_revise_pool_;

bool SkillConfigPool::LoadSkill(GameConfigData* data)
{
	if (!data->openGlobalTable("SkillsConfig"))
	{
		OutputMsg(rmError, ("can't open SkillsConfig table"));
		return false;
	}

	if (data->enumTableFirst())
	{
		do {
			SkillConfig conf;
			//memset(&conf, 0, sizeof(SkillConfig));
			int ndef = 0;

			conf.base.id = data->getFieldInt("id");
			conf.base.cast_range = (float)data->getFieldNumber("castRange");
			conf.base.cd = data->getFieldInt("cd");
			ndef = 2;
			conf.base.cast_type = data->getFieldInt("castType", &ndef);
			conf.base.target_type = data->getFieldInt("targetType", &ndef);
			ndef = 1;
			conf.base.affect_range = data->getFieldInt("affectRange", &ndef);
			conf.base.affect_count = data->getFieldInt("affectCount", &ndef);
			conf.base.calc_type = data->getFieldInt("calcType", &ndef);
			ndef = 100;
			conf.herd_mon_rate = data->getFieldInt("herdMonRate", &ndef);
			conf.herd_boss_rate = data->getFieldInt("herdBossRate", &ndef);
			ndef = 10;
			conf.herd_player_rate = data->getFieldInt("herdPlayerRate", &ndef);
			ndef = 1;
			conf.exp = data->getFieldInt("exp", &ndef);
			ndef = 0;
			if (data->fieldTableExists("passive") && data->openFieldTable("passive"))
			{
				conf.passive.is = true;
				conf.passive.rate = data->getFieldInt("rate", &ndef);
				conf.passive.cond = data->getFieldInt("cond", &ndef);
				conf.passive.p1 = data->getFieldInt("p1", &ndef);
				conf.passive.p2 = data->getFieldInt("p2", &ndef);
				conf.passive.p3 = data->getFieldInt("p3", &ndef);
				conf.passive.p4 = data->getFieldInt("p4", &ndef);
				data->closeTable();
			}
			else
			{
				conf.passive.is = false;
			}
			if (data->fieldTableExists("args") && data->openFieldTable("args"))
			{
				double fdef = 0.0;
				conf.args.a = (float)data->getFieldNumber("a", &fdef);
				conf.args.b = (float)data->getFieldNumber("b", &fdef);
				conf.args.c = (float)data->getFieldNumber("c", &fdef);
				conf.args.attr = data->getFieldInt("attr", &ndef);
				//conf.args.type = data->getFieldInt("type", &ndef);
				data->closeTable();
			}
			if (data->fieldTableExists("otherSkills") && data->openFieldTable("otherSkills"))
			{
				if (data->enumTableFirst())
				{
					do {
						int id = data->getFieldInt(NULL);
						conf.other_skills.push_back(id);
					} while (data->enumTableNext());
				}
				data->closeTable();
			}
			if (data->fieldTableExists("tarEff") && data->openFieldTable("tarEff"))
			{
				if (data->enumTableFirst())
				{
					do {
						int id = data->getFieldInt(NULL);
						if (effect_config_pool_.find(id) == effect_config_pool_.end())
						{
							OutputMsg(rmError, "effect %d 's config is null in skill %d", id, conf.base.id);
							return false;
						}
						conf.tar_eff.push_back(id);
					} while (data->enumTableNext());
				}
				data->closeTable();
			}
			if (data->fieldTableExists("otarEff") && data->openFieldTable("otarEff"))
			{
				if (data->enumTableFirst())
				{
					do {
						int id = data->getFieldInt(NULL);
						if (effect_config_pool_.find(id) == effect_config_pool_.end())
						{
							OutputMsg(rmError, "effect %d 's config is null in skill %d", id, conf.base.id);
							return false;
						}
						conf.other_tar_eff.push_back(id);
					} while (data->enumTableNext());
				}
				data->closeTable();
			}
			if (data->fieldTableExists("selfEff") && data->openFieldTable("selfEff"))
			{
				if (data->enumTableFirst())
				{
					do {
						int id = data->getFieldInt(NULL);
						if (effect_config_pool_.find(id) == effect_config_pool_.end())
						{
							OutputMsg(rmError, "effect %d 's config is null in skill %d", id, conf.base.id);
							return false;
						}
						conf.self_eff.push_back(id);
					} while (data->enumTableNext());
				}
				data->closeTable();
			}
			ndef = 0;
			conf.teleport = data->getFieldInt("teleport", &ndef) > 0;
			conf.repel_distance = data->getFieldInt("repelDistance", &ndef);
			conf.no_public_cd = data->getFieldInt("noPublicCD", &ndef) > 0;
			conf.sync_cd = data->getFieldInt("syncCD", &ndef) > 0;
			conf.efftime = data->getFieldInt("efftime", &ndef);

			skill_config_pool_[conf.base.id] = conf;
		} while (data->enumTableNext());
	}
	else
	{
		OutputMsg(rmError, "SkillsConfig is null");
	}

	data->closeTable();

	return true;
}

bool SkillConfigPool::LoadEffect(GameConfigData* data)
{
	if (!data->openGlobalTable("EffectsConfig"))
	{
		OutputMsg(rmError, ("can't open EffectsConfig table"));
		return false;
	}

	if (data->enumTableFirst())
	{
		do {
			EffectConfig conf;
			conf.id = data->getFieldInt("id");
			int ndef = 1;
			conf.is_buff = data->getFieldInt("isBuff", &ndef) > 0;
			ndef = 0;
			conf.interval = data->getFieldInt("interval", &ndef);
			conf.delay = data->getFieldInt("delay", &ndef);
			conf.overlay_type = data->getFieldInt("overlayType", &ndef);
			conf.type = data->getFieldInt("type");
			conf.duration = data->getFieldInt("duration");
			conf.group = data->getFieldInt("group");
			conf.probability = data->getFieldInt("probabilityBuff", &ndef);
			conf.overMaxCount = data->getFieldInt("overMaxCount", &ndef);
			conf.skillid = data->getFieldInt("skillid", &ndef);
			if (data->openFieldTable("args"))
			{
				double fdef = 0.0;
				conf.args.i = (float)data->getFieldNumber("i", &fdef);
				conf.args.a = (float)data->getFieldNumber("a", &fdef);
				conf.args.b = (float)data->getFieldNumber("b", &fdef);
				conf.args.c = (float)data->getFieldNumber("c", &fdef);
				conf.args.d = (float)data->getFieldNumber("d", &fdef);
				data->closeTable();
			}
			if (data->fieldTableExists("unionBuff") && data->openFieldTable("unionBuff"))
			{
				if (data->enumTableFirst())
				{
					do {
						int id = data->getFieldInt(NULL);
						conf.unionBuff.push_back(id);
					} while (data->enumTableNext());
				}
				data->closeTable();
			}
			if (data->fieldTableExists("otherBuffs") && data->openFieldTable("otherBuffs"))
			{
				if (data->enumTableFirst())
				{
					do {
						int id = data->getFieldInt(NULL);
						conf.otherBuffs.push_back(id);
					} while (data->enumTableNext());
				}
				data->closeTable();
			}
			effect_config_pool_[conf.id] = conf;
		} while (data->enumTableNext());
	}
	else
	{
		OutputMsg(rmError, "EffectsConfig is null");
	}

	data->closeTable();

	return true;
}

bool SkillConfigPool::LoadSkillPowerConfig(GameConfigData* data)
{
	if (!data->openGlobalTable("SkillPowerConfig"))
	{
		OutputMsg(rmError, ("can't open SkillPowerConfig table"));
		return false;
	}

	if (data->enumTableFirst())
	{
		do {
			int index = data->getFieldInt("index");
			int powerPerLevel = data->getFieldInt("powerPerLevel");
			skill_power_pool[index] = powerPerLevel;

		} while (data->enumTableNext());
	}
	else
	{
		OutputMsg(rmError, "SkillPowerConfig is null");
	}

	data->closeTable();

	return true;
}

const SkillConfig* SkillConfigPool::GetSkillConfig(int id)
{
	auto it = skill_config_pool_.find(id);
	if (it == skill_config_pool_.end())
		return nullptr;
	return &it->second;
}

const EffectConfig* SkillConfigPool::GetEffectConfig(int id)
{
	auto it = effect_config_pool_.find(id);
	if (it == effect_config_pool_.end())
		return nullptr;
	return &it->second;
}

float SkillConfigPool::GetSkillCastDistance(int id)
{
	auto skill = GetSkillConfig(id);
	if (skill)
		return skill->base.cast_range;

	id = id / 1000 * 1000 + 1;
	skill = GetSkillConfig(id);
	if (skill)
		return skill->base.cast_range;
	OutputMsg(rmError, "ai skill config error, skill :%d is not found", id);

	return 2; // 太近了寻路会有问题
}

int SkillConfigPool::GetSkillCd(int id)
{
	auto skill = GetSkillConfig(id);
	if (skill)
		return skill->base.cd;

	id = id / 1000 * 1000 + 1;
	skill = GetSkillConfig(id);
	if (skill)
		return skill->base.cd;
	OutputMsg(rmError, "ai skill config error, skill :%d is not found", id);

	return 1000; // 随便写的了
}



bool SkillConfigPool::LoadSkillBreak(GameConfigData* data)
{


	if (!data->openGlobalTable("SkillsBreakConf"))
	{
		OutputMsg(rmError, ("can't open SkillsBreakConf table"));
		return false;
	}

	if (data->enumTableFirst())
	{
		do {
			SkillBreakConf conf;
			//int ndef = 0;

			conf.base.id = data->getFieldInt("id");
			conf.base.cast_range = (float)data->getFieldNumber("castRange");
			conf.base.cast_type = data->getFieldInt("castType");
			conf.base.cd = data->getFieldInt("cd");
			conf.base.target_type = data->getFieldInt("targetType");
			conf.base.affect_range = data->getFieldInt("affectRange");
			conf.base.affect_count = data->getFieldInt("affectCount");
			conf.base.calc_type = data->getFieldInt("calcType");
			
			

			if (!data->openFieldTable("args"))
			{
				OutputMsg(rmError, ("SkillsBreakConf can't open args table"));
				data->closeTable();
				return false;
			}

			int len = data->getTableLen();
			conf.args.resize(len);

			int index = 0;
			if (data->enumTableFirst())
			{
				do {
					SkillBreakConf::arg& info = conf.args[index];
					if (!LoadOneBreakArgs(data, info))
					{
						data->closeTable();
						data->closeTable();
						return false;
					}
					++index;

				} while (data->enumTableNext());
			}
			data->closeTable();

			conf.power = data->getFieldInt("power");
			break_conf_pool_[conf.base.id] = conf;
		} while (data->enumTableNext());
	}
	else
	{
		OutputMsg(rmError, "SkillsBreakConf is null");
	}

	data->closeTable();
	return true;
}

bool SkillConfigPool::LoadOneBreakArgs(GameConfigData* data, SkillBreakConf::arg& info)
{
	int def = 0;
	info.type = data->getFieldInt("type", &def);

	if (data->openFieldTable("vals"))
	{
		int len = data->getTableLen();
		if (len > MAX_BREAK_VAL)
		{
			data->closeTable();
			return false;
		}

		int index = 0;
		if (data->enumTableFirst())
		{
			do {
				info.vals[index] = (float)data->getFieldNumber(NULL);
				++index;

			} while (data->enumTableNext());

		}
		data->closeTable();
	}

	return true;
}


const SkillBreakConf* SkillConfigPool::GetSkillBreakConfig(int id)
{
	auto it = break_conf_pool_.find(id);
	if (it == break_conf_pool_.end())
		return nullptr;
	return &it->second;
}

bool SkillConfigPool::LoadOneRevise(GameConfigData* data, ImbaSkillRevise &revise) {
	int ndef = 0; double fdef = 0.0;
	revise.a = (float)data->getFieldNumber("a", &fdef);
	revise.b = data->getFieldInt("b", &ndef);
	revise.cd = data->getFieldInt("cd", &ndef);
	revise.d = data->getFieldInt("d", &ndef);
	revise.crit = data->getFieldInt("crit", &ndef);
	revise.critDamage = data->getFieldInt("critDamage", &ndef);

	if (data->fieldTableExists("selfEff") && data->openFieldTable("selfEff"))
	{
		if (data->enumTableFirst())
		{
			do {
				int id = data->getFieldInt(NULL);
				if (effect_config_pool_.find(id) == effect_config_pool_.end())
				{
					OutputMsg(rmError, "effect %d 's config is null ", id);
					return false;
				}
				revise.self_eff.push_back(id);
			} while (data->enumTableNext());
		}
		data->closeTable();
	}

	if (data->fieldTableExists("targetEff") && data->openFieldTable("targetEff"))
	{
		if (data->enumTableFirst())
		{
			do {
				int id = data->getFieldInt(NULL);
				if (effect_config_pool_.find(id) == effect_config_pool_.end())
				{
					OutputMsg(rmError, "effect %d 's config is null ", id);
					return false;
				}
				revise.target_eff.push_back(id);
			} while (data->enumTableNext());
		}
		data->closeTable();
	}

	if (data->fieldTableExists("args") && data->openFieldTable("args"))
	{
		if (data->enumTableFirst())
		{
			do {
				ImbaSkillRevise::arg info;
				LoadOneSevArgs(data, info);
				revise.args.push_back(info);
			} while (data->enumTableNext());
		}
		data->closeTable();
	}

	return true;
}

bool SkillConfigPool::LoadImbaSkillRevise(GameConfigData* data)
{
	if (!data->openGlobalTable("ImbaSkillReviseConfig"))
	{
		OutputMsg(rmError, ("can't open ImbaSkillReviseConfig table"));
		return false;
	}

	if (data->enumTableFirst())
	{
		do {
			ImbaSkillReviseCfg conf;
			int ndef = 0; //double fdef = 0.0;

			int skill_id = data->getFieldInt("skill", &ndef);
			conf.imba_id = data->getFieldInt("imba_id", &ndef);

			LoadOneRevise(data, conf.revise);

			imba_revise_pool_[skill_id].push_back(conf);
		} while (data->enumTableNext());
	}
	else
	{
		OutputMsg(rmError, "ImbaSkillReviseConfig is null");
	}

	data->closeTable();
	return true;
}

bool SkillConfigPool::LoadGwSkillRevise(GameConfigData* data)
{
	
	if (!data->openGlobalTable("GWSkillReviseConfig"))
	{
		OutputMsg(rmError, ("can't open GWSkillReviseConfig table"));
		return false;
	}

	if (data->enumTableFirst())
	{
		do {
			ImbaSkillRevise revise;
			int ndef = 0; double fdef = 0.0;

			int skill_id = data->getFieldInt("skill", &ndef);
			int gwlv = data->getFieldInt("gwIndex", &ndef);
			revise.base.affect_range = data->getFieldInt("affectRange", &ndef);
			revise.base.affect_count = data->getFieldInt("affectCount", &ndef);
			revise.base.cast_range = (float)data->getFieldNumber("castRange", &fdef);
			ndef = 2;
			revise.base.cast_type = data->getFieldInt("castType", &ndef);
			revise.base.target_type = data->getFieldInt("targetType", &ndef);
			ndef = 1;
			revise.base.calc_type = data->getFieldInt("calcType", &ndef);

			LoadOneRevise(data, revise);

			gw_revise_pool_[skill_id][gwlv] = revise;
		} while (data->enumTableNext());
	}
	else
	{
		OutputMsg(rmError, "ImbaSkillReviseConfig is null");
	}

	data->closeTable();
	
	return true;
}

bool SkillConfigPool::LoadOneSevArgs(GameConfigData* data, ImbaSkillRevise::arg& info)
{
	int def = 0;
	info.type = data->getFieldInt("type", &def);

	if (data->openFieldTable("vals"))
	{

		int index = 0;
		if (data->enumTableFirst())
		{
			do {
				info.vals[index] = (float)data->getFieldNumber(NULL);
				++index;

			} while (data->enumTableNext());

		}
		data->closeTable();
	}

	return true;
}

const ImbaSkillReviseCfgList* SkillConfigPool::GetImbaSkillReviseConfig(int id)
{
	auto it = imba_revise_pool_.find(id);
	if (it == imba_revise_pool_.end())
		return nullptr;
	return &it->second;
}

const GWSkillReviseMap* SkillConfigPool::GetGWSkillReviseConfig(int id)
{
	auto it = gw_revise_pool_.find(id);
	if (it == gw_revise_pool_.end())
		return nullptr;
	return &it->second;
}
