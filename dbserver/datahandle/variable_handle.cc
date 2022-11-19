#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

using namespace InterSrvComm::DbServerProto;


bool DBSession::QueryActorScriptData(ActorId nActorID) {
	//if (!QueryActorVariableDataFromCache(nActorID, DBCacheType_ScriptData, dcLoadVar))
	//	QueryActorVariableData(nActorID, "variable", dcLoadVar);
	return QueryActorVariableDataFromCache(nActorID, DBCacheType_ScriptData, dcLoadVar);
}

bool DBSession::SaveScriptDataToDB(DataPacketReader& inPacket, SQLConnection& sql) {
	return SaveActorVariableData(inPacket, "variable", sql, dcSaveVar);
}

bool DBSession::QueryActorCsScriptData(ActorId nActorID) {
	//OutputMsg(rmTip, "load actor cross LUA var actorid;%d", nActorID);
	return QueryActorVariableDataFromCache(nActorID, DBCacheType_CsScriptData, dcLoadCsWarVar);
}

bool DBSession::SaveCsScriptDataToDB(DataPacketReader& inPacket, SQLConnection& sql) {
	return SaveActorVariableData(inPacket, "cs_variable", sql, dcSaveCsWarVar);
}

//bool DBSession::QueryCrossScriptData(ActorId nActorID)
//{
//	//if (!QueryActorVariableDataFromCache(nActorID, enCT_CrossData, dcLoadCrossVar))
//	//	QueryActorVariableData(nActorID, "crossvariable", dcLoadCrossVar);
//	return QueryActorVariableDataFromCache(nActorID, enCT_CrossScriptData, dcLoadCrossVar);
//}
//
//void DBSession::SaveCrossScriptData(DataPacketReader& inPacket, SQLConnection& sql)
//{
//	SaveActorVariableData(inPacket, "crossvariable", sql, dcSaveCrossVar);
//}

bool DBSession::QueryStoreData(ActorId actorId) {
	return QueryActorVariableDataFromCache(actorId, DBCacheType_Store, dcLoadStore);
}

bool DBSession::QueryTogHitEquipData(ActorId actorId) {
	return QueryActorVariableDataFromCache(actorId, DBCacheType_TogHitEquip, dcLoadTogHitEquip);
}

bool DBSession::SaveStoreData(DataPacketReader& packet, SQLConnection& sql) {
	return SaveActorVariableData(packet, "storedata", sql, dcSaveStore);
}

bool DBSession::SaveTogHitEquipData(DataPacketReader& packet, SQLConnection& sql) {
	return SaveActorVariableData(packet, "together_hit_equip", sql, dcSaveTogHitEquip);
}
