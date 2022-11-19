#include "StdAfx.h"
#include "ai_config.h"
#include "../ai.h"
#include "../ai_condition.h"
#include "skill/skill_config.h"
#include "../skill_condition.h"


std::map<int, AIConfig>  AIConfigPool::config_pool_;


bool ReadMonsterSkills(GameConfigData *data, AIConfig* conf);
bool ReadOneAI(GameConfigData *data, AIConfig* conf, int idx);
bool ReadState(int state_id, GameConfigData *data, AIEventConfigs* conf);
bool ReadConditions(GameConfigData *data, AIConditionConfigs* conf);
bool ReadActions(GameConfigData* data, AIActionConfigs* conf, int index);
bool ReadCondition(GameConfigData* data, AIConditionConfig* conf);
bool ReadSkillCondition(GameConfigData* data, SkillConditionConfig* conf);

bool ReadOneAI(GameConfigData *data, AIConfig* conf, int idx)
{
	int n_def = 0;
	bool bdef = false;
	conf->id = data->getFieldInt("id");
	//if (conf->id != idx)
	//	return false;
	conf->aggressive = data->getFieldInt("aggressive") > 0 ? true : false;
	conf->can_recover = data->getFieldInt("canRecover") > 0 ? true : false;
	conf->dead_time = data->getFieldInt("dead_time", &n_def);
	conf->vision = data->getFieldInt("vision");
	conf->home_range = data->getFieldInt("home_range");
	conf->maxDam = data->getFieldBoolean("maxdam", &bdef);

	if (!ReadMonsterSkills(data, conf))
		return false;

	ReadState(AI::asBorn, data, &conf->born);
	ReadState(AI::asIdle, data, &conf->idle);
	ReadState(AI::asBattle, data, &conf->battle);
	ReadState(AI::asBack, data, &conf->back);
	ReadState(AI::asDead, data, &conf->dead);

	return true;
}

bool ReadMonsterSkills(GameConfigData *data, AIConfig* conf)
{
	//怪物的技能列表
	if (!data->fieldTableExists("skills") || !data->openFieldTable("skills")) {
		return true;
	}

	const int cnt = data->getTableLen();
	if (cnt <= 0)	// 没有技能
	{
		data->closeTable();
		return true;
	}

	if (cnt > AI::MAX_SKILL)
	{
		OutputMsg(rmError, "monster skill count is too much!%d,max=%d", cnt, AI::MAX_SKILL);
		data->closeTable();
		return false;
	}

	conf->skills.resize(cnt);
	if (data->enumTableFirst())
	{
		int n_idx = 0;
		int ndelay = 0;
		int ncd = 500;

		do
		{
			AiSkill *p_skill = &conf->skills[n_idx];
			p_skill->index = n_idx;
			p_skill->skill_id = data->getFieldInt("id");
			p_skill->cd = (uint16_t)data->getFieldInt("cd", &ncd);
			int cd = SkillConfigPool::GetSkillCd(p_skill->skill_id);
			if (cd > p_skill->cd)	// ai里只允许比实际的长
				p_skill->cd = cd;
			p_skill->first_delay = (uint16_t)data->getFieldInt("first_delay", &ndelay);
			ncd = 1;
			p_skill->dis = (unsigned short)(GRIDSIZE * SkillConfigPool::GetSkillCastDistance(p_skill->skill_id));
			ReadSkillCondition(data, &p_skill->cond);
			n_idx++;
		} while (data->enumTableNext());
	}

	data->closeTable();
	return true;
}

const char* getStateName(int id)
{
	switch (id)
	{
	case AI::asBorn:
		return "born";
	case AI::asIdle:
		return "idle";
	case AI::asBattle:
		return "battle";
	case AI::asBack:
		return "back";
	case AI::asDead:
		return "dead";
	default:
		return NULL;
	}
}

bool ReadState(int state_id, GameConfigData* data, AIEventConfigs* conf)
{
	const char* state_name = getStateName(state_id);
	if (!data->fieldTableExists(state_name) || !data->openFieldTable(state_name)) {
		return true;
	}

	const int cnt = data->getTableLen();
	if (cnt <= 0)	// 没有事件
	{
		data->closeTable();
		return true;
	}

	conf->resize(cnt);
	if (data->enumTableFirst())
	{
		int n_idx = 0;
		int n_def = 0;
		double n_def2 = 1;
		state_id <<= 8;		// 用8位表示event 最高支持256个event在同一个state里 - -b
		do
		{
			AIEventConfig &eventconf = (*conf)[n_idx];
			eventconf.delay = (int)data->getFieldNumber("delay", &n_def2); // 默认1
			eventconf.lcnt = data->getFieldInt("count", &n_def);	
			eventconf.interval = (int)data->getFieldNumber("interval", &n_def2);	


			ReadConditions(data, &eventconf.conditions);
			ReadActions(data, &eventconf.actions, state_id + n_idx);

			n_idx++;
		} while (data->enumTableNext());
	}

	data->closeTable();
	return true;
}


bool ReadConditions(GameConfigData *data, AIConditionConfigs* conf)
{
	if (!data->fieldTableExists("conditions") || !data->openFieldTable("conditions")) {
		return true;
	}

	const int cnt = data->getTableLen();

	if (cnt <= 0)	// 没有condition
	{
		data->closeTable();
		return true;
	}

	conf->resize(cnt);
	if (data->enumTableFirst())
	{
		int n_idx = 0;
		do
		{
			AIConditionConfig &condition = (*conf)[n_idx];
			condition.type = data->getFieldInt("type");
			if (!ReadCondition(data, &condition)){
				OutputMsg(rmWarning, "condition read failed. %d", condition.type);
				condition.type = 0;
				continue;
			}

			n_idx++;
		} while (data->enumTableNext());
	}
	data->closeTable();
	return true;
}

bool ReadActions(GameConfigData* data, AIActionConfigs* conf, int index)
{
	if (!data->fieldTableExists("actions") || !data->openFieldTable("actions")) {
		return true;
	}
	const int cnt = data->getTableLen();
	if (cnt <= 0)	// 没有事件
	{
		data->closeTable();
		return true;
	}

	conf->resize(cnt);
	if (data->enumTableFirst())
	{
		int n_idx = 0;
		double n_def = 0;
		index = index << 5;		// 用5位表示action，最高支持32个action在同一个event里
		do
		{
			AIActionConfig &action = (*conf)[n_idx];

			//action.type = getFieldInt("type");
			action.duration = (int)data->getFieldNumber("duration", &n_def) * 1000;
			action.interval = (int)data->getFieldNumber("interval", &n_def) * 1000;

			action.index = index + n_idx;
			//action.args = getFieldString("args", "");
			/*const char* args = getFieldString("args", "");
			action.args = new char[strlen(args) + 1];	// 如果反复重载就会内存泄露, 需要改成dataalloc的方式？
			strcpy(action.args, args);
			*/
			n_idx++;
		} while (data->enumTableNext());
	}
	data->closeTable();
	return true;
}

bool ReadCondition(GameConfigData* data, AIConditionConfig* conf)
{
	int type = conf->type;
	int n_def = 0;
	switch (type){
	case acTime:
	//case acPlayerCount:
		n_def = 0;
		conf->arg1 = data->getFieldInt("min", &n_def);
		conf->arg2 = data->getFieldInt("max", &n_def);
		return true;
		break;
	case acSelfHp:
	case acTargetHp:
	case acRoleMinHp:
	case acTargetDistance:
		n_def = 0;	conf->arg1 = data->getFieldInt("min", &n_def);
		n_def = 100;conf->arg2 = data->getFieldInt("max", &n_def);
		return true;
		break;
	case acSelfBuff:
	case acTargetBuff:
		conf->arg1 = data->getFieldInt("id");
		return true;
		break;
	case acHasBattlePet:
		conf->arg1 = data->getFieldInt("pet");
		return true;
		break;
	case acHatredListDistanceCount:
	case acHatreListMonDisCount:
	case acMonsterCount:
	case acTargetMonCount:
		n_def = 0;
		conf->arg1 = data->getFieldInt("min", &n_def);
		conf->arg2 = data->getFieldInt("max", &n_def);
		conf->arg3 = data->getFieldInt("count", &n_def);
		return true;
		break;
	//case acMonsterDistance:
	//	conf->arg1 = data->getFieldInt("id");
	//	conf->arg2 = data->getFieldInt("min");
	//	conf->arg3 = data->getFieldInt("max");
	//	return true;
	//	break;
	//case acPostionDistance:
	//	conf->arg1 = data->getFieldInt("px");
	//	conf->arg2 = data->getFieldInt("py");
	//	conf->arg3 = data->getFieldInt("min");
	//	conf->arg4 = data->getFieldInt("max");
	//	return true;
	//	break;

	default:
		return false;
	}

	return true;
}

bool ReadSkillCondition(GameConfigData* data, SkillConditionConfig* conf)
{
	int n_def = 0;
	conf->type = data->getFieldInt("type", &n_def);
	switch (conf->type) {
	case scMonsterCount:
	case scTargetMonCount:
		conf->arg1 = data->getFieldInt("min", &n_def);
		conf->arg2 = data->getFieldInt("max", &n_def);
		conf->arg3 = data->getFieldInt("count", &n_def);
		return true;
		break;
	default:
		return false;
	}

	return true;
}

bool AIConfigPool::Load(GameConfigData* data)
{
	if (!data->openGlobalTable("AiConfig"))
	{
		OutputMsg(rmError, "can't open AIConfigConfig table");
		return false;
	}

	if (data->enumTableFirst())
	{
		int idx = 0;
		do {
			idx = data->getFieldInt("id");
			AIConfig* aic = &config_pool_[idx];

			if (ReadOneAI(data, aic, idx) == false)
			{
				OutputMsg(rmError, "read ai config failed ,id:%d", idx);
				data->closeTable();
				return false;
			}

			idx++;
		} while (data->enumTableNext());
	}
	else
	{
		OutputMsg(rmError, "----------------------------AIConfig is null");
	}

	data->closeTable();

	return true;
}


const AIConfig* AIConfigPool::Get(int id)
{
	auto it = config_pool_.find(id);
	if (it != config_pool_.end())
		return &(it->second);
	return NULL;
}