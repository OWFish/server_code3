#ifndef _FILE_LOGGER_H_
#define _FILE_LOGGER_H_

/*********************************************************
*                      日志文件记录器
* 将此类型在main函数中定义一份变量即可，请勿在一个程序中多次使用此类型
*
*********************************************************/

class FileLogger
{
public:
	FileLogger(const char* sLogFileNamePattern);
	~FileLogger();
};


#endif

