#include "StdAfx.h"
#include "actor/actor.h"
#include "godweaponsystem.h"

GodWeaponSystem::GodWeaponSystem(Actor* actor)
	: actor_(actor)
{
	attribute_.Reset();
	ex_attribute_.Reset();
	isPeak_ = false;
	level_ = 0;
	weapon_list_.clear();
	memset(ex_power_, 0, sizeof(ex_power_));
}

GodWeaponSystem::~GodWeaponSystem()
{

}



void GodWeaponSystem::Save()
{

}

void GodWeaponSystem::Destroy()
{

}

bool GodWeaponSystem::Init()
{
	return true;
}

void GodWeaponSystem::AddActId(int idx, int id)
{
	auto it = weapon_list_.find(idx);
	if(weapon_list_.end() == it){
		std::set<int> list;
		list.insert(id);
		weapon_list_[idx] = list;
	}
	else {
		it->second.insert(id);
	}
}

const std::set<int>* GodWeaponSystem::getIdList(int idx)
{
	auto it = weapon_list_.find(idx);
	if (weapon_list_.end() != it) {
		return &it->second;
	}

	return nullptr;
}

void GodWeaponSystem::setPower(int job, int power)
{
	if (job <= JobType_None || job >= JobType_Max) return;
	ex_power_[job] = power;
}

int GodWeaponSystem::getPower(int job)
{
	if (job <= JobType_None || job >= JobType_Max) return 0;
	return ex_power_[job];
}

void GodWeaponSystem::ClearAttr()
{
	attribute_.Reset();
	ex_attribute_.Reset();
}

void GodWeaponSystem::AddAttr(int type, int value)
{
	attribute_.Add((Attribute::AttributeType)type, value);
}


void GodWeaponSystem::AddExAttr(int type, int value)
{
	ex_attribute_.Add(type,value);
}




