#ifndef _PROPERTY_ID_DEF_H_
#define _PROPERTY_ID_DEF_H_

///下面这里定义的是实体的属性的ID，脚本里需要用到,通过实体的id可以获取实体的属性

//tolua_begin

//下面这些是属性的偏移
enum enPropEntity
{
    P_ID = 0,   // 实体的id
    P_POS_X , // 位置 posx
    P_POS_Y , // 位置pos y
    P_MODELID, // 实体的模型ID
    P_ICON,  // 头像ID
    P_DIR,   // 实体的朝向
    P_MAX_ENTITY,
};

enum enPropCreature
{
    P_LEVEL = P_MAX_ENTITY, // 等级
    P_HP , //血
    P_MP ,  //蓝
    P_SPEED, //移动1格需要的时间，单位ms
    P_MAXHP, //最大血，也就是生命
    P_MAXMP,//最大蓝，也就是内力
    P_OUT_ATTACK, //外功攻击
    P_OUT_DEFENCE,//外功防御
    P_DEFCRITICALSTRIKES,//抗爆击值
    P_ALL_ATTACK, // 所有攻击力
    P_SUB_DEF, // 无视防御
    P_IN_ATTACK,//内功攻击
    P_IN_DEFENCE,//内功防御

    P_CRITICALSTRIKES,	// 爆击值
    P_DODGERATE, // 闪避值
    P_HITRATE,	// 命中值

    P_ATTACK_ADD,	// 伤害追加
    P_HP_RENEW,//HP恢复
    P_MP_RENEW,//MP恢复
    P_ATTACK_SPEED, //攻击速度

    P_IN_ATTACK_DAMAGE_ADD, // 承受内功伤害的数值提高
    P_OUT_ATTACK_DAMAGE_ADD,	// 承受外功伤害的数值提高

    P_THUNDER_ATTACK,	//雷攻
    P_THUNDER_DEFENCE,	//雷抗
    P_POISON_ATTACK,	//毒攻
    P_POISON_DEFENCE,	//毒抗
    P_ICE_ATTACK,		//冰攻
    P_ICE_DEFENCE,		//冰抗
    P_FIRE_ATTACK,		//火攻
    P_FIRE_DEFENCE,		//火抗

	P_STATE, //生物的状态,死亡，打坐等等

	P_BASE_MAXHP, //基础的最大血,等级带来的MaxHp,不包括buff，装备等附加的
	P_BASE_MAXMP, //基础的最大蓝,等级带来的MaxMp,不包括buff，装备等附加的

	P_STAND_POINT,	//立场，立场不为0且不相等的可以互相攻击
	
	P_RESEVS0,		//保留字段
	P_RESEVS1,		//保留字段

    P_MAX_CREATURE,		//
};

//怪物的
enum enPropMonster
{
    P_MONSTER_START = P_MAX_CREATURE,
    P_BORNPOINT = P_MONSTER_START, // 怪物的出生点(无用）
    P_LEVEL_DIFF,					// 无用
    //// 以下属性是为了给宠物的
    P_PET_TITLE,					// 宠物的称号，低2位是等阶称号，高2位是兽阶称号，如果不是宠物，则为0
    P_PET_COLOR,
    P_PET_RANK_TITLE,
    P_MAX_MONSTER,
};

enum enPropActor
{
    P_WEAPON = P_MAX_CREATURE,   //武器的外观属性
    P_MOUNT,      //坐骑的外观属性
    P_DIZZY_RATE11,		 // 低2为攻击打出晕眩的几率,高2位是烦晕眩几率(取消
    P_DIZZY_TIME1,        // 攻击打出晕眩的时间（取消）
    P_HP_STORE,        //hp存量
    P_MP_STORE,          //宠物的hp存量(旧:mp存量)
    P_SPIRIT,		         //精灵样式
    P_PK_MOD,   //玩家的PK模式
    P_STRONG_EFFECT, //强化特效
    P_WING, // 翅膀特效
    P_STAGE_EFFECT, //品质特效

    P_PET_HP_STORE,     // 宠物药包
    PROP_ACTOR_XIUWEI_RENEW_RATE, //玩家的修为的恢复速度(取消）

    P_SEX , //性别
    P_VOCATION , //职业
    P_EXP , //这个多1个字节,uint64的
    P_PK_VALUE = P_EXP + 2, //玩家的pk值(杀戮值)（已无用）
    P_BAG_GRID, //背包的格子数量
    P_WEEK_CHARM,  // 周魅力值
    P_BIND_COIN, //绑定金钱
    P_COIN, //非绑定金钱
    P_BIND_YB, //绑定元宝
    P_YB, //非绑定元宝
    P_SHENGWANG,  //玩家的声望
    P_CHARM, //魅力值，男的叫帅气值，女的叫魅力值
    P_SPIRIT_SLOT, //宝物开通的槽位的数目(貌似没用）
    P_RENOWN, //历练
    P_GUILD_ID , //帮派的ID
    P_TEAM_ID, //队伍的ID
    P_SOCIAL,// 社会关系的mask，是一些bit位合用的
    P_GUILD_EXP, //帮会贡献度
    P_LUCKY, //幸运值
    P_SYS_OPEN, // 开启系统的开放情况
    P_ROOT_EXP_POWER,    // 灵气增长的倍率
    P_CHANGE_MODEL,		 // 变身后的模型(不存盘)
    PROP_BANGBANGTANG_EXP, ////棒棒糖经验的增长的速度(这功能应该没用了）

    PROP_ACTOR_MAX_EXP,     //玩家的最大经验，64位的(貌似无用）
    P_GIVE_YB = PROP_ACTOR_MAX_EXP + 2, //元宝中有多少是赠送的元宝
    P_CRITICAL_STRIKE, //暴击的伤害百分比
    P_EXP_RATE,     //玩家经验的增长的速度，默认是1倍的

    P_DEPOT_GRID,   // 仓库打开格子数量
    P_ANGER, // 怒气值
    P_ROOT_EXP,  // 灵气值
	P_ACHIEVEPOINT, //完成的成就个数(排行榜)
    P_ZYCONT,//阵营的贡献度(不要直接修改！！！ 调用Actor的接口ChangeZYCount进行修改)
    P_QQ_VIP,  // vip信息数据
    P_WING_ID,	// 翅膀id
    P_WING_SCORE,	// 翅膀评分
    P_PET_SCORE,	// 宠物评分
    PROP_ACTOR_VIPFLAG, // VIP开通标记，通过位掩码标记各种VIP类型。enVIPType定义着VIP类型，分别对应0-2位掩码。(好像没用）
    P_CAMP,            //玩家的阵营 1逍遥，2星尘，3逸仙
    P_PET_SLOT, //玩家开启的宠物槽位的数量（取消）
    P_HONOR,				//荣誉值
    P_QING_YUAN,  //情缘值
    PROP_ACTOR_DUR_KILLTIMES, //连斩的次数（取消）
    PROP_ACTOR_BASE_FIGHT, //今天获得的经验（取消）
    P_FIGHT_VALUE,  //战斗力
    P_MAX_RENOWN,   //玩家的最大的声望的数值
    P_RECHARGE,	// 玩家充值总金额
    P_VIP_LEVEL,  // 玩家的头衔,用于头衔系统，按位表示玩家是否有这个头衔，默认为0，取消
    P_BEAST_LEVEL,	// 玩家所在帮派的仙宗神兽等级(取消，这个放到PROP_FOOT_EFFECT)
    P_FOOT_EFFECT,  // 足迹
    P_EQUIP_SCORE,        //玩家的装备的总分
    P_HAIR_MODEL,  //时装帽外观
	P_BUBBLE,		// 气泡
	P_ACTOR_STATE,		//玩家的状态
	P_JINGJIE_TITLE,	//境界称号
	P_ZHUMOBI,			//诛魔币

    P_MAX_ACTOR,
};
//tolua_end

#endif


