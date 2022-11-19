#include "StdAfx.h"
#include "actor/actor.h"
#include "imbasystem.h"

ImbaSystem::ImbaSystem(Actor* actor)
	: actor_(actor)
{

}

ImbaSystem::~ImbaSystem()
{

}



void ImbaSystem::Save()
{

}

void ImbaSystem::Destroy()
{

}

bool ImbaSystem::Init()
{
	return true;
}

void ImbaSystem::ClearAttr()
{
	attribute_.Reset();
	ex_attribute_.Reset();
}

void ImbaSystem::AddAttr(int type, int value)
{
	attribute_.Add((Attribute::AttributeType)type, value);
}

void ImbaSystem::AddExAttr(int type, int value)
{
	ex_attribute_.Add(type,value);
}




