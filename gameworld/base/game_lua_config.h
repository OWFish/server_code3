#ifndef _GAME_LUA_CONFIG_H_
#define _GAME_LUA_CONFIG_H_

#include "utils/luareader.h"


/************************************************************************
*              ���ṩĬ�ϵ�lua������ڴ�������Ľű�������
************************************************************************/
class GameLuaConfig :
	public LuaReader
{
public:
	typedef LuaReader Inherited;
	void RegisteToPreprocessor(LuaPreProcessor& pp);

	// ��̬������ͳһ���ļ���ȡlua���ã������ļ����ݣ����̰߳�ȫ
	static const char* LoadFromFile(const char* fn, GameLuaConfig* config);
public:
	// �ṩһЩ��ȡ���ó��õĺ���
	// ��ȡһ������int����,�������ǰ�Ѿ��򿪣����ظ�����ʾʧ��
	int ReadIntArray(int* arr, int count, const char* field = NULL);
	int ReadIntArray(const char* table, int* arr, int count);
	// ��ȡһ������int����,table��ʾ���������ظ�����ʾʧ��
	int ReadIntArray(const char* table, int** arr, MemoryContainer<char>& alloc);
	//int ReadGameAttrArray(const char* table, GAMEATTR** arr, MemoryContainer<char>& alloc);

	// ��ȡһ������int����,ͬʱ����һ�������ֶ��������������ȡ����field��ֵ����arr��
	int ReadIntArray(int* arr, int count, const char** field, int fcount);
	int ReadIntArray(const char* table, int** arr, const char** field, int fcount, MemoryContainer<char>& alloc);

	//bool ReadAttr(GAMEATTR& attr);

	int ReadDoubleArray(double* arr, int count, const char* field = NULL);
	int ReadFloatArray(float* arr, int count, const char* field = NULL);
protected:
	//ע�᱾�ؿ�
	bool registLocalLibs();
};

#endif
