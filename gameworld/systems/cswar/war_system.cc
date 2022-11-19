#include "StdAfx.h"
#include <string.h>
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

using namespace InterSrvComm::DbServerProto;

WarSystem::WarSystem(Actor* actor)
	: actor_(actor)
{
	is_loaded_ = false;
	lua_var_.clear();
}

WarSystem::~WarSystem()
{
	lua_var_.clear();
}

void WarSystem::InitLuaVar(DataPacketReader& reader)
{
	if (!actor_)
	{
		OutputMsg(rmError, "actor is nil.");
		return;
	}
	//if (!actor_->GetBasicData())
	//{
	//	OutputMsg(rmError, "load cs var error. actor base data not init.");
	//	return;
	//}
	//OutputMsg(rmTip, "load actor cross LUA var actorid;%d", actor_->GetActorId());
	if (actor_->CheckInitStep(Actor::InitFlagType_CsWarLua))
	{
		OutputMsg(rmError, "actor CsWarLua initstep error.");
		return;
	}
	uint32_t curr_index = 0;
	uint32_t size = 0;
	uint32_t max_size = 0;
	reader >> curr_index >> size >> max_size;

	if (max_size != 0)
	{
		if (db_buf_.size() < max_size)
		{
			db_buf_.resize(max_size);
			size_t index_size = 0;
			if (max_size != 0)
			{
				index_size = (size_t)ceil(max_size * 1.0 / PACK_LEN);
			}
			buf_index_.resize(index_size);
		}

		memcpy(&db_buf_[curr_index], reader.getOffsetPtr(), reader.getAvaliableLength());

		buf_index_[curr_index / PACK_LEN] = true;
	}
	auto check_buf_ok = [&](void)
	{
		for (size_t i = 0; i < buf_index_.size(); ++i)
		{
			if (!buf_index_[i])
				return false;
		}
		return true;
	};
	if (check_buf_ok())
	{
		size_t size = db_buf_.size();
		//OutputMsg(rmError, "LoadCSScriptData:actorid=%d,buf_size=%lld", actor_->GetActorId(), size);
		lua_var_.loadFromMemory(db_buf_.c_str(), size);
		is_loaded_ = true;
		db_buf_.clear();
		buf_index_.clear();
		actor_->OnFinishInitStep(Actor::InitFlagType_CsWarLua);
		
	}
}

bool WarSystem::LoadCsData(void* pData, size_t size)
{
	if (!actor_->CheckInitStep(Actor::InitFlagType_Basic))
	{
		OutputMsg(rmError, "init order error. on init csdata.");
		return false;
	}
	if (actor_->CheckInitStep(Actor::InitFlagType_ActorCsData))
		return true;


	memcpy(&srv_data_, pData, size);
	// 当玩家进入游戏后，根据这个值判断是否跳转到战斗服
	actor_->cw_serverid_ = HIINT32(srv_data_.cw_fbhdl_sid_);
	actor_->cw_fbhdl_ = LOINT32(srv_data_.cw_fbhdl_sid_);
	actor_->cw_sceneid_ = LOINT32(srv_data_.cw_scene_xy_);
	actor_->cw_x_ = LOINT16(HIINT32(srv_data_.cw_scene_xy_));
	actor_->cw_y_ = HIINT16(HIINT32(srv_data_.cw_scene_xy_));

	actor_->cw_static_sceneid_ = LOINT32(srv_data_.cw_static_pos_);
	actor_->cw_static_x_ = LOINT16(HIINT32(srv_data_.cw_static_pos_));
	actor_->cw_static_y_ = HIINT16(HIINT32(srv_data_.cw_static_pos_));

	static GameServer* srv = ServerInstance();
	if (actor_->cw_serverid_ == srv->GetServerIndex())
		actor_->cw_serverid_ = 0;

	actor_->OnFinishInitStep(Actor::InitFlagType_ActorCsData);

	return true;
}


void WarSystem::SaveCsData()
{
	if (!is_loaded_) return;	// 如果从来没从db中加载过则不保存
	if (!actor_) return;
	if (actor_->IsImage()) return;

	static GameServer* srv = ServerInstance();
	DBClient* db = srv->GetDbClient(actor_->GetServerId());
	if (!db) return;
	int battleflag = srv->GetBattleSrvFlag();
	if (battleflag == bsLianFuSrv || battleflag == bsCommSrv)
	{
		if (!actor_->waitForCross_)
		{
			srv_data_.cw_fbhdl_sid_ = 0;
			srv_data_.cw_scene_xy_ = 0;
			srv_data_.cw_static_pos_ = 0;
		}
		else
		{
			srv_data_.cw_fbhdl_sid_ = MAKEINT64(actor_->cw_fbhdl_, actor_->cw_serverid_);
			srv_data_.cw_scene_xy_ = MAKEINT64(actor_->cw_sceneid_, MAKEINT32(actor_->cw_x_, actor_->cw_y_));
			srv_data_.cw_static_pos_ = MAKEINT64(actor_->cw_static_sceneid_, MAKEINT32(actor_->cw_static_x_, actor_->cw_static_y_));
		}
	}
	DataPacket& dataPacket = db->allocProtoPacket(MAKEINT16(siActor, dcActorCacheSave));
	dataPacket << actor_->GetId();
	//dcActorDbSave
	dataPacket.writeBuf(&srv_data_, sizeof(ActorCsData));
	db->flushProtoPacket(dataPacket);
}

void WarSystem::SaveVar()
{
	if (!is_loaded_) return;	// 如果从来没从db中加载过则不保存
	if (!actor_) return;
	if (actor_->IsImage()) return;

	DBClient* db = ServerInstance()->GetDbClient(actor_->GetServerId());
	if (!db) return;

	//OutputMsg(rmTip, "save actor cross LUA var actorid;%d", actor_->GetId());

	bool mem = true;

	size_t size = lua_var_.saveToMemory(NULL, 0, mem);
	db_buf_.resize(size);


	if (lua_var_.saveToMemory(&db_buf_[0], db_buf_.size(), mem) != size)
	{
		OutputMsg(rmWarning, ("actor id=%d, the var data too large"), actor_->GetActorId());
	}

	if (db_buf_.size() == 0)
	{
		DataPacket& pack = db->allocProtoPacket(MAKEINT16(siActor, dcSaveCsWarVar));
		pack << (ActorId)actor_->GetActorId() << (uint32_t)0 << (uint32_t)0 << (uint32_t)0;
		db->flushProtoPacket(pack);
	}
	for (uint32_t i = 0; i < db_buf_.size(); i += PACK_LEN)
	{
		DataPacket& pack = db->allocProtoPacket(MAKEINT16(siActor, dcSaveCsWarVar));
		pack << (ActorId)actor_->GetActorId() << i;

		if ((i + PACK_LEN) >= db_buf_.size())
		{
			pack << (uint32_t)db_buf_.size() - i;
		}
		else
		{
			pack << (uint32_t)PACK_LEN;
		}
		pack << (uint32_t)db_buf_.size();

		if ((i + PACK_LEN) > db_buf_.size())
		{
			pack.writeBuf(&db_buf_[i], db_buf_.size() - i);
		}
		else
		{
			pack.writeBuf(&db_buf_[i], PACK_LEN);
		}
		db->flushProtoPacket(pack);
	}

	//OutputMsg(rmError, "save War Lua data:actorid=%d, size=%lld", actor_->GetActorId(), db_buf_.size());

	db_buf_.clear();
}

void WarSystem::Save() {
	SaveCsData();
	SaveVar();
}

int WarSystem::GetIntValue(const char* key, int def/* = 0*/)
{
	if (!actor_ || !key) return def;
	const char *p = NULL;
	int s = 0;
	int e = 0;
	int n = 0;
	int max = static_cast<int>( strlen(key) );

	char subkey[128];
	
	CLVariant* var = NULL;
	var =  &lua_var_;//根变量;
	do 
	{
		if ((p = strchr(key + s, '.')))
		{
			e = int(p - key);
			n = e - s;
			strncpy(subkey, key+s, n);
			subkey[n] = '\0';
			s = s + n + 1;
			
			var = var->get(subkey);
			if (!var)
			{
				return def;
			}
		}
		else
		{
			e = max + 1;
			n = e - s;
			strncpy(subkey, key + s, n);
			subkey[n] = '\0';
			s += n;

			var = var->get(subkey);
			if (!var)
			{
				return def;
			}
			double tar = *var;
			return (int)tar;
			
		}
	} while (s <= max);

	return def;
}





