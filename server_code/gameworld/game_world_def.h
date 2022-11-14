#ifndef _GAME_WORLD_DEF_H_
#define _GAME_WORLD_DEF_H_

#include "os_def.h"
#include "../common/db/msg.h"

//定义游戏逻辑引擎版本号
#define GAME_KN_VERSION	0x0200
#define PFSTR_MAX_LEN	128
#define PFID_MAX_LEN	128
#define APPID_MAX_LEN	128

class Scene;
class FuBen;

class EntityHandle : public memory::Handle64
{
public:
	EntityHandle(void) : memory::Handle64() {}
	EntityHandle(int64_t h) : memory::Handle64(h) {}

	inline unsigned int GetType() const
	{
		return rev_;
	}
	inline void SetType(unsigned short t)
	{
		rev_ = t;
	}
	inline operator int64_t (void) const
	{
		return (handle_);
	}
	inline EntityHandle& operator = (const int64_t v)
	{
		handle_ = v;
		return *this;
	}
	inline EntityHandle& operator = (const EntityHandle v)
	{
		handle_ = v.handle_;
		return *this;
	}
};

STATIC_ASSERT(sizeof(EntityHandle) == 8);

typedef Vector<EntityHandle> VisiHandleList;	// 注意：最少是1024个元素，通常用作static变量

typedef LinkedListEx<EntityHandle, 4096* 8> EntityList;	// 这个应该需要的比较多，所以是40960


#define PROTO_HDR_DEF(sysid, protoid) 	const uint8_t hdr[2] = {sysid, protoid}

// 格子的像素大小
#define GRIDSIZE 64

// 像素点结构
struct Point
{
	int x;
	int y;

	/******************/
	Point(void) { this->x = 0; this->y = 0; }
	Point(int x, int y){ this->x = x; this->y = y; }
	Point(const Point& pt){ this->x = pt.x; this->y = pt.y; }
	Point& operator+=(const Point& point) { x += point.x; y += point.y; return *this; }
	Point& operator-=(const Point& point) { x -= point.x; y -= point.y; return *this; }
	Point& operator=(const Point& point) { x = point.x; y = point.y; return *this; }
	bool operator==(const Point& point) const { return x == point.x && y == point.y; }
};

// 坐标结构
struct Pos
{
	short x;
	short y;

	/******************/
	Pos(int x, int y){ this->x = x; this->y = y; }
	Pos(const Pos& pos){ x = pos.x; y = pos.y; }
	Pos(const Point& pt){ x = pt.x / GRIDSIZE; y = pt.y / GRIDSIZE; }
	Pos& operator+=(const Pos& pos) { x += pos.x; y += pos.y; return *this; }
	Pos& operator-=(const Pos& pos) { x -= pos.x; y -= pos.y; return *this; }
	Pos& operator=(const Pos& pos) { x = pos.x; y = pos.y; return *this; }
	bool operator==(const Pos& pos) { return x == pos.x && y == pos.y; }
	Point ToPoint() const { return Point(x * GRIDSIZE + GRIDSIZE/2, y * GRIDSIZE + GRIDSIZE/2); }
};
typedef Pos Grid;


// 实体的具体位置信息
struct EntityPosInfo 
{
	FuBen*	fuben;
	Scene*	scene;
	Point  point_pos;
	EntityPosInfo():fuben(0),scene(0),point_pos(0,0){}
};

struct EntityLocation
{
	int sid;
	short x;
	short y;
	EntityLocation(int sid, short x, short y) { this->sid = sid, this->x = x; this->y = y; }
	EntityLocation() :sid(0), x(0), y(0) {}
};

// 像素点计算结构
struct DPoint
{
	double x;
	double y;

	/******************/
	DPoint(int x, int y){ this->x = x; this->y = y; }
	DPoint(const Point& pt){ this->x = pt.x; this->y = pt.y; }
	DPoint& operator=(const DPoint& point) { x = point.x; y = point.y; return *this; }
	Point ToPoint() const { return Point(int(x), int(y)); }
	Grid ToGrid() const { return Grid(int(x / GRIDSIZE), int(y/GRIDSIZE)); }
};

// 返回距离
inline int GetGridDistance(const Pos& p1, const Pos& p2)
{
	int dx = abs(p1.x - p2.x);
	int dy = abs(p1.y - p2.y);

	return __max(dx, dy);
}

inline int GetPixDistance(const Point& p1, const Point& p2, int offset)
{
	int dx = abs(p1.x - p2.x);
	int dy = abs(p1.y - p2.y);
	double dis = sqrt(dx*dx + dy*dy);
	return static_cast<int>(__max(dis-offset, 0));
}

//struct POS
//{
//	short x;
//	short y;
//};

enum GameWorldInternalMessage
{
	SSM_ACTOR_LOGIN = 1,	//USER LOGIN
	SSM_ACTOR_LOGOUT,       //USER LOGOUT
	SSM_GW_DUMP,			// 与网关失去连接
	SSM_DB_RET_DATA,		//db返回数据
	SSM_CLOSE_ACTOR_BY_ID,	// 关闭玩家
	SSM_GAMESESSION_REG,		// gamesession发过来的信息
	SSM_GAMESESSION_GATEWAY,	// 同步gateway的信息(无用)
	SSM_CROSSWAR_KEY,		// 跨服的key的回应
	SSM_GAMECLIENT_REG,		//  gameclient连接成功的消息
	SSM_CROSSWAR_MSG,		// 跨服战的通信的数据包
	SSM_WORK_THREAD,		// 通用线程的消息
	SSM_RELOAD_GLOBAL_NPC,	// 重新加载全局npc的脚本
	SSM_RUN_ALL_TESTS,		// 单元测试
	SSM_CENTER_DATA,	// 中心服务器的数据
	SSM_CROSSTTMSG_GAME,	// 把跨服消息转发到游戏主逻辑里
	SSM_RELOAD_GLOBAL_NPC_MAIN,	//重新加载全局npc的脚本(主线程ServerMain)

	SSM_CREATE_ACTOR_IMAGE,	// 创建角色镜像
	SSM_USER_CHANGE_NAME, //玩家改名
	SSM_ADD_LOGIN, //添加玩家都登陆队列

	SSM_CROSS_RELOGIN,		// 跨服重复登录
};

typedef union GameInterMsgData
{
	struct
	{
		int cmd_;
		DataPacket* packet_;
		void* rev_;
		int dbsid_;
		int param1_;
	};
	struct
	{
		int64_t handle_;
		int account_id_;
		char fn_[8];	// 必须是字符串常量
	};
	struct
	{
		GateUser* user_;
		char pf_[PFSTR_MAX_LEN];
		char pf_id_[PFID_MAX_LEN];
		char appid_[APPID_MAX_LEN];
		int serverId_;
	};
	struct
	{
		int count_;
		void* item_;
	};
	struct 
	{
		void* buffdata_;
	};
	struct
	{
		void* ptr_;
	};
	struct
	{
		int64_t gm_actor_;
		int type_;
	};
	struct  
	{
		int actor_id;
		int sId_;
	};
} GAMEINTERMSGDATA;

typedef struct GameInterMsg
{
	int	msg_id_;
	GAMEINTERMSGDATA data_;
} GAMEINTERMSG;

////实体移动的方向
typedef enum tagDirCode
{
    DIR_UP = 0,		//上
    DIR_UP_RIGHT = 1,	//右上
    DIR_RIGHT = 2,		//右
    DIR_DOWN_RIGHT = 3,	//右下
    DIR_DOWN = 4,		//下
    DIR_DOWN_LEFT = 5,	//左下
    DIR_LEFT = 6,		//左
    DIR_UP_LEFT = 7,	//左上
    DIR_STOP,		//不动
	DIR_MAX = DIR_STOP
} DIRCODE;

inline int getDir(int sx, int sy, int dx, int dy)
{
	int xx = dx - sx; int yy = dy - sy;
	if (xx == 0) {
		if (yy == 0) return DIR_STOP;
		else if (yy > 0) return DIR_UP;
		else return DIR_DOWN;
	} else if (xx > 0) {
		if (yy == 0) return DIR_RIGHT;
		else if (yy > 0) return DIR_UP_RIGHT;
		else return DIR_DOWN_RIGHT;
	} else {
		if (yy == 0) return DIR_LEFT;
		else if (yy > 0) return DIR_UP_LEFT;
		else return DIR_DOWN_LEFT;
	}
	return DIR_STOP;
}

inline void getDir(int dir, int &x, int &y)
{
	switch (dir)
	{
	case DIR_UP:
		x = 0; y = 1;
		break;
	case DIR_UP_RIGHT:
		x = 1; y = 1;
		break;
	case DIR_RIGHT:
		x = 1; y = 0;
		break;
	case DIR_DOWN_RIGHT:
		x = 1; y = -1;
		break;
	case DIR_DOWN:
		x = 0; y = -1;
		break;
	case DIR_DOWN_LEFT:
		x = -1; y = -1;
		break;
	case DIR_LEFT:
		x = -1; y = 0;
		break;
	case DIR_UP_LEFT:
		x = -1; y = 1;
		break;
	default:
		x = 0; y = 0;
		break;
	}
}

//
//struct Point
//{
//	int x;
//	int y;
//};
//
//struct DPoint
//{
//	double x;
//	double y;
//};
//
//#pragma pack(push, 1)
//struct SPoint
//{
//	uint16_t x;
//	uint16_t y;
//};
//#pragma pack(pop)

typedef Vector<void*>	AnyVector;
typedef Vector<DataPacket*> DataPackList;
//typedef Vector<MailData> MailDataVector;

struct GameRoute
{
	int		sid_;	//服务器ID
	int		count_;	//路由地址数量
	struct
	{
		char	host_[128];	//服务器地址（客户端支持域名）
		int		port_;		//服务器端口
	} t[2];	//路由表
};

class ScriptEvent
{
public:
	ScriptEvent()
	{
	}
	unsigned int		handle_;					// 事件句柄
	ScriptValueList		args_;						// 脚本参数列表
	char fn_[32];			// 回调函数名称
};

// 实体脚本回调句柄和句柄管理器类型定义
typedef memory::Handle										SEventHandle;
typedef memory::HandleMgr<ScriptEvent, SEventHandle>		ScriptEventHdlMgr;

#endif

