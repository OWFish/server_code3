#pragma once


//ʵ������Ա�־λ
struct EntityFlags
{
	union
	{
		int nValue;
		struct
		{
			bool DenyMove:1;        //�����ƶ�(ʵ��)
			bool DenyBeMove:1;      //���ܱ��ƶ�����������(ʵ��)
			bool DenyAttackActor:1;  //���������(ʵ��)
			bool DenyBeAttack:1;       //���ܱ�����(ʵ��)
			bool DenyAttackedByActor:1;  //���ܱ���ҹ���(ʵ��)
			bool CanAttackMonster:1;    //�ܹ���������(ʵ��)
			bool DenyBeTaunt:1;      //���ܱ�����(ʵ��)
			bool DenyAutoAddHp:1;    //�����Զ����HP(ʵ��)
			bool DenyAutoAddMp:1;     //�����Զ����MP(ʵ��)
			bool CanSceneTelport:1;    //�ܷ�糡������(ʵ��)
			bool CanSeeHideActor:1;     //�ܷ񿴵���������(ʵ��)
			bool DenyDieSubExp:1;       //�����о���˥��(ʵ��)
			bool TelByOwnerEntity:1;	// ���͵�ʱ����Ź����ߴ���
			bool MonsterLazyFollow:1;	// ����������ԡ����Ը������Զ�˻��Զ������������ߣ��Ƕ��Ը�����������룬������ϻᴫ�͡�������ʵ�֣�
			bool DenyUseNearAttack:1;     //��ʹ���ⲫ��ȡ����
			bool DenyDizzyBuff:1;          //���������ѣ��buff
			bool DenyMoveForbidBuff:1;      //������Ӷ����Buff
			bool DenyInnnerSkillForbidBuff:1; //������ӷ��buff
			bool DenyOutSkillForbidBuff:1;    //������Ӷϵ�buff
			bool DenyMoveSpeedSlowBuff:1;     //��ֹ�ƶ��ٶȽ��͵�buff
			bool DenySee:1;                   //���ܱ�����
			bool DenyInitiativeAttackActor:1;	// ������������ң���������֣�
			bool ActorModel:1;		// �Ƿ�����������
			bool DenyHpPower:1;		// �Ƿ��ֹѪ�������ӵ�buff������
			bool OnlyAttkackByPet:1; //�Ƿ�ֻ�ܱ����﹥��(ʵ��)
			bool DenyTurnDir:1;		// �Ƿ��ֹת��
			bool DenyUseSkill:1;		// �Ƿ��ֹʹ���κμ���
		};
	};
	EntityFlags()
	{
		nValue = 0;
	}
};
