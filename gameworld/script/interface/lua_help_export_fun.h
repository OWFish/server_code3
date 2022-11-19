/*
	由于一些特殊的函数需要直接调用Lua_state进行操作，这里注册一些函数作为特殊处理的
	
*/
#pragma once

extern const luaL_reg LuaHelpExpot[];

/*
*关于luaL_reg类函数的返回参数请注意，该返回参数表示给脚本的返回的值的个数，如果没有返回就返回0
*如果有2个返回就返回2
*/

namespace LuaHelp
{
	/*
	* Comments:保存一个Lua的表到一个文件里去
	比如有一个表
	aa=
	{
	   xxx = "112",
	   zz = 
	  {
	   121, 2332,
	   },
	  yyy = 111,
	}
	要存盘为../Data/aa.txt使用
	存盘的时候用  LuaHelp.saveTable(aa,"../Data/aa.txt",表格名字);
	如果表格名字不赋值 ，那么将不存名字,否则将保持为

	如果不传表名保存完的aa.txt的内容为:
	{
		xxx = "112",
		zz = 
		{
		121, 2332,
		},
		yyy = 111,
	}
	否则为加入名字为STable将为
	STable =
	{
	xxx = "112",
	zz = 
	{
	121, 2332,
	},
	yyy = 111,
	}
	* Param lua_State * L: lua的指针
	* @Return int:没有返回,这里的返回值是表示给lua的返回的参数的个数
	*/
	int saveTable(lua_State *L);

	/*
	* Comments:这个是测试用例，用于把一个数据表压入
	  脚本里使用local b = LuaHelp.getTestTable() 将得到一个table
	* Param lua_State * L:
	* @Return int:返回值，是一个表的话就返回1
	*/
	int getTestTable(lua_State *L);

	/*
	* Comments:获取角色所在队伍的队员的列表
	* Param lua_State * L:脚本传来的参数是角色的指针
	   使用方法为: LuaHelp.getTeamMemberList(玩家的指针)
	* @Return int:返回1，是一个表
	*/
	int getTeamMemberList(lua_State *L);

	/*
	* Comments:通过队伍的指针，获取队伍成员的列表
	* Param lua_State * L:
	* @Return int:
	*/
	int getTeamMemberListByPtr(lua_State *L);

	/*
	* Comments:根据副本的id获取全服中这个副本的所有copy,返回副本的handle列表
	* Param int nFbid:
	* @Return void:
	*/
	int getFbFromId(lua_State *L);

	/*
	* Comments:获取玩家重配地图的坐标点
	* Param lua_State * L:传入玩家的指针
	* @Return int:返回一个表，里面3个数字，分别是场景id，坐标X，坐标Y
	*/
	int getReloadMapPos(lua_State *L);

	/*
	* Comments:获取周围的实体的指针列表
	* Param lua_State * L:[实体的指针][半径范围]
	* @Return int:返回一个表，包含所有的实体指针
	*/
	int getNearEntityList(lua_State *L);

	/*
	* Comments:获取周围的实体的指针列表
	* Param lua_State * L:[场景指针][x][y][半径范围]
	* @Return int:返回一个表，包含所有的实体指针
	*/
	int getNearEntityListFromXY(lua_State *L);

	

	/*
	* Comments:获取周围的实体的指针列表
	* Param lua_State * L:[场景指针][x][y][宽度半径][高度半径]
	* @Return int:返回一个表，包含所有的实体指针。获取到的区域范围是 (2*宽度半径)*(2*高度半径)
	*/
	int getNearEntityListFromRange(lua_State *L);

	/*
	*	f(pScene, leftUpX, leftUpY, rightDownX, rightDownY)
	*	获取区域内实体指针列表
	*/
	int getEntityListFromRange(lua_State *L);

	/*
	* Comments:获取所有的在线玩家的指针
	* Param lua_State * L:
	* @Return int:返回一个表，包含所有的实体指针
	*/
	int getAllActorList(lua_State *L);

	/*
	* Comments:获取场景的在线玩家的指针
	* Param lua_State * L:[int：场景id]
	* @Return int:返回一个表，包含所有的实体指针
	*/
	int getSceneActorListById(lua_State *L);

	/*
	* Comments:获取场景的怪物的指针
	* Param lua_State * L:[int：实体指针]
	* @Return int:返回一个表，包含所有的实体指针
	*/
	int getSceneMonsterList(lua_State *L);


		/*
	* Comments:获取场景的NPC指针
	* Param lua_State * L:[int：场景id]
	* @Return int:返回一个表，包含所有的实体指针
	*/
	int getSceneNpcListById(lua_State* L);

	/*
	* Comments:通过场景获取场景的怪物的指针列表
	* Param lua_State * L:场景指针
	* @Returns int:返回一个表，包含所有怪物实体指针
	*/
	int getSceneMonsterListByScene(lua_State *L);

	/*
	* Comments:获取场景的在线玩家的指针
	* Param lua_State * L:[void* et: 实体指针]
	* @Return int:返回一个表，包含所有的实体指针
	*/
	int getSceneActorList(lua_State *L);


	/*
	* Comments:获取排行榜前N名的数据
	* Param lua_State * L:[排行榜的指针][数量，表示要获取前N名]
	* @Return int:返回一个表，包含排行榜项的指针
	*/
	int getRankingItemList(lua_State* L);

	/*
	* Comments:获取副本内所有玩家的列表
	* Param lua_State * L:[副本的指针]
	* @Return int:返回一个表，包含所有玩家的指针
	*/
	int getFbActorList(lua_State* L);

	/*
	* Comments:获取实体可见范围内玩家的列表
	* Param lua_State * L:[实体指针]
	* @Return int:
	*/
	int getVisiActorList(lua_State* L);


	/*
	* Comments:获取当前常见的玩家列表
	* Param lua_State * L: [实体指针]
	* @Returns int:
	*/
	int getSceneActorListByPtr( lua_State *L);
}
