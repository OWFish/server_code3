#ifndef _LUA_LANG_SECTION_H_
#define _LUA_LANG_SECTION_H_

/************************************************************************
*
*                  LnagTextSection向脚本导出的注册以及实现
*
************************************************************************/

namespace LuaLangSection
{
//将LangTextSection类导出到脚本
void regist(lua_State* L);
//将LangTextSection类作为指定的类名导出到脚本
void registTo(lua_State* L, const char* className);
//向脚本返回LangTextSection实例
int returnValue(lua_State* L, LangSection& section);
//向脚本设置LangTextSection实例为全局变量
void setGlobalValue(lua_State* L, LangSection& section, const char* globalname);
}

#endif


