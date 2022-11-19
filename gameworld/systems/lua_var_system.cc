#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

using namespace InterSrvComm::DbServerProto;


LuaVarSystem::LuaVarSystem(Actor* actor)
: actor_(actor)
{
	is_loaded_ = false;
	lua_var_.clear();
}

LuaVarSystem::~LuaVarSystem()
{
	lua_var_.clear();
}
int LuaVarSystem::GetIntValue(const char* key, int def/* = 0*/)
{
	if(!actor_ || !key) return def;

	ScriptValueList params;
	params << actor_;
	params << key;
	params << def;
	ScriptValueList retList;
	bool ret = actor_->CallFunc("GetIntVar", &params, &retList);
	
	if (!ret || retList.count() != 1) return def;
	
	ScriptValue& retParam = retList[0];
	
	if (retParam.getType() != ScriptValue::vNumber) return def;

	return (int)retParam;
}

// 按key设置整数数据
void LuaVarSystem::SetIntValue(const char* key, int value)
{
	if(!key) return;

	lua_var_.set(key, value);
}

void LuaVarSystem::Init(DataPacketReader& reader)
{

	if (!actor_)
	{
		OutputMsg(rmError, "actor is nil.");
		return;
	}
	if (actor_->CheckInitStep(Actor::InitFlagType_Lua))
	{
		OutputMsg(rmError, "actor initstep error.");
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
		lua_var_.loadFromMemory(db_buf_.c_str(), size);
		is_loaded_ = true;
		db_buf_.clear();
		buf_index_.clear();
		actor_->OnFinishInitStep(Actor::InitFlagType_Lua);
	}

	/*
	size_t size = reader.getAvaliableLength();
	lua_var_.loadFromMemory(reader.getOffsetPtr(), size);

	// 读取禁言数据
	//entity_->GetChatSystem().LoadFromScriptData();
	//entity_->GetGuildSystem().OnLoadScriptData();

	is_loaded_ = true;

	actor_->OnFinishInitStep(Actor::InitFlagType_Lua);
	*/
	
}

void LuaVarSystem::Save(ActorBasicData* pData)
{
	if (!is_loaded_) return;	// 如果从来没从db中加载过则不保存

	if (!actor_) return;

	DBClient* db = ServerInstance()->GetDbClient(actor_->GetServerId());
	if (!db) return;

	bool mem = true;
	
	size_t size = lua_var_.saveToMemory(NULL, 0, mem);
	db_buf_.resize(size);


	if ( lua_var_.saveToMemory(&db_buf_[0],db_buf_.size(),mem) != size)
	{
		OutputMsg(rmWarning, ("actor id=%d, the var data too large"), actor_->GetActorId());
	}

	if (db_buf_.size() == 0)
	{
		DataPacket& pack = db->allocProtoPacket(MAKEINT16(siActor, dcSaveVar));
		pack << (ActorId)actor_->GetActorId() << (uint32_t)0 << (uint32_t)0 << (uint32_t)0;
		db->flushProtoPacket(pack);
	}
	for (uint32_t i = 0; i < db_buf_.size(); i += PACK_LEN)
	{
		DataPacket& pack = db->allocProtoPacket(MAKEINT16(siActor, dcSaveVar));
		pack << (ActorId)actor_->GetActorId() <<i;

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

	//OutputMsg(rmError, "save Lua data:actorid=%d, size=%lld", actor_->GetActorId(), db_buf_.size());

	db_buf_.clear();

	/*
	DataPacket& pack = db->allocProtoPacket(MAKEINT16(siActor, dcSaveVar));

	pack << (ActorId)actor_->GetActorId();

	CLVariant* var_ptr = &lua_var_;

	bool mem = true;
	size_t totalSize = var_ptr->saveToMemory(NULL, 0, mem);

	pack.reserve(pack.getPosition() + totalSize);

	size_t savesize = var_ptr->saveToMemory(pack.getOffsetPtr(), pack.getAvaliableBufLen(), mem);
	if (savesize != totalSize)
	{
		OutputMsg(rmWarning, ("actor id=%d, the var data too large"), actor_->GetActorId());
	}
	pack.adjustOffset(savesize);

	db->flushProtoPacket(pack);

	*/
}


