#pragma once
#include <map>

//class DBDataCache;
class DBSession;
class CDBPvmCache;

class ActorCacheData
{
public:
	ActorId						m_nActorId;							// ��ɫId
	int64_t						m_nNextSaveTick;					// ��һ�δ���ʱ��
	DataPacket					m_sActorCacheData[DBCacheType_Max];		// ��ɫ����Cache
	bool						m_bDirty;							// �����Ƿ���Ҫ����
#ifdef DB_TYPEDIRTY
	bool                        m_bTypeDirty[DBCacheType_Max];            // ĳ�־������͵����ݸ����ж�����
#endif
	bool						m_bExpired;							// �Ƿ���ڣ���������´�RunOne��ɾ��
	static const int64_t		s_nExpireTime;						// ����ʱ��
	bool						readable_[DBCacheType_Max];
	bool						m_valid;							// �Ƿ���Ч�ģ��Ѿ���¼��û�˳�д�������Ч��
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
	//��Ϊֻ���ж��Ƿ񱣴棬�ڳ��������£�Ĭ�ϱ���
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
	* Comments: �����ɫ����
	* Param enActorCacheDataType cdType: ������������
	* Param DataPacketReader & packet: ��������
	* @Return bool: �ɹ�����true��ʧ�ܷ���false
	* @Remark:
	*/
	bool CacheData(DBCacheType cdType, DataPacketReader& packet);

	/*
	* Comments: ����Cache����
	* @Param bCheckCD: ָ���Ƿ���CD
	* @Param bResp: �Ƿ��Ӧ��Ϣ���߼���
	* @Return bool: �ɹ�����true��ʧ�ܷ���false
	* @Remark:
	*/
	bool SaveData(bool bCheckCD, SQLConnection& sql, bool all = false);
	void SetNextSaveTime(int actorid, int time);
	/*
	* Comments: ���д���
	* @Return void:
	* @Remark:
	*/
	void RunOne(SQLConnection &sql);

	/*
	* Comments: ��ɫ�˳�
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
	* Comments: �������
	* Param ActorId ai: ��ɫid
	* Param enActorCacheDataType cdType: ��������
	* Param bool toSave: �Ƿ񱣴�
	* @Return bool: �ɹ�����true��ʧ�ܷ���false
	* @Remark:
	*/
	bool ClearCacheData(SQLConnection& sql, ActorId aid, DBCacheType cdType, bool toSave = true); //���ָ�����ָ���������ݵĻ���
	bool ClearCacheData(SQLConnection& sql, DataPacketReader& packet); //�����һ���
	bool ClearCacheData(SQLConnection& sql, ActorId aid, bool toSave = true); //���ָ��������л�������
	bool ClearCacheData(SQLConnection& sql, DBCacheType cdType, bool toSave = true); //����������ָ�����͵�����
	bool ClearCacheData(SQLConnection& sql, bool toSave = true); //���������ҵĻ���

	// ����������Ч��
	void SetValidFlag(ActorId aid, bool flag);

	// ���ñ���һ����Ҫ���ʱ��
	static void SetSaveOnceTime(DataPacketReader& packet);
protected:
	/*
	* Comments: ��ȡ��ɫId
	* Param DataPacketReader & packet:
	* Param int nOffset: ��ɫId����Ϣ���е�ƫ��
	* @Return int: �ɹ����ؽ�ɫid��ʧ�ܷ���0
	* @Remark: ��ȡ�����еĽ�ɫid�ֶΣ����Ҳ��޸�packet����
	*/
	int GetIntFromPacket(DataPacketReader& packet, int nOffset = 0);

	/*
	* Comments:���̱����ɫ����
	* Param int nActorId:
	* Param bool bResp: �Ƿ���߼�����Ӧ����Ϣ
	* @Return bool:
	* @Remark:
	*/
	bool SaveActorDataImmediately(ActorId nActorId, SQLConnection& sql);

	/*
	* Comments: �Ƴ�����CacheData
	* @Return void:
	* @Remark:
	*/
	void RemoveExpireCache();

	/*
	* Comments: �����ɫ����
	* Param CActorCacheData & data: ��ɫ����
	* Param bool bCheckCD: �Ƿ���CD
	* Param int64_t nCurrTick: ��ǰ��TickCount
	* Param bool bResp: �Ƿ���߼���������������Ӧ����Ϣ
	* @Return bool: �ɹ�����true��ʧ�ܷ���false
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
	// �����Ǹı仺�����ݵĺ���
	// �����������ҵİ��ɵ�����
	void ClearWeekCharm();
private:
	BaseAllocator				m_allocator;						// BuffAllocator
	std::map<ActorId, ActorCacheData>	m_sActorCacheDataTbl;				// ��ɫCache���ݱ�
	int64_t						m_nNextCheckTime;					// �����½�ɫ���ݶ�ʱ��
	bool							m_bHasExpireCache;					// ����Ƿ�ɾ��Cache����
	static const int64_t			s_nCheckInterval;					// �����½�ɫ���ݶ�ʱ�����
public:
	static SaveHandler		s_aActorCacheHandler[DBCacheType_Max];				// ��ɫ����Cache��������
	static int64_t			s_nActorCacheSaveInterval;			// ��ɫ���ݴ��̼��
	static int64_t			s_nSaveOnceTime;					// ����һ�����ʱ��(����)
};

