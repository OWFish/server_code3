//tolua_begin
namespace Fuben
{

unsigned int createFuBen(int nFbID);


//void createMonstersByConfig(unsigned int hScene);


void closeFuben(unsigned int hFuben);
void setEnd(unsigned int hFuben);
void setBelong(unsigned int hFuben);
void setIsNeedAi(unsigned int hFuben, bool canRun);

unsigned int getFubenHandle(void* pFuben);

void* getFubenPtr(unsigned int hFuben);

unsigned int getStaticFubenHandle();

void* createMonster(unsigned int hScene, unsigned int nMonsterid, int posX = 0, int posY = 0, unsigned int nLiveTime = 0, void* met = 0);

void* createDropBag(unsigned int hScene, int type, int id, int count, int x, int y, int belong_id = 0);

int RewardDropBag(lua_State* L);

//void createMonsters(unsigned int hScene, unsigned int nMonsterid,
//                    int posX1, int posX2, int posY1, int posY2,
//					int nCount, unsigned int nLiveTime, int tarX = -1, int tarY = -1);

//bool canMove(unsigned int hScene, int posX, int posY);

//void deleteEntity(int hScene, unsigned int hFuben, char* name);

// 副本广播
void sendData(unsigned int hdl, void* dp);
void sendDataNoActor(unsigned int hdl, void* dp, void* actor);
int getAllActor(lua_State* L);
int getAllMonster(lua_State* L);
int getAllDropBag(lua_State* L);
int getAllCloneRole(lua_State* L);
int getActorCount(unsigned int hdl);
//获取剩余怪物数量- 
int GetResActorMirrorCount(unsigned int hdl);
void* getCloneRole(unsigned int hdl,int ActorID);

// 副本脚本系统回调
void releaseInstance(void *fb);
int getMonsterId(void *mon);
bool isKillAllMonster(unsigned int hScene, int monId = 0);
void killAllMonster(unsigned int hScene);
void clearAllMonster(unsigned int hScene);
void clearAllCloneRole(unsigned int hScene);
void clearCloneRoleById(unsigned int hScene, int actor_id);
double getMonsterMaxHp(int id);
void setMonsterCamp(void *mon, int camp);
void setBaseAttr(void *mon, float rate);

void* getSceneMonsterById(void *pScene, int targetId);
int Getscenelist(lua_State *L);
unsigned int getSceneHandlebyPtr(void *pScene);

};

//tolua_end

