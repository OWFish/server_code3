#pragma once
#ifndef _RANKING_H_
#define _RANKING_H_

/********************************************
*
*	���а��࣬��Ҫ�������ű�ʹ��
*
*********************************************/
class DynamicRankingMgr;
class DynamicRanking;

typedef ActorId RankItemId;

//���а��ÿ���ʾһ���û��ķ�ֵ��ÿ�����а��ɶ�����а������
class RankingItem
{
	friend class DynamicRanking;
public:
	RankingItem();
	virtual ~RankingItem();

	//����ĳ�е�����
	void SetSub(int idx, const char* data);
	//��������
	void SetColCount(int count);
	//��ָ������ǰ����һ��.-1��ʾ��������
	void AddColumn(const char* data, int idx = -1);
	//�����еı���
	void SetColumnTitle(const char* data, int idx);
	//ɾ��ĳ�е�����
	void RemoveColumn(int idx);

	inline void SetId(RankItemId id) { id_ = id; }
	inline RankItemId GetId() { return id_; }
	inline int GetPoint() { return point_; }
	inline void SetPoint(int point) { point_ = point; }
	inline int GetIndex() { return idx_; }
	inline int GetColCount() { return col_; }
	//��ȡĳ�е�����
	const char* GetSubData(int idx);

private:
	RankItemId id_;	//Ψһֵ�������ǽ�ɫid���߰���id��
	int		point_; //����,���а�����������
	char**	cd_;	//ÿ�е��������ݣ�ÿ�ж����ַ������ͣ���Ҫ������ʾ
	int		col_;	//�е���Ŀ
	int		max_col_;	//�����
	int		idx_;		//���������а��λ��,0�ǵ�һλ
	DynamicRanking* rank_; // ���ڵ����а�
};

//���а���
class DynamicRanking :
	public ObjectRef
{
public:
	struct tagIndex
	{
	public:
		RankItemId			id_;
		RankingItem*		item_;
	};

	// ���пɼ�����
	enum RankVisibleType
	{
		enVisible_All,				// �����������
		//enVisible_SameCamp,			// ͬ��Ӫ���
		//enVisible_SameGuild,		// ͬ�������
		//enVisible_SameTeam,			// ͬ����
	};
	// ���пɼ�����
	struct RankVisibleParam
	{
		union
		{
			int		camp_id_;		// ��ӪId
			int		guild_id_;		// ����id
			int		team_id_;		// ����Id
		} data;
	};

public:
	DynamicRanking(const char* name, int max_item, bool display);
	virtual ~DynamicRanking();


public:
	//�̳л��࣬�ͷ���Դ��������ü�����û��0�������ͷ��ڴ�
	//virtual int release();
	virtual void destroy();

	/*
	* Comments:���ļ���ȡ���а����ݣ����ԭ���Ѿ���ȡ��һ�Σ���ȫ����������ļ�������m_szName
	* @Return bool:�ɹ���ȡ����true
	*/
	bool Load(const char* file);
	/*
	* Comments:����һ��
	* Param const char* sTitle:����
	* Param int nIndex:�ڱ�����ǰ����,-1��ʾ�������
	* @Return bool:
	*/
	void AddColumn(const char* title, int idx);
	/*
	* Comments: �����б���
	* Param const char* sTitle: ����
	* Param int nIndex: �е�����
	* @Return void:
	*/
	void SetColumnTitle(const char* title, int idx);
	/*
	* Comments:ɾ��һ��
	* Param int nIndex:�е�����
	* @Return void:
	*/
	void RemoveColumn(int idx);
	/*
	* Comments:��������
	* @Return void:
	*/
	void Save(const char* file);
	/*
	* Comments:�����������
	* freeItem:�Ƿ��ͷ��ڴ�
	* @Return void:
	*/
	void clear(bool freeItem = true);
	//��ȡ�е�����
	inline int ColumnCount() { return title_.GetColCount(); }

	/*
	* Comments:��������һ�����а���
	* Param int nId:idֵ
	* Param int nPoints:��ʼ�ķ�ֵ
	* @Return CRankingItem*:����������ڷ������а�����򷵻�NULL,����Ѿ����ڶ�Ӧ��id�������ʧ��
	*/
	RankingItem* TryAddItem(RankItemId id, int point);
	/*
	* Comments:����һ�����а���
	* Param int nId:idֵ
	* Param int nPoints:��ʼ�ķ�ֵ
	* @Return CRankingItem*:�ɹ��������а�����򷵻�NULL,����Ѿ����ڶ�Ӧ��id�������ʧ��
	*/
	RankingItem* AddItem(RankItemId id, int point);

	// ����һ�����а���
	int AddItem(RankingItem* itemPtr);

	/*
	* Comments:��ĳ��id���ӷ�ֵ
	* Param int nId:���а����id
	* Param int nPoint:��ֵ��������ʾ����
	* @Return CRankingItem*:��NULL��ʾ�ɹ�
	*/
	RankingItem* Update(RankItemId id, int point);

	/*
	* Comments:ֱ������ĳ��id�ķ�ֵ
	* Param int nId:���а����id
	* Param int nPoint:��ֵ
	* @Return CRankingItem*:��NULL��ʾ�ɹ�
	*/
	RankingItem* Set(RankItemId id, int point);

	//��ȡ�б�
	inline Vector<RankingItem*>& GetList() { return itemList_; }

	/*
	* Comments:ɾ��ָ����id
	* Param int nId:
	* @Return void:
	*/
	void RemoveId(RankItemId id);

	////�����ϰ���������,Ҫ��������
	//void SetRankMax(int nCount);

	/*
	* Comments:����������ȡĳһ��û��ı����ַ�������ֵ������������ı��ֵ
	* Param int nIndex:�����а��λ��
	* @Return CRankingItem*:λ�ò���ȷ�᷵��NULL
	*/
	RankingItem* GetItem(int idx);

	/*
	* Comments:�Ѹ���嵽���а���,���ϸ���λ��
	* Param CRankingItem * pItem:
	* @Return int:���������а��е�λ��
	*/
	int UpdateUpPos(RankingItem* item);

	/*
	* Comments:�Ѹ���嵽���а���,���¸���λ��
	* Param CRankingItem * pItem:
	* @Return int:���������а��е�λ��
	*/
	int UpdateDownPos(RankingItem* item);

	/*
	* Comments:��ȡĳ��id�����а��е�λ�ã���һλ��0���������
	* Param int nId:
	* @Return int:
	*/
	int GetIndexFromId(RankItemId id, int& id_index);

	/*
	* Comments:����id��ȡָ��
	* Param int nId:
	* @Return CRankingItem*:
	*/
	RankingItem* GetPtrFromId(RankItemId id);


	//�ڰ����Ҹ����ģ��ϰ�
	RankingItem* FindMaxItem();
	inline const char* GetName() { return name_; }
	inline int GetMax() { return rank_max_; }
	inline int GetColCount() { return title_.GetColCount(); }

	/*
	* Comments:����ĳ���Ƿ���ʾ�ڿͻ���
	* Param int nIndex:����
	* Param bool disp:�Ƿ���ʾ
	* @Return void:
	*/
	void SetColDisplay(int idx, bool disp);

	/*
	* Comments:�жϸ����Ƿ���ʾ
	* Param int nIndex:������
	* @Return bool:��ʾ����true
	*/
	bool IsColDisplay(int idx);

	//�Ƿ񷢵��ͻ�����ʾ
	inline bool IsDisplay(Actor* actor)
	{
		bool visible = true;

		switch (rankVisibleType_)
		{
		case enVisible_All:
			visible = true;
			break;

		/*case enVisible_SameCamp:
		{
			if (actor && actor->GetIntProp(P_CAMP) != rankVisibleParam_.data.camp_id_)
				visible = false;
		}
		break;

		// ��Щ��ʱ��ûʵ�֣� �Ժ���Ҫ��ʱ�򣬰�������ķ�ʽʵ���¾����ˣ�
		case enVisible_SameGuild:
		case enVisible_SameTeam:
			break;
		*/
		}

		return display_ & visible;
	}

	//�����ڿͻ�����ʾ������
	inline void SetDisplayName(const char* name)
	{
		if (name)
		{
			_STRNCPY_A(cn_name_, name);
		}
		else
		{
			cn_name_[0] = 0;
		}
	}
	//��ȡ�ڿͻ�����ʾ������
	inline const char* GetDisplayName() { return cn_name_; }
	//��ȡ����
	inline RankingItem& GetTitle() { return title_; }

	inline const char* GetIdTitle() { return id_title_; }
	inline void SetIdTitle(const char* name)
	{
		if (name)
		{
			_STRNCPY_A(id_title_, name);
		}
		else
		{
			id_title_[0] = 0;
		}
	}

	inline const char* GetPointTitle() { return point_title_; }
	inline void SetPointTitle(const char* name)
	{
		if (name)
		{
			_STRNCPY_A(point_title_, name);
		}
		else
		{
			point_title_[0] = 0;
		}
	}

	inline void SetRankVisibleInfo(RankVisibleType vt, RankVisibleParam param)
	{
		rankVisibleType_ = vt;
		rankVisibleParam_ = param;
	}

	//�Ƿ������ݸı�
	inline bool IsModify() { return modify_; }

	inline void SetModify() { modify_ = true; }

	inline bool IsAutoSave() { return autosave_; }

	inline void SetAutoSave(bool as) { autosave_ = as; }

	// ����������ȵ����
	void SwapEqualItem(RankingItem* item1, RankingItem* item2);

	inline const char* GetFileName() const { return file_; }

	inline void SetFileName(const char* name)
	{
		if (name == NULL) return;
		_STRNCPY_A(file_, name);
	}

private:
	//����ÿ�����ݵ��ļ���
	void SaveItem(RankingItem* item, FILE* fp);
	//����id���뵽������
	void InsertId(tagIndex& IndexItem);
	//�����λ��
	void SwapItem(RankingItem* ri, RankingItem* item);

private:
	char							name_[32];	//���а�����֣��ű�ͨ��������ַ������а�ͬʱҲ�������������Ϊ�ļ�����
	char							cn_name_[32];	//���а������������Ҫ��ʾ�ڿͻ��˵�

	char							id_title_[32];	//id�ı�������
	char							point_title_[32]; //��ֵ�ı�������

	RankingItem						title_;	//�����������ʾ����
	Vector<RankingItem*>			itemList_;	//�������е��б�
	Vector<tagIndex>				index_;	//����������id���򣬲���ʱ���ݶ��ֲ���
	int								rank_max_;	//�ϰ���������
	uint8_t							col_display_[255];	//��ʾ�ڼ����Ƿ���ʾ�ڿͻ��ˣ�0��ʾ��ʾ��Ĭ����0����0��ʾ����ʾ
	bool							display_;			//��ʾ�Ƿ���ʾ

	RankVisibleParam				rankVisibleParam_;				// ���а�ɼ�������صĲ�����������Ӫ��ص����У������ſɼ����е���ӪID
	RankVisibleType					rankVisibleType_;				// ���а�ɼ�����
	bool							modify_;	//�Ƿ��޸Ĺ�����

	char							file_[256];	//������ļ�
	bool							autosave_; // �Ƿ�ʱ�Զ�����
};


#endif

