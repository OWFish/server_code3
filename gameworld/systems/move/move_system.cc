#include "StdAfx.h"
#include "move_system.h"
#include "entity.h"
#include "protos/base_proto.h"


MoveSystem::MoveSystem(Creature* creature)
: self_(creature)
, move_timer_(100)
, last_t_(0)
, last_pos_(0,0)
, last_tar_pos_(0,0)
{}

MoveSystem::~MoveSystem()
{}


void MoveSystem::OnTimeCheck(int64_t tick_t)
{
	if (!self_) return;

	if (move_timer_.CheckAndSet(tick_t, false))
	{
		if(last_t_ != 0)
			MovingTime(false, true);
		return;
	}
}

void MoveSystem::OnDeath()
{
	// �ڵ�ǰ������λ��ֹͣ�ƶ�
	// ������ƶ��У�Ҫ����ֹͣ�ƶ�ʱ����λ��
	if (last_t_)
		MovingTime(true, true);
}

/*void MoveSystem::OnSpeedChange()
{
	// �������Ӧ��ֻ�й���ŵ��õ�
	if (!self_) return;

	if (IsMoving())
	{
		// ���㵱ǰӦ�����ڵ�λ��
		int destX = 0, destY = 0;
		self_->GetMoveDest(destX, destY);
		int gx = 0, gy = 0;
		self_->GetPixPos(gx, gy);
		StartMove(destX, destY, gx, gy);	// ���¹㲥һ���ƶ�
	}
}*/

//ʵ���ƶ�ʵ�ʴ�����
//bool MoveSystem::StartMove(int x, int y, int curr_x, int curr_y, Actor* ex, bool jump, int jumpSpeed)
bool MoveSystem::StartMove(const Point& tarPos)
{
	if (!self_) return false;

	Scene* scene = self_->GetScene();
	if (!scene)	return false;

	//�������ƶ�
	if (self_->GetAttr(Attribute::atMoveSpeed) <= 0)
		return false;

	// todo �ƶ�����״̬�ж�

	//��ǰ������
	const Point& current_pos = self_->GetPosition();

	if (current_pos == tarPos || !self_->CanMove()) {
		ClearMoveData();
	} else {
		self_->SetMoveDest(tarPos);
		Point dir(tarPos.x - current_pos.x, tarPos.y - current_pos.y);
		self_->SetDirection(dir);
		//OutputMsg(rmTip, "start move, id:%d,pos:(%d,%d)->(%d,%d), n:%d", self_->GetId(),
		//	current_pos.x, current_pos.y,tarPos.x, tarPos.y, GetGameEngine()->getTickCount());
		if (last_t_ == 0)
		{
			last_t_ = GetGameEngine()->getTickCount();
			last_pos_ = current_pos;
		}
		if(!(last_tar_pos_ == Grid(tarPos))) {
			last_tar_pos_ = Grid(tarPos);
			//�񸽽��㲥�ƶ���Ϣ//�����ͬһ��������Ź㲥
			static Protocol::EntityMoveProto msg;
			msg.handle = self_->GetHandle();
			msg.tar_x = tarPos.x;
			msg.tar_y = tarPos.y;
			msg.cur_x = current_pos.x;
			msg.cur_y = current_pos.y;

			// �㲥�������˿�ʼ�ƶ���(�ɷ�ʽ)
			//ObserverSystem& system = self_->GetObserverSystem();
			//system.BroadCast((char*)&data, sizeof(data), false, ex);

			// todo��ʱ�ɳ�������㲥���Ժ��ڳ������㲥�Ż�������
			Scene* scene = self_->GetScene();
			scene->SendData(msg);
			//test_time_ = GetGameEngine()->getTickCount();
		}
	}

	return true;
}

void MoveSystem::MovingTime(bool mustStop, bool sendPos)
{
	if (!self_) return;

	static GameEngine* ge = GetGameEngine();
	int64_t now_t = ge->getTickCount();
	int64_t inter_t = now_t - last_t_;

	if (inter_t <= 5) return;

	// �����µ�λ�ã����ŵ��µ�������
	const Point& dest_pos = self_->GetMoveDest();
	double inter_x = dest_pos.x - last_pos_.x;
	double inter_y = dest_pos.y - last_pos_.y;

	double dis = sqrt((double)(inter_x * inter_x + inter_y * inter_y));
	double speed = self_->GetAttr(Attribute::atMoveSpeed);
	double ds = (double)speed / 1000 * GRIDSIZE / 1000 * inter_t;

	// ����Ѿ�������Ŀ���
	bool stop = false;
	DPoint new_pt(0,0);

	if (ds >= dis)
	{
		// ��������ֹͣ��
		new_pt = dest_pos;
		stop = true;
	}
	else
	{
		ds /= dis;
		new_pt.x = (ds * inter_x) + last_pos_.x;
		new_pt.y = (ds * inter_y) + last_pos_.y;
		last_t_ = now_t;
		last_pos_ = new_pt;
	}

	// �ŵ��µ�������
	Grid old_grid = self_->GetPosition();

	self_->SetPosition(new_pt.ToPoint());
	if (!(old_grid == Grid((int)new_pt.x, (int)new_pt.y)))
	{
		Scene* scene = self_->GetScene();
		if (scene)
		{
			FuBen *fuben = scene->GetFuBen();
			if (fuben && fuben->GetConfig() && fuben->GetConfig()->findPath != 0)
			{
				bool ret = scene->CanMove(new_pt.ToGrid());
				if (ret)
				ret = scene->MoveTo(self_, new_pt.ToPoint());
				if (!ret) 
				{
					StopMove();
					return;
				}
			}
			else 
			{
				scene->MoveTo(self_, new_pt.ToPoint());
			}
		}
	}

	// ����ֹͣ�ƶ�
	if (stop || mustStop || !self_->CanMove())
	{
		self_->SetPosition(new_pt.ToPoint());
		StopMove();	// ������ƶ���ʱ�䣬�´ξͲ���ִ��������
		//OutputMsg(rmTip, "-=-=-=-=-=-=-=  start--stop pos(%d,%d) time:%d",
		//	(int)new_pt.x, (int)new_pt.y, now_t - test_time_);
	}
}

bool MoveSystem::GetMovablePoint(const Point& pos, int range, Point& ret)
{
	Scene *scene = self_->GetScene();
	if (scene->CanMove(pos))
	{
		ret = pos;
		return true;
	}

	for (int i = 1; i <= range; i++)
	{
		for (ret.x = pos.x - i; ret.x <= pos.x + i; ++ret.x)
		{
			if (ret.x == pos.x - i || ret.x == pos.x + i)
			{
				for (ret.y = pos.y - i; ret.y <= pos.y + i; ++ret.y)
				{
					if (scene->CanMove(ret))
					{
						return true;
					}
				}
			}
			else
			{
				ret.y = pos.y - i;
				if (scene->CanMove(ret))
					return true;

				ret.y = pos.y + i;
				if (scene->CanMove(ret))
					return true;
			}
		}
	}

	return false;
}


void MoveSystem::NotifySpecialMove(const Point& pos, int move_type)
{
	static Protocol::EntitySpectialMoveProto msg;
	msg.handle = self_->GetHandle();
	msg.x = pos.x;
	msg.y = pos.y;
	msg.type = (short)move_type;

	// todo��ʱ�ɳ�������㲥���Ժ��ڳ������㲥�Ż�������
	Scene* scene = self_->GetScene();
	if (scene)
		scene->SendData(msg);

	//ObserverSystem& obser = self_->GetObserverSystem();
	//obser.BroadCast((char*)&data, sizeof(data), toSelf);
}

//˲���ƶ���һ����ȥ
bool MoveSystem::InstantMove(const Point& pos)
{
	//const Point& cur_pos = self_->GetPosition();

	//�ܷ�����ƶ�״̬
	//if (!self_->CanEnterState(esStateMove)) return false;

	Scene* scene = self_->GetScene();
	if (!scene) return false;

	bool ret = true;

	if (ret && scene->MoveTo(self_, pos))
	{
		NotifySpecialMove(pos, SMT_InstantMove);
		self_->ClearMoveLine();
		ClearMoveData();	// ����bug������timecheck������Ȼ��ʵ���ƶ���Ŀ�ĵ�
	}

	return ret;
}

void MoveSystem::NotifyStopMove(const Point& pos)
{
	if (!self_) return;
	static Protocol::EntityStopProto msg;
	msg.handle = self_->GetHandle();
	msg.x = pos.x;
	msg.y = pos.y;

#ifdef _MSC_VER
	if (self_->GetType() == EntityType_Role)
	{
		Actor *actor = ((Role*)self_)->GetActor();
		//OutputMsg(rmTip, "Role,onStopMove,aid:%d,roldId:%d,dst:(%d,%d), now:(%d,%d)", actor->GetActorId(), self_->GetId(), self_->GetMoveDest().x, self_->GetMoveDest().y, msg.x, msg.y);
	}
	else
	{
		//OutputMsg(rmTip, "entity,onStopMove,type:%d,id:%d,dst:(%d,%d), now:(%d,%d)", self_->GetType(), self_->GetId(), self_->GetMoveDest().x, self_->GetMoveDest().y, msg.x, msg.y);
	}
#endif // _MSC_VER



	// todo �����㲥�ƶ��ӿ�
	if (self_->GetScene())
		self_->GetScene()->SendData(msg);
}

void MoveSystem::StopMove()
{
	if (!self_) return;

	const std::list<Point> & lines = self_->GetMoveLine();
	if (!lines.empty())
	{
		Point dest = lines.back();
		self_->MoveLinePopData();
		StartMove(dest);
		return;
	}

	const Point& pos = self_->GetPosition();
	NotifyStopMove(pos);

	ClearMoveData();
}


void MoveSystem::ClearMoveData()
{
	if (!self_) return;

	self_->SetMoveDest(Point(-1,-1));	// �����ƶ���Ŀ��
	last_pos_.x = last_pos_.y = 0;
	last_t_ = 0;
}

void MoveSystem::OnExitScene() {
	ClearMoveData();
	last_tar_pos_.x = 0;
	last_tar_pos_.y = 0;
}

void MoveSystem::StartFubenPathToTarget()
{
	if (self_ == NULL)
		return;

	const std::list<Point> & lines = self_->GetMoveLine();
	if (lines.empty())
		return;

	Point dest = lines.back();
	self_->MoveLinePopData();
	StartMove(dest);
}

