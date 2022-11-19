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

	//��Ӽ�¼
	void AddRecordByDB(int32_t actorid, ChallengeRecord recorddata);
	void AddRecordByScript(int32_t actorid , int32_t targetid, int32_t result, int32_t changerank, int32_t targetrank,int32_t recordtime);
	void DelRecord(std::map<int32_t, ChallengeRecord>& recordmap);

	//���а����
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

	//�Ƿ���������
	void NewSave(bool is_RightNow = false);
	void NewLoad();


	//�����ݼ���
	void LoadOldData();
	void LoadRankByDB(int32_t actorid, int32_t irank);

private:
	//��ս��¼ < ���id �� < ��¼ʱ�� ����ս��¼ > >
	std::unordered_map<int32_t, std::map<int32_t, ChallengeRecord> > _mChallengeRecord;
	//���а� < ���� �� ���id >
	std::map<int32_t, int32_t > _PVMRank;

	//���а�ӳ�����id
	std::map<int32_t, int32_t> _PlayerIndex;
	//�����ݻ���
	std::map<int32_t , std::vector<int32_t>> _DataCache;
	//��ɾ���ļ�¼
	std::map<int32_t, int32_t> _DelDataCache;

	time_t _SaveTime;
	time_t _OldTime;
	int next_save_time_;
	int RecordMaxCount;
	int ChangeFlag; //���±�ʶ
	int oldFlag;
};

#endif
