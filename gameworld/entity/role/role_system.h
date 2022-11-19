#ifndef _ROLE_SYSTEM_H_
#define _ROLE_SYSTEM_H_

#include "StdAfx.h"
#include "role.h"


struct RoleDatas;
class RoleSystem
{
public:
	RoleSystem(Actor* actor);

	~RoleSystem();

	void Init(DataPacketReader& reader);
	void Save(ActorBasicData* pData);

	void Destroy();
	void OnEnterGame();
	void OnLevelUp();
	void OnEnterScene();
	void OnExitScene();
	void OnRelive();
	void On1sTick(int64_t curr_t);
	void Recover();
	Role* GetRoleByJob(int job);
	Role* GetRoleById(int id);
	RoleData* GetRoleData(int roleid);
	int GetRoleCount() { return data_->role_count; }

	void CreateRole(int job, int sex);
	bool WriteRolesData(DataPacket &pack);
	bool CreateCloneData(DataPacket &pack, int attrper = 0);
	bool IsAllDie();
	void UpdateTotalPower();
	void OnPowerChangeEvent();
	void GetRoles(Role **list);
	void ReCalcAttr();
	void ReCalcExAttr();
	void ReCalcBattleAttr();
	void InstantMove(int x = 0, int y = 0);
	// 获取Actor或者role中没dead并且战力最高的，都dead的话返回NULL
	Role* GetLiveByPower();
	Role* GetRandomLiveRole();
	Role* GetLiveByJob();
	int GetDeathCount();  //获取死亡角色数量，目前用于白虎伤害计算
	void WriteRoleBattleInfo(DataPacket& pack);
private:
	void UpdateInfo();
	void UpdateRank();

private:
	Actor *actor_;
	RoleDatas *data_;
	EntityHandle role_hdl_[MAX_ROLE];
	Role*	roles_[MAX_ROLE];
	bool isload_;
};

#endif