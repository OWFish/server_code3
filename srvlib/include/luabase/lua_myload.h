#ifndef _LUA_MYLOAD_H_
#define _LUA_MYLOAD_H_

// ��ʼ���汾
void lua_initVersion(lua_State* L);

// ���Ӱ汾
void lua_incVersion(lua_State* L);

// ע���µ�require
void lua_registerMyRequire(lua_State* L);

#endif
