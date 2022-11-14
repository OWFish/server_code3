#pragma once
#ifndef _TIANTI_MANAGER_H_
#define _TIANTI_MANAGER_H_

class Actor;

#include <unordered_map>
#include <map>
#include <set>
#include <vector>

struct ChallengeRecord
{
	int actor_id;
	int record_time;
	int result;
	int change_rank;
	int target_rank;
	int headimage;
	int job;
	long long int total_power;
	const char* actor_name;
	const char*  guild_name;

	void clear()
	{
		actor_id = 0;
		record_time = 0;
		result = 0;
		change_rank = 0;
		target_rank = 0;
		headimage = 0;
		total_power = 0;
		job = 0;
		actor_name = "";
		guild_name = "";
	}
};

class TianTiManger
{
private:
	TianTiManger();
	
public:
	~TianTiManger();

	static TianTiManger* GetInstance()
	{
		static TianTiManger tiantimgr;
		return &tiantimgr;
	}

	//添加记录
	void AddRecordByDB(int32_t actorid, ChallengeRecord recorddata);
	void AddRecordByScript(int32_t actorid , int32_t targetid, int32_t result, int32_t changerank, int32_t targetrank,int32_t recordtime);
	void DelRecord(std::map<int32_t, ChallengeRecord>& recordmap);

	//排行榜更新
	void UpdataRank(int32_t actorid , int32_t newrank);

	

	const ChallengeRecord* GetChallengeData(int32_t actorid, int32_t recordtime);
	int32_t GetPlayerRank(int32_t actor_id);


	std::map<int32_t, std::vector<int32_t>>& GetDataCache() { return _DataCache; }
	std::map<int32_t, int32_t>& GetDelDataCache() { return _DelDataCache; }

	void SaveRank(int irank , int iactorid);

	void SendRankToClient(Actor* pActor,int Limit,int flag);

	void SendChallengeRecordToClient(Actor* pActor);

	void InitRecordMaxCount(int max_count) { RecordMaxCount = max_count; }

	int GetRankByPlayerID(int actorid);

	int GetPlayerIDByRank(int rank);

	int GetRankSize() {
		return (int)_PVMRank.size();
	}

	//是否立即保存
	void NewSave(bool is_RightNow = false);
	void NewLoad();


	//旧数据兼容
	void LoadOldData();
	void LoadRankByDB(int32_t actorid, int32_t irank);

private:
	//对战记录 < 玩家id ， < 记录时间 ，对战记录 > >
	std::unordered_map<int32_t, std::map<int32_t, ChallengeRecord> > _mChallengeRecord;
	//排行榜 < 排名 ， 玩家id >
	std::map<int32_t, int32_t > _PVMRank;

	//排行榜映射玩家id
	std::map<int32_t, int32_t> _PlayerIndex;
	//脏数据缓存
	std::map<int32_t , std::vector<int32_t>> _DataCache;
	//带删除的记录
	std::map<int32_t, int32_t> _DelDataCache;

	time_t _SaveTime;
	time_t _OldTime;
	int next_save_time_;
	int RecordMaxCount;
	int ChangeFlag; //更新标识
	int oldFlag;
};

#endif
