#ifndef _ATTRIBUTE_H_
#define _ATTRIBUTE_H_

/************************************************************************
*                          游戏属性集（新简化版）
************************************************************************/
#include "cstring"

// tolua_begin
class Attribute
{	
public:
	// 属性定义
	enum AttributeType {
		atHp = 0,	// 0,当前hp
		atMp,		// 1,当前mp
		atHpMax,	// 2,最大血量
		atMpMax,	// 3,最大mp
		atAtk,		// 4,物攻
		atDef,		// 5,物防御
		atRes,		// 6,魔法防御
		atCrit,		// 7,暴击率
		atTough,	// 8,坚韧（抗暴）
		atMoveSpeed,	// 9,移动速度
		atAttackSpeed,	// 10,攻击速度

		atHpEx,		// 11,倍率属性 10000= 100%
		atAtkEx,	// 12,倍率属性 10000= 100%
		atStunPower,	// 13,麻痹力
		atStunRes,		// 14,麻痹抗性
		atStunTime,		// 15,麻痹时间
		atDamageReduction, // 16,伤害减免 比率万分比

		atCritHurt, // 17,暴击伤害 值
		atRegeneration, // 18,每秒回复
		atCritEnhance, // 19,暴击伤害加强
		atPenetrate, // 20,穿透(无视万分比双防)

		atRoleDamageEnhance,   // 21,攻击玩家伤害加深 万份比
		atRoleDamageReduction, // 22,受到玩家伤害减免 万分比

		atDefEx,		// 23,物防御万分比
		atResEx,		// 24,魔法防御万分比
		atNeiGong, //25,当前内功
		atNeiGongMax,//26,最大内功
		atNeiGongDamageAbsorb,//27,内功吸收伤害 万分比

		atJob1HpEx,	//28,战士生效,增加最大生命
		atJob2HpEx,	//29,法师生效,增加最大生命
		atJob3HpEx,	//30,道士生效,增加最大生命

		atNeiGongRestore, //31,定时恢复内功值

		atVamirePro, //32.传世装备,攻击时吸血的概率(万份比)
		atVamirePen, //33.传世装备,攻击时吸血的伤害比例(万份比)
		atVamireCd,	//34.传世装备,攻击时吸血的cd(毫秒)

		atCursePro, //35.传世装备,诅咒概率(万份比)
		atCurseCd,  //36.传世装备,诅咒cd(毫秒)

		atAttAddDamPro, //37.攻击增加伤害的概率(万份比)(兵魂)
		atAttAddDamVal, //38.攻击增加伤害的值(兵魂)
		atBeAttAddHpPro,//39.受到攻击时候恢复生命的概率(万份比)(兵魂)
		atBeAttAddHpVal,//40.受到攻击时候恢复生命的值(兵魂)
		atAttMbAddDamPen,//41.对被麻痹的目标额外造成X%伤害提升(兵魂)
		atHpLtAddBuff,	//42.生命低于(万分比例)时,触发生命恢复buff(兵魂)
		atAttHpLtPenAddDam,//43.攻击生命低的目标增加伤害的血量比例(万份比)(兵魂)
		atAttHpLtAddDamPen,//44.攻击生命低的目标增加伤害比例(万份比)(兵魂)

		atJob1AtkEx,	//45,战士生效,增加物攻
		atJob2AtkEx,	//46,法师生效,增加物攻
		atJob3AtkEx,	//47,道士生效,增加物攻

		atJob1DefEx,	//48,战士生效,增加物防御
		atJob2DefEx,	//49,法师生效,增加物防御
		atJob3DefEx,	//50,道士生效,增加物防御

		atJob1ResEx,	//51,战士生效,增加魔法防御
		atJob2ResEx,	//52,法师生效,增加魔法防御
		atJob3ResEx,	//53,道士生效,增加魔法防御

		atAttPerDamPan, //54.命中时追加当前伤害50%的额外伤害的机率(万份比)(兵魂)
		atDamageEnhance,//55.对目标加深伤害万份比
		atCritEnhanceResist, // 56,暴击伤害抵抗率
		atHolyDamege,		//57.神圣伤害固定值
		atHolyMaster,		//58.神圣伤害精通率
		atHolyResist,		//59.神圣伤害抵抗率
		atTogetherHolyDamege,		//60.合击神圣伤害固定值
		atTogetherHolyMaster,		//61.合击神圣伤害精通率
		atTogetherHolyResist,		//62.合击神圣伤害抵抗率
		atZhuiMingPro, //63.触发追命伤害的概率(万份比)
		atZhuiMingVal, //64.追命伤害(固定值)
		atHuiXinDamage,// 65,会心伤害率(万份比)
		atNeiGongEx, //66.内功倍率(万分比)
		atDeadLyPro,		//67.致命一击概率
		atDeadLyMaster,		//68.致命一击伤害精通率
		atDeadLyResist,		//69.致命一击伤害抵抗率
		atAddEnemyHp,		//70.自己被打后给对方加血(固定值)
		atHurtMyself,		//71.攻击对方后自己掉血(万份比)
		atBladeMailPro,  //72.刃甲概率(万份比)
		atBladeMailPer,  //73.刃甲反伤(万份比)
		atDefPen,		 //74.物防穿透(万份比)
		atResPen,		 //75.魔防穿透(万份比)
		atDeadLyHurt,    //76.致命一击附加伤害(固定值)
		atDeadLyHurtResist,    //77.致命一击附加伤害减免(固定值)
		atCritHurtResist, //78.暴击附加伤害减免(固定值)
		atHunGuPro, //79.魂骨6件套共鸣触发概率
		atHunGuHurt, //80.魂骨6件套共鸣增加伤害万分比
		atHunGuCd, //81.魂骨6件套共鸣cd
		atHearthDamege,//82.心法3额外伤害(固定值)
		atHearthHurt,//83.心法3额外伤害率(万份比)
		atHearthCount,//84.心法3每N次触发82and83

		atCount,
	};

public:
	Attribute();
	Attribute(const Attribute& attrs);
	void Reset() { memset(&values_, 0, sizeof(values_)); extra_power_ = 0; }

	void Add(AttributeType type, double value);
	void Set(AttributeType type, double value);
	double Get(AttributeType type);
	const double& operator[](int type) const { return values_[type]; }
	double& operator[](int type) { return values_[type]; }
	void GetValues(double* data) const;

	void SetExtraPower(double power){ extra_power_ = power; }
	void AddExtraPower(double power) { extra_power_ += power; }
	double GetExtraPower() const{ return extra_power_; }
//tolua_end

	Attribute& operator= (const Attribute& otherAttrs);
	Attribute& operator+= (const Attribute& otherAttrs);
	Attribute& operator*= (float rate);
private:
	double values_[atCount];	// 属性集定义
	double extra_power_;	//额外战力
};// tolua_export
#endif



