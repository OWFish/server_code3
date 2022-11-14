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

	
	/*//��ʼ��
	param:
		int type : ��������
		int id : �������Ͷ�Ӧ��ID
		int count : ������ｱ������
		ActorId belong_id : �����߽�ɫID def: 0
		int beinvtime : ����ʧЧʱ��(��) def: 0 ��ʧЧ
		int destrtime : ������С��ʱ��(��) def: 300
	return:
		bool ���ص������ʼ���Ƿ�ɹ�
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

	//����LogicRun��ʵ�ֶԽű����ڴ涨ʱ����
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
	ActorId belong_id_;//����˭��
	int64_t belong_invalid_time_;//������ʧЧʱ��
	int64_t destroy_time_;//��ʧʱ��
	//bool flag_;//����Ƿ����˰�Ŀ������Ϊ��
};

#endif

