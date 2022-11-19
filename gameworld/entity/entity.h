#ifndef _ENTITY_H_
#define _ENTITY_H_

#define GetIntProp GetProperty<int>
#define SetIntProp SetProperty<int>
#define SetIntPropEx SetPropFromSet<int>

#define GetUIntProp GetProperty<unsigned int>
#define SetUIntProp SetProperty<unsigned int>

#define GetFloatProp GetProperty<float>
#define SetFloatProp SetProperty<float>

class ObserverSystem;
class MoveSystem;
class BuffSystem;
class UserBag;
class QuestSystem;
struct ActMsg;
class Actor;


typedef LinkedListEx<Entity*>	EntityPtrList;

// 实体传送类型
enum EntityTransferStype
{
    etsTeleport,			// 通过传送门传送
    etsOther,				// 其他方式传送
};

class OwnedBabyInfo
{
public:
	EntityHandle handle_;				// 宝宝句柄
};

class Entity
{
	friend class Actor;
public:
	static const int MAX_BABY = 4;
	typedef StaticArrayList<OwnedBabyInfo, MAX_BABY>	BabyList;
public:

	Entity();
	virtual ~Entity();

	virtual bool Init(void* data, size_t size);
	virtual void OnDestroy();

	inline void RunOne(int64_t now_t)
	{
		BeforeLogicRun(now_t);
		LogicRun(now_t);
		AfterLogicRun(now_t);
	}

	virtual void BeforeLogicRun(int64_t curr_t);
	virtual void LogicRun(int64_t curr_t);
	virtual void AfterLogicRun(int64_t curr_t);

	virtual int GetId() = 0;

	virtual bool IsCreature() { return false; }
	virtual bool isNonLive() { return false; }
	virtual bool IsMonster() { return false; }
	virtual bool IsAttackImmune() { return false; }
	virtual bool IsDeath() { return false; }
	// 获取实体最终归属的actor
	virtual Actor* GetActor() { return NULL; }

	virtual void OnEntityDeath(EntityHandle killer); //当实体死亡的时候
	virtual void OnEnterScene();
	virtual void OnExitScene(){}
	virtual void OnMove(const Point &pos){}
	inline virtual UpdateMask* GetBroadCastMask() { return NULL; }  //获取广播的mask }
	virtual void CreateAppearData(DataPacket& appearPack);
	//设置目标实体的handle
	virtual void SetTarget(Entity* target);
	virtual int GetActorId(void) { return 0; };
	virtual uint64_t GetSummitHandle();
	virtual int GetHeadID() { return 0;}
public:

	//向实体发送消息
	int64_t PostActMsg(ActMsg* msg, int64_t delay = 0, bool callInDestroy = false,
	                   int64_t interv = 0, int count = 1);
	//向实体发送消息，如果存在同消息号的消息则更新原有消息
	//void UpdateEntityMsg(const EntityMsg& msg);

	inline const char* GetEntityName() const { return entity_name_; }
	void SetEntityName(const char* name);

	// EntityPosInfo 实体的位置信息
	inline const EntityPosInfo& GetPosInfo() const { return entity_pos_; }
	inline void SetPosInfo(EntityPosInfo& posInfo) { entity_pos_ = posInfo; }

	inline FuBen* GetFuBen() const { return entity_pos_.fuben; }
	inline void SetFuBen(FuBen* fb) { entity_pos_.fuben = fb; }
	inline Scene* GetScene() const { return entity_pos_.scene; }
	inline void SetScene(Scene* scene) { entity_pos_.scene = scene; }

	// 获取当前像素坐标位置
	inline void GetPosition(int& x, int& y) { x = entity_pos_.point_pos.x; y = entity_pos_.point_pos.y; }
	inline const Point& GetPosition() { return entity_pos_.point_pos; }
	//设置进入副本的原始坐标
	inline void SetOriginPosition(Point g) { origin_pos = g; }
	inline const Point& GetOriginPosition() { return origin_pos; }


	//获取实体所处的场景对象指针
	inline void SetPosition(const Point &point) { entity_pos_.point_pos = point; }
	inline void SetPosition(const Grid &pos) { SetPosition(pos.ToPoint()); }

	inline unsigned int GetType() const { return entity_handle_.GetType(); }
	void SetType(int type) { entity_handle_.SetType(type); }

	inline const EntityHandle& GetHandle() const { return entity_handle_; }
	inline const EntityHandle& GetMasterHandle() const { return master_handle_; }
	Entity* GetMaster(); 
	inline void SetHandle(const EntityHandle& hHandle) { entity_handle_ = hHandle; }
	inline void SetMasterHandle(const EntityHandle& hHandle) { master_handle_ = hHandle; }
	inline void SetInitFlag(bool flag) { inited_ = flag; }

	inline bool IsInited() const { return inited_; }


	//获取目标实体的handle
	Entity* GetTarget() const;
	inline EntityHandle GetTargetHdl() const { return target_handle_; }

	int64_t PostScriptEvent(int64_t delay, int64_t interval, int count, const char* func, const ScriptValueList& args);
	void CancelScriptTimer(int64_t handle);


	//设置在实体管理器里的Node
	inline void SetNode(EntityPtrList::NodeType* node) { entity_node_ = node; }

	inline EntityPtrList::NodeType* GetNode() { return entity_node_; }

	void SetMoveDest(const Point& pos) { dest_pos_ = pos; }
	const Point& GetMoveDest() { return dest_pos_; }

	/*
	* Comments:是否有这个状态
	* Param int nStateID:状态ID
	* @Return bool:有返回true，否则返回false
	*/
	bool HasBitState(int sid);

	bool InSafeArea();	//是否在安全区

	/*
	* Comments: 设置实体的状态，实体的状态是按位存储的
	* Param int nStateID:状态id
	* @Return bool:成功返回true,否则返回false
	*/
	bool AddBitState(int sid);

	/*
	* Comments:去除实体的状态
	* Param int nStateID: 成功返回true，否则返回false
	* @Return bool:成功返回true，否则返回false
	*/
	bool RemoveBitState(int sid);


protected:
	/*
	* Comments:清空所有的实体消息
	* @Return void:
	* @Remark:
	*/
	void ClearAllActMsg();

	/*
	* Comments: 投递一个实体死亡消息
	* @Return void:
	*/
	void PostEntityDeadMsg();

protected:
	// 死亡后清除指定的实体消息
	static bool DelActMsgOnDeath(void* data);

	static void FreeActMsg(void* data);
	static void S_ProcessActMsg(void* data, int* count);

protected:
	char				entity_name_[64];		//所有的长度用玩家名字的长度
	char                show_name_[128];    //显示的名字，玩家显示的名字 名字\\帮派\\帮派排名，其他NPC可能改玩家的名字
	EntityPosInfo		entity_pos_;
	EntityHandle		entity_handle_;		//实体句柄
	EntityHandle		master_handle_;		//主人句柄
	bool				inited_;			//是否初始化好了
	EntityHandle        target_handle_;    //实体的目标的句柄
	EntityHandle		target_npc_handle_; //实体的npc目标的句柄
	TimeCaller			msg_timer_;			//实体消息队列

	ACTORNAME			title_;				//实体的称号，如“铁匠”“商人”等

	EntityFlags			attri_flag_;			//怪物的属性标志位,怪物刚创建，默认就是配置表的设置，可由程序动态修改
	int					maxFollowDistSqrt_;			// 最大跟随距离的平方
	EntityPtrList::NodeType* entity_node_;

	EntityHandle		killer_;					// 杀死自己的handle
	Point				dest_pos_;		// 移动的目的地坐标，如果是-1，表示不在移动状态
	Point				origin_pos;		//创建entity时的原点坐标
	// 标志某个状态，用位来表示
	unsigned int		bit_state_;
	bool				is_init_;	// 标记是否初始化完毕，但logic里不能因为这个直接返回，会导致timer的计时延迟
};


#endif


