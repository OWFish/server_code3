#pragma once

class Actor;

#include <map>
#include <vector>



class Tianti
{
public:
private:

public:
	Tianti(void);
	bool Init(void);
	ActorId FindActor(Actor* actor);
	void CreateCloneRole(ActorId actor_id, unsigned int scene,int x,int y, int sid = 0,int camp = 0);
	void* CreateRobot(RobotData* data, unsigned int scene, int x, int y);
	void refreshWeek(void);
private:
	
};
