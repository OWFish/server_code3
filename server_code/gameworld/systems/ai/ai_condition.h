#ifndef _AI_CONDITION_H_
#define _AI_CONDITION_H_

enum AIConditionType
{
	acNull = 0,			// 空条件或解析失败的条件

	acTime,				// 进入该阶段时间
	acSelfHp,			// 自己的血量
	acTargetHp,			// 当前目标血量
	acTargetDistance,	// 与目标距离
	acSelfBuff,			// 自己是否有指定buff
	acTargetBuff,		// 目标是否有指定buff
	acHasBattlePet,		// 是否有战斗宠物
	acRoleMinHp,		// 自己角色最少血量 (role限定ai)
	acHatredListDistanceCount,   // 仇恨列表中的敌人距离和数量
	acHatreListMonDisCount,//仇恨列表中的怪物距离和数量
	acMonsterCount,		 // 自身周围怪数量
	acTargetMonCount,   //目标周围怪数量
	//acMonsterDistance,	// 与指定怪的距离， 找到的第一个为准
	//acPostionDistance,	// 与指定位置的距离
	//acPlayerCount,		// 周围敌人数量

	acConditionCount,
};

class Creature;
class AIState;
struct AIConditionConfig;

namespace AICondition {
	bool Check(const AIConditionConfig *config, Creature *self, AIState *ai_state);
}; // end of namespace


#endif