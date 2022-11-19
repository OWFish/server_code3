#include "StdAfx.h"
#include "item.h"
#include "item_config.h"


Item::Item()
{
	memset(&data_, 0, sizeof(ItemData));
}

Item::~Item()
{

}


bool Item::Init()
{
	if (config_ == NULL)
		return false;

	return true;
}

