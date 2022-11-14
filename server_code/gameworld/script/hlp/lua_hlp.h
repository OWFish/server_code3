#pragma once

/************************************************************************
*                                                                      *
*                           LUA�ű�������������                         *
*                                                                      *
************************************************************************/
namespace LuaHelp
{
	/*
	* Comments: ������������ָ�뱣�浽һ�����в�����ѹ��ջ�������dataCountΪ0�����ջ��ѹ��nilֵ
	* Param lua_State * L: lua���������
	* Param const void* lpData: ���ݻ�����ָ��
	* Param size_t sizeElement: ���ݶ����С
	* Param size_t dataCount: �����������ݵ�����
	* @Return void:
	*/
	void PushDataPointerToTable(lua_State *L, const void* lpData, size_t sizeElement, size_t elementCount);

	/*
	* Comments:������������ָ�뱣�浽һ�����в�����ѹ��ջ�������dataCountΪ0�����ջ��ѹ��nilֵ
	* Param lua_State * L:lua���������
	* Param void * * lpData:���ݻ�����ָ��
	* Param size_t elementCount:�����������ݵ�����
	* @Return void:
	*/
	void PushDataPointerToTable(lua_State *L, void** lpData, size_t elementCount);
	/*
	* Comments: ���ַ����б��浽һ�����в�����ѹ��ջ�������dataCountΪ0�����ջ��ѹ��nilֵ
	* Param lua_State * L: lua���������
	* Param const void* lpData: ���ݻ�����ָ��
	* Param size_t sizeElement: ���ݶ����С
	* Param size_t dataCount: �����������ݵ�����
	* @Return void:
	*/
	void PushStringsToTable(lua_State *L, const char* *ppStrList, size_t strCount);
	/*
	* Comments: ���������鱣�浽һ�����в�����ѹ��ջ�������elementCountΪ0�����ջ��ѹ��nilֵ
	* Param lua_State * L: lua���������
	* Param const void* pIntList: ����ָ��
	* Param size_t elementCount: �����Ա����
	* @Return void:
	*/
	void PushIntsToTable(lua_State* L, int* pIntList, size_t elementCount);
	/*
	* Comments: ��һ��LUA��������л�ΪASCII�ű��ַ���
	* Param lua_State * L: lua���������
	* Param int stackId: ����������е�ջ����
	* Param stream::BaseStream & stm: ���������
	* @Return size_t: ���ر����л�������˶��ٸ��ֽڵ�����
	*/
	size_t FormatTableA(lua_State *L, int stackId, stream::BaseStream &stm);

	/*
	* Comments: ��һ��Lua��ջ��д��һ����ֵ�б�����һ��Vector<float>����int a[10]
	* Param lua_State * L: ��ջ
	* Param T * pData: ���ݵ�ָ��
	* Param int elementCount: ��ֵ�ĸ���
	* @Return void:
	*/
	template<class T>
	void PushNumberVector(lua_State *L,T * pData,size_t elementCount)
	{
		if (pData == NULL)
		{
			lua_pushnil(L);
			return;
		}
		if (elementCount > 0)

		{
			lua_createtable(L, (int)elementCount, 0);
			for (size_t i=1; i<=elementCount; ++i)
			{
				lua_pushnumber( L, (LUA_NUMBER)(* pData) );
				lua_rawseti( L, -2, (int)i );
				pData ++;
			}
		}
		else lua_pushnil(L);
	}

};
