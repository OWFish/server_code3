/*
	创建排行榜的相关接口
*/


//tolua_begin
namespace Ranking
{
/*
* Comments:获取排行榜前N名的数据
* Param lua_State * L:[排行榜的指针][数量，表示要获取前N名]
* @Return int:返回一个表，包含排行榜项的指针
*/
int getRankingItemList(lua_State* L);

/*
* Comments:增加引用值
* Param void * pRank:
* @Return void:
*/
void addRef(void* pRank);

/*
* Comments:减少引用值
* Param void * pRank:
* @Return void:
*/
void release(void* pRank);

/*
* Comments:获取引用值
* Param void * pRank:
* @Return int:
*/
int getRef(void* pRank);

/*
* Comments:获取排行榜的指针
* Param char * sName:排行榜的名称
* @Return void*:返回NULL表示没有
*/
void* getRanking(char* sName);

/*
* Comments:增加一个排行榜
* Param char * sName:排行榜的名称
* Param int nMax:发给客户端最多的行数
* Param boDisplay:是否在客户端显示，默认是0，不显示，1显示
* @Return void*:添加成功会返回排行榜的指针，返回NULL
*/
void* add(char* sName, int nMax, int boDisplay = 0);

/*
* Comments:排行榜从文件中读入数据
* Param CRanking * pRank:排行榜的指针
* Param char * sFile:指定的文件，文件保存在当前目录的 ph/XXX,传入XXX就行
* @Return bool:如果文件存在并读取成功返回true
*/
bool load(void* pRank, char* sFile);

/*
* Comments:排行榜保存数据到文件
* Param void * pRank:
* Param char * sFile:文件名，不需要包含路径
* @Return bool:是否保存成功
*/
bool save(void* pRank, char* sFile);

/*
* Comments:增加一列
* Param CRanking * pRank:
* Param char * sTitle:列的标题名称
* Param int nIndex:-1表示在最后增加，否则在指定的列前增加
* @Return void:
*/
void addColumn(void* pRank, char* sTitle, int nIndex = -1);

// 获取一个排行榜的列数
int getColumnCount(void* pRank);

/*
* Comments: 设置列的标题
* Param void * pRank: 排行榜的指针
* Param char * sTitle: 列的标题名称
* Param int nIndex: 列的索引 由0开始
* @Return void:
*/
void setColumnTitle(void* pRank, char* sTitle, int nIndex);

/*
* Comments:增加一个排行榜项
* Param void * pRank:排行榜的指针
* Param int nId:id值
* Param int nPoint:初始的分值
* @Return void*:成功返回排行榜项，否则返回NULL,如果已经存在对应的id，会加入失败
*/
void* addItem(void* pRank, int nId, int nPoint);
/*
* Comments:尝试添加一个排行榜项
* Param void * pRank:排行榜的指针
* Param int nId:id值
* Param int nPoint:初始的分值
* @Return void*:如果进入榜单范围内返回排行榜项，否则返回空，如果已存在返回nil
*/
void* tryAddItem(void* pRank, int nId, int nPoint);
/*
* Comments:获取某个id在排行榜中的位置，第一位是0，不在这个返回-1
* Param int nId:
* @Return int:
*/
int getItemIndexFromId(void* pRank, int nId);

/*
* Comments:根据id获取排行榜项的指针
* Param void * pRank:
* Param int nId:
* @Return void*:不存在返回NULL
*/
void* getItemPtrFromId(void* pRank, int nId);

/*
* Comments:更新排行榜项的分值
* Param void * pRank:
* Param int nId:id
* Param int nPoint:分值
* @Return void*:成功会返回对应的排行榜项，失败（不存在）返回NULL
*/
void* updateItem(void* pRank, int nId, int nPoint);

/*
* Comments:设置排行榜项的分值
* Param void * pRank:
* Param int nId:id
* Param int nPoint:分值
* @Return void*:成功会返回对应的排行榜项，失败（不存在）返回NULL
*/
void* setItem(void* pRank, int nId, int nPoint);

/*
* Comments:设置某列是否显示在客户端
* Param void * pRank:排行榜指针
* Param int nIndex:列索引，第一列是0
* Param int boDisplay:是否显示，1显示，0不显示，注意：默认是显示的
* @Return void:
*/
void setColumnDisplay(void* pRank, int nIndex , int boDisplay);

/*
* Comments:设置排行榜项的列的显示内容
* Param void * pRankItem:排行榜项的指针
* Param int nIndex:第几列
* Param char * sData:字符串内容
* @Return void:
*/
void setSub(void* pRankItem, int nIndex, char* sData);

// 
void setSubInt(void* rankItem, int nIndex, int data);

// 增加为正，减少为负
int updateSubInt(void* rankItem, int nIndex, int val);

/*
* Comments:删除指定的排版榜
* Param char * sName:
* @Return void:
*/
void removeRanking(char* sName);

/*
* Comments:获取本排行榜名单的数量
* Param void * pRank:
* @Return int:
*/
int getRankItemCount(void* pRank);

/*
* Comments:获取玩家的分数
* Param void * pRankItem:
* @Return int:
*/
int getPoint(void* pRankItem);

/*
* Comments:获取排行榜项的id
* Param void * pRankItem:
* @Return int:
*/
int getId(void* pRankItem);

/*
* Comments:获取名次
* Param void * pRankItem:
* @Return int:第一名是0
*/
int getIndexFromPtr(void* pRankItem);

/*
* Comments:获取某列的字符串数据
* Param void * pRankItem:排行榜项的指针
* Param int nIndex:列索引
* @Return char*:
*/
const char* getSub(void* pRankItem, int nIndex);

// 
int getSubInt(void* pRankItem, int nIndex);


/*
* Comments:清除排行榜所有的名单数据
* Param void * pRank:排行榜的指针
* @Return void:
*/
void clearRanking(void* pRank);

/*
* Comments:获取排行榜某个位置的排行榜项
* Param void * pRank:
* Param int nIndex:名词，0表示第一名
* @Return void*:
*/
void* getItemFromIndex(void* pRank, int nIndex);

/*
* Comments:设置排行榜的显示在客户端的名称
* Param void * pRank:排行榜的指针
* Param const char * sName:名称
* @Return void:
*/
void setDisplayName(void* pRank, const char* sName);

/*
* Comments:设置id的显示标题
* Param void * pRank:
* Param const char * sName:
* @Return void:
*/
void setIdTitle(void* pRank, const char* sName);

/*
* Comments:设置分值的显示标题
* Param void * pRank:
* Param const char * sName:
* @Return void:
*/
void setPointTitle(void* pRank, const char* sName);

/*
* Comments:删除id
* Param void * pRank:
* Param int id:
* @Return void:
*/
void removeId(void* pRank, int id);

// 设置排行榜是否自动保存
void setAutoSave(void* pRank, bool isAuto);

// 交换两个积分相同的项
void swapEqualItem(void* rank, void* item1, void* item2);

//返回排行榜数据
int getLianfuRankData(lua_State* L);

//获取静态排行榜
void* getStaticRank(int rankId);

//获取静态排行榜单名次通过ID
int getSRIndexFromId(void* rank, int id);

//获取静态排行榜单ID通过名次
int getSRIdFromIdx(void* rank, int idx);

void updateStaticRank();

const char* getRankName(void* rank);

void setRankName(void* rank, const char* name);
};

//tolua_end

