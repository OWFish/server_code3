#ifndef _LIANFU_RANK_H_
#define _LIANFU_RANK_H_

struct LianfuRankActor
{
	ActorId aid_; // 玩家ID
	int sid_; // 所在的服务器ID
	uint8_t rankNum_[rtMax];	// 在每个榜的排名，如果没排上，就是0

	void reset(ActorId aid) {
		aid_ = aid;
		ZeroMemory(rankNum_, sizeof(rankNum_));
	}
};

class LianfuRank
{
public:
	static const int MAX_RANK_ACTOR = RankDbItem::MAX_COUNT * rtMax;
public:
	LianfuRank();
	~LianfuRank();

public:
	// 获取总排行榜
	AllRankList* GetTotalRank() { return total_rank_; }

public:
	void ProcessNetData(int cmd, DataPacketReader& packet);

	// 排行榜已经刷新
	void OnUpdateRank();
	// 发送排行榜列表
	void SendRankList();

	// 查找玩家在总排行榜中的信息
	LianfuRankActor* FindRankActor(ActorId aid);

private:
	// 查找排行榜玩家，没有就分配一个
	LianfuRankActor* GetRankActor(ActorId aid);
	// 排行榜列表
	void HandleRankList(DataPacketReader& packet);
	//给在连服的玩家加或删除排行榜称号
	void GiveOrGiveupTitle(DataPacketReader& packet);

private:
	// 更新到总排行榜
	void UpdateRank();

private:
	bool rank_update_;

	AllRankList* total_rank_; // 连服排行榜
	StaticHashTable<LianfuRankActor*, MAX_RANK_ACTOR * 2> rank_actor_hash_; // 上榜的玩家信息
	StaticArrayList<LianfuRankActor, MAX_RANK_ACTOR> rank_actor_list_; // 上榜玩家信息,相当于分配器
};

#endif