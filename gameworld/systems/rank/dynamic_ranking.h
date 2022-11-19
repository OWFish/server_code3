#pragma once
#ifndef _RANKING_H_
#define _RANKING_H_

/********************************************
*
*	排行榜类，主要导出给脚本使用
*
*********************************************/
class DynamicRankingMgr;
class DynamicRanking;

typedef ActorId RankItemId;

//排行榜项，每项表示一个用户的分值，每个排行榜由多个排行榜项组成
class RankingItem
{
	friend class DynamicRanking;
public:
	RankingItem();
	virtual ~RankingItem();

	//设置某列的数据
	void SetSub(int idx, const char* data);
	//设置列数
	void SetColCount(int count);
	//在指定的列前增加一列.-1表示在最后插入
	void AddColumn(const char* data, int idx = -1);
	//设置列的标题
	void SetColumnTitle(const char* data, int idx);
	//删除某列的数据
	void RemoveColumn(int idx);

	inline void SetId(RankItemId id) { id_ = id; }
	inline RankItemId GetId() { return id_; }
	inline int GetPoint() { return point_; }
	inline void SetPoint(int point) { point_ = point; }
	inline int GetIndex() { return idx_; }
	inline int GetColCount() { return col_; }
	//获取某列的数据
	const char* GetSubData(int idx);

private:
	RankItemId id_;	//唯一值，可以是角色id或者帮派id等
	int		point_; //分数,排行榜根据这个排序
	char**	cd_;	//每列的数据内容，每列都是字符串类型，主要用于显示
	int		col_;	//列的数目
	int		max_col_;	//最大列
	int		idx_;		//自身在排行榜的位置,0是第一位
	DynamicRanking* rank_; // 所在的排行榜
};

//排行榜类
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

	// 排行可见类型
	enum RankVisibleType
	{
		enVisible_All,				// 世界所有玩家
		//enVisible_SameCamp,			// 同阵营玩家
		//enVisible_SameGuild,		// 同公会玩家
		//enVisible_SameTeam,			// 同队伍
	};
	// 排行可见参数
	struct RankVisibleParam
	{
		union
		{
			int		camp_id_;		// 阵营Id
			int		guild_id_;		// 公会id
			int		team_id_;		// 队伍Id
		} data;
	};

public:
	DynamicRanking(const char* name, int max_item, bool display);
	virtual ~DynamicRanking();


public:
	//继承基类，释放资源，如果引用计数器没到0，不能释放内存
	//virtual int release();
	virtual void destroy();

	/*
	* Comments:从文件读取排行榜数据，如果原来已经读取过一次，会全部清除掉；文件名根据m_szName
	* @Return bool:成功读取返回true
	*/
	bool Load(const char* file);
	/*
	* Comments:增加一列
	* Param const char* sTitle:标题
	* Param int nIndex:在本索引前插入,-1表示最后增加
	* @Return bool:
	*/
	void AddColumn(const char* title, int idx);
	/*
	* Comments: 设置列标题
	* Param const char* sTitle: 标题
	* Param int nIndex: 列的索引
	* @Return void:
	*/
	void SetColumnTitle(const char* title, int idx);
	/*
	* Comments:删除一列
	* Param int nIndex:列的索引
	* @Return void:
	*/
	void RemoveColumn(int idx);
	/*
	* Comments:保存数据
	* @Return void:
	*/
	void Save(const char* file);
	/*
	* Comments:清除所有数据
	* freeItem:是否释放内存
	* @Return void:
	*/
	void clear(bool freeItem = true);
	//获取列的数量
	inline int ColumnCount() { return title_.GetColCount(); }

	/*
	* Comments:尝试增加一个排行榜项
	* Param int nId:id值
	* Param int nPoints:初始的分值
	* @Return CRankingItem*:如果在名次内返回排行榜项，否则返回NULL,如果已经存在对应的id，会加入失败
	*/
	RankingItem* TryAddItem(RankItemId id, int point);
	/*
	* Comments:增加一个排行榜项
	* Param int nId:id值
	* Param int nPoints:初始的分值
	* @Return CRankingItem*:成功返回排行榜项，否则返回NULL,如果已经存在对应的id，会加入失败
	*/
	RankingItem* AddItem(RankItemId id, int point);

	// 增加一个排行榜项
	int AddItem(RankingItem* itemPtr);

	/*
	* Comments:给某个id增加分值
	* Param int nId:排行榜项的id
	* Param int nPoint:分值，负数表示减少
	* @Return CRankingItem*:非NULL表示成功
	*/
	RankingItem* Update(RankItemId id, int point);

	/*
	* Comments:直接设置某个id的分值
	* Param int nId:排行榜项的id
	* Param int nPoint:分值
	* @Return CRankingItem*:非NULL表示成功
	*/
	RankingItem* Set(RankItemId id, int point);

	//获取列表
	inline Vector<RankingItem*>& GetList() { return itemList_; }

	/*
	* Comments:删除指定的id
	* Param int nId:
	* @Return void:
	*/
	void RemoveId(RankItemId id);

	////设置上榜的最多人数,要重新排序
	//void SetRankMax(int nCount);

	/*
	* Comments:根据索引获取某一项，用户改变列字符串的数值，不能在这里改变分值
	* Param int nIndex:在排行榜的位置
	* @Return CRankingItem*:位置不正确会返回NULL
	*/
	RankingItem* GetItem(int idx);

	/*
	* Comments:把该项插到排行榜中,向上更新位置
	* Param CRankingItem * pItem:
	* @Return int:返回在排行榜中的位置
	*/
	int UpdateUpPos(RankingItem* item);

	/*
	* Comments:把该项插到排行榜中,向下更新位置
	* Param CRankingItem * pItem:
	* @Return int:返回在排行榜中的位置
	*/
	int UpdateDownPos(RankingItem* item);

	/*
	* Comments:获取某个id在排行榜中的位置，第一位是0，不在这个
	* Param int nId:
	* @Return int:
	*/
	int GetIndexFromId(RankItemId id, int& id_index);

	/*
	* Comments:根据id获取指针
	* Param int nId:
	* @Return CRankingItem*:
	*/
	RankingItem* GetPtrFromId(RankItemId id);


	//在榜外找个最大的，上榜
	RankingItem* FindMaxItem();
	inline const char* GetName() { return name_; }
	inline int GetMax() { return rank_max_; }
	inline int GetColCount() { return title_.GetColCount(); }

	/*
	* Comments:设置某列是否显示在客户端
	* Param int nIndex:列数
	* Param bool disp:是否显示
	* @Return void:
	*/
	void SetColDisplay(int idx, bool disp);

	/*
	* Comments:判断该列是否显示
	* Param int nIndex:列索引
	* @Return bool:显示返回true
	*/
	bool IsColDisplay(int idx);

	//是否发到客户端显示
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

		// 这些暂时还没实现！ 以后需要的时候，按照上面的方式实现下就行了！
		case enVisible_SameGuild:
		case enVisible_SameTeam:
			break;
		*/
		}

		return display_ & visible;
	}

	//设置在客户端显示的名称
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
	//获取在客户端显示的名称
	inline const char* GetDisplayName() { return cn_name_; }
	//获取标题
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

	//是否有数据改变
	inline bool IsModify() { return modify_; }

	inline void SetModify() { modify_ = true; }

	inline bool IsAutoSave() { return autosave_; }

	inline void SetAutoSave(bool as) { autosave_ = as; }

	// 两个积分相等的项交换
	void SwapEqualItem(RankingItem* item1, RankingItem* item2);

	inline const char* GetFileName() const { return file_; }

	inline void SetFileName(const char* name)
	{
		if (name == NULL) return;
		_STRNCPY_A(file_, name);
	}

private:
	//保存每项数据到文件中
	void SaveItem(RankingItem* item, FILE* fp);
	//把新id插入到索引中
	void InsertId(tagIndex& IndexItem);
	//两项交换位置
	void SwapItem(RankingItem* ri, RankingItem* item);

private:
	char							name_[32];	//排行榜的名字，脚本通过这个名字访问排行榜，同时也是用这个名字作为文件保存
	char							cn_name_[32];	//排行榜的中文名，主要显示在客户端的

	char							id_title_[32];	//id的标题文字
	char							point_title_[32]; //分值的标题文字

	RankingItem						title_;	//这个项用来表示标题
	Vector<RankingItem*>			itemList_;	//保存所有的列表
	Vector<tagIndex>				index_;	//索引表，根据id排序，查找时根据二分查找
	int								rank_max_;	//上榜的最多人数
	uint8_t							col_display_[255];	//表示第几列是否显示在客户端，0表示显示，默认是0，非0表示不显示
	bool							display_;			//表示是否显示

	RankVisibleParam				rankVisibleParam_;				// 排行榜可见类型相关的参数。例如阵营相关的排行，这里存放可见排行的阵营ID
	RankVisibleType					rankVisibleType_;				// 排行榜可见类型
	bool							modify_;	//是否修改过数据

	char							file_[256];	//保存的文件
	bool							autosave_; // 是否定时自动保存
};


#endif

