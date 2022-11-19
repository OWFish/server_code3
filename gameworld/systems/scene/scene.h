#pragma once

#ifndef _SCENE_H_
#define _SCENE_H_

#include "scene_def.h"
#include "scene_config.h"


/**************************
	ʵ�ֳ���������ص���
****************************/
class Actor;
typedef memory::Handle  SceneHandle;
class Scene
{
	friend class FuBen;
public:
	Scene();
	~Scene();

	//void ReleaseConfig();

	//���ó�����id��ͬʱҪ��һЩ��ʼ���Ĺ���
	inline int GetId() { return scene_conf_ ? scene_conf_->sid : -1; }

	bool Init(FuBen* fuben, int id);
	inline void SetHandle(SceneHandle handle) { handle_ = handle; }
	inline SceneHandle GetHandle() { return handle_; }

	inline const SceneConfig* GetSceneConf() { return scene_conf_; }

	bool EnterScene(Entity* et, int x=0, int y=0, bool pix = false);
	void ExitScene(Entity* et);

	void OnEntityEnter(Entity* et);
	void OnActorEnter(Actor* et); // ��Ҫ��actor EnterScene�д������Ե����ó���
	void OnEntityExit(Entity* et);

	void RemoveEntity(EntityHandle handle);

	bool CanMove(const Grid& pos);
	bool MoveTo(Entity* et, const Point& pos);
	//void NoticMeAppear(Entity* et);
	//void MoveNotice(Entity* et, int old_x, int old_y, int new_x, int new_y);
	//void NoticAppear(int start_x, int end_x, int i, Entity* et, DataPacket** ptr, DataPacket* appear_pack);
	//void NoticMeAppear(int start_x, int end_x, int i, Animal* et);
	//void NoticDisappear(int start_x, int end_x, int i, EntityHandle handle, Entity* et);
	//void NoticMeDisappear(int start_x, int end_x, int i, int type, ObserverSystem* obser);
	GameMap* GetMap() { return map_; }

	bool RunOne();

	void SendChatMsg(const char* szMsg, SceneHandle nSrc, SceneHandle nDest);
	void BroadcastAppear(Entity* et);
	void BroadcastDisappear(Entity* et);

	void AddDeathEntity(Entity* et);
	void ExitAllActor();

	inline int GetMonsterCount() { return entity_list_[EntityType_Monster].count(); }
	inline FuBen* GetFuBen() { return fuben_; }
	inline EntityList& GetActorList() { return entity_list_[EntityType_Actor]; }
	inline EntityList& GetMonsterList() { return entity_list_[EntityType_Monster]; }
	inline EntityList& GetRoleList() { return entity_list_[EntityType_Role]; }
	inline EntityList& GetCloneRoleList() { return entity_list_[EntityType_CloneRole]; }
	inline EntityList& GetDropBagList() { return entity_list_[EntityType_DropBag]; }
	bool GetEntityList(VisiHandleList& list);
	bool GetEntityListReDrop(VisiHandleList& list, Creature *et);
	bool GetMonsterList(VisiHandleList& list);
	int GetDropBagCount();

	bool GetGridEntityList(int x, int y, VisiHandleList& list);
	int GetGridEntityCount(int x, int y);

	bool IsKillAllMonster(int mid);
	void KillFubenMonsters(); // ��ʱû����������ʧ

	void SendData(const void* buf, size_t size, Actor* except = NULL);
	void SendDataNoActor(const void* buf, size_t size, Actor* except = NULL);
	template<class ProtoType>
	void SendData(ProtoType& proto, Actor* except = NULL) { SendData(&proto, sizeof(proto), except); }
	void SendData(DataPacket& pack, Actor* except = NULL);
	void SendPacket(DataPacket* pack, Actor* except = NULL);
	bool CloneRoleEmpyt(void); //
	bool HasAreaAttr(const SceneAreaAttrDef attr, const Point &point);
	bool HasAreaAttr(const SceneAreaAttrDef attr, const Grid &grid);
	const std::vector<int>* GetAreaAttriparm(const SceneAreaAttrDef attr, const Grid &grid);
	uint32_t GetAreaMask(const Grid &grid);
	const SceneArea* GetArea(const Grid &grid);
	bool isLeapArea(const Grid &old_grid, const Grid &new_grid);

private:
	GameMap*		map_;	//��ͼ���ϰ���Ϣ // ly ��ʱδ����
	const SceneConfig*	scene_conf_;//������������Ϣ��ע�⣬������������ʹ�����ָ�루��CLogicEngine::InitReserveScene��������)
	int				width_;
	int				height_;
	SceneHandle		handle_;
private:
	//SceneGrid		grid_;	//����
	FuBen*			fuben_;

	//����������б�
	//EntityList			actor_list_;
	//EntityList			role_list_;
	//EntityList			monster_list_;
	EntityList			entity_list_[EntityType_Count];

	EntityList			death_list_;//��������ʵ����б����Ҫ���ڼ�飬���������
	Timer				death_list_timer_;	//0.5�����������Ĺ���һ��
	int					scene_size_output_counter_;
};

#endif
