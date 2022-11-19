#pragma once

/************************************************************************
*                                                                      *
*                           LUA脚本辅助处理函数库                         *
*                                                                      *
************************************************************************/
namespace LuaHelp
{
	/*
	* Comments: 将二进制数据指针保存到一个表中并将表压入栈顶，如果dataCount为0则会向栈顶压入nil值
	* Param lua_State * L: lua虚拟机对象
	* Param const void* lpData: 数据缓冲区指针
	* Param size_t sizeElement: 数据对象大小
	* Param size_t dataCount: 缓冲区中数据的数量
	* @Return void:
	*/
	void PushDataPointerToTable(lua_State *L, const void* lpData, size_t sizeElement, size_t elementCount);

	/*
	* Comments:将二进制数据指针保存到一个表中并将表压入栈顶，如果dataCount为0则会向栈顶压入nil值
	* Param lua_State * L:lua虚拟机对象
	* Param void * * lpData:数据缓冲区指针
	* Param size_t elementCount:缓冲区中数据的数量
	* @Return void:
	*/
	void PushDataPointerToTable(lua_State *L, void** lpData, size_t elementCount);
	/*
	* Comments: 将字符串列表保存到一个表中并将表压入栈顶，如果dataCount为0则会向栈顶压入nil值
	* Param lua_State * L: lua虚拟机对象
	* Param const void* lpData: 数据缓冲区指针
	* Param size_t sizeElement: 数据对象大小
	* Param size_t dataCount: 缓冲区中数据的数量
	* @Return void:
	*/
	void PushStringsToTable(lua_State *L, const char* *ppStrList, size_t strCount);
	/*
	* Comments: 将整形数组保存到一个表中并将表压入栈顶，如果elementCount为0则会向栈顶压入nil值
	* Param lua_State * L: lua虚拟机对象
	* Param const void* pIntList: 数组指针
	* Param size_t elementCount: 数组成员数量
	* @Return void:
	*/
	void PushIntsToTable(lua_State* L, int* pIntList, size_t elementCount);
	/*
	* Comments: 将一个LUA表对象序列化为ASCII脚本字符串
	* Param lua_State * L: lua虚拟机对象
	* Param int stackId: 表在虚拟机中的栈索引
	* Param stream::BaseStream & stm: 输出流对象
	* @Return size_t: 返回表序列化后产生了多少个字节的数据
	*/
	size_t FormatTableA(lua_State *L, int stackId, stream::BaseStream &stm);

	/*
	* Comments: 往一个Lua堆栈里写入一个数值列表，比如一个Vector<float>或者int a[10]
	* Param lua_State * L: 堆栈
	* Param T * pData: 数据的指针
	* Param int elementCount: 数值的个数
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
