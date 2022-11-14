#ifndef _SCENE_GRID_H_
#define _SCENE_GRID_H_

/************************
	实现场景中网格的管理和操作
***********************/
class Entity;
class Scene;

// 定义游戏中单个实体格子
typedef container::Vector<EntityHandle, 4> GridEntityVector;

class EntityGrid
{
public:
	EntityGrid();
	~EntityGrid();

	void add(EntityHandle handle)
	{
		entitys_.add(handle);
	}
	void remove(EntityHandle handle)
	{
		int count = entitys_.count();
		EntityHandle* list = entitys_;

		for (int i = 0; i < count; ++i)
		{
			if (list[i] == handle)
			{
				--count;

				if (i != count) list[i] = list[count];

				entitys_.trunc(count);
			}
		}
	}

	GridEntityVector entitys_;		// 格子中的实体列表
};


class SceneGrid
{
	friend class Scene;
public:
	SceneGrid();
	virtual ~SceneGrid();

	void SetScene(Scene* s) { scene_ = s; }

	EntityGrid* GetList(int x, int y);

	//释放资源
	void Release();

	//只清理怪物和玩家，以备重用
	void Reset();

	//重新设置网格的大小
	void Init();


	/*
	* Comments: 进入,删除,移动实体
	* Parameter: Entity * et: pEntity:实体指针
	* Parameter: int x: 坐标x
	* Parameter: int y: 坐标y
	* Returns: int: SCENE_ERR
	*/
	bool AddEntity(Entity* et, int x, int y);
	void DelEntity(Entity* et);
	bool MoveTo(Entity* et, const Point& pos);



private:
	/*
	* Comments:判断指定的xy坐标是否能走动的点
	* Param int x:x坐标
	* Param int y:y坐标
	* @Return bool:
	*/
	bool CanMove(int x, int y);

private:
	//网格的行数和列数
	int	rows_;
	int	cols_;

	EntityGrid*	grids_;	// 格子集合，用于一个维护一个场景中的所有小格子列表
	Scene* scene_;
};

#endif


