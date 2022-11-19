#pragma once
#include "StdAfx.h"
//#include "fuben.h"
//#include "scene.h"
//#include "memory/handle_mgr.h"

//#define REUSEFB

using namespace container;

class GameEngine;

struct MAPDATA
{
	char		file_[256];
	GameMap*	map_data_;
};


//一共48个，从里边到外边遍历，找到一个合适的位置
/*static	BYTE s_matrix[][2] =
{
	//第1圈8个
	{ -1,2 },{ 0,1 },{ 2,-1 },{ -1,0 },{ 1,0 },{ 1,-2 },{ 0,-1 },{ 0,2 },

	//第2圈16个
	{ 1,-1 },{ -1,-2 },{ 1,1 },{ 0,-3 },{ -2,-2 },{ -2,-3 },{ -1,1 },{ 2,-2 },{ 1,3 },{ -2,2 },{ -1,-1 },{ 1,-3 },{ 3,-2 },{ 2,2 },{ -2,0 },{ -3,1 },{ -2,-1 },

	//第3圈24个
	{ -2,1 },{ 2,1 },{ -3,-1 },{ 1,2 },{ -1,-3 },{ 2,0 },{ -3,-3 },{ 3,2 },{ -3,2 },{ 3,-1 },{ 3,0 },{ 0,3 },{ 3,1 },
	{ -3,3 },{ -3,-2 },{ 3,3 },{ -1,3 },{ -3,0 },{ 3,-3 },{ 2,3 },

	//第4圈32个
	{ -3,-4 },{ 0,4 },{ -1,-4 },{ 1,-4 },{ -4,2 },{ 4,4 },{ 2,-4 },{ 3,-4 },{ -2,4 },{ 4,-4 },{ 2,4 },{ -4,-3 },{ 4,-3 },{ 4,3 },{ -4,-2 },{ -4,4 },{ 4,-2 },{ 4,1 },
	{ -4,-4 },{ 0,-4 },{ -4,0 },{ -4,-1 },{ 4,0 },{ -4,1 },{ 4,1 },{ -2,-4 },{ 4,2 },{ -4,3 },{ -3,4 },{ -1,4 },{ 1,4 },{ 3,4 },

	//第5圈40个
	{ -4,-5 },{ -2,5 },{ -3,-5 },{ 5,-2 },{ -1,-5 },{ 1,5 },{ 0,-5 },{ 2,-5 },{ -5,2 },{ 4,5 },{ 5,0 },{ 5,3 },{ -5,-4 },{ 5,-3 },{ -5,5 },
	{ -5,-2 },{ -5,-1 },{ 5,1 },{ 3,-5 },{ -5,0 },{ 5,-4 },{ -5,1 },{ 5,1 },{ 5,2 },{ 5,-5 },{ -5,3 },{ -5,4 },{ -5,-3 },{ 5,4 },{ -4,5 },
	{ -5,-5 },{ -3,5 },{ -1,5 },{ -2,-5 },{ 0,5 },{ 2,5 },{ 1,-5 },{ 3,5 },{ 5,5 },{ 4,-5 },

	//第6圈48个
	{ -5,-6 },{ 6,1 },{ -6,5 },{ -4,-6 },{ -6,0 },{ -5,6 },{ -6,-2 },{ 0,-6 },{ 2,6 },{ -6,2 },{ -6,4 },{ 2,-6 },{ 5,6 },{ 1,6 },{ 3,-6 },{ 4,-6 },{ 5,-6 },{ -6,-5 },
	{ -6,-4 },{ -6,-6 },{ 6,-4 },{ -3,-6 },{ -6,-3 },{ -3,6 },{ -1,-6 },{ 4,6 },{ 0,6 },{ 6,-3 },{ -6,-1 },{ 6,0 },{ 6,-5 },{ 6,1 },{ -6,3 },{ 6,-6 },{ 6,3 },{ -2,-6 },
	{ 6,4 },{ 6,5 },{ -6,6 },{ 6,-2 },{ -6,1 },{ -4,6 },{ -2,6 },{ 6,2 },{ 1,-6 },{ -1,6 },{ 3,6 },{ 6,6 },

};*/

//保存地图障碍信息的列表
typedef Vector<FuBen*>	FubenList;

typedef memory::HandleMgr<Scene, SceneHandle, 1024> SceneHandleMgr;

class FBHandleMgr: public memory::HandleMgr<FuBen, FuBenHandle, 256>
{
	typedef memory::HandleMgr<FuBen, FuBenHandle, 256> Inherited;
public:
	FBHandleMgr(const char* desc);
	FuBen* GetPtr(FuBenHandle handle);
};

class FuBenMgr
{
//执行刷怪需要的参数，保证刷怪占用的时间片
	typedef struct tagRefreshPara
	{
		FuBen*	fuben_;//上次刷怪的副本
		int		scene_pos_;//上次刷怪的场景，这个不是场景id，而是在副本中场景的索引
		void setFB(FuBen* fb)
		{
			fuben_ = fb;
			scene_pos_ = 0;
		}
		void setScene(int i)
		{
			scene_pos_ = i;
		}
	} RefreshPara;

public:
	FuBenMgr(void);
	virtual ~FuBenMgr(void);
public:
	//组件的销毁函数，这里要消耗一些S分配的内存
	void Destroy();

	//创建一批空闲的副本备用
	//void CreateFreeFb();

	/*
	* Comments: 实体请求进入一个副本
	* Param CEntity * pEntity: 实体的指针
	* Param unsigned int hFbHandle: 副本的handle
	* Param unsigned int nScenceID: 场景的ID
	* Param int nPosX: 位置x
	* Param int nPosY: 位置y
	teleport: 是否经过传送门
	* @Return bool:    成功返回true，否则返回false
	*/
	//inline bool EnterFuBen(Entity* et, unsigned int fb_handle, int sid)
	//{
	//	FuBenHandle hHandle(fb_handle);
	//	FuBen* fb = fb_hdl_mgr_.GetPtr(hHandle);
	//	return EnterFuBen(et, fb, sid);
	//}

	// sindex 场景序号
	bool EnterFuBen(Entity* et, FuBen* fb = NULL, int sid = 0, int x = 0, int y = 0, bool pix = false);

	/*
	* Comments: 获取一个副本的静态拷贝的指针，每个副本份都至少有1份拷贝，普通场景是1份，其他场景可能是多份，但是静态的只有1份
	* Param unsigned int nFbId:
	* @Return CFuBen *:
	*/
	//inline FuBen* GetFbStaticDataPtr(int fbId)
	//{
	//	if (fbId < 0 || fbId >= static_fb_list_.count())
	//	{
	//		OutputMsg(rmWaning, ("Enter fb fail for fBid=%d is invalid"), fbId);
	//		return NULL;
	//	}

	//	return static_fb_list_[fbId];
	//}

	/*
	* Comments: 通过场景的名字返回副本的指针和场景的指针，主要用于GM指令的传送
	* Param const char* sSceneName:  场景名字
	* Param CFuBen * & pRetFb: 副本的指针
	* Param CScene * & pRetScene: 场景的指针
	* @Return bool: 如果找到了返回true，否则返回false
	*/
	bool GetFbPtrBySceneName(const char* scene_name, FuBen*& ret_fb, Scene*& ret_scen);

	//每次逻辑循环都需执行一次的操作
	void RunOne();

	//inline FubenList* GetFbList() { return &static_fb_list_; }

	//生成一个新的副本
	FuBen* CreateFuBen(int nFbId);
	bool CreateStaticFuBen();


	//删除一个副本,释放资源
	void ReleaseFuBen(FuBen* fb);

	void* CreateMonster(unsigned int hScene, unsigned int nMonsterid, Pos pos, unsigned int nLiveTime, void* met = NULL );

	void* createDropBag(unsigned int hScene, int type, int id, int count, int x, int y, ActorId belong_id = 0);

	// 释放资源
	void GC();

	FuBen* GetFubenPtr(FuBenHandle handle);
	FuBen* GetFuben(FuBenUId uid);
	FuBen* GetFubenFromID(int uid);
	Scene* GetScenePtr(SceneHandle handle);
	FuBen* GetStaticFuben() { return static_fb_; }

	void FreeScene(SceneHandle handle);

	//Scene* AllocSceneHandle(SceneHandle& handle);
	//FuBen* AllocFubenHandle(FuBenHandle& handle);
	void RegMonsterDamageEvent(int fid);
	bool HasMonsterDamageEvent(int fid);
	void RegActorDamageEvent(int fid);
	bool HasActorDamageEvent(int fid);

private:

	void OnInitFuben(int id, unsigned int hfb);
	FuBen* AllocNewFb(int fbid, bool run = true);
	Scene* AllocNewScene(FuBen *fb, int sid);
	FuBenUId AllocNewUId();


private:
	union FuBenSeries
	{
		FuBenUId uid;
		struct
		{
			unsigned int time;
			unsigned int series;
		};
	};
	//游戏中出现的所有副本copy,不包括m_vStaticFbList里面的
	Vector<FuBen*, 256>	all_fb_list_;
	FuBen*				static_fb_;		// 0号副本
	std::map<FuBenUId, FuBen*> fb_map_;	// 副本索引
	FuBenSeries			fb_series_;  // 副本序列号记录

	//副本的静态实例，其他副本都从这些副本中clone出来
	//里面的实例都是new出来，没有使用HandleManager内存管理
	//FubenList			static_fb_list_;

	//所有地图的障碍信息列表
	//Vector<MAPDATA*, 16> map_data_list;

	//Vector<FubenList*, 512>	free_fb_list_;	// 保存空闲的副本列表,便于重用
	Timer			ref_timer_; // 副本刷新定时器
	Timer			logic_script_timer_;  // 副本脚本执行定时器
	std::map<int, bool> fb_monster_damage_event_flags_; // 副本怪物受伤事件标记
	std::map<int, bool> fb_actor_damage_event_flags_;	//副本玩家受伤事件标记

public:
	//全局的场景管理内存块
	FBHandleMgr		fb_hdl_mgr_;
	//全局的场景管理内存块
	SceneHandleMgr	scene_hdl_mgr_;

	//static RefreshPara		refreshPara_;
};


