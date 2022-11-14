#pragma once

#define  MAXFBPARAM	32
#define	MAXBOSSCOUNT 6

#include "fuben_config.h"

class FuBenMgr;
class Scene;
struct SceneConfig;
typedef memory::Handle  FuBenHandle;
class FuBen
{
public:
	static const int MAX_SCENE = 128;
	typedef StaticArrayList<Scene*, MAX_SCENE> SceneList;	// 64个不够用了,128个应该足够了
	friend class FuBenMgr;

public:
	FuBen();
	virtual ~FuBen();
public:
	bool Init(int id);

	inline void SetFbId(int id) { fb_id_ = id; }
	inline int GetFbId() { return fb_id_; }

	inline int GetFbType() { return conf_->type; }

	inline void SetFbUId(FuBenUId uid) { fb_uid_ = uid; }
	inline FuBenUId GetFbUId() { return fb_uid_; }

	inline bool IsFb() { return fb_id_ != 0; }
	inline bool IsNeedAi() { return run_ai_; }
	inline void SetIsNeedAi(bool isNeed) { run_ai_ = isNeed; }
	inline void SetEnd() { is_end_ = true; }
	inline void SetBelong() { belong_ = true; }
	inline bool IsEnd() { return is_end_; }
	inline bool IsBelong() { return belong_; }

	void SetHandle(const FuBenHandle& hHandle) { handle_ = hHandle; }
	FuBenHandle GetHandle() { return handle_; }
	SceneList& GetSceneList() { return scene_list_; }
	inline void AddScene(Scene* pScene) { scene_list_.add(pScene); }

	inline void SetConfig(FubenConfig* pConfig) { conf_ = pConfig; }

	bool Enter(Entity* et, int scene_index = 1, int x = 0, int y = 0, bool pix = false);

	//本函数只应该在程序启动时读取配置数据的时候执行
	//bool AddStaticScene(SceneConfig* scene_conf);

	inline const FubenConfig* GetConfig() { return conf_; }
	Scene* GetScene(int sid);
	Scene* GetSceneByIndex(int index);

	void ExitAllActor();
	bool HasScene(int sid);

	void SendData(const char* buf, size_t size);
	void SendDataNoActor(const char* buf, size_t size, Actor* except);
	template<class ProtoType>
	void SendData(ProtoType proto) { SendData(&proto, sizeof(proto)); }
	/*-------------------------------------*/
	void OnEnter(Actor *et, bool isLogin);
	void OnExit(Actor *et);
	void OnOffline(Actor *et);
	void OnActorLeapArea(Actor *actor);

	void OnEntityDie(Entity *et, EntityHandle killer);
	void OnMonsterDamage(Monster *mon, int nValue, Entity* attacker, double &ret);
	void OnRoleDamage(Role *role, int nValue, Entity* attacker, double &ret);
	//void OnMonsterBorn(Monster *mon); // 这个是放在ai里调用的，但是单人副本不执行ai，所以改成进入场景调用
	void OnMonsterEnter(Monster *mon);

	/*-------------------------------------*/

	void KillAllMonster();

	std::vector<Actor*> GetAllActor();
	std::vector<Monster*> GetAllMonster();
	std::vector<DropBag*> GetAllDropBag();
	void GetAllCloneRole(std::vector<RoleClone*> &ret);
	RoleClone* GetCloneRoleByID(int ID);

	int getActorCount();
	void SetReleased() {is_released_ = true; }
	bool IsReleased() { return is_released_; }

	inline bool NeedShowZhanLing() { return conf_->showZhanLing == 1; }
	//获取剩余怪物数量
	int GetResCloneRoleCount();

private:
	int RunOne();


private:
	int						fb_id_;		//副本的id
	FuBenUId				fb_uid_;	//副本uid
	FuBenHandle				handle_;	//副本的handle
	const FubenConfig*			conf_;		//这个副本的配置内容

	
	bool					is_end_;	 //胜利或失败，已经结束
	bool					belong_;	//是否使用归属者模式
	bool					is_released_;
	bool					has_mon_damage_event_;
	bool					has_actor_damage_event_;
	bool					run_ai_;
public:
	//副本的场景handle列表
	SceneList				scene_list_;
};



