#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

#include "system_var_mgr.h"

using namespace InterSrvComm::DbServerProto;

SysVarMgr::SysVarMgr()
	: mgr_("SysVarHdlMgr")
{
	list_.reserve(SYS_VAR_COUNT);
}

void SysVarMgr::Load()
{
	sysVarCount_ = -1;
	curSysVarCount_ = 0;

	DBClient* db = ServerInstance()->GetDbClient();
	if (!db) return;

	DataPacket& packet = db->allocProtoPacket(MAKEINT16(siCommon, dcLoadSysVar));
	db->flushProtoPacket(packet);
}

void SysVarMgr::OnDbReturnData(int cmd, DataPacketReader& reader)
{
	if (cmd == dcLoadSysVar)
	{
		int err;
		reader >> err;

		if (err != reSucc)
			return;
		
		int count;
		reader >> count;

		static ScriptNpc* npc = GetGameEngine()->GetGlobalNpc();

		for (int i = 0; i < count; ++i)
		{
			SysVarHandle hdl;
			SysVar* pVar = mgr_.AllocHandle(hdl);
			list_.push_back(hdl);

			reader >> pVar->id_;
			reader.readString(pVar->name_, sizeof(pVar->name_));
			reader >> pVar->sysId_;
			int buffSize;
			reader >> buffSize;
			size_t size = buffSize;
			pVar->var_.loadFromMemory(reader.getOffsetPtr(), size);
			reader.adjustOffset(buffSize);

			ScriptValueList vl;
			vl << pVar->id_
			   << pVar->name_
			   << pVar->sysId_
			   << (unsigned int)hdl;

			npc->GetScript().Call("OnSysVarDbReturnData", &vl, &vl);

			++curSysVarCount_;
		}
	}
	else if(cmd == dcSysVarCount)
	{
		int err;
		reader >> err;

		if (err != reSucc)
			return;

		reader >> sysVarCount_;
	}
}

unsigned int SysVarMgr::createSysVar(int ownerId, const char* ownerName, int type)
{
	if (ownerName == NULL)
		return 0;

	DBClient* db = ServerInstance()->GetDbClient();
	if (!db) return 0;

	SysVarHandle hdl;
	SysVar* pVar = mgr_.AllocHandle(hdl);
	list_.push_back(hdl);

	pVar->id_ = ownerId;
	_STRNCPY_A(pVar->name_, ownerName);
	pVar->sysId_ = type;

	DataPacket& packet = db->allocProtoPacket(MAKEINT16(siCommon, dcAddSysVar));
	packet << (ActorId)ownerId;
	packet.writeString(ownerName);
	packet << (int)type;

	bool mem = true;
	size_t totalSize = pVar->var_.saveToMemory(NULL, 0, mem);
	packet.reserve(packet.getPosition() + totalSize);

	size_t savesize = pVar->var_.saveToMemory(packet.getOffsetPtr(), packet.getAvaliableBufLen(), mem);

	if (savesize != totalSize)
	{
		OutputMsg(rmWarning, ("SysVarMgr createSysVar id=%d, the var data too large"), ownerId);
	}

	packet.adjustOffset(savesize);

	db->flushProtoPacket(packet);

	return hdl;
}

void SysVarMgr::saveSysVar(int ownerId, int type, unsigned int hdl)
{
	SysVar* pVar = getPtrByHandle(hdl);

	if (pVar == NULL)
		return;

	DBClient* db = ServerInstance()->GetDbClient();
	if (!db) return;

	DataPacket& packet = db->allocProtoPacket(MAKEINT16(siCommon, dcUpdateSysVar));
	packet << (ActorId)ownerId
	       << (int)type;

	bool mem = true;
	size_t totalSize = pVar->var_.saveToMemory(NULL, 0, mem);
	packet.reserve(packet.getPosition() + totalSize);

	size_t savesize = pVar->var_.saveToMemory(packet.getOffsetPtr(), packet.getAvaliableBufLen(), mem);

	if (savesize != totalSize)
	{
		OutputMsg(rmWarning, ("SysVarMgr saveSysVar id=%d, the var data too large"), ownerId);
	}

	packet.adjustOffset(savesize);

	db->flushProtoPacket(packet);
}

void SysVarMgr::reloadSysVar()
{
	static ScriptNpc* npc = GetGameEngine()->GetGlobalNpc();

	for (int i = 0; i < list_.count(); ++i)
	{
		SysVar* pVar = getPtrByHandle(list_[i]);

		if (pVar != NULL)
		{
			ScriptValueList vl;
			vl << pVar->id_
			   << pVar->name_
			   << pVar->sysId_
			   << (unsigned int)list_[i];
			npc->GetScript().Call("OnSysVarDbReturnData", &vl, &vl);
		}
	}
}

void SysVarMgr::Destroy()
{
	clearSysVar();
	int count = tmpList_.count();
	for (int i = 0; i < count; ++i)
	{
		CLVariant* var = tmpList_[i];
		delete var;
		tmpList_[i] = NULL;
	}
	tmpList_.clear();
}

void SysVarMgr::clearSysVar()
{
	for (int i = 0; i < list_.count(); ++i)
	{
		SysVar* pVar = getPtrByHandle(list_[i]);

		if (pVar != NULL)
			mgr_.Free(pVar);
	}

	list_.clear();
}

