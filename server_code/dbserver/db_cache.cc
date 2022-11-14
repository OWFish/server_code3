#include "StdAfx.h"


void ActorCacheData::PostponeNextSaveTick(int64_t nCurrTick)
{
	m_nNextSaveTick = nCurrTick + DBDataCache::s_nActorCacheSaveInterval;
}

void ActorCacheData::SetNextSaveTick(int64_t time)
{
	m_nNextSaveTick = time;
}

// 改成很大的数字，即永远不移除缓存
const int64_t ActorCacheData::s_nExpireTime = int64_t(0xffffff) * SecondTime::SecOfMin * 1000;
const int64_t DBDataCache::s_nCheckInterval = 1 * 1000;
int64_t	DBDataCache::s_nActorCacheSaveInterval;
int64_t DBDataCache::s_nSaveOnceTime = 32;

SaveHandler DBDataCache::s_aActorCacheHandler[DBCacheType_Max] =
{
	DBSession::SaveActorToDB,
	DBSession::SaveRoleData,
	DBSession::SaveScriptDataToDB,
	DBSession::SaveBagData,
	DBSession::SaveBagData,
	DBSession::SaveMailData,
	DBSession::SaveStoreData,
	DBSession::SaveBagData,
	DBSession::SaveActorGuild,
	DBSession::SaveTogHitEquipData,
	DBSession::SaveCsScriptDataToDB,
	DBSession::SaveActorCacheToDB,
	/***********按DDBCacheType顺序添加处理函数***************/
	/***********按DDBCacheType顺序添加处理函数***************/
	/***********按DDBCacheType顺序添加处理函数***************/
	/***********按DDBCacheType顺序添加处理函数***************/
};

STATIC_ASSERT(sizeof(DBDataCache::s_aActorCacheHandler) / sizeof(DBDataCache::s_aActorCacheHandler[0]) == DBCacheType_Max);

DBDataCache::DBDataCache() : m_allocator("CDBDataCache")
{
	m_bHasExpireCache = false;
	//SetDBClient(NULL);
	m_nNextCheckTime = _getTickCount();

	//设置保存时间
	s_nActorCacheSaveInterval = 5 * SecondTime::SecOfMin * 1000;
}

//void DBDataCache::SetDBClient(DBSession* pClient)
//{
//	//db_client_ = pClient;
//}

bool DBDataCache::CacheData(DBCacheType cdType, DataPacketReader& packet)
{
	if (cdType >= 0 && cdType < DBCacheType_Max)
	{
		STATIC_ASSERT(sizeof(ActorId) == 4);
		int id = GetIntFromPacket(packet);

		if (cdType == 2) printf("-#########---------%d\n", (int)packet.getAvaliableLength());
		if (id != 0 && (!UpdateCache(id, cdType, packet.getOffsetPtr(), packet.getAvaliableLength(), true)))
			return false;
	}
	else
	{
		OutputMsg(rmError, ("CacheData[type=%d] failed"), (int)cdType);
	}

	return true;
}

int DBDataCache::GetIntFromPacket(DataPacketReader& packet, int nOffset)
{
	int id = 0;

	if (packet.getAvaliableLength() < sizeof(id) + nOffset)
		return 0;

	size_t nPos = packet.getPosition();

	if (nOffset != 0)
		packet.adjustOffset(nOffset);

	packet >> id;
	packet.setPosition(nPos);
	return id;
}


void DBDataCache::OnActorLogout(DataPacketReader& packet)
{
	///zac:原来的算法是玩家下线后，就开始保存用户在缓存中的数据，现在修改为玩家下线后仍然不保存到数据库中，
	///而是等到保存的时间=上次保存的时间+s_nActorCacheSaveInterval 。这样可以减少玩家频繁登陆时写数据库的次数
	///注意：这样做的话，玩家上线时，查询数据库必须是在缓存中读出，而不能直接读取数据库的数据，因为数据可能还没存到数据库中
	//ActorId nActorId = GetActorId(packet, 0);
	//SaveActorDataImmediately(nActorId, false);
}

void DBDataCache::SaveAllActorDataImmediately(SQLConnection &sql)
{
	OutputMsg(rmNormal, ("Save all Actor Data"));
	SaveData(false, sql, true);
}

void DBDataCache::SetNextSaveTime(int actorid, int time)
{
	int64_t nCurrTick = _getTickCount();

	OutputMsg(rmNormal, ("SetNextSaveTime actorid=%d"), actorid);

	std::map<ActorId, ActorCacheData>::iterator iter = m_sActorCacheDataTbl.find(actorid);
	if (iter == m_sActorCacheDataTbl.end()) return;
	
	ActorCacheData& data = iter->second;
	
	data.SetNextSaveTick(nCurrTick + wrand(time) * 1000);
}

bool DBDataCache::SaveData(bool bCheckCD, SQLConnection& sql, bool all/* = false*/)
{
	int64_t nCurrTick = 0;

	if (bCheckCD)
		nCurrTick = _getTickCount();

	std::map<ActorId, ActorCacheData>::iterator iter		= m_sActorCacheDataTbl.begin();
	std::map<ActorId, ActorCacheData>::iterator iter_end	= m_sActorCacheDataTbl.end();

	int64_t start_t = _getTickCount();
	for (; iter != iter_end; ++iter)
	{
		ActorCacheData& data = iter->second;
		SaveActorDataImpl(data, bCheckCD, nCurrTick, sql);

		if (all)
		{
			data.m_valid = true; // GameWorld连接断开后所有数据设置为有效的
		}
		else if (_getTickCount() - start_t >= s_nSaveOnceTime)
		{
			OutputMsg(rmError, "DBDataCache::SaveData. timeout:%d",_getTickCount() - start_t);
			if (_getTickCount() - start_t >= s_nSaveOnceTime * 5)
				break;
		}
	}

	return true;
}

bool DBDataCache::SaveActorDataImmediately(ActorId nActorId, SQLConnection& sql)
{
	std::map<ActorId, ActorCacheData>::iterator iter = m_sActorCacheDataTbl.find(nActorId);

	if (iter == m_sActorCacheDataTbl.end())
		return true;

	OutputMsg(rmNormal, ("SaveActorDataImmediately actorid=%d"), nActorId);
	ActorCacheData& data = iter->second;
	return SaveActorDataImpl(data, false, 0, sql);
}

void DBDataCache::RemoveExpireCache()
{
	std::map<ActorId, ActorCacheData>::iterator iter		= m_sActorCacheDataTbl.begin();
	std::map<ActorId, ActorCacheData>::iterator iter_end	= m_sActorCacheDataTbl.end();

	for (; iter != iter_end;)
	{
		if (iter->second.IsExpired())
		{
			//OutputMsg(rmNormal, ("Remove actor[%d] cache data"), iter->first);
			m_sActorCacheDataTbl.erase(iter++);
		}
		else
			++iter;
	}
}

bool DBDataCache::SaveActorDataImpl(ActorCacheData& data, bool bCheckCD, int64_t nCurrTick, SQLConnection &sql)
{
	if (!data.IsDirty())
	{
		if (data.m_nNextSaveTick + ActorCacheData::s_nExpireTime <= nCurrTick)
		{
			data.SetExpired(true);

			if (!m_bHasExpireCache)
				m_bHasExpireCache = true;
		}

		return true;
	}

	if (!bCheckCD || (bCheckCD && data.CheckAndSet(nCurrTick)))
	{
		int nCount = __min(ArrayCount(s_aActorCacheHandler), DBCacheType_Max);
		OutputMsg(rmNormal, ("Save Actor[actorid=%d] Data"), data.m_nActorId);
		bool dirty = false;
		for (int i = 0; i < nCount; i++) {
			if (data.m_sActorCacheData[i].getAvaliableLength() <= 0) {
				//OutputMsg(rmNormal, ("ActorCacheData avaliable length error:%d,%d"), data.m_nActorId, i);
				continue;
			}

			int64_t start_t = _getTickCount();
#ifdef DB_TYPEDIRTY
			bool bRet = true;
			if (data.IsTypeDataDirty((DBCacheType)i)) {
				if (this->s_aActorCacheHandler[i]) {
					size_t pos = data.m_sActorCacheData[i].getPosition();
					if ((this->s_aActorCacheHandler[i])(data.m_sActorCacheData[i], sql)) {
						bRet = true;
						data.SetTypeDataDirty((DBCacheType)i, false);
						OutputMsg(rmTip, "SaveActorDataImpl:%d,%d,%d", data.m_nActorId, i, (int)(_getTickCount() - start_t));
					} else {
						dirty = true;//这个包保存不成功,肯定是坏的包
					}
					data.m_sActorCacheData[i].setPosition(pos);
				} else {
					OutputMsg(rmError, ("SaveData Failed(Actorid=%d, cacheType=%d"), data.m_nActorId, i);
				}
			}
#else
		bool bRet =  (this->*s_aActorCacheHandler[i])(data.m_sActorCacheData[i], sql);
#endif
			if (bRet) {
				//去警告
			}
		}
		OutputMsg(rmNormal, ("Save Actor[actorid=%d] Data finished"), data.m_nActorId);
		data.SetDirty(dirty);
	}

	return true;
}

bool DBDataCache::ClearCacheData(SQLConnection& sql, ActorId nActorId, DBCacheType cdType, bool toSave)
{
	if (nActorId == 0)
	{
		OutputMsg(rmError, " nActorId <= 0 nActorId %d cdType %d", nActorId, (int)cdType );
		return false;
	}

	ActorCacheData* pData = NULL;
	std::map<ActorId, ActorCacheData>::iterator iter = m_sActorCacheDataTbl.find(nActorId);

	if (iter == m_sActorCacheDataTbl.end())
	{
		return false;
	}
	else
	{
		pData = &(iter->second);
	}

	if( DBCacheType_Max <= cdType || cdType < 0)
	{
		OutputMsg(rmError, " enCT_Max <= cdType || cdType < 0 nActorId %d cdType %d", nActorId, (int)cdType );
		return false;
	}

	if (toSave && pData->readable_[cdType])
	{
		(this->s_aActorCacheHandler[cdType])(pData->m_sActorCacheData[cdType], sql);
	}

	pData->SetDirty(false);
	pData->readable_[cdType] = false;
#ifdef DB_TYPEDIRTY
	pData->SetTypeDataDirty((DBCacheType)cdType, false);
#endif
	DataPacket& cachePacket = pData->m_sActorCacheData[cdType];
	cachePacket.setPosition(0);
	cachePacket.setLength(0);

	return true;
}

bool DBDataCache::ClearCacheData(SQLConnection& sql, ActorId nActorId, bool toSave)
{
	if (nActorId == 0)
	{
		OutputMsg(rmError, " nActorId <= 0 nActorId %d", nActorId);
		return false;
	}
	for(int i = 0; i < DBCacheType_Max; i++)
	{
		bool ret = ClearCacheData(sql,nActorId, (DBCacheType)i, toSave);
		if (!ret)
		{
			OutputMsg(rmError,"clear cache failed aid %d type %d", nActorId, i);
		}
	}
	return true;
}

bool DBDataCache::ClearCacheData(SQLConnection& sql, DBCacheType cdType, bool toSave)
{
	if( DBCacheType_Max <= cdType || cdType < 0)
	{
		OutputMsg(rmError, " enCT_Max <= cdType || cdType < 0!! cdType %d", (int)cdType );
		return false;
	}

	std::map<ActorId, ActorCacheData>::iterator iter		= m_sActorCacheDataTbl.begin();
	std::map<ActorId, ActorCacheData>::iterator iter_end	= m_sActorCacheDataTbl.end();

	for (; iter != iter_end; iter++)
	{
		ActorId aid = iter->first;
		bool ret = ClearCacheData(sql,aid, cdType, toSave);
		if (!ret)
		{
			OutputMsg(rmError, "ClearCacheData(sql,aid, toSave) wrong, aid: %d, type %d!", aid, cdType);
		}

	}
	return true;
}

bool DBDataCache::ClearCacheData(SQLConnection& sql, bool toSave)
{
	std::map<ActorId, ActorCacheData>::iterator iter		= m_sActorCacheDataTbl.begin();
	std::map<ActorId, ActorCacheData>::iterator iter_end	= m_sActorCacheDataTbl.end();

	for (; iter != iter_end; iter++)
	{
		ActorId aid = iter->first;
		bool ret = ClearCacheData(sql,aid, toSave);
		if (!ret)
		{
			OutputMsg(rmError, "ClearCacheData(sql,aid, toSave) wrong, aid: %d", aid);
		}

	}
	return true;
}

bool DBDataCache::ClearCacheData(SQLConnection& sql, DataPacketReader& packet)
{
	ActorId aid = 0;
	packet >> aid;
	int cdType = 0;
	packet >> cdType;
	int isSave = 0;
	packet >> isSave;
	bool toSave = isSave == 0 ? true:false;
	//int timeNotCache = 0; //不使用缓存的时间
	//packet >> timeNotCache;


	if (aid > 0 && cdType >= 0)
	{
		ClearCacheData(sql, aid, (DBCacheType)cdType, toSave);
	}
	else if (aid > 0 && cdType < 0)
	{
		ClearCacheData(sql, aid, toSave);
	}
	else if( aid < 0 && cdType >= 0)  //对所有玩家清除缓存
	{
		ClearCacheData(sql, (DBCacheType)cdType, toSave);
	}
	else if( aid < 0 && cdType < 0)  //对所有玩家清除缓存
	{
		ClearCacheData(sql, toSave);
	}
	else
	{
		OutputMsg(rmError, "read clear cache error, actorid = 0");
	}

	return true;
}

void DBDataCache::SetSaveOnceTime(DataPacketReader& packet)
{
	int64_t sTime = 0;
	packet >> sTime;
	if (sTime < 0)
		return ;
	s_nSaveOnceTime = sTime;

	OutputMsg(rmTip, "SetSaveOnceTime : %d", (int)sTime);
}

void DBDataCache::RunOne(SQLConnection &sql)
{
	int64_t nCurrTick = _getTickCount();

	if (nCurrTick >= m_nNextCheckTime)
	{
		m_nNextCheckTime += s_nCheckInterval;
		SaveData(true, sql);
	}

	if (m_bHasExpireCache)
	{
		RemoveExpireCache();
		m_bHasExpireCache = false;
	}
	CDBPvmCache::instance()->RunOne(nCurrTick, sql);
}


DataPacket* DBDataCache::GetReadableData(ActorId aid, int type, bool* valid)
{
	if (type < 0 || type >= DBCacheType_Max) return NULL;

	ActorCacheData* pData = NULL;
	std::map<ActorId, ActorCacheData>::iterator iter = m_sActorCacheDataTbl.find(aid);

	if (iter == m_sActorCacheDataTbl.end())
	{
		return NULL;
	}
	else 
	{
		pData = &(iter->second);
		if (pData && pData->readable_[type])
		{
			if (valid)
			{
				*valid = pData->m_valid;
			}
			DataPacket& cachePacket = pData->m_sActorCacheData[type];
			return &cachePacket;
		}
	}
	return NULL;
}

ActorBasicData* DBDataCache::GetActorBasicData(ActorId aid)
{
	DataPacket *pack = this->GetReadableData(aid, enCT_ActorBasicData);
	if (pack != NULL)
	{
		if (pack->getLength() >= sizeof(ActorBasicData) + sizeof(ActorId))
		{
			ActorBasicData* actorData = (ActorBasicData*)pack->getPositionPtr(sizeof(ActorId));
			return actorData;
		}
	}
	return NULL;
}


DataPacket* DBDataCache::UpdateCache( ActorId nActorId, int cdType, void* buf, size_t size, bool dirty )
{
	ActorCacheData* pData = NULL;
	std::map<ActorId, ActorCacheData>::iterator iter = m_sActorCacheDataTbl.find(nActorId);

	if (iter == m_sActorCacheDataTbl.end())
	{
		ActorCacheData tmp_data;
		std::pair<std::map<ActorId, ActorCacheData>::iterator, bool> pr;
		pr = m_sActorCacheDataTbl.insert(std::make_pair(nActorId, tmp_data));

		if (!pr.second)
		{
			OutputMsg(rmError, ("alloc Actor[%d] CacheData Failed"), nActorId);
			return NULL;
		}

		pData = &(pr.first->second);
		pData->Init(&m_allocator, nActorId);
		pData->PostponeNextSaveTick(_getTickCount());
	}
	else
	{
		pData = &(iter->second);
	}

	pData->SetDirty(dirty);
	pData->readable_[cdType] = true;
#ifdef DB_TYPEDIRTY
	pData->SetTypeDataDirty((DBCacheType)cdType, dirty);
#endif
	DataPacket& cachePacket = pData->m_sActorCacheData[cdType];
	cachePacket.setPosition(0);
	if (buf && size > 0)
	{
		cachePacket.setLength(size);
		cachePacket.writeBuf(buf, size);
		cachePacket.setPosition(0);
	}

	return &cachePacket;
}

void DBDataCache::SetValidFlag(ActorId aid, bool flag)
{
	ActorCacheData* pData = NULL;
	std::map<ActorId, ActorCacheData>::iterator iter = m_sActorCacheDataTbl.find(aid);

	if (iter == m_sActorCacheDataTbl.end())
	{
		OutputMsg(rmError, "DATAVALID,NULL,%d", aid);
	}
	else
	{
		pData = &(iter->second);
		if (pData)
		{
			pData->m_valid = flag;
		}
	}
}
