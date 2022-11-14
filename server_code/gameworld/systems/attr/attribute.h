#ifndef _ATTRIBUTE_H_
#define _ATTRIBUTE_H_

/************************************************************************
*                          ��Ϸ���Լ����¼򻯰棩
************************************************************************/
#include "cstring"

// tolua_begin
class Attribute
{	
public:
	// ���Զ���
	enum AttributeType {
		atHp = 0,	// 0,��ǰhp
		atMp,		// 1,��ǰmp
		atHpMax,	// 2,���Ѫ��
		atMpMax,	// 3,���mp
		atAtk,		// 4,�﹥
		atDef,		// 5,�����
		atRes,		// 6,ħ������
		atCrit,		// 7,������
		atTough,	// 8,���ͣ�������
		atMoveSpeed,	// 9,�ƶ��ٶ�
		atAttackSpeed,	// 10,�����ٶ�

		atHpEx,		// 11,�������� 10000= 100%
		atAtkEx,	// 12,�������� 10000= 100%
		atStunPower,	// 13,�����
		atStunRes,		// 14,��Կ���
		atStunTime,		// 15,���ʱ��
		atDamageReduction, // 16,�˺����� ������ֱ�

		atCritHurt, // 17,�����˺� ֵ
		atRegeneration, // 18,ÿ��ظ�
		atCritEnhance, // 19,�����˺���ǿ
		atPenetrate, // 20,��͸(������ֱ�˫��)

		atRoleDamageEnhance,   // 21,��������˺����� ��ݱ�
		atRoleDamageReduction, // 22,�ܵ�����˺����� ��ֱ�

		atDefEx,		// 23,�������ֱ�
		atResEx,		// 24,ħ��������ֱ�
		atNeiGong, //25,��ǰ�ڹ�
		atNeiGongMax,//26,����ڹ�
		atNeiGongDamageAbsorb,//27,�ڹ������˺� ��ֱ�

		atJob1HpEx,	//28,սʿ��Ч,�����������
		atJob2HpEx,	//29,��ʦ��Ч,�����������
		atJob3HpEx,	//30,��ʿ��Ч,�����������

		atNeiGongRestore, //31,��ʱ�ָ��ڹ�ֵ

		atVamirePro, //32.����װ��,����ʱ��Ѫ�ĸ���(��ݱ�)
		atVamirePen, //33.����װ��,����ʱ��Ѫ���˺�����(��ݱ�)
		atVamireCd,	//34.����װ��,����ʱ��Ѫ��cd(����)

		atCursePro, //35.����װ��,�������(��ݱ�)
		atCurseCd,  //36.����װ��,����cd(����)

		atAttAddDamPro, //37.���������˺��ĸ���(��ݱ�)(����)
		atAttAddDamVal, //38.���������˺���ֵ(����)
		atBeAttAddHpPro,//39.�ܵ�����ʱ��ָ������ĸ���(��ݱ�)(����)
		atBeAttAddHpVal,//40.�ܵ�����ʱ��ָ�������ֵ(����)
		atAttMbAddDamPen,//41.�Ա���Ե�Ŀ��������X%�˺�����(����)
		atHpLtAddBuff,	//42.��������(��ֱ���)ʱ,���������ָ�buff(����)
		atAttHpLtPenAddDam,//43.���������͵�Ŀ�������˺���Ѫ������(��ݱ�)(����)
		atAttHpLtAddDamPen,//44.���������͵�Ŀ�������˺�����(��ݱ�)(����)

		atJob1AtkEx,	//45,սʿ��Ч,�����﹥
		atJob2AtkEx,	//46,��ʦ��Ч,�����﹥
		atJob3AtkEx,	//47,��ʿ��Ч,�����﹥

		atJob1DefEx,	//48,սʿ��Ч,���������
		atJob2DefEx,	//49,��ʦ��Ч,���������
		atJob3DefEx,	//50,��ʿ��Ч,���������

		atJob1ResEx,	//51,սʿ��Ч,����ħ������
		atJob2ResEx,	//52,��ʦ��Ч,����ħ������
		atJob3ResEx,	//53,��ʿ��Ч,����ħ������

		atAttPerDamPan, //54.����ʱ׷�ӵ�ǰ�˺�50%�Ķ����˺��Ļ���(��ݱ�)(����)
		atDamageEnhance,//55.��Ŀ������˺���ݱ�
		atCritEnhanceResist, // 56,�����˺��ֿ���
		atHolyDamege,		//57.��ʥ�˺��̶�ֵ
		atHolyMaster,		//58.��ʥ�˺���ͨ��
		atHolyResist,		//59.��ʥ�˺��ֿ���
		atTogetherHolyDamege,		//60.�ϻ���ʥ�˺��̶�ֵ
		atTogetherHolyMaster,		//61.�ϻ���ʥ�˺���ͨ��
		atTogetherHolyResist,		//62.�ϻ���ʥ�˺��ֿ���
		atZhuiMingPro, //63.����׷���˺��ĸ���(��ݱ�)
		atZhuiMingVal, //64.׷���˺�(�̶�ֵ)
		atHuiXinDamage,// 65,�����˺���(��ݱ�)
		atNeiGongEx, //66.�ڹ�����(��ֱ�)
		atDeadLyPro,		//67.����һ������
		atDeadLyMaster,		//68.����һ���˺���ͨ��
		atDeadLyResist,		//69.����һ���˺��ֿ���
		atAddEnemyHp,		//70.�Լ��������Է���Ѫ(�̶�ֵ)
		atHurtMyself,		//71.�����Է����Լ���Ѫ(��ݱ�)
		atBladeMailPro,  //72.�м׸���(��ݱ�)
		atBladeMailPer,  //73.�м׷���(��ݱ�)
		atDefPen,		 //74.�����͸(��ݱ�)
		atResPen,		 //75.ħ����͸(��ݱ�)
		atDeadLyHurt,    //76.����һ�������˺�(�̶�ֵ)
		atDeadLyHurtResist,    //77.����һ�������˺�����(�̶�ֵ)
		atCritHurtResist, //78.���������˺�����(�̶�ֵ)
		atHunGuPro, //79.���6���׹�����������
		atHunGuHurt, //80.���6���׹��������˺���ֱ�
		atHunGuCd, //81.���6���׹���cd
		atHearthDamege,//82.�ķ�3�����˺�(�̶�ֵ)
		atHearthHurt,//83.�ķ�3�����˺���(��ݱ�)
		atHearthCount,//84.�ķ�3ÿN�δ���82and83

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
	double values_[atCount];	// ���Լ�����
	double extra_power_;	//����ս��
};// tolua_export
#endif



