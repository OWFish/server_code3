#ifndef _BUFF_TYPE_H_
#define _BUFF_TYPE_H_
/************************************************************************
* ���ļ�������Ϸ��ʹ�õ�buff���ͣ������Ĭ������ȡ�
* �ļ���ͬʱ�ᶨ����Щbuff����������Լӳɵȣ���Ȼ����������صĿ��Կ��Ǹĵ������ļ��
* ע�⣺��֮ǰ����Ŀ�У�buff���ͺ����������Ǻϲ���һ��ģ����ڰ����Ƕ���ֿ���
* ����<> �������Զ����ɴ��롣����������Ƕ�Ӧ���������ͣ���attr_type.h����),��ʾbuff
* �������Ӧ������������û��<> ��ʾbuff����ı�����
* ����ע��buff���ͱ����������ģ���ʹ����ҲҪ�и����ռλ��Ҳ��ע�͵���
************************************************************************/

//tolua_begin

enum BuffType
{
	bUndefined = 0,				//δ����
	bSilence = 1,				// ��Ĭ
	bMoveForbid = 2,	 //���� ��ֹ�ƶ�,�����ƶ�������ʩ�ż���
	bDizzy = 3,		  // ��ѣ,�����ƶ�������ʩ����ͨ���ܣ�ѣ��״̬�²������⼼�ܿ�ʹ��
	bControlSkillImmune = 4, // ���߸��ֿ��Ƽ���
	bInnnerSkillForbid = 5, // �⣬��ֹʹ���ڹ�����
	bOutSkillForbid = 6,  // �ϣ���ֹʹ���⹥����
	bInnerAttackImmune = 7, // �����ڹ����� �����������Է������ܣ��⡢�������٣�
	bOutAttackImmune = 8, // �����⹥���������������������ܣ��ϡ��������٣�
	bHide = 9,							   // ����
	bReliveProtectState = 10,				   // �����״̬

	bHpAdd = 11,					//Ѫ����<aUndefined,adInt>
	bHpPower = 12,					//Ѫ��������<aUndefined,adFloat>
	bMpAdd = 13 ,					//������<aUndefined,adInt>
	bMpPower = 14,					//����������<aUndefined,adFloat>
	bMoveSpeedAdd = 15 ,			//�ƶ��ٶ�����<aMoveSpeedAdd,adInt>
	bMoveSpeedPower = 16,			//�ƶ��ٶȱ�������<aMoveSpeedPower,adFloat>
	bMaxHpAdd = 17,					//���Ѫ����<aMaxHpAdd,adInt>
	bMaxHpPower = 18,				//���Ѫ��������<aMaxHpPower,adFloat>
	bMaxMpAdd = 19,					//���������<aMaxMpAdd,adInt>
	bMaxMpPower = 20,				//�������������<aMaxMpPower,adFloat>
	bOutAttackAdd = 21,				//����������<aOutAttackAdd,adInt>
	bOutAttackPower = 22,			//��������������<aOutAttackPower,adFloat>
	bOutDefenceAdd = 23,			//�����������<aOutDefenceAdd,adInt>
	bOutDefencePower = 24,			//���������������<aOutDefencePower,adFloat>
	bAddDefStrike = 25,				//������ֵ����<aAddDefStrike,adInt>
	bAddDefStrikePower = 26,		//��������������<aAddDefStrikePower,adFloat>
	bAllAttackAdd = 27,				// ���й���������<aAllAttackAdd,adInt>
	bAllAttackPower = 28,			//���й�������������<aAllAttackPower,adFloat>
	bSubDef = 29,					//���ӷ���<aSubDef,adInt>
	bSubDefPower = 30,				//���ӷ�������<aSubDefPower,adFloat>
	bInnerAttackAdd = 31,			//������������<aInnerAttackAdd,adInt>
	bInnerAttackPower = 32,			//����������������<aInnerAttackPower,adFloat>
	bInnerDefenceAdd = 33,			//������������<aInnerDefenceAdd,adInt>
	bInnerDefencePower = 34,			//����������������<aInnerDefencePower,adFloat>
	bCriticalStrikesValueAdd = 35,	//����ֵ������<aCriticalStrikesValueAdd,adInt>
	bCriticalStrikesValuePower = 36,	//����ֵ��������<aCriticalStrikesValuePower,adFloat>
	bDodgeValueAdd = 37 ,				//����ֵ����<aDodgeValueAdd,adInt>
	bDodgeValuePower = 38,			//����ֵ��������<aDodgeValuePower,adFloat>
	bHitValueAdd = 39,				//����ֵ����<aHitValueAdd,adInt>
	bHitValuePower = 40,				//����ֵ��������<aHitValuePower,adFloat>
	bAttackAppend = 41,				// �˺�׷��<aAttackAppend,adInt>
	bAttackAppendPower = 42,		// �˺�׷�ӱ�������/����<aAttackAppendPower,adFloat>
	bHpRenewAdd = 43,					//HP�ָ�����<aHpRenewAdd,adInt>
	bHpRenewPower = 44,					//HP�ָ���������<aHpRenewPower,adFloat>
	bMpRenewAdd = 45,					//MP�ָ�����<aMpRenewAdd,adInt>
	bMpRenewPower = 46,					//MP�ָ���������<aMpRenewPower,adFloat>
	bAttackSpeedAdd = 47,				//���ӹ����ٶ�<aAttackSpeedAdd,adInt>
	bAttackSpeedPower = 48,			  //�����ٶ����ӱ���<aAttackSpeedPower,adFloat>
	bInAttackDamageValueAdd = 49,		  //���ܷ����˺�����ֵ���<aInAttackDamageValueAdd,adInt>
	bInAttackDamageValueAddPower = 50,	 //���ܷ����˺��ı������<aInAttackDamageValueAddPower,adFloat>
	bOutAttackDamageValueAdd = 51,		  //���������˺�����ֵ���<aOutAttackDamageValueAdd,adInt>
	bOutAttackDamageValueAddPower = 52,	 //���������˺��ı������<aOutAttackDamageValueAddPower,adFloat>

	bDamageAbsorb = 53,  //�˺�����,�Լ������ʩ�Ż��ܣ�����N���˺�
	bDamageAbsorbRate = 54, //�����������˺�,����һ���ٷֱȵ������˺�
	bDamage2Mp = 55, // �˺�ת��Ϊ��������,����N���˺���ÿ����һ���˺���Ҫ���m������ֵ����������ʱ������ʧ

	bDamageDeepen = 56, //�˺�����<aUndefined,adFloat>
	bRiseUp = 57,		//�����ڿ�buff (���ᱻ�������ᱻѣ��)
	bXuanFengZhan = 58, //����ն���buff (���ᱻ�������ᱻѣ��)
	bBaoyi = 59,		//����buff
	bBlackScreen = 60,	//ɳ����(����)
	bSoap = 61,			//����(����)
	bMagnet = 62,		//����(����)
	bCriticalStrikeDamageRateAdd = 63, //�������˺����ʵ���ߣ�Ĭ�ϵ���1.5���ģ���������<aCriticalStrikeDamageRateAdd,adFloat>
	bDizzyRate = 64,			 // ���������ѣ�ļ���<aDizzyRate,adInt>
	bExpAdd = 65,								  //��������һ����ֵ
	bDizzyDef = 66,							   // ѣ�����߸���<aDizzyDef,adInt>
	bMeiHuo = 67,							  //�Ȼ�(����)
	bSuperMan = 68,							  //�޵�,�ܹ��������ܱ�����
	bHitFinalAddPower = 69,					  //�����������Ӱٷֱ�
	bAllAttackDamageRateAdd = 70,			//��������,�����˺��ı������<aAllAttackDamageRateAdd,adFloat>
	bDamageRate = 71,					 // �����˺�׷�Ӱٷֱȣ�Ϊ10000�ı���������2000��ʾ0.2,����<aDamageRate,adInt>
	bUseSkill = 72,						  //ʹ��һ��buff��Ч���Ƕ�ʱʹ�ü���
	bHitFinalAddRate = 73,				 //�������б�������<aHitFinalAddRate,adInt>
	bHitFinalMin = 74,					 //�������ܱ���(���ܳ������ֵ)<aHitFinalMin,adInt>
	bExpPower = 75,						   // ��������ӵı���<aExpPower,adFloat>
	bUnableDoubleSunbath = 76,						  //�޷���ԡ��DEBUFF
	bReboundAttack = 77,						 // �������⹦���˺��ٷֱ�, ����<aReboundAttack,adFloat>
	bPetAddHp = 78,								// �����Ѫ
	bRefFeatureForbid = 79,					// ��ֹˢ�����
	bSuperExpTime = 80,						//�౶����һ�BUFF
	bInnerAttackDamageRateAdd = 81,		  //���ܷ����˺��ı������<aInnerAttackDamageRateAdd,adFloat>
	bOutAttackDamageRateAdd = 82,		   //���������˺��ı������<aOutAttackDamageRateAdd,adFloat>
	bInnerAttackDamageRebound = 83,		  //���ܷ��������˺����ж��ٱ����������Է�<aInnerAttackDamageRebound,adFloat>
	bOutAttackDamageRebound = 84,			//�����������˺����ж��ٱ����������Է�<aOutAttackDamageRebound,adFloat>
	bDodgeFinalAddRate = 85,			  //�������ܱ�������<aDodgeFinalAddRate,adInt>
	bGuildAnimal = 86,				 //��������buff<aDodgeFinalAddRate,adInt>������Ҫ�ˣ�
	bSilenceDef = 87,				// ��Ĭ���ߵĸ���<aSilenceDef,adInt>
	bSelfCSDamageDec = 88,				//�ܵ������˺�����n% (�԰ٷֱȵ���ʽ�������û��ܵ��ı����˺�)<aSelfCSDamageDec,adFloat>
	bRenownAdd = 89,					//�������� n (����)
	bDamage2Hp = 90,				   // ��Ѫ�İٷֱȣ��Ѹ��Է����˺���һ����ת��Ϊ�Լ���Ѫ��<aDamage2Hp,adFloat>
	bRenowRateAdd = 91,				//�����Ļ�ȡ�ٶȼӳ�(������),+n%<aRenowRateAdd,adFloat>
	bBananaSkin = 92,				//�㽶Ƥ(����)
	bNotUseMount	= 93,				// ��ֹ������
	bNotTeleport	= 94,			// ��ֹ�ٴ�
	bDiChi = 95,					// �ش�(����)
	bAllDefenceAdd = 96,		// ���з�������<aAllDefenceAdd,adInt>
	bAllDefenceRateAdd = 97,	// ���з�����������<aAllDefenceRateAdd,adFloat>
	bThreat = 98,				// ����buff(�����޷�����)
	bWuDi = 99,					//�޵�(����)
	bAbsorbHpByAttack = 100,	//���ݹ�������Ѫ
	// �������
	//bFTYVal = 101,				// ����ӡ��Ŀ����ɶ���A���˺� (ȡ������Щ���Զ���ͨ������ϵͳ������������buffϵͳ���������ﶨ�岻��Ҫ��

	bStrikeState = 102,			// 100%����״̬
	bTotalExpRate = 103,		// �ܾ��鱶�����ӣ�С��,��ʱֻ���־���<aUndefined,adFloat>

	bImprison = 104,			// ����Ч��(���ɹ����Ͳ����ƶ�,����״̬���ɱ��Ƴ�)

	bActorExtraDamage = 105,		// �������ɵ��˺���ɶ�����˺���С��
	bAbsorbRate = 106, // ��Ѫ�İٷֱ�,�����Ⱥ������ֻ����һ����ҵ�Ѫ(��ʱֻ���ؼ�����)
	//bActorExpress = 107,   //���ڸı����һЩ���ԣ��ض�group��ʾ�ı���ɫ(ȡ����
	//bSkillDamageRate = 108, //�����ļ��ܵ�buff������ʹ�ü�������˺�,  ��Ԫն(ȡ����
	bAbsorbHp = 109, // ��Ŀ������˺������ظ���Ӧ��Ѫ������� ,С��<aUndefined,adFloat>
	//bSkillDamageRate1 = 110, //��������buff��̤��(ȡ����
	bTeamExp = 111, // ��Ӿ���buff,С��<aUndefined, adFloat>
	bSceneExpRate = 112, // ���ⳡ������ӳ�,С��
	bFlower = 113, // �ʻ�BUFF
	//����ɳ̲���
	bSunshade = 114, // ̫��ɡbuff
	bRepulseStop = 115,	//���� ������buff

	bAddHpByDamage = 116, //���������ʻָ�<aAddHpByDamage,adFloat>

	/* ������µ���������ö�ٳ�Ա����GameAttributeCountǰ��ӣ��� */
	GameBuffCount,	//��ö�ٳ�Ա��ֵ�����Զ�ȡֵΪ�Ѷ������Ե�����
	/* ������µ���������ö�ٳ�Ա����GameAttributeCountǰ��ӣ��� */
} ;

//tolua_end

extern GAMEATTRTYPE Buff2Attr[GameBuffCount];
extern eAttribueTypeDataType BuffDataType[GameBuffCount];

#endif

