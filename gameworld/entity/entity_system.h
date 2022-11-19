#ifndef _ENTITY_SYSTEM_H_
#define _ENTITY_SYSTEM_H_

/***************************************************************
*                     实体的子系统基类
* 实体的功能模块,比如组队子系统,技能子系统，继承这个基类
* 实体的子系统实现一个特定的功能，并有网络消息的分发功能
* 游戏中的技能,buff，任务等特定的功能都可以搞一个子系统，给实体挂一个
***************************************************************/
class Entity;
/*
	SUBSYSTEMID 子系统的ID
	SonClass    子类
	EntityClass	该子系统所挂载的实体类型
*/
template<int SUBSYSTEMID, class SonClass, class EntityClass>
class EntitySystem
{
public:
	EntitySystem() : entity_(NULL), load_data_(false)
	{
		entity_ = NULL;
	}

	virtual ~EntitySystem()
	{
		load_data_ = false;
	}

	/*
	 *子系统的初始化，
	 *lpEntity 子系统所属的实体指针
	 *data 初始化的数据，如果没有用 NULL
	 *size 子系统初始化数据的长度，如果没有数据用0
	*/
	inline bool Create(EntityClass* entity, void* data, size_t size)
	{
		entity_ = entity;
		return Initialize(data, size);
	}

	//子系统初始化,如果是玩家需要输入玩家的存盘数据
	virtual bool Initialize(void* /*data*/, size_t /*size*/)
	{
		return true;
	}

	/*
	* Comments: 数据库返回数据
	* Param int nCmd: 命令码，如下面的命令
	* Param DataPacketReader reader &: 读写器
	* @Return void:
	*/
	virtual void OnDbRetData(int /*nCmd*/, int /*nErrorCode*/, DataPacketReader& /*reader*/) {}

	/*
	*存盘接口，传的是存盘的结构指针,单独存盘的系统就不关住这个数据指针
	*data 玩家存盘数据指针
	*/
	virtual void Save(ActorBasicData* /*pData*/) { }

	//清空内存
	virtual void Destroy() {};

	//获取子系统的ID
	inline int GetSystemID() const
	{
		return SUBSYSTEMID;
	}

	/*
	 *处理网络数据包
	 *nCmd ，分派到该系统里命令，从0开始
	 *packet，网络数据
	*/
	virtual void ProcessNetData(int /*nCmd*/, DataPacketReader& /*packet*/) {};

	//角色各子系统初始化完毕，向客户端发送创建主角的数据包后，调用该接口
	virtual void OnEnterGame() {};
protected:
	EntityClass* entity_; //这个子系统是属于那个实体的,保持的是实体的指针
	bool load_data_;
};

#endif

