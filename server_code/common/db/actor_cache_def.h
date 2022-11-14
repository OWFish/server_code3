#pragma once


enum DBCacheType
{
	DBCacheType_Undefined = -1, // 返回错误类型

	DBCacheType_ActorBasic = 0,	// 角色基础数据
	DBCacheType_RoleData,		// 子角色数据
	DBCacheType_ScriptData,
	DBCacheType_ItemBag,		// 道具包
	DBCacheType_EquipBag,		// 装备包
	DBCacheType_Mail,			// 邮件
	DBCacheType_Store,			// 商城
	DBCacheType_Depot,			// 仓库
	DBCacheType_Guild,			// 公会
	DBCacheType_TogHitEquip,	// 合击装备
	DBCacheType_CsScriptData,   //跨服的lua
	DBCacheType_ActorCache,   //跨服缓冲用

	DBCacheType_Max,
};

// 角色Cache数据类型 (旧的 弃用 暂时先留着 工作量太大)
enum enActorCacheDataType
{	
	enCT_ActorBasicData,					// 角色基本数据
	enCT_BagItemData,						// 角色背包数据
	enCT_EquipItemData,						// 角色装备数据
	enCT_DepotItemData,						// 角色仓库数据		
	enCT_SkillData,							// 技能数据
	enCT_QuestData,							// 任务数据
	enCT_GuildData,							// 公会数据
	enCT_MiscData,							// 杂项数据
	enCT_ScriptData,						// 脚本二进制数据
	enCT_GemData,							// 宝物数据
	enCT_MountData,							// 宠物数据
	enCT_DmkjItemData,						//盗梦空间仓库
	enCT_WingData,							//翅膀数据
	enCT_BuffData,							//buff数据
	enCT_AchieveData,						// 成就
	enCT_CaleData,							//副本统计数据
	enCT_FbCountData,						//每天进入副本次数
	enCT_PlotData,							// 剧情(已无用）
	enCT_MiscStruct,						// 杂七杂八数据(已无用）
	enCT_PetSkill,						// 宠物技能
	enCT_EntrustItemData,				// 副本委托仓库
	enCT_PetItemData,						//宠物装备
	enCT_PetCrossItem,					//宠物闯关仓库
	enCT_CrossScriptData,				// 跨服战脚本数据
	enCT_TongTianTaData,				//通天塔数据
	enCT_MijiItem,                    //秘籍数据
	enCT_PetBase,						//宠物系统
	enCT_MarryBase,				  //婚姻系统
	enCT_Max,						 // 最大角色Cache数据类型
};