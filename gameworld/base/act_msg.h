#ifndef _ACT_MSG_H_
#define _ACT_MSG_H_

class Entity;

void InitActMsgMemPool();
void ReleaseActMsgMemPool();

struct ActMsg
{
	Entity* this_;
	EntityHandle sender_;
	bool delOnDeath_;
	ActMsg() : this_(NULL), sender_(0), delOnDeath_(false)
	{
	}
	virtual void process() = 0;
	virtual void free() = 0;
};

#define VIRFUNCDEF(x) 	virtual void process();\
	virtual void free();\
	static x* alloc()

struct AMSkillResult : public ActMsg
{
	AMSkillResult()
	{
		delOnDeath_ = true;
	}
	//SKILLRESULTPARAM ret_;
	//int param1_;
	//uint16_t param2_;
	//uint16_t param3_;
	//void* param4_;
	//bool param5_;
	//uint16_t param6_;
	VIRFUNCDEF(AMSkillResult);
};

struct AMEntityEffect : public ActMsg
{
	enum 
	{
		efEntity,
		efScreen,
	};

	EntityHandle target_;
	int type_;	//特效类型, 0 - 释放在实体身上 1 - 释放在场景上
	int eid_;
	int time_;

	int ex_;	// 场景特效使用到
	int ey_;
	VIRFUNCDEF(AMEntityEffect);
	AMEntityEffect() : target_(0), type_(0)
	{
		delOnDeath_ = true;
	}
};
struct AMScriptEvent : public ActMsg
{
	void* sp_;
	VIRFUNCDEF(AMScriptEvent);
};

struct AMCommon : public ActMsg
{
	enum
	{
	    AMHPCHANGE,
	    AMQUESTSTATE,
	    AMREUSE,
	    AMTRANSFER,
	    AMDEAD,
	    AMHIDE,
	    AMSPEED,
	    AMNPCTALK,
	    AMSEDNHPCHANGE,
	    AMSENDCRITICAL,
	    AMREFRESHPET,
	    AMFULLHP,
	    AMPETBATTLE,
	    AMACCEPTREFRESHQUEST,
	    AMFINISHITEMQUEST,
	    AMADDBABY,
	    AMSENDCOLORCHANGE,
		AMREFRESHFIGHTVAL,
		AMJUMPSKILL,
	};
	int msg_;
	size_t val_;;
	EntityHandle target_;
	VIRFUNCDEF(AMCommon);
};

struct AMCreateMonster : public ActMsg
{
	int monsterid_;
	int posX1_;
	int posX2_;
	int posY1_;
	int posY2_;
	int count_;
	unsigned int liveTime_;
	bool callback_;
	int param_;
	VIRFUNCDEF(AMCreateMonster);
};

struct AMTeleportBaby : public ActMsg
{
	int sceneID_;
	int posX_;
	int posY_;
	int ownerPosX_;
	int ownerPosY_;
	int transStype_;
	VIRFUNCDEF(AMTeleportBaby);
};

struct AMJump : public ActMsg
{
	int pos_x;
	int pos_y;
	VIRFUNCDEF(AMJump);
};

struct AMMjUseSkill : public ActMsg
{
	bool pet_;
	int p1_;
	int p2_;
	int p3_;
	int p4_;
	AMMjUseSkill() : pet_(false), p1_(0), p2_(0), p3_(0), p4_(0)
	{}

	VIRFUNCDEF(AMMjUseSkill);
};

struct AMMarkerEffect : ActMsg
{
	EntityHandle target_;
	int p1_;
	int p2_;
	int p3_;
	int p4_;
	int p5_;
	VIRFUNCDEF(AMMarkerEffect);
};

struct AMUseSKill : public ActMsg
{
	int skill_id_;
	int level_;
	EntityHandle target_; //固定目标
	bool no_fix_target_;     //是否不会根据当前选定目标而发生变化
	int x_;
	int y_;
	bool needLearn_;
	AMUseSKill() : skill_id_(0), level_(0), x_(-1), y_(-1), needLearn_(false)
	{
	}
	VIRFUNCDEF(AMUseSKill);
};
#undef VIRFUNCDEF

#endif

