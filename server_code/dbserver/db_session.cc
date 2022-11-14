#include "StdAfx.h"

using namespace InterSrvComm::DbServerProto;


const char* lua_fn = "./data/dbserver.txt";

void OnBlock(void* db)
{
	if (db)
	{
		//DBSession* client = (DBSession*)db;
		//client->GetSQL()->Disconnect();
		//char buf[256];
		//SNPRINTFA(buf, sizeof(buf) - 1, "serverid:%d: dbserver OnBlock!", client->getClientServerIndex());
		printf("dbserver OnBlock!\n");
	}
}

char* DBSession::huge_buf_s = (char*)malloc(sizeof(char) * HUNGSIZE);

DBSession::DBSession(DBSessionMgr* mgr, SQLConnection* sql, SOCKET s, sockaddr_in* addr)
	: Inherited("DBSession"), allocator_("DBclient_allocator"), sentToBIDay_(0), battleflag_(0), netAlloc_("netAlloc")
{
	SetClientSocket(s, addr);
	target_sid_ = 0;
	srv_name_[0] = 0;
	client_mgr_ = mgr;
	sql_ = sql;
	close_t_ = 0;
	huge_buf_ = (char*)allocator_.AllocBuffer(HUNGSIZE);
//	cache_.SetDBClient(this);
	check_gm_t_ = 0;
	gc_t_ = 0;
	report_t_ = 0;
	wait_for_list_.clear();
	//vsp_def_.LoadDefinitions("./data/vspdef.txt");
	//script_.SetVspDef(&vsp_def_);
	//script_.LoadScript(lua_fn);
	//reload_script_ = false;

	watch_id_ = wrand(1000000);
	WatchThread* watch = client_mgr_->GetWatch();

	if (watch) watch->AddWatch(watch_id_, 120000, &OnBlock, this);

	executor_ = new DBExecutor(this);
}

DBSession::~DBSession()
{
	allocator_.FreeBuffer(huge_buf_);

	for (int i = 0; i < netMsgList_.count(); i++)
	{
		DataPacket* dp = netMsgList_[i];
		delete dp;
	}

	netMsgList_.clear();

	WatchThread* watch = client_mgr_->GetWatch();

	if (watch) watch->RemoveWatch(watch_id_);

	delete executor_;
}

void DBSession::OnDisconnected()
{
	close_t_ = NOW_T;
	OutputMsg(rmWarning, "client(%s:%d) disconnect", GetRemoteHost(), GetRemotePort());
}

void DBSession::OnRecvSysMsg(UINT, size_t, size_t, size_t, size_t)
{

}

void DBSession::OnTxApiProcess()
{
	time_t now_t = NOW_T;

	if (now_t > check_fee_t_)
	{
		// 每秒检查一下
		check_fee_t_ = now_t + 1;

		if (!sql_->Connect())
		{
			return;
		}

		int err = sql_->Query("call loadfee(%d);", getClientServerIndex());

		if (!err)
		{
			fee_list_.clear();
			MYSQL_ROW row = sql_->CurrentRow();

			while (row)
			{
				FeeData data;
				_STRNCPY_A(data.openid_, row[0] ? row[0] : "");
				data.itemId_ = StrToInt(row[1]);
				data.num_ = StrToInt(row[2]);
				data.id_ = StrToInt(row[3]);
				data.actor_id_ = StrToInt(row[4]);
				_STRNCPY_A(data.order_num_, row[5] ? row[5] : "");

				fee_list_.add(data);

				row = sql_->NextRow();
			}

			sql_->ResetQuery();

			//OutputMsg(rmError, "recv %d fee data", fee_list_.count());

			for (int i = 0; i < fee_list_.count(); ++i)
			{
				FeeData& data = fee_list_[i];
				err = sql_->Exec("call delfeecallback(%d);", data.id_);

				if (!err)
				{
					sql_->ResetQuery();

					DataPacket& out = allocProtoPacket(MAKEINT16(siTxApi, sFeeCallBack));
					out.writeString(data.openid_);
					out << (int)data.itemId_;
					out << (int)data.num_;
					out << (int)data.actor_id_;
					out.writeString(data.order_num_);
					flushProtoPacket(out);

					OutputMsg(rmError, "send fee data:%s, %d, %d", data.openid_, data.itemId_, data.num_, data.actor_id_);
				}
				else
				{
					// 这里设置成了true，那这里就不会再扣费了，这样是避免删除不了，而不断给用户增加元宝，这是严重问题
					//del_fee_err_ = true;
					OutputMsg(rmError, "!!!!!!!! delete fee msg fail!!!!!!!!!");
				}
			}

			fee_list_.clear();

			canOutputMsg_ = true;
		}
		else
		{
			if (canOutputMsg_)
			{
				OutputMsg(rmError, "query fee error:%d", getClientServerIndex());
				canOutputMsg_ = false;	// 避免不断输出同样的错误
			}
		}

		// 每秒检查一下
		check_fee_t_ = now_t + 1;

		err = sql_->Query("call loadtxapimsg(%d);", getClientServerIndex());

		if (!err)
		{
			tx_list_.clear();
			MYSQL_ROW row = sql_->CurrentRow();

			while (row)
			{
				TxApiMsgData data;
				_STRNCPY_A(data.openid_, row[0] ? row[0] : "");
				data.type_ = StrToInt(row[1]);
				_STRNCPY_A(data.para1_, row[2] ? row[2] : "");
				_STRNCPY_A(data.para2_, row[3] ? row[3] : "");
				_STRNCPY_A(data.para3_, row[4] ? row[4] : "");
				_STRNCPY_A(data.para4_, row[5] ? row[5] : "");
				_STRNCPY_A(data.para5_, row[6] ? row[6] : "");
				data.id_ = StrToInt(row[7]);
				tx_list_.add(data);

				row = sql_->NextRow();
			}

			sql_->ResetQuery();

			//OutputMsg(rmError, "recv %d fee data", fee_list_.count());

			for (int i = 0; i < tx_list_.count(); ++i)
			{
				TxApiMsgData& data = tx_list_[i];
				err = sql_->Exec("call deltxapimsg(%d);", data.id_);

				if (!err)
				{
					sql_->ResetQuery();

					DataPacket& out = allocProtoPacket(MAKEINT16(siTxApi, sTxApiMsg));
					out.writeString(data.openid_);
					out << (int)data.type_;
					out.writeString(data.para1_);
					out.writeString(data.para2_);
					out.writeString(data.para3_);
					out.writeString(data.para4_);
					out.writeString(data.para5_);
					flushProtoPacket(out);
				}
				else
				{
					// 这里设置成了true，那这里就不会再扣费了，这样是避免删除不了，而不断给用户增加元宝，这是严重问题
					//del_fee_err_ = true;
					OutputMsg(rmError, "!!!!!!!! delete tx api msg fail!!!!!!!!!");
				}
			}

			tx_list_.clear();

			canOutputMsg_ = true;
		}
		else
		{
			if (canOutputMsg_)
			{
				OutputMsg(rmError, "query fee error:%d", getClientServerIndex());
				canOutputMsg_ = false;	// 避免不断输出同样的错误
			}
		}
	}
}

void DBSession::OnRun()
{
	/*if (reload_script_)
	{
		script_.LoadScript(lua_fn);
		reload_script_ = false;
	}*/

	int64_t start_t = _getTickCount();

	for (; netMsgList_.count() > 0;)
	{
		DataPacket* dp = netMsgList_[0];
		netMsgList_.remove(0);

		if (!dp) continue;

		dp->setPosition(0);
		uint16_t cmd = 0;
		(*dp) >> cmd;
		processNetMsg(cmd, *dp);
		delete dp;

		// 每次限定执行时间在32ms内，超过时间则等下次执行
		// 这么做的目的是为了当数据包过多的时候，可以先把完成执行的结果发送给gameworld
		// 从而减少因为数据库性能而造成卡的问题
		// zac:需要更新到外网才看到效果，留意新服是否有卡登陆的问题，或者是否有缓解
		int64_t end_t = _getTickCount();

		if ((end_t - start_t) >= 128) break;
	}
	int64_t end_t = _getTickCount();
	if ((end_t - start_t) >= 128)
		OutputMsg(rmWarning, "db session on netmsg %d ms", end_t - start_t);

	// 定期检查gm命令表
	time_t now_t = NOW_T;

	if (now_t > check_gm_t_)
	{
		// 每秒检查一下
		check_gm_t_ = now_t + 3;
		//OutputMsg(rmError, "=======test:battleflag:%d,serverid=%d", battleflag_, getClientServerIndex());

		if (!IsBattleSrv())
		{
			int err = sql_->Query(loadgmcmd, getClientServerIndex());

			if (!err)
			{
				gm_list_.clear();
				MYSQL_ROW row = sql_->CurrentRow();

				while (row)
				{
					GMData data;
					data.id_ = StrToInt(row[0]);
					_STRNCPY_A(data.cmd_, row[1] ? row[1] : "");
					_STRNCPY_A(data.param1_, row[2] ? row[2] : "");
					_STRNCPY_A(data.param2_, row[3] ? row[3] : "");
					_STRNCPY_A(data.param3_, row[4] ? row[4] : "");
					_STRNCPY_A(data.param4_, row[5] ? row[5] : "");
					_STRNCPY_A(data.param5_, row[6] ? row[6] : "");
					data.cmdid_ = StrToInt(row[7] ? row[7] : "0");
					gm_list_.add(data);

					row = sql_->NextRow();
				}

				sql_->ResetQuery();

				//OutputMsg(rmError, "recv %d fee data", gm_list_.count());

				for (int i = 0; i < gm_list_.count(); ++i)
				{
					GMData& data = gm_list_[i];
					err = sql_->Exec(delgmcmd, data.id_);

					if (!err)
					{
						sql_->ResetQuery();

						DataPacket& out = allocProtoPacket(MAKEINT16(siGlobal, dcGmCmd));
						out.writeString(data.cmd_);
						out << int(data.cmdid_);
						out.writeString(data.param1_);
						out.writeString(data.param2_);
						out.writeString(data.param3_);
						out.writeString(data.param4_);
						out.writeString(data.param5_);
						flushProtoPacket(out);

						OutputMsg(rmTip, "recv gmcmd: %s, 1:%s, 2:%s, 3:%s, 4:%s, 5:%s",
							data.cmd_, data.param1_, data.param2_, data.param3_, data.param4_, data.param5_);
					}
					else
					{
						OutputMsg(rmError, "!!!!!!!! delete gm msg fail!!!!!!!!!");
					}
				}

				gm_list_.clear();
			}
			else
			{
				OutputMsg(rmError, "query gm cmd error:%d", getClientServerIndex());
			}
		}

	}

	if (!IsBattleSrv())
	{
		OnTxApiProcess();
	}

	if (now_t > gc_t_)
	{
		gc_t_ = now_t + 1800;
		GC();
	}

	if (abs(now_t - report_t_) > 10)
	{
		report_t_ = now_t;// +30;
		WatchThread* watch = client_mgr_->GetWatch();

		if (watch) watch->Report(watch_id_);
		OutputMsg(rmNormal, "db_session report");
	}
}

void DBSession::OnRecv(const uint16_t cmd, char* buf, int size)
{
	DataPacket* dp = new DataPacket(&netAlloc_);
	(*dp) << (uint16_t)cmd;
	dp->writeBuf(buf, size);
	netMsgList_.add(dp);
}

bool DBSession::OnValidateRegData(const SrvDef::PSERVER_REGDATA regData)
{
	return (regData->GameType == SERVER_REGDATA::GT_ID &&
	        (regData->ServerType == T_GameServer));
}

//void DBSession::ExecuInitDb()
//{
//	if (sql_->Connected())
//	{
//		if (!sql_->Exec(szSQL_InitDB, getClientServerIndex()))
//		{
//			sql_->ResetQuery();
//		}
//	}
//}

//void DBSession::OnDefaultSysRecv(int cmd, DataPacketReader&)
//{
//	switch (cmd)
//	{
//	case dcInitDB:
//		{
//			ExecuInitDb();
//			break;
//		}
//	}
//}

inline DBCacheType GetCacheType(int bag_type)
{
	switch (bag_type)
	{
	case BagType_Item:
		return DBCacheType_ItemBag;
		break;
	case BagType_Equip:
		return DBCacheType_EquipBag;
		break;
	case BagType_Depot:
		return DBCacheType_Depot;
		break;
	}
	return DBCacheType_Undefined;
}

inline DBCacheType GetItemCacheType(DataPacketReader& reader)
{
	size_t pos = reader.getPosition();
	reader.adjustOffset(sizeof(ActorId));
	int bag_type;
	reader >> bag_type;
	reader.setPosition(pos);
	return GetCacheType(bag_type);
}


void DBSession::SaveItem(DataPacketReader& reader)
{
	ActorId actorid = 0;

	int bag_type = 0;

	reader >> actorid >> bag_type;
	//reader.setPosition(0);
	int cache_type = GetCacheType(bag_type);

	static  std::map<ActorId, std::map<int, std::string>> db_buf; //分包数据
	uint32_t curr_index = 0;
	uint32_t size = 0;
	uint32_t max_size = 0;

	reader >> curr_index >> size >> max_size;

	auto& buf = db_buf[actorid][bag_type];
#pragma  pack(1)
	struct head
	{
		ActorId actorid;
		int bag_type;
	};
#pragma  pack()
	if (curr_index == 0)
	{
		buf.resize(max_size + sizeof(head));


		head* h = (head*)&buf[0];

		h->actorid = actorid;
		h->bag_type = bag_type;
	}
	if (max_size != 0)
	{
		if (curr_index + sizeof(head) < buf.size()) {
			memcpy(&buf[curr_index + sizeof(head)], reader.getOffsetPtr(), reader.getAvaliableLength());
		}
		else {
			OutputMsg(rmNormal, "save Item Error");
		}
	}
	if ((curr_index + size) >= max_size)
	{
		client_mgr_->LockCache();
		client_mgr_->GetCache()->UpdateCache(actorid, cache_type, &buf[0], buf.size(), true);
		client_mgr_->UnLockCache();
		db_buf[actorid].erase(bag_type);

		if (db_buf[actorid].empty())
		{
			db_buf.erase(actorid);
		}
	}

}

void DBSession::SaveCSScriptData(DataPacketReader& reader) {
	ActorId actorid = 0;
	uint32_t curr_index = 0;
	uint32_t size = 0;
	uint32_t max_size = 0;
	reader >> actorid >> curr_index >> size >> max_size;
	static  std::map<ActorId, std::string> db_cs_buf; //分包数据
	auto& buf = db_cs_buf[actorid];
#pragma  pack(1)
	struct head {
		ActorId actorid;
	};
#pragma  pack()
	if (curr_index == 0) {
		buf.resize(max_size + sizeof(head));
		head* h = (head*)&buf[0];
		h->actorid = actorid;
	}

	if (max_size != 0) {
		memcpy(&buf[curr_index + sizeof(head)], reader.getOffsetPtr(), reader.getAvaliableLength());
	}
	if ((curr_index + size) >= max_size) {
		client_mgr_->LockCache();
		size_t tmpSize = buf.size();
		client_mgr_->GetCache()->UpdateCache(actorid, DBCacheType_CsScriptData, &buf[0], buf.size(), true);
		client_mgr_->UnLockCache();
		db_cs_buf.erase(actorid);
		OutputMsg(rmError, "SaveCSScriptData:actorid=%d,max_size=%lld", actorid, tmpSize);
	}
	OutputMsg(rmError, "SaveCSScriptData:actorid=%d,curr_index=%d", actorid, curr_index);
	/*
	client_mgr_->LockCache();

	client_mgr_->GetCache()->CacheData(DBCacheType_ScriptData, reader);
	client_mgr_->UnLockCache();
	*/
}

void DBSession::SaveScriptData(DataPacketReader& reader)
{
	ActorId actorid = 0;
	uint32_t curr_index = 0;
	uint32_t size = 0;
	uint32_t max_size = 0;
	reader >>actorid>> curr_index >> size >> max_size;
	static  std::map<ActorId, std::string> db_buf; //分包数据
	auto& buf = db_buf[actorid];
#pragma  pack(1)
	struct head
	{
		ActorId actorid;
	};
#pragma  pack()
	if (curr_index == 0)
	{
		buf.resize(max_size + sizeof(head));
		head* h = (head*)&buf[0];
		h->actorid = actorid;
	}

	if (max_size != 0)
	{
		memcpy(&buf[curr_index + sizeof(head)], reader.getOffsetPtr(), reader.getAvaliableLength());
	}
	if ((curr_index + size) >= max_size)
	{
		client_mgr_->LockCache();
		client_mgr_->GetCache()->UpdateCache(actorid, DBCacheType_ScriptData, &buf[0], buf.size(), true);
		client_mgr_->UnLockCache();
		db_buf.erase(actorid);
		OutputMsg(rmError, "SaveScriptData:actorid=%d,max_size=%lld", actorid, max_size);
	}
	OutputMsg(rmError, "SaveScriptData:actorid=%d,curr_index=%d", actorid, curr_index);
	/*
	client_mgr_->LockCache();

	client_mgr_->GetCache()->CacheData(DBCacheType_ScriptData, reader);
	client_mgr_->UnLockCache();
	*/
}

bool DBSession::OnEntitySysRecv(int cmd, DataPacketReader& reader)
{
	switch (cmd)
	{
	case dcQuery:			//查询数据
		QueryActorFromDB(reader);
		break;

	case dcSave:				//保存数据
		client_mgr_->LockCache();
		client_mgr_->GetCache()->CacheData(DBCacheType_ActorBasic, reader);
		client_mgr_->UnLockCache();
		break;
	case dcSaveCsWarVar:
		//client_mgr_->LockCache();
		//client_mgr_->GetCache()->CacheData(DBCacheType_CsScriptData, reader);
		//client_mgr_->UnLockCache();
		SaveCSScriptData(reader);
		break;
	case dcActorCacheSave:
		client_mgr_->LockCache();
		client_mgr_->GetCache()->CacheData(DBCacheType_ActorCache, reader);
		client_mgr_->UnLockCache();
		break;
	case dcSaveRole:
		client_mgr_->LockCache();
		OutputMsg(rmTip, "---------DB, on SaveRole.");
		client_mgr_->GetCache()->CacheData(DBCacheType_RoleData, reader);
		client_mgr_->UnLockCache();
		break;

	case dcSaveVar:			//保存角色变量
		SaveScriptData(reader);
		break;

	case dcSaveItem:		//保存道具背包
	{

		SaveItem(reader);
	
		break;
	}

	case dcSaveMail:
		client_mgr_->LockCache();
		OutputMsg(rmTip, "---------DB, on SaveMail.");
		client_mgr_->GetCache()->CacheData(DBCacheType_Mail, reader);
		client_mgr_->UnLockCache();
		break;

	case dcSaveStore:
		client_mgr_->LockCache();
		OutputMsg(rmTip, "---------DB, on SaveStore.");
		client_mgr_->GetCache()->CacheData(DBCacheType_Store, reader);
		client_mgr_->UnLockCache();
		break;
	case dcSaveTogHitEquip:
		client_mgr_->LockCache();
		OutputMsg(rmTip, "---------DB, on SaveTogHitEquip.");
		client_mgr_->GetCache()->CacheData(DBCacheType_TogHitEquip, reader);
		client_mgr_->UnLockCache();
		break;
	case dcLogout:
		ActorId actorId;
		int level;
		int job;
		unsigned long long cw_fbhdl_sid;
		long long int total_power;
		long long int rank_power;
		const char* name;
		reader >> actorId >> level >> job;
		reader >> name;
		reader >> cw_fbhdl_sid;
		reader >> total_power;
		reader >> rank_power;
		

		updateOnLogout(actorId, name, total_power, rank_power);

		client_mgr_->LockCache();
		client_mgr_->GetCache()->OnActorLogout(reader);
		client_mgr_->UnLockCache();
		break;

	case dcResetCrossPos:
		ResetCrossPos(reader);
		break;

	case dcLoadMsg:		//读取用户的消息数据
		{
			LoadMsgList(reader);
			break;
		}

	case dcDeleteMsg:			//删除某条消息
		{
			DeleteMsg(reader);
			break;
		}

	case dcLoadMail:
		{
			//LoadMailList(reader);
			break;
		}

	case dcDeleteMail:
		{
			//DeleteMail(reader);
			break;
		}

	case dcUpdateMailStatus:
		{
			//UpdateMailStatus(reader);
			break;
		}

	case dcDeleteMailFile:
		{
			//DeleteMailFile(reader);
			break;
		}

	case dcGetActorIdFromActroName:
		{
			//GetActorIdFormActorName(reader);
			break;
		}

	case dcSaveMountData:
		{
/*			client_mgr_->LockCache();
			client_mgr_->GetCache()->CacheData(enCT_MountData, reader);
			client_mgr_->UnLockCache();
			break*/;
		}

	case dcLoadFriends:
		{
			LoadFriends(reader);
			break;
		}

	
	case dcUpdateFriend:
	{
		UpdateFriend(reader);
		break;
	}
	case dcDelFriend:
		{
			DelFriend(reader);
			break;
		}

	case dcUpdateFriendInfo:
		{
			//UpdateFriendInfo(reader);
			break;
		}

	case dcUpdateFriendContact:
		{
			//UpdateFriendContact(reader);
			break;
		}

	case dcAddEqSign:
		{
			//AddEqSign(reader);
			break;
		}

	case dcInheritEqSign:
		{
			//InheritEqSign(reader);
			break;
		}

	case dcGetEqSignList:
		{
			//GetEqSignList(reader);
			break;
		}

	case dcSaveCale:
		{
			//if (IsBattleSrv()) break;
/*
			client_mgr_->LockCache();
			client_mgr_->GetCache()->CacheData(enCT_CaleData, reader);
			client_mgr_->UnLockCache();
			break*/;
		}

		//case dcLoadCale:
		//{
		//	ActorId nActorID;
		//	reader >> nActorID;
		//	QueryActorCaleData(nActorID);
		//	break;
		//}

	case dcSaveFbCountData:
		{
			//client_mgr_->LockCache();
			//client_mgr_->GetCache()->CacheData(enCT_FbCountData, reader);
			//client_mgr_->UnLockCache();
			break;
		}

	case dcAddFightLog:
		{
			//AddFightLog(reader);
			break;
		}

	case dcDelFightLog:
		{
			//DelFightLog(reader);
			break;
		}

	case dcPetSkill:        //保持技能数据
		{
//			client_mgr_->LockCache();
//			client_mgr_->GetCache()->CacheData(enCT_PetSkill, reader);
//			client_mgr_->UnLockCache();
			break;
		}

	case dcSavePetBase:
		{
/*			client_mgr_->LockCache();
			client_mgr_->GetCache()->CacheData(enCT_PetBase, reader);
			client_mgr_->UnLockCache();
			break*/;
		}

	//case dcSaveMarryInfo:
	//{
	//	client_mgr_->LockCache();
	//	client_mgr_->GetCache()->CacheData(enCT_MarryBase, reader);
	//	client_mgr_->UnLockCache();
	//	break;
	//}

	case dcOfflineDivorce:
	{
		//offlineDivorce(reader, *sql_);
		break;
	}

	//case dcOfflineLogout:
	//{
	//	//offlineSetLogouTime(reader, *sql_);
	//	break;
	//}

	//	//case dcLoadCrossVar:			//加载角色跨服战变量
	//	//	{
	//	//		ActorId nActorID;
	//	//		reader >> nActorID;
	//	//		QueryCrossScriptData(nActorID);
	//	//		break;
	//	//	}

	//case dcSaveCrossVar:			//保存角色跨服战变量
	//	{
	//		client_mgr_->LockCache();
	//		client_mgr_->GetCache()->CacheData(enCT_CrossScriptData, reader);
	//		client_mgr_->UnLockCache();
	//		break;
	//	}

	/*case dcSaveTongTianTaStoreItem:
		{
			//if (IsBattleSrv()) break;

			client_mgr_->LockCache();
			client_mgr_->GetCache()->CacheData(enCT_TongTianTaData, reader);
			client_mgr_->UnLockCache();
			break;
		}*/

	//case dcSaveSkillMiji:
	//	{
	//		client_mgr_->LockCache();
	//		client_mgr_->GetCache()->CacheData(enCT_MijiItem, reader);
	//		client_mgr_->UnLockCache();
	//		break;
	//	}

	//case dcClearActorDbCache:
	//	{
	//		client_mgr_->LockCache();
	//		client_mgr_->GetCache()->ClearCacheData(*sql_, reader);
	//		client_mgr_->UnLockCache();
	//		break;
	//	}

	//case dcSaveOnceTime:
	//	{
	//		DBDataCache::SetSaveOnceTime(reader);
	//		break;
	//	}

	//case dcSaveWing:
	//	{
	//		client_mgr_->LockCache();
	//		client_mgr_->GetCache()->CacheData(enCT_WingData, reader);
	//		client_mgr_->UnLockCache();
	//		break;
	//	}

	//case dcSaveActorMisc:
	//	{
	//		SaveActorMisc(reader);
	//		break;
	//	}

	//case dcLoadActorMisc:
	//	{
	//		LoadActorMisc(reader);
	//		break;
	//	}

	//case dcSaveRankVar:
	//	{
	//		SaveActorRankVar(reader);
	//		break;
	//	}

	case dcSaveActorGuild:
		client_mgr_->LockCache();
		OutputMsg(rmTip, "---------DB, on SaveGuild.");
		client_mgr_->GetCache()->CacheData(DBCacheType_Guild, reader);
		client_mgr_->UnLockCache();
		break;
	case dcAddMember:
	{
		AddGuildMember(reader);
		break;
	}
	case dcDeleteMember:
	{
		DeleteMember(reader);
		break;
	}

	case dcSetDataValid:
		{
			OnSetValid(reader);
			break;
		}

	case dcEnableCheckValid:
		{
			OnEnableCheckValid(reader);
			break;
		}
	case dcLoadPrivateChat:
	{
		LoadPrivateChats(reader);
		break;
	}
	case dcAddPrivateChat:
	{
		AddPrivateChats(reader);
		break;
	}
	case dcDelPrivateChat:
	{
		DelPrivateChats(reader);
		break;
	}
	case dcBatchDelPrivateChat:
	{
		BachDelPrivateChats(reader);
		break;
	}
	case dcLoadPVMlayer:
	{
		LoadPVMlayerData(reader);
		break;
	}
	case dcUpdatePVMlayer:
	{
		SavePVMlayerData(reader);
		break;
	}
	case dcUpdateChallengeRecord:
	{
		UpdateChannengeRecord(reader);
		break;
	}
	case dcLoadChallengeRecord:
	{
		LoadPlayerRecord(reader);
		break;
	}
	case dcSaveAFKData:
	{
		SavePlayerAFKData(reader);
		break;
	}
	case dcLoadAFKData:
	{
		LoadPlayerAFKData(reader);
		break;
	}
	default:
		{
			return false;
			break;
		}
	}

	return true;
}

void DBSession::OnGuildSysRecv(int cmd, DataPacketReader& reader)
{
	switch (cmd)
	{
	case dcLoadGuildList://帮派组件读入所有帮派的数据
		{
			//LoadGuildList(reader);
			break;
		}

	case dcLoadGuildDetail:	//帮派的详细数据
		{
			//LoadGuildDetail(reader);
			break;
		}

	case dcAddGuild:			//增加帮派
		{
			AddGuild(reader);
			break;
		}

	case dcDeleteGuild:		//解散帮派
		{
			DeleteGuild(reader);
			break;
		}

	case dcSaveGuild:		//保存帮派的信息
		{
			SaveGuild(reader);
			break;
		}

	case dcSaveGuildVar:
		{
			SaveGuildVar(reader);
			break;
		}

	case dcSaveGuildChat:
	{
		SaveGuildChat(reader);
		break;
	}

	case dcLoadGuildDepot:
		{
			//LoadGuildDepot(reader);
			break;
		}

	case dcSaveGuildDepot:	//保存帮派仓库信息
		{
			//SaveGuildDepot(reader);
			break;
		}

	case dcLoadBeastLog:
		{
			//LoadBeastLog(reader);
			break;
		}

	case dcAddBeastLog:
		{
			//AddBeastLog(reader);
			break;
		}

	case dcDeleteBeastLog:
		{
			//DeleteBeastLog(reader);
			break;
		}

	case dcLoadGuildLog:
		{
			//LoadGuildLog(reader);
			break;
		}

	case dcAddGuildLog:
		{
			AddGuildLog(reader);
			break;
		}

	case dcDelGuildLog:
		{
			DeleteGuildLog(reader);
			break;
		}

	case dcLoadOneGuild:
		{
			//LoadOneGuild(reader);
			break;
		}
	case dcSaveGuildStore:
	{
		SaveGuildStore(reader);
		break;
	}
	}
}

void DBSession::OnConsignmentSysRecv(int cmd, DataPacketReader& reader)
{
	switch (cmd)
	{
	case dcLoadConsignment://读取所有的寄卖物品信息
		{
			//LoadAllConsignmentItem(reader);
			break;
		}

	case dcSaveConsignmentItem:  //保存寄卖物品,包括删除和添加
		{
			//SaveConsignmentItem(reader);
			break;
		}
	}
}

void DBSession::OnMailSysRecv(int cmd, DataPacketReader& reader)
{
	switch (cmd)
	{
	case dcAddMail:				//增加用户一条信息
		{
			//AddMail(reader);
			break;
		}

	case dcAddMailByActorName:
		{
			//AddMailByName(reader);
			break;
		}

	case dcAddMailByAccountName:
		{
			//AddMailByAccountName(reader);
			break;
		}
	}
}

void DBSession::OnMsgSysRecv(int cmd, DataPacketReader& reader)
{
	switch (cmd)
	{
	case dcAddMsg:				//增加用户一条信息
		{
			AddMsg(reader);
			break;
		}
	case dcAddChat:
		{
			SaveChat(reader);
			break;
		}
	}
}

void DBSession::OnLoadRank(int cmd, DataPacketReader&)
{
	switch (cmd)
	{
	case dcLoadRank:
		{
			//LoadRank();
			break;
		}
	}
}

//todo
bool DBSession::OnGlobalRecv(int cmd, DataPacketReader& reader)
{
	switch (cmd)
	{
	//case dcLoadBossKiller:
	//case dcLoadMaster:
	//	{
	//		LoadGlobal(cmd, reader);
	//		break;
	//	}

	//case dcSaveBossKiller:
	//case dcSaveMaster:
	//	{
	//		SaveGlobal(cmd, reader);
	//		break;
	//	}

	case dcCheckVer:
		{
			int ver = 0;
			reader >> ver;

			if (ver != InterSrvComm::DBSER_VER)
			{
				OutputMsg(rmError, "check version fail!except %d, now:%d", InterSrvComm::DBSER_VER, ver);
				// 版本不对，直接close连接
				Close();
			}

			break;
		}

	case dcBattleFlag:
		{
			int target_sid;
			reader >> target_sid >> battleflag_;
			OutputMsg(rmError, "=======recv:battleflag:%d,targetsid:%d", battleflag_, target_sid);
			SetTargetId(target_sid);
			break;
		}

	//case dcAddQuestion:
		//AddGmQuestion(reader);
		//break;

	//case  dcLoadQuestions:
		//LoadGmQuestions(reader);
		//break;

	//case dcLoadQuestion:
		//LoadGmQuestion(reader);
		//break;

	//case dcUpdateQuestion:
		//UpdateGmQuestion(reader);
		//break;

	//case dcAddBug:
	//	AddBug(reader);
	//	break;

	//case dcLoadGoldRank:
	//	LoadGoldRank(reader);
	//	break;

	//case dcLoadMarry:
	//	LoadMarryRecord(reader);
	//	break;

	default:
		{
			return false;
			break;
		}
	}

	return true;
}

void DBSession::OnFightRecv(int cmd, DataPacketReader& reader)
{
	switch (cmd)
	{
	case dcLoadFightRank:
		{
			//LoadFightRank();
			break;
		}

	case dcSaveFightRank:
		{
			//SaveFightRank(reader);
			break;
		}
	}
}

void DBSession::OnCommonRecv(int cmd, DataPacketReader& reader)
{
	switch (cmd)
	{
	case dcLoadSysVar:
		LoadSysVar(reader);
		break;

	case dcAddSysVar:
		AddSysVar(reader);
		break;

	case dcUpdateSysVar:
		UpdateSysVar(reader);
		break;
	}
}

void DBSession::OnWarTeamRecv(int cmd, DataPacketReader& reader)
{
	switch (cmd)
	{
	case dcLoadWarTeam:
		//LoadWarTeamList(reader);
		break;

	case dcAddWarTeam:
		//AddWarTeam(reader);
		break;

	case dcDelWarTeam:
		//DeleteWarTeam(reader);
		break;

	case dcUpdateWarTeam:
		//UpdateWarTeam(reader);
		break;

	case dcLoadWarTeamMember:
		//LoadWarTeamMember(reader);
		break;

	case dcAddWarTeamMember:
		//AddWarTeamMember(reader);
		break;

	case dcDelWarTeamMember:
		//DelWarTeamMember(reader);
		break;

	case dcUpdateWarTeamMember:
		//UpdateWarTeamMember(reader);
		break;

	case dcLoadOneWarTeam:
		//LoadOneWarTeam(reader);

	default:
		break;
	}
}


//查询礼包物品
void DBSession::LoadGiftItem(DataPacketReader& reader)
{
	/*
	DataPacket& retPack = allocProtoPacket(MAKEINT16(siConfig, ctLoadGiftItem));

	//数据库连接是否就绪
	if (!sql_->Connected())
	{
		retPack << (char)reDbErr;
	}
	else
	{
		int err = sql_->Query(loadgiftitem);

		if (!err)
		{
			retPack << (char)reSucc;
			MYSQL_ROW row = sql_->CurrentRow();
			retPack << (int)sql_->GetRowCount();

			while (row)
			{
				int i = 0;
				Staticaward_t data;
				memset(&data, 0, sizeof(data));
				sscanf(row[++i], "%d", &data.itemid); //为了，直接返回所有数据，包括自增长id，但是不存入内存中
				sscanf(row[++i], "%d", &data.needgrid);
				i++;
				_STRNCPY_A(data.itemname, row[i]);
				i++;
				_STRNCPY_A(data.itemdesc, row[i]);
				sscanf(row[++i], "%d", &data.icon);
				sscanf(row[++i], "%d", &data.dup);
				sscanf(row[++i], "%d", &data.flag);
				sscanf(row[++i], "%d", &data.grouptype);
				sscanf(row[++i], "%d", &data.itime);
				sscanf(row[++i], "%d", &data.cond_cons_id);
				sscanf(row[++i], "%d", &data.cond_cons_count);
				sscanf(row[++i], "%d", &data.cond_money_type);
				sscanf(row[++i], "%d", &data.cond_money_count);
				i++;
				_STRNCPY_A(data.cond_value, row[i]);
				row = sql_->NextRow();
				retPack << data;
			}

			sql_->ResetQuery();
		}
		else
		{
			retPack << (char)reDbErr; //这里用db是否合理
		}
	}

	flushProtoPacket(retPack);
	*/
}

//查询礼包配置,即有哪些奖品
void DBSession::LoadGiftConfig(DataPacketReader& reader)
{
	DataPacket& retPack = allocProtoPacket(MAKEINT16(siConfig, ctLoadGiftConfig));

	//数据库连接是否就绪
	if (!sql_->Connected())
	{
		retPack << (char)reDbErr;
	}
	else
	{
		int err = sql_->Query(loadgiftconfig);

		if (!err)
		{
			retPack << (char)reSucc;
			MYSQL_ROW row = sql_->CurrentRow();
			retPack << (int)sql_->GetRowCount();

			while (row)
			{
				Staticawardconfig_t data;
				memset(&data, 0, sizeof(data));
				sscanf(row[1], "%d", &data.giftitemid);
				sscanf(row[2], "%d", &data.rewardtype);
				sscanf(row[3], "%d", &data.contenttype);
				sscanf(row[4], "%d", &data.amount);
				sscanf(row[5], "%d", &data.itemid);
				sscanf(row[6], "%d", &data.bind);
				sscanf(row[7], "%d", &data.group);
				sscanf(row[8], "%d", &data.rate);
				sscanf(row[9], "%d", &data.noworldrate);
				sscanf(row[10], "%d", &data.quality);
				sscanf(row[11], "%d", &data.strong);
				row = sql_->NextRow();
				retPack << data;
			}

			sql_->ResetQuery();
		}
		else
		{
			retPack << (char)reDbErr; //这里用db是否合理
		}
	}

	flushProtoPacket(retPack);

}


void DBSession::OnGiftItemConfigRecv(int cmd, DataPacketReader& reader)
{
	switch (cmd)
	{
	case ctLoadGiftItem:
		LoadGiftItem(reader);

		break;

	case ctLoadGiftConfig:
		LoadGiftConfig(reader);
		break;

	default:

		break;
	}

}

void DBSession::OnRecvCommonDB(int cmd, DataPacketReader& reader)
{
	switch (cmd)
	{
	case dcDBExec:
	{
		executor_->HandleExec(reader);
	}
	break;
	default:
		break;
	}
}

void DBSession::OnRecvAuctionDB(int cmd, DataPacketReader & reader)
{
	switch (cmd)
	{
	case dcAuctionAdd:
	{
		int id, addTime, guildEndTime, globalEndTime, guildId, auctionId, flag;
		const char *owners;
		reader >> id >> addTime >> guildEndTime >> globalEndTime;
		reader >> owners;
		reader >> guildId >> auctionId >> flag;
		//数据库连接是否就绪
		if (!sql_->Connected()) {
			OutputMsg(rmError, ("%s on add Connected fail, %d %d %s"), __FUNCTION__, id, auctionId, owners);
		}
		else
		{
			int err = sql_->Exec(addauctionitem, id, addTime, guildEndTime, globalEndTime, owners, guildId, auctionId, getClientServerIndex(), flag);

			if (!err) {
				sql_->ResetQuery();
			} else {
				OutputMsg(rmError, ("%d on add sql exec err(%d) %d %d %s"), __FUNCTION__, err, id, auctionId, owners);
			}
		}
		break;
	}
	case dcAuctionDel:
	{
		int id;
		reader >> id;
		//数据库连接是否就绪
		if (!sql_->Connected()) {
			OutputMsg(rmError, ("%s on del Connected fail, %d"), __FUNCTION__, id);
		}
		else
		{
			int err = sql_->Exec(delauctionitem, id);

			if (!err) {
				sql_->ResetQuery();
			}
			else {
				OutputMsg(rmError, ("%d on del sql exec err(%d) %d"), __FUNCTION__, err, id);
			}
		}
		break;
	}
	case dcAuctionUpdate:
	{
		int count, guildEndTime, globalEndTime, bid, bidder, gbidder, flag, hyLimit, ybLimit, id;

		reader >> count;
		//数据库连接是否就绪
		if (!sql_->Connected()) {
			OutputMsg(rmError, ("%s on update Connected fail"), __FUNCTION__);
		}
		else
		{
			for (int i=0; i<count; i++){
				reader >> guildEndTime >> globalEndTime >> bid >> bidder >> gbidder >> flag >> hyLimit >> ybLimit >> id;
				int err = sql_->Exec(updateauctionitem, guildEndTime, globalEndTime, bid, bidder, gbidder, flag, hyLimit, ybLimit, id);

				if (!err) {
					sql_->ResetQuery();
				}
				else {
					OutputMsg(rmError, ("%d on update sql exec err(%d) %d"), __FUNCTION__, err, id);
				}
			}
		}
		break;
	}
	default:
		break;
	}
}

void DBSession::OnRecvPVMDB(int cmd, DataPacketReader & reader)
{
}


void DBSession::ResetCrossPos(DataPacketReader& reader)
{
	ActorId aid = 0;
	reader >> aid;

	client_mgr_->LockCache();
	ActorCsData* actorData = nullptr;
	DataPacket *pack = client_mgr_->GetCache()->GetReadableData(aid, DBCacheType_ActorCache);
	if (pack != nullptr) {
		if (pack->getLength() >= sizeof(ActorCsData) + sizeof(ActorId)) {
			actorData = (ActorCsData*)pack->getPositionPtr(sizeof(ActorId));
		}
	}

	if (actorData) {
		actorData->cw_fbhdl_sid_ = 0;
		actorData->cw_scene_xy_ = 0;
		actorData->cw_static_pos_ = 0;
	}
	client_mgr_->UnLockCache();
}

void DBSession::processNetMsg(const uint16_t cmd, DataPacketReader& data)
{
	bool proced = true;
	int sys_id = LOINT8(cmd);
	int cmd_id = HIINT8(cmd);

	if (sys_id == siActor)
	{
		proced = OnEntitySysRecv(cmd_id, data);
	}
	else if (sys_id == siGuild)
	{
		OnGuildSysRecv(cmd_id, data);
	}
	else if (sys_id == siConsignment)
	{
		OnConsignmentSysRecv(cmd_id, data);
	}
	else if (sys_id == siMsg)
	{
		OnMsgSysRecv(cmd_id, data);
	}
	else if (sys_id == siMail)
	{
		OnMailSysRecv(cmd_id, data);
	}
	else if (sys_id == siRank)
	{
		OnLoadRank(cmd_id, data);
	}
	else if (sys_id == siGlobal)
	{
		proced = OnGlobalRecv(cmd_id, data);
	}
	else if (sys_id == siFight)
	{
		OnFightRecv(cmd_id, data);
	}
	else if (sys_id == siCommon)
	{
		OnCommonRecv(cmd_id, data);
	}
	else if (sys_id == siConfig)
	{
		OnGiftItemConfigRecv(cmd_id, data);
	}
	else if (sys_id == siWarTeam)
	{
		OnWarTeamRecv(cmd_id, data);
	}
	else if (sys_id == siDefault)
	{
		OnDefaultSysRecv(cmd_id, data);
	}
	else if (sys_id == siCommonDB)
	{
		OnRecvCommonDB(cmd_id, data);
	}
	else if (sys_id == siAuction) {
		OnRecvAuctionDB(cmd_id, data);
	}
	else if (sys_id == siPvmDB)
	{
		OnRecvPVMDB(cmd_id, data);
	}
	else
	{
		proced = false;
	}

	if (proced){};
	//去警告的

	/*if (!proced)
	{
		ScriptValueList args;
		args << (int)sys_id;
		args << (int)cmd_id;
		args << (void*)&data;
		args << getClientServerIndex();
		args << (void*)sql_;
		args << this;
		script_.Call("OnRecv", &args, &args);
	}*/
}

void DBSession::updateOnLogout(ActorId actorId, const char* name, long long int tPower, long long int rank_power)
{
	//sprintf(huge_buf_, updateactorlogout, level, job, cw_fbhdl_sid, actorId);

	//int err = sql_->RealExec(huge_buf_, strlen(huge_buf_));

	//if (err == reSucc)
	//	sql_->ResetQuery();

	sprintf(huge_buf_, updateactorlogout, name, tPower, rank_power, actorId);

	int err = sql_->RealExec(huge_buf_, strlen(huge_buf_));
	if (err == reSucc)
		sql_->ResetQuery();
}

void DBSession::updateOnLogin(ActorId actorId)
{
	//sprintf(huge_buf_, updateactorlogin, actorId);

	//int err = sql_->RealExec(huge_buf_, strlen(huge_buf_));

	//if (err == reSucc)
		//sql_->ResetQuery();
}

void DBSession::OnDefaultSysRecv(int cmd, DataPacketReader& reader)
{
	switch (cmd)
	{
	case dcInitDB:
		InitDB(reader);
		break;

	case dcExecDB:
		ExecFromGameWorld(reader);
		break;

	default:
		break;
	}
}

void DBSession::ExecFromGameWorld(DataPacketReader& reader)
{
	//返回结果给gameworld
	DataPacket& retPack = allocProtoPacket(MAKEINT16(siDefault, dcExecDB));

	//数据库连接是否就绪
	if (!sql_->Connected())
	{
		retPack << (char)reDbErr;
	}
	else
	{
		reader.readString(huge_buf_, HUNGSIZE);

		int err = sql_->RealExec(huge_buf_, strlen(huge_buf_));

		if (err == reSucc)
			sql_->ResetQuery();

		retPack << (char)err;
	}

	retPack.writeString(huge_buf_);
	flushProtoPacket(retPack);
}

void DBSession::InitDB(DataPacketReader& reader)
{
	int serverid = getClientServerIndex();

	if (!sql_->Connected()) return;

	int err = sql_->Query(initdb, serverid);

	if (err == reSucc)
	{
		sql_->ResetQuery();
	}
	else
	{
		OutputMsg(rmError, "initdb error !!!");
	}
}

void DBSession::SaveActorMisc(DataPacketReader& reader)
{
	ActorId actorId = 0;
	int type, val;
	const char* fieldName = NULL;
	reader >> actorId >> type >> val;

	if (type == 1)
	{
		fieldName = "cw_team_time";
	}
	else
	{
		return;
	}

	if (!sql_->Connected()) return;

	int err = sql_->Exec(saveactormisc, fieldName, val, actorId);

	if (err == reSucc)
	{
		sql_->ResetQuery();
	}
	else
	{
		OutputMsg(rmError, "saveactormisc error !!! actorId=%d, fieldName=%s, value=%d", actorId, fieldName, val);
	}

}

void DBSession::LoadActorMisc(DataPacketReader& reader)
{
	ActorId actorId = 0;
	int type;
	int val = 0;
	const char* fieldName = NULL;
	reader >> actorId >> type;

	if (type == 1)
	{
		fieldName = "cw_team_time";
	}
	else
	{
		return;
	}

	if (!sql_->Connected()) return;

	int err = sql_->Query(loadactormisc, fieldName, actorId);

	if (err == reSucc)
	{
		MYSQL_ROW row = sql_->CurrentRow();

		if (!row)
		{
			sql_->ResetQuery();
			int tmpErr = sql_->Exec(insertmisc, actorId);

			if (tmpErr == reSucc)
			{
				sql_->ResetQuery();
			}
		}
		else
		{
			if (row[0]) sscanf(row[0], "%d", &val);

			sql_->ResetQuery();
		}

		DataPacket& packet = allocProtoPacket(MAKEINT16(siActor, dcLoadActorMisc));
		packet << (int)actorId << (char)err << (int)type << (int)val;
		flushProtoPacket(packet);
	}
	else
	{
		OutputMsg(rmError, "loadactormisc error !!! actorId=%d, type=%d", actorId, type);
	}
}

void DBSession::SaveActorRankVar(DataPacketReader& reader)
{
	if (!sql_ || !sql_->Connect()) return;

	SaveActorVariableData(reader, "rankdata", *sql_, dcSaveRankVar);
}

void DBSession::OnSetValid(DataPacketReader& inPacket)
{
	ActorId aid;
	uint8_t flag;
	int targetSid;
	inPacket >> aid >> flag >> targetSid;
	bool valid_flag = (flag == 1);
	OutputMsg(rmTip, "DBSession::OnSetValid aid:%d,flag:%d", aid, flag);
	client_mgr_->LockCache();
	client_mgr_->GetCache()->SetValidFlag(aid, valid_flag);
	client_mgr_->UnLockCache();

	if (valid_flag && targetSid != 0)
	{
		client_mgr_->PostMsg(DBSessionMgr::rmWaitForLogin, targetSid, aid, 0, 0);
	}
}


void DBSession::OnEnableCheckValid(DataPacketReader& inPacket)
{
	uint8_t flag;
	inPacket >> flag;

	client_mgr_->LockCache();
	client_mgr_->s_checkValid = (flag == 1);
	client_mgr_->UnLockCache();
}

bool DBSession::HasWaitFor(ActorId actorid)
{
	if (wait_for_list_.get(actorid))
	{
		return true;
	}

	return false;
}

void DBSession::AddWaitFor(ActorId actorid)
{
	if (wait_for_list_.get(actorid))
	{
		return;
	}

	wait_for_list_.put(actorid, actorid);
	OutputMsg(rmTip, "DBSession::AddWaitFor actorid = %d", actorid);
}

void DBSession::RemoveWaitFor(ActorId actorid)
{
	wait_for_list_.remove(actorid);
	OutputMsg(rmTip, "DBSession::RemoveWaitFor actorid = %d", actorid);
}

void DBSession::SaveDepotItemCache(DataPacketReader& inPacket)
{
	uint8_t bDepotType;
	inPacket >> bDepotType;
	int cacheType = -1;
	switch (bDepotType)
	{
	case ipDepot   :
		cacheType = enCT_DepotItemData;   
		break;
	case ipLottery :
		cacheType = enCT_DmkjItemData;   
		break;
	case ipEntrust :
		cacheType = enCT_EntrustItemData; 
		break;
	case ipTreasure:
		cacheType = enCT_PetCrossItem;    
		break;
	case ipBabel   :
		cacheType = enCT_TongTianTaData;  
		break;
	}
	if (cacheType > 0)
	{
		client_mgr_->LockCache();
		client_mgr_->GetCache()->CacheData(DBCacheType(cacheType), inPacket);
		client_mgr_->UnLockCache();
	}
}
