#include "StdAfx.h"
#include "ai.h"
#include "ai_state.h"
#include "entity/monster/monster.h"
#include "move/move_system.h"
#include "skill/skill_system.h"
#include "skill/status_system.h"
#include "protos/base_proto.h"
#include "entity/monster/monster_config.h"

AIState::AIState(AI* ai_mgr, Creature *mon, const AIEventConfigs *conf, int frame_time)
: ai_mgr_(ai_mgr)
, frame_timer_(frame_time)
, frame_time_(frame_time)
, self_(mon)
, current_event_(NULL)
, state_start_time_(0)
{
	frame_timer_.SetNextHitTime(GetGameEngine()->getTickCount());
	//events_.resize(conf->size());
	for (std::size_t i = 0;  i < conf->size(); ++i)
	{
		//events_[i] = AIEvent(&(*conf)[i]);
		events_.push_back(AIEvent(&(*conf)[i]));
	}
}

AIState::~AIState()
{

}

void AIState::Update(int64_t now_t)
{
	if (frame_timer_.CheckAndSet(now_t, true)) {
		for (std::size_t i = 0; i < events_.size(); ++i)
		{
			events_[i].TryEvent(self_, this);
		}
	}
}

void AIState::Reset()
{
	static GameEngine* ge = GetGameEngine();
	int64_t now_t = ge->getTickCount();
	for (std::size_t i = 0; i < events_.size(); ++i)
	{
		events_[i].Reset(now_t);
	}
	state_start_time_ = static_cast<int>(now_t / 1000);
}

void AIState::OnEnterScene()
{
}

int AIState::GetStateTime()
{
	static GameEngine* ge = GetGameEngine();
	return ge->getMiniDateTime() - state_start_time_;
}

int AIState::GetDistance(Entity *tar)
{
	int offset = 0;
	if (tar->GetType() == EntityType_Monster)
	{
		offset = ((Monster*)tar)->GetConfig()->gsize;
	}
	return ::GetPixDistance(self_->GetPosition(), tar->GetPosition(), offset);
}

Entity* AIState::FindOtherEnemy()
{
	//static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	const AIConfig* aiconfig = ai_mgr_->GetConfig();
	{//怪打人的时候,进入这里: 需要怪物配置为追一个玩家打
		Entity* et = self_->GetTarget();
		if (et && aiconfig->maxDam) {
			Actor* actor = et->GetActor();
			if (actor) {
				et = actor->GetLiveByJob();
				if (!(NULL == et || et->GetPosInfo().scene != self_->GetPosInfo().scene)) {
					self_->SetTarget(et);
					return et;
				}
			}
		}
	}

	// 在受攻击时记录仇恨列表，选出下一个目标
	return ai_mgr_->SetTargetByDamageList();
}


bool PathLine(Scene *scene, const Pos& pt1, const Pos& pt2, Pos& out)
{
	out = pt1;
	Pos last = pt1;

	double k = 0;
	if (pt2.x == pt1.x) k = 1;
	else k = (pt2.y - pt1.y) * 1.0 / (pt2.x - pt1.x); // 直线方程 y = kx + b
	double b = pt2.y - k * pt2.x;

	// 第一个点先加进去
	int dx = pt2.x > pt1.x ? 1 : -1;	// x方向
	int dy = pt2.y > pt1.y ? 1 : -1;	// y方向

	int px = pt1.x + (dx > 0 ? 1 : 0);

	int loop = abs((int)pt1.x - (int)pt2.x);

	Pos pos = pt2;

	// i <= loop 多循环一次 是由于算法是在x轴方向上遍历递增，
	// 所以有可能在最后的点和pt2的x坐标相等，但y方向有差距的情况，所以最后循环是补全y轴的点
	for (int i = 0; i <= loop; i++, px += dx)
	{
		if (i != loop)
		{
			// x轴方向递增，每次计算出经过的格子
			pos.x = dx > 0 ? px : px - 1;
			pos.y = int(k * pos.x + b);
		}

		if (last.y != pos.y)
		{
			for (int j = last.y + dy;; j += dy)
			{
				//OutputMsg(rmTip, "test PathLine. (%d,%d)->(%d,%d) path: (%d,%d)",
				//	pt1.x, pt1.y, pt2.x, pt2.y, last.x, j);
				if (!scene->CanMove(Pos(last.x, j)))
				{
					return false;
				}
				out.x = last.x;
				out.y = j;

				if (j == pos.y) break;
			}
		}

		// i == loop 的情况下，point点其实是已经判断过了
		if (i != loop)
		{
			//OutputMsg(rmTip, "test PathLine. (%d,%d)->(%d,%d) path: (%d,%d)",
			//	pt1.x, pt1.y, pt2.x, pt2.y, pos.x, pos.y);
			if (!scene->CanMove(pos))
			{
				return false;
			}
			out = pos;
		}
		last = pos;
	}

	return true;
}


bool AIState::PathToTarget(const Point& tarPos, int skill_dis)
{
	Scene *scene = self_->GetScene();
	if (!scene) return false;
	Point pos(tarPos);
	Point cur_pos = self_->GetPosition();
	if (skill_dis > 0) {
		// 重新计算目的点
		Point dp(pos);
		dp -= cur_pos;
		double dis = sqrt(dp.x*dp.x + dp.y*dp.y);//与目标点的距离
		if (dis < skill_dis)
			return true;
		//按方向回退
		double k = (skill_dis - 1) / dis;
		dp.x = (int)(pos.x - (dp.x * k));
		dp.y = (int)(pos.y - (dp.y * k));
		if (scene->CanMove(Grid(dp))) {//先这样
			pos = dp;
		}
		/*
		Grid gpos(pos);
		if (scene->GetGridEntityCount(gpos.x, gpos.y) > 0) {
			int x, y;
			getDir(getDir(pos.x, pos.y, cur_pos.x, cur_pos.y), x, y);
			pos.x += x; pos.y += y;
		}
		*/
	}
	if (pos == self_->GetMoveDest())
		return true;

	if (cur_pos == pos)
		return true;

	Grid p1(cur_pos), p2(pos);
	Grid last(0, 0);

	//bool ret = true;
	FuBen * fuben = self_->GetFuBen();
	if (fuben && fuben->GetConfig() && fuben->GetConfig()->findPath != 0) {
		if (!PathLine(scene, p1, p2, last))	{
			//地图复杂寻路, 需要计算路线,目前先由客户端a*计算
			RequestFubenPathLine(pos);
			return false;
		}
	}

	self_->GetMoveSystem()->StartMove(pos);
	return true;
}

bool AIState::PathToMaster(int size) {	
	Scene *scene = self_->GetScene();
	if (!scene) return false;

	Entity *master = (Entity*)self_->GetMaster();
	if (!master) return false;
	//获取我的点,和主人的点
	const Point& mpos = master->GetPosition();
	const Point& spos = self_->GetPosition();
	//移动到距离它一格仔的地方
	//int range = wrand(size);
	int x = mpos.x > spos.x ? (mpos.x - size) : (mpos.x + size);
	//range = wrand(size);
	int y = mpos.y > spos.y ? (mpos.y - size) : (mpos.y + size);
	Point pos = Point(x, y);
	//判断算出来的位置是否可走
	if (!scene->CanMove(Grid(pos))) {
		//不可走,直接和主人站一起
		pos = mpos;
	}
	return PathToTarget(pos);
}

bool AIState::CheckState()
{
	if (!self_->GetStatusSystem()->CanControll())
		return false;

	if (self_->GetSkillSystem()->IsCasting())
		return false;

	// 如果正在执行某个action
	if (GetCurrentEvent())
		return false;
	if (self_->GetType() == EntityType_Role)
	{
		Role* role = (Role*)self_;
		if (role->GetActor()->GetCurrGatherMonster())
		{
			//在采集不能攻击
			return false;
		}
	}else if (self_->GetType() == EntityType_Monster) {
		auto m = self_->GetMaster();
		if (m != nullptr && m->GetType() == EntityType_Role)
		{
			auto role = (Role*)m;
			if (role->GetActor()->GetCurrGatherMonster())
			{
				return false;
			}
		}
	}
	// 正在移动 -- 没有正在移动了
	//if (self->GetMoveSystem().IsMoving())
	//	return false;

	return true;
}

bool AIState::IsExistFubenPathLine(Entity* et)
{
	if (!et) return false;
	if (!self_->GetMoveLine().empty()) {
		if (Grid(et->GetPosition()) == Grid(last_path_point_)) {
			return true;
		} else {
			self_->ClearMoveLine();
		}
	}
	last_path_point_ = et->GetPosition();
	return false;
}

bool AIState::RequestFubenPathLine(Point &tar)
{
	//玩家寻路
	if (self_->GetMoveLineStatus() != MOVELINE_NORMAL)//不能重复发送
		return false;

	Actor* actor = self_->GetActor();
	if (!actor) {
		return false;
	}

	Protocol::FubenMoveLineProto msg;
	msg.handle = self_->GetHandle();
	msg.self_x = self_->GetPosition().x;
	msg.self_y = self_->GetPosition().y;
	msg.target_x = tar.x;
	msg.target_y = tar.y;
	actor->SendData(msg);
	OutputMsg(rmTip, "actor:%d, handle:%ld,etype:%d, RequestFubenPathLine, (%d,%d)=>(%d,%d)", actor->GetActorId(), msg.handle, self_->GetType(), msg.self_x, msg.self_y, tar.x, tar.y);
	self_->SetMoveLineStatus(MOVELINE_SEND_REQUEST);//标记为已发送请求, 防止重复发送
	return true;
}

