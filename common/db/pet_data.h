#ifndef _PET_H_
#define _PET_H_

#include "common/system_param_def.h"


#pragma  pack(push,1)

struct PropData
{
	int data_[PI_MAX];
};

#pragma  pack (pop)

//lua里面也有限制
#define MAX_BLOOD 20
#endif

