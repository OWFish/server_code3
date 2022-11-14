#include "StdAfx.h"
#include "scene_grid.h"


EntityGrid::EntityGrid(): entitys_(&GameEngine::global_var_->entity_grid_alloc_)
{

}

EntityGrid::~EntityGrid()
{
	entitys_.empty();
}


SceneGrid::SceneGrid()
{
	rows_ = 0;
	cols_ = 0;
	grids_ = NULL;
	scene_ = NULL;
}

SceneGrid::~SceneGrid()
{
	Release();
}

void SceneGrid::Release()
{
	if (grids_)
	{
		GameMap *map = scene_->GetMap();
		int count = 0;
		if (map)
		{
			count = map->getUnitCount();
		}

		for (int i = 0; i < count; ++i)
		{
			grids_[i].~EntityGrid();
		}

		GameEngine::global_var_->scene_grid_alloc_.FreeBuffer(grids_);
	}

	grids_ = NULL;
	rows_ = 0;
	cols_ = 0;
	scene_ = NULL;
}


void SceneGrid::Reset()
{
	if (!grids_ || !scene_) return;
	GameMap *map = scene_->GetMap();
	if (!map) return;

	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	int gcount = map->getUnitCount();

	for (int j = 0; j < gcount; j++)
	{
		EntityHandle* entitys = grids_[j].entitys_;

		for (int i = grids_[j].entitys_.count() - 1; i >= 0; i--)
		{
			int type = entitys[i].GetType();

			// 怪物要清除，npc不清理，重用，角色在其他地方删,宠物会跟随玩家移出
			if (enMonster == type || enMovingNPC == type ||
			        enDropBag == type || enGatherMonster == type)
				em->DestroyEntity(entitys[i]);
		}
	}
}

//重新设置网格的大小
void SceneGrid::Init()
{
	if (!scene_) return;
	GameMap *map = scene_->GetMap();
	if (!map) return;

	if (grids_)
	{
		Release();
	}

	int count = map->getUnitCount();
	int size = count * sizeof(EntityGrid);

	grids_ = (EntityGrid*)GameEngine::global_var_->scene_grid_alloc_.AllocBuffer(size);

	for (int i = 0; i < count; ++i)
	{
		new(grids_ + i)EntityGrid();
	}

	rows_ = map->getWidth();
	cols_ = map->getHeight();
}



// 场景中删除一个实体（实体死亡或退出游戏）
void SceneGrid::DelEntity(Entity* et)
{
	if (!et) return;

	int x , y;
	et->GetPosition(x, y);

	x = x / GRIDSIZE;
	y = y / GRIDSIZE;

	EntityGrid* grid = GetList(x, y);

	if (grid) grid->remove(et->GetHandle());

}

bool SceneGrid::MoveTo(Entity* et, const Point& pos)
{
	if (!et) return false;

	EntityHandle handle = et->GetHandle();

	int old_x = 0 , old_y = 0;
	et->GetPosition(old_x, old_y);

	old_x = old_x / GRIDSIZE;
	old_y = old_y / GRIDSIZE;

	Pos tmpGrid(pos);

	EntityGrid* grid = GetList(old_x, old_y);
	EntityGrid* new_grid = GetList(tmpGrid.x, tmpGrid.y);

	if (!grid || !new_grid)
	{
		OutputMsg(rmError, ("%s get grid null[%d, %d] when remove"), __FUNCTION__, tmpGrid.x, tmpGrid.y);
		return false;
	}
	if (grid != new_grid)
	{
		grid->remove(handle);
		new_grid->add(handle);
	}

	return true;
}

bool SceneGrid::AddEntity(Entity* et, int x, int y)
{
	if (!et) return false;

	EntityHandle handle = et->GetHandle();

	EntityGrid* grid = GetList(x, y);

	if (!grid)
	{
		OutputMsg(rmError, ("%s get grid null[%d, %d]"), __FUNCTION__, x, y);
		return false;
	}

	grid->add(handle);
	return true;
}


EntityGrid* SceneGrid::GetList(int x, int y)
{
	if (!scene_) return NULL;
	GameMap *map = scene_->GetMap();
	if (!map) return NULL;

	int nPosIdx = map->getPosIndex((unsigned int)x, (unsigned int)y);

	if (nPosIdx >= 0)
		return &grids_[nPosIdx];

	return NULL;
}




