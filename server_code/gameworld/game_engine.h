#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#include "os_def.h"
#include "lianfu/lf_netmsg_mgr.h"
#include "actor/global_mail_mgr.h"
#include "actor/tianti.h"
#include "../../common/redis/redis_def.h"
#include <memory>

class EntityMgr;
struct GlobalVar;
class FuBenMgr;
class AiMgr;
class ActorAsynMgr;
class ActorDataMgr;
class RankingSystem;
class LoginQueue;
class GlobalMailMgr;
class Tianti;
class GuildMgr;
class CRedisConnect;

#define GLOBAL_TIME_FLUCTUATE	20
#define GLOBAL_WEE_HOURS_TIME (22 * 60 * 60)

static const char* loadpvmrankdata = "call loadpvmrankdata()";
static const char* loadpvmchallengerecord = "call loadpvchallengerecord()";

class GameEngine :
	public thread::BaseThread
{
public:
	typedef BaseThread Inherited;
	typedef struct stCampTipData
	{
		void*		m_data;
		size_t		m_nLen;
	} CampTipData;

	typedef struct stCrossServerInfo
	{
		int sid; //������id
		int sType; //��������
		stCrossServerInfo(int id, int type)
		{
			sid = id;
			sType = type;
		}
	}CrossServerInfo;

	friend class LoginQueue;
public:
	static int64_t			game_tick_;
	//ȫ�ֹ��ܽű��ļ�·��
	static const char*		GlobalScriptFile;

	//static const int MAX_SERVER_ID = 65535; //���ķ���������public:
	GameEngine();
	~GameEngine();

	//�����߼�����
	bool StartEngine();
	//ֹͣ�߼�����
	void StopEngine();
	//�Ƿ��������
	bool IsStarted() { return started_; }

	/*
	* Comments:�ṩ�ӿڸ����ݷ��������ӵ��ã��������ϵ�ʱ��
	* @Return void:
	*/
	void InitComponent()
	{
		//guildMgr_.Load();
		//consignmentMgr_.Load();
		//db_rank_mgr_.Load();
		//miscMgr_.Load();
		//fight_mgr_.Load();
		sysvar_mgr_.Load();
		//dym_item_conf.Load();
		//gamewar_mgr_.Load();
	}

	// ���ÿ�������ݿ�������ݵ�ģ�飬�����Ƿ������ȫ
	inline bool isInitComponentFinished()
	{
		return sysvar_mgr_.isLoad();
		/*return guildMgr_.isLoaded()
		       && consignmentMgr_.isLoaded()
		       && db_rank_mgr_.isLoaded()
		       && miscMgr_.isLoaded()
		       && fight_mgr_.isLoad()
		       && sysvar_mgr_.isLoad()
		       && gamewar_mgr_.isLoaded()
		       && dym_item_conf.isLoad();
			   */
	}

	void ClearAllInterMsg();
	void ClearAllGameRoute();

	inline EntityMgr* GetEntityMgr(void) { return entity_mgr_; }
	inline ActorAsynMgr* GetActorAsynMgr(void) { return actor_asyn_mgr_; }
	inline ActorDataMgr* GetActorDataMgr(void) { return actor_data_mgr_; }
	inline LoginQueue* GetLoginQueue(void) { return login_queue_; }
	inline RankingSystem* GetRankingSystem(void) { return ranking_system_; }
	inline GuildMgr* GetGuildMgr(void) { return guild_mgr_; }
	//inline CampMgr& GetCampMgr() { return camp_mgr_; }
	//inline ConsignmentMgr& GetConsignmentMgr(void) { return consignmentMgr_; }
	inline FuBenMgr* GetFuBenMgr(void) { return fuben_mgr_; }
	inline ScriptNpc* GetReserveNpc() { return globalFuncNpc_rese_; }
	inline ScriptNpc* GetGlobalNpc() { return globalFuncNpc_; }
	//inline RankingMgr& GetRankingMgr() { return rankingMgr_; }
	inline GlobalVarMgr& GetGlobalVarMgr() { return globalVarMgr_; }
	//inline DbRankMgr& GetDbRankMgr() { return db_rank_mgr_; }
	//inline TeamMgr& GetTeamMgr() { return teamMgr_;    //��ȡ��������� }
	//inline MiscMgr& GetMiscMgr() { return miscMgr_; }
	inline MsgMgr& GetMsgMgr() { return msgMgr_; }
	inline Tianti& GetTianti(void) { return tianti_; }
	//inline DcApiMgr& GetDcApiMgr() { return dcapi_mgr_; }
	inline DKMLogMgr& GetDKMlogMgr() { return dkm_log_mgr_; }
	//inline DymItemConfig& getDymItemConf() { return dym_item_conf; }
	//inline GameWarMgr& GetGameWarMgr() { return gamewar_mgr_; }
	//inline FightMgr& GetFightMgr() { return fight_mgr_; }

	//�����û���Ʒ����boGenNewSeries�������ھ����Ƿ�����µ���Ʒϵ�к�
//#ifndef _MEMORY_TRACE_
//	inline ItemData* AllocUserItem(const bool isNew)
//	{
//		ItemData* item = isNew ? item_alloc_.allocItem() : item_alloc_.Alloc();
//		item->sign_data = NULL;
//		return item;
//	}
//	// �����û���Ʒ
//	inline void DestroyUserItem(ItemData* item)
//	{
//		if (item->sign_data)
//		{
//			global_var_->sign_data_alloc_.release(item->sign_data);
//			item->sign_data = NULL;
//		}
//
//		item_alloc_.Free(item);
//	}
//#else
//#define AllocUserItem(isNew) _AllocUserItem(isNew, __FILE__, __LINE__)
//#define DestroyUserItem(ptr) _DestroyUserItem(ptr, __FILE__, __LINE__)
//
//	inline ItemData* _AllocUserItem(const bool isNew, const char* fn, int line)
//	{
//		ItemData* item = isNew ? item_alloc_._allocItem(fn, line) : item_alloc_._Alloc(fn, line);
//		//item->sign_data = NULL;
//		return item;
//	}
//
//	// �����û���Ʒ
//	inline void _DestroyUserItem(ItemData* item, const char* fn, int line)
//	{
//		item_alloc_._Free(item, fn, line);
//	}
//#endif

//	inline int64_t AllocItemSeries() { return item_alloc_.allocSeries(); }

	/*
	* Comments: �����ű��¼���������
	* Param EntitySCBHandle & handle: SCB���
	* @Return ScriptCallbackParam*:
	*/
	ScriptEvent* AllocScriptEvent(SEventHandle& handle);


	/*
	* Comments: ���ٽű�ʱ���������
	* Param EntitySCBHandle & handle:
	* @Return void:
	*/
	void FreeScriptEvent(SEventHandle& handle);


	/*
	* Comments: ��ȡ�ű��ص�ʱ�����
	* Param const EntitySCBHandle & handle:
	* @Return ScriptCallbackParam*:
	*/
	ScriptEvent* GetScriptEvent(const SEventHandle& handle);

	//���붨ʱ��Ϣ
	/*inline TimeCallMsg* AllocMonsterActionTimeCall()
	{
		return monsterActionCallAlloc_.Alloc();
	}
	//���ٶ�ʱ��Ϣ
	inline void DestroyMonsterActionTimeCall(TimeCallMsg* pMsg)
	{
		monsterActionCallAlloc_.Free(pMsg);
	}*/

	//��ȡͬ����ϵͳ�߼����ں�ʱ��
	inline SystemTime& getSysTime() { return cur_sys_time_; }
	//��ȡͬ����ϵͳint64_t
	inline int64_t getTickCount() { return game_tick_; }
	//��ȡͬ�����߼�������ʱ��ֵ
	inline unsigned int getMiniDateTime() { return now_sec_; }
	/*
	* Comments: ��ȡһ�����������ʱ�õ�ǰ�ĵδ�������������ܻ����޸�
	* @Return int: ����һ�������
	*/
	inline unsigned int GetRandValue() { return wrandvalue(); }

	//����ai������
	inline AiMgr* GetAiMgr() { return ai_mgr_; }

	//���ض���������
	//inline ActionMgr& GetActionMgr() { return action_mgr_; }

	// ����ϵͳ����������
	inline SysVarMgr& GetSysVarMgr() { return sysvar_mgr_; }
	//��ȡ���ű��洢�Ķ�̬����
	inline CLVariant& GetDyanmicVar() { return dynamicVar_; }

	void SetGateMgr(GameGateMgr* gate_mgr) { gate_mgr_ = gate_mgr; }
	void PostMsg(GameInterMsg& msg);

	// ���Ӻ�ɾ��Ƶ����user,type 0 �����ӣ� 1 ��ɾ��
	void ChannelUser(int channelId, int para, Actor* actor, int type = 0);
	/*
	* Comments:ȫ�ֹ㲥
	* Param int channelId:Ƶ��id
	* Param int para:�����������������id
	* Param const char * buf:��������
	* Param int len:
	* @Returns void:
	*/
	void BroadCast(int channelId, int para, const char* buf, size_t len);

	// ȫ���㲥
	void BroadCast(const char* buff, size_t len);

	// ��ȡ��ʽ��������ݣ�������buf��
	int FormatTipmsg(char* buf, int size, const char* msg, int tipType);

	/*
	* Comments: ȫ����������
	* Param char * sTipmsg: tipmsg��ָ��
	* Param int nTipmsgType: �������ʾ���ͣ������������ǵ������
	* @Return void:
	*/
	void BroadcastTipmsg(const char* sTipmsg, int level, int nTipmsgType = ttTipmsgWindow);

	/*
	* Comments:������Ӫ��tipmsg
	* Param int nCampId:��Ӫ��id
	* Param char * sTipmsg: ��ʾ������
	* Param int nTipmsgType:��ʾ����ʾλ��
	* @Return void:
	*/
	void BroadcastCampTipmsg(int nCampId, const char* sTipmsg, int nTipmsgType = ttTipmsgWindow);
	/*
	* Comments:�������ɵ�tipmsg
	* Param int nCampId:���ɵ�id
	* Param char * sTipmsg: ��ʾ������
	* @Return void:
	*/
	void BroadcastGuildTipmsg(int guild, const char* sTipmsg);
	/*
	* Comments: ͨ��ID�㲥tipmsg
	* Param int nTipmsgID: ��ʾ��ID
	* Param int nTipmsgType: ��ʾ������
	* @Return void:
	*/
	void BroadcastTipmsgWithID(int nTipmsgID, int nTipmsgType = ttTipmsgWindow);

	// ��Ӫ�㲥
	void BroadCampTipmsgWithParams(int camp, int tip, int type = ttTipmsgWindow, ...);
	// ���ɹ㲥
	void BroadGuildTipmsgWithParams(int gid, int tip, int type = ttTipmsgWindow, ...);

	/*
	* Comments: ������ȫ���㲥
	* Param int nTipmsgID: ��ʾ��ID
	* Param int nTipmsgType: ��ʾ����ʾ����
	* Param char * sParam1:����1
	* Param char * sParam2:����2
	* Param char * sParam3:����3
	* @Return void:
	*/
	void BroadTipmsgWithParams(int tip, int type = ttTipmsgWindow, ...);

	/*
	* Comments:��ʽ��ϵͳ��ʾ���ַ���,����ӿڿ��Ը��ⲿʹ��
	* Param int nTipmsgID: ϵͳ��ʾ��ID
	* Param int nTipmsgType: ϵͳ��ʾ������
	* Param ...: �ɱ����
	* @Return int: �������ݳ���
	*/
	int FormatTipmsg(int nTipmsgID, va_list& args, int nTipmsgType = ttTipmsgWindow);

	/*
	* Comments: ͬ��Ӫ�㲥
	* Param int nOccupation: ��Ӫ����
	* Param char * pData: �㲥����
	* Param size_t size: �㲥���ݳ���
	* @Return void:
	*/
	inline void BroadCastCamp(int camp, const char* data, size_t size)
	{
		//if (camp <= zyNone || camp >= zyMax) return;

		//BroadCast(ciChannelCamp, camp, data, size);
	}

	/*
	* Comments: ͬ���ɹ㲥
	* Param int nOccupation: ��Ӫ����
	* Param char * pData: �㲥����
	* Param size_t size: �㲥���ݳ���
	* @Return void:
	*/
	/*inline void BroadCastGuild(int guildid, const char* data, size_t size)
	{
		Guild* guild = guildMgr_.FindGuild(guildid);
		if (guild)
			guild->BroadCast(data, size, true);
		else
			BroadCast(ciChannelGuild, guildid, data, size);
	}*/

	/*
	* Comments: �㲥��Ӫ��ʾ
	* Param const void * pData1:
	* Param size_t size1:
	* Param const void * pData2:
	* Param size_t size2:
	* Param const void * pData3:
	* Param size_t size3:
	* @Return void:
	* @Remark:
	*/
	inline void BroadCampTipmsg(CampTipData data[3])
	{
		//for (int i = 0; i < zyMax - 1; ++i)
		//{
		//	CampTipData* pData = &data[i];

		//	if (pData->m_data == NULL || pData->m_nLen <= 0) continue;

		//	BroadCast(ciChannelCamp, i + 1, (const char*)pData->m_data, (int)pData->m_nLen);
		//}
	}

	//��ȡ�㲥���ݵ�ָ��
	inline char* GetBroadcastDataPtr()
	{
		return broadcastBuff_;
	}

	// ����ĳ��������Ϣ��c++����������lua���������ǹر�ϵͳ�����pid==0����ʾsysid�����ж�����Ϊval
	void SetNetMsgRoute(int sysId, int pid, int val);
	// ����ĳ��db������Ϣ��c++����������lua����
	void SetDbRetRoute(int sysid, int cmd, int val);
	// �����ڴ��ͷ�
	void GC();
	void FreeMsgPack(GameInterMsg& msg);

	//void UpdateCrossGateway(DataPacket& dp);
	void SendActorCrossKey(DataPacket& dp, int sid, int loginType);

	void AddBattleSrv(int sid, int type)
	{
		if (!HasBattleSrv(sid))
		{
			CrossServerInfo info(sid, type);
			cross_server_list_.add(info);
		}
	}

	bool HasBattleSrv(int sid)
	{
		for (int i = 0; i < cross_server_list_.count(); ++i)
		{
			if (cross_server_list_[i].sid == sid)
				return true;
		}

		return false;
	}
	void RemoveBattleSrv(int sid)
	{
		for (int i = 0; i < cross_server_list_.count(); ++i)
		{
			if (cross_server_list_[i].sid == sid)
			{
				cross_server_list_.remove(i);
				return;
			}
		}
	}
	
	int GetSrvByType(int type)
	{
		for (int i = 0; i < cross_server_list_.count(); i++)
		{
			if (cross_server_list_[i].sType == type)
			{
				return cross_server_list_[i].sid;
			}
		}
		return 0;
	}

	void SetSrvType(int sid, int type)
	{
		for (int i = 0; i < cross_server_list_.count(); i++)
		{
			if (cross_server_list_[i].sid == sid)
			{
				cross_server_list_[i].sType = type;
				return;
			}
		}
	}


	// hdl����Ҫ֪ͨ����ҵ�handle����ˢ��npc�Ľű����֪ͨ�������ң�type��0��ʾȫ��npc��1��ʾ�����õ�ȫ��npc
	bool PostReloadGlobaNpc(EntityHandle hdl = 0, int type = 0);
	bool ReloadGlobalNpc(EntityHandle hdl = 0, int type = 0);

	/*
	* Comments:����һ���ַ�
	* Param INOUT char * pInput:������ַ���
	* @Return int:���������˵��ַ��ĸ���
	*/
	int Filter(char* pInput);

	/*
	* Comments: һ���ַ����Ƿ��г
	* Param char * pInput:�ַ���ָ��
	* @Return bool:��г����true�����򷵻�false
	*/
	bool IsStrInvalid(char* pInput);

	bool ReloadFilterDb(); //����װ�������ַ���

	// ��Ԫ����
	void RunAllTests();

	GameRoute* GetGameRoute(int sid, bool create = false);

	inline LianfuMgr& GetLianfuMgr() { return lianfu_mgr_; }

	inline LianfuRank& GetLianfuRank() { return lianfu_rank_; }

	//inline LianfuGuild& GetLianfuGuild() { return lianfu_guild_; }

	LFNetmsgMgr& GetLFNetmsgMgr() { return lf_netmsg_mgr_; }

	inline SQLConnection* GetGlobalSqlConn() { return &global_sql_; }

	inline GlobalMailMgr* GetGlobalMailMgr(){ return &global_mail_mgr_; }
	bool StartOneGameClient(const char* ip, int port, int serverId, int serverType);
	void ResetGameRoute();
	void ResetSingleGameRoute(int sid);

	void GameInit();
protected:
	void OnRoutine();
	//�����߼�����
	void LogicRun();
	//���ȫ���¼�ˢ��ʱ��
	void CheckRefreshTime();

	void MiscRun();


	//�߼��������������������߼��߳�����ʱ���ã�
	void EngineStarted();
	//�߼�����ֹͣ�����������߼��̼߳����˳�ǰ���ã�
	void EngineStoped();
private:
	//��ȫ�ֱ����ĳ�ʼ������
	void InitStaticVar();
	//�ͷų����е�ȫ�ֱ���
	void ReleaseStaticVar();

	void SetupSQLConnection(SQLConnection* sql);
private:
	//��ʼ���������� ???
	bool InitReserveScene();
	bool InitStaticFuben();
	//��ʼ������NPC
	bool InitReserveNpc();
	bool LoadActorBasicData();
	// �����̵߳��׺Ͷ�
	void ProcessSysMsg();
	void OnRecvSysMsg(GameInterMsg& msg);

	void OnAsynWorkerMsg(GameInterMsg& msg);

	void OnCrosswayKey(GameInterMsg& msg);

	//void OnGameSessionGw(GameInterMsg& msg);

	void OnGameSessionReg(GameInterMsg& msg);
	void OnGameClientResp(GameInterMsg& msg);
	void OnCloseActorById(GameInterMsg& msg);

	void OnGatewayDump(GameInterMsg& msg);
	void OnDbServerMsg(GameInterMsg& msg);
	void OnActorLogout(GameInterMsg& msg);
	//void OnActorLogin(GameInterMsg& msg);	//�ɰ棬 ���ڲ���Ϣ����
	void ActorLogin(GateUser* user, int serverId, const char* pf, const char* pfid, const char* appid); //��Ϊ�ߵ�½��������
	void OnCreateImageActor(GameInterMsg& msg);
	void OnCrossWarMsg(GameInterMsg& msg);
	void OnCenterServerMsg(GameInterMsg& msg);
	void OnRunAllTests(GameInterMsg&);

	void OnCrossServerTtMsg(GameInterMsg& msg);
	void OnChangeUserName(GameInterMsg& msg);
	void OnCrossRelogin(GameInterMsg& msg);
public:
	static CTimeStatisticMgr*		timeStatisticMgr_;     //ʱ��ͳ�����
	static GlobalVar*				global_var_;
	// ������Ϣת���ı�־�������1��ʾ�رգ�0��ʾc++������������lua����
	char							net_msg_route[256][256];
	// db������Ϣ������־ 0��ʾc++������������lua����
	char							db_ret_route[256][256];

	static void PostMsgToGE(void* cb);	// ��asyncworker�ص��ĺ���
	static void AsyncWorkLuaCallback(void* cb);	// asyncworkderִ�����Ļص�����

public:
	/*
	* Comments:�ܹ�ʵ�ֲ�����ʽ�����ܵķ���ϵͳ��ʾ��Ϣ
	* Param const char* sFormat: ��Ϣ��ʽ
	* Param int nType:  ϵͳ��ʾ��ʾ������
	* @Return void:
	*/
	void SendTipmsgWithArgs(ActorId sActorId, const char* fmt, va_list& args, int type);

	// ������Ϣ��ĳ����ң�������������������
	void SendTipmsg(ActorId sActorId, const char* sTipmsg, int type = ttTipmsgWindow);

	void SendTipWithId(ActorId sActorId, int msgid, int type = ttTipmsgWindow, ...);

	// ���ͼ����Ч�Ա�ʶ��DBServer
	void SendEnableCheckValid(bool flag);

	void ChangeToOnlineList(DataPacket& pack);
	//�������id ���ظ�������ĸ�������
	int GetActorInServerId(ActorId aid);

	void SetDbConfig(const char* host, int port, const char* db_name, const char* user, const char* pw);

	bool AddRoutes(int serverid, const char* host, int port);
	bool HasRoute(int serverId);

	void OnAddLoginList(GameInterMsg& msg);

	void SetRedisCfg(const char* host, int port, int db_index, const char* pw);

	std::shared_ptr<CRedisConnect> GetRedis() { return global_redis_; }

private:

	bool				started_;

	SystemTime			cur_sys_time_;			//��ǰϵͳ���ں�ʱ�䣬ÿ��ѭ������һ��
	GameGateMgr*		gate_mgr_;
	EntityMgr*			entity_mgr_;
	ActorAsynMgr*		actor_asyn_mgr_;	// �첽�ص�������
	ActorDataMgr*		actor_data_mgr_;	// ������ݹ���
	LoginQueue*			login_queue_;		// ��½����
	RankingSystem*		ranking_system_;		// ���а�ϵͳ
	GuildMgr*			guild_mgr_;			// ����ϵͳ
	//ConsignmentMgr		consignmentMgr_;
	//RankingMgr			rankingMgr_;	//���а������
	//CampMgr		camp_mgr_;
	GlobalVarMgr		globalVarMgr_;
	//DbRankMgr			db_rank_mgr_;
	//MiscMgr				miscMgr_;
	MsgMgr				msgMgr_;
	//DymItemConfig		dym_item_conf;

	FuBenMgr*			fuben_mgr_;
	SecondTime			now_sec_;		//��ǰ������ʱ��
	SecondTime			EventRefreshTime_;	// ����22���ˢ�´��������������߼���

	//TeamMgr				teamMgr_; //���������
	//ItemAllocator		item_alloc_;	//�û���Ʒ������

	//ObjPool<TimeCallMsg> monsterActionCallAlloc_; //���ﶯ����ʱ����

	GameMap				reserveMapData_;//���������ĵ�ͼ����
	Scene*				reserveScene_;//�������������ڴ�ű���NPC
	ScriptNpc*			globalFuncNpc_;	//ִ��ȫ�ֵĽű�����
	ScriptNpc*			globalFuncNpc_rese_;

	AiMgr*               ai_mgr_; //ai������
	//FightMgr			fight_mgr_; //������������

	SysVarMgr			sysvar_mgr_;

	CLVariant			dynamicVar_;		//һ���������ű�����ȫ�ֱ������ݵı��������ݲ�����db

	QueueList<GameInterMsg>	inter_msg_;		//�ڲ���Ϣ�б�
	Mutex				inter_msg_lock_;		//�ڲ���Ϣ�б���

	char				broadcastBuff_[4096]; //�㲥��Ϣ�õ�
	//ActionMgr			action_mgr_;	// ����������

	Timer				engine_report_t_;	// �����Ϸ���̵߳����ݿ��Ƿ�����
	Timer				engine_60s_t_; // ��ʱִ��event��ʱ��
	Timer				engine_5s_t_; // ��ʱִ��event��ʱ��
	Timer				gc_t_;			// �����ͷ��ڴ�ļ�ʱ��

	//DcApiMgr			dcapi_mgr_;
	DKMLogMgr			dkm_log_mgr_;
	//GameWarMgr			gamewar_mgr_;
	LianfuMgr			lianfu_mgr_;
	LianfuRank			lianfu_rank_;
	//LianfuGuild			lianfu_guild_;
	LFNetmsgMgr			lf_netmsg_mgr_;	//todo �Ժ�ĳ��������Ǹ��汾
	// ������
	// ����ÿ�����ӹ�����gameworld��gateway����Ϣ
	container::StaticArrayList<GameRoute*, MAX_SERVER_ID> gateway_routes_;

	Vector<CrossServerInfo, 4>		cross_server_list_;		// ս������id�б�
	ScriptEventHdlMgr		se_hdl_mgr_;	// ʵ��ű��ص��¼����������

	PFT_MBCS_CHAR				filterWords_;		//���δ��б�

	char			db_host_[128];			//���ݿ��ַ
	int				db_port_;				//���ݿ�˿�
	char			db_name_[128];			//���ݿ�����
	char			db_user_[128];			//���ݿ��û���
	char			db_pw_[128];			//���ݿ��û�����

	SQLConnection			global_sql_;

	std::shared_ptr<tg_redis_param> redis_config_;
	std::shared_ptr<CRedisConnect> global_redis_;

	GlobalMailMgr			global_mail_mgr_; //ȫ���ʼ�������
	Tianti					tianti_;  //����

public:
	// ������ֵĻ����ǵ����õģ���ʱ����ɾ��
	bool				script_5s_timer_;	// �Ƿ񴥷�5s��

	int					gc_actor_cnt_;		// ����gc����������

	container::StaticHashTable<int, 4096 * 4> actor_online_list_;//���������Ϣ
};

struct ActorIdPacket
{
	Actor* actor_; // Ŀ����ҵ�ָ��
	ActorId actor_id_;
	DataPacket dp_;

	ActorIdPacket();

	DataPacket& AllocIdPacket(ActorId aid, Actor* actor = NULL);
	void flush();

	static const int HEAD_SIZE = sizeof(int) + sizeof(ActorId);
};

#endif

