#include "StdAfx.h"
#include "neigong_config.h"

int NeigongConfig::_intervalTime;
int NeigongConfig::_precent;

bool NeigongConfig::LoadNeigongConfig(GameConfigData * data)
{
	if (!data->openGlobalTable("NeiGongBaseConfig"))
	{
		OutputMsg(rmError, ("can't open NeiGongBaseConfig table"));
		return false;
	}

	_intervalTime = data->getFieldInt("intervalTime");
	_precent = data->getFieldInt("precent");

	data->closeTable();

	return true;
}

int NeigongConfig::GetIntervalTime()
{
	return _intervalTime;
}
