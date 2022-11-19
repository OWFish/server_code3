#pragma once

/***************************************************************
* 实体移动系统
* 模拟实体的移动和跳跃
***************************************************************/

#include <stdint.h>
#include "data_packet_reader.hpp"
#include "timer.h"
#include "game_world_def.h"


class Scene;
class Creature;
class MoveSystem
{
public:
	enum SpecialMoveType{
		SMT_InstantMove = 0,
		SMT_DashMove	= 1,	// 冲撞
		SMT_RepelMove   = 2,    // 击退
	};
public:
	MoveSystem(Creature*);
	~MoveSystem();


	//定时检查，主要是怪物寻路用的
	void OnTimeCheck(int64_t nTick);
	void OnDeath();
	// todo void OnChangeSpeed();
	//void OnSpeedChange();

	bool StartMove(const Point& tarPos);
	// 在当前时间检查实体移动到的位置，mustStop表示是否强制停止移动
	void MovingTime(bool mustStop, bool sendPos);
	void StopMove();
	bool IsMoving() { return last_t_ != 0; }
	//void ResetMovingSpeed();
	bool InstantMove(const Point& pos);
	void ClearMoveData(); // 清除移动数据缓存
	void OnExitScene();
	//启动副本寻路
	void StartFubenPathToTarget();
private:
	void NotifySpecialMove(const Point& pos, int move_type);
	void NotifyStopMove(const Point& pos);
	bool GetMovablePoint(const Point& pos, int range, Point& ret);

private:
	Creature *self_;
	Timer	move_timer_;	// 逻辑运行间隔
	int64_t last_t_;	// 开始移动的时间
	DPoint last_pos_;
	Grid	last_tar_pos_;

	int64_t test_time_;
};

