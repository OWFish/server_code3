#include "StdAfx.h"
#include "db/item_data.h"


#include <chrono>
#include <string>
using namespace InterSrvComm::DbServerProto;


bool DBSession::SaveBagData(DataPacketReader& inPacket, SQLConnection& sql)
{

	auto start = std::chrono::steady_clock::now();
	ActorId actor_id = 0;
	int bag_type = 0;
	inPacket >> actor_id >> bag_type; 

	//int nRetID = 0;

	int err = reSucc;

	if (!sql.Connected()) {
		OutputMsg(rmError, "on save bag .db not connected");
		//err = reDbNotConnected; //db没有连接上
		return false;
	}

	err = sql.Exec(sql_cleanitem, actor_id, bag_type);

	if (!err) {
		sql.ResetQuery(); //函数调用里没有重置数据的
	} else {
		OutputMsg(rmError, "on save bag .db not connected");
		return false;
	}


	OutputMsg(rmNormal, "%lld start", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count());

	start = std::chrono::steady_clock::now();
	strcpy(huge_buf_s, sql_saveitem);
	char databuf[2048];
	char fieldbuf[1024];
	ItemData item_data;
	STATIC_ASSERT(sizeof(ItemData) < 2048);
	int i = 0;
	for (; inPacket.getAvaliableLength() >= sizeof(item_data); ++i)
	{
		inPacket >> item_data;

		//"(uid,actorid,bag_type,id, count, attrs)"
		strcpy(databuf, "(");
		FirstLInt(item_data.uid);
		AddInt(actor_id);
		AddInt(bag_type);
		AddInt(item_data.id);
		AddInt(item_data.count);
		AddData(item_data.attr_data, sizeof(item_data.attr_data));

		strcat(databuf, ")");
		if (i > 0)
			strcat(huge_buf_s, ",");
		strcat(huge_buf_s, databuf);
	}
	//inPacket.setPosition(0);
	if(i != 0) {
		err = sql.RealExec(huge_buf_s, strlen(huge_buf_s));
		if (!err) {
			sql.ResetQuery();
			OutputMsg(rmNormal, "%lld end--- %d", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count(), i);
			return true;
		}
		OutputMsg(rmError, "sql_save items failed; %s", huge_buf_s);
	}
	return false;
}

void DBSession::QueryBagData(ActorId actorid)
{
	QueryBagData(actorid, BagType_Item);
	QueryBagData(actorid, BagType_Equip);
	QueryBagData(actorid, BagType_Depot);
}

inline int GetCacheType(int bagType)
{
	switch (bagType)
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
	return -1;
}


void DBSession::QueryBagData(ActorId actorid, int bagType)
{
	int cache_type = GetCacheType(bagType);
	if (cache_type == -1) return;
	auto get_cache = [&]()
	{
		client_mgr_->LockCache();
		auto *pack = client_mgr_->GetCache()->GetReadableData(actorid, cache_type);
		if (!pack)
		{
			client_mgr_->UnLockCache();
			return false;
		}
		pack->setPosition(0);

		{
			ActorId id;
			int bt;
			(*pack) >> id >> bt;
		}
		if (pack->getAvaliableLength() == 0)
		{
			DataPacket &retPack = allocProtoPacket(MAKEINT16(siActor, dcLoadItem));
			retPack << actorid << (uint8_t)reSucc << bagType << (uint32_t)0<<(uint32_t)0<<(uint32_t)0;
			flushProtoPacket(retPack);
		}
		else
		{
			for (uint32_t i = 0; i < pack->getAvaliableLength(); i += PACK_LEN)
			{
				DataPacket &retPack = allocProtoPacket(MAKEINT16(siActor, dcLoadItem));
				retPack << actorid << (uint8_t)reSucc << bagType << (uint32_t)i;
				if ((i + PACK_LEN) > pack->getAvaliableLength())
				{
					retPack << (uint32_t)pack->getAvaliableLength() - i;
				}
				else
				{
					retPack << (uint32_t)PACK_LEN;
				}
				retPack << (uint32_t)pack->getAvaliableLength();
				if ((i + PACK_LEN) > pack->getAvaliableLength())
				{
					retPack.writeBuf(pack->getOffsetPtr() + i, pack->getAvaliableLength() - i);
				}
				else
				{
					retPack.writeBuf(pack->getOffsetPtr() + i, PACK_LEN);
				}

				flushProtoPacket(retPack);

			}
		}
		
		
		pack->setPosition(0);
		client_mgr_->UnLockCache();
		return true;
	};
	if (get_cache())
	{
		return;
	}
	else
	{
		int errId = reSucc;
		//数据库连接是否就绪
		if (!sql_->Connected())
		{
			errId = reDbErr;
		}
		else
		{
			errId = sql_->Query(sql_loaditem, actorid, bagType);

			if (!errId)
			{
				client_mgr_->LockCache();
				DataPacket& pack = *client_mgr_->GetCache()->UpdateCache(actorid, cache_type,
					NULL, 0, false);
				pack.setPosition(0);
				pack << actorid<<bagType;
				BEGIN_GET_ROW();
				int i = 0;
				ItemData item_data;
				while (pRow)
				{
					//"(uid,actorid,bag_type,id, count, attrs)"
					memset(&item_data, 0, sizeof(ItemData));
					GetLIntRow(0, item_data.uid);
					GetIntRow(3, item_data.id);
					GetIntRow(4, item_data.count);
					GetDataRow(5, item_data.attr_data);
					pack << item_data;

					pRow = sql_->NextRow();
					GET_NEXT_FIELD_LENGTH();
					++i;
				}
				sql_->ResetQuery();
				pack.setPosition(0);

				client_mgr_->UnLockCache();
				get_cache();
				OutputMsg(rmTip, "bag_type %d size %d",bagType, i);
				return;
			}
			else
			{
				OutputMsg(rmError, ("%s load item data failed,%d %d"), __FUNCTION__, actorid, bagType);
				errId = reDbErr;
			}
		}

		if (errId != reSucc)
		{
			OutputMsg(rmError, ("%s load item data failed,%d %d"), __FUNCTION__, actorid, bagType);
			DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcLoadItem));
			retPack << actorid << (uint8_t)errId << bagType;
			flushProtoPacket(retPack);
		}

	}

	return;
}
