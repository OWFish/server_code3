#ifndef _MONSTER_H_
#define _MONSTER_H_


#include "creature.h"
#include "timer.h"



struct MonsterConfig;
class Monster:
	public Creature	//todo ???
{
	friend class PropertySystem;
	friend class Scene;
public:

	//static const int MAX_DROP = 8;
public:
	typedef Creature Inherited;

	Monster();
	virtual ~Monster();
	virtual void OnDestroy();


	bool Init(int id);


	/**************entity****************/
	//����������ʱ��
	virtual void OnEntityDeath(EntityHandle killer);
	virtual void OnEnterScene();
	//�����߼�������
	virtual void LogicRun(int64_t curr_t);
	virtual void OnKilledByEntity(Entity* killer);
	virtual int GetId();
	virtual bool IsMonster() { return true; }
	virtual Actor* GetActor();
	/**************entity****************/


	/**************creature**************/
	virtual void InitBasicAttribute();
	virtual void CreateAppearData(DataPacket& appearPack);
	virtual void CalcAttributes();
	virtual void CalcBattleAttributes();
	virtual void CalcExAttributes(); // ������������
	virtual bool IsBoss();
	int GetMonType();
	virtual double GetAtkSum(void);
	virtual uint64_t GetSummitHandle() { return GetMaster()? GetMaster()->GetSummitHandle(): Inherited::GetSummitHandle(); }
	//virtual bool IsEnemy(Creature *target);

	/**************creature**************/


	const MonsterConfig* GetConfig() { return config_; }
	void SetLiveTIme(unsigned int nTime);
	void addCacheAttr(Attribute::AttributeType type, int value) { basic_attrs_cache_.Add(type, value); }

	// ��ȡ������ֱ��(��)��0��ʾ����
	unsigned int GetLiveTime() { return (unsigned int)live_time_; }

	void ResetBasicAttr(float rate);
protected:
	virtual void OnChangeHp(double nValue, Creature* attacker, double &ret);
	//��ʼ��ai
	void InitAi();

protected:
	const MonsterConfig*	config_; // ����
	Attribute				basic_attrs_cache_;  // �������Ի���
	//MonsterProperty			mon_property_; // todo ������û�У�
	//static UpdateMask*		broadcastMask_; //��Щ������Ҫ���͵��ͻ��� todo �����Ųο���
	int64_t					live_time_;	//���ʱ�䣬Ĭ����0������������
	Timer					t500_timer_;
};


#endif

