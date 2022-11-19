#ifndef _LUA_CLVARIANT_H_
#define _LUA_CLVARIANT_H_

/************************************************************************
*                  CCLVariant向脚本导出的注册以及实现
************************************************************************/

namespace LuaCLVariant
{
	//将CLVariant类导出到脚本
	void regist(lua_State *L);
	//将CLVariant类作为指定的类名导出到脚本
	void registTo(lua_State *L, const char *className);
	//向脚本返回CLVariant实例
	int returnValue(lua_State *L, CLVariant &var);
}

#endif

