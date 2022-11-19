#pragma once

/***************************************************************
* ʵ���ƶ�ϵͳ
* ģ��ʵ����ƶ�����Ծ
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
		SMT_DashMove	= 1,	// ��ײ
		SMT_RepelMove   = 2,    // ����
	};
public:
	MoveSystem(Creature*);
	~MoveSystem();


	//��ʱ��飬��Ҫ�ǹ���Ѱ·�õ�
	void OnTimeCheck(int64_t nTick);
	void OnDeath();
	// todo void OnChangeSpeed();
	//void OnSpeedChange();

	bool StartMove(const Point& tarPos);
	// �ڵ�ǰʱ����ʵ���ƶ�����λ�ã�mustStop��ʾ�Ƿ�ǿ��ֹͣ�ƶ�
	void MovingTime(bool mustStop, bool sendPos);
	void StopMove();
	bool IsMoving() { return last_t_ != 0; }
	//void ResetMovingSpeed();
	bool InstantMove(const Point& pos);
	void ClearMoveData(); // ����ƶ����ݻ���
	void OnExitScene();
	//��������Ѱ·
	void StartFubenPathToTarget();
private:
	void NotifySpecialMove(const Point& pos, int move_type);
	void NotifyStopMove(const Point& pos);
	bool GetMovablePoint(const Point& pos, int range, Point& ret);

private:
	Creature *self_;
	Timer	move_timer_;	// �߼����м��
	int64_t last_t_;	// ��ʼ�ƶ���ʱ��
	DPoint last_pos_;
	Grid	last_tar_pos_;

	int64_t test_time_;
};

