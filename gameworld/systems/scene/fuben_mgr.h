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


//һ��48��������ߵ���߱������ҵ�һ�����ʵ�λ��
/*static	BYTE s_matrix[][2] =
{
	//��1Ȧ8��
	{ -1,2 },{ 0,1 },{ 2,-1 },{ -1,0 },{ 1,0 },{ 1,-2 },{ 0,-1 },{ 0,2 },

	//��2Ȧ16��
	{ 1,-1 },{ -1,-2 },{ 1,1 },{ 0,-3 },{ -2,-2 },{ -2,-3 },{ -1,1 },{ 2,-2 },{ 1,3 },{ -2,2 },{ -1,-1 },{ 1,-3 },{ 3,-2 },{ 2,2 },{ -2,0 },{ -3,1 },{ -2,-1 },

	//��3Ȧ24��
	{ -2,1 },{ 2,1 },{ -3,-1 },{ 1,2 },{ -1,-3 },{ 2,0 },{ -3,-3 },{ 3,2 },{ -3,2 },{ 3,-1 },{ 3,0 },{ 0,3 },{ 3,1 },
	{ -3,3 },{ -3,-2 },{ 3,3 },{ -1,3 },{ -3,0 },{ 3,-3 },{ 2,3 },

	//��4Ȧ32��
	{ -3,-4 },{ 0,4 },{ -1,-4 },{ 1,-4 },{ -4,2 },{ 4,4 },{ 2,-4 },{ 3,-4 },{ -2,4 },{ 4,-4 },{ 2,4 },{ -4,-3 },{ 4,-3 },{ 4,3 },{ -4,-2 },{ -4,4 },{ 4,-2 },{ 4,1 },
	{ -4,-4 },{ 0,-4 },{ -4,0 },{ -4,-1 },{ 4,0 },{ -4,1 },{ 4,1 },{ -2,-4 },{ 4,2 },{ -4,3 },{ -3,4 },{ -1,4 },{ 1,4 },{ 3,4 },

	//��5Ȧ40��
	{ -4,-5 },{ -2,5 },{ -3,-5 },{ 5,-2 },{ -1,-5 },{ 1,5 },{ 0,-5 },{ 2,-5 },{ -5,2 },{ 4,5 },{ 5,0 },{ 5,3 },{ -5,-4 },{ 5,-3 },{ -5,5 },
	{ -5,-2 },{ -5,-1 },{ 5,1 },{ 3,-5 },{ -5,0 },{ 5,-4 },{ -5,1 },{ 5,1 },{ 5,2 },{ 5,-5 },{ -5,3 },{ -5,4 },{ -5,-3 },{ 5,4 },{ -4,5 },
	{ -5,-5 },{ -3,5 },{ -1,5 },{ -2,-5 },{ 0,5 },{ 2,5 },{ 1,-5 },{ 3,5 },{ 5,5 },{ 4,-5 },

	//��6Ȧ48��
	{ -5,-6 },{ 6,1 },{ -6,5 },{ -4,-6 },{ -6,0 },{ -5,6 },{ -6,-2 },{ 0,-6 },{ 2,6 },{ -6,2 },{ -6,4 },{ 2,-6 },{ 5,6 },{ 1,6 },{ 3,-6 },{ 4,-6 },{ 5,-6 },{ -6,-5 },
	{ -6,-4 },{ -6,-6 },{ 6,-4 },{ -3,-6 },{ -6,-3 },{ -3,6 },{ -1,-6 },{ 4,6 },{ 0,6 },{ 6,-3 },{ -6,-1 },{ 6,0 },{ 6,-5 },{ 6,1 },{ -6,3 },{ 6,-6 },{ 6,3 },{ -2,-6 },
	{ 6,4 },{ 6,5 },{ -6,6 },{ 6,-2 },{ -6,1 },{ -4,6 },{ -2,6 },{ 6,2 },{ 1,-6 },{ -1,6 },{ 3,6 },{ 6,6 },

};*/

//�����ͼ�ϰ���Ϣ���б�
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
//ִ��ˢ����Ҫ�Ĳ�������֤ˢ��ռ�õ�ʱ��Ƭ
	typedef struct tagRefreshPara
	{
		FuBen*	fuben_;//�ϴ�ˢ�ֵĸ���
		int		scene_pos_;//�ϴ�ˢ�ֵĳ�����������ǳ���id�������ڸ����г���������
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
	//��������ٺ���������Ҫ����һЩS������ڴ�
	void Destroy();

	//����һ�����еĸ�������
	//void CreateFreeFb();

	/*
	* Comments: ʵ���������һ������
	* Param CEntity * pEntity: ʵ���ָ��
	* Param unsigned int hFbHandle: ������handle
	* Param unsigned int nScenceID: ������ID
	* Param int nPosX: λ��x
	* Param int nPosY: λ��y
	teleport: �Ƿ񾭹�������
	* @Return bool:    �ɹ�����true�����򷵻�false
	*/
	//inline bool EnterFuBen(Entity* et, unsigned int fb_handle, int sid)
	//{
	//	FuBenHandle hHandle(fb_handle);
	//	FuBen* fb = fb_hdl_mgr_.GetPtr(hHandle);
	//	return EnterFuBen(et, fb, sid);
	//}

	// sindex �������
	bool EnterFuBen(Entity* et, FuBen* fb = NULL, int sid = 0, int x = 0, int y = 0, bool pix = false);

	/*
	* Comments: ��ȡһ�������ľ�̬������ָ�룬ÿ�������ݶ�������1�ݿ�������ͨ������1�ݣ��������������Ƕ�ݣ����Ǿ�̬��ֻ��1��
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
	* Comments: ͨ�����������ַ��ظ�����ָ��ͳ�����ָ�룬��Ҫ����GMָ��Ĵ���
	* Param const char* sSceneName:  ��������
	* Param CFuBen * & pRetFb: ������ָ��
	* Param CScene * & pRetScene: ������ָ��
	* @Return bool: ����ҵ��˷���true�����򷵻�false
	*/
	bool GetFbPtrBySceneName(const char* scene_name, FuBen*& ret_fb, Scene*& ret_scen);

	//ÿ���߼�ѭ������ִ��һ�εĲ���
	void RunOne();

	//inline FubenList* GetFbList() { return &static_fb_list_; }

	//����һ���µĸ���
	FuBen* CreateFuBen(int nFbId);
	bool CreateStaticFuBen();


	//ɾ��һ������,�ͷ���Դ
	void ReleaseFuBen(FuBen* fb);

	void* CreateMonster(unsigned int hScene, unsigned int nMonsterid, Pos pos, unsigned int nLiveTime, void* met = NULL );

	void* createDropBag(unsigned int hScene, int type, int id, int count, int x, int y, ActorId belong_id = 0);

	// �ͷ���Դ
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
	//��Ϸ�г��ֵ����и���copy,������m_vStaticFbList�����
	Vector<FuBen*, 256>	all_fb_list_;
	FuBen*				static_fb_;		// 0�Ÿ���
	std::map<FuBenUId, FuBen*> fb_map_;	// ��������
	FuBenSeries			fb_series_;  // �������кż�¼

	//�����ľ�̬ʵ������������������Щ������clone����
	//�����ʵ������new������û��ʹ��HandleManager�ڴ����
	//FubenList			static_fb_list_;

	//���е�ͼ���ϰ���Ϣ�б�
	//Vector<MAPDATA*, 16> map_data_list;

	//Vector<FubenList*, 512>	free_fb_list_;	// ������еĸ����б�,��������
	Timer			ref_timer_; // ����ˢ�¶�ʱ��
	Timer			logic_script_timer_;  // �����ű�ִ�ж�ʱ��
	std::map<int, bool> fb_monster_damage_event_flags_; // �������������¼����
	std::map<int, bool> fb_actor_damage_event_flags_;	//������������¼����

public:
	//ȫ�ֵĳ��������ڴ��
	FBHandleMgr		fb_hdl_mgr_;
	//ȫ�ֵĳ��������ڴ��
	SceneHandleMgr	scene_hdl_mgr_;

	//static RefreshPara		refreshPara_;
};


