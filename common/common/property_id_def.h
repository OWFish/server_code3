#ifndef _PROPERTY_ID_DEF_H_
#define _PROPERTY_ID_DEF_H_

///�������ﶨ�����ʵ������Ե�ID���ű�����Ҫ�õ�,ͨ��ʵ���id���Ի�ȡʵ�������

//tolua_begin

//������Щ�����Ե�ƫ��
enum enPropEntity
{
    P_ID = 0,   // ʵ���id
    P_POS_X , // λ�� posx
    P_POS_Y , // λ��pos y
    P_MODELID, // ʵ���ģ��ID
    P_ICON,  // ͷ��ID
    P_DIR,   // ʵ��ĳ���
    P_MAX_ENTITY,
};

enum enPropCreature
{
    P_LEVEL = P_MAX_ENTITY, // �ȼ�
    P_HP , //Ѫ
    P_MP ,  //��
    P_SPEED, //�ƶ�1����Ҫ��ʱ�䣬��λms
    P_MAXHP, //���Ѫ��Ҳ��������
    P_MAXMP,//�������Ҳ��������
    P_OUT_ATTACK, //�⹦����
    P_OUT_DEFENCE,//�⹦����
    P_DEFCRITICALSTRIKES,//������ֵ
    P_ALL_ATTACK, // ���й�����
    P_SUB_DEF, // ���ӷ���
    P_IN_ATTACK,//�ڹ�����
    P_IN_DEFENCE,//�ڹ�����

    P_CRITICALSTRIKES,	// ����ֵ
    P_DODGERATE, // ����ֵ
    P_HITRATE,	// ����ֵ

    P_ATTACK_ADD,	// �˺�׷��
    P_HP_RENEW,//HP�ָ�
    P_MP_RENEW,//MP�ָ�
    P_ATTACK_SPEED, //�����ٶ�

    P_IN_ATTACK_DAMAGE_ADD, // �����ڹ��˺�����ֵ���
    P_OUT_ATTACK_DAMAGE_ADD,	// �����⹦�˺�����ֵ���

    P_THUNDER_ATTACK,	//�׹�
    P_THUNDER_DEFENCE,	//�׿�
    P_POISON_ATTACK,	//����
    P_POISON_DEFENCE,	//����
    P_ICE_ATTACK,		//����
    P_ICE_DEFENCE,		//����
    P_FIRE_ATTACK,		//��
    P_FIRE_DEFENCE,		//��

	P_STATE, //�����״̬,�����������ȵ�

	P_BASE_MAXHP, //���������Ѫ,�ȼ�������MaxHp,������buff��װ���ȸ��ӵ�
	P_BASE_MAXMP, //�����������,�ȼ�������MaxMp,������buff��װ���ȸ��ӵ�

	P_STAND_POINT,	//������������Ϊ0�Ҳ���ȵĿ��Ի��๥��
	
	P_RESEVS0,		//�����ֶ�
	P_RESEVS1,		//�����ֶ�

    P_MAX_CREATURE,		//
};

//�����
enum enPropMonster
{
    P_MONSTER_START = P_MAX_CREATURE,
    P_BORNPOINT = P_MONSTER_START, // ����ĳ�����(���ã�
    P_LEVEL_DIFF,					// ����
    //// ����������Ϊ�˸������
    P_PET_TITLE,					// ����ĳƺţ���2λ�ǵȽ׳ƺţ���2λ���޽׳ƺţ�������ǳ����Ϊ0
    P_PET_COLOR,
    P_PET_RANK_TITLE,
    P_MAX_MONSTER,
};

enum enPropActor
{
    P_WEAPON = P_MAX_CREATURE,   //�������������
    P_MOUNT,      //������������
    P_DIZZY_RATE11,		 // ��2Ϊ���������ѣ�ļ���,��2λ�Ƿ���ѣ����(ȡ��
    P_DIZZY_TIME1,        // ���������ѣ��ʱ�䣨ȡ����
    P_HP_STORE,        //hp����
    P_MP_STORE,          //�����hp����(��:mp����)
    P_SPIRIT,		         //������ʽ
    P_PK_MOD,   //��ҵ�PKģʽ
    P_STRONG_EFFECT, //ǿ����Ч
    P_WING, // �����Ч
    P_STAGE_EFFECT, //Ʒ����Ч

    P_PET_HP_STORE,     // ����ҩ��
    PROP_ACTOR_XIUWEI_RENEW_RATE, //��ҵ���Ϊ�Ļָ��ٶ�(ȡ����

    P_SEX , //�Ա�
    P_VOCATION , //ְҵ
    P_EXP , //�����1���ֽ�,uint64��
    P_PK_VALUE = P_EXP + 2, //��ҵ�pkֵ(ɱ¾ֵ)�������ã�
    P_BAG_GRID, //�����ĸ�������
    P_WEEK_CHARM,  // ������ֵ
    P_BIND_COIN, //�󶨽�Ǯ
    P_COIN, //�ǰ󶨽�Ǯ
    P_BIND_YB, //��Ԫ��
    P_YB, //�ǰ�Ԫ��
    P_SHENGWANG,  //��ҵ�����
    P_CHARM, //����ֵ���еĽ�˧��ֵ��Ů�Ľ�����ֵ
    P_SPIRIT_SLOT, //���￪ͨ�Ĳ�λ����Ŀ(ò��û�ã�
    P_RENOWN, //����
    P_GUILD_ID , //���ɵ�ID
    P_TEAM_ID, //�����ID
    P_SOCIAL,// ����ϵ��mask����һЩbitλ���õ�
    P_GUILD_EXP, //��ṱ�׶�
    P_LUCKY, //����ֵ
    P_SYS_OPEN, // ����ϵͳ�Ŀ������
    P_ROOT_EXP_POWER,    // ���������ı���
    P_CHANGE_MODEL,		 // ������ģ��(������)
    PROP_BANGBANGTANG_EXP, ////�����Ǿ�����������ٶ�(�⹦��Ӧ��û���ˣ�

    PROP_ACTOR_MAX_EXP,     //��ҵ�����飬64λ��(ò�����ã�
    P_GIVE_YB = PROP_ACTOR_MAX_EXP + 2, //Ԫ�����ж��������͵�Ԫ��
    P_CRITICAL_STRIKE, //�������˺��ٷֱ�
    P_EXP_RATE,     //��Ҿ�����������ٶȣ�Ĭ����1����

    P_DEPOT_GRID,   // �ֿ�򿪸�������
    P_ANGER, // ŭ��ֵ
    P_ROOT_EXP,  // ����ֵ
	P_ACHIEVEPOINT, //��ɵĳɾ͸���(���а�)
    P_ZYCONT,//��Ӫ�Ĺ��׶�(��Ҫֱ���޸ģ����� ����Actor�Ľӿ�ChangeZYCount�����޸�)
    P_QQ_VIP,  // vip��Ϣ����
    P_WING_ID,	// ���id
    P_WING_SCORE,	// �������
    P_PET_SCORE,	// ��������
    PROP_ACTOR_VIPFLAG, // VIP��ͨ��ǣ�ͨ��λ�����Ǹ���VIP���͡�enVIPType������VIP���ͣ��ֱ��Ӧ0-2λ���롣(����û�ã�
    P_CAMP,            //��ҵ���Ӫ 1��ң��2�ǳ���3����
    P_PET_SLOT, //��ҿ����ĳ����λ��������ȡ����
    P_HONOR,				//����ֵ
    P_QING_YUAN,  //��Եֵ
    PROP_ACTOR_DUR_KILLTIMES, //��ն�Ĵ�����ȡ����
    PROP_ACTOR_BASE_FIGHT, //�����õľ��飨ȡ����
    P_FIGHT_VALUE,  //ս����
    P_MAX_RENOWN,   //��ҵ�������������ֵ
    P_RECHARGE,	// ��ҳ�ֵ�ܽ��
    P_VIP_LEVEL,  // ��ҵ�ͷ��,����ͷ��ϵͳ����λ��ʾ����Ƿ������ͷ�Σ�Ĭ��Ϊ0��ȡ��
    P_BEAST_LEVEL,	// ������ڰ��ɵ��������޵ȼ�(ȡ��������ŵ�PROP_FOOT_EFFECT)
    P_FOOT_EFFECT,  // �㼣
    P_EQUIP_SCORE,        //��ҵ�װ�����ܷ�
    P_HAIR_MODEL,  //ʱװñ���
	P_BUBBLE,		// ����
	P_ACTOR_STATE,		//��ҵ�״̬
	P_JINGJIE_TITLE,	//����ƺ�
	P_ZHUMOBI,			//��ħ��

    P_MAX_ACTOR,
};
//tolua_end

#endif


