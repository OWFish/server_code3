#pragma once

#include "config/game_config_data.h"
#include <map>
#include "utils/singleton.h"

struct SceneAreaParm {
	std::vector<int> iparm;
	SceneAreaParm(void) {
		iparm.clear();
	}
};

struct SceneArea {
	std::map<uint32_t,SceneAreaParm> attri;//����Ͳ�������
	uint32_t ref_count;//���ø���
	uint32_t mark;//�����ʶ;�ڱ�ʶ��ͬ�ĸ����л��ᵼ�´��������л��ص�
	SceneArea(void) {
		mark = 0;
		ref_count = 0;
		attri.clear();
	}
	SceneArea &operator+=(const SceneArea &r) {
		for (auto it:r.attri) {
			this->attri[it.first] = it.second;
		}
		return *this;
	}
};

struct SceneConfig
{
	int sid;
	int enter_x;
	int enter_y;
	int size_x;
	int size_y;
	char turn;
	std::string map_data;
	std::vector<SceneArea*> areas;//�����б�
};
typedef std::map<uint32_t, SceneArea* > AreaMap;
typedef std::map<uint32_t, AreaMap> SceneAreaMap;
class SceneConfigPool :public Singleton<SceneConfigPool>
{
public:
	friend Singleton<SceneConfigPool>;

	static bool Load(GameConfigData* data);
	static void LoadAllGrid(GameConfigData* data, std::vector<Grid> &allGrid, int &left, int &top, int &right, int &bottom);
	static void SetAreaOutline(SceneConfig &conf, std::vector<Grid> &all_grid, SceneArea *area, uint32_t index, AreaMap &area_pool_);
	static void FillArea(SceneConfig &conf, SceneArea *area, int left, int top, int right, int bottom, uint32_t index, AreaMap &area_pool_);
	static bool isAreaInIndex(SceneArea *area, uint32_t index);
	static const SceneConfig* Get(int id);
	static void Destructor();
private:
	static std::map<int, SceneConfig> config_pool_;
	static SceneAreaMap scene_area_pool_;
};



