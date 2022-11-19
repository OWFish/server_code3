#include "StdAfx.h"
#include <string>
using namespace InterSrvComm::DbServerProto;


//这里放的是玩家基本信息表的存放和读取
void DBSession::QueryActorFromDB(DataPacketReader& inPacket)
{
	ActorId aid;
	bool isImage;
	inPacket >> aid;
	inPacket >> isImage;
	QueryActorFromDB(aid, isImage);
}

//从数据库里装载玩家
void DBSession::QueryActorFromDB(ActorId aid, bool isImage)
{
	int64_t start_t = _getTickCount();
	OutputMsg(rmNormal, "QueryActorFromDB start:%d,%lld", aid, (long long int)start_t);

	client_mgr_->LockCache();

	bool valid = true;
	DataPacket* pack = client_mgr_->GetCache()->GetReadableData(aid, DBCacheType_ActorBasic, &valid);

	if (pack != NULL)
	{
		if (!valid && client_mgr_->s_checkValid && !isImage)
		{
			client_mgr_->UnLockCache();
			OutputMsg(rmTip, "DATAVALID,FLAG,%d", aid);
			if (!HasWaitFor(aid))
			{
				AddWaitFor(aid);
			}
			return;
		}
		// 直接在缓存里读入这个数据
		size_t pos = pack->getPosition();
		pack->setPosition(sizeof(ActorId));

		DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcLoad));
		retPack << aid << (uint8_t)reSucc;
		retPack.writeBuf(pack->getOffsetPtr(), pack->getAvaliableBufLen());
		flushProtoPacket(retPack);

		pack->setPosition(pos);

		client_mgr_->UnLockCache();

#ifdef _MSC_VER
		OutputMsg(rmNormal, "QueryActorFromCache end:%d,%I64d", aid, _getTickCount() - start_t);
#else
		OutputMsg(rmNormal, "QueryActorFromCache end:%d,%lld", aid, (long long int)(_getTickCount() - start_t));
#endif

		QueryActorSubSystemData(aid);
		return;
	}

	client_mgr_->UnLockCache();

	ActorBasicData actor_data;
	memset(&actor_data, 0, sizeof(ActorBasicData));
	actor_data.actor_id = aid;
	DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcLoad));
	retPack << aid;
	bool result = false;

	//数据库连接是否就绪
	if (!sql_->Connected())
	{
		retPack << (char)reDbErr;
		flushProtoPacket(retPack);
		return;
	}

	int err = sql_->Query(sql_loadactorbasic, aid);

	if (err)
	{
		OutputMsg(rmError, ("%s load actor data fail %d"), __FUNCTION__, aid);
		retPack << (char)reDbErr;
		flushProtoPacket(retPack);
		return;
	}

	MYSQL_ROW pRow = sql_->CurrentRow();

	if (!pRow)
	{
		retPack << (char)reNoActor;
		OutputMsg(rmError, "no this actor data!!");
		sql_->ResetQuery();
		flushProtoPacket(retPack);
		return;
	}

	//uint16_t wValue = 0;

	retPack << (char)reSucc;

	// ActorBasicData在gameworld上也要加载，所以把加载流程封装，避免不同步
	ReadActorBasicData(actor_data, pRow, sql_->GetFieldsLength());

	retPack << actor_data;
	result = true;
#undef GetDBVal

	sql_->ResetQuery();
	flushProtoPacket(retPack);

	OutputMsg(rmNormal, "QueryActorFromDB end:%d,%lld", aid, (long long int)(_getTickCount() - start_t));

	if (result)
	{
		QueryActorSubSystemData(aid); //装载玩家各子系统的ID
	}
}

void OutputTimeCost(const char* desc, time_t& time)
{
	time_t now_t = _getTickCount();
	OutputMsg(rmWarning, "%s:%lld", desc, (now_t - time));
	time = now_t;
}

void DBSession::QueryActorSubSystemData(ActorId nActorID)
{
	updateOnLogin(nActorID);

	int64_t now_t = _getTickCount();
	OutputMsg(rmNormal, "QueryActorSubSystemData start:%d,%lld", nActorID, now_t);

	QueryRoleData(nActorID);
	QueryBagData(nActorID);
	QueryMailData(nActorID);
	QueryActorCacheData(nActorID);

	//---------------------------
	//actorvariable 加载，保留旧代码方式, 只执行一遍sql
	Vector<VariableDataFlag> fieldList;
	VariableDataFlag flag;
	fieldList.clear();

	if (!QueryActorScriptData(nActorID))
	{
		flag.fieldName_ = "variable";	//todo这个表清理不用字段
		flag.protoId_ = dcLoadVar;
		flag.cache_type_ = DBCacheType_ScriptData;
		fieldList.add(flag);
	}

	if (!QueryActorCsScriptData(nActorID)) {
		flag.fieldName_ = "cs_variable";	//todo这个表清理不用字段
		flag.protoId_ = dcLoadCsWarVar;
		flag.cache_type_ = DBCacheType_CsScriptData;
		fieldList.add(flag);
	}

	if (!QueryStoreData(nActorID))
	{
		flag.fieldName_ = "storedata";	//todo这个表清理不用字段
		flag.protoId_ = dcLoadStore;
		flag.cache_type_ = DBCacheType_Store;
		fieldList.add(flag);
	}

	if (!QueryTogHitEquipData(nActorID))
	{
		flag.fieldName_ = "together_hit_equip";	//todo这个表清理不用字段
		flag.protoId_ = dcLoadTogHitEquip;
		flag.cache_type_ = DBCacheType_TogHitEquip;
		fieldList.add(flag);
	}

	if (fieldList.count() > 0)
		QueryActorVariableList(nActorID, fieldList);
	OutputTimeCost("Query AllVariables.", now_t);
	//----------------------------

	OutputTimeCost("Query RoleSystemData.", now_t);

	OutputMsg(rmNormal, "QueryActorSubSystemData end:%d,%lld", nActorID, now_t);
}

void DBSession::QueryActorCacheData(ActorId actorId) {
	client_mgr_->LockCache();
	auto *pack = client_mgr_->GetCache()->GetReadableData(actorId, DBCacheType_ActorCache);
	if (pack != nullptr) {
		size_t pos = pack->getPosition();
		pack->setPosition(sizeof(ActorId));

		DataPacket &retPack = allocProtoPacket(MAKEINT16(siActor, dcActorCacheLoad));
		retPack << actorId << (uint8_t)reSucc;

		retPack.writeBuf(pack->getOffsetPtr(), pack->getAvaliableLength());
		flushProtoPacket(retPack);

		pack->setPosition(pos);

		client_mgr_->UnLockCache();
		return;
	}
	client_mgr_->UnLockCache();

	DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcActorCacheLoad));
	retPack << actorId << (uint8_t)reSucc;
	size_t headlen = retPack.getPosition();
	ActorCsData actorData;
	retPack << actorData;
	flushProtoPacket(retPack);

	{
		client_mgr_->LockCache();
		DataPacket *pack = client_mgr_->GetCache()->UpdateCache(actorId, DBCacheType_ActorCache, NULL, 0, false);
		pack->setPosition(0);
		(*pack) << actorId;
		pack->writeBuf(retPack.getPositionPtr(0) + headlen, retPack.getLength() - headlen);
		pack->setPosition(0);
		client_mgr_->UnLockCache();
	}
}

bool DBSession::SaveActorCacheToDB(DataPacketReader& inPacket, SQLConnection& sql) {
	//占位置用的
	return true;
}


//将玩家保存到数据库里去
bool DBSession::SaveActorToDB(DataPacketReader& inPacket, SQLConnection& sql)
{
	if (inPacket.getAvaliableLength() != sizeof(int)+sizeof(ActorBasicData))
	{
		OutputMsg(rmError, ("%s Data size error"), __FUNCTION__);
		return false;
	}

	ActorId aid;
	ActorBasicData data;
	inPacket >> aid >> data;

	//数据库连接是否就绪
	if (sql.Connected())
	{
		sprintf(huge_buf_s, "update actors set ");
		char fieldbuf[128];
		FirstSetInt("level", data.level);
		SetInt("exp", data.exp);
		SetInt("job", data.job);
		SetInt("sex", data.sex);
		SetLInt("fbuid", data.fb_uid);
		SetInt("sceneid", data.fb_scene_id);
		SetInt("lastonlinetime", data.last_online_time);
		SetInt("totalonline", data.total_online);
		SetInt("dailyonline", data.daily_online);
		SetInt("baggridcount", data.bag_grid);
		SetLInt("gold", data.gold);
		SetLInt("yuanbao", data.yuanbao);
		SetLInt("totalpower", data.total_power);
		SetLInt("rankpower", data.rank_power);
		SetInt("recharge", data.recharge);
		SetInt("paid", data.paid);
		SetInt("chapterlevel", data.chapter_level);
		SetInt("vip_level", data.vip_level);
		SetInt("essence", data.essence);
		SetInt("zhuansheng_lv", data.zhuansheng_lv);
		SetInt("zhuansheng_exp", data.zhuansheng_exp);
		SetInt("monthcard", data.monthcard);

		SetInt("tianti_level", data.tianti_level);
		SetInt("tianti_dan", data.tianti_dan);
		SetInt("tianti_win_count", data.tianti_win_count);
		SetInt("tianti_week_refres", data.tianti_week_refres);
		SetInt("guildid", data.guild_id_);


		SetLInt("total_wing_power", data.total_wing_power);
		SetLInt("warrior_power", data.warrior_power);
		SetLInt("mage_power", data.mage_power);
		SetLInt("taoistpriest_power", data.taoistpriest_power);
		SetInt("train_level", data.train_level);
		SetInt("train_exp", data.train_exp);
		SetInt("total_stone_level", data.total_stone_level);
		SetInt("zhan_ling_star", data.zhan_ling_star);
		SetInt("zhan_ling_stage", data.zhan_ling_stage);
		SetInt("total_loongsoul_level", data.total_loongsoul_level);
		SetLInt("feats", data.feats);
		SetData("ex_ring_lv",data.ex_ring_lv, sizeof(data.ex_ring_lv));
		SetLInt("shatter", data.shatter);
		SetLInt("spcshatter", data.spcshatter);
		SetInt("knighthood_lv", data.knighthood_lv);
		SetLInt("togeatter", data.togeatter);
		SetInt("total_wing_lv", data.total_wing_lv);
		SetLInt("total_tujian_power", data.total_tujian_power);
		SetLInt("total_equip_power", data.total_equip_power);
		SetLInt("togeatterhigh", data.togeatterhigh);
		SetInt("prestige_exp", data.prestige_exp);
		SetInt("total_zhuling_level", data.total_zhuling_level);
		SetInt("reincarnate_lv", data.reincarnate_lv);
		SetInt("reincarnate_exp", data.reincarnate_exp);
		SetString("guild_name", data.guild_name_);
		SetInt("fieldchapterlevel", data.field_chapter_level);
		SetInt("fieldchapterprogress", data.field_chapter_progress);
		SetInt("field_pk_mode", data.field_pk_mode);
		{
			char buf[1000];
			sprintf(buf, "FROM_UNIXTIME( %s, ", std::to_string(time(nullptr)).c_str());
			strcat(buf,"'%Y-%m-%d %H:%i:%s' )");
		
			strcat(huge_buf_s, ",updatetime = ");
			strcat(huge_buf_s, buf);
		}
		
		sprintf(fieldbuf, "where `actorid`=%d limit 1", data.actor_id);
		strcat(huge_buf_s, fieldbuf);

		int err = sql.RealExec(huge_buf_s, strlen(huge_buf_s));
		if (!err) {
			sql.ResetQuery();
			return true;
		}
	}
	return false;
#undef GI
}

