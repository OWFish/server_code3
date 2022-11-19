#ifndef _LUA_MYLOAD_H_
#define _LUA_MYLOAD_H_

// 初始化版本
void lua_initVersion(lua_State* L);

// 增加版本
void lua_incVersion(lua_State* L);

// 注册新的require
void lua_registerMyRequire(lua_State* L);

#endif
