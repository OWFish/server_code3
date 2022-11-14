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
	//怪物死亡的时候
	virtual void OnEntityDeath(EntityHandle killer);
	virtual void OnEnterScene();
	//例行逻辑处理函数
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
	virtual void CalcExAttributes(); // 计算特殊属性
	virtual bool IsBoss();
	int GetMonType();
	virtual double GetAtkSum(void);
	virtual uint64_t GetSummitHandle() { return GetMaster()? GetMaster()->GetSummitHandle(): Inherited::GetSummitHandle(); }
	//virtual bool IsEnemy(Creature *target);

	/**************creature**************/


	const MonsterConfig* GetConfig() { return config_; }
	void SetLiveTIme(unsigned int nTime);
	void addCacheAttr(Attribute::AttributeType type, int value) { basic_attrs_cache_.Add(type, value); }

	// 获取怪物存活直到(秒)，0表示无限
	unsigned int GetLiveTime() { return (unsigned int)live_time_; }

	void ResetBasicAttr(float rate);
protected:
	virtual void OnChangeHp(double nValue, Creature* attacker, double &ret);
	//初始化ai
	void InitAi();

protected:
	const MonsterConfig*	config_; // 配置
	Attribute				basic_attrs_cache_;  // 基础属性缓存
	//MonsterProperty			mon_property_; // todo 基类里没有？
	//static UpdateMask*		broadcastMask_; //那些属性需要发送到客户端 todo 先留着参考下
	int64_t					live_time_;	//存活时间，默认是0，代表无限期
	Timer					t500_timer_;
};


#endif

