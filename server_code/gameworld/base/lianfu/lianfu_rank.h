#ifndef _LIANFU_RANK_H_
#define _LIANFU_RANK_H_

struct LianfuRankActor
{
	ActorId aid_; // ���ID
	int sid_; // ���ڵķ�����ID
	uint8_t rankNum_[rtMax];	// ��ÿ��������������û���ϣ�����0

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
	// ��ȡ�����а�
	AllRankList* GetTotalRank() { return total_rank_; }

public:
	void ProcessNetData(int cmd, DataPacketReader& packet);

	// ���а��Ѿ�ˢ��
	void OnUpdateRank();
	// �������а��б�
	void SendRankList();

	// ��������������а��е���Ϣ
	LianfuRankActor* FindRankActor(ActorId aid);

private:
	// �������а���ң�û�оͷ���һ��
	LianfuRankActor* GetRankActor(ActorId aid);
	// ���а��б�
	void HandleRankList(DataPacketReader& packet);
	//������������Ҽӻ�ɾ�����а�ƺ�
	void GiveOrGiveupTitle(DataPacketReader& packet);

private:
	// ���µ������а�
	void UpdateRank();

private:
	bool rank_update_;

	AllRankList* total_rank_; // �������а�
	StaticHashTable<LianfuRankActor*, MAX_RANK_ACTOR * 2> rank_actor_hash_; // �ϰ�������Ϣ
	StaticArrayList<LianfuRankActor, MAX_RANK_ACTOR> rank_actor_list_; // �ϰ������Ϣ,�൱�ڷ�����
};

#endif