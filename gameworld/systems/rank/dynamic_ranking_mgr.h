#pragma once

/********************************************
*
*	���а������
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
	* Comments:��ȡһ�����а�
	* Param const char* name:���а������
	* @Return CRanking*:û���ҵ�����NULL
	*/
	DynamicRanking* GetRanking(const char* name);

	/*
	* Comments:ɾ�����а�
	* Param const char* name:���а������
	* @Return void:
	*/
	void Remove(const char* name);

	/*
	* Comments:����һ�����а�
	* Param const char* name:���а������
	* @Return CRanking*:����Ѿ����ڣ�����NULL
	*/
	DynamicRanking* Add(const char* name, int maxitem, int display);

	//��ȡ�б�
	RankingList& GetList()
	{
		return ranking_array_;
	}

	//��������ҷ���֪ͨ�����а�ı���
	void NotifyUpdate();

	//�ͷ���Դ
	void Destroy();

	/*
	* Comments:���ڼ���Ƿ�����Ϣ��Ҫ����
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
	static 	RankAlloc* allocator_;	//���а�ͳһ���ڴ������
private:
	Timer saveTime_;	//2��Сʱ����һ��

						// ȫ�������а��������hash��洢��hash����Ϊ�˼ӿ��ѯ���ٶȡ�������Ҫ��������һ��
	Vector<DynamicRanking*> ranking_array_;//ȫ�������а���б�,�������ֲ���
	StaticHashTable<DynamicRanking*, MAX_RANKING>	ranking_table_; //���а���б�,������(ת����)����ϣ
};


