#ifndef _GAME_WORLD_DEF_H_
#define _GAME_WORLD_DEF_H_

#include "os_def.h"
#include "../common/db/msg.h"

//������Ϸ�߼�����汾��
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

typedef Vector<EntityHandle> VisiHandleList;	// ע�⣺������1024��Ԫ�أ�ͨ������static����

typedef LinkedListEx<EntityHandle, 4096* 8> EntityList;	// ���Ӧ����Ҫ�ıȽ϶࣬������40960


#define PROTO_HDR_DEF(sysid, protoid) 	const uint8_t hdr[2] = {sysid, protoid}

// ���ӵ����ش�С
#define GRIDSIZE 64

// ���ص�ṹ
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

// ����ṹ
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


// ʵ��ľ���λ����Ϣ
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

// ���ص����ṹ
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

// ���ؾ���
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
	SSM_GW_DUMP,			// ������ʧȥ����
	SSM_DB_RET_DATA,		//db��������
	SSM_CLOSE_ACTOR_BY_ID,	// �ر����
	SSM_GAMESESSION_REG,		// gamesession����������Ϣ
	SSM_GAMESESSION_GATEWAY,	// ͬ��gateway����Ϣ(����)
	SSM_CROSSWAR_KEY,		// �����key�Ļ�Ӧ
	SSM_GAMECLIENT_REG,		//  gameclient���ӳɹ�����Ϣ
	SSM_CROSSWAR_MSG,		// ���ս��ͨ�ŵ����ݰ�
	SSM_WORK_THREAD,		// ͨ���̵߳���Ϣ
	SSM_RELOAD_GLOBAL_NPC,	// ���¼���ȫ��npc�Ľű�
	SSM_RUN_ALL_TESTS,		// ��Ԫ����
	SSM_CENTER_DATA,	// ���ķ�����������
	SSM_CROSSTTMSG_GAME,	// �ѿ����Ϣת������Ϸ���߼���
	SSM_RELOAD_GLOBAL_NPC_MAIN,	//���¼���ȫ��npc�Ľű�(���߳�ServerMain)

	SSM_CREATE_ACTOR_IMAGE,	// ������ɫ����
	SSM_USER_CHANGE_NAME, //��Ҹ���
	SSM_ADD_LOGIN, //�����Ҷ���½����

	SSM_CROSS_RELOGIN,		// ����ظ���¼
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
		char fn_[8];	// �������ַ�������
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

////ʵ���ƶ��ķ���
typedef enum tagDirCode
{
    DIR_UP = 0,		//��
    DIR_UP_RIGHT = 1,	//����
    DIR_RIGHT = 2,		//��
    DIR_DOWN_RIGHT = 3,	//����
    DIR_DOWN = 4,		//��
    DIR_DOWN_LEFT = 5,	//����
    DIR_LEFT = 6,		//��
    DIR_UP_LEFT = 7,	//����
    DIR_STOP,		//����
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
	int		sid_;	//������ID
	int		count_;	//·�ɵ�ַ����
	struct
	{
		char	host_[128];	//��������ַ���ͻ���֧��������
		int		port_;		//�������˿�
	} t[2];	//·�ɱ�
};

class ScriptEvent
{
public:
	ScriptEvent()
	{
	}
	unsigned int		handle_;					// �¼����
	ScriptValueList		args_;						// �ű������б�
	char fn_[32];			// �ص���������
};

// ʵ��ű��ص�����;�����������Ͷ���
typedef memory::Handle										SEventHandle;
typedef memory::HandleMgr<ScriptEvent, SEventHandle>		ScriptEventHdlMgr;

#endif

