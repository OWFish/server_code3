/*
	����һЩ����ĺ�����Ҫֱ�ӵ���Lua_state���в���������ע��һЩ������Ϊ���⴦���
	
*/
#pragma once

extern const luaL_reg LuaHelpExpot[];

/*
*����luaL_reg�ຯ���ķ��ز�����ע�⣬�÷��ز�����ʾ���ű��ķ��ص�ֵ�ĸ��������û�з��ؾͷ���0
*�����2�����ؾͷ���2
*/

namespace LuaHelp
{
	/*
	* Comments:����һ��Lua�ı�һ���ļ���ȥ
	������һ����
	aa=
	{
	   xxx = "112",
	   zz = 
	  {
	   121, 2332,
	   },
	  yyy = 111,
	}
	Ҫ����Ϊ../Data/aa.txtʹ��
	���̵�ʱ����  LuaHelp.saveTable(aa,"../Data/aa.txt",�������);
	���������ֲ���ֵ ����ô����������,���򽫱���Ϊ

	������������������aa.txt������Ϊ:
	{
		xxx = "112",
		zz = 
		{
		121, 2332,
		},
		yyy = 111,
	}
	����Ϊ��������ΪSTable��Ϊ
	STable =
	{
	xxx = "112",
	zz = 
	{
	121, 2332,
	},
	yyy = 111,
	}
	* Param lua_State * L: lua��ָ��
	* @Return int:û�з���,����ķ���ֵ�Ǳ�ʾ��lua�ķ��صĲ����ĸ���
	*/
	int saveTable(lua_State *L);

	/*
	* Comments:����ǲ������������ڰ�һ�����ݱ�ѹ��
	  �ű���ʹ��local b = LuaHelp.getTestTable() ���õ�һ��table
	* Param lua_State * L:
	* @Return int:����ֵ����һ����Ļ��ͷ���1
	*/
	int getTestTable(lua_State *L);

	/*
	* Comments:��ȡ��ɫ���ڶ���Ķ�Ա���б�
	* Param lua_State * L:�ű������Ĳ����ǽ�ɫ��ָ��
	   ʹ�÷���Ϊ: LuaHelp.getTeamMemberList(��ҵ�ָ��)
	* @Return int:����1����һ����
	*/
	int getTeamMemberList(lua_State *L);

	/*
	* Comments:ͨ�������ָ�룬��ȡ�����Ա���б�
	* Param lua_State * L:
	* @Return int:
	*/
	int getTeamMemberListByPtr(lua_State *L);

	/*
	* Comments:���ݸ�����id��ȡȫ�����������������copy,���ظ�����handle�б�
	* Param int nFbid:
	* @Return void:
	*/
	int getFbFromId(lua_State *L);

	/*
	* Comments:��ȡ��������ͼ�������
	* Param lua_State * L:������ҵ�ָ��
	* @Return int:����һ��������3�����֣��ֱ��ǳ���id������X������Y
	*/
	int getReloadMapPos(lua_State *L);

	/*
	* Comments:��ȡ��Χ��ʵ���ָ���б�
	* Param lua_State * L:[ʵ���ָ��][�뾶��Χ]
	* @Return int:����һ�����������е�ʵ��ָ��
	*/
	int getNearEntityList(lua_State *L);

	/*
	* Comments:��ȡ��Χ��ʵ���ָ���б�
	* Param lua_State * L:[����ָ��][x][y][�뾶��Χ]
	* @Return int:����һ�����������е�ʵ��ָ��
	*/
	int getNearEntityListFromXY(lua_State *L);

	

	/*
	* Comments:��ȡ��Χ��ʵ���ָ���б�
	* Param lua_State * L:[����ָ��][x][y][��Ȱ뾶][�߶Ȱ뾶]
	* @Return int:����һ�����������е�ʵ��ָ�롣��ȡ��������Χ�� (2*��Ȱ뾶)*(2*�߶Ȱ뾶)
	*/
	int getNearEntityListFromRange(lua_State *L);

	/*
	*	f(pScene, leftUpX, leftUpY, rightDownX, rightDownY)
	*	��ȡ������ʵ��ָ���б�
	*/
	int getEntityListFromRange(lua_State *L);

	/*
	* Comments:��ȡ���е�������ҵ�ָ��
	* Param lua_State * L:
	* @Return int:����һ�����������е�ʵ��ָ��
	*/
	int getAllActorList(lua_State *L);

	/*
	* Comments:��ȡ������������ҵ�ָ��
	* Param lua_State * L:[int������id]
	* @Return int:����һ�����������е�ʵ��ָ��
	*/
	int getSceneActorListById(lua_State *L);

	/*
	* Comments:��ȡ�����Ĺ����ָ��
	* Param lua_State * L:[int��ʵ��ָ��]
	* @Return int:����һ�����������е�ʵ��ָ��
	*/
	int getSceneMonsterList(lua_State *L);


		/*
	* Comments:��ȡ������NPCָ��
	* Param lua_State * L:[int������id]
	* @Return int:����һ�����������е�ʵ��ָ��
	*/
	int getSceneNpcListById(lua_State* L);

	/*
	* Comments:ͨ��������ȡ�����Ĺ����ָ���б�
	* Param lua_State * L:����ָ��
	* @Returns int:����һ�����������й���ʵ��ָ��
	*/
	int getSceneMonsterListByScene(lua_State *L);

	/*
	* Comments:��ȡ������������ҵ�ָ��
	* Param lua_State * L:[void* et: ʵ��ָ��]
	* @Return int:����һ�����������е�ʵ��ָ��
	*/
	int getSceneActorList(lua_State *L);


	/*
	* Comments:��ȡ���а�ǰN��������
	* Param lua_State * L:[���а��ָ��][��������ʾҪ��ȡǰN��]
	* @Return int:����һ�����������а����ָ��
	*/
	int getRankingItemList(lua_State* L);

	/*
	* Comments:��ȡ������������ҵ��б�
	* Param lua_State * L:[������ָ��]
	* @Return int:����һ��������������ҵ�ָ��
	*/
	int getFbActorList(lua_State* L);

	/*
	* Comments:��ȡʵ��ɼ���Χ����ҵ��б�
	* Param lua_State * L:[ʵ��ָ��]
	* @Return int:
	*/
	int getVisiActorList(lua_State* L);


	/*
	* Comments:��ȡ��ǰ����������б�
	* Param lua_State * L: [ʵ��ָ��]
	* @Returns int:
	*/
	int getSceneActorListByPtr( lua_State *L);
}
