#ifndef _LUA_CLVARIANT_H_
#define _LUA_CLVARIANT_H_

/************************************************************************
*                  CCLVariant��ű�������ע���Լ�ʵ��
************************************************************************/

namespace LuaCLVariant
{
	//��CLVariant�ർ�����ű�
	void regist(lua_State *L);
	//��CLVariant����Ϊָ���������������ű�
	void registTo(lua_State *L, const char *className);
	//��ű�����CLVariantʵ��
	int returnValue(lua_State *L, CLVariant &var);
}

#endif

