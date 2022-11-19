#pragma once
#include "StdAfx.h"

class ActorExRingSystem
{
public:
	typedef std::map<int, Monster*> BattleExRingMap;
	ActorExRingSystem(Actor* actor);
	~ActorExRingSystem();
	bool Init();
	void OnExitScene();
	void OnEnterScene();
	void OnAllRoleDie();
	void OnRelive();
	void ReCreateAllRing();
	ExAttribute* GetExAttr() { return &ex_attribute_; }
	Monster* CreateExRingMonster(int rid, int id);//创建怪物
	void CreateCloneExRingMonster(unsigned int scene, int x, int y, RoleClone* clone); //克隆玩家创建怪物
	inline void ClearExRingMonster(int rid)	{
		BattleExRingMap::iterator it = battle_ring_.find(rid);
		if (it == battle_ring_.end()) return;
		battle_ring_.erase(it);
	}
	inline int FindActorExRingMonsterRid(Monster *mon) {
		for (BattleExRingMap::iterator it = battle_ring_.begin(); it != battle_ring_.end(); ++it) {
			if (it->second == mon) {
				return it->first;
			}
		}
		return -1;
	}
	inline Monster* GetExRingMonster(int rid)
	{
		if (rid < 0 || rid >= ActorExRingType_MAX) return NULL;
		BattleExRingMap::iterator it = battle_ring_.find(rid);
		if (it == battle_ring_.end()) return NULL;
		return it->second;
	}

	Attribute* GetMonsterAttr(int rid);
	ExAttribute* GetMonsterExAttr(int rid);
	void DestroyBattleRing(int rid);
	void stopAllExringAi();
	void SetCamp(int camp);
	void setCanChangeCamp(bool canChg);
private:
	void DestroyBattleRingAll();

	Actor *actor_;
	ExAttribute ex_attribute_;
	std::map<int,Attribute> monster_attr;
	std::map<int, ExAttribute> monster_ex_attr;
	BattleExRingMap battle_ring_;//可以战斗的特戒
};

