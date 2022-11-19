#ifndef _ENTITY_MGR_H_
#define _ENTITY_MGR_H_

/***************************************************************
*��Ϸ��ʵ��Ĺ�������ʵ�������ɫ�� ���npc��



!!! ע��,���Ӿ�����Һ�,ʵ���������Ȼ��������actor,��Ҫ����actor�ĵط�
Ҫ����ʹ�ó���,�����ǵ�����lua�Ľӿ�,Ҫ�ų��������δ��ʼ�������

***************************************************************/

#include "entity.h"


//ʹ�����������Ϸ�������ʵ��
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

	//�ͷ�һ��handle
	inline void Release(EntityHandle handle)
	{
		entity_mgr_.Release(handle);
	}

	// ���һ��ʵ��
	inline void Add(Entity* et)
	{
		if (!et) return;

		T* entity = (T*)et;
		// ����ʵ��Ľڵ�ΪΪ��ǰ�Ľڵ㣬Ϊ��ɾ����ʱ���Ч��ɾ��
		et->SetNode(entity_list_.linkAfter(entity));
	}

	// ɾ��һ��ʵ��
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
	* Comments:һ���߼�����
	* Param Uint64 nRunTimes:��ǰ��ѭ�������˼���
	* @Return bool: �Ƿ�ʱ�������ʱ����true�����򷵻�false
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
	memory::HandleMgr<T, EntityHandle, EntityCount> entity_mgr_; // ʵ��Ĺ�����
	EntityPtrList::Iterator iterator_;  // ��ǰ�ĵ�����
	int run_limit_;  // ִ�е�����ʱ��
	int div_num_;
};

class EntityMgr:
	public SendPacketPool //ʵ������������Ϊ�˹����������ݰ���ʵ�ַ�ʱ����
{
public:
	typedef WorldEntityList<Actor, 128> ActorMgr;
	typedef WorldEntityList<Role, 256> RoleMgr;
	typedef WorldEntityList<Monster> MonsterMgr;
	typedef WorldEntityList<Npc, 256> NpcMgr;
	typedef WorldEntityList<RoleClone, 256> RoleCloneMgr;
	//typedef WorldEntityList<MovingNPC> MovingNpcMgr;
	typedef WorldEntityList<ScriptNpc, 2> ScriptNpcMgr;
	//typedef WorldEntityList<Transfer, 128> TransferMgr;  //������
	typedef WorldEntityList<GatherMonster, 512> GatherMonsterMgr;
	typedef WorldEntityList<DropBag, 256>	DropBagMgr;

	EntityMgr();
	~EntityMgr(){}

	bool Initialize();
	void Destroy();

	void CloseAllActor(int gate = -1);
	//����ҵ�½�ˣ�����¼����
	void OnActorLogin(Actor* actor);
	void OnActorClosed(Actor* actor);

	void AddImage() { image_actor_count_++; } // ����һ�������¼
	void DecImage() { image_actor_count_--; } // ����һ�������¼
	void SendActorOnline(ActorId actorid, uint8_t status, int serverid = 0);

	// ����ҵ����ּӵ�������
	void AddToNameList(Actor* actor);

	// db����������sql�Ľ��
	void OnDbReturnData(int cmd, DataPacketReader& reader);

	/*
	* Comments: ����һ��ʵ��
	* Param int nEntityType: ʵ�������
	* Param EntityHandle & hHandle: ʵ���handle
	* @Return CEntity *:ʵ���ָ��
	*/
	Entity* CreateEntity(int nEntityType, EntityHandle& hHandle);  //����һ��ʵ��,��������ʵ��ID

	/*
	* Comments: ͨ��ʵ���handle����һ��ʵ��
	* Param EntityHandle nEntityID: ʵ���handle
	* Param bool bDelayDestroy: �ӳ�ɾ��
	* @Return bool:�ɹ�����true�����򷵻�false
	*/
	bool DestroyEntity(EntityHandle handle, bool delay = false); //����һ��ʵ��

	/*
	* Comments: ͨ��ʵ��handle����ʵ��ָ��
	* Param EntityHandle & hEntity: ʵ�� handle
	* @Return CEntity *:ʵ��ָ��
	*/
	Entity* GetEntity(const EntityHandle& handle);

	/*
	* Comments: ͨ����ҵ����ֲ���ָ��
	* Param char * name: �������
	* @Return Actor *: ����ָ��
	*/
	Actor* GetActorPtrByName(const char* name);

	/*
	* Comments: ͨ��actorID����ҵ�ָ��
	* Param unsigned int nActorID: ��ҵĽ�ɫid
	* Param bool getImage:�Ƿ��ȡ�������
	* @Return Actor *: ��ҵ�����ָ��
	*/
	Actor* GetActorPtrById(ActorId aid);

	Actor* GetActorPtrByAccount(const char* name);

	void RunOne();

	/*
	* Comments: ��ȡ��������������
	* @Return int:������������������
	*/
	inline int GetOnlineActorCount(bool includeCache = false)
	{
		return actor_mgr_.entity_list_.count() - (includeCache ? 0 : image_actor_count_);
	}

	// ��ȡ��Ϸ�����й���������������������ڵģ�
	inline int GetMonsterCount()
	{
		return monster_mgr_.entity_list_.count();
	}

	// ��ȡ����������ҵ�ID��д�����ݰ�
	void GetOnlineActorIdToPack(DataPacket& pack);

	// ��ȡ����������ҵ�ָ��
	int GetOnlineActorPtrList(void** actorList, int max_count);

	/*
	* Comments:���¹�������Ϊ������������ˢ��ʱʵ�帴�����á�
	* Param CEntity * pEntity: ����ʵ�����ָ��
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
	static const int		one_entity_t_ = 4; //һ��ʵ�崦�������ʱ��

private:
	ActorMgr				actor_mgr_;		//��� ����
	RoleMgr					role_mgr_;		//����Խ�ɫ
	MonsterMgr				monster_mgr_;	//monster
	NpcMgr					npc_mgr_;			//nPC�Ĺ�����
	//MovingNpcMgr			moving_npc_mgr_; //�ƶ���NPC�Ĺ�����
	ScriptNpcMgr			script_npc_mgr_; //�ű�NPC�Ĺ�����
	//TransferMgr				transfer_mgr_; //�����ŵĹ�����
	GatherMonsterMgr		gather_mgr_; // �ɼ��־��������
	DropBagMgr				dropbag_mgr_;	// �������
	RoleCloneMgr				role_clone_mgr_;  // �ӽ�ɫ��¡
	Vector<EntityHandle>	wait_remove_list_; // �ȴ�ɾ��ʵ���б���ÿ��logicRun��ɾ��

	container::StaticHashTable<EntityHandle, 4096 * 4> actor_id_table_;
	container::StaticHashTable<EntityHandle, 4096 * 4> actor_name_table_;
	int						image_actor_count_;	// �������������¼
};

#endif

