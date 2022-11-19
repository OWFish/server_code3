#pragma once
#include <map>

//class DBDataCache;
class DBSession;
class CDBPvmCache;

class ActorCacheData
{
public:
	ActorId						m_nActorId;							// 角色Id
	int64_t						m_nNextSaveTick;					// 下一次存盘时间
	DataPacket					m_sActorCacheData[DBCacheType_Max];		// 角色数据Cache
	bool						m_bDirty;							// 数据是否需要更新
#ifdef DB_TYPEDIRTY
	bool                        m_bTypeDirty[DBCacheType_Max];            // 某种具体类型的数据更新判断数组
#endif
	bool						m_bExpired;							// 是否过期，如果过期下次RunOne会删除
	static const int64_t		s_nExpireTime;						// 过期时间
	bool						readable_[DBCacheType_Max];
	bool						m_valid;							// 是否有效的，已经登录还没退出写入就是无效的
	ActorCacheData() : m_nActorId(0), m_bExpired(false), m_valid(true) {}

	ActorCacheData(const ActorCacheData& rhs)
	{
		m_nActorId	= rhs.m_nActorId;
		m_bExpired	= false;
		m_valid = true;
		SetDirty(false);
#ifdef DB_TYPEDIRTY
		memset(m_bTypeDirty, 0, sizeof(m_bTypeDirty));
#endif
	}

	inline void Init(BaseAllocator* allocator, ActorId nActorId)
	{
		for (int i = 0; i < DBCacheType_Max; i++)
		{
			m_sActorCacheData[i].setAllocator(allocator);
			readable_[i] = false;
		}

		m_nActorId = nActorId;
		m_nNextSaveTick = _getTickCount();
	}

	inline bool IsDirty() const
	{
		return m_bDirty;
	}

	inline void SetDirty(bool bDirty)
	{
		m_bDirty = bDirty;

		if (bDirty && IsExpired())
			SetExpired(false);
	}
#ifdef DB_TYPEDIRTY
	//因为只是判断是否保存，在出错的情况下，默认保存
	inline bool IsTypeDataDirty(DBCacheType cdType) const
	{
		if ( cdType >= DBCacheType_Max || cdType < 0)
		{
			return true;
		}
		return m_bTypeDirty[cdType];
	}

	inline void SetTypeDataDirty(DBCacheType cdType, bool bDirty)
	{
		if ( cdType >= DBCacheType_Max || cdType < 0)
		{
			return;
		}
		m_bTypeDirty[cdType] = bDirty;
	}
#endif

	inline bool IsExpired() const
	{
		return m_bExpired;
	}

	inline void SetExpired(bool bExpired)
	{
		if (m_bExpired != bExpired)
			m_bExpired = bExpired;
	}

	inline bool CheckAndSet(int64_t nCurrTick)
	{
		if (nCurrTick >= m_nNextSaveTick)
		{
			PostponeNextSaveTick(nCurrTick);
			return true;
		}

		return false;
	}

	void PostponeNextSaveTick(int64_t nCurrTick);
	void SetNextSaveTick(int64_t time);

	inline bool operator < (const ActorCacheData& data)
	{
		return m_nActorId < data.m_nActorId;
	}
};


typedef bool (*SaveHandler)(DataPacketReader&,SQLConnection& sql);

class DBDataCache
{
	friend class ActorCacheData;

public:
	DBDataCache();
	virtual ~DBDataCache() {}
public:
	/*
	* Comments: 缓存角色数据
	* Param enActorCacheDataType cdType: 缓存数据类型
	* Param DataPacketReader & packet: 缓存数据
	* @Return bool: 成功返回true；失败返回false
	* @Remark:
	*/
	bool CacheData(DBCacheType cdType, DataPacketReader& packet);

	/*
	* Comments: 保存Cache数据
	* @Param bCheckCD: 指定是否检测CD
	* @Param bResp: 是否回应消息给逻辑服
	* @Return bool: 成功返回true；失败返回false
	* @Remark:
	*/
	bool SaveData(bool bCheckCD, SQLConnection& sql, bool all = false);
	void SetNextSaveTime(int actorid, int time);
	/*
	* Comments: 例行处理
	* @Return void:
	* @Remark:
	*/
	void RunOne(SQLConnection &sql);

	/*
	* Comments: 角色退出
	* Param DataPacketReader & packet:
	* @Return void:
	* @Remark:
	*/
	void OnActorLogout(DataPacketReader& packet);

	void SaveAllActorDataImmediately(SQLConnection &sql);
	DataPacket* GetReadableData(ActorId aid, int type, bool* valid = NULL);
	ActorBasicData* GetActorBasicData(ActorId aid);

	DataPacket* UpdateCache( ActorId nActorId, int cdType, void* buf, size_t size, bool dirty );

		/*
	* Comments: 清除缓存
	* Param ActorId ai: 角色id
	* Param enActorCacheDataType cdType: 数据类型
	* Param bool toSave: 是否保存
	* @Return bool: 成功返回true；失败返回false
	* @Remark:
	*/
	bool ClearCacheData(SQLConnection& sql, ActorId aid, DBCacheType cdType, bool toSave = true); //清除指定玩家指定类型数据的缓存
	bool ClearCacheData(SQLConnection& sql, DataPacketReader& packet); //清除玩家缓存
	bool ClearCacheData(SQLConnection& sql, ActorId aid, bool toSave = true); //清除指定玩家所有缓存数据
	bool ClearCacheData(SQLConnection& sql, DBCacheType cdType, bool toSave = true); //清除所有玩家指定类型的数据
	bool ClearCacheData(SQLConnection& sql, bool toSave = true); //清除所有玩家的缓存

	// 设置数据有效性
	void SetValidFlag(ActorId aid, bool flag);

	// 设置保存一次需要的最长时间
	static void SetSaveOnceTime(DataPacketReader& packet);
protected:
	/*
	* Comments: 获取角色Id
	* Param DataPacketReader & packet:
	* Param int nOffset: 角色Id在消息包中的偏移
	* @Return int: 成功返回角色id，失败返回0
	* @Remark: 读取数据中的角色id字段，并且不修改packet内容
	*/
	int GetIntFromPacket(DataPacketReader& packet, int nOffset = 0);

	/*
	* Comments:立刻保存角色数据
	* Param int nActorId:
	* Param bool bResp: 是否给逻辑服回应答消息
	* @Return bool:
	* @Remark:
	*/
	bool SaveActorDataImmediately(ActorId nActorId, SQLConnection& sql);

	/*
	* Comments: 移除过期CacheData
	* @Return void:
	* @Remark:
	*/
	void RemoveExpireCache();

	/*
	* Comments: 保存角色数据
	* Param CActorCacheData & data: 角色数据
	* Param bool bCheckCD: 是否检测CD
	* Param int64_t nCurrTick: 当前的TickCount
	* Param bool bResp: 是否给逻辑服务器会操作结果应答消息
	* @Return bool: 成功返回true；失败返回false
	* @Remark:
	*/
	bool SaveActorDataImpl(ActorCacheData& data, bool bCheckCD, int64_t nCurrTick, SQLConnection &sql);

	bool SaveActorBasicData(DataPacketReader& packet, SQLConnection& sql);
	bool SaveNothing(DataPacketReader& packet, SQLConnection& sql);

	bool SaveRoleData(DataPacketReader& packet, SQLConnection& sql);
	/*bool SaveBagItemData(DataPacketReader& packet,	 SQLConnection& sql);
	bool SaveEquipItemData(DataPacketReader& packet, SQLConnection& sql);
	bool SaveDepotItemData(DataPacketReader& packet, SQLConnection& sql);
	bool SavePetItemData(DataPacketReader& packet,	 SQLConnection& sql);
	bool SaveMountItemData(DataPacketReader& packet,	 SQLConnection& sql);
	
	bool SaveSkillData(DataPacketReader& packet,	 SQLConnection& sql);
	bool SaveQuestData(DataPacketReader& packet,	 SQLConnection& sql);
	bool SaveGuildData(DataPacketReader& packet,	 SQLConnection& sql);
	bool SaveMiscData(DataPacketReader& packet,	 SQLConnection& sql);
	bool SaveScriptData(DataPacketReader& packet,	 SQLConnection& sql);
	bool SaveGemData(DataPacketReader& packet,		 SQLConnection& sql);
	bool SaveMountData(DataPacketReader& packet,		 SQLConnection& sql);
	bool SaveDmkjItemData(DataPacketReader& packet, SQLConnection& sql);
	bool SaveBuffData(DataPacketReader& packet, SQLConnection& sql);
	bool SaveAchData(DataPacketReader& packet, SQLConnection& sql);
	bool SaveFbCountData(DataPacketReader& packet, SQLConnection& sql);
	bool SaveCrossData(DataPacketReader& packet, SQLConnection& sql);
	bool SaveCaleData(DataPacketReader& packet, SQLConnection& sql);
	bool SavePlotData(DataPacketReader& packet, SQLConnection& sql);
	bool SaveMiscStruct(DataPacketReader& packet, SQLConnection& sql);
	bool SavePetSkill(DataPacketReader& packet, SQLConnection& sql);
	bool SavePetBase(DataPacketReader& packet, SQLConnection& sql);
	bool SaveEntrustData(DataPacketReader& packet, SQLConnection& sql);
	bool SavePetCrossItem(DataPacketReader& packet, SQLConnection& sql);
	bool SaveCrossVar(DataPacketReader& packet, SQLConnection& sql);
	bool SaveTongTianTaData(DataPacketReader& packet, SQLConnection& sql);
	bool SaveMijiItem(DataPacketReader& packet, SQLConnection& sql);
	bool SaveWingData(DataPacketReader& packet, SQLConnection& sql);
	bool SaveMarryInfo(DataPacketReader& packet, SQLConnection& sql);
	*/

public:
	// 以下是改变缓存数据的函数
	// 清除缓存中玩家的帮派的数据
	void ClearWeekCharm();
private:
	BaseAllocator				m_allocator;						// BuffAllocator
	std::map<ActorId, ActorCacheData>	m_sActorCacheDataTbl;				// 角色Cache数据表
	int64_t						m_nNextCheckTime;					// 检测更新角色数据定时器
	bool							m_bHasExpireCache;					// 标记是否删除Cache数据
	static const int64_t			s_nCheckInterval;					// 检测更新角色数据定时器间隔
public:
	static SaveHandler		s_aActorCacheHandler[DBCacheType_Max];				// 角色数据Cache处理器表
	static int64_t			s_nActorCacheSaveInterval;			// 角色数据存盘间隔
	static int64_t			s_nSaveOnceTime;					// 保存一次最长的时间(毫秒)
};

