/*
	�������а����ؽӿ�
*/


//tolua_begin
namespace Ranking
{
/*
* Comments:��ȡ���а�ǰN��������
* Param lua_State * L:[���а��ָ��][��������ʾҪ��ȡǰN��]
* @Return int:����һ�����������а����ָ��
*/
int getRankingItemList(lua_State* L);

/*
* Comments:��������ֵ
* Param void * pRank:
* @Return void:
*/
void addRef(void* pRank);

/*
* Comments:��������ֵ
* Param void * pRank:
* @Return void:
*/
void release(void* pRank);

/*
* Comments:��ȡ����ֵ
* Param void * pRank:
* @Return int:
*/
int getRef(void* pRank);

/*
* Comments:��ȡ���а��ָ��
* Param char * sName:���а������
* @Return void*:����NULL��ʾû��
*/
void* getRanking(char* sName);

/*
* Comments:����һ�����а�
* Param char * sName:���а������
* Param int nMax:�����ͻ�����������
* Param boDisplay:�Ƿ��ڿͻ�����ʾ��Ĭ����0������ʾ��1��ʾ
* @Return void*:��ӳɹ��᷵�����а��ָ�룬����NULL
*/
void* add(char* sName, int nMax, int boDisplay = 0);

/*
* Comments:���а���ļ��ж�������
* Param CRanking * pRank:���а��ָ��
* Param char * sFile:ָ�����ļ����ļ������ڵ�ǰĿ¼�� ph/XXX,����XXX����
* @Return bool:����ļ����ڲ���ȡ�ɹ�����true
*/
bool load(void* pRank, char* sFile);

/*
* Comments:���а񱣴����ݵ��ļ�
* Param void * pRank:
* Param char * sFile:�ļ���������Ҫ����·��
* @Return bool:�Ƿ񱣴�ɹ�
*/
bool save(void* pRank, char* sFile);

/*
* Comments:����һ��
* Param CRanking * pRank:
* Param char * sTitle:�еı�������
* Param int nIndex:-1��ʾ��������ӣ�������ָ������ǰ����
* @Return void:
*/
void addColumn(void* pRank, char* sTitle, int nIndex = -1);

// ��ȡһ�����а������
int getColumnCount(void* pRank);

/*
* Comments: �����еı���
* Param void * pRank: ���а��ָ��
* Param char * sTitle: �еı�������
* Param int nIndex: �е����� ��0��ʼ
* @Return void:
*/
void setColumnTitle(void* pRank, char* sTitle, int nIndex);

/*
* Comments:����һ�����а���
* Param void * pRank:���а��ָ��
* Param int nId:idֵ
* Param int nPoint:��ʼ�ķ�ֵ
* @Return void*:�ɹ��������а�����򷵻�NULL,����Ѿ����ڶ�Ӧ��id�������ʧ��
*/
void* addItem(void* pRank, int nId, int nPoint);
/*
* Comments:�������һ�����а���
* Param void * pRank:���а��ָ��
* Param int nId:idֵ
* Param int nPoint:��ʼ�ķ�ֵ
* @Return void*:�������񵥷�Χ�ڷ������а�����򷵻ؿգ�����Ѵ��ڷ���nil
*/
void* tryAddItem(void* pRank, int nId, int nPoint);
/*
* Comments:��ȡĳ��id�����а��е�λ�ã���һλ��0�������������-1
* Param int nId:
* @Return int:
*/
int getItemIndexFromId(void* pRank, int nId);

/*
* Comments:����id��ȡ���а����ָ��
* Param void * pRank:
* Param int nId:
* @Return void*:�����ڷ���NULL
*/
void* getItemPtrFromId(void* pRank, int nId);

/*
* Comments:�������а���ķ�ֵ
* Param void * pRank:
* Param int nId:id
* Param int nPoint:��ֵ
* @Return void*:�ɹ��᷵�ض�Ӧ�����а��ʧ�ܣ������ڣ�����NULL
*/
void* updateItem(void* pRank, int nId, int nPoint);

/*
* Comments:�������а���ķ�ֵ
* Param void * pRank:
* Param int nId:id
* Param int nPoint:��ֵ
* @Return void*:�ɹ��᷵�ض�Ӧ�����а��ʧ�ܣ������ڣ�����NULL
*/
void* setItem(void* pRank, int nId, int nPoint);

/*
* Comments:����ĳ���Ƿ���ʾ�ڿͻ���
* Param void * pRank:���а�ָ��
* Param int nIndex:����������һ����0
* Param int boDisplay:�Ƿ���ʾ��1��ʾ��0����ʾ��ע�⣺Ĭ������ʾ��
* @Return void:
*/
void setColumnDisplay(void* pRank, int nIndex , int boDisplay);

/*
* Comments:�������а�����е���ʾ����
* Param void * pRankItem:���а����ָ��
* Param int nIndex:�ڼ���
* Param char * sData:�ַ�������
* @Return void:
*/
void setSub(void* pRankItem, int nIndex, char* sData);

// 
void setSubInt(void* rankItem, int nIndex, int data);

// ����Ϊ��������Ϊ��
int updateSubInt(void* rankItem, int nIndex, int val);

/*
* Comments:ɾ��ָ�����Ű��
* Param char * sName:
* @Return void:
*/
void removeRanking(char* sName);

/*
* Comments:��ȡ�����а�����������
* Param void * pRank:
* @Return int:
*/
int getRankItemCount(void* pRank);

/*
* Comments:��ȡ��ҵķ���
* Param void * pRankItem:
* @Return int:
*/
int getPoint(void* pRankItem);

/*
* Comments:��ȡ���а����id
* Param void * pRankItem:
* @Return int:
*/
int getId(void* pRankItem);

/*
* Comments:��ȡ����
* Param void * pRankItem:
* @Return int:��һ����0
*/
int getIndexFromPtr(void* pRankItem);

/*
* Comments:��ȡĳ�е��ַ�������
* Param void * pRankItem:���а����ָ��
* Param int nIndex:������
* @Return char*:
*/
const char* getSub(void* pRankItem, int nIndex);

// 
int getSubInt(void* pRankItem, int nIndex);


/*
* Comments:������а����е���������
* Param void * pRank:���а��ָ��
* @Return void:
*/
void clearRanking(void* pRank);

/*
* Comments:��ȡ���а�ĳ��λ�õ����а���
* Param void * pRank:
* Param int nIndex:���ʣ�0��ʾ��һ��
* @Return void*:
*/
void* getItemFromIndex(void* pRank, int nIndex);

/*
* Comments:�������а����ʾ�ڿͻ��˵�����
* Param void * pRank:���а��ָ��
* Param const char * sName:����
* @Return void:
*/
void setDisplayName(void* pRank, const char* sName);

/*
* Comments:����id����ʾ����
* Param void * pRank:
* Param const char * sName:
* @Return void:
*/
void setIdTitle(void* pRank, const char* sName);

/*
* Comments:���÷�ֵ����ʾ����
* Param void * pRank:
* Param const char * sName:
* @Return void:
*/
void setPointTitle(void* pRank, const char* sName);

/*
* Comments:ɾ��id
* Param void * pRank:
* Param int id:
* @Return void:
*/
void removeId(void* pRank, int id);

// �������а��Ƿ��Զ�����
void setAutoSave(void* pRank, bool isAuto);

// ��������������ͬ����
void swapEqualItem(void* rank, void* item1, void* item2);

//�������а�����
int getLianfuRankData(lua_State* L);

//��ȡ��̬���а�
void* getStaticRank(int rankId);

//��ȡ��̬���а�����ͨ��ID
int getSRIndexFromId(void* rank, int id);

//��ȡ��̬���а�IDͨ������
int getSRIdFromIdx(void* rank, int idx);

void updateStaticRank();

const char* getRankName(void* rank);

void setRankName(void* rank, const char* name);
};

//tolua_end

