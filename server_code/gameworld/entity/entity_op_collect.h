#ifndef _ENTITY_OP_COLLECT_H_
#define _ENTITY_OP_COLLECT_H_

/************************************************************************
* 
*                            ʵ�������������ռ�ϵͳ
*
*    ʵ�����������ܴ��������Ż��������ܣ�����һ���߼�ѭ������Ҫ��δ������ͬ���鼯��
* �������߼�������������ǰִ�С�
* ���磺
*  1) ˢ�����ԣ���һ�������߼��п�����Ҫ���ˢ�����ԣ���ʹ�ü��б�������ֻ����Ҫˢ����
*     �Եı�־��Ϊ�棬�������к�����������ǰ�жϱ�ǲ�ˢ�����ԣ�
*
*  2) ˢ����ۣ���һ�������߼��п�����Ҫ���ˢ����ۣ���۰����·�����Ʒ���������ơ�����
*     ��ɫ���Ƿ���ӵȱ�־
*
************************************************************************/

class EntityOPCollector
{
	friend class Creature;
public:
	enum CollecteOPType
	{
		coRefAbility = 0,	//���¼�������
		coRefFeature,		//���¼������
		coTransport,       //���ͱ�ǣ������Ժ�Ҫ���³����ص��Աߵ���ҷ�һ����Ϣ
		coResetMaxHPMP,		// �������Ѫ���ͷ���ֵ������������ĸ���
		coRefMonsterDynProp,	// ˢ�¹��ﶯ̬����
		coDenaturation,		//����
		coEndHide,		// ����
		coActordataerr,	// ��db��ȡ���ߵ����ݳ���
		coSpeed,		// �ٶȸı�
		coCheckProp,	// �·����Ա仯
		//����������
		MaxCollectedOp
	};

	STATIC_ASSERT(MaxCollectedOp < 32);
public:
	EntityOPCollector()
	{
		Reset();
	}

	//������ܱ������
	inline void Reset()
	{
		operations_ = 0;
	}

	//���û��ܱ������
	inline void Collect(const CollecteOPType eOPType)
	{
		if (eOPType >= 0 && eOPType < MaxCollectedOp)
			operations_ |= (1 << (eOPType & 31));
	}

	inline bool IsCollected() { return operations_ != 0; }

	//�ж�ĳ����������Ƿ�����
	inline bool IsCollected(const CollecteOPType eOPType)
	{
		if (eOPType >= 0 && eOPType < MaxCollectedOp)
			return (operations_ & (1 << (eOPType & 31))) != 0;
		else return false;
	}
protected:
	int	operations_;
};


#endif

