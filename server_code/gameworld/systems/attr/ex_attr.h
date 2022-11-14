#pragma once


/***************************************************************
*					�������Լ�(�����ؼ��༼��)
***************************************************************/
// tolua_begin
class ExAttribute {
public:
	enum ExAttributeType {
		eatReflectProbability = 0,	// 0,���˸���
		eatReflectRate, // 1,���˱���
		eatIgnoreReflect, // 2,���ӷ���
		eatGodBlessProbability, // 3,���Ӵ��� ����
		eatGodBlessRate, // 4,���Ӹ�����ֱ�
		eatDeathCurseProbability, // 5,���䴥������
		eatDeathCurseDamageIncrease, //6,���������˺���ݱ�
		eatDeathCurseTime,		//7.����Ч��չʾʱ��
		eatAllCrit,		// 8.�����ᴥ�������ĸ��ʣ�0-10000
		eatAllCritTime,	// 9.AllCrit���������󣬳�����ʱ��, ��λ:��
		eatBeHitTimesDodge,//10.�ܵ�X�ι���ʱ�ض�����
		eatAttackTimesCrit,//11.����X�αض�����������������
		eatAttackAddHpProbability,//12.���ƽ�ָ,����ʱ��Ѫ�ĸ���
		eatAttackAddHpValue,//13.���ƽ�ָ,������ʱ��Ѫ��
		eatAddToWarriorDamageInc,//14.���Ӷ�սʿ���˺���ݱ�
		eatAddToMageDamageInc,//15.���ӶԷ�ʦ���˺���ݱ�
		eatAddToTaoistDamageInc,//16.���ӶԵ�ʿ���˺���ݱ�
		eatSubWarriorDamageInc,//17.�����ܵ�սʿ���˺���ݱ�
		eatSubMageDamageInc,//18.�����ܵ���ʦ���˺���ݱ�
		eatSubTaoistDamageInc,//19.�����ܵ���ʿ���˺���ݱ�
		eatTogetherHitFree,//20.���ٺϻ��ܵ����˺���ݱ�
		eatTogetherHitMonDamageInc,//21.�ϻ�װ���ںϻ����ܵ�ʱ��Թ�����˺���ݱ�
		eatTogetherHitRoleDamageInc,//22.�ϻ�װ���ںϻ����ܵ�ʱ�����ҵ��˺���ֱ�
		eatTogetherHitCdSub,//23.�ϻ�װ������Ч�����ٺϻ�����CDʱ��(��ݱ�)
		eatAdditionalHarm,//24�˺����ӹ̶�ֵ
		eatReductionHarm,//25�˺�����̶�ֵ
		eatMiss,//26���ܸ�����ֱ�
		eatBaseSkillExArg,// 27�������ܶ���ϵ���ӳɰٷֱ�
		eatMultipleCrit,//28���ر���������ֱ�
		eatMultipleCritCoeff,// 29����һ�����˺��������(��ֱ�)
		atMultipleCritHurt,//30����һ�����˺�����̶�ֵ
		eatAddWarriorDamageInc,//31.����սʿ���˺���ݱ�
		eatAddMageDamageInc,//32.���ӷ�ʦ���˺���ݱ�
		eatAddTaoistDamageInc,//33.���ӵ�ʿ���˺���ݱ�
		eatMultipleCritTime, //34.����һ������ȴʱ��
		eatAttackAddHpTime, //35.���ƽ�ָ,������ʱ��Ѫ����ȴʱ��
		eatStunTime,	//36.�����ȴʱ��
		eatGodPowerCd,//37.��֮������CD(��ȴʱ��)
		eatGodPowerProbability, // 38,��֮����������
		eatGodPowerDamageIncrease, //39,��֮�������˺���ݱ�
		eatHpLtAddBuffId, //40.��������(��ֱ���)ʱ,���������ָ�buffID(����)
		eatHpLtAddBuffCd, //41.��������(��ֱ���)ʱ,���������ָ�buff CD
		eatHit, //42.��������ֱ�
		eatSkillVamirePro, //43.��Ѫ��ֱȣ�����ض�����
		eatWarriorPeakDamageInc,//44.սʿ����۷��˺���ݱ�
		eatMagePeakDamageInc,//45.��ʦ����۷��˺���ݱ�
		eatTaoistPeakDamageInc,//46.��ʿ����۷��˺���ݱ�
		eatPetSkillLevel,//47.����ר�ü��ܵȼ�
		eatPetAttackInc,//48.��ʿ���﹥�����ӳ���ֱ�
		eatSkillAddArgA, //49.�Լ��ܵ�A����������ֵ-�������ܵ��˺�ֵ��������
		eatSkillAddArgB, //50.�Լ��ܵ�B����������ֵ-�������ܵĹ̶��˺�ֵ����
		eatResistDeathCd,//51.����ʱ��ֵ�һ�������˺�CD
		eatResistDeathPro,//52.����ʱ��ֵ�һ�������˺��ĸ�����ݱ�
		eatResistDeathRate,//53.����ʱ��ֵ�һ�������˺���Ѫ����ݱ�
		eatCritHpLt, //54.��������ʱ��������(��ֱ���)�����˺�����(������)
		eatCritHpLtAddDamage, //55.��������ʱ��������(��ֱ���)�����˺�������(������)

		eatMiJiKNHpPer,//56.��ŭ�ؼ����ڶ���Ѫ���ٷֱ���Ч
		eatMiJiKNHpSubPer,//57.��ŭ�ؼ�ÿ���Ͱٷֶ���
		eatMiJiKNDamPer,//58.��ŭ�ؼ����Ӷ��ٰٷֱ�
		//INT((m - ����Ѫ���ٷֱ�) / x)*y > 0

		eatMiJiZHDamPer,//59.׷���ؼ��˺��ٷֱ�
		eatMiJiZHTime,//60.׷���ؼ���ȴʱ��

		eatMiJiBQHpTime,//61.�����ؼ���ȴʱ��
		eatMiJiBQHpPer,//62.�����ؼ����ڶ���Ѫ���ٷֱ���Ч
		eatMiJiBQBuffId,//63.�����ؼ�buffID

		eatAddSkillDamageInc,//64.�����˺��ӳ�
		eatSubSkillDamageInc,//65.�����˺�����
		eatCount,
	};
public:
	ExAttribute();
	ExAttribute(const ExAttribute& attrs);
	void Reset() { memset(&values_, 0, sizeof(values_)); }
	void Add(int type, int value);
	void Set(int type, int value);
	int Get(int type);
	int& operator[](int type) { return values_[type]; }
	void GetValues(int* data) const;
	//tolua_end
	ExAttribute& operator= (const ExAttribute& otherAttrs);
	ExAttribute& operator+= (const ExAttribute& otherAttrs);
	ExAttribute& operator*= (float rate);
private:
	int values_[eatCount];	// ���Լ�
};// tolua_export
