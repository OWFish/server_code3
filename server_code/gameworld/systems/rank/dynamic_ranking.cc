#include "StdAfx.h"

#include "rank/ranking_system.h"
#include "dynamic_ranking.h"
#include "dynamic_ranking_mgr.h"



RankingItem::RankingItem()
	: id_(0)
	, point_(0)
	, cd_(NULL)
	, col_(0)
	, max_col_(0)
	, idx_(0)
	, rank_(NULL)
{
	//ZeroMemory(this, sizeof(*this));
}

RankingItem::~RankingItem()
{
	if (cd_)
	{
		for (int i = 0; i < col_; i++)
			DynamicRankingMgr::allocator_->FreeBuffer(cd_[i]);

		DynamicRankingMgr::allocator_->FreeBuffer(cd_);
	}
}

void RankingItem::AddColumn(const char* data, int idx)
{
	if (idx == -1)
	{
		SetColCount(col_ + 1);
		SetSub(col_ - 1, data);
	}
	else if (idx >= 0 && idx < col_)
	{
		SetColCount(col_ + 1);
		memmove(cd_ + (idx + 1), cd_ + idx, sizeof(char*) * (col_ - idx)); //列往后移
		cd_[idx] = NULL;
		SetSub(idx, data);
	}
}

void RankingItem::RemoveColumn(int idx)
{
	if (cd_ && idx >= 0 && idx < col_ && col_ > 0)
	{
		if (cd_[idx])
			DynamicRankingMgr::allocator_->FreeBuffer(cd_[idx]);

		memcpy(cd_ + idx, cd_ + idx + 1, sizeof(char*) * (col_ - idx - 1)); //后面的数据往前移
		col_--;

		if (col_ > 0)
			cd_[col_ - 1] = NULL;
	}
}

void RankingItem::SetColumnTitle(const char* data, int idx)
{
	if (idx >= 0 && idx < col_)
		SetSub(idx, data);
	else
		OutputMsg(rmError, "SetColumnTitle Error, Index wrong!");
}

void RankingItem::SetColCount(int count)
{
	if (count > max_col_)
	{
		int size = sizeof(char*) * count;
		char** ss = (char**)DynamicRankingMgr::allocator_->AllocBuffer(size);
		ZeroMemory(ss, size);

		if (cd_)
		{
			memcpy(ss, cd_, sizeof(char*) * max_col_);
			DynamicRankingMgr::allocator_->FreeBuffer(cd_);
		}

		cd_ = ss;
		max_col_ = count;
	}

	col_ = count;
}

void RankingItem::SetSub(int idx, const char* data)
{
	if (cd_ && idx >= 0 && idx < col_ && data)
	{
		size_t len = strlen(data);

		if (!cd_[idx])
		{
			cd_[idx] = (char*)DynamicRankingMgr::allocator_->AllocBuffer(len + 1);
		}
		else if (strlen(cd_[idx]) < len)
		{
			DynamicRankingMgr::allocator_->FreeBuffer(cd_[idx]);
			cd_[idx] = (char*)DynamicRankingMgr::allocator_->AllocBuffer(len + 1);
		}

		_STRNCPY_S(cd_[idx], data, len + 1);
		cd_[idx][len] = 0;

		if (rank_)
			rank_->SetModify();
	}
}

const char* RankingItem::GetSubData(int idx)
{
	if (cd_ && idx >= 0 && idx < col_)
		return cd_[idx] ? cd_[idx] : "-";
	else
		return "-";
}

DynamicRanking::DynamicRanking(const char* name, int max_item, bool display) :
	itemList_(DynamicRankingMgr::allocator_), index_(DynamicRankingMgr::allocator_)
{
	if (name)
	{
		_STRNCPY_A(name_, name);
	}
	else
	{
		name_[0] = 0;
	}

	cn_name_[0] = 0;
	id_title_[0] = 0;
	point_title_[0] = 0;
	file_[0] = 0;
	modify_ = false;
	autosave_ = true;

	rank_max_ = (int)max_item;
	rankVisibleType_ = enVisible_All;
	ZeroMemory(&rankVisibleParam_, sizeof(rankVisibleParam_));
	display_ = display;
	ZeroMemory(col_display_, sizeof(col_display_));
}

DynamicRanking::~DynamicRanking()
{
	//保存数据并释放内存
	for (int i = 0; i < itemList_.count(); i++)
	{
		RankingItem* item = itemList_[i];
		item->~RankingItem();
		DynamicRankingMgr::allocator_->FreeBuffer(item);
	}

	index_.empty();
	itemList_.empty();

	modify_ = false;
}

void DynamicRanking::destroy()
{
	static DynamicRankingMgr* mgr = GetGameEngine()->GetRankingSystem()->GetDynamicRankingMgr();
	mgr->Remove(name_);
}

void DynamicRanking::clear(bool freeItem)
{
	if (freeItem)
	{
		for (int i = 0; i < itemList_.count(); i++)
		{
			RankingItem* item = itemList_[i];
			item->~RankingItem();
			DynamicRankingMgr::allocator_->FreeBuffer(item);
		}
	}

	index_.clear();
	itemList_.clear();

	modify_ = true;
}

bool DynamicRanking::Load(const char* file)
{
	char path[256] = "./runtime/rank/";

	if (!FDOP::FileExists(path))
	{
		FDOP::DeepCreateDirectory(path);
	}
	_STRNCAT_A(path, file);

	FILE* fp = fopen(path, "r");

	if (!fp)
	{
		return false;
	}

	//纯文本，tab隔开各个字段，每行一个记录,第一行是标题
	int row = 0;
	const int size = 128;
	char buf[size];//缓冲区,保存每列的字符串，128应该够了
	int bufpos = 0;
	int col = 0;
	RankingItem* item = &title_;
	char ch = fgetc(fp);

	while (!feof(fp))
	{
		if (ch == '\n')//
		{
			buf[bufpos] = 0;
			if (col < 2)
			{
				//前两个是数字
				int value = atoi(buf);

				if (col == 0) item->id_ = value;//id和分值的数据
				else item->point_ = value;
			}
			else
			{
				item->AddColumn(buf, -1); //这是列的数据
			}
			bufpos = 0;
			col = 0;

			if (row > 0)
			{
				//要建立索引
				item->idx_ = (int)itemList_.count();
				itemList_.add(item);
				tagIndex index;
				index.id_ = item->id_;
				index.item_ = item;
				InsertId(index);
				item = NULL;
			}

			item = (RankingItem*)DynamicRankingMgr::allocator_->AllocBuffer(sizeof(RankingItem));//下一行的数据
			new(item)RankingItem();
			item->rank_ = this;

			row++;
		}
		else if (ch == '\t')
		{
			buf[bufpos] = 0;

			if (col < 2)
			{
				//前两个是数字
				int value = atoi(buf);

				if (col == 0) item->id_ = value;//id和分值的数据
				else item->point_ = value;
			}
			else
			{
				item->AddColumn(buf, -1); //这是列的数据
			}

			bufpos = 0;
			col++;
		}
		else
		{
			if (bufpos < (size - 1))
			{
				buf[bufpos++] = ch;
			}
		}

		ch = fgetc(fp);
	}

	fclose(fp);

	if (item)//还有数据没加到队列中
	{
		buf[bufpos] = 0;
		if (col < 2)
		{
			//前两个是数字
			int value = atoi(buf);

			if (col == 0) item->id_ = value;//id和分值的数据
			else item->point_ = value;
		}
		else
		{
			item->AddColumn(buf, -1); //这是列的数据
		}
		bufpos = 0;
		col = 0;

		if (row > 0)
		{
			item->idx_ = (int)itemList_.count();
			itemList_.add(item);
			tagIndex index;
			index.id_ = item->id_;
			index.item_ = item;
			InsertId(index);
			item = NULL;
		}

		row++;
	}

	_STRNCPY_A(file_, file); //保存的文件名
	return true;
}

void DynamicRanking::Save(const char* file)
{
	const char* realFile = file;

	if (!file)
	{
		realFile = file_;
	}
	else if (!file_[0])
	{
		_STRNCPY_A(file_, file); // 保存文件名
	}

	if (realFile == NULL || realFile[0] == 0)
	{
		return;
	}

	char path[256] = "./runtime/rank/";

	if (!FDOP::FileExists(path))
	{
		FDOP::DeepCreateDirectory(path);
	}

	_STRNCAT_A(path, realFile);
	FILE* fp = fopen(path, "w");

	if (!fp)
	{
		return;
	}

	SaveItem(&title_, fp);//保存标题先

	int count = itemList_.count();

	if (count > 0)
	{
		fputc('\n', fp);
	}

	for (int i = 0; i < count; i++)
	{
		RankingItem* item = itemList_[i];
		SaveItem(item, fp);

		if (i != (count - 1))
		{
			fputc('\n', fp);
		}
	}

	fclose(fp);
	modify_ = false;
}

void DynamicRanking::AddColumn(const char* title, int idx)
{
	title_.AddColumn(title, idx);
	int count = itemList_.count();

	for (int i = 0; i < count; i++)//所有排行榜项都要增加
	{
		RankingItem* item = itemList_[i];
		item->AddColumn("-", idx); //空的数据
	}

	modify_ = true;
}

void DynamicRanking::SetColumnTitle(const char* title, int idx)
{
	title_.SetColumnTitle(title, idx);	//设置列标题
}

void DynamicRanking::RemoveColumn(int idx)
{
	title_.RemoveColumn(idx);
	int count = itemList_.count();

	for (int i = 0; i < count; i++)//所有排行榜项都要增加
	{
		RankingItem* item = itemList_[i];
		item->RemoveColumn(idx);
	}

	modify_ = true;
}

RankingItem* DynamicRanking::Update(RankItemId id, int point)
{
	int idIndex = -1;
	int index = GetIndexFromId(id, idIndex);

	if (index >= 0 && index < itemList_.count())
	{
		RankingItem* item = itemList_[index];

		if (item && point != 0)
		{
			item->SetPoint((int)(item->point_ + point));

			if (point > 0)
			{
				UpdateUpPos(item);
			}
			else if (point < 0)//等于0 不做操作
			{
				UpdateDownPos(item);
			}

			modify_ = true;
		}

		return item;
	}
	else
	{
		return NULL;
	}
}

RankingItem* DynamicRanking::Set(RankItemId id, int point)
{
	int idIndex = -1;
	int index = GetIndexFromId(id, idIndex);

	if (index >= 0 && index < itemList_.count())
	{
		RankingItem* item = itemList_[index];

		if (item && item->point_ != point)
		{
			int nOldPoint = item->point_;
			item->SetPoint((int)point);

			if (point > nOldPoint)
			{
				UpdateUpPos(item);
			}
			else if (point < nOldPoint)
			{
				UpdateDownPos(item);
			}

			modify_ = true;
		}

		return item;
	}
	else
	{
		return NULL;
	}
}

void DynamicRanking::RemoveId(RankItemId id)
{
	int idIndex = -1;
	int index = GetIndexFromId(id, idIndex);

	if (index >= 0 && index < itemList_.count())
	{
		if (idIndex >= 0 && idIndex < index_.count())
		{
			index_.remove(idIndex);
		}

		RankingItem* item = itemList_[index];

		if (item)
		{
			//要重新排序，要释放内存
			if (item->idx_ < rank_max_ && itemList_.count() > rank_max_)		// 要在榜外找个最大的填补位置
			{
				RankingItem* max_item = FindMaxItem();
				itemList_.remove(max_item->idx_);		// 删除原来位置的，替代pItem
				itemList_.remove(item->idx_);
				itemList_.insert(rank_max_ - 1, max_item);
			}
			else
			{
				itemList_.remove(index);
			}

			int cnt = itemList_.count();

			for (int i = index; i < cnt; i++)
			{
				itemList_[i]->idx_ = i;
			}

			item->~RankingItem();
			DynamicRankingMgr::allocator_->FreeBuffer(item);
		}

		modify_ = true;
	}
}

RankingItem* DynamicRanking::GetPtrFromId(RankItemId id)
{
	int temp = -1;
	int index = GetIndexFromId(id, temp);

	if (index < 0 || index >= itemList_.count()) return NULL;

	return itemList_[index];
}

int DynamicRanking::GetIndexFromId(RankItemId id, int& idIndex)
{
	int low = 0;
	int high = (int)(index_.count() - 1);

	while (low <= high)
	{
		int mid = ((unsigned)(low + high)) >> 1;
		tagIndex& Index = index_[mid];

		if (Index.id_ < id)
			low = mid + 1;
		else if (Index.id_ > id)
			high = mid - 1;
		else
		{
			idIndex = mid;
			return Index.item_ ? Index.item_->idx_ : -1;
		}
	}

	return -1;
}

RankingItem* DynamicRanking::TryAddItem(RankItemId id, int points)
{
	int idIndex = -1;

	if (GetIndexFromId(id, idIndex) >= 0)
	{
		return NULL;
	}
	// 没上榜就不往里放
	if ((int)itemList_.count() >= rank_max_)
	{
		if (itemList_[rank_max_ - 1]->point_ >= points)
			return NULL;
		else
			RemoveId(itemList_[rank_max_ - 1]->id_);
	}

	RankingItem* item = (RankingItem*)DynamicRankingMgr::allocator_->AllocBuffer(sizeof(RankingItem));
	new(item)RankingItem();
	item->rank_ = this;
	item->SetPoint((int)points);
	item->SetId((int)id);
	item->SetColCount(title_.GetColCount());
	item->idx_ = (int)itemList_.count();
	tagIndex IndexItem;
	IndexItem.id_ = (int)id;
	IndexItem.item_ = item;
	itemList_.add(item);

	UpdateUpPos(item);

	InsertId(IndexItem);

	modify_ = true;

	return item;
}


RankingItem* DynamicRanking::AddItem(RankItemId id, int points)
{
	int idIndex = -1;

	if (GetIndexFromId(id, idIndex) >= 0)
	{
		return NULL;
	}

	RankingItem* item = (RankingItem*)DynamicRankingMgr::allocator_->AllocBuffer(sizeof(RankingItem));
	new(item)RankingItem();
	item->rank_ = this;
	item->SetPoint((int)points);
	item->SetId((int)id);
	item->SetColCount(title_.GetColCount());
	item->idx_ = -1;//
	tagIndex IndexItem;
	IndexItem.id_ = (int)id;
	IndexItem.item_ = item;
	//如果上榜，要重新排序，否则直接加到队列的最后面
	item->idx_ = (int)itemList_.count();
	itemList_.add(item);

	UpdateUpPos(item);

	InsertId(IndexItem);

	modify_ = true;

	return item;
}

int DynamicRanking::AddItem(RankingItem* itemPtr)
{
	if (!itemPtr) return -1;

	int idIndex = -1;

	if (GetIndexFromId(itemPtr->GetId(), idIndex) >= 0) // 已经存在
	{
		return idIndex;
	}

	itemPtr->rank_ = this;

	tagIndex IndexItem;
	IndexItem.id_ = (int)itemPtr->GetId();
	IndexItem.item_ = itemPtr;
	//如果上榜，要重新排序，否则直接加到队列的最后面
	itemPtr->idx_ = (int)itemList_.count();
	itemList_.add(itemPtr);

	UpdateUpPos(itemPtr);

	InsertId(IndexItem);

	modify_ = true;

	return itemPtr->GetIndex();
}

RankingItem* DynamicRanking::GetItem(int idx)
{
	if (idx >= 0 && idx < itemList_.count())
	{
		return itemList_[idx];
	}

	return NULL;
}

int DynamicRanking::UpdateUpPos(RankingItem* item)
{
	ScriptValueList arg;
	arg << name_;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("dRankUpdateBefore", &arg, &arg, 0);

	int start = (item->idx_ >= rank_max_) ? rank_max_ : (item->idx_);
	for (int i = (int)(start - 1); i >= 0; i--)
	{
		RankingItem* ri = itemList_[i];

		if (ri->point_ < item->point_)
		{
			//换个位置
			SwapItem(ri, item);
			modify_ = true;
		}
		else
		{
			break;
		}
	}

	arg.clear();
	arg << name_;
	luaScript.Call("dynamicRankUpdate", &arg, &arg, 0);

	return item->idx_;
}

int DynamicRanking::UpdateDownPos(RankingItem* item)
{
	if (item->idx_ < rank_max_)
	{
		ScriptValueList arg;
		arg << name_;
		static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
		luaScript.Call("dRankUpdateBefore", &arg, &arg, 0);

		int i = 0, count = itemList_.count();

		for (i = item->idx_ + 1; i < rank_max_ && i < count; i++)
		{
			RankingItem* ri = itemList_[i];

			if (ri->point_ > item->point_)
			{
				//换个位置
				SwapItem(ri, item);
				modify_ = true;
			}
			else
			{
				break;
			}
		}

		if (i >= rank_max_)
		{
			//看看榜外有没有比它大的
			RankingItem* max_item = FindMaxItem();

			if (max_item && max_item->point_ > item->point_)
			{
				//换个位置
				SwapItem(max_item, item);
				modify_ = true;
			}
		}
		arg.clear();
		arg << name_;
		luaScript.Call("dynamicRankUpdate", &arg, &arg, 0);
	}

	return item->idx_;
}

RankingItem* DynamicRanking::FindMaxItem()
{
	int count = itemList_.count();

	if (count <= rank_max_)
	{
		return NULL;
	}

	RankingItem* max_item = itemList_[rank_max_];

	for (int i = rank_max_ + 1; i < count; i++)
	{
		RankingItem* temp = itemList_[i];

		if (temp->point_ > max_item->point_)
		{
			max_item = temp;
		}
	}

	return max_item;
}

void DynamicRanking::SwapItem(RankingItem* ri, RankingItem* item)
{
	int tempIdx = ri->idx_;
	itemList_[tempIdx] = item;
	itemList_[item->idx_] = ri;
	ri->idx_ = item->idx_;
	item->idx_ = (int)tempIdx;
	modify_ = true;
}

void DynamicRanking::InsertId(tagIndex& IndexItem)
{
	//id加到列表中
	int low = 0;
	int high = (int)(index_.count() - 1);

	while (low <= high)
	{
		int mid = ((unsigned)(low + high)) >> 1;
		tagIndex& Index = index_[mid];

		if (Index.id_ < IndexItem.id_)
			low = mid + 1;
		else
			high = mid - 1;
	}

	index_.insert(low, IndexItem);
}

void DynamicRanking::SwapEqualItem(RankingItem* item1, RankingItem* item2)
{
	if (item1 == NULL || item2 == NULL) return;

	if (item1->GetPoint() != item2->GetPoint())	return;

	SwapItem(item1, item2);
}

void DynamicRanking::SaveItem(RankingItem* item, FILE* fp)
{
	char buf[256];
	SNPRINTFA(buf, sizeof(buf), "%d\t%d", item->id_, item->point_);
	fputs(buf, fp);

	for (int i = 0; i < item->GetColCount(); i++)
	{
		fputc('\t', fp);
		const char* data = item->GetSubData(i);
		fputs(data ? data : "-", fp);
	}
}

void DynamicRanking::SetColDisplay(int idx, bool disp)
{
	if (idx >= 0 && idx < title_.GetColCount())
	{
		col_display_[idx] = !disp;//1是不显示
	}
}

bool DynamicRanking::IsColDisplay(int idx)
{
	if (idx >= 0 && idx < title_.GetColCount())
	{
		return !col_display_[idx];
	}

	return false;
}


