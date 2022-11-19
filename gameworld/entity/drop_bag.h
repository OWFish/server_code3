#ifndef _DROP_BAG_H_
#define _DROP_BAG_H_

class DropBag:
	public Entity
{
public:
	typedef Entity Inherited;

public:
	DropBag();
	virtual ~DropBag() {}

	
	/*//初始化
	param:
		int type : 奖励类型
		int id : 奖励类型对应的ID
		int count : 掉落包里奖励数量
		ActorId belong_id : 所属者角色ID def: 0
		int beinvtime : 所属失效时长(秒) def: 0 不失效
		int destrtime : 掉落物小事时长(秒) def: 300
	return:
		bool 返回掉落物初始化是否成功
	*/
	inline bool Init(int type, int id, int count, ActorId belong_id = 0, int beinvtime = 0, int destrtime = 300)
	{
		if (count <= 0) return false;
		type_ = type;
		id_ = id;
		count_ = count;
		//flag_ = false;
		belong_id_ = belong_id;
		int64_t s = _getTickCount();
		if (beinvtime) belong_invalid_time_ = s + beinvtime * 1000;
		destroy_time_ = s + destrtime * 1000;
		return true;
	}

	//处理LogicRun，实现对脚本的内存定时回收
	void LogicRun(int64_t curr_t);

	virtual int GetId();
	inline ActorId GetBelongId() { return belong_id_; }
	bool GetDrop(Actor *actor);
	bool CanGetDrop(Actor *actor);
	virtual void CreateAppearData(DataPacket& appearPack);
	inline int GetRewardType() { return type_; }
	inline int GetRewardId() { return id_; }
	inline int GetRewardCount() { return count_; }

	//inline void SetFlag(bool flag) { flag_ = flag; }
	//inline bool GetFlag() { return flag_; }
private:
	int type_;
	int id_;
	int count_;
	ActorId belong_id_;//属于谁的
	int64_t belong_invalid_time_;//所属者失效时间
	int64_t destroy_time_;//消失时间
	//bool flag_;//标记是否有人把目标设置为它
};

#endif

