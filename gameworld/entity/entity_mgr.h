#ifndef _ENTITY_MGR_H_
#define _ENTITY_MGR_H_

/***************************************************************
*游戏中实体的管理器，实体包括角色， 怪物，npc等



!!! 注意,增加镜像玩家后,实体管理器仍然正常返回actor,需要处理actor的地方
要考虑使用场景,尤其是导出给lua的接口,要排除掉镜像和未初始化的玩家

***************************************************************/

#include "entity.h"


//使用链表管理游戏世界里的实体
template<class T, int EntityCount = 1024>
class WorldEntityList
{
public:
	WorldEntityList(const char* desc, int limit = 4, int div = 1) : entity_mgr_(desc)
	{
		run_limit_ = limit;
		iterator_.setList(entity_list_);
		div_num_ = div;
	}

	//释放一个handle
	inline void Release(EntityHandle handle)
	{
		entity_mgr_.Release(handle);
	}

	// 添加一个实体
	inline void Add(Entity* et)
	{
		if (!et) return;

		T* entity = (T*)et;
		// 设置实体的节点为为当前的节点，为了删除的时候高效地删除
		et->SetNode(entity_list_.linkAfter(entity));
	}

	// 删除一个实体
	inline bool Destroy(Entity* et)
	{
		if (!et) return false;

		EntityPtrList::NodeType* node = (EntityPtrList::NodeType*)et->GetNode();

		if (node)
		{
			iterator_.remove(node);
		}

		et->SetNode(NULL);
		return true;
	}

	inline void Empty()
	{
		entity_list_.clear();
	}

	/*
	* Comments:一次逻辑调用
	* Param Uint64 nRunTimes:当前主循环运行了几轮
	* @Return bool: 是否超时，如果超时返回true，否则返回false
	*/
	bool Run(int64_t tick)
	{
		size_t max_run_cnt = this->entity_list_.count() / div_num_;

		int64_t start = _getTickCount();

		T* entity;
		EntityPtrList::NodeType* node;
		size_t run_cnt = 0;

		while ((node = iterator_.next()))
		{
			entity = (T*)node->data_;

			if (entity)
			{
				entity->RunOne(tick);
				run_cnt++;

				if (int(_getTickCount() - start) > run_limit_ || 
					run_cnt >= max_run_cnt)   //
				{
					return true;
				}
			}
		}

		return false;
	}

	inline void SetDiv(int num)
	{
		div_num_ = num;
	}
public:
	EntityPtrList entity_list_;
	memory::HandleMgr<T, EntityHandle, EntityCount> entity_mgr_; // 实体的管理器
	EntityPtrList::Iterator iterator_;  // 当前的迭代器
	int run_limit_;  // 执行的最大的时间
	int div_num_;
};

class EntityMgr:
	public SendPacketPool //实体管理器搞这个为了管理网络数据包，实现分时处理
{
public:
	typedef WorldEntityList<Actor, 128> ActorMgr;
	typedef WorldEntityList<Role, 256> RoleMgr;
	typedef WorldEntityList<Monster> MonsterMgr;
	typedef WorldEntityList<Npc, 256> NpcMgr;
	typedef WorldEntityList<RoleClone, 256> RoleCloneMgr;
	//typedef WorldEntityList<MovingNPC> MovingNpcMgr;
	typedef WorldEntityList<ScriptNpc, 2> ScriptNpcMgr;
	//typedef WorldEntityList<Transfer, 128> TransferMgr;  //传送门
	typedef WorldEntityList<GatherMonster, 512> GatherMonsterMgr;
	typedef WorldEntityList<DropBag, 256>	DropBagMgr;

	EntityMgr();
	~EntityMgr(){}

	bool Initialize();
	void Destroy();

	void CloseAllActor(int gate = -1);
	//有玩家登陆了，将记录他的
	void OnActorLogin(Actor* actor);
	void OnActorClosed(Actor* actor);

	void AddImage() { image_actor_count_++; } // 增加一个镜像记录
	void DecImage() { image_actor_count_--; } // 减少一个镜像记录
	void SendActorOnline(ActorId actorid, uint8_t status, int serverid = 0);

	// 把玩家的名字加到索引中
	void AddToNameList(Actor* actor);

	// db服务器返回sql的结果
	void OnDbReturnData(int cmd, DataPacketReader& reader);

	/*
	* Comments: 创建一个实体
	* Param int nEntityType: 实体的类型
	* Param EntityHandle & hHandle: 实体的handle
	* @Return CEntity *:实体的指针
	*/
	Entity* CreateEntity(int nEntityType, EntityHandle& hHandle);  //创建一个实体,返回他的实体ID

	/*
	* Comments: 通过实体的handle销毁一个实体
	* Param EntityHandle nEntityID: 实体的handle
	* Param bool bDelayDestroy: 延迟删除
	* @Return bool:成功返回true，否则返回false
	*/
	bool DestroyEntity(EntityHandle handle, bool delay = false); //销毁一个实体

	/*
	* Comments: 通过实体handle返回实体指针
	* Param EntityHandle & hEntity: 实体 handle
	* @Return CEntity *:实体指针
	*/
	Entity* GetEntity(const EntityHandle& handle);

	/*
	* Comments: 通过玩家的名字查找指针
	* Param char * name: 玩家名字
	* @Return Actor *: 数据指针
	*/
	Actor* GetActorPtrByName(const char* name);

	/*
	* Comments: 通过actorID找玩家的指针
	* Param unsigned int nActorID: 玩家的角色id
	* Param bool getImage:是否获取镜像玩家
	* @Return Actor *: 玩家的数据指针
	*/
	Actor* GetActorPtrById(ActorId aid);

	Actor* GetActorPtrByAccount(const char* name);

	void RunOne();

	/*
	* Comments: 获取在线人数的数量
	* @Return int:返回在线人数的总数
	*/
	inline int GetOnlineActorCount(bool includeCache = false)
	{
		return actor_mgr_.entity_list_.count() - (includeCache ? 0 : image_actor_count_);
	}

	// 获取游戏内所有怪物的总数量（包括副本内的）
	inline int GetMonsterCount()
	{
		return monster_mgr_.entity_list_.count();
	}

	// 获取所有在线玩家的ID并写到数据包
	void GetOnlineActorIdToPack(DataPacket& pack);

	// 获取所有在线玩家的指针
	int GetOnlineActorPtrList(void** actorList, int max_count);

	/*
	* Comments:更新怪物句柄，为怪物死亡立即刷新时实体复用适用。
	* Param CEntity * pEntity: 怪物实体对象指针
	* @Return void:
	*/
	void UpdateMonsterHandle(Entity* et);

	inline void SetMonsterMgrDiv(int num)
	{
		monster_mgr_.SetDiv(num);
	}

	void OnSsReturnData(int cmd, DataPacketReader& reader);

	void OnActorChangeName(Actor* actor, const char* lastName);

	ActorMgr & GetActorMgr() { return actor_mgr_; }

public:
	static const int		one_entity_t_ = 4; //一个实体处理的最大的时间

private:
	ActorMgr				actor_mgr_;		//玩家 在线
	RoleMgr					role_mgr_;		//玩家自角色
	MonsterMgr				monster_mgr_;	//monster
	NpcMgr					npc_mgr_;			//nPC的管理器
	//MovingNpcMgr			moving_npc_mgr_; //移动的NPC的管理器
	ScriptNpcMgr			script_npc_mgr_; //脚本NPC的管理器
	//TransferMgr				transfer_mgr_; //传送门的管理器
	GatherMonsterMgr		gather_mgr_; // 采集怪句柄管理器
	DropBagMgr				dropbag_mgr_;	// 掉落包裹
	RoleCloneMgr				role_clone_mgr_;  // 子角色克隆
	Vector<EntityHandle>	wait_remove_list_; // 等待删除实体列表。在每次logicRun中删除

	container::StaticHashTable<EntityHandle, 4096 * 4> actor_id_table_;
	container::StaticHashTable<EntityHandle, 4096 * 4> actor_name_table_;
	int						image_actor_count_;	// 镜像玩家数量记录
};

#endif

