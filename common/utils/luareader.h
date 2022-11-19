#pragma once

#include "luabase/base_lua_config.h"
#include "string_ex.h"

/*
	ly:ʹ������Զ����ṩ��ȡlua�Ĺ����ͽӿڣ���ȡlua���õĵط�ֻ��Ҫ��Դ�ļ�������
	���ļ�������������Ҫ�������о�Ҫ���벢�̳�BaseLuaConfig��
*/
class LuaReader :public BaseLuaConfig
{
	typedef BaseLuaConfig Base;
public:
	void showError(const char* sError) { OutputMsg(rmError, sError); }
	void showTableNotExists(const char* sTableName) { return Base::showTableNotExists(sTableName); }
	void showFieldDoesNotContainValue(const char* sFieldName, const char* sValueType) { return Base::showFieldDoesNotContainValue(sFieldName, sValueType); }

	bool openGlobalTable(const char* sTableName) { return Base::openGlobalTable(sTableName); }
	bool openFieldTable(const char* sTableName) { return Base::openFieldTable(sTableName); }
	bool enumTableFirst(){ return Base::enumTableFirst(); }
	bool enumTableNext() { return Base::enumTableNext(); }
	void endTableEnum() { return Base::endTableEnum(); }
	bool getFieldIndexTable(const int IndexStartFromOne) { return Base::getFieldIndexTable(IndexStartFromOne); }
	bool fieldTableExists(const char* sTableName) { return Base::feildTableExists(sTableName); }
	void closeTable() { return Base::closeTable(); }
	const char* getTablePath() { String r; return Base::getTablePath(r); }
	const char* getKeyName() { String r; return Base::getKeyName(r); }
	inline int getValueType(){ return Base::getValueType(); }
	bool getFieldBoolean(const char* sFieldName, const bool* pDefValue = nullptr, int* pIsValid = nullptr) { return Base::getFieldBoolean(sFieldName, pDefValue, pIsValid); }
	double getFieldNumber(const char* sFieldName, const double* pDefValue = nullptr, int* pIsValid = nullptr) { return Base::getFieldNumber(sFieldName, pDefValue, pIsValid); }
	int64_t getFieldInt64(const char* sFieldName, const int64_t* pDefValue = nullptr, int* pIsValid = nullptr) { return Base::getFieldInt64(sFieldName, pDefValue, pIsValid); }
	int getFieldInt(const char* sFieldName, const int* pDefValue = nullptr, int* pIsValid = nullptr) { return Base::getFieldInt(sFieldName, pDefValue, pIsValid); }
	const char* getFieldString(const char* sFieldName, const char* pDefValue = nullptr, int* pIsValid = nullptr) { return Base::getFieldString(sFieldName, pDefValue, pIsValid); }
	int getFieldStringBuffer(const char* sFieldName, char* sBuffer, size_t dwBufLen) { return Base::getFieldStringBuffer(sFieldName, sBuffer, dwBufLen); }
	int getTableLen() { return (int)lua_objlen(lua_, -1); }
};
