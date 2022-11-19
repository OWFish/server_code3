#pragma once


class Actor;
class SkirmishHelper
{
public:
	static void CreateSkirmishData(Actor* actor, int index, int id, int level, const char* name, int attrper);
	static void createFieldPlayerData(Actor* actor, int index, int actor_id, int pos_x, int pos_y, int actionType, int isForay, int killNum, int ox, int oy);
	static std::vector<ActorId> FindSkirmish(Actor* actor);
	static std::vector<ActorId> FindFieldPlayer(Actor *actor, int startlv, int endlv, int needNum, int flSize);
};