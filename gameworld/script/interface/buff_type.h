#ifndef _BUFF_TYPE_H_
#define _BUFF_TYPE_H_
/************************************************************************
* 本文件定义游戏中使用的buff类型，比如沉默，隐身等。
* 文件中同时会定义这些buff会带来的属性加成等（当然，跟属性相关的可以考虑改到配置文件里）
* 注意：在之前的项目中，buff类型和属性类型是合并在一起的，现在把它们定义分开）
* 括号<> 是用于自动生成代码。里面的内容是对应的属性类型（看attr_type.h定义),表示buff
* 会产生对应的属性增长。没有<> 表示buff不会改变属性
* 另外注意buff类型必须是连续的，即使不用也要有个编号占位（也可注释掉）
************************************************************************/

//tolua_begin

enum BuffType
{
	bUndefined = 0,				//未定义
	bSilence = 1,				// 沉默
	bMoveForbid = 2,	 //定身 禁止移动,不可移动，但可施放技能
	bDizzy = 3,		  // 晕眩,不可移动，不可施放普通技能，眩晕状态下部分特殊技能可使用
	bControlSkillImmune = 4, // 免疫各种控制技能
	bInnnerSkillForbid = 5, // 封，禁止使用内攻攻击
	bOutSkillForbid = 6,  // 断，禁止使用外攻攻击
	bInnerAttackImmune = 7, // 免疫内攻攻击 （包括控制性法术技能：封、定身、减速）
	bOutAttackImmune = 8, // 免疫外攻攻击（包括控制性物理技能：断、定身、减速）
	bHide = 9,							   // 隐身
	bReliveProtectState = 10,				   // 复活保护状态

	bHpAdd = 11,					//血增加<aUndefined,adInt>
	bHpPower = 12,					//血倍率增加<aUndefined,adFloat>
	bMpAdd = 13 ,					//蓝增加<aUndefined,adInt>
	bMpPower = 14,					//蓝倍率增加<aUndefined,adFloat>
	bMoveSpeedAdd = 15 ,			//移动速度增加<aMoveSpeedAdd,adInt>
	bMoveSpeedPower = 16,			//移动速度倍率增加<aMoveSpeedPower,adFloat>
	bMaxHpAdd = 17,					//最大血增加<aMaxHpAdd,adInt>
	bMaxHpPower = 18,				//最大血倍率增加<aMaxHpPower,adFloat>
	bMaxMpAdd = 19,					//最大蓝增加<aMaxMpAdd,adInt>
	bMaxMpPower = 20,				//最大蓝倍率增加<aMaxMpPower,adFloat>
	bOutAttackAdd = 21,				//物理攻击增加<aOutAttackAdd,adInt>
	bOutAttackPower = 22,			//物理攻击倍率增加<aOutAttackPower,adFloat>
	bOutDefenceAdd = 23,			//物理防御增加<aOutDefenceAdd,adInt>
	bOutDefencePower = 24,			//物理防御倍率增加<aOutDefencePower,adFloat>
	bAddDefStrike = 25,				//抗暴击值增加<aAddDefStrike,adInt>
	bAddDefStrikePower = 26,		//抗暴击倍率增加<aAddDefStrikePower,adFloat>
	bAllAttackAdd = 27,				// 所有攻击力增加<aAllAttackAdd,adInt>
	bAllAttackPower = 28,			//所有攻击力倍率增加<aAllAttackPower,adFloat>
	bSubDef = 29,					//无视防御<aSubDef,adInt>
	bSubDefPower = 30,				//无视防御增加<aSubDefPower,adFloat>
	bInnerAttackAdd = 31,			//法术攻击增加<aInnerAttackAdd,adInt>
	bInnerAttackPower = 32,			//法术攻击倍率增加<aInnerAttackPower,adFloat>
	bInnerDefenceAdd = 33,			//法术防御增加<aInnerDefenceAdd,adInt>
	bInnerDefencePower = 34,			//法术防御倍率增加<aInnerDefencePower,adFloat>
	bCriticalStrikesValueAdd = 35,	//暴击值的增加<aCriticalStrikesValueAdd,adInt>
	bCriticalStrikesValuePower = 36,	//暴击值倍率增加<aCriticalStrikesValuePower,adFloat>
	bDodgeValueAdd = 37 ,				//闪避值增加<aDodgeValueAdd,adInt>
	bDodgeValuePower = 38,			//闪避值倍率增加<aDodgeValuePower,adFloat>
	bHitValueAdd = 39,				//命中值增加<aHitValueAdd,adInt>
	bHitValuePower = 40,				//命中值倍率增加<aHitValuePower,adFloat>
	bAttackAppend = 41,				// 伤害追加<aAttackAppend,adInt>
	bAttackAppendPower = 42,		// 伤害追加倍率增加/减低<aAttackAppendPower,adFloat>
	bHpRenewAdd = 43,					//HP恢复增加<aHpRenewAdd,adInt>
	bHpRenewPower = 44,					//HP恢复倍率增加<aHpRenewPower,adFloat>
	bMpRenewAdd = 45,					//MP恢复增加<aMpRenewAdd,adInt>
	bMpRenewPower = 46,					//MP恢复倍率增加<aMpRenewPower,adFloat>
	bAttackSpeedAdd = 47,				//增加攻击速度<aAttackSpeedAdd,adInt>
	bAttackSpeedPower = 48,			  //攻击速度增加比率<aAttackSpeedPower,adFloat>
	bInAttackDamageValueAdd = 49,		  //承受法术伤害的数值提高<aInAttackDamageValueAdd,adInt>
	bInAttackDamageValueAddPower = 50,	 //承受法术伤害的倍率提高<aInAttackDamageValueAddPower,adFloat>
	bOutAttackDamageValueAdd = 51,		  //承受物理伤害的数值提高<aOutAttackDamageValueAdd,adInt>
	bOutAttackDamageValueAddPower = 52,	 //承受物理伤害的倍率提高<aOutAttackDamageValueAddPower,adFloat>

	bDamageAbsorb = 53,  //伤害吸收,自己或队友施放护盾，吸收N点伤害
	bDamageAbsorbRate = 54, //按比例吸收伤害,降低一定百分比的所受伤害
	bDamage2Mp = 55, // 伤害转换为蓝的消耗,吸收N点伤害，每吸收一点伤害需要损耗m点内力值，内力不足时护盾消失

	bDamageDeepen = 56, //伤害加深<aUndefined,adFloat>
	bRiseUp = 57,		//跳劈腾空buff (不会被定身，不会被眩晕)
	bXuanFengZhan = 58, //旋风斩免控buff (不会被定身，不会被眩晕)
	bBaoyi = 59,		//爆衣buff
	bBlackScreen = 60,	//沙尘暴(赛马)
	bSoap = 61,			//肥皂(赛马)
	bMagnet = 62,		//磁铁(赛马)
	bCriticalStrikeDamageRateAdd = 63, //物理暴击伤害比率的提高，默认的是1.5倍的，可以提升<aCriticalStrikeDamageRateAdd,adFloat>
	bDizzyRate = 64,			 // 攻击打出晕眩的几率<aDizzyRate,adInt>
	bExpAdd = 65,								  //经验增加一个数值
	bDizzyDef = 66,							   // 眩晕免疫概率<aDizzyDef,adInt>
	bMeiHuo = 67,							  //魅惑(赛马)
	bSuperMan = 68,							  //无敌,能攻击，不能被攻击
	bHitFinalAddPower = 69,					  //最终命中增加百分比
	bAllAttackDamageRateAdd = 70,			//承受物理,法术伤害的倍率提高<aAllAttackDamageRateAdd,adFloat>
	bDamageRate = 71,					 // 技能伤害追加百分比，为10000的倍数，比如2000表示0.2,整数<aDamageRate,adInt>
	bUseSkill = 72,						  //使用一个buff的效果是定时使用技能
	bHitFinalAddRate = 73,				 //最终命中倍率增加<aHitFinalAddRate,adInt>
	bHitFinalMin = 74,					 //最终闪避倍率(不能超过这个值)<aHitFinalMin,adInt>
	bExpPower = 75,						   // 经验的增加的倍率<aExpPower,adFloat>
	bUnableDoubleSunbath = 76,						  //无法共浴的DEBUFF
	bReboundAttack = 77,						 // 反弹内外功的伤害百分比, 整数<aReboundAttack,adFloat>
	bPetAddHp = 78,								// 宠物加血
	bRefFeatureForbid = 79,					// 禁止刷新外观
	bSuperExpTime = 80,						//多倍经验挂机BUFF
	bInnerAttackDamageRateAdd = 81,		  //承受法术伤害的倍率提高<aInnerAttackDamageRateAdd,adFloat>
	bOutAttackDamageRateAdd = 82,		   //承受物理伤害的倍率提高<aOutAttackDamageRateAdd,adFloat>
	bInnerAttackDamageRebound = 83,		  //承受法术攻击伤害将有多少比例反弹给对方<aInnerAttackDamageRebound,adFloat>
	bOutAttackDamageRebound = 84,			//承受物理攻击伤害将有多少比例反弹给对方<aOutAttackDamageRebound,adFloat>
	bDodgeFinalAddRate = 85,			  //最终闪避倍率增加<aDodgeFinalAddRate,adInt>
	bGuildAnimal = 86,				 //帮派神兽buff<aDodgeFinalAddRate,adInt>（不需要了）
	bSilenceDef = 87,				// 沉默免疫的概率<aSilenceDef,adInt>
	bSelfCSDamageDec = 88,				//受到暴击伤害减少n% (以百分比的形式，减少用户受到的暴击伤害)<aSelfCSDamageDec,adFloat>
	bRenownAdd = 89,					//声望增加 n (整型)
	bDamage2Hp = 90,				   // 吸血的百分比（把给对方的伤害的一部分转换为自己的血）<aDamage2Hp,adFloat>
	bRenowRateAdd = 91,				//声望的获取速度加成(浮点型),+n%<aRenowRateAdd,adFloat>
	bBananaSkin = 92,				//香蕉皮(赛马)
	bNotUseMount	= 93,				// 禁止上坐骑
	bNotTeleport	= 94,			// 禁止速传
	bDiChi = 95,					// 地刺(赛马)
	bAllDefenceAdd = 96,		// 所有防御增加<aAllDefenceAdd,adInt>
	bAllDefenceRateAdd = 97,	// 所有防御倍率增加<aAllDefenceRateAdd,adFloat>
	bThreat = 98,				// 恐吓buff(宠物无法攻击)
	bWuDi = 99,					//无敌(赛马)
	bAbsorbHpByAttack = 100,	//根据攻击力吸血
	// 神器相关
	//bFTYVal = 101,				// 翻天印对目标造成额外A点伤害 (取消，这些属性都是通过各自系统产生，而不是buff系统，所以这里定义不需要）

	bStrikeState = 102,			// 100%暴击状态
	bTotalExpRate = 103,		// 总经验倍率增加，小数,暂时只算打怪经验<aUndefined,adFloat>

	bImprison = 104,			// 禁锢效果(不可攻击和不可移动,禁锢状态不可被移除)

	bActorExtraDamage = 105,		// 标记者造成的伤害造成额外的伤害，小数
	bAbsorbRate = 106, // 吸血的百分比,如果是群攻技能只吸第一个玩家的血(暂时只能秘籍中用)
	//bActorExpress = 107,   //用于改变玩家一些特性，特定group表示改变颜色(取消）
	//bSkillDamageRate = 108, //关联的技能的buff，，，使用技能造成伤害,  华元斩(取消）
	bAbsorbHp = 109, // 对目标造成伤害，并回复相应的血量给玩家 ,小数<aUndefined,adFloat>
	//bSkillDamageRate1 = 110, //关联技能buff，踏云(取消）
	bTeamExp = 111, // 组队经验buff,小数<aUndefined, adFloat>
	bSceneExpRate = 112, // 特殊场景经验加成,小数
	bFlower = 113, // 鲜花BUFF
	//浪漫沙滩相关
	bSunshade = 114, // 太阳伞buff
	bRepulseStop = 115,	//答题 抗击飞buff

	bAddHpByDamage = 116, //被攻击后几率恢复<aAddHpByDamage,adFloat>

	/* ★添加新的属性类型枚举成员请在GameAttributeCount前添加！★ */
	GameBuffCount,	//此枚举成员的值将会自动取值为已定义属性的数量
	/* ★添加新的属性类型枚举成员请在GameAttributeCount前添加！★ */
} ;

//tolua_end

extern GAMEATTRTYPE Buff2Attr[GameBuffCount];
extern eAttribueTypeDataType BuffDataType[GameBuffCount];

#endif

