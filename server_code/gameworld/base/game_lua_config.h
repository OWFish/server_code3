#ifndef _GAME_LUA_CONFIG_H_
#define _GAME_LUA_CONFIG_H_

#include "utils/luareader.h"


/************************************************************************
*              可提供默认的lua虚拟机内存管理函数的脚本配置类
************************************************************************/
class GameLuaConfig :
	public LuaReader
{
public:
	typedef LuaReader Inherited;
	void RegisteToPreprocessor(LuaPreProcessor& pp);

	// 静态方法，统一从文件读取lua配置，返回文件内容，非线程安全
	static const char* LoadFromFile(const char* fn, GameLuaConfig* config);
public:
	// 提供一些读取配置常用的函数
	// 读取一连串的int数组,表必须提前已经打开，返回负数表示失败
	int ReadIntArray(int* arr, int count, const char* field = NULL);
	int ReadIntArray(const char* table, int* arr, int count);
	// 读取一连串的int数组,table表示表名，返回负数表示失败
	int ReadIntArray(const char* table, int** arr, MemoryContainer<char>& alloc);
	//int ReadGameAttrArray(const char* table, GAMEATTR** arr, MemoryContainer<char>& alloc);

	// 读取一连串的int数组,同时传入一连串的字段名，函数将会读取各个field的值放入arr中
	int ReadIntArray(int* arr, int count, const char** field, int fcount);
	int ReadIntArray(const char* table, int** arr, const char** field, int fcount, MemoryContainer<char>& alloc);

	//bool ReadAttr(GAMEATTR& attr);

	int ReadDoubleArray(double* arr, int count, const char* field = NULL);
	int ReadFloatArray(float* arr, int count, const char* field = NULL);
protected:
	//注册本地库
	bool registLocalLibs();
};

#endif
