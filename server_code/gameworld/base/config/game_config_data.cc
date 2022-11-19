#include "StdAfx.h"

#include "game_config_data.h"
#include "scene/fuben_config.h"
#include "scene/scene_config.h"
#include "entity/monster/monster_config.h"
#include "entity/role/role_config.h"
#include "item/item_config.h"
#include "item/container/bag_config.h"
#include "skill/skill_config.h"
#include "ai/config/ai_config.h"
#include "guild/guild_config.h"
#include "neigongsystem/neigong_config.h"
#include "prestige/prestige_helper.h"
#include "rank/rank_config.h"

const char GameConfigData::IncludeFileName[] = "data/dataconfig.txt";

static char FileDirName[] = "data";

GameConfigData::GameConfigData()
	: Inherited(), alloc_("GameConfigData")
{
}

GameConfigData::~GameConfigData()
{
	SceneConfigPool::Destructor();
}

bool GameConfigData::LoadConfig()
{
//#ifdef _MSC_VER
//	const char* paths[] = {"./data/config/", "./data/language/"};
//	file_check_.check(paths, ArrayCount(paths));
//#endif
//
	const char* result = NULL;
	stream::MemoryStream ms(NULL);

	LuaPreProcessor pp(NULL);
	pp.addIncludeDirectory(FileDirName);
	RegisteToPreprocessor(pp);

	if (ms.loadFromFile(IncludeFileName) > 0)
	{
		pp.setSize(20 * 1024 * 1024);
		result = pp.parse((const char*)ms.getMemory(), IncludeFileName);
	}

	if (result == NULL)
	{
		OutputMsg(rmError, ("preprocess file %s fail"), IncludeFileName);
		return false;
	}

	if (!setScript(result))
	{
		const char* script_txt = NULL;
		script_txt = pp.parse((const char*)ms.getMemory(), IncludeFileName);

		// 输出脚本，用于调试
		FILE* fp = fopen("d:\\scripterror.txt", "wb");

		if (fp)
		{
			fputs(script_txt, fp);
			fclose(fp);
		}

		OutputMsg(rmError, ("preprocess files fail"));
		return false;
	}
	//开始加载dataconfig中的配置
	if (!FubenConfigPool::Load(this)) return false;
	if (!SceneConfigPool::Load(this)) return false;
	if (!MonsterConfigPool::Load(this)) return false;
	if (!RoleConfigPool::Load(this)) return false;
	if (!ItemConfigPool::Load(this)) return false;
	if (!ItemConfigPool::LoadEquip(this)) return false;
	if (!SkillConfigPool::LoadEffect(this)) return false;
	if (!SkillConfigPool::LoadSkill(this)) return false;
	//if (!SkillConfigPool::LoadSkillBreak(this)) return false;
	if (!SkillConfigPool::LoadImbaSkillRevise(this)) return false;
	if (!SkillConfigPool::LoadGwSkillRevise(this)) return false;
	if (!AIConfigPool::Load(this)) return false;
	//if (!ItemConfigPool::LoadSmelt(this)) return false;
	if (!ItemConfigPool::LoadLevelup(this)) return false;
	if (!ItemConfigPool::LoadCompose(this)) return false;
	if (!ItemConfigPool::LoadLegendAttr(this)) return false;
	if (!BattleAttribute::LoadAttrPowerConfig(this)) return false;
	if (!BagConfigPool::LoadBase(this)) return false;
	if (!BagConfigPool::LoadExpand(this)) return false;
	if (!BagConfigPool::LoadVipGrid(this)) return false;
	if (!SkillConfigPool::LoadSkillPowerConfig(this)) return false;
	if (!GuildConfig::LoadGuildLevel(this)) return false;
	if (!NeigongConfig::LoadNeigongConfig(this)) return false;
	if (!PrestigeHelper::LoadPrestigeConfig(this)) return false;
	if (!RankConfigPool::Load(this)) return false;
	//if (!LoadConfigTerms())
	//	return false;

	setScript(NULL);
	OutputMsg(rmTip, ("all game config load complete!"));
	return true;
}

void GameConfigData::showError(const char* err)
{
	SetErrDesc(err);
	OutputMsg(rmError, "%s", err);
}

