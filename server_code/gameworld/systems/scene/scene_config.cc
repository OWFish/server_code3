#include "StdAfx.h"
#include "scene_config.h"


std::map<int, SceneConfig> SceneConfigPool::config_pool_;
SceneAreaMap SceneConfigPool::scene_area_pool_;

bool SceneConfigPool::Load(GameConfigData* data)
{
	if (!data->openGlobalTable("ScenesConfig")) {
		OutputMsg(rmError, ("can't open scene table"));
		return false;
	}

	if (data->enumTableFirst()) {
		do {
			SceneConfig conf;
			int ndef = 0;
			//bool valid = false;
			string::AnsiString r;

			conf.sid = data->getFieldInt("sceneid");
			conf.enter_x = data->getFieldInt("enterX");
			conf.enter_y = data->getFieldInt("enterY");
			conf.size_x = data->getFieldInt("sizeX", &ndef);
			conf.size_y = data->getFieldInt("sizeY", &ndef);
			const char* temp = data->getFieldString("mapfilename");
			//conf.map_data = data->getFieldString("mapfilename");
			conf.map_data = temp;
			conf.turn = data->getFieldInt("turn", &ndef);
			conf.areas.clear();
			if (data->fieldTableExists("area") && data->openFieldTable("area")) {
				AreaMap &area_pool_ = scene_area_pool_[conf.sid];
				if (data->enumTableFirst()) {
					size_t vec_size = (conf.size_x+1)*(conf.size_y+1);
					conf.areas.resize(vec_size);
					//还是初始化一下比较安全
					for (int i = 0; i < (int)conf.areas.size(); ++i) {
						conf.areas[i] = NULL;
					}
					uint32_t index = 0;
					do {
						//读取所有线段,和边界点
						std::vector<Grid> all_grid; int left = conf.size_x+1, top = conf.size_y+1, right = 0, bottom = 0;
						LoadAllGrid(data, all_grid, left, top, right, bottom);
						if (all_grid.size() > 3 && data->fieldTableExists("attr") && data->openFieldTable("attr")) {
							if (data->enumTableFirst()) {
								//生成区域对象
								SceneArea *area = new SceneArea();
								//读取区域属性
								do {
									int type = data->getFieldInt("type");
									if (type >= 0 && type < aaAttrCount) {
										SceneAreaParm sap;
										//获取区域参数
										if (data->fieldTableExists("iparm") && data->openFieldTable("iparm")) {
											if (data->enumTableFirst()) {
												do {
													sap.iparm.push_back(data->getFieldInt(NULL));
												} while (data->enumTableNext());
											}
											data->closeTable();
										}
										//获取区域参数结束
										area->attri[type] = sap;
									}
								} while (data->enumTableNext());
								area->mark = 1 << index;
								area_pool_[area->mark] = area;
								//填充图形轮框边缘
								SetAreaOutline(conf, all_grid, area, index, area_pool_);
								//填充图形内部
								FillArea(conf, area, left, top, right, bottom, index, area_pool_);
								++index;
							}//if (data->enumTableFirst())
							data->closeTable();
						}
					} while (data->enumTableNext());
				}
				data->closeTable();
				//在最后;回收一些引用计数为0的SceneArea
				for (AreaMap::iterator it = area_pool_.begin(); it != area_pool_.end();) {
					if (it->second && it->second->ref_count > 0) {
						++it;
						continue;
					}
					if (it->second) SafeDelete(it->second);
					it = area_pool_.erase(it);
				}
			}
			//todo field scenes
			config_pool_[conf.sid] = conf;
		} while (data->enumTableNext());
	} else {
		OutputMsg(rmError, "instanceConfig is null");
	}

	data->closeTable();

	return true;
}

void SceneConfigPool::LoadAllGrid(GameConfigData* data, std::vector<Grid> &allGrid, int &left, int &top, int &right, int &bottom) {
	if (data->fieldTableExists("grids") && data->openFieldTable("grids")) {
		if (data->enumTableFirst()) {
			do {
				int x = data->getFieldInt("x");
				int y = data->getFieldInt("y");
				allGrid.push_back(Grid(x, y));
				if (x < left) left = x;
				if (x > right) right = x;
				if (y > bottom) bottom = y;
				if (y < top) top = y;
			} while (data->enumTableNext());
		}//if (data->enumTableFirst())
		data->closeTable();
	}
}

void SceneConfigPool::SetAreaOutline(SceneConfig &conf, std::vector<Grid> &all_grid, SceneArea *area, uint32_t index, AreaMap &area_pool_) {
	int vsize = (int)all_grid.size();
	for (int i = 0; i < vsize; ++i) {
		Grid *p1 = &(all_grid[i]);
		Grid *p2 = NULL;
		if (i + 1 == vsize) p2 = &(all_grid[0]);
		else p2 = &(all_grid[i + 1]);
		//填充直线格仔
		double k = (p2->y - p1->y) * 1.0 / (p2->x - p1->x);
		double b = p2->y - k * p2->x;//直线算法
		int dx = p2->x > p1->x ? 1 : -1;	// x方向遍历
		int loop = abs(p2->x - p1->x);//遍历次数
		if (loop == 0)   //纵向遍历y坐标
		{
			int dy = p2->y > p1->y ? 1 : -1;	// x方向遍历
			int count = abs(p2->y - p1->y);//遍历次数
			for (int i = 0;i < count ;++i)
			{
				if ((p1->y + (i * dy))*conf.size_x + p1->x < conf.areas.size())
				{
					conf.areas[(p1->y + (i * dy))*conf.size_x + p1->x] = area;
					++area->ref_count;
				}

			}
		}
		for (int j = 0; j < loop; ++j) {
			int x = (p1->x + j*dx);
			int y = static_cast<int>(k*x + b);

			if (conf.areas[y*conf.size_x + x]) {
				uint32_t new_mark = (conf.areas[y*conf.size_x + x])->mark | area->mark;
				SceneArea *new_area = NULL;
				{
					AreaMap::iterator it = area_pool_.find(new_mark);
					if (it == area_pool_.end()) {
						new_area = new SceneArea();
						(*new_area) = *(conf.areas[y*conf.size_x + x]);
						(*new_area) += (*area);
						area_pool_[new_mark] = new_area;
					} else {
						new_area = it->second;
					}
				}
				--((conf.areas[y*conf.size_x + x])->ref_count);
				conf.areas[y*conf.size_x + x] = new_area;
				++new_area->ref_count;
			} else {
				conf.areas[y*conf.size_x + x] = area;
				++area->ref_count;
			}
		}
	}
}

void SceneConfigPool::FillArea(SceneConfig & conf, SceneArea *area, int left, int top, int right, int bottom, uint32_t index, AreaMap &area_pool_) {
	for (int y = top; y <= bottom; ++y) { //横向遍历
		int start = -1; int stop = -1;
		bool canStart = false; bool findStop = false;
		for (int x = left; x <= right; ++x) { //打横的一排
			//if (!canStart && conf.areas[y*conf.size_x + x] == area) {
			if (!canStart && isAreaInIndex(conf.areas[y*conf.size_x + x], index)) {
				canStart = true;
			//} else if (canStart && !findStop && conf.areas[y*conf.size_x + x] != area) {
			} else if (canStart && !findStop &&	!isAreaInIndex(conf.areas[y*conf.size_x + x], index)) {
				start = x;
				findStop = true;
			//} else if (canStart && findStop && conf.areas[y*conf.size_x + x] == area) {
			} else if (canStart && findStop && isAreaInIndex(conf.areas[y*conf.size_x + x], index)) {
				stop = x;
				break;
			}
		}
		if (start != -1 && stop != -1) {
			for (int x = start; x < stop; ++x) {

				if (conf.sid == 1)
				{
					//OutputMsg(rmError, "----------22222-------. x:%d, y:%d   %d", x, y,0);
				}
				if (conf.areas[y*conf.size_x + x]) {
					uint32_t new_mark = (conf.areas[y*conf.size_x + x])->mark | area->mark;
					SceneArea *new_area = NULL;
					{
						AreaMap::iterator it = area_pool_.find(new_mark);
						if (it == area_pool_.end()) {
							new_area = new SceneArea();
							(*new_area) = *(conf.areas[y*conf.size_x + x]);
							(*new_area) += (*area);
							area_pool_[new_mark] = new_area;
						} else {
							new_area = it->second;
						}
					}
					--((conf.areas[y*conf.size_x + x])->ref_count);
					conf.areas[y*conf.size_x + x] = new_area;
					++new_area->ref_count;
				} else {
					conf.areas[y*conf.size_x + x] = area;
					++area->ref_count;
				}
			}
		}
	}
}

bool SceneConfigPool::isAreaInIndex(SceneArea *area, uint32_t index) {
	if (!area) return false;
	return area->mark & (1 << index)?true:false;
}

const SceneConfig* SceneConfigPool::Get(int id)
{
	auto it = config_pool_.find(id);
	if (it == config_pool_.end())
		return nullptr;
	return &it->second;
}

void SceneConfigPool::Destructor() {
	for (auto it : scene_area_pool_) {
		for (auto iit:it.second) {
			SafeDelete(iit.second);
		}
	}
	scene_area_pool_.clear();
	config_pool_.clear();
}
