#ifndef _AI_CONDITION_H_
#define _AI_CONDITION_H_

enum AIConditionType
{
	acNull = 0,			// �����������ʧ�ܵ�����

	acTime,				// ����ý׶�ʱ��
	acSelfHp,			// �Լ���Ѫ��
	acTargetHp,			// ��ǰĿ��Ѫ��
	acTargetDistance,	// ��Ŀ�����
	acSelfBuff,			// �Լ��Ƿ���ָ��buff
	acTargetBuff,		// Ŀ���Ƿ���ָ��buff
	acHasBattlePet,		// �Ƿ���ս������
	acRoleMinHp,		// �Լ���ɫ����Ѫ�� (role�޶�ai)
	acHatredListDistanceCount,   // ����б��еĵ��˾��������
	acHatreListMonDisCount,//����б��еĹ�����������
	acMonsterCount,		 // ������Χ������
	acTargetMonCount,   //Ŀ����Χ������
	//acMonsterDistance,	// ��ָ���ֵľ��룬 �ҵ��ĵ�һ��Ϊ׼
	//acPostionDistance,	// ��ָ��λ�õľ���
	//acPlayerCount,		// ��Χ��������

	acConditionCount,
};

class Creature;
class AIState;
struct AIConditionConfig;

namespace AICondition {
	bool Check(const AIConditionConfig *config, Creature *self, AIState *ai_state);
}; // end of namespace


#endif