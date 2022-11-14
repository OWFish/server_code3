#ifndef _LUA_LANG_SECTION_H_
#define _LUA_LANG_SECTION_H_

/************************************************************************
*
*                  LnagTextSection��ű�������ע���Լ�ʵ��
*
************************************************************************/

namespace LuaLangSection
{
//��LangTextSection�ർ�����ű�
void regist(lua_State* L);
//��LangTextSection����Ϊָ���������������ű�
void registTo(lua_State* L, const char* className);
//��ű�����LangTextSectionʵ��
int returnValue(lua_State* L, LangSection& section);
//��ű�����LangTextSectionʵ��Ϊȫ�ֱ���
void setGlobalValue(lua_State* L, LangSection& section, const char* globalname);
}

#endif


