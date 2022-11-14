#pragma once

/********************************************
*
*	排行榜管理器
*
*********************************************/
class DynamicRanking;

class DynamicRankingMgr
{
public:
	typedef Vector<DynamicRanking*> RankingList;

public:
	static const int MAX_RANKING = 512;

	/*
	* Comments:获取一个排行榜
	* Param const char* name:排行榜的名称
	* @Return CRanking*:没有找到返回NULL
	*/
	DynamicRanking* GetRanking(const char* name);

	/*
	* Comments:删除排行榜
	* Param const char* name:排行榜的名称
	* @Return void:
	*/
	void Remove(const char* name);

	/*
	* Comments:增加一个排行榜
	* Param const char* name:排行榜的名称
	* @Return CRanking*:如果已经存在，返回NULL
	*/
	DynamicRanking* Add(const char* name, int maxitem, int display);

	//获取列表
	RankingList& GetList()
	{
		return ranking_array_;
	}

	//向所有玩家发送通知，排行榜改变了
	void NotifyUpdate();

	//释放资源
	void Destroy();

	/*
	* Comments:定期检查是否有信息需要保存
	* @Return void:
	*/
	void RunOne(int64_t now_t);
public:
	DynamicRankingMgr();
	virtual ~DynamicRankingMgr();
	bool Initialize()
	{
		allocator_->SetMultiThread(false);
		return true;
	}
public:
	static 	RankAlloc* allocator_;	//排行榜统一的内存分配器
private:
	Timer saveTime_;	//2个小时保存一次

						// 全部的排行榜用数组和hash表存储，hash表是为了加快查询的速度。两个表要保持数据一致
	Vector<DynamicRanking*> ranking_array_;//全服的排行榜的列表,根据名字查找
	StaticHashTable<DynamicRanking*, MAX_RANKING>	ranking_table_; //排行榜的列表,以名字(转整数)做哈希
};


