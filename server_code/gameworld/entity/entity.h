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

// ʵ�崫������
enum EntityTransferStype
{
    etsTeleport,			// ͨ�������Ŵ���
    etsOther,				// ������ʽ����
};

class OwnedBabyInfo
{
public:
	EntityHandle handle_;				// �������
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
	// ��ȡʵ�����չ�����actor
	virtual Actor* GetActor() { return NULL; }

	virtual void OnEntityDeath(EntityHandle killer); //��ʵ��������ʱ��
	virtual void OnEnterScene();
	virtual void OnExitScene(){}
	virtual void OnMove(const Point &pos){}
	inline virtual UpdateMask* GetBroadCastMask() { return NULL; }  //��ȡ�㲥��mask }
	virtual void CreateAppearData(DataPacket& appearPack);
	//����Ŀ��ʵ���handle
	virtual void SetTarget(Entity* target);
	virtual int GetActorId(void) { return 0; };
	virtual uint64_t GetSummitHandle();
	virtual int GetHeadID() { return 0;}
public:

	//��ʵ�巢����Ϣ
	int64_t PostActMsg(ActMsg* msg, int64_t delay = 0, bool callInDestroy = false,
	                   int64_t interv = 0, int count = 1);
	//��ʵ�巢����Ϣ���������ͬ��Ϣ�ŵ���Ϣ�����ԭ����Ϣ
	//void UpdateEntityMsg(const EntityMsg& msg);

	inline const char* GetEntityName() const { return entity_name_; }
	void SetEntityName(const char* name);

	// EntityPosInfo ʵ���λ����Ϣ
	inline const EntityPosInfo& GetPosInfo() const { return entity_pos_; }
	inline void SetPosInfo(EntityPosInfo& posInfo) { entity_pos_ = posInfo; }

	inline FuBen* GetFuBen() const { return entity_pos_.fuben; }
	inline void SetFuBen(FuBen* fb) { entity_pos_.fuben = fb; }
	inline Scene* GetScene() const { return entity_pos_.scene; }
	inline void SetScene(Scene* scene) { entity_pos_.scene = scene; }

	// ��ȡ��ǰ��������λ��
	inline void GetPosition(int& x, int& y) { x = entity_pos_.point_pos.x; y = entity_pos_.point_pos.y; }
	inline const Point& GetPosition() { return entity_pos_.point_pos; }
	//���ý��븱����ԭʼ����
	inline void SetOriginPosition(Point g) { origin_pos = g; }
	inline const Point& GetOriginPosition() { return origin_pos; }


	//��ȡʵ�������ĳ�������ָ��
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


	//��ȡĿ��ʵ���handle
	Entity* GetTarget() const;
	inline EntityHandle GetTargetHdl() const { return target_handle_; }

	int64_t PostScriptEvent(int64_t delay, int64_t interval, int count, const char* func, const ScriptValueList& args);
	void CancelScriptTimer(int64_t handle);


	//������ʵ����������Node
	inline void SetNode(EntityPtrList::NodeType* node) { entity_node_ = node; }

	inline EntityPtrList::NodeType* GetNode() { return entity_node_; }

	void SetMoveDest(const Point& pos) { dest_pos_ = pos; }
	const Point& GetMoveDest() { return dest_pos_; }

	/*
	* Comments:�Ƿ������״̬
	* Param int nStateID:״̬ID
	* @Return bool:�з���true�����򷵻�false
	*/
	bool HasBitState(int sid);

	bool InSafeArea();	//�Ƿ��ڰ�ȫ��

	/*
	* Comments: ����ʵ���״̬��ʵ���״̬�ǰ�λ�洢��
	* Param int nStateID:״̬id
	* @Return bool:�ɹ�����true,���򷵻�false
	*/
	bool AddBitState(int sid);

	/*
	* Comments:ȥ��ʵ���״̬
	* Param int nStateID: �ɹ�����true�����򷵻�false
	* @Return bool:�ɹ�����true�����򷵻�false
	*/
	bool RemoveBitState(int sid);


protected:
	/*
	* Comments:������е�ʵ����Ϣ
	* @Return void:
	* @Remark:
	*/
	void ClearAllActMsg();

	/*
	* Comments: Ͷ��һ��ʵ��������Ϣ
	* @Return void:
	*/
	void PostEntityDeadMsg();

protected:
	// ���������ָ����ʵ����Ϣ
	static bool DelActMsgOnDeath(void* data);

	static void FreeActMsg(void* data);
	static void S_ProcessActMsg(void* data, int* count);

protected:
	char				entity_name_[64];		//���еĳ�����������ֵĳ���
	char                show_name_[128];    //��ʾ�����֣������ʾ������ ����\\����\\��������������NPC���ܸ���ҵ�����
	EntityPosInfo		entity_pos_;
	EntityHandle		entity_handle_;		//ʵ����
	EntityHandle		master_handle_;		//���˾��
	bool				inited_;			//�Ƿ��ʼ������
	EntityHandle        target_handle_;    //ʵ���Ŀ��ľ��
	EntityHandle		target_npc_handle_; //ʵ���npcĿ��ľ��
	TimeCaller			msg_timer_;			//ʵ����Ϣ����

	ACTORNAME			title_;				//ʵ��ĳƺţ��硰�����������ˡ���

	EntityFlags			attri_flag_;			//��������Ա�־λ,����մ�����Ĭ�Ͼ������ñ�����ã����ɳ���̬�޸�
	int					maxFollowDistSqrt_;			// ����������ƽ��
	EntityPtrList::NodeType* entity_node_;

	EntityHandle		killer_;					// ɱ���Լ���handle
	Point				dest_pos_;		// �ƶ���Ŀ�ĵ����꣬�����-1����ʾ�����ƶ�״̬
	Point				origin_pos;		//����entityʱ��ԭ������
	// ��־ĳ��״̬����λ����ʾ
	unsigned int		bit_state_;
	bool				is_init_;	// ����Ƿ��ʼ����ϣ���logic�ﲻ����Ϊ���ֱ�ӷ��أ��ᵼ��timer�ļ�ʱ�ӳ�
};


#endif


