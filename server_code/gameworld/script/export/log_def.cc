#include "StdAfx.h"
#include "../interface/log_def.h"

namespace GameLog
{
	const char* logList[clMax];

	void Init()
	{
		memset(logList, 0, sizeof(logList));

#include "log_def.data"

	}

	const char* LogStr(int logid)
	{
		if (logid < 0 || logid >= clMax)
			return "";
		return logList[logid];
	}
};

