#include "StdAfx.h"
#include "actor.h"

#include "role/role_system.h"
#include "item/container/item_bag.h"
#include "item/container/equip_bag.h"
#include "item/container/depot_system.h"
#include "mail/mail_system.h"
#include "zhuansheng/zhuansheng_system.h"
#include "store/store_system.h"
#include "title/title_system.h"
#include "guild/guild_system.h"
#include "offlinemsg/msg_system.h"
#include "togetherhit/together_hit_system.h"


void Actor::SaveDb(bool IsLogout)
{
	if (!inited_) return;

	DBClient* db = ServerInstance()->GetDbClient(serverId_);
	if (!db) return;

	static GameServer* srv = ServerInstance();
	//ActorBasicData *data = basic_data_; //实体的存盘数据
	if (srv->IsCommonSrv()) {
		DataPacket& dataPacket = db->allocProtoPacket(MAKEINT16(siActor, dcSave));
		dataPacket << actor_id_;

		ActorBasicData *data = basic_data_; //实体的存盘数据
		// ENTITYDATA包含了坐标的信息，实际上如果在战斗服中，这个坐标是不应该保存回去的,在savepos函数改回正确的坐标
		// 这个备注留着以后参考
		if (entity_pos_.scene) {
			basic_data_->fb_scene_id = entity_pos_.scene->GetId();
			basic_data_->fb_uid = entity_pos_.fuben->GetFbUId();
		}

		if (!IsImage()) {
			//保存在线时间
			static GameEngine* ge = GetGameEngine();
			unsigned int online_t = ge->getMiniDateTime() - data->last_online_time;
			data->last_online_time = ge->getMiniDateTime();
			data->total_online += online_t;
			data->daily_online += online_t;
		}

		var_sys_->Save(data);
		role_sys_->Save(data);
		item_bag_->Save(data);
		equip_bag_->Save(data);
		mail_sys_->Save(data);
		store_sys_->Save(data);
		zhuansheng_sys_->Save();
		depot_->Save(data);
		together_hit_sys_->Save(data);

		//GetSpecialDataForPhp(data);

		dataPacket.writeBuf(data, sizeof(ActorBasicData));
		db->flushProtoPacket(dataPacket);


		// todo dbsession onActorLogout
		if (IsLogout || waitForCross_) {
			DataPacket& pack = db->allocProtoPacket(MAKEINT16(siActor, dcLogout));
			int logoutData[] = { actor_id_,
				(int)data->level,
			};
			pack.writeBuf(logoutData, sizeof(logoutData));
			pack << (int)(data->job); //前面的人居然漏写了这个，如果我在最后加数据发到DB那就坑爹了
			pack << entity_name_;
			pack << (unsigned long long)0;// data.cw_fbhdl_sid_;
			pack << data->total_power;
			pack << data->rank_power;
			db->flushProtoPacket(pack);
		}
	}
	if (!IsImage()) {
		war_sys_->Save();
	}
	// 设置缓存为可读
	if (IsLogout && !IsImage()) // 那就和dcLogout一起做啊
	{
		SendDataValid(serverId_, actor_id_, true, cw_serverid_ != 0 ? cw_serverid_ : (kick_relogin_ ? serverId_ : 0));
	}
	//OutputMsg(rmError, "actor savedb:actorid=%d,%s", GetActorId(), IsImage() ? "image" : "real");
}


void Actor::OnDbReturnData(int cmd, DataPacketReader& reader)
{
	switch (cmd)
	{
	case dcLoad: //玩家基础数据
		if (IsInited()) return;

		if (!Init(reader.getOffsetPtr(), reader.getAvaliableLength()))
		{
			CloseActor("db init");		// 如果初始化失败就踢掉玩家

#ifdef OPENLOGTLOG
			static TlogMgr& tlog = GetGameEngine()->GetTlogMgr();
			tlog.LogOffline(*actor, OlServerKill);
#endif
		}

		break;
	case dcLoadRole:
	//	printf("-----------------size reader:%d", reader.getAvaliableLength());
	//	printf("-----------------size roledate:%d", sizeof(RoleDatas));
		GetRoleSystem()->Init(reader);
		break;

	case dcLoadItem:
	{
	   int type = 0;
	   reader >> type;
	   //OutputMsg(rmError, "--------- init bag %d",type);

	   if (type == BagType_Item)
		   GetItemBag()->Init(reader);
	   if (type == BagType_Equip)
		   GetEquipBag()->Init(reader);
	   if (type == BagType_Depot)
		   GetDepot()->Init(reader);
	   break;
	}
	case dcLoadMail:
	{
		GetMailSystem()->Init(reader);
		break;
	}
	case dcLoadStore:
	{
		GetStoreSystem()->Init(reader);
		break;
	}
	case dcLoadTogHitEquip:
	{
		GetTogetherHitSystem()->Init(reader);
		break;
	}
	case dcLoadVar:
		GetActorVarSystem()->Init(reader);
		GetTitleSystem()->Init();
		break;
	case dcLoadMsg:
		GetMsgSystem()->Init(reader);
		break;
	case dcLoadCsWarVar:
		GetWarSystem()->InitLuaVar(reader);
		break;
	case dcActorCacheLoad:
		if (!GetWarSystem()->LoadCsData(reader.getOffsetPtr(), reader.getAvaliableLength())) {
			OutputMsg(rmError, ("init actor cache data error!!!!!"));
		}
		break;
	}

}



void Actor::GetSpecialDataForPhp(ActorBasicData* data)
{
	/* 留作参考
	int mount_lvl = var_sys_.GetIntValue("sys.mount.level");
	int star = var_sys_.GetIntValue("sys.rootsys.level");
	int spirit = var_sys_.GetIntValue("sys.spirit.level");
	int live = var_sys_.GetIntValue("sys.liveness.total");
	int supertime = var_sys_.GetIntValue("superexptime.main.surplusTime");

	int wing_star = 0, wing_stage = 0;
	ItemData* item = equip_sys_.GetItemByType(Item::itWing);
	if (item)
	{
	wing_star = item->wing.stage_point;
	wing_stage = item->wing.stage;
	}

	SNPRINTFA(data.mis_for_php_, sizeof(data.mis_for_php_), ("mount:%d,star:%d,spirit:%d,live:%d,sutime:%d,wing1:%d,wing2:%d"), mount_lvl, star, spirit, live, supertime, wing_star, wing_stage);
	*/
}
