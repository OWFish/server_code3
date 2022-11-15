/*
** Lua binding: server
** Generated automatically by tolua++-1.0.92 on .
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
int  tolua_server_open (lua_State* tolua_S);

#include "StdAfx.h"
#include "../interface/actor_mgr_fun.h"
#include "../interface/actor_event_def.h"
#include "../interface/actor_export_fun.h"
#include "../interface/fuben_export_fun.h"
#include "../interface/system_export_fun.h"
#include "../interface/lua_data_packet.h"
#include "../interface/ranking_export.h"
#include "../interface/guild_export_fun.h"
#include "../../../common/common/property_id_def.h"
#include "../../../common/common/system_param_def.h"
#include "../../../common/db/actor_db_data.h"
#include "../../../common/db/role_data.h"
#include "../../../common/db/item_data.h"
#include "../../protocol/protos/test_proto.h"
#include "../../systems/attr/attribute.h"
#include "../../systems/attr/ex_attr.h"
#include "../../systems/togetherhit/together_hit_system.h"
#include "../../systems/scene/scene_def.h"
#include "../../entity/role/role_clone.h"
#include "../interface/redis_api.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_RobotData (lua_State* tolua_S)
{
 RobotData* self = (RobotData*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ItemData (lua_State* tolua_S)
{
 ItemData* self = (ItemData*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_RoleDatas (lua_State* tolua_S)
{
 RoleDatas* self = (RoleDatas*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ExAttribute (lua_State* tolua_S)
{
 ExAttribute* self = (ExAttribute*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_RoleData (lua_State* tolua_S)
{
 RoleData* self = (RoleData*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_Protocol__TestProto (lua_State* tolua_S)
{
 Protocol::TestProto* self = (Protocol::TestProto*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_Attribute (lua_State* tolua_S)
{
 Attribute* self = (Attribute*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_EquipSlotData (lua_State* tolua_S)
{
 EquipSlotData* self = (EquipSlotData*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"WingsEquip");
 tolua_usertype(tolua_S,"ShieldData");
 tolua_usertype(tolua_S,"ExRingsData");
 tolua_usertype(tolua_S,"LuaSocket");
 tolua_usertype(tolua_S,"BaseProto");
 tolua_usertype(tolua_S,"ActorBasicData");
 tolua_usertype(tolua_S,"FuWenData");
 tolua_usertype(tolua_S,"SkillsBreakData");
 tolua_usertype(tolua_S,"EquipSlotData");
 tolua_usertype(tolua_S,"Attribute");
 tolua_usertype(tolua_S,"Monster");
 tolua_usertype(tolua_S,"Actor");
 tolua_usertype(tolua_S,"RoleDatas");
 tolua_usertype(tolua_S,"ItemData");
 tolua_usertype(tolua_S,"Protocol::Test");
 tolua_usertype(tolua_S,"JingMaiData");
 tolua_usertype(tolua_S,"RobotData");
 tolua_usertype(tolua_S,"WingsData");
 tolua_usertype(tolua_S,"Protocol::TestProto");
 tolua_usertype(tolua_S,"RoleData");
 tolua_usertype(tolua_S,"SkillsData");
 tolua_usertype(tolua_S,"ExAttribute");
 tolua_usertype(tolua_S,"LoogsoulData");
 tolua_usertype(tolua_S,"XueyuData");
 tolua_usertype(tolua_S,"YuanShenData");
 tolua_usertype(tolua_S,"EquipsData");
}

/* function: LActorMgr::getDbConn */
#ifndef TOLUA_DISABLE_tolua_server_LActorMgr_getDbConn00
static int tolua_server_LActorMgr_getDbConn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   void* tolua_ret = (void*)  LActorMgr::getDbConn();
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getDbConn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActorMgr::getDataPacket */
#ifndef TOLUA_DISABLE_tolua_server_LActorMgr_getDataPacket00
static int tolua_server_LActorMgr_getDataPacket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   void* tolua_ret = (void*)  LActorMgr::getDataPacket();
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getDataPacket'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActorMgr::SendToGate */
#ifndef TOLUA_DISABLE_tolua_server_LActorMgr_SendToGate00
static int tolua_server_LActorMgr_SendToGate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* netid = ((void*)  tolua_touserdata(tolua_S,1,0));
  void* dp = ((void*)  tolua_touserdata(tolua_S,2,0));
  {
   LActorMgr::SendToGate(netid,dp);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'SendToGate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActorMgr::lowerCaseNameStr */
#ifndef TOLUA_DISABLE_tolua_server_LActorMgr_lowerCaseNameStr00
static int tolua_server_LActorMgr_lowerCaseNameStr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  LActorMgr::lowerCaseNameStr(name);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'lowerCaseNameStr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActorMgr::checkNameStr */
#ifndef TOLUA_DISABLE_tolua_server_LActorMgr_checkNameStr00
static int tolua_server_LActorMgr_checkNameStr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  LActorMgr::checkNameStr(name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'checkNameStr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActorMgr::nameHasUser */
#ifndef TOLUA_DISABLE_tolua_server_LActorMgr_nameHasUser00
static int tolua_server_LActorMgr_nameHasUser00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  LActorMgr::nameHasUser(name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'nameHasUser'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActorMgr::createActor */
#ifndef TOLUA_DISABLE_tolua_server_LActorMgr_createActor00
static int tolua_server_LActorMgr_createActor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isstring(tolua_S,8,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,9,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int accountid = ((int)  tolua_tonumber(tolua_S,1,0));
  const char* accountname = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,3,0));
  int sex = ((int)  tolua_tonumber(tolua_S,4,0));
  int job = ((int)  tolua_tonumber(tolua_S,5,0));
  int headimage = ((int)  tolua_tonumber(tolua_S,6,0));
  int actor_id = ((int)  tolua_tonumber(tolua_S,7,0));
  const char* pfid = ((const char*)  tolua_tostring(tolua_S,8,0));
  void* gateuser = ((void*)  tolua_touserdata(tolua_S,9,0));
  {
   int tolua_ret = (int)  LActorMgr::createActor(accountid,accountname,name,sex,job,headimage,actor_id,pfid,gateuser);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushnumber(tolua_S,(lua_Number)actor_id);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'createActor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActorMgr::enterGame */
#ifndef TOLUA_DISABLE_tolua_server_LActorMgr_enterGame00
static int tolua_server_LActorMgr_enterGame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* user = ((void*)  tolua_touserdata(tolua_S,1,0));
  int actor_id = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* pf = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* pfid = ((const char*)  tolua_tostring(tolua_S,4,0));
  const char* appid = ((const char*)  tolua_tostring(tolua_S,5,0));
  {
   LActorMgr::enterGame(user,actor_id,pf,pfid,appid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'enterGame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActorMgr::getRandomName */
#ifndef TOLUA_DISABLE_tolua_server_LActorMgr_getRandomName00
static int tolua_server_LActorMgr_getRandomName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int sex = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  LActorMgr::getRandomName(sex);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRandomName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActorMgr::isLoginBattle */
#ifndef TOLUA_DISABLE_tolua_server_LActorMgr_isLoginBattle00
static int tolua_server_LActorMgr_isLoginBattle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int aid = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  LActorMgr::isLoginBattle(aid);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'isLoginBattle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActorMgr::isLogoutBattle */
#ifndef TOLUA_DISABLE_tolua_server_LActorMgr_isLogoutBattle00
static int tolua_server_LActorMgr_isLogoutBattle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int aid = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActorMgr::isLogoutBattle(aid);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'isLogoutBattle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActorMgr::LoginOtherSrv */
#ifndef TOLUA_DISABLE_tolua_server_LActorMgr_LoginOtherSrv00
static int tolua_server_LActorMgr_LoginOtherSrv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* user = ((void*)  tolua_touserdata(tolua_S,1,0));
  int srvId = ((int)  tolua_tonumber(tolua_S,2,0));
  int actorId = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  LActorMgr::LoginOtherSrv(user,srvId,actorId);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'LoginOtherSrv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActorMgr::LoginLianfuSrv */
#ifndef TOLUA_DISABLE_tolua_server_LActorMgr_LoginLianfuSrv00
static int tolua_server_LActorMgr_LoginLianfuSrv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* user = ((void*)  tolua_touserdata(tolua_S,1,0));
  int actorId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  LActorMgr::LoginLianfuSrv(user,actorId);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'LoginLianfuSrv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getEntity */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getEntity00
static int tolua_server_LActor_getEntity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double handle = ((double)  tolua_tonumber(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LActor::getEntity(handle);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getEntity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getId */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getId00
static int tolua_server_LActor_getId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getId(et);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActor */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActor00
static int tolua_server_LActor_getActor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LActor::getActor(et);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorById */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorById00
static int tolua_server_LActor_getActorById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const int actorId = ((const int)  tolua_tonumber(tolua_S,1,0));
  bool ignoreinit = ((bool) (tolua_toboolean(tolua_S,2,false)!=0));
  bool includeImage = ((bool) (tolua_toboolean(tolua_S,3,false)!=0));
  {
   void* tolua_ret = (void*)  LActor::getActorById(actorId,ignoreinit,includeImage);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorById'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getServerId */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getServerId00
static int tolua_server_LActor_getServerId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getServerId(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getServerId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getServerIdById */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getServerIdById00
static int tolua_server_LActor_getServerIdById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const int actorid = ((const int)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getServerIdById(actorid);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getServerIdById'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorByName */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorByName00
static int tolua_server_LActor_getActorByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LActor::getActorByName(name);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorByAccountName */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorByAccountName00
static int tolua_server_LActor_getActorByAccountName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* accountName = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LActor::getActorByAccountName(accountName);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorByAccountName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorIdByAccountName */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorIdByAccountName00
static int tolua_server_LActor_getActorIdByAccountName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* accountName = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getActorIdByAccountName(accountName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorIdByAccountName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorIdByName */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorIdByName00
static int tolua_server_LActor_getActorIdByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* actorName = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getActorIdByName(actorName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorIdByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorData */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorData00
static int tolua_server_LActor_getActorData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   const ActorBasicData* tolua_ret = (const ActorBasicData*)  LActor::getActorData(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"const ActorBasicData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getName */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getName00
static int tolua_server_LActor_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  LActor::getName(et);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getLevel00
static int tolua_server_LActor_getLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   unsigned int tolua_ret = (unsigned int)  LActor::getLevel(et);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getJob */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getJob00
static int tolua_server_LActor_getJob00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getJob(et);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getJob'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getSex */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getSex00
static int tolua_server_LActor_getSex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getSex(et);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getSex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getLastLoginIp */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getLastLoginIp00
static int tolua_server_LActor_getLastLoginIp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  LActor::getLastLoginIp(et);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getLastLoginIp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorDataById */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorDataById00
static int tolua_server_LActor_getActorDataById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int id = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   const ActorBasicData* tolua_ret = (const ActorBasicData*)  LActor::getActorDataById(id);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"const ActorBasicData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorDataById'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorLevel00
static int tolua_server_LActor_getActorLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int id = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   unsigned int tolua_ret = (unsigned int)  LActor::getActorLevel(id);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorZhuanShengLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorZhuanShengLevel00
static int tolua_server_LActor_getActorZhuanShengLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int id = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   unsigned int tolua_ret = (unsigned int)  LActor::getActorZhuanShengLevel(id);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorZhuanShengLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorName */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorName00
static int tolua_server_LActor_getActorName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int id = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  LActor::getActorName(id);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorPower */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorPower00
static int tolua_server_LActor_getActorPower00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int id = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   double tolua_ret = (double)  LActor::getActorPower(id);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorPower'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorJob */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorJob00
static int tolua_server_LActor_getActorJob00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int id = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getActorJob(id);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorJob'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorSex */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorSex00
static int tolua_server_LActor_getActorSex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int id = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getActorSex(id);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorSex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::loginOtherSrv */
#ifndef TOLUA_DISABLE_tolua_server_LActor_loginOtherSrv00
static int tolua_server_LActor_loginOtherSrv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isstring(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int sid = ((int)  tolua_tonumber(tolua_S,2,0));
  unsigned int fbhdl = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  int sceneid = ((int)  tolua_tonumber(tolua_S,4,0));
  int x = ((int)  tolua_tonumber(tolua_S,5,0));
  int y = ((int)  tolua_tonumber(tolua_S,6,0));
  const char* reason = ((const char*)  tolua_tostring(tolua_S,7,""));
  {
   LActor::loginOtherSrv(et,sid,fbhdl,sceneid,x,y,reason);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'loginOtherSrv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setLevel00
static int tolua_server_LActor_setLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int level = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::setLevel(actor,level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::onLevelUp */
#ifndef TOLUA_DISABLE_tolua_server_LActor_onLevelUp00
static int tolua_server_LActor_onLevelUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::onLevelUp(actor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'onLevelUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getExp */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getExp00
static int tolua_server_LActor_getExp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   unsigned int tolua_ret = (unsigned int)  LActor::getExp(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getExp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setExp */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setExp00
static int tolua_server_LActor_setExp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int exp = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::setExp(actor,exp);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setExp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getRole */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getRole00
static int tolua_server_LActor_getRole00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   void* tolua_ret = (void*)  LActor::getRole(actor,roleId);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetRoleByJob */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetRoleByJob00
static int tolua_server_LActor_GetRoleByJob00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int job = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   void* tolua_ret = (void*)  LActor::GetRoleByJob(actor,job);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetRoleByJob'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getRoleData */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getRoleData00
static int tolua_server_LActor_getRoleData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   RoleData* tolua_ret = (RoleData*)  LActor::getRoleData(actor,roleId);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"RoleData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRoleData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getRoleCount */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getRoleCount00
static int tolua_server_LActor_getRoleCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getRoleCount(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRoleCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::createRole */
#ifndef TOLUA_DISABLE_tolua_server_LActor_createRole00
static int tolua_server_LActor_createRole00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int job = ((int)  tolua_tonumber(tolua_S,2,0));
  int sex = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::createRole(actor,job,sex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'createRole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::changeGold */
#ifndef TOLUA_DISABLE_tolua_server_LActor_changeGold00
static int tolua_server_LActor_changeGold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* log = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   LActor::changeGold(actor,value,log);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'changeGold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::changeYuanBao */
#ifndef TOLUA_DISABLE_tolua_server_LActor_changeYuanBao00
static int tolua_server_LActor_changeYuanBao00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* log = ((const char*)  tolua_tostring(tolua_S,3,0));
  bool ignore = ((bool) (tolua_toboolean(tolua_S,4,false)!=0));
  {
   LActor::changeYuanBao(actor,value,log,ignore);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'changeYuanBao'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getCurrency */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getCurrency00
static int tolua_server_LActor_getCurrency00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   long long tolua_ret = (long long)  LActor::getCurrency(actor,type);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getCurrency'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::changeCurrency */
#ifndef TOLUA_DISABLE_tolua_server_LActor_changeCurrency00
static int tolua_server_LActor_changeCurrency00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  int value = ((int)  tolua_tonumber(tolua_S,3,0));
  const char* log = ((const char*)  tolua_tostring(tolua_S,4,0));
  {
   LActor::changeCurrency(actor,type,value,log);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'changeCurrency'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::giveItem */
#ifndef TOLUA_DISABLE_tolua_server_LActor_giveItem00
static int tolua_server_LActor_giveItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  int count = ((int)  tolua_tonumber(tolua_S,3,0));
  const char* log = ((const char*)  tolua_tostring(tolua_S,4,0));
  {
   LActor::giveItem(actor,id,count,log);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'giveItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getEquipBagSpace */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getEquipBagSpace00
static int tolua_server_LActor_getEquipBagSpace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getEquipBagSpace(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getEquipBagSpace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::gmClearBag */
#ifndef TOLUA_DISABLE_tolua_server_LActor_gmClearBag00
static int tolua_server_LActor_gmClearBag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::gmClearBag(actor,type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'gmClearBag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getShowName */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getShowName00
static int tolua_server_LActor_getShowName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  LActor::getShowName(et);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getShowName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getHandle */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getHandle00
static int tolua_server_LActor_getHandle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   double tolua_ret = (double)  LActor::getHandle(et);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorOfflineTime */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorOfflineTime00
static int tolua_server_LActor_getActorOfflineTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getActorOfflineTime(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorOfflineTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::exitFuben */
#ifndef TOLUA_DISABLE_tolua_server_LActor_exitFuben00
static int tolua_server_LActor_exitFuben00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::exitFuben(et);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'exitFuben'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::reEnterScene */
#ifndef TOLUA_DISABLE_tolua_server_LActor_reEnterScene00
static int tolua_server_LActor_reEnterScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::reEnterScene(actor,x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'reEnterScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getFubenHandle */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getFubenHandle00
static int tolua_server_LActor_getFubenHandle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   unsigned int tolua_ret = (unsigned int)  LActor::getFubenHandle(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getFubenHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getSceneHandle */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getSceneHandle00
static int tolua_server_LActor_getSceneHandle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   unsigned int tolua_ret = (unsigned int)  LActor::getSceneHandle(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getSceneHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getFubenPrt */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getFubenPrt00
static int tolua_server_LActor_getFubenPrt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LActor::getFubenPrt(actor);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getFubenPrt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getFubenPtr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getFubenPtr00
static int tolua_server_LActor_getFubenPtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LActor::getFubenPtr(et);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getFubenPtr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getScenePtr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getScenePtr00
static int tolua_server_LActor_getScenePtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LActor::getScenePtr(et);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getScenePtr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getFubenId */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getFubenId00
static int tolua_server_LActor_getFubenId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getFubenId(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getFubenId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::isInFuben */
#ifndef TOLUA_DISABLE_tolua_server_LActor_isInFuben00
static int tolua_server_LActor_isInFuben00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  LActor::isInFuben(actor);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'isInFuben'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::isBoss */
#ifndef TOLUA_DISABLE_tolua_server_LActor_isBoss00
static int tolua_server_LActor_isBoss00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* creature = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  LActor::isBoss(creature);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'isBoss'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::enterScene */
#ifndef TOLUA_DISABLE_tolua_server_LActor_enterScene00
static int tolua_server_LActor_enterScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  unsigned int hScene = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  int x = ((int)  tolua_tonumber(tolua_S,3,0));
  int y = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::enterScene(et,hScene,x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'enterScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::instantMove */
#ifndef TOLUA_DISABLE_tolua_server_LActor_instantMove00
static int tolua_server_LActor_instantMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::instantMove(actor,x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'instantMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetFuBenType */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetFuBenType00
static int tolua_server_LActor_GetFuBenType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::GetFuBenType(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetFuBenType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getChapterLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getChapterLevel00
static int tolua_server_LActor_getChapterLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getChapterLevel(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getChapterLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setChapterLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setChapterLevel00
static int tolua_server_LActor_setChapterLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int level = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::setChapterLevel(actor,level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setChapterLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getVipLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getVipLevel00
static int tolua_server_LActor_getVipLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getVipLevel(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getVipLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setVipLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setVipLevel00
static int tolua_server_LActor_setVipLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int vip = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::setVipLevel(actor,vip);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setVipLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getMonthCard */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getMonthCard00
static int tolua_server_LActor_getMonthCard00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getMonthCard(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getMonthCard'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getRecharge */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getRecharge00
static int tolua_server_LActor_getRecharge00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getRecharge(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRecharge'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addRecharge */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addRecharge00
static int tolua_server_LActor_addRecharge00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int yb = ((int)  tolua_tonumber(tolua_S,2,0));
  int itemid = ((int)  tolua_tonumber(tolua_S,3,-1));
  {
   LActor::addRecharge(actor,yb,itemid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addRecharge'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addRechargeOffline */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addRechargeOffline00
static int tolua_server_LActor_addRechargeOffline00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actor_id = ((int)  tolua_tonumber(tolua_S,1,0));
  int yb = ((int)  tolua_tonumber(tolua_S,2,0));
  int itemid = ((int)  tolua_tonumber(tolua_S,3,-1));
  int yb_back = ((int)  tolua_tonumber(tolua_S,4,0));
  std::string orderNum = ((std::string)  tolua_tocppstring(tolua_S,5,""));
  {
   LActor::addRechargeOffline(actor_id,yb,itemid,yb_back,orderNum);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addRechargeOffline'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getEssence */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getEssence00
static int tolua_server_LActor_getEssence00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getEssence(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getEssence'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setEssence */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setEssence00
static int tolua_server_LActor_setEssence00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::setEssence(actor,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setEssence'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getExRingLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getExRingLevel00
static int tolua_server_LActor_getExRingLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* role = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  LActor::getExRingLevel(role,id);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getExRingLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setExRingLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setExRingLevel00
static int tolua_server_LActor_setExRingLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* role = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  int level = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::setExRingLevel(role,id,level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setExRingLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorExRingLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorExRingLevel00
static int tolua_server_LActor_getActorExRingLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  LActor::getActorExRingLevel(actor,id);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorExRingLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setActorExRingLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setActorExRingLevel00
static int tolua_server_LActor_setActorExRingLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  int level = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::setActorExRingLevel(actor,id,level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setActorExRingLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetActorExRingIsEff */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetActorExRingIsEff00
static int tolua_server_LActor_GetActorExRingIsEff00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  LActor::GetActorExRingIsEff(actor,id);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetActorExRingIsEff'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::SetActorExRingIsEff */
#ifndef TOLUA_DISABLE_tolua_server_LActor_SetActorExRingIsEff00
static int tolua_server_LActor_SetActorExRingIsEff00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  int eff = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::SetActorExRingIsEff(actor,id,eff);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'SetActorExRingIsEff'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::SetAexringMon */
#ifndef TOLUA_DISABLE_tolua_server_LActor_SetAexringMon00
static int tolua_server_LActor_SetAexringMon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* clone = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  void* mon = ((void*)  tolua_touserdata(tolua_S,3,0));
  {
   LActor::SetAexringMon(clone,id,mon);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'SetAexringMon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::ClearExRingMonster */
#ifndef TOLUA_DISABLE_tolua_server_LActor_ClearExRingMonster00
static int tolua_server_LActor_ClearExRingMonster00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::ClearExRingMonster(actor,id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'ClearExRingMonster'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::AddAerMonAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_AddAerMonAttr00
static int tolua_server_LActor_AddAerMonAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* clone = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,0));
  double value = ((double)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::AddAerMonAttr(clone,id,type,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'AddAerMonAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::AddAerMonExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_AddAerMonExAttr00
static int tolua_server_LActor_AddAerMonExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* clone = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,0));
  int value = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::AddAerMonExAttr(clone,id,type,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'AddAerMonExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::createSkirmishData */
#ifndef TOLUA_DISABLE_tolua_server_LActor_createSkirmishData00
static int tolua_server_LActor_createSkirmishData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  int id = ((int)  tolua_tonumber(tolua_S,3,0));
  int level = ((int)  tolua_tonumber(tolua_S,4,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,5,0));
  int attrper = ((int)  tolua_tonumber(tolua_S,6,0));
  {
   LActor::createSkirmishData(actor,index,id,level,name,attrper);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'createSkirmishData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::createKuangActorData */
#ifndef TOLUA_DISABLE_tolua_server_LActor_createKuangActorData00
static int tolua_server_LActor_createKuangActorData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int tactorId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::createKuangActorData(actor,tactorId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'createKuangActorData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::createFieldPlayerData */
#ifndef TOLUA_DISABLE_tolua_server_LActor_createFieldPlayerData00
static int tolua_server_LActor_createFieldPlayerData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,11,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  int actor_id = ((int)  tolua_tonumber(tolua_S,3,0));
  int pos_x = ((int)  tolua_tonumber(tolua_S,4,0));
  int pos_y = ((int)  tolua_tonumber(tolua_S,5,0));
  int actionType = ((int)  tolua_tonumber(tolua_S,6,0));
  int isForay = ((int)  tolua_tonumber(tolua_S,7,0));
  int killNum = ((int)  tolua_tonumber(tolua_S,8,0));
  int ox = ((int)  tolua_tonumber(tolua_S,9,0));
  int oy = ((int)  tolua_tonumber(tolua_S,10,0));
  {
   LActor::createFieldPlayerData(actor,index,actor_id,pos_x,pos_y,actionType,isForay,killNum,ox,oy);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'createFieldPlayerData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::isDeath */
#ifndef TOLUA_DISABLE_tolua_server_LActor_isDeath00
static int tolua_server_LActor_isDeath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  LActor::isDeath(et);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'isDeath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::relive */
#ifndef TOLUA_DISABLE_tolua_server_LActor_relive00
static int tolua_server_LActor_relive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::relive(et,x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'relive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::useSkill */
#ifndef TOLUA_DISABLE_tolua_server_LActor_useSkill00
static int tolua_server_LActor_useSkill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int skillId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  LActor::useSkill(et,skillId);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'useSkill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetSkillLaveCD */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetSkillLaveCD00
static int tolua_server_LActor_GetSkillLaveCD00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int skillId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   long long int tolua_ret = (long long int)  LActor::GetSkillLaveCD(et,skillId);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetSkillLaveCD'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::SetAllRoleSkillCdById */
#ifndef TOLUA_DISABLE_tolua_server_LActor_SetAllRoleSkillCdById00
static int tolua_server_LActor_SetAllRoleSkillCdById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int skillId = ((int)  tolua_tonumber(tolua_S,2,0));
  int cd_time = ((int)  tolua_tonumber(tolua_S,3,0));
  int mod = ((int)  tolua_tonumber(tolua_S,4,1));
  {
   LActor::SetAllRoleSkillCdById(actor,skillId,cd_time,mod);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'SetAllRoleSkillCdById'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addSkillEffect */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addSkillEffect00
static int tolua_server_LActor_addSkillEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int effid = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::addSkillEffect(et,effid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addSkillEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getMoneyCount */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getMoneyCount00
static int tolua_server_LActor_getMoneyCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  LActor::getMoneyCount(actor,type);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getMoneyCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::enterFuBen */
#ifndef TOLUA_DISABLE_tolua_server_LActor_enterFuBen00
static int tolua_server_LActor_enterFuBen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  unsigned int hFb = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  int sceneId = ((int)  tolua_tonumber(tolua_S,3,-1));
  int x = ((int)  tolua_tonumber(tolua_S,4,0));
  int y = ((int)  tolua_tonumber(tolua_S,5,0));
  bool pix = ((bool) (tolua_toboolean(tolua_S,6,false)!=0));
  {
   bool tolua_ret = (bool)  LActor::enterFuBen(et,hFb,sceneId,x,y,pix);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'enterFuBen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::changeHp */
#ifndef TOLUA_DISABLE_tolua_server_LActor_changeHp00
static int tolua_server_LActor_changeHp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  double nValue = ((double)  tolua_tonumber(tolua_S,2,0));
  void* killer = ((void*)  tolua_touserdata(tolua_S,3,NULL));
  {
   LActor::changeHp(et,nValue,killer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'changeHp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setHp */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setHp00
static int tolua_server_LActor_setHp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  double hp = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::setHp(et,hp);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setHp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setMp */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setMp00
static int tolua_server_LActor_setMp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  double mp = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::setMp(et,mp);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setMp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setNp */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setNp00
static int tolua_server_LActor_setNp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  double np = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::setNp(et,np);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setNp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getHp */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getHp00
static int tolua_server_LActor_getHp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   double tolua_ret = (double)  LActor::getHp(et);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getHp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getNp */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getNp00
static int tolua_server_LActor_getNp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   double tolua_ret = (double)  LActor::getNp(et);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getNp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getHpMax */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getHpMax00
static int tolua_server_LActor_getHpMax00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   double tolua_ret = (double)  LActor::getHpMax(et);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getHpMax'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getMpMax */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getMpMax00
static int tolua_server_LActor_getMpMax00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   double tolua_ret = (double)  LActor::getMpMax(et);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getMpMax'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getAttr00
static int tolua_server_LActor_getAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int atype = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   double tolua_ret = (double)  LActor::getAttr(et,atype);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getAtkSum */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getAtkSum00
static int tolua_server_LActor_getAtkSum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   double tolua_ret = (double)  LActor::getAtkSum(et);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getAtkSum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::gmSetAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_gmSetAttr00
static int tolua_server_LActor_gmSetAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  double value = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::gmSetAttr(actor,type,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'gmSetAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::recover */
#ifndef TOLUA_DISABLE_tolua_server_LActor_recover00
static int tolua_server_LActor_recover00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::recover(actor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'recover'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::sendTipmsg */
#ifndef TOLUA_DISABLE_tolua_server_LActor_sendTipmsg00
static int tolua_server_LActor_sendTipmsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  const char* sTipmsg = ((const char*)  tolua_tostring(tolua_S,2,0));
  int nType = ((int)  tolua_tonumber(tolua_S,3,ttMessage));
  {
   LActor::sendTipmsg(actor,sTipmsg,nType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'sendTipmsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::sendTipWithId */
#ifndef TOLUA_DISABLE_tolua_server_LActor_sendTipWithId00
static int tolua_server_LActor_sendTipWithId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int tipId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::sendTipWithId(actor,tipId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'sendTipWithId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorPtrByName */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorPtrByName00
static int tolua_server_LActor_getActorPtrByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* sName = ((char*)  tolua_tostring(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LActor::getActorPtrByName(sName);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorPtrByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getLoginTime */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getLoginTime00
static int tolua_server_LActor_getLoginTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   unsigned int tolua_ret = (unsigned int)  LActor::getLoginTime(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getLoginTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getLastLogoutTime */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getLastLogoutTime00
static int tolua_server_LActor_getLastLogoutTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   unsigned int tolua_ret = (unsigned int)  LActor::getLastLogoutTime(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getLastLogoutTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getLastLogoutDate */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getLastLogoutDate00
static int tolua_server_LActor_getLastLogoutDate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   unsigned int tolua_ret = (unsigned int)  LActor::getLastLogoutDate(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getLastLogoutDate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getLoginDate */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getLoginDate00
static int tolua_server_LActor_getLoginDate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   unsigned int tolua_ret = (unsigned int)  LActor::getLoginDate(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getLoginDate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getStaticVar */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getStaticVar00
static int tolua_server_LActor_getStaticVar00(lua_State* tolua_S)
{
	return LActor::getStaticVar(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getCrossVar */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getCrossVar00
static int tolua_server_LActor_getCrossVar00(lua_State* tolua_S)
{
	return LActor::getCrossVar(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::postScriptEvent */
#ifndef TOLUA_DISABLE_tolua_server_LActor_postScriptEvent00
static int tolua_server_LActor_postScriptEvent00(lua_State* tolua_S)
{
	return LActor::postScriptEvent(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::nextScriptEvent */
#ifndef TOLUA_DISABLE_tolua_server_LActor_nextScriptEvent00
static int tolua_server_LActor_nextScriptEvent00(lua_State* tolua_S)
{
	return LActor::nextScriptEvent(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::cancelScriptTimer */
#ifndef TOLUA_DISABLE_tolua_server_LActor_cancelScriptTimer00
static int tolua_server_LActor_cancelScriptTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  double handle = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::cancelScriptTimer(et,handle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'cancelScriptTimer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::isMonster */
#ifndef TOLUA_DISABLE_tolua_server_LActor_isMonster00
static int tolua_server_LActor_isMonster00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  LActor::isMonster(et);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'isMonster'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::isActor */
#ifndef TOLUA_DISABLE_tolua_server_LActor_isActor00
static int tolua_server_LActor_isActor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  LActor::isActor(et);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'isActor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::isPet */
#ifndef TOLUA_DISABLE_tolua_server_LActor_isPet00
static int tolua_server_LActor_isPet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  LActor::isPet(et);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'isPet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorId */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorId00
static int tolua_server_LActor_getActorId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getActorId(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getCloneRoleActorId */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getCloneRoleActorId00
static int tolua_server_LActor_getCloneRoleActorId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* clone_role = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getCloneRoleActorId(clone_role);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getCloneRoleActorId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getAccountName */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getAccountName00
static int tolua_server_LActor_getAccountName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  LActor::getAccountName(actor);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getAccountName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getAccountId */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getAccountId00
static int tolua_server_LActor_getAccountId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getAccountId(et);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getAccountId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getEntityType */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getEntityType00
static int tolua_server_LActor_getEntityType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getEntityType(et);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getEntityType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getPf */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getPf00
static int tolua_server_LActor_getPf00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  LActor::getPf(actor);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getPf'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getAppid */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getAppid00
static int tolua_server_LActor_getAppid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  LActor::getAppid(actor);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getAppid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getPfId */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getPfId00
static int tolua_server_LActor_getPfId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  LActor::getPfId(actor);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getPfId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getCloneRoleIsMirror */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getCloneRoleIsMirror00
static int tolua_server_LActor_getCloneRoleIsMirror00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* clone_role = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getCloneRoleIsMirror(clone_role);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getCloneRoleIsMirror'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetCloneRoleAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetCloneRoleAttr00
static int tolua_server_LActor_GetCloneRoleAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* clone_role = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::GetCloneRoleAttr(clone_role);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetCloneRoleAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getItemCount */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getItemCount00
static int tolua_server_LActor_getItemCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int itemId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  LActor::getItemCount(actor,itemId);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getItemCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::costItem */
#ifndef TOLUA_DISABLE_tolua_server_LActor_costItem00
static int tolua_server_LActor_costItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int itemId = ((int)  tolua_tonumber(tolua_S,2,0));
  int count = ((int)  tolua_tonumber(tolua_S,3,0));
  char* log = ((char*)  tolua_tostring(tolua_S,4,0));
  {
   LActor::costItem(actor,itemId,count,log);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'costItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::reCalcRoleAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_reCalcRoleAttr00
static int tolua_server_LActor_reCalcRoleAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::reCalcRoleAttr(et,roleId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'reCalcRoleAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::reCalcAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_reCalcAttr00
static int tolua_server_LActor_reCalcAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::reCalcAttr(et);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'reCalcAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::reCalcExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_reCalcExAttr00
static int tolua_server_LActor_reCalcExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::reCalcExAttr(et);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'reCalcExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::reCalcBattleAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_reCalcBattleAttr00
static int tolua_server_LActor_reCalcBattleAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::reCalcBattleAttr(et);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'reCalcBattleAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::battleComparison */
#ifndef TOLUA_DISABLE_tolua_server_LActor_battleComparison00
static int tolua_server_LActor_battleComparison00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int actorId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::battleComparison(actor,actorId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'battleComparison'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getWingInfo */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getWingInfo00
static int tolua_server_LActor_getWingInfo00(lua_State* tolua_S)
{
	return LActor::getWingInfo(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setWingLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setWingLevel00
static int tolua_server_LActor_setWingLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int level = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::setWingLevel(actor,roleId,level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setWingLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setWingStar */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setWingStar00
static int tolua_server_LActor_setWingStar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int star = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::setWingStar(actor,roleId,star);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setWingStar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setWingExp */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setWingExp00
static int tolua_server_LActor_setWingExp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int exp = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::setWingExp(actor,roleId,exp);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setWingExp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setWingStatus */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setWingStatus00
static int tolua_server_LActor_setWingStatus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int status = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::setWingStatus(actor,roleId,status);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setWingStatus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setWingCTime */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setWingCTime00
static int tolua_server_LActor_setWingCTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  unsigned int ctime = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::setWingCTime(actor,roleId,ctime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setWingCTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setWingPill */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setWingPill00
static int tolua_server_LActor_setWingPill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int idx = ((int)  tolua_tonumber(tolua_S,3,0));
  int count = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::setWingPill(actor,roleId,idx,count);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setWingPill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::clearWingAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_clearWingAttr00
static int tolua_server_LActor_clearWingAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::clearWingAttr(actor,roleId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'clearWingAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addWingAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addWingAttr00
static int tolua_server_LActor_addWingAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,0));
  int value = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::addWingAttr(actor,roleId,type,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addWingAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addWingTempAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addWingTempAttr00
static int tolua_server_LActor_addWingTempAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,0));
  int value = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::addWingTempAttr(actor,roleId,type,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addWingTempAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::wingInfoSync */
#ifndef TOLUA_DISABLE_tolua_server_LActor_wingInfoSync00
static int tolua_server_LActor_wingInfoSync00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::wingInfoSync(actor,roleId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'wingInfoSync'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getEnhanceInfo */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getEnhanceInfo00
static int tolua_server_LActor_getEnhanceInfo00(lua_State* tolua_S)
{
	return LActor::getEnhanceInfo(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setEnhanceLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setEnhanceLevel00
static int tolua_server_LActor_setEnhanceLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int posId = ((int)  tolua_tonumber(tolua_S,3,0));
  int level = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::setEnhanceLevel(actor,roleId,posId,level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setEnhanceLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::clearEnhanceAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_clearEnhanceAttr00
static int tolua_server_LActor_clearEnhanceAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::clearEnhanceAttr(actor,roleId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'clearEnhanceAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addEnhanceAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addEnhanceAttr00
static int tolua_server_LActor_addEnhanceAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,0));
  int value = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::addEnhanceAttr(actor,roleId,type,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addEnhanceAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getFulingInfo */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getFulingInfo00
static int tolua_server_LActor_getFulingInfo00(lua_State* tolua_S)
{
	return LActor::getFulingInfo(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setFulingInfo */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setFulingInfo00
static int tolua_server_LActor_setFulingInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int posId = ((int)  tolua_tonumber(tolua_S,3,0));
  int level = ((int)  tolua_tonumber(tolua_S,4,0));
  int exp = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   LActor::setFulingInfo(actor,roleId,posId,level,exp);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setFulingInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getFulingAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getFulingAttr00
static int tolua_server_LActor_getFulingAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getFulingAttr(actor,roleId);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getFulingAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getFulingExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getFulingExAttr00
static int tolua_server_LActor_getFulingExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::getFulingExAttr(actor,roleId);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getFulingExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getSoulLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getSoulLevel00
static int tolua_server_LActor_getSoulLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int pos = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   int tolua_ret = (int)  LActor::getSoulLevel(actor,roleId,pos);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getSoulLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setSoulLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setSoulLevel00
static int tolua_server_LActor_setSoulLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int posId = ((int)  tolua_tonumber(tolua_S,3,0));
  int level = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::setSoulLevel(actor,roleId,posId,level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setSoulLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getSoulAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getSoulAttr00
static int tolua_server_LActor_getSoulAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getSoulAttr(actor,roleId);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getSoulAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getSoulExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getSoulExAttr00
static int tolua_server_LActor_getSoulExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::getSoulExAttr(actor,roleId);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getSoulExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getJadePlateAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getJadePlateAttr00
static int tolua_server_LActor_getJadePlateAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getJadePlateAttr(actor,roleId);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getJadePlateAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getJadePlateExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getJadePlateExAttr00
static int tolua_server_LActor_getJadePlateExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::getJadePlateExAttr(actor,roleId);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getJadePlateExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getZhiZunAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getZhiZunAttr00
static int tolua_server_LActor_getZhiZunAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getZhiZunAttr(actor,roleId);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getZhiZunAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getZhiZunExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getZhiZunExAttr00
static int tolua_server_LActor_getZhiZunExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::getZhiZunExAttr(actor,roleId);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getZhiZunExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getLeiTingEquipAttrs */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getLeiTingEquipAttrs00
static int tolua_server_LActor_getLeiTingEquipAttrs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getLeiTingEquipAttrs(actor,roleId);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getLeiTingEquipAttrs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getLeiTingEquipExAttrs */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getLeiTingEquipExAttrs00
static int tolua_server_LActor_getLeiTingEquipExAttrs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::getLeiTingEquipExAttrs(actor,roleId);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getLeiTingEquipExAttrs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getTogetherPunchInfo */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getTogetherPunchInfo00
static int tolua_server_LActor_getTogetherPunchInfo00(lua_State* tolua_S)
{
	return LActor::getTogetherPunchInfo(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setTogetHerEquipLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setTogetHerEquipLevel00
static int tolua_server_LActor_setTogetHerEquipLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int pos = ((int)  tolua_tonumber(tolua_S,2,0));
  int lv = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::setTogetHerEquipLevel(actor,pos,lv);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setTogetHerEquipLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getTogetherPunchAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getTogetherPunchAttr00
static int tolua_server_LActor_getTogetherPunchAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getTogetherPunchAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getTogetherPunchAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getTogetherPunchExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getTogetherPunchExAttr00
static int tolua_server_LActor_getTogetherPunchExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::getTogetherPunchExAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getTogetherPunchExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getMailInfo */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getMailInfo00
static int tolua_server_LActor_getMailInfo00(lua_State* tolua_S)
{
	return LActor::getMailInfo(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getMailList */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getMailList00
static int tolua_server_LActor_getMailList00(lua_State* tolua_S)
{
	return LActor::getMailList(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::deleteMail */
#ifndef TOLUA_DISABLE_tolua_server_LActor_deleteMail00
static int tolua_server_LActor_deleteMail00(lua_State* tolua_S)
{
	return LActor::deleteMail(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::changeMailReadStatus */
#ifndef TOLUA_DISABLE_tolua_server_LActor_changeMailReadStatus00
static int tolua_server_LActor_changeMailReadStatus00(lua_State* tolua_S)
{
	return LActor::changeMailReadStatus(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::changeMailAwardStatus */
#ifndef TOLUA_DISABLE_tolua_server_LActor_changeMailAwardStatus00
static int tolua_server_LActor_changeMailAwardStatus00(lua_State* tolua_S)
{
	return LActor::changeMailAwardStatus(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getStoneInfo */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getStoneInfo00
static int tolua_server_LActor_getStoneInfo00(lua_State* tolua_S)
{
	return LActor::getStoneInfo(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setStoneLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setStoneLevel00
static int tolua_server_LActor_setStoneLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int posId = ((int)  tolua_tonumber(tolua_S,3,0));
  int level = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::setStoneLevel(actor,roleId,posId,level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setStoneLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::clearStoneAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_clearStoneAttr00
static int tolua_server_LActor_clearStoneAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::clearStoneAttr(actor,roleId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'clearStoneAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addStoneAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addStoneAttr00
static int tolua_server_LActor_addStoneAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,0));
  int value = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::addStoneAttr(actor,roleId,type,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addStoneAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getJingmaiInfo */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getJingmaiInfo00
static int tolua_server_LActor_getJingmaiInfo00(lua_State* tolua_S)
{
	return LActor::getJingmaiInfo(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setJingmaiLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setJingmaiLevel00
static int tolua_server_LActor_setJingmaiLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int level = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::setJingmaiLevel(actor,roleId,level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setJingmaiLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setJingmaiStage */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setJingmaiStage00
static int tolua_server_LActor_setJingmaiStage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int stage = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::setJingmaiStage(actor,roleId,stage);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setJingmaiStage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::clearJingmaiAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_clearJingmaiAttr00
static int tolua_server_LActor_clearJingmaiAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::clearJingmaiAttr(actor,roleId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'clearJingmaiAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addJingmaiAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addJingmaiAttr00
static int tolua_server_LActor_addJingmaiAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,0));
  int value = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::addJingmaiAttr(actor,roleId,type,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addJingmaiAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getZhulingInfo */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getZhulingInfo00
static int tolua_server_LActor_getZhulingInfo00(lua_State* tolua_S)
{
	return LActor::getZhulingInfo(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setZhulingLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setZhulingLevel00
static int tolua_server_LActor_setZhulingLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int posId = ((int)  tolua_tonumber(tolua_S,3,0));
  int level = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::setZhulingLevel(actor,roleId,posId,level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setZhulingLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::clearZhulingAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_clearZhulingAttr00
static int tolua_server_LActor_clearZhulingAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::clearZhulingAttr(actor,roleId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'clearZhulingAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addZhulingAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addZhulingAttr00
static int tolua_server_LActor_addZhulingAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,0));
  int value = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::addZhulingAttr(actor,roleId,type,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addZhulingAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::takeOutEquip */
#ifndef TOLUA_DISABLE_tolua_server_LActor_takeOutEquip00
static int tolua_server_LActor_takeOutEquip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int posId = ((int)  tolua_tonumber(tolua_S,3,0));
  int equiptype = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::takeOutEquip(actor,roleId,posId,equiptype);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'takeOutEquip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getEquipAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getEquipAttr00
static int tolua_server_LActor_getEquipAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int posId = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   Attribute tolua_ret = (Attribute)  LActor::getEquipAttr(actor,roleId,posId);
   {
#ifdef __cplusplus
    void* tolua_obj = new Attribute(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"Attribute");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Attribute));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"Attribute");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getEquipAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getEquipExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getEquipExAttr00
static int tolua_server_LActor_getEquipExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int posId = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   ExAttribute tolua_ret = (ExAttribute)  LActor::getEquipExAttr(actor,roleId,posId);
   {
#ifdef __cplusplus
    void* tolua_obj = new ExAttribute(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"ExAttribute");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(ExAttribute));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"ExAttribute");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getEquipExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getZhuanShengAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getZhuanShengAttr00
static int tolua_server_LActor_getZhuanShengAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getZhuanShengAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getZhuanShengAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getNeigongAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getNeigongAttr00
static int tolua_server_LActor_getNeigongAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getNeigongAttr(actor,roleId);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getNeigongAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getExRingAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getExRingAttr00
static int tolua_server_LActor_getExRingAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* role = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getExRingAttr(role);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getExRingAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getExRingExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getExRingExAttr00
static int tolua_server_LActor_getExRingExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* role = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::getExRingExAttr(role);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getExRingExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorExRingAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorExRingAttr00
static int tolua_server_LActor_getActorExRingAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getActorExRingAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorExRingAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorExRingExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorExRingExAttr00
static int tolua_server_LActor_getActorExRingExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::getActorExRingExAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorExRingExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorExRingMonsterAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorExRingMonsterAttr00
static int tolua_server_LActor_getActorExRingMonsterAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int rid = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getActorExRingMonsterAttr(actor,rid);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorExRingMonsterAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorExRingMonsterExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorExRingMonsterExAttr00
static int tolua_server_LActor_getActorExRingMonsterExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int rid = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::getActorExRingMonsterExAttr(actor,rid);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorExRingMonsterExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::createActorExRingMonster */
#ifndef TOLUA_DISABLE_tolua_server_LActor_createActorExRingMonster00
static int tolua_server_LActor_createActorExRingMonster00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int rid = ((int)  tolua_tonumber(tolua_S,2,0));
  int id = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   Monster* tolua_ret = (Monster*)  LActor::createActorExRingMonster(actor,rid,id);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Monster");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'createActorExRingMonster'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::DestroyBattleRing */
#ifndef TOLUA_DISABLE_tolua_server_LActor_DestroyBattleRing00
static int tolua_server_LActor_DestroyBattleRing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int rid = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::DestroyBattleRing(actor,rid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'DestroyBattleRing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorExRingMonster */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorExRingMonster00
static int tolua_server_LActor_getActorExRingMonster00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int rid = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Monster* tolua_ret = (Monster*)  LActor::getActorExRingMonster(actor,rid);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Monster");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorExRingMonster'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::SetMasterHandle */
#ifndef TOLUA_DISABLE_tolua_server_LActor_SetMasterHandle00
static int tolua_server_LActor_SetMasterHandle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  void* met = ((void*)  tolua_touserdata(tolua_S,2,0));
  {
   LActor::SetMasterHandle(et,met);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'SetMasterHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::changeMonsterAi */
#ifndef TOLUA_DISABLE_tolua_server_LActor_changeMonsterAi00
static int tolua_server_LActor_changeMonsterAi00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int aid = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::changeMonsterAi(et,aid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'changeMonsterAi'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getTogetherHitAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getTogetherHitAttr00
static int tolua_server_LActor_getTogetherHitAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getTogetherHitAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getTogetherHitAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getTogetherHitExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getTogetherHitExAttr00
static int tolua_server_LActor_getTogetherHitExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::getTogetherHitExAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getTogetherHitExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getTogetherHitSkillExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getTogetherHitSkillExAttr00
static int tolua_server_LActor_getTogetherHitSkillExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::getTogetherHitSkillExAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getTogetherHitSkillExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorsystemAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorsystemAttr00
static int tolua_server_LActor_getActorsystemAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int attrId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getActorsystemAttr(actor,attrId);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorsystemAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getZhuanShengLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getZhuanShengLevel00
static int tolua_server_LActor_getZhuanShengLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getZhuanShengLevel(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getZhuanShengLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getReincarnateLv */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getReincarnateLv00
static int tolua_server_LActor_getReincarnateLv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getReincarnateLv(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getReincarnateLv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getRoleSkillLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getRoleSkillLevel00
static int tolua_server_LActor_getRoleSkillLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleid = ((int)  tolua_tonumber(tolua_S,2,0));
  int index = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   int tolua_ret = (int)  LActor::getRoleSkillLevel(actor,roleid,index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRoleSkillLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::upgradeSkill */
#ifndef TOLUA_DISABLE_tolua_server_LActor_upgradeSkill00
static int tolua_server_LActor_upgradeSkill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleid = ((int)  tolua_tonumber(tolua_S,2,0));
  int index = ((int)  tolua_tonumber(tolua_S,3,0));
  int level = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::upgradeSkill(actor,roleid,index,level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'upgradeSkill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getRoleSkillBreakLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getRoleSkillBreakLevel00
static int tolua_server_LActor_getRoleSkillBreakLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleid = ((int)  tolua_tonumber(tolua_S,2,0));
  int index = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   int tolua_ret = (int)  LActor::getRoleSkillBreakLevel(actor,roleid,index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRoleSkillBreakLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::upgradeSkillBreak */
#ifndef TOLUA_DISABLE_tolua_server_LActor_upgradeSkillBreak00
static int tolua_server_LActor_upgradeSkillBreak00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleid = ((int)  tolua_tonumber(tolua_S,2,0));
  int index = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::upgradeSkillBreak(actor,roleid,index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'upgradeSkillBreak'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getStoreItemData */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getStoreItemData00
static int tolua_server_LActor_getStoreItemData00(lua_State* tolua_S)
{
	return LActor::getStoreItemData(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::giveStoreItem */
#ifndef TOLUA_DISABLE_tolua_server_LActor_giveStoreItem00
static int tolua_server_LActor_giveStoreItem00(lua_State* tolua_S)
{
	return LActor::giveStoreItem(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addStoreItem */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addStoreItem00
static int tolua_server_LActor_addStoreItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  int itemId = ((int)  tolua_tonumber(tolua_S,3,0));
  int count = ((int)  tolua_tonumber(tolua_S,4,0));
  int currencyType = ((int)  tolua_tonumber(tolua_S,5,0));
  int currency = ((int)  tolua_tonumber(tolua_S,6,0));
  int discount = ((int)  tolua_tonumber(tolua_S,7,0));
  {
   LActor::addStoreItem(actor,id,itemId,count,currencyType,currency,discount);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addStoreItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::StoreClearList */
#ifndef TOLUA_DISABLE_tolua_server_LActor_StoreClearList00
static int tolua_server_LActor_StoreClearList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::StoreClearList(actor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'StoreClearList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::StoreDataSync */
#ifndef TOLUA_DISABLE_tolua_server_LActor_StoreDataSync00
static int tolua_server_LActor_StoreDataSync00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int refreshCount = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::StoreDataSync(actor,refreshCount);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'StoreDataSync'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getAITarget */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getAITarget00
static int tolua_server_LActor_getAITarget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* creature = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LActor::getAITarget(creature);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getAITarget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::changeAITarget */
#ifndef TOLUA_DISABLE_tolua_server_LActor_changeAITarget00
static int tolua_server_LActor_changeAITarget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* creature = ((void*)  tolua_touserdata(tolua_S,1,0));
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::changeAITarget(creature,type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'changeAITarget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setAITarget */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setAITarget00
static int tolua_server_LActor_setAITarget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* creature = ((void*)  tolua_touserdata(tolua_S,1,0));
  void* target = ((void*)  tolua_touserdata(tolua_S,2,0));
  {
   LActor::setAITarget(creature,target);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setAITarget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setAITargetNull */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setAITargetNull00
static int tolua_server_LActor_setAITargetNull00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* creature = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::setAITargetNull(creature);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setAITargetNull'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setAIPassivity */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setAIPassivity00
static int tolua_server_LActor_setAIPassivity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* creature = ((void*)  tolua_touserdata(tolua_S,1,0));
  bool b = ((bool) (tolua_toboolean(tolua_S,2,0)!=0));
  {
   LActor::setAIPassivity(creature,b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setAIPassivity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getAIPassivity */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getAIPassivity00
static int tolua_server_LActor_getAIPassivity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* creature = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  LActor::getAIPassivity(creature);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getAIPassivity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setAIAttackMonster */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setAIAttackMonster00
static int tolua_server_LActor_setAIAttackMonster00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::setAIAttackMonster(actor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setAIAttackMonster'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getSoulShieldinfo */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getSoulShieldinfo00
static int tolua_server_LActor_getSoulShieldinfo00(lua_State* tolua_S)
{
	return LActor::getSoulShieldinfo(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setSoulShieldLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setSoulShieldLevel00
static int tolua_server_LActor_setSoulShieldLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,0));
  int level = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::setSoulShieldLevel(actor,roleId,type,level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setSoulShieldLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setSoulShieldStage */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setSoulShieldStage00
static int tolua_server_LActor_setSoulShieldStage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,0));
  int stage = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::setSoulShieldStage(et,roleId,type,stage);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setSoulShieldStage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setSoulShieldExp */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setSoulShieldExp00
static int tolua_server_LActor_setSoulShieldExp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,0));
  int exp = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::setSoulShieldExp(et,roleId,type,exp);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setSoulShieldExp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setSoulShieldAct */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setSoulShieldAct00
static int tolua_server_LActor_setSoulShieldAct00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,0));
  int act = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::setSoulShieldAct(et,roleId,type,act);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setSoulShieldAct'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::clearSoulShieldAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_clearSoulShieldAttr00
static int tolua_server_LActor_clearSoulShieldAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::clearSoulShieldAttr(actor,roleId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'clearSoulShieldAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addSoulShieldAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addSoulShieldAttr00
static int tolua_server_LActor_addSoulShieldAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,0));
  int value = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::addSoulShieldAttr(actor,roleId,type,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addSoulShieldAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::giveItemToDepot */
#ifndef TOLUA_DISABLE_tolua_server_LActor_giveItemToDepot00
static int tolua_server_LActor_giveItemToDepot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int itemId = ((int)  tolua_tonumber(tolua_S,2,0));
  int count = ((int)  tolua_tonumber(tolua_S,3,0));
  const char* log = ((const char*)  tolua_tostring(tolua_S,4,0));
  {
   LActor::giveItemToDepot(actor,itemId,count,log);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'giveItemToDepot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getDepotCount */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getDepotCount00
static int tolua_server_LActor_getDepotCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getDepotCount(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getDepotCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getRoleBasicAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getRoleBasicAttr00
static int tolua_server_LActor_getRoleBasicAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getRoleBasicAttr(actor,roleId);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRoleBasicAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getKnighthoodAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getKnighthoodAttr00
static int tolua_server_LActor_getKnighthoodAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getKnighthoodAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getKnighthoodAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getKnighthoodExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getKnighthoodExAttr00
static int tolua_server_LActor_getKnighthoodExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::getKnighthoodExAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getKnighthoodExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getYuPeiAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getYuPeiAttr00
static int tolua_server_LActor_getYuPeiAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getYuPeiAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getYuPeiAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getYuPeiExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getYuPeiExAttr00
static int tolua_server_LActor_getYuPeiExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::getYuPeiExAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getYuPeiExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getPerstigeAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getPerstigeAttr00
static int tolua_server_LActor_getPerstigeAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getPerstigeAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getPerstigeAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getArtifactsAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getArtifactsAttr00
static int tolua_server_LActor_getArtifactsAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getArtifactsAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getArtifactsAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getTrainsystemAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getTrainsystemAttr00
static int tolua_server_LActor_getTrainsystemAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getTrainsystemAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getTrainsystemAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getTrainsystemExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getTrainsystemExAttr00
static int tolua_server_LActor_getTrainsystemExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::getTrainsystemExAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getTrainsystemExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getChallengefbsystemAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getChallengefbsystemAttr00
static int tolua_server_LActor_getChallengefbsystemAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getChallengefbsystemAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getChallengefbsystemAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getRongLuAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getRongLuAttr00
static int tolua_server_LActor_getRongLuAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getRongLuAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRongLuAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getMonthCardAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getMonthCardAttr00
static int tolua_server_LActor_getMonthCardAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getMonthCardAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getMonthCardAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetReincarnateAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetReincarnateAttr00
static int tolua_server_LActor_GetReincarnateAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::GetReincarnateAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetReincarnateAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetReincarnateExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetReincarnateExAttr00
static int tolua_server_LActor_GetReincarnateExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::GetReincarnateExAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetReincarnateExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getPrivilegeAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getPrivilegeAttr00
static int tolua_server_LActor_getPrivilegeAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getPrivilegeAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getPrivilegeAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getVipAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getVipAttr00
static int tolua_server_LActor_getVipAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getVipAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getVipAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getNewWorldBossAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getNewWorldBossAttr00
static int tolua_server_LActor_getNewWorldBossAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getNewWorldBossAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getNewWorldBossAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getGodWeaponAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getGodWeaponAttr00
static int tolua_server_LActor_getGodWeaponAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getGodWeaponAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getGodWeaponAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getGodWeaponExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getGodWeaponExAttr00
static int tolua_server_LActor_getGodWeaponExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::getGodWeaponExAttr(actor);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getGodWeaponExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getCreateTime */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getCreateTime00
static int tolua_server_LActor_getCreateTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   unsigned int tolua_ret = (unsigned int)  LActor::getCreateTime(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getCreateTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::updataEquipBagCapacity */
#ifndef TOLUA_DISABLE_tolua_server_LActor_updataEquipBagCapacity00
static int tolua_server_LActor_updataEquipBagCapacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int add = ((int)  tolua_tonumber(tolua_S,2,0));
  int capacity = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::updataEquipBagCapacity(actor,add,capacity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'updataEquipBagCapacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::isImage */
#ifndef TOLUA_DISABLE_tolua_server_LActor_isImage00
static int tolua_server_LActor_isImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  LActor::isImage(actor);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'isImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getGmLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getGmLevel00
static int tolua_server_LActor_getGmLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getGmLevel(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getGmLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getEquipPointAttrs */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getEquipPointAttrs00
static int tolua_server_LActor_getEquipPointAttrs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int role_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getEquipPointAttrs(actor,role_id);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getEquipPointAttrs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorInfoPacket */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorInfoPacket00
static int tolua_server_LActor_getActorInfoPacket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LActor::getActorInfoPacket(et);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorInfoPacket'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetActorInfo */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetActorInfo00
static int tolua_server_LActor_GetActorInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int actor_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  LActor::GetActorInfo(actor,actor_id);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetActorInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::findTiantiActor */
#ifndef TOLUA_DISABLE_tolua_server_LActor_findTiantiActor00
static int tolua_server_LActor_findTiantiActor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::findTiantiActor(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'findTiantiActor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::createRoldClone */
#ifndef TOLUA_DISABLE_tolua_server_LActor_createRoldClone00
static int tolua_server_LActor_createRoldClone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actor_id = ((int)  tolua_tonumber(tolua_S,1,0));
  unsigned int scene = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  int x = ((int)  tolua_tonumber(tolua_S,3,0));
  int y = ((int)  tolua_tonumber(tolua_S,4,0));
  int sid = ((int)  tolua_tonumber(tolua_S,5,0));
  int camp = ((int)  tolua_tonumber(tolua_S,6,0));
  {
   LActor::createRoldClone(actor_id,scene,x,y,sid,camp);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'createRoldClone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::createRobot */
#ifndef TOLUA_DISABLE_tolua_server_LActor_createRobot00
static int tolua_server_LActor_createRobot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RobotData",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RobotData* data = ((RobotData*)  tolua_tousertype(tolua_S,1,0));
  unsigned int scene = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  int x = ((int)  tolua_tonumber(tolua_S,3,0));
  int y = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   void* tolua_ret = (void*)  LActor::createRobot(data,scene,x,y);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'createRobot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::cloneRoleEmpty */
#ifndef TOLUA_DISABLE_tolua_server_LActor_cloneRoleEmpty00
static int tolua_server_LActor_cloneRoleEmpty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int scene = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  LActor::cloneRoleEmpty(scene);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'cloneRoleEmpty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::tiantiRefreshWeek */
#ifndef TOLUA_DISABLE_tolua_server_LActor_tiantiRefreshWeek00
static int tolua_server_LActor_tiantiRefreshWeek00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LActor::tiantiRefreshWeek();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'tiantiRefreshWeek'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getEquipBlessAttrs */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getEquipBlessAttrs00
static int tolua_server_LActor_getEquipBlessAttrs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int role_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getEquipBlessAttrs(actor,role_id);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getEquipBlessAttrs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getTitleAttrs */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getTitleAttrs00
static int tolua_server_LActor_getTitleAttrs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getTitleAttrs(et);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getTitleAttrs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::reCalcTitleAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_reCalcTitleAttr00
static int tolua_server_LActor_reCalcTitleAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::reCalcTitleAttr(et);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'reCalcTitleAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setRoleTitle */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setRoleTitle00
static int tolua_server_LActor_setRoleTitle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int tId = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::setRoleTitle(et,roleId,tId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setRoleTitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::changeMiJi */
#ifndef TOLUA_DISABLE_tolua_server_LActor_changeMiJi00
static int tolua_server_LActor_changeMiJi00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleid = ((int)  tolua_tonumber(tolua_S,2,0));
  int oldId = ((int)  tolua_tonumber(tolua_S,3,0));
  int id = ((int)  tolua_tonumber(tolua_S,4,0));
  bool refresh = ((bool) (tolua_toboolean(tolua_S,5,0)!=0));
  int param1 = ((int)  tolua_tonumber(tolua_S,6,0));
  int param2 = ((int)  tolua_tonumber(tolua_S,7,0));
  int param3 = ((int)  tolua_tonumber(tolua_S,8,0));
  int power = ((int)  tolua_tonumber(tolua_S,9,0));
  {
   LActor::changeMiJi(actor,roleid,oldId,id,refresh,param1,param2,param3,power);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'changeMiJi'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::refreshMiJi */
#ifndef TOLUA_DISABLE_tolua_server_LActor_refreshMiJi00
static int tolua_server_LActor_refreshMiJi00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleid = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::refreshMiJi(actor,roleid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'refreshMiJi'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getRainingFirstCacheByType */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getRainingFirstCacheByType00
static int tolua_server_LActor_getRainingFirstCacheByType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int type = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LActor::getRainingFirstCacheByType(type);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRainingFirstCacheByType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::updateDynamicFirstCache */
#ifndef TOLUA_DISABLE_tolua_server_LActor_updateDynamicFirstCache00
static int tolua_server_LActor_updateDynamicFirstCache00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actor_id = ((int)  tolua_tonumber(tolua_S,1,0));
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::updateDynamicFirstCache(actor_id,type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'updateDynamicFirstCache'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::updateRanking */
#ifndef TOLUA_DISABLE_tolua_server_LActor_updateRanking00
static int tolua_server_LActor_updateRanking00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LActor::updateRanking();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'updateRanking'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getRankDataByType */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getRankDataByType00
static int tolua_server_LActor_getRankDataByType00(lua_State* tolua_S)
{
	return LActor::getRankDataByType(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getRanking */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getRanking00
static int tolua_server_LActor_getRanking00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int type = ((int)  tolua_tonumber(tolua_S,1,0));
  void* et = ((void*)  tolua_touserdata(tolua_S,2,0));
  {
   int tolua_ret = (int)  LActor::getRanking(type,et);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRanking'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getRankCacheByType */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getRankCacheByType00
static int tolua_server_LActor_getRankCacheByType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int type = ((int)  tolua_tonumber(tolua_S,1,0));
  int min = ((int)  tolua_tonumber(tolua_S,2,0));
  int max = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   void* tolua_ret = (void*)  LActor::getRankCacheByType(type,min,max);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRankCacheByType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::regAsynEvent */
#ifndef TOLUA_DISABLE_tolua_server_LActor_regAsynEvent00
static int tolua_server_LActor_regAsynEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actorid = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   LActor::regAsynEvent(actorid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'regAsynEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getGuildSkillAttrs */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getGuildSkillAttrs00
static int tolua_server_LActor_getGuildSkillAttrs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getGuildSkillAttrs(actor,roleId);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getGuildSkillAttrs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getGuildId */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getGuildId00
static int tolua_server_LActor_getGuildId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getGuildId(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getGuildId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getGuildPtr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getGuildPtr00
static int tolua_server_LActor_getGuildPtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LActor::getGuildPtr(actor);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getGuildPtr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getGuildPos */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getGuildPos00
static int tolua_server_LActor_getGuildPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getGuildPos(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getGuildPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getGuildName */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getGuildName00
static int tolua_server_LActor_getGuildName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  LActor::getGuildName(actor);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getGuildName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getTotalGx */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getTotalGx00
static int tolua_server_LActor_getTotalGx00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getTotalGx(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getTotalGx'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::changeTotalGx */
#ifndef TOLUA_DISABLE_tolua_server_LActor_changeTotalGx00
static int tolua_server_LActor_changeTotalGx00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int val = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::changeTotalGx(actor,val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'changeTotalGx'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::saveDb */
#ifndef TOLUA_DISABLE_tolua_server_LActor_saveDb00
static int tolua_server_LActor_saveDb00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actorImage = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::saveDb(actorImage);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'saveDb'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::changeName */
#ifndef TOLUA_DISABLE_tolua_server_LActor_changeName00
static int tolua_server_LActor_changeName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  int way = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::changeName(et,name,way);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'changeName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setEntityName */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setEntityName00
static int tolua_server_LActor_setEntityName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   LActor::setEntityName(et,name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setEntityName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addEffect */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addEffect00
static int tolua_server_LActor_addEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::addEffect(actor,id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getItemData */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getItemData00
static int tolua_server_LActor_getItemData00(lua_State* tolua_S)
{
	return LActor::getItemData(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getItemIdByUid */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getItemIdByUid00
static int tolua_server_LActor_getItemIdByUid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  double uid = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  LActor::getItemIdByUid(actor,uid);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getItemIdByUid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getItemInfoByUid */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getItemInfoByUid00
static int tolua_server_LActor_getItemInfoByUid00(lua_State* tolua_S)
{
	return LActor::getItemInfoByUid(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::costItemByUid */
#ifndef TOLUA_DISABLE_tolua_server_LActor_costItemByUid00
static int tolua_server_LActor_costItemByUid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  double uid = ((double)  tolua_tonumber(tolua_S,2,0));
  int count = ((int)  tolua_tonumber(tolua_S,3,0));
  const char* log = ((const char*)  tolua_tostring(tolua_S,4,0));
  {
   bool tolua_ret = (bool)  LActor::costItemByUid(actor,uid,count,log);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'costItemByUid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setCamp */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setCamp00
static int tolua_server_LActor_setCamp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int camp = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::setCamp(et,camp);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setCamp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getCamp */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getCamp00
static int tolua_server_LActor_getCamp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getCamp(et);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getCamp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setCanChangeCamp */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setCanChangeCamp00
static int tolua_server_LActor_setCanChangeCamp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  bool canChange = ((bool) (tolua_toboolean(tolua_S,2,0)!=0));
  {
   LActor::setCanChangeCamp(et,canChange);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setCanChangeCamp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getLiveByPower */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getLiveByPower00
static int tolua_server_LActor_getLiveByPower00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LActor::getLiveByPower(actor);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getLiveByPower'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getLiveByJob */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getLiveByJob00
static int tolua_server_LActor_getLiveByJob00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LActor::getLiveByJob(actor);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getLiveByJob'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getEquipId */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getEquipId00
static int tolua_server_LActor_getEquipId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* role = ((void*)  tolua_touserdata(tolua_S,1,0));
  short pos = ((short)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  LActor::getEquipId(role,pos);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getEquipId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getEquipQuality */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getEquipQuality00
static int tolua_server_LActor_getEquipQuality00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* role = ((void*)  tolua_touserdata(tolua_S,1,0));
  short pos = ((short)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  LActor::getEquipQuality(role,pos);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getEquipQuality'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getEquipLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getEquipLevel00
static int tolua_server_LActor_getEquipLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* role = ((void*)  tolua_touserdata(tolua_S,1,0));
  short pos = ((short)  tolua_tonumber(tolua_S,2,0));
  int zsLevel = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   int tolua_ret = (int)  LActor::getEquipLevel(role,pos,zsLevel);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushnumber(tolua_S,(lua_Number)zsLevel);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getEquipLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setZhanLingConfig */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setZhanLingConfig00
static int tolua_server_LActor_setZhanLingConfig00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int cd = ((int)  tolua_tonumber(tolua_S,1,0));
  int delay = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::setZhanLingConfig(cd,delay);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setZhanLingConfig'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::initZhanLingInfo */
#ifndef TOLUA_DISABLE_tolua_server_LActor_initZhanLingInfo00
static int tolua_server_LActor_initZhanLingInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  int level = ((int)  tolua_tonumber(tolua_S,3,0));
  int effId = ((int)  tolua_tonumber(tolua_S,4,0));
  int rate = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   LActor::initZhanLingInfo(actor,id,level,effId,rate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'initZhanLingInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setZhanLingId */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setZhanLingId00
static int tolua_server_LActor_setZhanLingId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::setZhanLingId(actor,id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setZhanLingId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addZhanLingEffect */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addZhanLingEffect00
static int tolua_server_LActor_addZhanLingEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  int rate = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::addZhanLingEffect(actor,id,rate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addZhanLingEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getBattlePet */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getBattlePet00
static int tolua_server_LActor_getBattlePet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* role = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LActor::getBattlePet(role);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getBattlePet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setZhuangBan */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setZhuangBan00
static int tolua_server_LActor_setZhuangBan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleindex = ((int)  tolua_tonumber(tolua_S,2,0));
  int pos1id = ((int)  tolua_tonumber(tolua_S,3,0));
  int pos2id = ((int)  tolua_tonumber(tolua_S,4,0));
  int pos3id = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   LActor::setZhuangBan(actor,roleindex,pos1id,pos2id,pos3id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setZhuangBan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getZhuangBan */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getZhuangBan00
static int tolua_server_LActor_getZhuangBan00(lua_State* tolua_S)
{
	return LActor::getZhuangBan(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getRoleZhuangBanAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getRoleZhuangBanAttr00
static int tolua_server_LActor_getRoleZhuangBanAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleindex = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getRoleZhuangBanAttr(actor,roleindex);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRoleZhuangBanAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getMasterHdl */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getMasterHdl00
static int tolua_server_LActor_getMasterHdl00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   double tolua_ret = (double)  LActor::getMasterHdl(et);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getMasterHdl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getMaster */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getMaster00
static int tolua_server_LActor_getMaster00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LActor::getMaster(et);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getMaster'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::KillMonster */
#ifndef TOLUA_DISABLE_tolua_server_LActor_KillMonster00
static int tolua_server_LActor_KillMonster00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double hdl = ((double)  tolua_tonumber(tolua_S,1,0));
  {
   LActor::KillMonster(hdl);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'KillMonster'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::DestroyEntity */
#ifndef TOLUA_DISABLE_tolua_server_LActor_DestroyEntity00
static int tolua_server_LActor_DestroyEntity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  bool delay = ((bool) (tolua_toboolean(tolua_S,2,false)!=0));
  {
   LActor::DestroyEntity(et,delay);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'DestroyEntity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getOffMsg */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getOffMsg00
static int tolua_server_LActor_getOffMsg00(lua_State* tolua_S)
{
	return LActor::getOffMsg(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getOffMsgCnt */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getOffMsgCnt00
static int tolua_server_LActor_getOffMsgCnt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getOffMsgCnt(et);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getOffMsgCnt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getOffMsgIndex */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getOffMsgIndex00
static int tolua_server_LActor_getOffMsgIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  double msg_id = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  LActor::getOffMsgIndex(et,msg_id);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getOffMsgIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::deleteOffMsg */
#ifndef TOLUA_DISABLE_tolua_server_LActor_deleteOffMsg00
static int tolua_server_LActor_deleteOffMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int idx = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  LActor::deleteOffMsg(et,idx);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'deleteOffMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::AddSkill */
#ifndef TOLUA_DISABLE_tolua_server_LActor_AddSkill00
static int tolua_server_LActor_AddSkill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::AddSkill(et,id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'AddSkill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::DelSkill */
#ifndef TOLUA_DISABLE_tolua_server_LActor_DelSkill00
static int tolua_server_LActor_DelSkill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::DelSkill(et,id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'DelSkill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::AddAISkill */
#ifndef TOLUA_DISABLE_tolua_server_LActor_AddAISkill00
static int tolua_server_LActor_AddAISkill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::AddAISkill(et,id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'AddAISkill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::DelAISkill */
#ifndef TOLUA_DISABLE_tolua_server_LActor_DelAISkill00
static int tolua_server_LActor_DelAISkill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::DelAISkill(et,id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'DelAISkill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::DelAllAISkill */
#ifndef TOLUA_DISABLE_tolua_server_LActor_DelAllAISkill00
static int tolua_server_LActor_DelAllAISkill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::DelAllAISkill(et);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'DelAllAISkill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::DelSkillById */
#ifndef TOLUA_DISABLE_tolua_server_LActor_DelSkillById00
static int tolua_server_LActor_DelSkillById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::DelSkillById(et,id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'DelSkillById'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::DelAllSkill */
#ifndef TOLUA_DISABLE_tolua_server_LActor_DelAllSkill00
static int tolua_server_LActor_DelAllSkill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::DelAllSkill(et);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'DelAllSkill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::AddPassiveSkill */
#ifndef TOLUA_DISABLE_tolua_server_LActor_AddPassiveSkill00
static int tolua_server_LActor_AddPassiveSkill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::AddPassiveSkill(et,id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'AddPassiveSkill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::DelPassiveSkill */
#ifndef TOLUA_DISABLE_tolua_server_LActor_DelPassiveSkill00
static int tolua_server_LActor_DelPassiveSkill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::DelPassiveSkill(et,id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'DelPassiveSkill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::DelPassiveSkillById */
#ifndef TOLUA_DISABLE_tolua_server_LActor_DelPassiveSkillById00
static int tolua_server_LActor_DelPassiveSkillById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::DelPassiveSkillById(et,id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'DelPassiveSkillById'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::TogetherHitInfoSync */
#ifndef TOLUA_DISABLE_tolua_server_LActor_TogetherHitInfoSync00
static int tolua_server_LActor_TogetherHitInfoSync00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::TogetherHitInfoSync(actor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'TogetherHitInfoSync'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getFuWenuIdInfo */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getFuWenuIdInfo00
static int tolua_server_LActor_getFuWenuIdInfo00(lua_State* tolua_S)
{
	return LActor::getFuWenuIdInfo(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::CheckFuWenByPost */
#ifndef TOLUA_DISABLE_tolua_server_LActor_CheckFuWenByPost00
static int tolua_server_LActor_CheckFuWenByPost00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int posid = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  LActor::CheckFuWenByPost(et,posid);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'CheckFuWenByPost'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::SetFuwen */
#ifndef TOLUA_DISABLE_tolua_server_LActor_SetFuwen00
static int tolua_server_LActor_SetFuwen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int posid = ((int)  tolua_tonumber(tolua_S,3,0));
  double uid = ((double)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::SetFuwen(et,roleId,posid,uid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'SetFuwen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::FuwenLevelup */
#ifndef TOLUA_DISABLE_tolua_server_LActor_FuwenLevelup00
static int tolua_server_LActor_FuwenLevelup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int posid = ((int)  tolua_tonumber(tolua_S,3,0));
  int itemId = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::FuwenLevelup(et,roleId,posid,itemId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'FuwenLevelup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addFuWenExattr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addFuWenExattr00
static int tolua_server_LActor_addFuWenExattr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleid = ((int)  tolua_tonumber(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,0));
  int value = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::addFuWenExattr(et,roleid,type,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addFuWenExattr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::CalcExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_CalcExAttr00
static int tolua_server_LActor_CalcExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleid = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::CalcExAttr(et,roleid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'CalcExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::clearFuWenAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_clearFuWenAttr00
static int tolua_server_LActor_clearFuWenAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::clearFuWenAttr(et,roleId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'clearFuWenAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addFuWenAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addFuWenAttr00
static int tolua_server_LActor_addFuWenAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,0));
  int value = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::addFuWenAttr(et,roleId,type,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addFuWenAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getFuWenAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getFuWenAttr00
static int tolua_server_LActor_getFuWenAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getFuWenAttr(et,roleId);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getFuWenAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addImbaExattr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addImbaExattr00
static int tolua_server_LActor_addImbaExattr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  int value = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::addImbaExattr(et,type,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addImbaExattr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::clearImbaAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_clearImbaAttr00
static int tolua_server_LActor_clearImbaAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::clearImbaAttr(et);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'clearImbaAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addImbaAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addImbaAttr00
static int tolua_server_LActor_addImbaAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  int value = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::addImbaAttr(et,type,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addImbaAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getImbaAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getImbaAttr00
static int tolua_server_LActor_getImbaAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getImbaAttr(et);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getImbaAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getPosition */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getPosition00
static int tolua_server_LActor_getPosition00(lua_State* tolua_S)
{
	return LActor::getPosition(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getOriginPosition */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getOriginPosition00
static int tolua_server_LActor_getOriginPosition00(lua_State* tolua_S)
{
	return LActor::getOriginPosition(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getDropBagData */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getDropBagData00
static int tolua_server_LActor_getDropBagData00(lua_State* tolua_S)
{
	return LActor::getDropBagData(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::SetInvincible */
#ifndef TOLUA_DISABLE_tolua_server_LActor_SetInvincible00
static int tolua_server_LActor_SetInvincible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  bool res = ((bool) (tolua_toboolean(tolua_S,2,0)!=0));
  {
   LActor::SetInvincible(et,res);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'SetInvincible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getActorByEt */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getActorByEt00
static int tolua_server_LActor_getActorByEt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LActor::getActorByEt(et);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorByEt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::clearImbaActId */
#ifndef TOLUA_DISABLE_tolua_server_LActor_clearImbaActId00
static int tolua_server_LActor_clearImbaActId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::clearImbaActId(actor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'clearImbaActId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addImbaActId */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addImbaActId00
static int tolua_server_LActor_addImbaActId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::addImbaActId(actor,id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addImbaActId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::clearGodWeaponActId */
#ifndef TOLUA_DISABLE_tolua_server_LActor_clearGodWeaponActId00
static int tolua_server_LActor_clearGodWeaponActId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::clearGodWeaponActId(actor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'clearGodWeaponActId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addGodWeaponActId */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addGodWeaponActId00
static int tolua_server_LActor_addGodWeaponActId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int idx = ((int)  tolua_tonumber(tolua_S,2,0));
  int id = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::addGodWeaponActId(actor,idx,id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addGodWeaponActId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setGodWeaponPeak */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setGodWeaponPeak00
static int tolua_server_LActor_setGodWeaponPeak00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int peak = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::setGodWeaponPeak(actor,peak);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setGodWeaponPeak'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setGodWeaponLevel */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setGodWeaponLevel00
static int tolua_server_LActor_setGodWeaponLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int level = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::setGodWeaponLevel(actor,level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setGodWeaponLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setGodWeaponPower */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setGodWeaponPower00
static int tolua_server_LActor_setGodWeaponPower00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int job = ((int)  tolua_tonumber(tolua_S,2,0));
  int power = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::setGodWeaponPower(actor,job,power);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setGodWeaponPower'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::clearGodWeaponPower */
#ifndef TOLUA_DISABLE_tolua_server_LActor_clearGodWeaponPower00
static int tolua_server_LActor_clearGodWeaponPower00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::clearGodWeaponPower(actor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'clearGodWeaponPower'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getHeirloomLv */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getHeirloomLv00
static int tolua_server_LActor_getHeirloomLv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int slot = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   int tolua_ret = (int)  LActor::getHeirloomLv(actor,roleId,slot);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getHeirloomLv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setHeirloomLv */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setHeirloomLv00
static int tolua_server_LActor_setHeirloomLv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int slot = ((int)  tolua_tonumber(tolua_S,3,0));
  int lv = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LActor::setHeirloomLv(actor,roleId,slot,lv);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setHeirloomLv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetHeirloomAttrs */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetHeirloomAttrs00
static int tolua_server_LActor_GetHeirloomAttrs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int role_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::GetHeirloomAttrs(actor,role_id);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetHeirloomAttrs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetWeaponSoulAttrs */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetWeaponSoulAttrs00
static int tolua_server_LActor_GetWeaponSoulAttrs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int role_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::GetWeaponSoulAttrs(actor,role_id);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetWeaponSoulAttrs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetWeaponSoulExAttrs */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetWeaponSoulExAttrs00
static int tolua_server_LActor_GetWeaponSoulExAttrs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int role_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::GetWeaponSoulExAttrs(actor,role_id);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetWeaponSoulExAttrs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetGodWingAttrs */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetGodWingAttrs00
static int tolua_server_LActor_GetGodWingAttrs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int role_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::GetGodWingAttrs(actor,role_id);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetGodWingAttrs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetCampBattleAttrs */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetCampBattleAttrs00
static int tolua_server_LActor_GetCampBattleAttrs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int role_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::GetCampBattleAttrs(actor,role_id);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetCampBattleAttrs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetReincarnateEquipAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetReincarnateEquipAttr00
static int tolua_server_LActor_GetReincarnateEquipAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int role_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::GetReincarnateEquipAttr(actor,role_id);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetReincarnateEquipAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetReincarnateEquipExAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetReincarnateEquipExAttr00
static int tolua_server_LActor_GetReincarnateEquipExAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int role_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::GetReincarnateEquipExAttr(actor,role_id);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetReincarnateEquipExAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetGodWingExAttrs */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetGodWingExAttrs00
static int tolua_server_LActor_GetGodWingExAttrs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int role_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::GetGodWingExAttrs(actor,role_id);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetGodWingExAttrs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetWingExAttrs */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetWingExAttrs00
static int tolua_server_LActor_GetWingExAttrs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int role_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  LActor::GetWingExAttrs(actor,role_id);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetWingExAttrs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getUseingWeaponSoulId */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getUseingWeaponSoulId00
static int tolua_server_LActor_getUseingWeaponSoulId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int role_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  LActor::getUseingWeaponSoulId(actor,role_id);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getUseingWeaponSoulId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::setUseingWeaponSoulId */
#ifndef TOLUA_DISABLE_tolua_server_LActor_setUseingWeaponSoulId00
static int tolua_server_LActor_setUseingWeaponSoulId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int role_id = ((int)  tolua_tonumber(tolua_S,2,0));
  int id = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::setUseingWeaponSoulId(actor,role_id,id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setUseingWeaponSoulId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::TuJianPower */
#ifndef TOLUA_DISABLE_tolua_server_LActor_TuJianPower00
static int tolua_server_LActor_TuJianPower00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::TuJianPower(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'TuJianPower'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getEquipBasePower */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getEquipBasePower00
static int tolua_server_LActor_getEquipBasePower00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getEquipBasePower(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getEquipBasePower'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::hasJobRole */
#ifndef TOLUA_DISABLE_tolua_server_LActor_hasJobRole00
static int tolua_server_LActor_hasJobRole00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int job = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  LActor::hasJobRole(actor,job);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'hasJobRole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::SetTogeLv */
#ifndef TOLUA_DISABLE_tolua_server_LActor_SetTogeLv00
static int tolua_server_LActor_SetTogeLv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int lv = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::SetTogeLv(actor,lv);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'SetTogeLv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::SetYuPeiLv */
#ifndef TOLUA_DISABLE_tolua_server_LActor_SetYuPeiLv00
static int tolua_server_LActor_SetYuPeiLv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int lv = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::SetYuPeiLv(actor,lv);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'SetYuPeiLv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::InSafeArea */
#ifndef TOLUA_DISABLE_tolua_server_LActor_InSafeArea00
static int tolua_server_LActor_InSafeArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  LActor::InSafeArea(actor);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'InSafeArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::stopAI */
#ifndef TOLUA_DISABLE_tolua_server_LActor_stopAI00
static int tolua_server_LActor_stopAI00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::stopAI(actor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'stopAI'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getSceneAreaIParm */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getSceneAreaIParm00
static int tolua_server_LActor_getSceneAreaIParm00(lua_State* tolua_S)
{
	return LActor::getSceneAreaIParm(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::RequestFubenPathLine */
#ifndef TOLUA_DISABLE_tolua_server_LActor_RequestFubenPathLine00
static int tolua_server_LActor_RequestFubenPathLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* role = ((void*)  tolua_touserdata(tolua_S,1,0));
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::RequestFubenPathLine(role,x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'RequestFubenPathLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::MonsterFubenPathLine */
#ifndef TOLUA_DISABLE_tolua_server_LActor_MonsterFubenPathLine00
static int tolua_server_LActor_MonsterFubenPathLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* role = ((void*)  tolua_touserdata(tolua_S,1,0));
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::MonsterFubenPathLine(role,x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'MonsterFubenPathLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getSceneId */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getSceneId00
static int tolua_server_LActor_getSceneId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::getSceneId(actor);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getSceneId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::clearAttrs */
#ifndef TOLUA_DISABLE_tolua_server_LActor_clearAttrs00
static int tolua_server_LActor_clearAttrs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int attrSysId = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  LActor::clearAttrs(actor,roleId,attrSysId);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'clearAttrs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addAttrsBaseAttr */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addAttrsBaseAttr00
static int tolua_server_LActor_addAttrsBaseAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int attrSysId = ((int)  tolua_tonumber(tolua_S,3,0));
  int type = ((int)  tolua_tonumber(tolua_S,4,0));
  int value = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   bool tolua_ret = (bool)  LActor::addAttrsBaseAttr(actor,roleId,attrSysId,type,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addAttrsBaseAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::addAttrsExaPower */
#ifndef TOLUA_DISABLE_tolua_server_LActor_addAttrsExaPower00
static int tolua_server_LActor_addAttrsExaPower00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int attrSysId = ((int)  tolua_tonumber(tolua_S,3,0));
  int power = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   bool tolua_ret = (bool)  LActor::addAttrsExaPower(actor,roleId,attrSysId,power);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addAttrsExaPower'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::getAttrs */
#ifndef TOLUA_DISABLE_tolua_server_LActor_getAttrs00
static int tolua_server_LActor_getAttrs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int roleId = ((int)  tolua_tonumber(tolua_S,2,0));
  int asid = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   Attribute* tolua_ret = (Attribute*)  LActor::getAttrs(actor,roleId,asid);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getAttrs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::AddSkillRevise */
#ifndef TOLUA_DISABLE_tolua_server_LActor_AddSkillRevise00
static int tolua_server_LActor_AddSkillRevise00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int skillId = ((int)  tolua_tonumber(tolua_S,2,0));
  int cd = ((int)  tolua_tonumber(tolua_S,3,0));
  double a = ((double)  tolua_tonumber(tolua_S,4,0));
  int b = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   LActor::AddSkillRevise(et,skillId,cd,a,b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'AddSkillRevise'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::AddSkillReviseSelfBuff */
#ifndef TOLUA_DISABLE_tolua_server_LActor_AddSkillReviseSelfBuff00
static int tolua_server_LActor_AddSkillReviseSelfBuff00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int skillId = ((int)  tolua_tonumber(tolua_S,2,0));
  int buffId = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::AddSkillReviseSelfBuff(et,skillId,buffId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'AddSkillReviseSelfBuff'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::AddSkillReviseTarBuff */
#ifndef TOLUA_DISABLE_tolua_server_LActor_AddSkillReviseTarBuff00
static int tolua_server_LActor_AddSkillReviseTarBuff00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int skillId = ((int)  tolua_tonumber(tolua_S,2,0));
  int buffId = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::AddSkillReviseTarBuff(et,skillId,buffId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'AddSkillReviseTarBuff'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::SetFlameStampLv */
#ifndef TOLUA_DISABLE_tolua_server_LActor_SetFlameStampLv00
static int tolua_server_LActor_SetFlameStampLv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int level = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::SetFlameStampLv(actor,level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'SetFlameStampLv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::SetFlameStampSkillLv */
#ifndef TOLUA_DISABLE_tolua_server_LActor_SetFlameStampSkillLv00
static int tolua_server_LActor_SetFlameStampSkillLv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int skillId = ((int)  tolua_tonumber(tolua_S,2,0));
  int level = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::SetFlameStampSkillLv(actor,skillId,level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'SetFlameStampSkillLv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::SetSkillCdById */
#ifndef TOLUA_DISABLE_tolua_server_LActor_SetSkillCdById00
static int tolua_server_LActor_SetSkillCdById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int skillId = ((int)  tolua_tonumber(tolua_S,2,0));
  int cd_time = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::SetSkillCdById(et,skillId,cd_time);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'SetSkillCdById'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::CIsEquip */
#ifndef TOLUA_DISABLE_tolua_server_LActor_CIsEquip00
static int tolua_server_LActor_CIsEquip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int equipID = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  LActor::CIsEquip(equipID);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'CIsEquip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::AddPVMRecord */
#ifndef TOLUA_DISABLE_tolua_server_LActor_AddPVMRecord00
static int tolua_server_LActor_AddPVMRecord00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actorid = ((int)  tolua_tonumber(tolua_S,1,0));
  int targetid = ((int)  tolua_tonumber(tolua_S,2,0));
  int result = ((int)  tolua_tonumber(tolua_S,3,0));
  int changerank = ((int)  tolua_tonumber(tolua_S,4,0));
  int targetrank = ((int)  tolua_tonumber(tolua_S,5,0));
  int recordtime = ((int)  tolua_tonumber(tolua_S,6,0));
  {
   LActor::AddPVMRecord(actorid,targetid,result,changerank,targetrank,recordtime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'AddPVMRecord'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::UpdataRank */
#ifndef TOLUA_DISABLE_tolua_server_LActor_UpdataRank00
static int tolua_server_LActor_UpdataRank00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actorid = ((int)  tolua_tonumber(tolua_S,1,0));
  int newrank = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LActor::UpdataRank(actorid,newrank);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'UpdataRank'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::SendPVMRank */
#ifndef TOLUA_DISABLE_tolua_server_LActor_SendPVMRank00
static int tolua_server_LActor_SendPVMRank00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  int Limit = ((int)  tolua_tonumber(tolua_S,2,0));
  int flag = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LActor::SendPVMRank(actor,Limit,flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'SendPVMRank'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::SendPVMRecord */
#ifndef TOLUA_DISABLE_tolua_server_LActor_SendPVMRecord00
static int tolua_server_LActor_SendPVMRecord00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* actor = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LActor::SendPVMRecord(actor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'SendPVMRecord'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::InitMaxRecordCount */
#ifndef TOLUA_DISABLE_tolua_server_LActor_InitMaxRecordCount00
static int tolua_server_LActor_InitMaxRecordCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int max_count = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   LActor::InitMaxRecordCount(max_count);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'InitMaxRecordCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetPlayerIDByPVMRank */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetPlayerIDByPVMRank00
static int tolua_server_LActor_GetPlayerIDByPVMRank00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int irank = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::GetPlayerIDByPVMRank(irank);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetPlayerIDByPVMRank'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetPVMRankByPlayerID */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetPVMRankByPlayerID00
static int tolua_server_LActor_GetPVMRankByPlayerID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actorid = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  LActor::GetPVMRankByPlayerID(actorid);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetPVMRankByPlayerID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::GetPVMRankSize */
#ifndef TOLUA_DISABLE_tolua_server_LActor_GetPVMRankSize00
static int tolua_server_LActor_GetPVMRankSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  LActor::GetPVMRankSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetPVMRankSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LActor::UpdataPvmRankOldData */
#ifndef TOLUA_DISABLE_tolua_server_LActor_UpdataPvmRankOldData00
static int tolua_server_LActor_UpdataPvmRankOldData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LActor::UpdataPvmRankOldData();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'UpdataPvmRankOldData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::createFuBen */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_createFuBen00
static int tolua_server_Fuben_createFuBen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int nFbID = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   unsigned int tolua_ret = (unsigned int)  Fuben::createFuBen(nFbID);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'createFuBen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::closeFuben */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_closeFuben00
static int tolua_server_Fuben_closeFuben00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int hFuben = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  {
   Fuben::closeFuben(hFuben);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'closeFuben'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::setEnd */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_setEnd00
static int tolua_server_Fuben_setEnd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int hFuben = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  {
   Fuben::setEnd(hFuben);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setEnd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::setBelong */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_setBelong00
static int tolua_server_Fuben_setBelong00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int hFuben = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  {
   Fuben::setBelong(hFuben);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setBelong'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::setIsNeedAi */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_setIsNeedAi00
static int tolua_server_Fuben_setIsNeedAi00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int hFuben = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  bool canRun = ((bool) (tolua_toboolean(tolua_S,2,0)!=0));
  {
   Fuben::setIsNeedAi(hFuben,canRun);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setIsNeedAi'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::getFubenHandle */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_getFubenHandle00
static int tolua_server_Fuben_getFubenHandle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pFuben = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   unsigned int tolua_ret = (unsigned int)  Fuben::getFubenHandle(pFuben);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getFubenHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::getFubenPtr */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_getFubenPtr00
static int tolua_server_Fuben_getFubenPtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int hFuben = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  Fuben::getFubenPtr(hFuben);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getFubenPtr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::getStaticFubenHandle */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_getStaticFubenHandle00
static int tolua_server_Fuben_getStaticFubenHandle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   unsigned int tolua_ret = (unsigned int)  Fuben::getStaticFubenHandle();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getStaticFubenHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::createMonster */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_createMonster00
static int tolua_server_Fuben_createMonster00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isuserdata(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int hScene = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  unsigned int nMonsterid = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  int posX = ((int)  tolua_tonumber(tolua_S,3,0));
  int posY = ((int)  tolua_tonumber(tolua_S,4,0));
  unsigned int nLiveTime = ((unsigned int)  tolua_tonumber(tolua_S,5,0));
  void* met = ((void*)  tolua_touserdata(tolua_S,6,0));
  {
   void* tolua_ret = (void*)  Fuben::createMonster(hScene,nMonsterid,posX,posY,nLiveTime,met);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'createMonster'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::createDropBag */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_createDropBag00
static int tolua_server_Fuben_createDropBag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int hScene = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  int id = ((int)  tolua_tonumber(tolua_S,3,0));
  int count = ((int)  tolua_tonumber(tolua_S,4,0));
  int x = ((int)  tolua_tonumber(tolua_S,5,0));
  int y = ((int)  tolua_tonumber(tolua_S,6,0));
  int belong_id = ((int)  tolua_tonumber(tolua_S,7,0));
  {
   void* tolua_ret = (void*)  Fuben::createDropBag(hScene,type,id,count,x,y,belong_id);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'createDropBag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::RewardDropBag */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_RewardDropBag00
static int tolua_server_Fuben_RewardDropBag00(lua_State* tolua_S)
{
	return Fuben::RewardDropBag(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::sendData */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_sendData00
static int tolua_server_Fuben_sendData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int hdl = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  void* dp = ((void*)  tolua_touserdata(tolua_S,2,0));
  {
   Fuben::sendData(hdl,dp);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'sendData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::sendDataNoActor */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_sendDataNoActor00
static int tolua_server_Fuben_sendDataNoActor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int hdl = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  void* dp = ((void*)  tolua_touserdata(tolua_S,2,0));
  void* actor = ((void*)  tolua_touserdata(tolua_S,3,0));
  {
   Fuben::sendDataNoActor(hdl,dp,actor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'sendDataNoActor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::getAllActor */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_getAllActor00
static int tolua_server_Fuben_getAllActor00(lua_State* tolua_S)
{
	return Fuben::getAllActor(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::getAllMonster */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_getAllMonster00
static int tolua_server_Fuben_getAllMonster00(lua_State* tolua_S)
{
	return Fuben::getAllMonster(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::getAllDropBag */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_getAllDropBag00
static int tolua_server_Fuben_getAllDropBag00(lua_State* tolua_S)
{
	return Fuben::getAllDropBag(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::getAllCloneRole */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_getAllCloneRole00
static int tolua_server_Fuben_getAllCloneRole00(lua_State* tolua_S)
{
	return Fuben::getAllCloneRole(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::getActorCount */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_getActorCount00
static int tolua_server_Fuben_getActorCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int hdl = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  Fuben::getActorCount(hdl);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::GetResActorMirrorCount */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_GetResActorMirrorCount00
static int tolua_server_Fuben_GetResActorMirrorCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int hdl = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  Fuben::GetResActorMirrorCount(hdl);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetResActorMirrorCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::getCloneRole */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_getCloneRole00
static int tolua_server_Fuben_getCloneRole00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int hdl = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  int ActorID = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   void* tolua_ret = (void*)  Fuben::getCloneRole(hdl,ActorID);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getCloneRole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::releaseInstance */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_releaseInstance00
static int tolua_server_Fuben_releaseInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* fb = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Fuben::releaseInstance(fb);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'releaseInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::getMonsterId */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_getMonsterId00
static int tolua_server_Fuben_getMonsterId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* mon = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  Fuben::getMonsterId(mon);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getMonsterId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::isKillAllMonster */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_isKillAllMonster00
static int tolua_server_Fuben_isKillAllMonster00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int hScene = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  int monId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  Fuben::isKillAllMonster(hScene,monId);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'isKillAllMonster'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::killAllMonster */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_killAllMonster00
static int tolua_server_Fuben_killAllMonster00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int hScene = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  {
   Fuben::killAllMonster(hScene);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'killAllMonster'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::clearAllMonster */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_clearAllMonster00
static int tolua_server_Fuben_clearAllMonster00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int hScene = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  {
   Fuben::clearAllMonster(hScene);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'clearAllMonster'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::clearAllCloneRole */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_clearAllCloneRole00
static int tolua_server_Fuben_clearAllCloneRole00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int hScene = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  {
   Fuben::clearAllCloneRole(hScene);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'clearAllCloneRole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::clearCloneRoleById */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_clearCloneRoleById00
static int tolua_server_Fuben_clearCloneRoleById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int hScene = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  int actor_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Fuben::clearCloneRoleById(hScene,actor_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'clearCloneRoleById'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::getMonsterMaxHp */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_getMonsterMaxHp00
static int tolua_server_Fuben_getMonsterMaxHp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int id = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   double tolua_ret = (double)  Fuben::getMonsterMaxHp(id);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getMonsterMaxHp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::setMonsterCamp */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_setMonsterCamp00
static int tolua_server_Fuben_setMonsterCamp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* mon = ((void*)  tolua_touserdata(tolua_S,1,0));
  int camp = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Fuben::setMonsterCamp(mon,camp);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setMonsterCamp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::setBaseAttr */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_setBaseAttr00
static int tolua_server_Fuben_setBaseAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* mon = ((void*)  tolua_touserdata(tolua_S,1,0));
  float rate = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   Fuben::setBaseAttr(mon,rate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setBaseAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::getSceneMonsterById */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_getSceneMonsterById00
static int tolua_server_Fuben_getSceneMonsterById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pScene = ((void*)  tolua_touserdata(tolua_S,1,0));
  int targetId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   void* tolua_ret = (void*)  Fuben::getSceneMonsterById(pScene,targetId);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getSceneMonsterById'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::Getscenelist */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_Getscenelist00
static int tolua_server_Fuben_Getscenelist00(lua_State* tolua_S)
{
	return Fuben::Getscenelist(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Fuben::getSceneHandlebyPtr */
#ifndef TOLUA_DISABLE_tolua_server_Fuben_getSceneHandlebyPtr00
static int tolua_server_Fuben_getSceneHandlebyPtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pScene = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   unsigned int tolua_ret = (unsigned int)  Fuben::getSceneHandlebyPtr(pScene);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getSceneHandlebyPtr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: print */
#ifndef TOLUA_DISABLE_tolua_server_print00
static int tolua_server_print00(lua_State* tolua_S)
{
	return print(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::version */
#ifndef TOLUA_DISABLE_tolua_server_System_version00
static int tolua_server_System_version00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  System::version();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'version'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::reloadGlobalNpc */
#ifndef TOLUA_DISABLE_tolua_server_System_reloadGlobalNpc00
static int tolua_server_System_reloadGlobalNpc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  System::reloadGlobalNpc(et,type);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'reloadGlobalNpc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getServerName */
#ifndef TOLUA_DISABLE_tolua_server_System_getServerName00
static int tolua_server_System_getServerName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   char* tolua_ret = (char*)  System::getServerName();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getServerName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getServerId */
#ifndef TOLUA_DISABLE_tolua_server_System_getServerId00
static int tolua_server_System_getServerId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  System::getServerId();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getServerId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getWebServer */
#ifndef TOLUA_DISABLE_tolua_server_System_getWebServer00
static int tolua_server_System_getWebServer00(lua_State* tolua_S)
{
	return System::getWebServer(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::isServerStarted */
#ifndef TOLUA_DISABLE_tolua_server_System_isServerStarted00
static int tolua_server_System_isServerStarted00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  System::isServerStarted();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'isServerStarted'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getDate */
#ifndef TOLUA_DISABLE_tolua_server_System_getDate00
static int tolua_server_System_getDate00(lua_State* tolua_S)
{
	return System::getDate(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getTime */
#ifndef TOLUA_DISABLE_tolua_server_System_getTime00
static int tolua_server_System_getTime00(lua_State* tolua_S)
{
	return System::getTime(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getUnixTime */
#ifndef TOLUA_DISABLE_tolua_server_System_getUnixTime00
static int tolua_server_System_getUnixTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   const char* tolua_ret = (const char*)  System::getUnixTime();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getUnixTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getTick */
#ifndef TOLUA_DISABLE_tolua_server_System_getTick00
static int tolua_server_System_getTick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   unsigned long long tolua_ret = (unsigned long long)  System::getTick();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getTick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getDayOfWeek */
#ifndef TOLUA_DISABLE_tolua_server_System_getDayOfWeek00
static int tolua_server_System_getDayOfWeek00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  System::getDayOfWeek();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getDayOfWeek'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getRandomNumber */
#ifndef TOLUA_DISABLE_tolua_server_System_getRandomNumber00
static int tolua_server_System_getRandomNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int nModule = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   unsigned int tolua_ret = (unsigned int)  System::getRandomNumber(nModule);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRandomNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getNowTime */
#ifndef TOLUA_DISABLE_tolua_server_System_getNowTime00
static int tolua_server_System_getNowTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   unsigned int tolua_ret = (unsigned int)  System::getNowTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getNowTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::encodeTime */
#ifndef TOLUA_DISABLE_tolua_server_System_encodeTime00
static int tolua_server_System_encodeTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int systime = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   unsigned int tolua_ret = (unsigned int)  System::encodeTime(systime);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'encodeTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getDiffendTime */
#ifndef TOLUA_DISABLE_tolua_server_System_getDiffendTime00
static int tolua_server_System_getDiffendTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int nHour = ((int)  tolua_tonumber(tolua_S,1,0));
  int nMinute = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   unsigned int tolua_ret = (unsigned int)  System::getDiffendTime(nHour,nMinute);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getDiffendTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getWeekDataTime */
#ifndef TOLUA_DISABLE_tolua_server_System_getWeekDataTime00
static int tolua_server_System_getWeekDataTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int y = ((int)  tolua_tonumber(tolua_S,1,0));
  int m = ((int)  tolua_tonumber(tolua_S,2,0));
  int d = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   unsigned int tolua_ret = (unsigned int)  System::getWeekDataTime(y,m,d);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getWeekDataTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::isSameWeek */
#ifndef TOLUA_DISABLE_tolua_server_System_isSameWeek00
static int tolua_server_System_isSameWeek00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int t1 = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  unsigned int t2 = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  System::isSameWeek(t1,t2);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'isSameWeek'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::trace */
#ifndef TOLUA_DISABLE_tolua_server_System_trace00
static int tolua_server_System_trace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* str = ((char*)  tolua_tostring(tolua_S,1,0));
  {
   System::trace(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'trace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::deepCreateDirectory */
#ifndef TOLUA_DISABLE_tolua_server_System_deepCreateDirectory00
static int tolua_server_System_deepCreateDirectory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* sDirName = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  System::deepCreateDirectory(sDirName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'deepCreateDirectory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::fileExists */
#ifndef TOLUA_DISABLE_tolua_server_System_fileExists00
static int tolua_server_System_fileExists00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* sFilePath = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  System::fileExists(sFilePath);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'fileExists'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getActorPtr */
#ifndef TOLUA_DISABLE_tolua_server_System_getActorPtr00
static int tolua_server_System_getActorPtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* sName = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  System::getActorPtr(sName);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorPtr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::broadcastTipmsg */
#ifndef TOLUA_DISABLE_tolua_server_System_broadcastTipmsg00
static int tolua_server_System_broadcastTipmsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* sTipmsg = ((const char*)  tolua_tostring(tolua_S,1,0));
  int nTipmsgType = ((int)  tolua_tonumber(tolua_S,2,ttTipmsgWindow));
  {
   System::broadcastTipmsg(sTipmsg,nTipmsgType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'broadcastTipmsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::broadcastLevelTipmsg */
#ifndef TOLUA_DISABLE_tolua_server_System_broadcastLevelTipmsg00
static int tolua_server_System_broadcastLevelTipmsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* sTipmsg = ((const char*)  tolua_tostring(tolua_S,1,0));
  int level = ((int)  tolua_tonumber(tolua_S,2,0));
  int nTipmsgType = ((int)  tolua_tonumber(tolua_S,3,ttTipmsgWindow));
  {
   System::broadcastLevelTipmsg(sTipmsg,level,nTipmsgType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'broadcastLevelTipmsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::broadcastTipmsgWithID */
#ifndef TOLUA_DISABLE_tolua_server_System_broadcastTipmsgWithID00
static int tolua_server_System_broadcastTipmsgWithID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int nTipmsgID = ((int)  tolua_tonumber(tolua_S,1,0));
  int nTipmsgType = ((int)  tolua_tonumber(tolua_S,2,ttTipmsgWindow));
  {
   System::broadcastTipmsgWithID(nTipmsgID,nTipmsgType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'broadcastTipmsgWithID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::broadcastData */
#ifndef TOLUA_DISABLE_tolua_server_System_broadcastData00
static int tolua_server_System_broadcastData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* dp = ((void*)  tolua_touserdata(tolua_S,1,0));
  bool isOffset = ((bool) (tolua_toboolean(tolua_S,2,false)!=0));
  {
   System::broadcastData(dp,isOffset);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'broadcastData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getEntityByPtr */
#ifndef TOLUA_DISABLE_tolua_server_System_getEntityByPtr00
static int tolua_server_System_getEntityByPtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pEntity = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  System::getEntityByPtr(pEntity);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getEntityByPtr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getAllActorList */
#ifndef TOLUA_DISABLE_tolua_server_System_getAllActorList00
static int tolua_server_System_getAllActorList00(lua_State* tolua_S)
{
	return System::getAllActorList(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getEntityTypeByHandle */
#ifndef TOLUA_DISABLE_tolua_server_System_getEntityTypeByHandle00
static int tolua_server_System_getEntityTypeByHandle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double entityHandle = ((double)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  System::getEntityTypeByHandle(entityHandle);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getEntityTypeByHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getEntityPtrByActorID */
#ifndef TOLUA_DISABLE_tolua_server_System_getEntityPtrByActorID00
static int tolua_server_System_getEntityPtrByActorID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int nActorID = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  System::getEntityPtrByActorID(nActorID);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getEntityPtrByActorID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::isInTimeRange */
#ifndef TOLUA_DISABLE_tolua_server_System_isInTimeRange00
static int tolua_server_System_isInTimeRange00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int nStartHour = ((int)  tolua_tonumber(tolua_S,1,0));
  int nStartMin = ((int)  tolua_tonumber(tolua_S,2,0));
  int nStartSec = ((int)  tolua_tonumber(tolua_S,3,0));
  int nEndHour = ((int)  tolua_tonumber(tolua_S,4,0));
  int nEndMin = ((int)  tolua_tonumber(tolua_S,5,0));
  int nEndSec = ((int)  tolua_tonumber(tolua_S,6,0));
  {
   bool tolua_ret = (bool)  System::isInTimeRange(nStartHour,nStartMin,nStartSec,nEndHour,nEndMin,nEndSec);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'isInTimeRange'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getToday */
#ifndef TOLUA_DISABLE_tolua_server_System_getToday00
static int tolua_server_System_getToday00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   unsigned int tolua_ret = (unsigned int)  System::getToday();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getToday'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getYesterday */
#ifndef TOLUA_DISABLE_tolua_server_System_getYesterday00
static int tolua_server_System_getYesterday00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   unsigned int tolua_ret = (unsigned int)  System::getYesterday();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getYesterday'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getGlobalNpc */
#ifndef TOLUA_DISABLE_tolua_server_System_getGlobalNpc00
static int tolua_server_System_getGlobalNpc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   void* tolua_ret = (void*)  System::getGlobalNpc();
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getGlobalNpc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getReserveNpc */
#ifndef TOLUA_DISABLE_tolua_server_System_getReserveNpc00
static int tolua_server_System_getReserveNpc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   void* tolua_ret = (void*)  System::getReserveNpc();
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getReserveNpc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getStaticVar */
#ifndef TOLUA_DISABLE_tolua_server_System_getStaticVar00
static int tolua_server_System_getStaticVar00(lua_State* tolua_S)
{
	return System::getStaticVar(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getSystemDef */
#ifndef TOLUA_DISABLE_tolua_server_System_getSystemDef00
static int tolua_server_System_getSystemDef00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  System::getSystemDef(name);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getSystemDef'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getServerOpenTime */
#ifndef TOLUA_DISABLE_tolua_server_System_getServerOpenTime00
static int tolua_server_System_getServerOpenTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   unsigned int tolua_ret = (unsigned int)  System::getServerOpenTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getServerOpenTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::isSameDay */
#ifndef TOLUA_DISABLE_tolua_server_System_isSameDay00
static int tolua_server_System_isSameDay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int t1 = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  unsigned int t2 = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  System::isSameDay(t1,t2);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'isSameDay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::setEntityShowName */
#ifndef TOLUA_DISABLE_tolua_server_System_setEntityShowName00
static int tolua_server_System_setEntityShowName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   System::setEntityShowName(et,name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setEntityShowName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getOpenServerDay */
#ifndef TOLUA_DISABLE_tolua_server_System_getOpenServerDay00
static int tolua_server_System_getOpenServerDay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  System::getOpenServerDay();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getOpenServerDay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getTimeToNowDay */
#ifndef TOLUA_DISABLE_tolua_server_System_getTimeToNowDay00
static int tolua_server_System_getTimeToNowDay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int optime = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  System::getTimeToNowDay(optime);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getTimeToNowDay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getOpenServerStartDateTime */
#ifndef TOLUA_DISABLE_tolua_server_System_getOpenServerStartDateTime00
static int tolua_server_System_getOpenServerStartDateTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  System::getOpenServerStartDateTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getOpenServerStartDateTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getOpenServerTime */
#ifndef TOLUA_DISABLE_tolua_server_System_getOpenServerTime00
static int tolua_server_System_getOpenServerTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   unsigned int tolua_ret = (unsigned int)  System::getOpenServerTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getOpenServerTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::setOpenServerTime */
#ifndef TOLUA_DISABLE_tolua_server_System_setOpenServerTime00
static int tolua_server_System_setOpenServerTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int year = ((int)  tolua_tonumber(tolua_S,1,0));
  int mon = ((int)  tolua_tonumber(tolua_S,2,0));
  int day = ((int)  tolua_tonumber(tolua_S,3,0));
  int hour = ((int)  tolua_tonumber(tolua_S,4,0));
  int m = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   System::setOpenServerTime(year,mon,day,hour,m);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setOpenServerTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getRestTimeFromOpenServer */
#ifndef TOLUA_DISABLE_tolua_server_System_getRestTimeFromOpenServer00
static int tolua_server_System_getRestTimeFromOpenServer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int day = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  System::getRestTimeFromOpenServer(day);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRestTimeFromOpenServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::bitOPMask */
#ifndef TOLUA_DISABLE_tolua_server_System_bitOPMask00
static int tolua_server_System_bitOPMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int val = ((int)  tolua_tonumber(tolua_S,1,0));
  int idx = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  System::bitOPMask(val,idx);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'bitOPMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::bitOpNot */
#ifndef TOLUA_DISABLE_tolua_server_System_bitOpNot00
static int tolua_server_System_bitOpNot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int val = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  System::bitOpNot(val);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'bitOpNot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::bitOpAnd */
#ifndef TOLUA_DISABLE_tolua_server_System_bitOpAnd00
static int tolua_server_System_bitOpAnd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int val1 = ((int)  tolua_tonumber(tolua_S,1,0));
  int val2 = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  System::bitOpAnd(val1,val2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'bitOpAnd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::bitOpOr */
#ifndef TOLUA_DISABLE_tolua_server_System_bitOpOr00
static int tolua_server_System_bitOpOr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int val1 = ((int)  tolua_tonumber(tolua_S,1,0));
  int val2 = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  System::bitOpOr(val1,val2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'bitOpOr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::bitOpRig */
#ifndef TOLUA_DISABLE_tolua_server_System_bitOpRig00
static int tolua_server_System_bitOpRig00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int val = ((int)  tolua_tonumber(tolua_S,1,0));
  int cnt = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  System::bitOpRig(val,cnt);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'bitOpRig'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::bitOpLeft */
#ifndef TOLUA_DISABLE_tolua_server_System_bitOpLeft00
static int tolua_server_System_bitOpLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int val = ((int)  tolua_tonumber(tolua_S,1,0));
  int cnt = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  System::bitOpLeft(val,cnt);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'bitOpLeft'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::bitOpSetMask */
#ifndef TOLUA_DISABLE_tolua_server_System_bitOpSetMask00
static int tolua_server_System_bitOpSetMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int val = ((int)  tolua_tonumber(tolua_S,1,0));
  int idx = ((int)  tolua_tonumber(tolua_S,2,0));
  bool flag = ((bool) (tolua_toboolean(tolua_S,3,0)!=0));
  {
   int tolua_ret = (int)  System::bitOpSetMask(val,idx,flag);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'bitOpSetMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::makeInt16 */
#ifndef TOLUA_DISABLE_tolua_server_System_makeInt1600
static int tolua_server_System_makeInt1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int lo = ((int)  tolua_tonumber(tolua_S,1,0));
  int hi = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  System::makeInt16(lo,hi);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'makeInt16'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::makeInt32 */
#ifndef TOLUA_DISABLE_tolua_server_System_makeInt3200
static int tolua_server_System_makeInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int lo = ((int)  tolua_tonumber(tolua_S,1,0));
  int hi = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  System::makeInt32(lo,hi);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'makeInt32'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::makeHiInt16 */
#ifndef TOLUA_DISABLE_tolua_server_System_makeHiInt1600
static int tolua_server_System_makeHiInt1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int val = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  System::makeHiInt16(val);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'makeHiInt16'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::makeLoInt16 */
#ifndef TOLUA_DISABLE_tolua_server_System_makeLoInt1600
static int tolua_server_System_makeLoInt1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int val = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  System::makeLoInt16(val);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'makeLoInt16'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::makeHiInt8 */
#ifndef TOLUA_DISABLE_tolua_server_System_makeHiInt800
static int tolua_server_System_makeHiInt800(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int val = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  System::makeHiInt8(val);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'makeHiInt8'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::makeLoInt8 */
#ifndef TOLUA_DISABLE_tolua_server_System_makeLoInt800
static int tolua_server_System_makeLoInt800(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int val = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  System::makeLoInt8(val);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'makeLoInt8'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::int32Byte */
#ifndef TOLUA_DISABLE_tolua_server_System_int32Byte00
static int tolua_server_System_int32Byte00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int b1 = ((int)  tolua_tonumber(tolua_S,1,0));
  int b2 = ((int)  tolua_tonumber(tolua_S,2,0));
  int b3 = ((int)  tolua_tonumber(tolua_S,3,0));
  int b4 = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   int tolua_ret = (int)  System::int32Byte(b1,b2,b3,b4);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'int32Byte'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::byteInt32 */
#ifndef TOLUA_DISABLE_tolua_server_System_byteInt3200
static int tolua_server_System_byteInt3200(lua_State* tolua_S)
{
	return System::byteInt32(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::timeEncode */
#ifndef TOLUA_DISABLE_tolua_server_System_timeEncode00
static int tolua_server_System_timeEncode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int year = ((int)  tolua_tonumber(tolua_S,1,0));
  int mon = ((int)  tolua_tonumber(tolua_S,2,0));
  int day = ((int)  tolua_tonumber(tolua_S,3,0));
  int hour = ((int)  tolua_tonumber(tolua_S,4,0));
  int m = ((int)  tolua_tonumber(tolua_S,5,0));
  int sec = ((int)  tolua_tonumber(tolua_S,6,0));
  {
   unsigned int tolua_ret = (unsigned int)  System::timeEncode(year,mon,day,hour,m,sec);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'timeEncode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::timeDecode */
#ifndef TOLUA_DISABLE_tolua_server_System_timeDecode00
static int tolua_server_System_timeDecode00(lua_State* tolua_S)
{
	return System::timeDecode(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::logCounter */
#ifndef TOLUA_DISABLE_tolua_server_System_logCounter00
static int tolua_server_System_logCounter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isstring(tolua_S,5,1,&tolua_err) ||
     !tolua_isstring(tolua_S,6,1,&tolua_err) ||
     !tolua_isstring(tolua_S,7,1,&tolua_err) ||
     !tolua_isstring(tolua_S,8,1,&tolua_err) ||
     !tolua_isstring(tolua_S,9,1,&tolua_err) ||
     !tolua_isstring(tolua_S,10,1,&tolua_err) ||
     !tolua_isstring(tolua_S,11,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,12,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,13,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actorid = ((int)  tolua_tonumber(tolua_S,1,0));
  const char* aid = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* user_level = ((const char*)  tolua_tostring(tolua_S,3,""));
  const char* counter = ((const char*)  tolua_tostring(tolua_S,4,""));
  const char* value = ((const char*)  tolua_tostring(tolua_S,5,""));
  const char* extra = ((const char*)  tolua_tostring(tolua_S,6,""));
  const char* kingdom = ((const char*)  tolua_tostring(tolua_S,7,""));
  const char* phylum = ((const char*)  tolua_tostring(tolua_S,8,""));
  const char* classfield = ((const char*)  tolua_tostring(tolua_S,9,""));
  const char* family = ((const char*)  tolua_tostring(tolua_S,10,""));
  const char* genus = ((const char*)  tolua_tostring(tolua_S,11,""));
  int flag = ((int)  tolua_tonumber(tolua_S,12,lfDB));
  {
   System::logCounter(actorid,aid,user_level,counter,value,extra,kingdom,phylum,classfield,family,genus,flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'logCounter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::logEnconomy */
#ifndef TOLUA_DISABLE_tolua_server_System_logEnconomy00
static int tolua_server_System_logEnconomy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isstring(tolua_S,5,1,&tolua_err) ||
     !tolua_isstring(tolua_S,6,1,&tolua_err) ||
     !tolua_isstring(tolua_S,7,1,&tolua_err) ||
     !tolua_isstring(tolua_S,8,1,&tolua_err) ||
     !tolua_isstring(tolua_S,9,1,&tolua_err) ||
     !tolua_isstring(tolua_S,10,1,&tolua_err) ||
     !tolua_isstring(tolua_S,11,1,&tolua_err) ||
     !tolua_isstring(tolua_S,12,1,&tolua_err) ||
     !tolua_isstring(tolua_S,13,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,14,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,15,1,&tolua_err) ||
     !tolua_isstring(tolua_S,16,1,&tolua_err) ||
     !tolua_isstring(tolua_S,17,1,&tolua_err) ||
     !tolua_isstring(tolua_S,18,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,19,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actorid = ((int)  tolua_tonumber(tolua_S,1,0));
  const char* aid = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* currency = ((const char*)  tolua_tostring(tolua_S,3,""));
  const char* amount = ((const char*)  tolua_tostring(tolua_S,4,""));
  const char* value = ((const char*)  tolua_tostring(tolua_S,5,""));
  const char* kingdom = ((const char*)  tolua_tostring(tolua_S,6,""));
  const char* phylum = ((const char*)  tolua_tostring(tolua_S,7,""));
  const char* classfield = ((const char*)  tolua_tostring(tolua_S,8,""));
  const char* family = ((const char*)  tolua_tostring(tolua_S,9,""));
  const char* genus = ((const char*)  tolua_tostring(tolua_S,10,""));
  const char* extra = ((const char*)  tolua_tostring(tolua_S,11,""));
  const char* extra2 = ((const char*)  tolua_tostring(tolua_S,12,""));
  const char* pf = ((const char*)  tolua_tostring(tolua_S,13,""));
  int flag = ((int)  tolua_tonumber(tolua_S,14,lfNormal));
  bool isPay = ((bool) (tolua_toboolean(tolua_S,15,true)!=0));
  const char* openkey = ((const char*)  tolua_tostring(tolua_S,16,""));
  const char* pfkey = ((const char*)  tolua_tostring(tolua_S,17,""));
  const char* pfid = ((const char*)  tolua_tostring(tolua_S,18,""));
  {
   System::logEnconomy(actorid,aid,currency,amount,value,kingdom,phylum,classfield,family,genus,extra,extra2,pf,flag,isPay,openkey,pfkey,pfid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'logEnconomy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::logMilestone */
#ifndef TOLUA_DISABLE_tolua_server_System_logMilestone00
static int tolua_server_System_logMilestone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isstring(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actorid = ((int)  tolua_tonumber(tolua_S,1,0));
  const char* aid = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* milestone = ((const char*)  tolua_tostring(tolua_S,3,""));
  const char* value = ((const char*)  tolua_tostring(tolua_S,4,""));
  const char* extra = ((const char*)  tolua_tostring(tolua_S,5,""));
  int flag = ((int)  tolua_tonumber(tolua_S,6,lfNormal));
  {
   System::logMilestone(actorid,aid,milestone,value,extra,flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'logMilestone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::logPayment */
#ifndef TOLUA_DISABLE_tolua_server_System_logPayment00
static int tolua_server_System_logPayment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,1,&tolua_err) ||
     !tolua_isstring(tolua_S,10,1,&tolua_err) ||
     !tolua_isstring(tolua_S,11,1,&tolua_err) ||
     !tolua_isstring(tolua_S,12,1,&tolua_err) ||
     !tolua_isstring(tolua_S,13,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,14,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,15,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,16,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,17,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int ret = ((int)  tolua_tonumber(tolua_S,1,0));
  int actorId = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* aid = ((const char*)  tolua_tostring(tolua_S,3,0));
  int amount = ((int)  tolua_tonumber(tolua_S,4,0));
  int mstType = ((int)  tolua_tonumber(tolua_S,5,0));
  int p1 = ((int)  tolua_tonumber(tolua_S,6,0));
  int p2 = ((int)  tolua_tonumber(tolua_S,7,0));
  int p3 = ((int)  tolua_tonumber(tolua_S,8,0));
  int value = ((int)  tolua_tonumber(tolua_S,9,1));
  const char* kingdom = ((const char*)  tolua_tostring(tolua_S,10,""));
  const char* phylum = ((const char*)  tolua_tostring(tolua_S,11,""));
  const char* transactionid = ((const char*)  tolua_tostring(tolua_S,12,""));
  const char* extra = ((const char*)  tolua_tostring(tolua_S,13,""));
  int p4 = ((int)  tolua_tonumber(tolua_S,14,0));
  int p5 = ((int)  tolua_tonumber(tolua_S,15,0));
  int flag = ((int)  tolua_tonumber(tolua_S,16,lfNormal));
  {
   System::logPayment(ret,actorId,aid,amount,mstType,p1,p2,p3,value,kingdom,phylum,transactionid,extra,p4,p5,flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'logPayment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::logInstall */
#ifndef TOLUA_DISABLE_tolua_server_System_logInstall00
static int tolua_server_System_logInstall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isstring(tolua_S,5,1,&tolua_err) ||
     !tolua_isstring(tolua_S,6,1,&tolua_err) ||
     !tolua_isstring(tolua_S,7,1,&tolua_err) ||
     !tolua_isstring(tolua_S,8,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* actorId = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* source = ((const char*)  tolua_tostring(tolua_S,2,""));
  const char* affiliate = ((const char*)  tolua_tostring(tolua_S,3,""));
  const char* creative = ((const char*)  tolua_tostring(tolua_S,4,""));
  const char* family = ((const char*)  tolua_tostring(tolua_S,5,""));
  const char* genus = ((const char*)  tolua_tostring(tolua_S,6,""));
  const char* from_uid = ((const char*)  tolua_tostring(tolua_S,7,""));
  const char* extra = ((const char*)  tolua_tostring(tolua_S,8,""));
  int flag = ((int)  tolua_tonumber(tolua_S,9,lfNormal));
  {
   System::logInstall(actorId,source,affiliate,creative,family,genus,from_uid,extra,flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'logInstall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::logDau */
#ifndef TOLUA_DISABLE_tolua_server_System_logDau00
static int tolua_server_System_logDau00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isstring(tolua_S,5,1,&tolua_err) ||
     !tolua_isstring(tolua_S,6,1,&tolua_err) ||
     !tolua_isstring(tolua_S,7,1,&tolua_err) ||
     !tolua_isstring(tolua_S,8,1,&tolua_err) ||
     !tolua_isstring(tolua_S,9,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,11,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* aid = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* source = ((const char*)  tolua_tostring(tolua_S,2,""));
  const char* affiliate = ((const char*)  tolua_tostring(tolua_S,3,""));
  const char* creative = ((const char*)  tolua_tostring(tolua_S,4,""));
  const char* family = ((const char*)  tolua_tostring(tolua_S,5,""));
  const char* genus = ((const char*)  tolua_tostring(tolua_S,6,""));
  const char* ip = ((const char*)  tolua_tostring(tolua_S,7,""));
  const char* from_uid = ((const char*)  tolua_tostring(tolua_S,8,""));
  const char* extra = ((const char*)  tolua_tostring(tolua_S,9,""));
  int flag = ((int)  tolua_tonumber(tolua_S,10,lfNormal));
  {
   System::logDau(aid,source,affiliate,creative,family,genus,ip,from_uid,extra,flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'logDau'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::logGameInfo */
#ifndef TOLUA_DISABLE_tolua_server_System_logGameInfo00
static int tolua_server_System_logGameInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isstring(tolua_S,5,1,&tolua_err) ||
     !tolua_isstring(tolua_S,6,1,&tolua_err) ||
     !tolua_isstring(tolua_S,7,1,&tolua_err) ||
     !tolua_isstring(tolua_S,8,1,&tolua_err) ||
     !tolua_isstring(tolua_S,9,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,11,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* aid = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* user_level = ((const char*)  tolua_tostring(tolua_S,2,""));
  const char* value = ((const char*)  tolua_tostring(tolua_S,3,""));
  const char* extra = ((const char*)  tolua_tostring(tolua_S,4,""));
  const char* kingdom = ((const char*)  tolua_tostring(tolua_S,5,""));
  const char* phylum = ((const char*)  tolua_tostring(tolua_S,6,""));
  const char* classfield = ((const char*)  tolua_tostring(tolua_S,7,""));
  const char* family = ((const char*)  tolua_tostring(tolua_S,8,""));
  const char* genus = ((const char*)  tolua_tostring(tolua_S,9,""));
  int flag = ((int)  tolua_tonumber(tolua_S,10,lfNormal));
  {
   System::logGameInfo(aid,user_level,value,extra,kingdom,phylum,classfield,family,genus,flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'logGameInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::logChat */
#ifndef TOLUA_DISABLE_tolua_server_System_logChat00
static int tolua_server_System_logChat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isstring(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* content = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* toaid = ((const char*)  tolua_tostring(tolua_S,4,""));
  const char* toname = ((const char*)  tolua_tostring(tolua_S,5,""));
  {
   System::logChat(et,type,content,toaid,toname);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'logChat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::logTLog */
#ifndef TOLUA_DISABLE_tolua_server_System_logTLog00
static int tolua_server_System_logTLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* logstr = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   System::logTLog(logstr);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'logTLog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::logOnline */
#ifndef TOLUA_DISABLE_tolua_server_System_logOnline00
static int tolua_server_System_logOnline00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   System::logOnline();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'logOnline'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getOnlineCount */
#ifndef TOLUA_DISABLE_tolua_server_System_getOnlineCount00
static int tolua_server_System_getOnlineCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isboolean(tolua_S,1,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool includeCache = ((bool) (tolua_toboolean(tolua_S,1,false)!=0));
  {
   int tolua_ret = (int)  System::getOnlineCount(includeCache);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getOnlineCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::actorMgrReloadScript */
#ifndef TOLUA_DISABLE_tolua_server_System_actorMgrReloadScript00
static int tolua_server_System_actorMgrReloadScript00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   System::actorMgrReloadScript();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'actorMgrReloadScript'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::actorMgrLoadFilterNames */
#ifndef TOLUA_DISABLE_tolua_server_System_actorMgrLoadFilterNames00
static int tolua_server_System_actorMgrLoadFilterNames00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   System::actorMgrLoadFilterNames();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'actorMgrLoadFilterNames'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::dbClose */
#ifndef TOLUA_DISABLE_tolua_server_System_dbClose00
static int tolua_server_System_dbClose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* db_conn = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   System::dbClose(db_conn);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'dbClose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::dbConnect */
#ifndef TOLUA_DISABLE_tolua_server_System_dbConnect00
static int tolua_server_System_dbConnect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* db_conn = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  System::dbConnect(db_conn);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'dbConnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getGameEngineGlobalDbConn */
#ifndef TOLUA_DISABLE_tolua_server_System_getGameEngineGlobalDbConn00
static int tolua_server_System_getGameEngineGlobalDbConn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   void* tolua_ret = (void*)  System::getGameEngineGlobalDbConn();
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getGameEngineGlobalDbConn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::createActorsDbConn */
#ifndef TOLUA_DISABLE_tolua_server_System_createActorsDbConn00
static int tolua_server_System_createActorsDbConn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   void* tolua_ret = (void*)  System::createActorsDbConn();
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'createActorsDbConn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::delActorsDbConn */
#ifndef TOLUA_DISABLE_tolua_server_System_delActorsDbConn00
static int tolua_server_System_delActorsDbConn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* db_conn = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   System::delActorsDbConn(db_conn);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'delActorsDbConn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::dbQuery */
#ifndef TOLUA_DISABLE_tolua_server_System_dbQuery00
static int tolua_server_System_dbQuery00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* db_conn = ((void*)  tolua_touserdata(tolua_S,1,0));
  const char* sql = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   int tolua_ret = (int)  System::dbQuery(db_conn,sql);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'dbQuery'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::dbExe */
#ifndef TOLUA_DISABLE_tolua_server_System_dbExe00
static int tolua_server_System_dbExe00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* db_connection = ((void*)  tolua_touserdata(tolua_S,1,0));
  const char* sql = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   int tolua_ret = (int)  System::dbExe(db_connection,sql);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'dbExe'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::dbResetQuery */
#ifndef TOLUA_DISABLE_tolua_server_System_dbResetQuery00
static int tolua_server_System_dbResetQuery00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* db_conn = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   System::dbResetQuery(db_conn);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'dbResetQuery'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::dbCurrentRow */
#ifndef TOLUA_DISABLE_tolua_server_System_dbCurrentRow00
static int tolua_server_System_dbCurrentRow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* db_conn = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  System::dbCurrentRow(db_conn);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'dbCurrentRow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::dbGetRow */
#ifndef TOLUA_DISABLE_tolua_server_System_dbGetRow00
static int tolua_server_System_dbGetRow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* row = ((void*)  tolua_touserdata(tolua_S,1,0));
  int idx = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   const char* tolua_ret = (const char*)  System::dbGetRow(row,idx);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'dbGetRow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::dbGetRowCount */
#ifndef TOLUA_DISABLE_tolua_server_System_dbGetRowCount00
static int tolua_server_System_dbGetRowCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* db_conn = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  System::dbGetRowCount(db_conn);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'dbGetRowCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::dbNextRow */
#ifndef TOLUA_DISABLE_tolua_server_System_dbNextRow00
static int tolua_server_System_dbNextRow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* db_conn = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  System::dbNextRow(db_conn);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'dbNextRow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::geAddRoutes */
#ifndef TOLUA_DISABLE_tolua_server_System_geAddRoutes00
static int tolua_server_System_geAddRoutes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int serverid = ((int)  tolua_tonumber(tolua_S,1,0));
  const char* host = ((const char*)  tolua_tostring(tolua_S,2,0));
  int port = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  System::geAddRoutes(serverid,host,port);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'geAddRoutes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::geHasRoute */
#ifndef TOLUA_DISABLE_tolua_server_System_geHasRoute00
static int tolua_server_System_geHasRoute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int serverid = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  System::geHasRoute(serverid);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'geHasRoute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getStrLenUtf8 */
#ifndef TOLUA_DISABLE_tolua_server_System_getStrLenUtf800
static int tolua_server_System_getStrLenUtf800(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* str = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   int tolua_ret = (int)  System::getStrLenUtf8(str);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getStrLenUtf8'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::SendToDb */
#ifndef TOLUA_DISABLE_tolua_server_System_SendToDb00
static int tolua_server_System_SendToDb00(lua_State* tolua_S)
{
	return System::SendToDb(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::allocDBPacket */
#ifndef TOLUA_DISABLE_tolua_server_System_allocDBPacket00
static int tolua_server_System_allocDBPacket00(lua_State* tolua_S)
{
	return System::allocDBPacket(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::flushDBPacket */
#ifndef TOLUA_DISABLE_tolua_server_System_flushDBPacket00
static int tolua_server_System_flushDBPacket00(lua_State* tolua_S)
{
	return System::flushDBPacket(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getDayDiff */
#ifndef TOLUA_DISABLE_tolua_server_System_getDayDiff00
static int tolua_server_System_getDayDiff00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int t1 = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  unsigned int t2 = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  System::getDayDiff(t1,t2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getDayDiff'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::start5sScripte */
#ifndef TOLUA_DISABLE_tolua_server_System_start5sScripte00
static int tolua_server_System_start5sScripte00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isboolean(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool flag = ((bool) (tolua_toboolean(tolua_S,1,0)!=0));
  {
   System::start5sScripte(flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'start5sScripte'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::sendOffMsg */
#ifndef TOLUA_DISABLE_tolua_server_System_sendOffMsg00
static int tolua_server_System_sendOffMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int aid = ((int)  tolua_tonumber(tolua_S,1,0));
  const char* actorname = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* account = ((const char*)  tolua_tostring(tolua_S,3,0));
  int srcid = ((int)  tolua_tonumber(tolua_S,4,0));
  void* dp = ((void*)  tolua_touserdata(tolua_S,5,0));
  {
   System::sendOffMsg(aid,actorname,account,srcid,dp);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'sendOffMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::saveChatMonitoring */
#ifndef TOLUA_DISABLE_tolua_server_System_saveChatMonitoring00
static int tolua_server_System_saveChatMonitoring00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isstring(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int aid = ((int)  tolua_tonumber(tolua_S,1,0));
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  int msgid = ((int)  tolua_tonumber(tolua_S,3,0));
  int guild = ((int)  tolua_tonumber(tolua_S,4,0));
  const char* actorname = ((const char*)  tolua_tostring(tolua_S,5,0));
  const char* account = ((const char*)  tolua_tostring(tolua_S,6,0));
  const char* msg = ((const char*)  tolua_tostring(tolua_S,7,0));
  {
   System::saveChatMonitoring(aid,type,msgid,guild,actorname,account,msg);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'saveChatMonitoring'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::checkIdentity */
#ifndef TOLUA_DISABLE_tolua_server_System_checkIdentity00
static int tolua_server_System_checkIdentity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* id = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   int tolua_ret = (int)  System::checkIdentity(id);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'checkIdentity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::setEngineGcActorCnt */
#ifndef TOLUA_DISABLE_tolua_server_System_setEngineGcActorCnt00
static int tolua_server_System_setEngineGcActorCnt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int cnt = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   System::setEngineGcActorCnt(cnt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setEngineGcActorCnt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::engineGc */
#ifndef TOLUA_DISABLE_tolua_server_System_engineGc00
static int tolua_server_System_engineGc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   System::engineGc();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'engineGc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::stopLog */
#ifndef TOLUA_DISABLE_tolua_server_System_stopLog00
static int tolua_server_System_stopLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isboolean(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool flag = ((bool) (tolua_toboolean(tolua_S,1,0)!=0));
  {
   System::stopLog(flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'stopLog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::stopCounterLog */
#ifndef TOLUA_DISABLE_tolua_server_System_stopCounterLog00
static int tolua_server_System_stopCounterLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isboolean(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool flag = ((bool) (tolua_toboolean(tolua_S,1,0)!=0));
  {
   System::stopCounterLog(flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'stopCounterLog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::stopEconomyLog */
#ifndef TOLUA_DISABLE_tolua_server_System_stopEconomyLog00
static int tolua_server_System_stopEconomyLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isboolean(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool flag = ((bool) (tolua_toboolean(tolua_S,1,0)!=0));
  {
   System::stopEconomyLog(flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'stopEconomyLog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getSystemTime */
#ifndef TOLUA_DISABLE_tolua_server_System_getSystemTime00
static int tolua_server_System_getSystemTime00(lua_State* tolua_S)
{
	return System::getSystemTime(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::setActorDbSaveTime */
#ifndef TOLUA_DISABLE_tolua_server_System_setActorDbSaveTime00
static int tolua_server_System_setActorDbSaveTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int sec = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   System::setActorDbSaveTime(sec);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setActorDbSaveTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::closeActor */
#ifndef TOLUA_DISABLE_tolua_server_System_closeActor00
static int tolua_server_System_closeActor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   System::closeActor(et);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'closeActor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getSysVar */
#ifndef TOLUA_DISABLE_tolua_server_System_getSysVar00
static int tolua_server_System_getSysVar00(lua_State* tolua_S)
{
	return System::getSysVar(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::createSysVar */
#ifndef TOLUA_DISABLE_tolua_server_System_createSysVar00
static int tolua_server_System_createSysVar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int ownerId = ((int)  tolua_tonumber(tolua_S,1,0));
  const char* ownerName = ((const char*)  tolua_tostring(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   unsigned int tolua_ret = (unsigned int)  System::createSysVar(ownerId,ownerName,type);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'createSysVar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::saveSysVar */
#ifndef TOLUA_DISABLE_tolua_server_System_saveSysVar00
static int tolua_server_System_saveSysVar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int ownerId = ((int)  tolua_tonumber(tolua_S,1,0));
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  unsigned int hdl = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  {
   System::saveSysVar(ownerId,type,hdl);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'saveSysVar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::reloadSysVar */
#ifndef TOLUA_DISABLE_tolua_server_System_reloadSysVar00
static int tolua_server_System_reloadSysVar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   System::reloadSysVar();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'reloadSysVar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::saveSysTmpVar */
#ifndef TOLUA_DISABLE_tolua_server_System_saveSysTmpVar00
static int tolua_server_System_saveSysTmpVar00(lua_State* tolua_S)
{
	return System::saveSysTmpVar(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::loadSysTmpVar */
#ifndef TOLUA_DISABLE_tolua_server_System_loadSysTmpVar00
static int tolua_server_System_loadSysTmpVar00(lua_State* tolua_S)
{
	return System::loadSysTmpVar(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::startOneGameClient */
#ifndef TOLUA_DISABLE_tolua_server_System_startOneGameClient00
static int tolua_server_System_startOneGameClient00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* ip = ((const char*)  tolua_tostring(tolua_S,1,0));
  int port = ((int)  tolua_tonumber(tolua_S,2,0));
  int serverId = ((int)  tolua_tonumber(tolua_S,3,0));
  int serverType = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   bool tolua_ret = (bool)  System::startOneGameClient(ip,port,serverId,serverType);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'startOneGameClient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::resetGameRoute */
#ifndef TOLUA_DISABLE_tolua_server_System_resetGameRoute00
static int tolua_server_System_resetGameRoute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   System::resetGameRoute();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'resetGameRoute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::resetSingleGameRoute */
#ifndef TOLUA_DISABLE_tolua_server_System_resetSingleGameRoute00
static int tolua_server_System_resetSingleGameRoute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int sid = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   System::resetSingleGameRoute(sid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'resetSingleGameRoute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::setBattleSrvFlag */
#ifndef TOLUA_DISABLE_tolua_server_System_setBattleSrvFlag00
static int tolua_server_System_setBattleSrvFlag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int flag = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   System::setBattleSrvFlag(flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setBattleSrvFlag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getBattleSrvFlag */
#ifndef TOLUA_DISABLE_tolua_server_System_getBattleSrvFlag00
static int tolua_server_System_getBattleSrvFlag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  System::getBattleSrvFlag();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getBattleSrvFlag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::isBattleSrv */
#ifndef TOLUA_DISABLE_tolua_server_System_isBattleSrv00
static int tolua_server_System_isBattleSrv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  System::isBattleSrv();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'isBattleSrv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::isLianFuSrv */
#ifndef TOLUA_DISABLE_tolua_server_System_isLianFuSrv00
static int tolua_server_System_isLianFuSrv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  System::isLianFuSrv();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'isLianFuSrv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::isCommSrv */
#ifndef TOLUA_DISABLE_tolua_server_System_isCommSrv00
static int tolua_server_System_isCommSrv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  System::isCommSrv();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'isCommSrv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::isCrossWarSrv */
#ifndef TOLUA_DISABLE_tolua_server_System_isCrossWarSrv00
static int tolua_server_System_isCrossWarSrv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  System::isCrossWarSrv();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'isCrossWarSrv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::sendMsgToAllGameClient */
#ifndef TOLUA_DISABLE_tolua_server_System_sendMsgToAllGameClient00
static int tolua_server_System_sendMsgToAllGameClient00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const void* buff = ((const void*)  tolua_touserdata(tolua_S,1,0));
  int size = ((int)  tolua_tonumber(tolua_S,2,0));
  int sid = ((int)  tolua_tonumber(tolua_S,3,0));
  int cross_method = ((int)  tolua_tonumber(tolua_S,4,CROSSSERVER_ALL));
  {
   System::sendMsgToAllGameClient(buff,size,sid,cross_method);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'sendMsgToAllGameClient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::sendPacketToAllGameClient */
#ifndef TOLUA_DISABLE_tolua_server_System_sendPacketToAllGameClient00
static int tolua_server_System_sendPacketToAllGameClient00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* packet = ((void*)  tolua_touserdata(tolua_S,1,0));
  int sid = ((int)  tolua_tonumber(tolua_S,2,0));
  int cross_method = ((int)  tolua_tonumber(tolua_S,3,CROSSSERVER_ALL));
  {
   System::sendPacketToAllGameClient(packet,sid,cross_method);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'sendPacketToAllGameClient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::removeBattleSrv */
#ifndef TOLUA_DISABLE_tolua_server_System_removeBattleSrv00
static int tolua_server_System_removeBattleSrv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int sid = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   System::removeBattleSrv(sid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'removeBattleSrv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::loadStringFromFile */
#ifndef TOLUA_DISABLE_tolua_server_System_loadStringFromFile00
static int tolua_server_System_loadStringFromFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  System::loadStringFromFile(filename);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'loadStringFromFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::reloadFilterDb */
#ifndef TOLUA_DISABLE_tolua_server_System_reloadFilterDb00
static int tolua_server_System_reloadFilterDb00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  System::reloadFilterDb();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'reloadFilterDb'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::filterText */
#ifndef TOLUA_DISABLE_tolua_server_System_filterText00
static int tolua_server_System_filterText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* text = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  System::filterText(text);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'filterText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::filterTextCount */
#ifndef TOLUA_DISABLE_tolua_server_System_filterTextCount00
static int tolua_server_System_filterTextCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* text = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   int tolua_ret = (int)  System::filterTextCount(text);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'filterTextCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::execute */
#ifndef TOLUA_DISABLE_tolua_server_System_execute00
static int tolua_server_System_execute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* cmd = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   System::execute(cmd);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'execute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::outputConfigFile */
#ifndef TOLUA_DISABLE_tolua_server_System_outputConfigFile00
static int tolua_server_System_outputConfigFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* fn = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* output = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  System::outputConfigFile(fn,output);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'outputConfigFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::startAsyncWorker */
#ifndef TOLUA_DISABLE_tolua_server_System_startAsyncWorker00
static int tolua_server_System_startAsyncWorker00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   System::startAsyncWorker();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'startAsyncWorker'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::reloadWorkerScript */
#ifndef TOLUA_DISABLE_tolua_server_System_reloadWorkerScript00
static int tolua_server_System_reloadWorkerScript00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   System::reloadWorkerScript();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'reloadWorkerScript'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::sendMessageToAsyncWorker */
#ifndef TOLUA_DISABLE_tolua_server_System_sendMessageToAsyncWorker00
static int tolua_server_System_sendMessageToAsyncWorker00(lua_State* tolua_S)
{
	return System::sendMessageToAsyncWorker(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::regScriptNetMsg */
#ifndef TOLUA_DISABLE_tolua_server_System_regScriptNetMsg00
static int tolua_server_System_regScriptNetMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int sysId = ((int)  tolua_tonumber(tolua_S,1,0));
  int cmdId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   System::regScriptNetMsg(sysId,cmdId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'regScriptNetMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::monUpdate */
#ifndef TOLUA_DISABLE_tolua_server_System_monUpdate00
static int tolua_server_System_monUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  System::monUpdate();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'monUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::itemUpdate */
#ifndef TOLUA_DISABLE_tolua_server_System_itemUpdate00
static int tolua_server_System_itemUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  System::itemUpdate();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'itemUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::changePrestigeExp */
#ifndef TOLUA_DISABLE_tolua_server_System_changePrestigeExp00
static int tolua_server_System_changePrestigeExp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   System::changePrestigeExp();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'changePrestigeExp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::reloadLang */
#ifndef TOLUA_DISABLE_tolua_server_System_reloadLang00
static int tolua_server_System_reloadLang00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  System::reloadLang();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'reloadLang'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::setDbRetRoute */
#ifndef TOLUA_DISABLE_tolua_server_System_setDbRetRoute00
static int tolua_server_System_setDbRetRoute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int sysid = ((int)  tolua_tonumber(tolua_S,1,0));
  int cmd = ((int)  tolua_tonumber(tolua_S,2,0));
  int val = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   System::setDbRetRoute(sysid,cmd,val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setDbRetRoute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::sendDataToCenter */
#ifndef TOLUA_DISABLE_tolua_server_System_sendDataToCenter00
static int tolua_server_System_sendDataToCenter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pack = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   System::sendDataToCenter(pack);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'sendDataToCenter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::runGTest */
#ifndef TOLUA_DISABLE_tolua_server_System_runGTest00
static int tolua_server_System_runGTest00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   System::runGTest();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'runGTest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getInt64 */
#ifndef TOLUA_DISABLE_tolua_server_System_getInt6400
static int tolua_server_System_getInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double num = ((double)  tolua_tonumber(tolua_S,1,0));
  {
   double tolua_ret = (double)  System::getInt64(num);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getInt64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::sendDataToActorServer */
#ifndef TOLUA_DISABLE_tolua_server_System_sendDataToActorServer00
static int tolua_server_System_sendDataToActorServer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pack = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   System::sendDataToActorServer(pack);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'sendDataToActorServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::enableCheckDataValid */
#ifndef TOLUA_DISABLE_tolua_server_System_enableCheckDataValid00
static int tolua_server_System_enableCheckDataValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isboolean(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool flag = ((bool) (tolua_toboolean(tolua_S,1,0)!=0));
  {
   System::enableCheckDataValid(flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'enableCheckDataValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::setActorDataValid */
#ifndef TOLUA_DISABLE_tolua_server_System_setActorDataValid00
static int tolua_server_System_setActorDataValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int serverId = ((int)  tolua_tonumber(tolua_S,1,0));
  int actorId = ((int)  tolua_tonumber(tolua_S,2,0));
  bool flag = ((bool) (tolua_toboolean(tolua_S,3,0)!=0));
  {
   System::setActorDataValid(serverId,actorId,flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setActorDataValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::sendTipmsg */
#ifndef TOLUA_DISABLE_tolua_server_System_sendTipmsg00
static int tolua_server_System_sendTipmsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actorid = ((int)  tolua_tonumber(tolua_S,1,0));
  const char* msg = ((const char*)  tolua_tostring(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,ttTipmsgWindow));
  {
   System::sendTipmsg(actorid,msg,type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'sendTipmsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::delOneGameClient */
#ifndef TOLUA_DISABLE_tolua_server_System_delOneGameClient00
static int tolua_server_System_delOneGameClient00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int serverId = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   System::delOneGameClient(serverId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'delOneGameClient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::loadFileAsUserData */
#ifndef TOLUA_DISABLE_tolua_server_System_loadFileAsUserData00
static int tolua_server_System_loadFileAsUserData00(lua_State* tolua_S)
{
	return System::loadFileAsUserData(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::saveUserDataToFile */
#ifndef TOLUA_DISABLE_tolua_server_System_saveUserDataToFile00
static int tolua_server_System_saveUserDataToFile00(lua_State* tolua_S)
{
	return System::saveUserDataToFile(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getOnlineActorList */
#ifndef TOLUA_DISABLE_tolua_server_System_getOnlineActorList00
static int tolua_server_System_getOnlineActorList00(lua_State* tolua_S)
{
	return System::getOnlineActorList(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getAllActorData */
#ifndef TOLUA_DISABLE_tolua_server_System_getAllActorData00
static int tolua_server_System_getAllActorData00(lua_State* tolua_S)
{
	return System::getAllActorData(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::findSkirmish */
#ifndef TOLUA_DISABLE_tolua_server_System_findSkirmish00
static int tolua_server_System_findSkirmish00(lua_State* tolua_S)
{
	return System::findSkirmish(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::FindFieldPlayer */
#ifndef TOLUA_DISABLE_tolua_server_System_FindFieldPlayer00
static int tolua_server_System_FindFieldPlayer00(lua_State* tolua_S)
{
	return System::FindFieldPlayer(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::sendMail */
#ifndef TOLUA_DISABLE_tolua_server_System_sendMail00
static int tolua_server_System_sendMail00(lua_State* tolua_S)
{
	return System::sendMail(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::regInstanceMonsterDamage */
#ifndef TOLUA_DISABLE_tolua_server_System_regInstanceMonsterDamage00
static int tolua_server_System_regInstanceMonsterDamage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int fid = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   System::regInstanceMonsterDamage(fid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'regInstanceMonsterDamage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::regInstanceActorDamage */
#ifndef TOLUA_DISABLE_tolua_server_System_regInstanceActorDamage00
static int tolua_server_System_regInstanceActorDamage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int fid = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   System::regInstanceActorDamage(fid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'regInstanceActorDamage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::regStartScript */
#ifndef TOLUA_DISABLE_tolua_server_System_regStartScript00
static int tolua_server_System_regStartScript00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* rule = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  System::regStartScript(rule);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'regStartScript'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::regEndScript */
#ifndef TOLUA_DISABLE_tolua_server_System_regEndScript00
static int tolua_server_System_regEndScript00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* rule = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  System::regEndScript(rule);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'regEndScript'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::checkRuleTime */
#ifndef TOLUA_DISABLE_tolua_server_System_checkRuleTime00
static int tolua_server_System_checkRuleTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* rule = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  System::checkRuleTime(rule);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'checkRuleTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getRuleStartTime */
#ifndef TOLUA_DISABLE_tolua_server_System_getRuleStartTime00
static int tolua_server_System_getRuleStartTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* rule = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   double tolua_ret = (double)  System::getRuleStartTime(rule);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRuleStartTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getRuleEndTime */
#ifndef TOLUA_DISABLE_tolua_server_System_getRuleEndTime00
static int tolua_server_System_getRuleEndTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* rule = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   double tolua_ret = (double)  System::getRuleEndTime(rule);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRuleEndTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getGlobalMailMaxUid */
#ifndef TOLUA_DISABLE_tolua_server_System_getGlobalMailMaxUid00
static int tolua_server_System_getGlobalMailMaxUid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  System::getGlobalMailMaxUid();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getGlobalMailMaxUid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::addGlobalMail */
#ifndef TOLUA_DISABLE_tolua_server_System_addGlobalMail00
static int tolua_server_System_addGlobalMail00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* head = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* context = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* item_str = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   System::addGlobalMail(head,context,item_str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addGlobalMail'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::buyMonthCard */
#ifndef TOLUA_DISABLE_tolua_server_System_buyMonthCard00
static int tolua_server_System_buyMonthCard00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actorid = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   System::buyMonthCard(actorid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'buyMonthCard'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::buyPrivilege */
#ifndef TOLUA_DISABLE_tolua_server_System_buyPrivilege00
static int tolua_server_System_buyPrivilege00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actorid = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   System::buyPrivilege(actorid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'buyPrivilege'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::buyPrivilegeCard */
#ifndef TOLUA_DISABLE_tolua_server_System_buyPrivilegeCard00
static int tolua_server_System_buyPrivilegeCard00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actorid = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   System::buyPrivilegeCard(actorid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'buyPrivilegeCard'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::buyRechargeLimitPackage */
#ifndef TOLUA_DISABLE_tolua_server_System_buyRechargeLimitPackage00
static int tolua_server_System_buyRechargeLimitPackage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actorid = ((int)  tolua_tonumber(tolua_S,1,0));
  int money = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   System::buyRechargeLimitPackage(actorid,money);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'buyRechargeLimitPackage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::buyRechargeLimitPackageOffline */
#ifndef TOLUA_DISABLE_tolua_server_System_buyRechargeLimitPackageOffline00
static int tolua_server_System_buyRechargeLimitPackageOffline00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Actor* tar = ((Actor*)  tolua_tousertype(tolua_S,1,0));
  int money = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   System::buyRechargeLimitPackageOffline(tar,money);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'buyRechargeLimitPackageOffline'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::buyFund */
#ifndef TOLUA_DISABLE_tolua_server_System_buyFund00
static int tolua_server_System_buyFund00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actorid = ((int)  tolua_tonumber(tolua_S,1,0));
  int money = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   System::buyFund(actorid,money);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'buyFund'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::buyFundOffline */
#ifndef TOLUA_DISABLE_tolua_server_System_buyFundOffline00
static int tolua_server_System_buyFundOffline00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Actor* tar = ((Actor*)  tolua_tousertype(tolua_S,1,0));
  int money = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   System::buyFundOffline(tar,money);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'buyFundOffline'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::rand */
#ifndef TOLUA_DISABLE_tolua_server_System_rand00
static int tolua_server_System_rand00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int max = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  System::rand(max);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'rand'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getTimeZone */
#ifndef TOLUA_DISABLE_tolua_server_System_getTimeZone00
static int tolua_server_System_getTimeZone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  System::getTimeZone();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getTimeZone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::shutup */
#ifndef TOLUA_DISABLE_tolua_server_System_shutup00
static int tolua_server_System_shutup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actor_id = ((int)  tolua_tonumber(tolua_S,1,0));
  int time = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   System::shutup(actor_id,time);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'shutup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::releaseShutup */
#ifndef TOLUA_DISABLE_tolua_server_System_releaseShutup00
static int tolua_server_System_releaseShutup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actor_id = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   System::releaseShutup(actor_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'releaseShutup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::offlineChangeTitle */
#ifndef TOLUA_DISABLE_tolua_server_System_offlineChangeTitle00
static int tolua_server_System_offlineChangeTitle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actor_id = ((int)  tolua_tonumber(tolua_S,1,0));
  int oper = ((int)  tolua_tonumber(tolua_S,2,0));
  int tId = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   System::offlineChangeTitle(actor_id,oper,tId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'offlineChangeTitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::startGameConnSrv */
#ifndef TOLUA_DISABLE_tolua_server_System_startGameConnSrv00
static int tolua_server_System_startGameConnSrv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* ip = ((const char*)  tolua_tostring(tolua_S,1,0));
  int port = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  System::startGameConnSrv(ip,port);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'startGameConnSrv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::stopGameConnSrv */
#ifndef TOLUA_DISABLE_tolua_server_System_stopGameConnSrv00
static int tolua_server_System_stopGameConnSrv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   System::stopGameConnSrv();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'stopGameConnSrv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::time2String */
#ifndef TOLUA_DISABLE_tolua_server_System_time2String00
static int tolua_server_System_time2String00(lua_State* tolua_S)
{
	return System::time2String(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getActorCountOfZhuanShengLv */
#ifndef TOLUA_DISABLE_tolua_server_System_getActorCountOfZhuanShengLv00
static int tolua_server_System_getActorCountOfZhuanShengLv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int lv = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   int tolua_ret = (int)  System::getActorCountOfZhuanShengLv(lv);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getActorCountOfZhuanShengLv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getGameTick */
#ifndef TOLUA_DISABLE_tolua_server_System_getGameTick00
static int tolua_server_System_getGameTick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   double tolua_ret = (double)  System::getGameTick();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getGameTick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::logDKMLog */
#ifndef TOLUA_DISABLE_tolua_server_System_logDKMLog00
static int tolua_server_System_logDKMLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* logstr = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* pf = ((const char*)  tolua_tostring(tolua_S,2,"0"));
  {
   System::logDKMLog(logstr,pf);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'logDKMLog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::printAllLua */
#ifndef TOLUA_DISABLE_tolua_server_System_printAllLua00
static int tolua_server_System_printAllLua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   System::printAllLua(et);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'printAllLua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: System::getClvariantSize */
#ifndef TOLUA_DISABLE_tolua_server_System_getClvariantSize00
static int tolua_server_System_getClvariantSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* et = ((void*)  tolua_touserdata(tolua_S,1,0));
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   int tolua_ret = (int)  System::getClvariantSize(et,str);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getClvariantSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::allocPacket */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_allocPacket00
static int tolua_server_LDataPack_allocPacket00(lua_State* tolua_S)
{
	return LDataPack::allocPacket(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::allocPacketCache */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_allocPacketCache00
static int tolua_server_LDataPack_allocPacketCache00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   void* tolua_ret = (void*)  LDataPack::allocPacketCache();
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'allocPacketCache'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::releasePacketCache */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_releasePacketCache00
static int tolua_server_LDataPack_releasePacketCache00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* dpcache = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LDataPack::releasePacketCache(dpcache);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'releasePacketCache'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::allocExtraPacket */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_allocExtraPacket00
static int tolua_server_LDataPack_allocExtraPacket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   void* tolua_ret = (void*)  LDataPack::allocExtraPacket();
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'allocExtraPacket'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::allocPacketToCenter */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_allocPacketToCenter00
static int tolua_server_LDataPack_allocPacketToCenter00(lua_State* tolua_S)
{
	return LDataPack::allocPacketToCenter(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::flush */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_flush00
static int tolua_server_LDataPack_flush00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* ap = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LDataPack::flush(ap);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'flush'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::flushLf */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_flushLf00
static int tolua_server_LDataPack_flushLf00(lua_State* tolua_S)
{
	return LDataPack::flushLf(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::test_allocPack */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_test_allocPack00
static int tolua_server_LDataPack_test_allocPack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   void* tolua_ret = (void*)  LDataPack::test_allocPack();
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'test_allocPack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::getAvaliableLength */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_getAvaliableLength00
static int tolua_server_LDataPack_getAvaliableLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LDataPack::getAvaliableLength(p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getAvaliableLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::getLength */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_getLength00
static int tolua_server_LDataPack_getLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LDataPack::getLength(p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::getPosition */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_getPosition00
static int tolua_server_LDataPack_getPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LDataPack::getPosition(p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::setPosition */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_setPosition00
static int tolua_server_LDataPack_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  int pos = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LDataPack::setPosition(p,pos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::readString */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_readString00
static int tolua_server_LDataPack_readString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  LDataPack::readString(p);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'readString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::readByte */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_readByte00
static int tolua_server_LDataPack_readByte00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   unsigned char tolua_ret = (unsigned char)  LDataPack::readByte(p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'readByte'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::readChar */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_readChar00
static int tolua_server_LDataPack_readChar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   char tolua_ret = (char)  LDataPack::readChar(p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'readChar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::readWord */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_readWord00
static int tolua_server_LDataPack_readWord00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   unsigned short tolua_ret = (unsigned short)  LDataPack::readWord(p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'readWord'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::readShort */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_readShort00
static int tolua_server_LDataPack_readShort00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   short tolua_ret = (short)  LDataPack::readShort(p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'readShort'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::readInt */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_readInt00
static int tolua_server_LDataPack_readInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LDataPack::readInt(p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'readInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::readUInt */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_readUInt00
static int tolua_server_LDataPack_readUInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   unsigned int tolua_ret = (unsigned int)  LDataPack::readUInt(p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'readUInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::readUint64 */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_readUint6400
static int tolua_server_LDataPack_readUint6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   double tolua_ret = (double)  LDataPack::readUint64(p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'readUint64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::readInt64 */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_readInt6400
static int tolua_server_LDataPack_readInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   double tolua_ret = (double)  LDataPack::readInt64(p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'readInt64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::readData */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_readData00
static int tolua_server_LDataPack_readData00(lua_State* tolua_S)
{
	return LDataPack::readData(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::writeString */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_writeString00
static int tolua_server_LDataPack_writeString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   LDataPack::writeString(p,str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'writeString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::writeByte */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_writeByte00
static int tolua_server_LDataPack_writeByte00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  unsigned char v = ((unsigned char)  tolua_tonumber(tolua_S,2,0));
  {
   LDataPack::writeByte(p,v);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'writeByte'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::writeChar */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_writeChar00
static int tolua_server_LDataPack_writeChar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  char v = ((char)  tolua_tonumber(tolua_S,2,0));
  {
   LDataPack::writeChar(p,v);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'writeChar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::writeWord */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_writeWord00
static int tolua_server_LDataPack_writeWord00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  unsigned short v = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
  {
   LDataPack::writeWord(p,v);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'writeWord'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::writeShort */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_writeShort00
static int tolua_server_LDataPack_writeShort00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  short v = ((short)  tolua_tonumber(tolua_S,2,0));
  {
   LDataPack::writeShort(p,v);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'writeShort'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::writeInt */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_writeInt00
static int tolua_server_LDataPack_writeInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  int v = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LDataPack::writeInt(p,v);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'writeInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::writeUInt */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_writeUInt00
static int tolua_server_LDataPack_writeUInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  unsigned int v = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   LDataPack::writeUInt(p,v);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'writeUInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::writeUint64 */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_writeUint6400
static int tolua_server_LDataPack_writeUint6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  double v = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   LDataPack::writeUint64(p,v);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'writeUint64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::writeInt64 */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_writeInt6400
static int tolua_server_LDataPack_writeInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  double v = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   LDataPack::writeInt64(p,v);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'writeInt64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::writeInt64I */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_writeInt64I00
static int tolua_server_LDataPack_writeInt64I00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  long long v = ((long long)  tolua_tonumber(tolua_S,2,0));
  {
   LDataPack::writeInt64I(p,v);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'writeInt64I'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::writeDouble */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_writeDouble00
static int tolua_server_LDataPack_writeDouble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  double v = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   LDataPack::writeDouble(p,v);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'writeDouble'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::writeUserItem */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_writeUserItem00
static int tolua_server_LDataPack_writeUserItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  void* item = ((void*)  tolua_touserdata(tolua_S,2,0));
  {
   LDataPack::writeUserItem(p,item);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'writeUserItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::writeData */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_writeData00
static int tolua_server_LDataPack_writeData00(lua_State* tolua_S)
{
	return LDataPack::writeData(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::writePacket */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_writePacket00
static int tolua_server_LDataPack_writePacket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  void* dp = ((void*)  tolua_touserdata(tolua_S,2,0));
  bool reset = ((bool) (tolua_toboolean(tolua_S,3,true)!=0));
  {
   LDataPack::writePacket(p,dp,reset);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'writePacket'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LDataPack::writeProto */
#ifndef TOLUA_DISABLE_tolua_server_LDataPack_writeProto00
static int tolua_server_LDataPack_writeProto00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* p = ((void*)  tolua_touserdata(tolua_S,1,0));
  void* proto = ((void*)  tolua_touserdata(tolua_S,2,0));
  {
   LDataPack::writeProto(p,proto);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'writeProto'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::getRankingItemList */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_getRankingItemList00
static int tolua_server_Ranking_getRankingItemList00(lua_State* tolua_S)
{
	return Ranking::getRankingItemList(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::addRef */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_addRef00
static int tolua_server_Ranking_addRef00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Ranking::addRef(pRank);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addRef'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::release */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_release00
static int tolua_server_Ranking_release00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Ranking::release(pRank);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'release'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::getRef */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_getRef00
static int tolua_server_Ranking_getRef00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  Ranking::getRef(pRank);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRef'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::getRanking */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_getRanking00
static int tolua_server_Ranking_getRanking00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* sName = ((char*)  tolua_tostring(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  Ranking::getRanking(sName);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRanking'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::add */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_add00
static int tolua_server_Ranking_add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* sName = ((char*)  tolua_tostring(tolua_S,1,0));
  int nMax = ((int)  tolua_tonumber(tolua_S,2,0));
  int boDisplay = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   void* tolua_ret = (void*)  Ranking::add(sName,nMax,boDisplay);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::load */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_load00
static int tolua_server_Ranking_load00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  char* sFile = ((char*)  tolua_tostring(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  Ranking::load(pRank,sFile);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'load'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::save */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_save00
static int tolua_server_Ranking_save00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  char* sFile = ((char*)  tolua_tostring(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  Ranking::save(pRank,sFile);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'save'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::addColumn */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_addColumn00
static int tolua_server_Ranking_addColumn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  char* sTitle = ((char*)  tolua_tostring(tolua_S,2,0));
  int nIndex = ((int)  tolua_tonumber(tolua_S,3,-1));
  {
   Ranking::addColumn(pRank,sTitle,nIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addColumn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::getColumnCount */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_getColumnCount00
static int tolua_server_Ranking_getColumnCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  Ranking::getColumnCount(pRank);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getColumnCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::setColumnTitle */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_setColumnTitle00
static int tolua_server_Ranking_setColumnTitle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  char* sTitle = ((char*)  tolua_tostring(tolua_S,2,0));
  int nIndex = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   Ranking::setColumnTitle(pRank,sTitle,nIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setColumnTitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::addItem */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_addItem00
static int tolua_server_Ranking_addItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  int nId = ((int)  tolua_tonumber(tolua_S,2,0));
  int nPoint = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   void* tolua_ret = (void*)  Ranking::addItem(pRank,nId,nPoint);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::tryAddItem */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_tryAddItem00
static int tolua_server_Ranking_tryAddItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  int nId = ((int)  tolua_tonumber(tolua_S,2,0));
  int nPoint = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   void* tolua_ret = (void*)  Ranking::tryAddItem(pRank,nId,nPoint);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'tryAddItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::getItemIndexFromId */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_getItemIndexFromId00
static int tolua_server_Ranking_getItemIndexFromId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  int nId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  Ranking::getItemIndexFromId(pRank,nId);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getItemIndexFromId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::getItemPtrFromId */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_getItemPtrFromId00
static int tolua_server_Ranking_getItemPtrFromId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  int nId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   void* tolua_ret = (void*)  Ranking::getItemPtrFromId(pRank,nId);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getItemPtrFromId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::updateItem */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_updateItem00
static int tolua_server_Ranking_updateItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  int nId = ((int)  tolua_tonumber(tolua_S,2,0));
  int nPoint = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   void* tolua_ret = (void*)  Ranking::updateItem(pRank,nId,nPoint);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'updateItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::setItem */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_setItem00
static int tolua_server_Ranking_setItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  int nId = ((int)  tolua_tonumber(tolua_S,2,0));
  int nPoint = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   void* tolua_ret = (void*)  Ranking::setItem(pRank,nId,nPoint);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::setColumnDisplay */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_setColumnDisplay00
static int tolua_server_Ranking_setColumnDisplay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  int nIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  int boDisplay = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   Ranking::setColumnDisplay(pRank,nIndex,boDisplay);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setColumnDisplay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::setSub */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_setSub00
static int tolua_server_Ranking_setSub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRankItem = ((void*)  tolua_touserdata(tolua_S,1,0));
  int nIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  char* sData = ((char*)  tolua_tostring(tolua_S,3,0));
  {
   Ranking::setSub(pRankItem,nIndex,sData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setSub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::setSubInt */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_setSubInt00
static int tolua_server_Ranking_setSubInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* rankItem = ((void*)  tolua_touserdata(tolua_S,1,0));
  int nIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  int data = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   Ranking::setSubInt(rankItem,nIndex,data);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setSubInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::updateSubInt */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_updateSubInt00
static int tolua_server_Ranking_updateSubInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* rankItem = ((void*)  tolua_touserdata(tolua_S,1,0));
  int nIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  int val = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   int tolua_ret = (int)  Ranking::updateSubInt(rankItem,nIndex,val);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'updateSubInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::removeRanking */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_removeRanking00
static int tolua_server_Ranking_removeRanking00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* sName = ((char*)  tolua_tostring(tolua_S,1,0));
  {
   Ranking::removeRanking(sName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'removeRanking'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::getRankItemCount */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_getRankItemCount00
static int tolua_server_Ranking_getRankItemCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  Ranking::getRankItemCount(pRank);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRankItemCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::getPoint */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_getPoint00
static int tolua_server_Ranking_getPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRankItem = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  Ranking::getPoint(pRankItem);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::getId */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_getId00
static int tolua_server_Ranking_getId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRankItem = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  Ranking::getId(pRankItem);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::getIndexFromPtr */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_getIndexFromPtr00
static int tolua_server_Ranking_getIndexFromPtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRankItem = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  Ranking::getIndexFromPtr(pRankItem);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getIndexFromPtr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::getSub */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_getSub00
static int tolua_server_Ranking_getSub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRankItem = ((void*)  tolua_touserdata(tolua_S,1,0));
  int nIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   const char* tolua_ret = (const char*)  Ranking::getSub(pRankItem,nIndex);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getSub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::getSubInt */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_getSubInt00
static int tolua_server_Ranking_getSubInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRankItem = ((void*)  tolua_touserdata(tolua_S,1,0));
  int nIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  Ranking::getSubInt(pRankItem,nIndex);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getSubInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::clearRanking */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_clearRanking00
static int tolua_server_Ranking_clearRanking00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   Ranking::clearRanking(pRank);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'clearRanking'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::getItemFromIndex */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_getItemFromIndex00
static int tolua_server_Ranking_getItemFromIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  int nIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   void* tolua_ret = (void*)  Ranking::getItemFromIndex(pRank,nIndex);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getItemFromIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::setDisplayName */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_setDisplayName00
static int tolua_server_Ranking_setDisplayName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  const char* sName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   Ranking::setDisplayName(pRank,sName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setDisplayName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::setIdTitle */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_setIdTitle00
static int tolua_server_Ranking_setIdTitle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  const char* sName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   Ranking::setIdTitle(pRank,sName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setIdTitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::setPointTitle */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_setPointTitle00
static int tolua_server_Ranking_setPointTitle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  const char* sName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   Ranking::setPointTitle(pRank,sName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setPointTitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::removeId */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_removeId00
static int tolua_server_Ranking_removeId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Ranking::removeId(pRank,id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'removeId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::setAutoSave */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_setAutoSave00
static int tolua_server_Ranking_setAutoSave00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* pRank = ((void*)  tolua_touserdata(tolua_S,1,0));
  bool isAuto = ((bool) (tolua_toboolean(tolua_S,2,0)!=0));
  {
   Ranking::setAutoSave(pRank,isAuto);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setAutoSave'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::swapEqualItem */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_swapEqualItem00
static int tolua_server_Ranking_swapEqualItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* rank = ((void*)  tolua_touserdata(tolua_S,1,0));
  void* item1 = ((void*)  tolua_touserdata(tolua_S,2,0));
  void* item2 = ((void*)  tolua_touserdata(tolua_S,3,0));
  {
   Ranking::swapEqualItem(rank,item1,item2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'swapEqualItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::getLianfuRankData */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_getLianfuRankData00
static int tolua_server_Ranking_getLianfuRankData00(lua_State* tolua_S)
{
	return Ranking::getLianfuRankData(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::getStaticRank */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_getStaticRank00
static int tolua_server_Ranking_getStaticRank00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int rankId = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  Ranking::getStaticRank(rankId);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getStaticRank'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::getSRIndexFromId */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_getSRIndexFromId00
static int tolua_server_Ranking_getSRIndexFromId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* rank = ((void*)  tolua_touserdata(tolua_S,1,0));
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  Ranking::getSRIndexFromId(rank,id);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getSRIndexFromId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::getSRIdFromIdx */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_getSRIdFromIdx00
static int tolua_server_Ranking_getSRIdFromIdx00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* rank = ((void*)  tolua_touserdata(tolua_S,1,0));
  int idx = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  Ranking::getSRIdFromIdx(rank,idx);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getSRIdFromIdx'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::updateStaticRank */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_updateStaticRank00
static int tolua_server_Ranking_updateStaticRank00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Ranking::updateStaticRank();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'updateStaticRank'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::getRankName */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_getRankName00
static int tolua_server_Ranking_getRankName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* rank = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  Ranking::getRankName(rank);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getRankName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Ranking::setRankName */
#ifndef TOLUA_DISABLE_tolua_server_Ranking_setRankName00
static int tolua_server_Ranking_setRankName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* rank = ((void*)  tolua_touserdata(tolua_S,1,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   Ranking::setRankName(rank,name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setRankName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getStaticVar */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getStaticVar00
static int tolua_server_LGuild_getStaticVar00(lua_State* tolua_S)
{
	return LGuild::getStaticVar(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::nameHasUsed */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_nameHasUsed00
static int tolua_server_LGuild_nameHasUsed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  LGuild::nameHasUsed(name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'nameHasUsed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::createGuild */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_createGuild00
static int tolua_server_LGuild_createGuild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,1,0));
  void* actor = ((void*)  tolua_touserdata(tolua_S,2,0));
  {
   void* tolua_ret = (void*)  LGuild::createGuild(name,actor);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'createGuild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::deleteGuild */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_deleteGuild00
static int tolua_server_LGuild_deleteGuild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  const char* reason = ((const char*)  tolua_tostring(tolua_S,2,""));
  {
   LGuild::deleteGuild(guild,reason);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'deleteGuild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::deleteMember */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_deleteMember00
static int tolua_server_LGuild_deleteMember00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  int actorId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LGuild::deleteMember(guild,actorId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'deleteMember'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::addMember */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_addMember00
static int tolua_server_LGuild_addMember00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  void* actor = ((void*)  tolua_touserdata(tolua_S,2,0));
  int pos = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LGuild::addMember(guild,actor,pos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addMember'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getGuildById */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getGuildById00
static int tolua_server_LGuild_getGuildById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int guildId = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LGuild::getGuildById(guildId);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getGuildById'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getGuildByName */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getGuildByName00
static int tolua_server_LGuild_getGuildByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LGuild::getGuildByName(name);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getGuildByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getGuildName */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getGuildName00
static int tolua_server_LGuild_getGuildName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  LGuild::getGuildName(guild);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getGuildName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getGuildMemberCount */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getGuildMemberCount00
static int tolua_server_LGuild_getGuildMemberCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LGuild::getGuildMemberCount(guild);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getGuildMemberCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getGuildId */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getGuildId00
static int tolua_server_LGuild_getGuildId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LGuild::getGuildId(guild);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getGuildId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::setUpdate */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_setUpdate00
static int tolua_server_LGuild_setUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LGuild::setUpdate(guild);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getLeaderId */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getLeaderId00
static int tolua_server_LGuild_getLeaderId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LGuild::getLeaderId(guild);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getLeaderId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getMemberInfo */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getMemberInfo00
static int tolua_server_LGuild_getMemberInfo00(lua_State* tolua_S)
{
	return LGuild::getMemberInfo(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::isMember */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_isMember00
static int tolua_server_LGuild_isMember00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  int actor_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  LGuild::isMember(guild,actor_id);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'isMember'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getAutoApprove */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getAutoApprove00
static int tolua_server_LGuild_getAutoApprove00(lua_State* tolua_S)
{
	return LGuild::getAutoApprove(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::setAutoApprove */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_setAutoApprove00
static int tolua_server_LGuild_setAutoApprove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  unsigned char bauto = ((unsigned char)  tolua_tonumber(tolua_S,2,0));
  int need_fight = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LGuild::setAutoApprove(guild,bauto,need_fight);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setAutoApprove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getGuildList */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getGuildList00
static int tolua_server_LGuild_getGuildList00(lua_State* tolua_S)
{
	return LGuild::getGuildList(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getGuildPosMemberCount */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getGuildPosMemberCount00
static int tolua_server_LGuild_getGuildPosMemberCount00(lua_State* tolua_S)
{
	return LGuild::getGuildPosMemberCount(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getMemberIdList */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getMemberIdList00
static int tolua_server_LGuild_getMemberIdList00(lua_State* tolua_S)
{
	return LGuild::getMemberIdList(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getJoinMsgIdList */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getJoinMsgIdList00
static int tolua_server_LGuild_getJoinMsgIdList00(lua_State* tolua_S)
{
	return LGuild::getJoinMsgIdList(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::postJoinMsg */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_postJoinMsg00
static int tolua_server_LGuild_postJoinMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  void* actor = ((void*)  tolua_touserdata(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  LGuild::postJoinMsg(guild,actor);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'postJoinMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::removeJoinMsg */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_removeJoinMsg00
static int tolua_server_LGuild_removeJoinMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  int actorId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  LGuild::removeJoinMsg(guild,actorId);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'removeJoinMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getJoinMsg */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getJoinMsg00
static int tolua_server_LGuild_getJoinMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  int actorId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  LGuild::getJoinMsg(guild,actorId);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getJoinMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getGuildPos */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getGuildPos00
static int tolua_server_LGuild_getGuildPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  int actorId = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  LGuild::getGuildPos(guild,actorId);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getGuildPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::changeGuildPos */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_changeGuildPos00
static int tolua_server_LGuild_changeGuildPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  int actorId = ((int)  tolua_tonumber(tolua_S,2,0));
  int pos = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  LGuild::changeGuildPos(guild,actorId,pos);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'changeGuildPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::updateGuildPos */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_updateGuildPos00
static int tolua_server_LGuild_updateGuildPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LGuild::updateGuildPos(guild);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'updateGuildPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getLargestContribution */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getLargestContribution00
static int tolua_server_LGuild_getLargestContribution00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LGuild::getLargestContribution(guild);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getLargestContribution'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::addGuildLog */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_addGuildLog00
static int tolua_server_LGuild_addGuildLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  unsigned char tp = ((unsigned char)  tolua_tonumber(tolua_S,2,0));
  const char* name1 = ((const char*)  tolua_tostring(tolua_S,3,""));
  const char* name2 = ((const char*)  tolua_tostring(tolua_S,4,""));
  int param1 = ((int)  tolua_tonumber(tolua_S,5,0));
  int param2 = ((int)  tolua_tonumber(tolua_S,6,0));
  int param3 = ((int)  tolua_tonumber(tolua_S,7,0));
  {
   LGuild::addGuildLog(guild,tp,name1,name2,param1,param2,param3);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addGuildLog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::broadcastData */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_broadcastData00
static int tolua_server_LGuild_broadcastData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  void* dp = ((void*)  tolua_touserdata(tolua_S,2,0));
  {
   LGuild::broadcastData(guild,dp);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'broadcastData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::setGuildLevel */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_setGuildLevel00
static int tolua_server_LGuild_setGuildLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  int level = ((int)  tolua_tonumber(tolua_S,2,0));
  int levelupTime = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LGuild::setGuildLevel(guild,level,levelupTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setGuildLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::setGuildAffairLevel */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_setGuildAffairLevel00
static int tolua_server_LGuild_setGuildAffairLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  int level = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LGuild::setGuildAffairLevel(guild,level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setGuildAffairLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::updateGuildRank */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_updateGuildRank00
static int tolua_server_LGuild_updateGuildRank00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LGuild::updateGuildRank(guild);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'updateGuildRank'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getGuildLevel */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getGuildLevel00
static int tolua_server_LGuild_getGuildLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LGuild::getGuildLevel(guild);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getGuildLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::addChatLog */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_addChatLog00
static int tolua_server_LGuild_addChatLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* content = ((const char*)  tolua_tostring(tolua_S,3,0));
  void* actor = ((void*)  tolua_touserdata(tolua_S,4,0));
  {
   LGuild::addChatLog(guild,type,content,actor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addChatLog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::writeChatLog */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_writeChatLog00
static int tolua_server_LGuild_writeChatLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  void* pack = ((void*)  tolua_touserdata(tolua_S,2,0));
  {
   LGuild::writeChatLog(guild,pack);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'writeChatLog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::clearChatLog */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_clearChatLog00
static int tolua_server_LGuild_clearChatLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LGuild::clearChatLog(guild);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'clearChatLog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::resetTodayContrib */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_resetTodayContrib00
static int tolua_server_LGuild_resetTodayContrib00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   LGuild::resetTodayContrib(guild);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'resetTodayContrib'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::addStoreLog */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_addStoreLog00
static int tolua_server_LGuild_addStoreLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  void* actor = ((void*)  tolua_touserdata(tolua_S,2,0));
  int item_id = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LGuild::addStoreLog(guild,actor,item_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'addStoreLog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::writeStoreLog */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_writeStoreLog00
static int tolua_server_LGuild_writeStoreLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  unsigned int last_time = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  void* pack = ((void*)  tolua_touserdata(tolua_S,3,0));
  {
   LGuild::writeStoreLog(guild,last_time,pack);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'writeStoreLog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getOnlineActor */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getOnlineActor00
static int tolua_server_LGuild_getOnlineActor00(lua_State* tolua_S)
{
	return LGuild::getOnlineActor(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getLeaderName */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getLeaderName00
static int tolua_server_LGuild_getLeaderName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guile = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  LGuild::getLeaderName(guile);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getLeaderName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getOnlineLeaderActor */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getOnlineLeaderActor00
static int tolua_server_LGuild_getOnlineLeaderActor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guile = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  LGuild::getOnlineLeaderActor(guile);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getOnlineLeaderActor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::GetMemberTotalGx */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_GetMemberTotalGx00
static int tolua_server_LGuild_GetMemberTotalGx00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guild = ((void*)  tolua_touserdata(tolua_S,1,0));
  int actor_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   int tolua_ret = (int)  LGuild::GetMemberTotalGx(guild,actor_id);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetMemberTotalGx'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::getChangeNameCount */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_getChangeNameCount00
static int tolua_server_LGuild_getChangeNameCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guile = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   int tolua_ret = (int)  LGuild::getChangeNameCount(guile);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getChangeNameCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::setChangeNameCount */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_setChangeNameCount00
static int tolua_server_LGuild_setChangeNameCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guile = ((void*)  tolua_touserdata(tolua_S,1,0));
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   LGuild::setChangeNameCount(guile,num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'setChangeNameCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LGuild::changeName */
#ifndef TOLUA_DISABLE_tolua_server_LGuild_changeName00
static int tolua_server_LGuild_changeName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* guile = ((void*)  tolua_touserdata(tolua_S,1,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  LGuild::changeName(guile,name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'changeName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: account_id of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_account_id
static int tolua_get_ActorBasicData_unsigned_account_id(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'account_id'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->account_id);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: account_id of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_account_id
static int tolua_set_ActorBasicData_unsigned_account_id(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'account_id'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->account_id = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: account_name of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_account_name
static int tolua_get_ActorBasicData_account_name(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'account_name'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->account_name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: account_name of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_account_name
static int tolua_set_ActorBasicData_account_name(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'account_name'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy(self->account_name,tolua_tostring(tolua_S,2,0),ACCOUNT_LENGTH-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: actor_id of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_actor_id
static int tolua_get_ActorBasicData_actor_id(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'actor_id'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->actor_id);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: actor_id of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_actor_id
static int tolua_set_ActorBasicData_actor_id(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'actor_id'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->actor_id = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: actor_name of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_actor_name
static int tolua_get_ActorBasicData_actor_name(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'actor_name'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->actor_name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: actor_name of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_actor_name
static int tolua_set_ActorBasicData_actor_name(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'actor_name'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy(self->actor_name,tolua_tostring(tolua_S,2,0),ACTOR_NAME_BUFF_LENGTH-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: server_idnex of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_server_idnex
static int tolua_get_ActorBasicData_unsigned_server_idnex(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'server_idnex'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->server_idnex);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: server_idnex of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_server_idnex
static int tolua_set_ActorBasicData_unsigned_server_idnex(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'server_idnex'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->server_idnex = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: job of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_job
static int tolua_get_ActorBasicData_unsigned_job(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'job'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->job);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: job of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_job
static int tolua_set_ActorBasicData_unsigned_job(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'job'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->job = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sex of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_sex
static int tolua_get_ActorBasicData_unsigned_sex(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'sex'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->sex);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sex of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_sex
static int tolua_set_ActorBasicData_unsigned_sex(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'sex'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sex = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: headimage of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_headimage
static int tolua_get_ActorBasicData_unsigned_headimage(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'headimage'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->headimage);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: headimage of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_headimage
static int tolua_set_ActorBasicData_unsigned_headimage(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'headimage'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->headimage = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: level of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_level
static int tolua_get_ActorBasicData_unsigned_level(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'level'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->level);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: level of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_level
static int tolua_set_ActorBasicData_unsigned_level(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'level'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->level = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: exp of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_exp
static int tolua_get_ActorBasicData_unsigned_exp(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'exp'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->exp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: exp of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_exp
static int tolua_set_ActorBasicData_unsigned_exp(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'exp'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->exp = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fb_uid of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_fb_uid
static int tolua_get_ActorBasicData_fb_uid(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'fb_uid'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->fb_uid);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fb_uid of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_fb_uid
static int tolua_set_ActorBasicData_fb_uid(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'fb_uid'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fb_uid = ((long long int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fb_scene_id of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_fb_scene_id
static int tolua_get_ActorBasicData_unsigned_fb_scene_id(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'fb_scene_id'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->fb_scene_id);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fb_scene_id of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_fb_scene_id
static int tolua_set_ActorBasicData_unsigned_fb_scene_id(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'fb_scene_id'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fb_scene_id = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: create_time of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_create_time
static int tolua_get_ActorBasicData_unsigned_create_time(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'create_time'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->create_time);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: create_time of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_create_time
static int tolua_set_ActorBasicData_unsigned_create_time(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'create_time'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->create_time = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: last_online_time of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_last_online_time
static int tolua_get_ActorBasicData_unsigned_last_online_time(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'last_online_time'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->last_online_time);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: last_online_time of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_last_online_time
static int tolua_set_ActorBasicData_unsigned_last_online_time(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'last_online_time'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->last_online_time = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: last_login_ip of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_last_login_ip
static int tolua_get_ActorBasicData_unsigned_last_login_ip(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'last_login_ip'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->last_login_ip);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: last_login_ip of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_last_login_ip
static int tolua_set_ActorBasicData_unsigned_last_login_ip(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'last_login_ip'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->last_login_ip = ((unsigned long long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: total_online of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_total_online
static int tolua_get_ActorBasicData_unsigned_total_online(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'total_online'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->total_online);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: total_online of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_total_online
static int tolua_set_ActorBasicData_unsigned_total_online(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'total_online'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->total_online = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: daily_online of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_daily_online
static int tolua_get_ActorBasicData_unsigned_daily_online(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'daily_online'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->daily_online);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: daily_online of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_daily_online
static int tolua_set_ActorBasicData_unsigned_daily_online(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'daily_online'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->daily_online = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bag_grid of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_bag_grid
static int tolua_get_ActorBasicData_unsigned_bag_grid(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'bag_grid'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->bag_grid);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bag_grid of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_bag_grid
static int tolua_set_ActorBasicData_unsigned_bag_grid(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'bag_grid'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bag_grid = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: gold of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_gold
static int tolua_get_ActorBasicData_gold(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'gold'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->gold);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: gold of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_gold
static int tolua_set_ActorBasicData_gold(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'gold'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->gold = ((long long int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: yuanbao of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_yuanbao
static int tolua_get_ActorBasicData_yuanbao(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'yuanbao'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->yuanbao);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: yuanbao of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_yuanbao
static int tolua_set_ActorBasicData_yuanbao(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'yuanbao'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->yuanbao = ((long long int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: total_power of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_total_power
static int tolua_get_ActorBasicData_total_power(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'total_power'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->total_power);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: total_power of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_total_power
static int tolua_set_ActorBasicData_total_power(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'total_power'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->total_power = ((long long int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rank_power of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_rank_power
static int tolua_get_ActorBasicData_rank_power(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'rank_power'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->rank_power);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: rank_power of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_rank_power
static int tolua_set_ActorBasicData_rank_power(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'rank_power'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->rank_power = ((long long int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: recharge of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_recharge
static int tolua_get_ActorBasicData_unsigned_recharge(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'recharge'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->recharge);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: recharge of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_recharge
static int tolua_set_ActorBasicData_unsigned_recharge(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'recharge'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->recharge = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: paid of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_paid
static int tolua_get_ActorBasicData_unsigned_paid(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'paid'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->paid);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: paid of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_paid
static int tolua_set_ActorBasicData_unsigned_paid(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'paid'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->paid = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: chapter_level of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_chapter_level
static int tolua_get_ActorBasicData_unsigned_chapter_level(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'chapter_level'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->chapter_level);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: chapter_level of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_chapter_level
static int tolua_set_ActorBasicData_unsigned_chapter_level(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'chapter_level'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->chapter_level = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: vip_level of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_vip_level
static int tolua_get_ActorBasicData_unsigned_vip_level(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'vip_level'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->vip_level);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: vip_level of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_vip_level
static int tolua_set_ActorBasicData_unsigned_vip_level(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'vip_level'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->vip_level = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: essence of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_essence
static int tolua_get_ActorBasicData_essence(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'essence'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->essence);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: essence of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_essence
static int tolua_set_ActorBasicData_essence(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'essence'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->essence = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: zhuansheng_lv of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_zhuansheng_lv
static int tolua_get_ActorBasicData_zhuansheng_lv(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'zhuansheng_lv'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->zhuansheng_lv);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: zhuansheng_lv of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_zhuansheng_lv
static int tolua_set_ActorBasicData_zhuansheng_lv(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'zhuansheng_lv'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->zhuansheng_lv = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: zhuansheng_exp of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_zhuansheng_exp
static int tolua_get_ActorBasicData_zhuansheng_exp(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'zhuansheng_exp'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->zhuansheng_exp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: zhuansheng_exp of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_zhuansheng_exp
static int tolua_set_ActorBasicData_zhuansheng_exp(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'zhuansheng_exp'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->zhuansheng_exp = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: monthcard of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_monthcard
static int tolua_get_ActorBasicData_unsigned_monthcard(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'monthcard'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->monthcard);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: monthcard of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_monthcard
static int tolua_set_ActorBasicData_unsigned_monthcard(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'monthcard'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->monthcard = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: tianti_level of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_tianti_level
static int tolua_get_ActorBasicData_tianti_level(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'tianti_level'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->tianti_level);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: tianti_level of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_tianti_level
static int tolua_set_ActorBasicData_tianti_level(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'tianti_level'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->tianti_level = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: tianti_dan of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_tianti_dan
static int tolua_get_ActorBasicData_tianti_dan(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'tianti_dan'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->tianti_dan);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: tianti_dan of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_tianti_dan
static int tolua_set_ActorBasicData_tianti_dan(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'tianti_dan'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->tianti_dan = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: tianti_win_count of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_tianti_win_count
static int tolua_get_ActorBasicData_tianti_win_count(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'tianti_win_count'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->tianti_win_count);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: tianti_win_count of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_tianti_win_count
static int tolua_set_ActorBasicData_tianti_win_count(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'tianti_win_count'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->tianti_win_count = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: tianti_week_refres of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_tianti_week_refres
static int tolua_get_ActorBasicData_tianti_week_refres(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'tianti_week_refres'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->tianti_week_refres);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: tianti_week_refres of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_tianti_week_refres
static int tolua_set_ActorBasicData_tianti_week_refres(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'tianti_week_refres'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->tianti_week_refres = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: total_wing_power of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_total_wing_power
static int tolua_get_ActorBasicData_total_wing_power(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'total_wing_power'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->total_wing_power);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: total_wing_power of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_total_wing_power
static int tolua_set_ActorBasicData_total_wing_power(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'total_wing_power'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->total_wing_power = ((long long int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: warrior_power of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_warrior_power
static int tolua_get_ActorBasicData_warrior_power(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'warrior_power'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->warrior_power);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: warrior_power of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_warrior_power
static int tolua_set_ActorBasicData_warrior_power(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'warrior_power'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->warrior_power = ((long long int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mage_power of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_mage_power
static int tolua_get_ActorBasicData_mage_power(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'mage_power'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->mage_power);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mage_power of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_mage_power
static int tolua_set_ActorBasicData_mage_power(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'mage_power'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mage_power = ((long long int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: taoistpriest_power of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_taoistpriest_power
static int tolua_get_ActorBasicData_taoistpriest_power(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'taoistpriest_power'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->taoistpriest_power);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: taoistpriest_power of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_taoistpriest_power
static int tolua_set_ActorBasicData_taoistpriest_power(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'taoistpriest_power'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->taoistpriest_power = ((long long int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: train_level of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_train_level
static int tolua_get_ActorBasicData_train_level(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'train_level'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->train_level);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: train_level of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_train_level
static int tolua_set_ActorBasicData_train_level(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'train_level'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->train_level = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: train_exp of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_train_exp
static int tolua_get_ActorBasicData_train_exp(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'train_exp'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->train_exp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: train_exp of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_train_exp
static int tolua_set_ActorBasicData_train_exp(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'train_exp'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->train_exp = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: total_stone_level of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_total_stone_level
static int tolua_get_ActorBasicData_total_stone_level(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'total_stone_level'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->total_stone_level);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: total_stone_level of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_total_stone_level
static int tolua_set_ActorBasicData_total_stone_level(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'total_stone_level'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->total_stone_level = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: total_zhuling_level of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_total_zhuling_level
static int tolua_get_ActorBasicData_total_zhuling_level(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'total_zhuling_level'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->total_zhuling_level);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: total_zhuling_level of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_total_zhuling_level
static int tolua_set_ActorBasicData_total_zhuling_level(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'total_zhuling_level'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->total_zhuling_level = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: guild_id_ of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_guild_id_
static int tolua_get_ActorBasicData_guild_id_(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'guild_id_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->guild_id_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: guild_id_ of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_guild_id_
static int tolua_set_ActorBasicData_guild_id_(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'guild_id_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->guild_id_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: guild_name_ of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_guild_name_
static int tolua_get_ActorBasicData_guild_name_(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'guild_name_'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->guild_name_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: guild_name_ of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_guild_name_
static int tolua_set_ActorBasicData_guild_name_(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'guild_name_'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy(self->guild_name_,tolua_tostring(tolua_S,2,0),32-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: zhan_ling_star of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_zhan_ling_star
static int tolua_get_ActorBasicData_zhan_ling_star(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'zhan_ling_star'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->zhan_ling_star);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: zhan_ling_star of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_zhan_ling_star
static int tolua_set_ActorBasicData_zhan_ling_star(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'zhan_ling_star'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->zhan_ling_star = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: zhan_ling_stage of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_zhan_ling_stage
static int tolua_get_ActorBasicData_zhan_ling_stage(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'zhan_ling_stage'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->zhan_ling_stage);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: zhan_ling_stage of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_zhan_ling_stage
static int tolua_set_ActorBasicData_zhan_ling_stage(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'zhan_ling_stage'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->zhan_ling_stage = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: total_loongsoul_level of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_total_loongsoul_level
static int tolua_get_ActorBasicData_total_loongsoul_level(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'total_loongsoul_level'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->total_loongsoul_level);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: total_loongsoul_level of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_total_loongsoul_level
static int tolua_set_ActorBasicData_total_loongsoul_level(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'total_loongsoul_level'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->total_loongsoul_level = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: prestige_exp of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_prestige_exp
static int tolua_get_ActorBasicData_prestige_exp(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'prestige_exp'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->prestige_exp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: prestige_exp of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_prestige_exp
static int tolua_set_ActorBasicData_prestige_exp(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'prestige_exp'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->prestige_exp = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: feats of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_feats
static int tolua_get_ActorBasicData_feats(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'feats'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->feats);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: feats of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_feats
static int tolua_set_ActorBasicData_feats(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'feats'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->feats = ((long long int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ex_ring_lv of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_server_ActorBasicData_ex_ring_lv
static int tolua_get_server_ActorBasicData_ex_ring_lv(lua_State* tolua_S)
{
 int tolua_index;
  ActorBasicData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ActorBasicData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=8)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->ex_ring_lv[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ex_ring_lv of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_server_ActorBasicData_ex_ring_lv
static int tolua_set_server_ActorBasicData_ex_ring_lv(lua_State* tolua_S)
{
 int tolua_index;
  ActorBasicData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ActorBasicData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=8)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
  self->ex_ring_lv[tolua_index] = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: shatter of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_shatter
static int tolua_get_ActorBasicData_shatter(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'shatter'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->shatter);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: shatter of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_shatter
static int tolua_set_ActorBasicData_shatter(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'shatter'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->shatter = ((long long int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: spcshatter of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_spcshatter
static int tolua_get_ActorBasicData_spcshatter(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'spcshatter'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->spcshatter);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: spcshatter of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_spcshatter
static int tolua_set_ActorBasicData_spcshatter(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'spcshatter'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->spcshatter = ((long long int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: knighthood_lv of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_knighthood_lv
static int tolua_get_ActorBasicData_unsigned_knighthood_lv(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'knighthood_lv'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->knighthood_lv);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: knighthood_lv of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_knighthood_lv
static int tolua_set_ActorBasicData_unsigned_knighthood_lv(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'knighthood_lv'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->knighthood_lv = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: togeatter of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_togeatter
static int tolua_get_ActorBasicData_togeatter(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'togeatter'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->togeatter);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: togeatter of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_togeatter
static int tolua_set_ActorBasicData_togeatter(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'togeatter'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->togeatter = ((long long int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: total_wing_lv of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_total_wing_lv
static int tolua_get_ActorBasicData_total_wing_lv(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'total_wing_lv'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->total_wing_lv);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: total_wing_lv of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_total_wing_lv
static int tolua_set_ActorBasicData_total_wing_lv(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'total_wing_lv'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->total_wing_lv = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: total_tujian_power of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_total_tujian_power
static int tolua_get_ActorBasicData_total_tujian_power(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'total_tujian_power'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->total_tujian_power);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: total_tujian_power of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_total_tujian_power
static int tolua_set_ActorBasicData_total_tujian_power(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'total_tujian_power'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->total_tujian_power = ((long long int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: total_equip_power of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_total_equip_power
static int tolua_get_ActorBasicData_total_equip_power(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'total_equip_power'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->total_equip_power);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: total_equip_power of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_total_equip_power
static int tolua_set_ActorBasicData_total_equip_power(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'total_equip_power'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->total_equip_power = ((long long int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: togeatterhigh of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_togeatterhigh
static int tolua_get_ActorBasicData_togeatterhigh(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'togeatterhigh'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->togeatterhigh);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: togeatterhigh of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_togeatterhigh
static int tolua_set_ActorBasicData_togeatterhigh(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'togeatterhigh'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->togeatterhigh = ((long long int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: privilege_monthcard of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_unsigned_privilege_monthcard
static int tolua_get_ActorBasicData_unsigned_privilege_monthcard(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'privilege_monthcard'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->privilege_monthcard);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: privilege_monthcard of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_unsigned_privilege_monthcard
static int tolua_set_ActorBasicData_unsigned_privilege_monthcard(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'privilege_monthcard'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->privilege_monthcard = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: reincarnate_lv of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_reincarnate_lv
static int tolua_get_ActorBasicData_reincarnate_lv(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'reincarnate_lv'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->reincarnate_lv);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: reincarnate_lv of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_reincarnate_lv
static int tolua_set_ActorBasicData_reincarnate_lv(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'reincarnate_lv'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->reincarnate_lv = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: reincarnate_exp of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_reincarnate_exp
static int tolua_get_ActorBasicData_reincarnate_exp(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'reincarnate_exp'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->reincarnate_exp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: reincarnate_exp of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_reincarnate_exp
static int tolua_set_ActorBasicData_reincarnate_exp(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'reincarnate_exp'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->reincarnate_exp = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: field_chapter_level of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_field_chapter_level
static int tolua_get_ActorBasicData_field_chapter_level(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'field_chapter_level'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->field_chapter_level);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: field_chapter_level of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_field_chapter_level
static int tolua_set_ActorBasicData_field_chapter_level(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'field_chapter_level'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->field_chapter_level = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: field_chapter_progress of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_field_chapter_progress
static int tolua_get_ActorBasicData_field_chapter_progress(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'field_chapter_progress'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->field_chapter_progress);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: field_chapter_progress of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_field_chapter_progress
static int tolua_set_ActorBasicData_field_chapter_progress(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'field_chapter_progress'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->field_chapter_progress = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: field_pk_mode of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_field_pk_mode
static int tolua_get_ActorBasicData_field_pk_mode(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'field_pk_mode'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->field_pk_mode);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: field_pk_mode of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_field_pk_mode
static int tolua_set_ActorBasicData_field_pk_mode(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'field_pk_mode'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->field_pk_mode = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: field_last_fuben_id of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_field_last_fuben_id
static int tolua_get_ActorBasicData_field_last_fuben_id(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'field_last_fuben_id'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->field_last_fuben_id);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: field_last_fuben_id of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_field_last_fuben_id
static int tolua_set_ActorBasicData_field_last_fuben_id(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'field_last_fuben_id'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->field_last_fuben_id = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: field_last_pos_x of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_field_last_pos_x
static int tolua_get_ActorBasicData_field_last_pos_x(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'field_last_pos_x'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->field_last_pos_x);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: field_last_pos_x of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_field_last_pos_x
static int tolua_set_ActorBasicData_field_last_pos_x(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'field_last_pos_x'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->field_last_pos_x = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: field_last_pos_y of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_get_ActorBasicData_field_last_pos_y
static int tolua_get_ActorBasicData_field_last_pos_y(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'field_last_pos_y'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->field_last_pos_y);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: field_last_pos_y of class  ActorBasicData */
#ifndef TOLUA_DISABLE_tolua_set_ActorBasicData_field_last_pos_y
static int tolua_set_ActorBasicData_field_last_pos_y(lua_State* tolua_S)
{
  ActorBasicData* self = (ActorBasicData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'field_last_pos_y'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->field_last_pos_y = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* function: toActorBasicData */
#ifndef TOLUA_DISABLE_tolua_server_toActorBasicData00
static int tolua_server_toActorBasicData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* data = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   ActorBasicData* tolua_ret = (ActorBasicData*)  toActorBasicData(data);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ActorBasicData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'toActorBasicData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: skill_level of class  SkillsData */
#ifndef TOLUA_DISABLE_tolua_get_server_SkillsData_skill_level
static int tolua_get_server_SkillsData_skill_level(lua_State* tolua_S)
{
 int tolua_index;
  SkillsData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (SkillsData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_SKILL_COUNT)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->skill_level[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: skill_level of class  SkillsData */
#ifndef TOLUA_DISABLE_tolua_set_server_SkillsData_skill_level
static int tolua_set_server_SkillsData_skill_level(lua_State* tolua_S)
{
 int tolua_index;
  SkillsData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (SkillsData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_SKILL_COUNT)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
  self->skill_level[tolua_index] = ((int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: skill_index of class  SkillsData */
#ifndef TOLUA_DISABLE_tolua_get_server_SkillsData_skill_index
static int tolua_get_server_SkillsData_skill_index(lua_State* tolua_S)
{
 int tolua_index;
  SkillsData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (SkillsData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_SKILL_COUNT)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->skill_index[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: skill_index of class  SkillsData */
#ifndef TOLUA_DISABLE_tolua_set_server_SkillsData_skill_index
static int tolua_set_server_SkillsData_skill_index(lua_State* tolua_S)
{
 int tolua_index;
  SkillsData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (SkillsData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_SKILL_COUNT)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
  self->skill_index[tolua_index] = ((int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: slot_filled of class  YuanShenData */
#ifndef TOLUA_DISABLE_tolua_get_server_YuanShenData_slot_filled
static int tolua_get_server_YuanShenData_slot_filled(lua_State* tolua_S)
{
 int tolua_index;
  YuanShenData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (YuanShenData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=6)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
 tolua_pushboolean(tolua_S,(bool)self->slot_filled[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: slot_filled of class  YuanShenData */
#ifndef TOLUA_DISABLE_tolua_set_server_YuanShenData_slot_filled
static int tolua_set_server_YuanShenData_slot_filled(lua_State* tolua_S)
{
 int tolua_index;
  YuanShenData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (YuanShenData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=6)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
  self->slot_filled[tolua_index] = ((bool)  tolua_toboolean(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: strength_lv of class  EquipSlotData */
#ifndef TOLUA_DISABLE_tolua_get_EquipSlotData_strength_lv
static int tolua_get_EquipSlotData_strength_lv(lua_State* tolua_S)
{
  EquipSlotData* self = (EquipSlotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'strength_lv'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->strength_lv);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: strength_lv of class  EquipSlotData */
#ifndef TOLUA_DISABLE_tolua_set_EquipSlotData_strength_lv
static int tolua_set_EquipSlotData_strength_lv(lua_State* tolua_S)
{
  EquipSlotData* self = (EquipSlotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'strength_lv'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->strength_lv = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fuling_lv of class  EquipSlotData */
#ifndef TOLUA_DISABLE_tolua_get_EquipSlotData_fuling_lv
static int tolua_get_EquipSlotData_fuling_lv(lua_State* tolua_S)
{
  EquipSlotData* self = (EquipSlotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'fuling_lv'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->fuling_lv);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fuling_lv of class  EquipSlotData */
#ifndef TOLUA_DISABLE_tolua_set_EquipSlotData_fuling_lv
static int tolua_set_EquipSlotData_fuling_lv(lua_State* tolua_S)
{
  EquipSlotData* self = (EquipSlotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'fuling_lv'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fuling_lv = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: gem_lv of class  EquipSlotData */
#ifndef TOLUA_DISABLE_tolua_get_EquipSlotData_gem_lv
static int tolua_get_EquipSlotData_gem_lv(lua_State* tolua_S)
{
  EquipSlotData* self = (EquipSlotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'gem_lv'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->gem_lv);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: gem_lv of class  EquipSlotData */
#ifndef TOLUA_DISABLE_tolua_set_EquipSlotData_gem_lv
static int tolua_set_EquipSlotData_gem_lv(lua_State* tolua_S)
{
  EquipSlotData* self = (EquipSlotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'gem_lv'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->gem_lv = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: equip_data of class  EquipSlotData */
#ifndef TOLUA_DISABLE_tolua_get_EquipSlotData_equip_data
static int tolua_get_EquipSlotData_equip_data(lua_State* tolua_S)
{
  EquipSlotData* self = (EquipSlotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'equip_data'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->equip_data,"ItemData");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: equip_data of class  EquipSlotData */
#ifndef TOLUA_DISABLE_tolua_set_EquipSlotData_equip_data
static int tolua_set_EquipSlotData_equip_data(lua_State* tolua_S)
{
  EquipSlotData* self = (EquipSlotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'equip_data'",NULL);
  if (!tolua_isusertype(tolua_S,2,"ItemData",0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->equip_data = *((ItemData*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: zhuling_lv of class  EquipSlotData */
#ifndef TOLUA_DISABLE_tolua_get_EquipSlotData_zhuling_lv
static int tolua_get_EquipSlotData_zhuling_lv(lua_State* tolua_S)
{
  EquipSlotData* self = (EquipSlotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'zhuling_lv'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->zhuling_lv);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: zhuling_lv of class  EquipSlotData */
#ifndef TOLUA_DISABLE_tolua_set_EquipSlotData_zhuling_lv
static int tolua_set_EquipSlotData_zhuling_lv(lua_State* tolua_S)
{
  EquipSlotData* self = (EquipSlotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'zhuling_lv'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->zhuling_lv = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: soul_lv of class  EquipSlotData */
#ifndef TOLUA_DISABLE_tolua_get_EquipSlotData_soul_lv
static int tolua_get_EquipSlotData_soul_lv(lua_State* tolua_S)
{
  EquipSlotData* self = (EquipSlotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'soul_lv'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->soul_lv);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: soul_lv of class  EquipSlotData */
#ifndef TOLUA_DISABLE_tolua_set_EquipSlotData_soul_lv
static int tolua_set_EquipSlotData_soul_lv(lua_State* tolua_S)
{
  EquipSlotData* self = (EquipSlotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'soul_lv'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->soul_lv = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bless_lv of class  EquipSlotData */
#ifndef TOLUA_DISABLE_tolua_get_EquipSlotData_bless_lv
static int tolua_get_EquipSlotData_bless_lv(lua_State* tolua_S)
{
  EquipSlotData* self = (EquipSlotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'bless_lv'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->bless_lv);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bless_lv of class  EquipSlotData */
#ifndef TOLUA_DISABLE_tolua_set_EquipSlotData_bless_lv
static int tolua_set_EquipSlotData_bless_lv(lua_State* tolua_S)
{
  EquipSlotData* self = (EquipSlotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'bless_lv'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bless_lv = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fuling_exp of class  EquipSlotData */
#ifndef TOLUA_DISABLE_tolua_get_EquipSlotData_fuling_exp
static int tolua_get_EquipSlotData_fuling_exp(lua_State* tolua_S)
{
  EquipSlotData* self = (EquipSlotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'fuling_exp'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->fuling_exp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fuling_exp of class  EquipSlotData */
#ifndef TOLUA_DISABLE_tolua_set_EquipSlotData_fuling_exp
static int tolua_set_EquipSlotData_fuling_exp(lua_State* tolua_S)
{
  EquipSlotData* self = (EquipSlotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'fuling_exp'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fuling_exp = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: slot_data of class  EquipsData */
#ifndef TOLUA_DISABLE_tolua_get_server_EquipsData_slot_data
static int tolua_get_server_EquipsData_slot_data(lua_State* tolua_S)
{
 int tolua_index;
  EquipsData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (EquipsData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=EquipSlotType_Max)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->slot_data[tolua_index],"EquipSlotData");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: slot_data of class  EquipsData */
#ifndef TOLUA_DISABLE_tolua_set_server_EquipsData_slot_data
static int tolua_set_server_EquipsData_slot_data(lua_State* tolua_S)
{
 int tolua_index;
  EquipsData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (EquipsData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=EquipSlotType_Max)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
  self->slot_data[tolua_index] = *((EquipSlotData*)  tolua_tousertype(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: god_slot_data of class  EquipsData */
#ifndef TOLUA_DISABLE_tolua_get_server_EquipsData_god_slot_data
static int tolua_get_server_EquipsData_god_slot_data(lua_State* tolua_S)
{
 int tolua_index;
  EquipsData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (EquipsData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=EquipSlotType_Dzi)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->god_slot_data[tolua_index],"EquipSlotData");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: god_slot_data of class  EquipsData */
#ifndef TOLUA_DISABLE_tolua_set_server_EquipsData_god_slot_data
static int tolua_set_server_EquipsData_god_slot_data(lua_State* tolua_S)
{
 int tolua_index;
  EquipsData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (EquipsData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=EquipSlotType_Dzi)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
  self->god_slot_data[tolua_index] = *((EquipSlotData*)  tolua_tousertype(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ring_level of class  ExRingsData */
#ifndef TOLUA_DISABLE_tolua_get_server_ExRingsData_ring_level
static int tolua_get_server_ExRingsData_ring_level(lua_State* tolua_S)
{
 int tolua_index;
  ExRingsData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ExRingsData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=4)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->ring_level[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ring_level of class  ExRingsData */
#ifndef TOLUA_DISABLE_tolua_set_server_ExRingsData_ring_level
static int tolua_set_server_ExRingsData_ring_level(lua_State* tolua_S)
{
 int tolua_index;
  ExRingsData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ExRingsData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=4)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
  self->ring_level[tolua_index] = ((int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: level of class  WingsData */
#ifndef TOLUA_DISABLE_tolua_get_WingsData_level
static int tolua_get_WingsData_level(lua_State* tolua_S)
{
  WingsData* self = (WingsData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'level'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->level);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: level of class  WingsData */
#ifndef TOLUA_DISABLE_tolua_set_WingsData_level
static int tolua_set_WingsData_level(lua_State* tolua_S)
{
  WingsData* self = (WingsData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'level'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->level = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: exp of class  WingsData */
#ifndef TOLUA_DISABLE_tolua_get_WingsData_exp
static int tolua_get_WingsData_exp(lua_State* tolua_S)
{
  WingsData* self = (WingsData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'exp'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->exp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: exp of class  WingsData */
#ifndef TOLUA_DISABLE_tolua_set_WingsData_exp
static int tolua_set_WingsData_exp(lua_State* tolua_S)
{
  WingsData* self = (WingsData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'exp'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->exp = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: openStatus of class  WingsData */
#ifndef TOLUA_DISABLE_tolua_get_WingsData_openStatus
static int tolua_get_WingsData_openStatus(lua_State* tolua_S)
{
  WingsData* self = (WingsData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'openStatus'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->openStatus);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: openStatus of class  WingsData */
#ifndef TOLUA_DISABLE_tolua_set_WingsData_openStatus
static int tolua_set_WingsData_openStatus(lua_State* tolua_S)
{
  WingsData* self = (WingsData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'openStatus'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->openStatus = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ctime of class  WingsData */
#ifndef TOLUA_DISABLE_tolua_get_WingsData_unsigned_ctime
static int tolua_get_WingsData_unsigned_ctime(lua_State* tolua_S)
{
  WingsData* self = (WingsData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'ctime'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->ctime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ctime of class  WingsData */
#ifndef TOLUA_DISABLE_tolua_set_WingsData_unsigned_ctime
static int tolua_set_WingsData_unsigned_ctime(lua_State* tolua_S)
{
  WingsData* self = (WingsData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'ctime'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ctime = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pill of class  WingsData */
#ifndef TOLUA_DISABLE_tolua_get_server_WingsData_pill
static int tolua_get_server_WingsData_pill(lua_State* tolua_S)
{
 int tolua_index;
  WingsData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (WingsData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_WING_PILL)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->pill[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pill of class  WingsData */
#ifndef TOLUA_DISABLE_tolua_set_server_WingsData_pill
static int tolua_set_server_WingsData_pill(lua_State* tolua_S)
{
 int tolua_index;
  WingsData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (WingsData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_WING_PILL)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
  self->pill[tolua_index] = ((short)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: wing_slot of class  WingsEquip */
#ifndef TOLUA_DISABLE_tolua_get_server_WingsEquip_wing_slot
static int tolua_get_server_WingsEquip_wing_slot(lua_State* tolua_S)
{
 int tolua_index;
  WingsEquip* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (WingsEquip*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=WingSlotType_Max)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->wing_slot[tolua_index],"EquipSlotData");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: wing_slot of class  WingsEquip */
#ifndef TOLUA_DISABLE_tolua_set_server_WingsEquip_wing_slot
static int tolua_set_server_WingsEquip_wing_slot(lua_State* tolua_S)
{
 int tolua_index;
  WingsEquip* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (WingsEquip*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=WingSlotType_Max)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
  self->wing_slot[tolua_index] = *((EquipSlotData*)  tolua_tousertype(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: level of class  JingMaiData */
#ifndef TOLUA_DISABLE_tolua_get_JingMaiData_level
static int tolua_get_JingMaiData_level(lua_State* tolua_S)
{
  JingMaiData* self = (JingMaiData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'level'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->level);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: level of class  JingMaiData */
#ifndef TOLUA_DISABLE_tolua_set_JingMaiData_level
static int tolua_set_JingMaiData_level(lua_State* tolua_S)
{
  JingMaiData* self = (JingMaiData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'level'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->level = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: stage of class  JingMaiData */
#ifndef TOLUA_DISABLE_tolua_get_JingMaiData_stage
static int tolua_get_JingMaiData_stage(lua_State* tolua_S)
{
  JingMaiData* self = (JingMaiData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'stage'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->stage);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: stage of class  JingMaiData */
#ifndef TOLUA_DISABLE_tolua_set_JingMaiData_stage
static int tolua_set_JingMaiData_stage(lua_State* tolua_S)
{
  JingMaiData* self = (JingMaiData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'stage'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->stage = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: skill_break_level of class  SkillsBreakData */
#ifndef TOLUA_DISABLE_tolua_get_server_SkillsBreakData_skill_break_level
static int tolua_get_server_SkillsBreakData_skill_break_level(lua_State* tolua_S)
{
 int tolua_index;
  SkillsBreakData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (SkillsBreakData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=5)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->skill_break_level[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: skill_break_level of class  SkillsBreakData */
#ifndef TOLUA_DISABLE_tolua_set_server_SkillsBreakData_skill_break_level
static int tolua_set_server_SkillsBreakData_skill_break_level(lua_State* tolua_S)
{
 int tolua_index;
  SkillsBreakData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (SkillsBreakData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=5)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
  self->skill_break_level[tolua_index] = ((int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: stage of class  LoogsoulData */
#ifndef TOLUA_DISABLE_tolua_get_LoogsoulData_stage
static int tolua_get_LoogsoulData_stage(lua_State* tolua_S)
{
  LoogsoulData* self = (LoogsoulData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'stage'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->stage);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: stage of class  LoogsoulData */
#ifndef TOLUA_DISABLE_tolua_set_LoogsoulData_stage
static int tolua_set_LoogsoulData_stage(lua_State* tolua_S)
{
  LoogsoulData* self = (LoogsoulData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'stage'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->stage = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: level of class  LoogsoulData */
#ifndef TOLUA_DISABLE_tolua_get_LoogsoulData_level
static int tolua_get_LoogsoulData_level(lua_State* tolua_S)
{
  LoogsoulData* self = (LoogsoulData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'level'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->level);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: level of class  LoogsoulData */
#ifndef TOLUA_DISABLE_tolua_set_LoogsoulData_level
static int tolua_set_LoogsoulData_level(lua_State* tolua_S)
{
  LoogsoulData* self = (LoogsoulData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'level'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->level = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: exp of class  LoogsoulData */
#ifndef TOLUA_DISABLE_tolua_get_LoogsoulData_exp
static int tolua_get_LoogsoulData_exp(lua_State* tolua_S)
{
  LoogsoulData* self = (LoogsoulData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'exp'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->exp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: exp of class  LoogsoulData */
#ifndef TOLUA_DISABLE_tolua_set_LoogsoulData_exp
static int tolua_set_LoogsoulData_exp(lua_State* tolua_S)
{
  LoogsoulData* self = (LoogsoulData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'exp'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->exp = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: act of class  LoogsoulData */
#ifndef TOLUA_DISABLE_tolua_get_LoogsoulData_act
static int tolua_get_LoogsoulData_act(lua_State* tolua_S)
{
  LoogsoulData* self = (LoogsoulData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'act'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->act);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: act of class  LoogsoulData */
#ifndef TOLUA_DISABLE_tolua_set_LoogsoulData_act
static int tolua_set_LoogsoulData_act(lua_State* tolua_S)
{
  LoogsoulData* self = (LoogsoulData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'act'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->act = ((char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: stage of class  ShieldData */
#ifndef TOLUA_DISABLE_tolua_get_ShieldData_stage
static int tolua_get_ShieldData_stage(lua_State* tolua_S)
{
  ShieldData* self = (ShieldData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'stage'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->stage);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: stage of class  ShieldData */
#ifndef TOLUA_DISABLE_tolua_set_ShieldData_stage
static int tolua_set_ShieldData_stage(lua_State* tolua_S)
{
  ShieldData* self = (ShieldData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'stage'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->stage = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: level of class  ShieldData */
#ifndef TOLUA_DISABLE_tolua_get_ShieldData_level
static int tolua_get_ShieldData_level(lua_State* tolua_S)
{
  ShieldData* self = (ShieldData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'level'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->level);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: level of class  ShieldData */
#ifndef TOLUA_DISABLE_tolua_set_ShieldData_level
static int tolua_set_ShieldData_level(lua_State* tolua_S)
{
  ShieldData* self = (ShieldData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'level'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->level = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: exp of class  ShieldData */
#ifndef TOLUA_DISABLE_tolua_get_ShieldData_exp
static int tolua_get_ShieldData_exp(lua_State* tolua_S)
{
  ShieldData* self = (ShieldData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'exp'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->exp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: exp of class  ShieldData */
#ifndef TOLUA_DISABLE_tolua_set_ShieldData_exp
static int tolua_set_ShieldData_exp(lua_State* tolua_S)
{
  ShieldData* self = (ShieldData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'exp'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->exp = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: act of class  ShieldData */
#ifndef TOLUA_DISABLE_tolua_get_ShieldData_act
static int tolua_get_ShieldData_act(lua_State* tolua_S)
{
  ShieldData* self = (ShieldData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'act'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->act);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: act of class  ShieldData */
#ifndef TOLUA_DISABLE_tolua_set_ShieldData_act
static int tolua_set_ShieldData_act(lua_State* tolua_S)
{
  ShieldData* self = (ShieldData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'act'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->act = ((char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: stage of class  XueyuData */
#ifndef TOLUA_DISABLE_tolua_get_XueyuData_stage
static int tolua_get_XueyuData_stage(lua_State* tolua_S)
{
  XueyuData* self = (XueyuData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'stage'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->stage);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: stage of class  XueyuData */
#ifndef TOLUA_DISABLE_tolua_set_XueyuData_stage
static int tolua_set_XueyuData_stage(lua_State* tolua_S)
{
  XueyuData* self = (XueyuData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'stage'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->stage = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: level of class  XueyuData */
#ifndef TOLUA_DISABLE_tolua_get_XueyuData_level
static int tolua_get_XueyuData_level(lua_State* tolua_S)
{
  XueyuData* self = (XueyuData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'level'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->level);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: level of class  XueyuData */
#ifndef TOLUA_DISABLE_tolua_set_XueyuData_level
static int tolua_set_XueyuData_level(lua_State* tolua_S)
{
  XueyuData* self = (XueyuData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'level'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->level = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: exp of class  XueyuData */
#ifndef TOLUA_DISABLE_tolua_get_XueyuData_exp
static int tolua_get_XueyuData_exp(lua_State* tolua_S)
{
  XueyuData* self = (XueyuData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'exp'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->exp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: exp of class  XueyuData */
#ifndef TOLUA_DISABLE_tolua_set_XueyuData_exp
static int tolua_set_XueyuData_exp(lua_State* tolua_S)
{
  XueyuData* self = (XueyuData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'exp'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->exp = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: act of class  XueyuData */
#ifndef TOLUA_DISABLE_tolua_get_XueyuData_act
static int tolua_get_XueyuData_act(lua_State* tolua_S)
{
  XueyuData* self = (XueyuData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'act'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->act);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: act of class  XueyuData */
#ifndef TOLUA_DISABLE_tolua_set_XueyuData_act
static int tolua_set_XueyuData_act(lua_State* tolua_S)
{
  XueyuData* self = (XueyuData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'act'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->act = ((char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fuwen_slot of class  FuWenData */
#ifndef TOLUA_DISABLE_tolua_get_server_FuWenData_fuwen_slot
static int tolua_get_server_FuWenData_fuwen_slot(lua_State* tolua_S)
{
 int tolua_index;
  FuWenData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (FuWenData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_FUWEN)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->fuwen_slot[tolua_index],"ItemData");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fuwen_slot of class  FuWenData */
#ifndef TOLUA_DISABLE_tolua_set_server_FuWenData_fuwen_slot
static int tolua_set_server_FuWenData_fuwen_slot(lua_State* tolua_S)
{
 int tolua_index;
  FuWenData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (FuWenData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MAX_FUWEN)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
  self->fuwen_slot[tolua_index] = *((ItemData*)  tolua_tousertype(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: id of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_get_RoleData_id
static int tolua_get_RoleData_id(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'id'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->id);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: id of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_set_RoleData_id
static int tolua_set_RoleData_id(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'id'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->id = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: job of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_get_RoleData_job
static int tolua_get_RoleData_job(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'job'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->job);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: job of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_set_RoleData_job
static int tolua_set_RoleData_job(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'job'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->job = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sex of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_get_RoleData_sex
static int tolua_get_RoleData_sex(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'sex'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->sex);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sex of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_set_RoleData_sex
static int tolua_set_RoleData_sex(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'sex'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sex = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: power of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_get_RoleData_power
static int tolua_get_RoleData_power(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'power'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->power);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: power of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_set_RoleData_power
static int tolua_set_RoleData_power(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'power'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->power = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: skills of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_get_RoleData_skills
static int tolua_get_RoleData_skills(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'skills'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->skills,"SkillsData");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: skills of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_set_RoleData_skills
static int tolua_set_RoleData_skills(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'skills'",NULL);
  if (!tolua_isusertype(tolua_S,2,"SkillsData",0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skills = *((SkillsData*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: equips_data of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_get_RoleData_equips_data
static int tolua_get_RoleData_equips_data(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'equips_data'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->equips_data,"EquipsData");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: equips_data of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_set_RoleData_equips_data
static int tolua_set_RoleData_equips_data(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'equips_data'",NULL);
  if (!tolua_isusertype(tolua_S,2,"EquipsData",0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->equips_data = *((EquipsData*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ex_rings of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_get_RoleData_ex_rings
static int tolua_get_RoleData_ex_rings(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'ex_rings'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->ex_rings,"ExRingsData");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ex_rings of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_set_RoleData_ex_rings
static int tolua_set_RoleData_ex_rings(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'ex_rings'",NULL);
  if (!tolua_isusertype(tolua_S,2,"ExRingsData",0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ex_rings = *((ExRingsData*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: wings of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_get_RoleData_wings
static int tolua_get_RoleData_wings(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'wings'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->wings,"WingsData");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: wings of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_set_RoleData_wings
static int tolua_set_RoleData_wings(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'wings'",NULL);
  if (!tolua_isusertype(tolua_S,2,"WingsData",0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->wings = *((WingsData*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: jingmai_data of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_get_RoleData_jingmai_data
static int tolua_get_RoleData_jingmai_data(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'jingmai_data'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->jingmai_data,"JingMaiData");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: jingmai_data of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_set_RoleData_jingmai_data
static int tolua_set_RoleData_jingmai_data(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'jingmai_data'",NULL);
  if (!tolua_isusertype(tolua_S,2,"JingMaiData",0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->jingmai_data = *((JingMaiData*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: loogsoul_data of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_get_RoleData_loogsoul_data
static int tolua_get_RoleData_loogsoul_data(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'loogsoul_data'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->loogsoul_data,"LoogsoulData");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: loogsoul_data of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_set_RoleData_loogsoul_data
static int tolua_set_RoleData_loogsoul_data(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'loogsoul_data'",NULL);
  if (!tolua_isusertype(tolua_S,2,"LoogsoulData",0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->loogsoul_data = *((LoogsoulData*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fuwen_data of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_get_RoleData_fuwen_data
static int tolua_get_RoleData_fuwen_data(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'fuwen_data'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->fuwen_data,"FuWenData");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fuwen_data of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_set_RoleData_fuwen_data
static int tolua_set_RoleData_fuwen_data(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'fuwen_data'",NULL);
  if (!tolua_isusertype(tolua_S,2,"FuWenData",0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fuwen_data = *((FuWenData*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: heirloom of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_get_server_RoleData_heirloom
static int tolua_get_server_RoleData_heirloom(lua_State* tolua_S)
{
 int tolua_index;
  RoleData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (RoleData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=HEIRLOOM_TYPE_MAX)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->heirloom[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: heirloom of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_set_server_RoleData_heirloom
static int tolua_set_server_RoleData_heirloom(lua_State* tolua_S)
{
 int tolua_index;
  RoleData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (RoleData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=HEIRLOOM_TYPE_MAX)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
  self->heirloom[tolua_index] = ((int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: weapon_soul_id of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_get_RoleData_weapon_soul_id
static int tolua_get_RoleData_weapon_soul_id(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'weapon_soul_id'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->weapon_soul_id);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: weapon_soul_id of class  RoleData */
#ifndef TOLUA_DISABLE_tolua_set_RoleData_weapon_soul_id
static int tolua_set_RoleData_weapon_soul_id(lua_State* tolua_S)
{
  RoleData* self = (RoleData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'weapon_soul_id'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->weapon_soul_id = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: role_count of class  RoleDatas */
#ifndef TOLUA_DISABLE_tolua_get_RoleDatas_role_count
static int tolua_get_RoleDatas_role_count(lua_State* tolua_S)
{
  RoleDatas* self = (RoleDatas*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'role_count'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->role_count);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: role_count of class  RoleDatas */
#ifndef TOLUA_DISABLE_tolua_set_RoleDatas_role_count
static int tolua_set_RoleDatas_role_count(lua_State* tolua_S)
{
  RoleDatas* self = (RoleDatas*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'role_count'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->role_count = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: roles of class  RoleDatas */
#ifndef TOLUA_DISABLE_tolua_get_server_RoleDatas_roles
static int tolua_get_server_RoleDatas_roles(lua_State* tolua_S)
{
 int tolua_index;
  RoleDatas* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (RoleDatas*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=3)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->roles[tolua_index],"RoleData");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: roles of class  RoleDatas */
#ifndef TOLUA_DISABLE_tolua_set_server_RoleDatas_roles
static int tolua_set_server_RoleDatas_roles(lua_State* tolua_S)
{
 int tolua_index;
  RoleDatas* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (RoleDatas*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=3)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
  self->roles[tolua_index] = *((RoleData*)  tolua_tousertype(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  RoleDatas */
#ifndef TOLUA_DISABLE_tolua_server_RoleDatas_new00
static int tolua_server_RoleDatas_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RoleDatas",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RoleDatas* tolua_ret = (RoleDatas*)  new RoleDatas();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"RoleDatas");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  RoleDatas */
#ifndef TOLUA_DISABLE_tolua_server_RoleDatas_new00_local
static int tolua_server_RoleDatas_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RoleDatas",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RoleDatas* tolua_ret = (RoleDatas*)  new RoleDatas();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"RoleDatas");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Protocol::TestProto */
#ifndef TOLUA_DISABLE_tolua_server_Protocol_TestProto_new00
static int tolua_server_Protocol_TestProto_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Protocol::TestProto",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Protocol::TestProto* tolua_ret = (Protocol::TestProto*)  new Protocol::TestProto();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Protocol::TestProto");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Protocol::TestProto */
#ifndef TOLUA_DISABLE_tolua_server_Protocol_TestProto_new00_local
static int tolua_server_Protocol_TestProto_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Protocol::TestProto",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Protocol::TestProto* tolua_ret = (Protocol::TestProto*)  new Protocol::TestProto();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"Protocol::TestProto");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: a of class  Protocol::TestProto */
#ifndef TOLUA_DISABLE_tolua_get_Protocol__TestProto_a
static int tolua_get_Protocol__TestProto_a(lua_State* tolua_S)
{
  Protocol::TestProto* self = (Protocol::TestProto*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'a'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->a);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: a of class  Protocol::TestProto */
#ifndef TOLUA_DISABLE_tolua_set_Protocol__TestProto_a
static int tolua_set_Protocol__TestProto_a(lua_State* tolua_S)
{
  Protocol::TestProto* self = (Protocol::TestProto*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'a'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->a = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: a of class  Protocol::Test */
#ifndef TOLUA_DISABLE_tolua_get_Protocol__Test_a
static int tolua_get_Protocol__Test_a(lua_State* tolua_S)
{
  Protocol::Test* self = (Protocol::Test*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'a'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->a);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: a of class  Protocol::Test */
#ifndef TOLUA_DISABLE_tolua_set_Protocol__Test_a
static int tolua_set_Protocol__Test_a(lua_State* tolua_S)
{
  Protocol::Test* self = (Protocol::Test*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'a'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->a = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: b of class  Protocol::Test */
#ifndef TOLUA_DISABLE_tolua_get_Protocol__Test_b
static int tolua_get_Protocol__Test_b(lua_State* tolua_S)
{
  Protocol::Test* self = (Protocol::Test*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'b'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->b);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: b of class  Protocol::Test */
#ifndef TOLUA_DISABLE_tolua_set_Protocol__Test_b
static int tolua_set_Protocol__Test_b(lua_State* tolua_S)
{
  Protocol::Test* self = (Protocol::Test*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'b'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->b = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Attribute */
#ifndef TOLUA_DISABLE_tolua_server_Attribute_new00
static int tolua_server_Attribute_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Attribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Attribute* tolua_ret = (Attribute*)  new Attribute();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Attribute */
#ifndef TOLUA_DISABLE_tolua_server_Attribute_new00_local
static int tolua_server_Attribute_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Attribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Attribute* tolua_ret = (Attribute*)  new Attribute();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Attribute */
#ifndef TOLUA_DISABLE_tolua_server_Attribute_new01
static int tolua_server_Attribute_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Attribute",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const Attribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Attribute* attrs = ((const Attribute*)  tolua_tousertype(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  new Attribute(*attrs);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
tolua_lerror:
 return tolua_server_Attribute_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Attribute */
#ifndef TOLUA_DISABLE_tolua_server_Attribute_new01_local
static int tolua_server_Attribute_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Attribute",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const Attribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Attribute* attrs = ((const Attribute*)  tolua_tousertype(tolua_S,2,0));
  {
   Attribute* tolua_ret = (Attribute*)  new Attribute(*attrs);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"Attribute");
  }
 }
 return 1;
tolua_lerror:
 return tolua_server_Attribute_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Reset of class  Attribute */
#ifndef TOLUA_DISABLE_tolua_server_Attribute_Reset00
static int tolua_server_Attribute_Reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Attribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Attribute* self = (Attribute*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'Reset'",NULL);
#endif
  {
   self->Reset();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'Reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Add of class  Attribute */
#ifndef TOLUA_DISABLE_tolua_server_Attribute_Add00
static int tolua_server_Attribute_Add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Attribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Attribute* self = (Attribute*)  tolua_tousertype(tolua_S,1,0);
  Attribute::AttributeType type = ((Attribute::AttributeType) (int)  tolua_tonumber(tolua_S,2,0));
  double value = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'Add'",NULL);
#endif
  {
   self->Add(type,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'Add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Set of class  Attribute */
#ifndef TOLUA_DISABLE_tolua_server_Attribute_Set00
static int tolua_server_Attribute_Set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Attribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Attribute* self = (Attribute*)  tolua_tousertype(tolua_S,1,0);
  Attribute::AttributeType type = ((Attribute::AttributeType) (int)  tolua_tonumber(tolua_S,2,0));
  double value = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'Set'",NULL);
#endif
  {
   self->Set(type,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'Set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Get of class  Attribute */
#ifndef TOLUA_DISABLE_tolua_server_Attribute_Get00
static int tolua_server_Attribute_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Attribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Attribute* self = (Attribute*)  tolua_tousertype(tolua_S,1,0);
  Attribute::AttributeType type = ((Attribute::AttributeType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'Get'",NULL);
#endif
  {
   double tolua_ret = (double)  self->Get(type);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'Get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  Attribute */
#ifndef TOLUA_DISABLE_tolua_server_Attribute__geti00
static int tolua_server_Attribute__geti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Attribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Attribute* self = (const Attribute*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'operator[]'",NULL);
#endif
  {
   const double tolua_ret = (const double)  self->operator[](type);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function '.geti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator&[] of class  Attribute */
#ifndef TOLUA_DISABLE_tolua_server_Attribute__seti00
static int tolua_server_Attribute__seti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Attribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Attribute* self = (Attribute*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  double tolua_value = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'operator&[]'",NULL);
#endif
  self->operator[](type) =  tolua_value;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function '.seti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  Attribute */
#ifndef TOLUA_DISABLE_tolua_server_Attribute__geti01
static int tolua_server_Attribute__geti01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Attribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Attribute* self = (Attribute*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'operator[]'",NULL);
#endif
  {
   double tolua_ret = (double)  self->operator[](type);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_server_Attribute__geti00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetValues of class  Attribute */
#ifndef TOLUA_DISABLE_tolua_server_Attribute_GetValues00
static int tolua_server_Attribute_GetValues00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Attribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Attribute* self = (const Attribute*)  tolua_tousertype(tolua_S,1,0);
  double data = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'GetValues'",NULL);
#endif
  {
   self->GetValues(&data);
   tolua_pushnumber(tolua_S,(lua_Number)data);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetValues'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetExtraPower of class  Attribute */
#ifndef TOLUA_DISABLE_tolua_server_Attribute_SetExtraPower00
static int tolua_server_Attribute_SetExtraPower00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Attribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Attribute* self = (Attribute*)  tolua_tousertype(tolua_S,1,0);
  double power = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'SetExtraPower'",NULL);
#endif
  {
   self->SetExtraPower(power);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'SetExtraPower'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddExtraPower of class  Attribute */
#ifndef TOLUA_DISABLE_tolua_server_Attribute_AddExtraPower00
static int tolua_server_Attribute_AddExtraPower00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Attribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Attribute* self = (Attribute*)  tolua_tousertype(tolua_S,1,0);
  double power = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'AddExtraPower'",NULL);
#endif
  {
   self->AddExtraPower(power);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'AddExtraPower'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetExtraPower of class  Attribute */
#ifndef TOLUA_DISABLE_tolua_server_Attribute_GetExtraPower00
static int tolua_server_Attribute_GetExtraPower00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Attribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Attribute* self = (const Attribute*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'GetExtraPower'",NULL);
#endif
  {
   double tolua_ret = (double)  self->GetExtraPower();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetExtraPower'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ExAttribute */
#ifndef TOLUA_DISABLE_tolua_server_ExAttribute_new00
static int tolua_server_ExAttribute_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ExAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ExAttribute* tolua_ret = (ExAttribute*)  new ExAttribute();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ExAttribute */
#ifndef TOLUA_DISABLE_tolua_server_ExAttribute_new00_local
static int tolua_server_ExAttribute_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ExAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ExAttribute* tolua_ret = (ExAttribute*)  new ExAttribute();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ExAttribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ExAttribute */
#ifndef TOLUA_DISABLE_tolua_server_ExAttribute_new01
static int tolua_server_ExAttribute_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ExAttribute",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const ExAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const ExAttribute* attrs = ((const ExAttribute*)  tolua_tousertype(tolua_S,2,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  new ExAttribute(*attrs);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ExAttribute");
  }
 }
 return 1;
tolua_lerror:
 return tolua_server_ExAttribute_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ExAttribute */
#ifndef TOLUA_DISABLE_tolua_server_ExAttribute_new01_local
static int tolua_server_ExAttribute_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ExAttribute",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const ExAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const ExAttribute* attrs = ((const ExAttribute*)  tolua_tousertype(tolua_S,2,0));
  {
   ExAttribute* tolua_ret = (ExAttribute*)  new ExAttribute(*attrs);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ExAttribute");
  }
 }
 return 1;
tolua_lerror:
 return tolua_server_ExAttribute_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Reset of class  ExAttribute */
#ifndef TOLUA_DISABLE_tolua_server_ExAttribute_Reset00
static int tolua_server_ExAttribute_Reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ExAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ExAttribute* self = (ExAttribute*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'Reset'",NULL);
#endif
  {
   self->Reset();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'Reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Add of class  ExAttribute */
#ifndef TOLUA_DISABLE_tolua_server_ExAttribute_Add00
static int tolua_server_ExAttribute_Add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ExAttribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ExAttribute* self = (ExAttribute*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  int value = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'Add'",NULL);
#endif
  {
   self->Add(type,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'Add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Set of class  ExAttribute */
#ifndef TOLUA_DISABLE_tolua_server_ExAttribute_Set00
static int tolua_server_ExAttribute_Set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ExAttribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ExAttribute* self = (ExAttribute*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  int value = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'Set'",NULL);
#endif
  {
   self->Set(type,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'Set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Get of class  ExAttribute */
#ifndef TOLUA_DISABLE_tolua_server_ExAttribute_Get00
static int tolua_server_ExAttribute_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ExAttribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ExAttribute* self = (ExAttribute*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'Get'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Get(type);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'Get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator&[] of class  ExAttribute */
#ifndef TOLUA_DISABLE_tolua_server_ExAttribute__seti00
static int tolua_server_ExAttribute__seti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ExAttribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ExAttribute* self = (ExAttribute*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  int tolua_value = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'operator&[]'",NULL);
#endif
  self->operator[](type) =  tolua_value;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function '.seti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  ExAttribute */
#ifndef TOLUA_DISABLE_tolua_server_ExAttribute__geti00
static int tolua_server_ExAttribute__geti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ExAttribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ExAttribute* self = (ExAttribute*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'operator[]'",NULL);
#endif
  {
   int tolua_ret = (int)  self->operator[](type);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function '.geti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetValues of class  ExAttribute */
#ifndef TOLUA_DISABLE_tolua_server_ExAttribute_GetValues00
static int tolua_server_ExAttribute_GetValues00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ExAttribute",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ExAttribute* self = (const ExAttribute*)  tolua_tousertype(tolua_S,1,0);
  int data = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'GetValues'",NULL);
#endif
  {
   self->GetValues(&data);
   tolua_pushnumber(tolua_S,(lua_Number)data);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetValues'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: actor_id of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_get_RobotData_actor_id
static int tolua_get_RobotData_actor_id(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'actor_id'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->actor_id);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: actor_id of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_set_RobotData_actor_id
static int tolua_set_RobotData_actor_id(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'actor_id'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->actor_id = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: name of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_get_RobotData_name
static int tolua_get_RobotData_name(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'name'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: name of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_set_RobotData_name
static int tolua_set_RobotData_name(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'name'",NULL);
  if (!tolua_isstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->name = ((char*)  tolua_tostring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: level of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_get_RobotData_level
static int tolua_get_RobotData_level(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'level'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->level);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: level of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_set_RobotData_level
static int tolua_set_RobotData_level(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'level'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->level = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: job of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_get_RobotData_job
static int tolua_get_RobotData_job(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'job'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->job);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: job of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_set_RobotData_job
static int tolua_set_RobotData_job(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'job'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->job = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sex of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_get_RobotData_sex
static int tolua_get_RobotData_sex(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'sex'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->sex);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sex of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_set_RobotData_sex
static int tolua_set_RobotData_sex(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'sex'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sex = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: clothesId of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_get_RobotData_clothesId
static int tolua_get_RobotData_clothesId(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'clothesId'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->clothesId);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: clothesId of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_set_RobotData_clothesId
static int tolua_set_RobotData_clothesId(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'clothesId'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->clothesId = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: weaponId of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_get_RobotData_weaponId
static int tolua_get_RobotData_weaponId(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'weaponId'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->weaponId);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: weaponId of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_set_RobotData_weaponId
static int tolua_set_RobotData_weaponId(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'weaponId'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->weaponId = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: wingOpenState of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_get_RobotData_wingOpenState
static int tolua_get_RobotData_wingOpenState(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'wingOpenState'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->wingOpenState);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: wingOpenState of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_set_RobotData_wingOpenState
static int tolua_set_RobotData_wingOpenState(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'wingOpenState'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->wingOpenState = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: wingLevel of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_get_RobotData_wingLevel
static int tolua_get_RobotData_wingLevel(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'wingLevel'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->wingLevel);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: wingLevel of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_set_RobotData_wingLevel
static int tolua_set_RobotData_wingLevel(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'wingLevel'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->wingLevel = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attrs of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_get_RobotData_attrs
static int tolua_get_RobotData_attrs(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'attrs'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->attrs,"Attribute");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attrs of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_set_RobotData_attrs
static int tolua_set_RobotData_attrs(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'attrs'",NULL);
  if (!tolua_isusertype(tolua_S,2,"Attribute",0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attrs = *((Attribute*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: skills of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_get_server_RobotData_skills
static int tolua_get_server_RobotData_skills(lua_State* tolua_S)
{
 int tolua_index;
  RobotData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (RobotData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=20)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->skills[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: skills of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_set_server_RobotData_skills
static int tolua_set_server_RobotData_skills(lua_State* tolua_S)
{
 int tolua_index;
  RobotData* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (RobotData*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=20)
  tolua_error(tolua_S,(char*)"array indexing out of range.",NULL);
#endif
  self->skills[tolua_index] = ((int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: headid of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_get_RobotData_headid
static int tolua_get_RobotData_headid(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'headid'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->headid);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: headid of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_set_RobotData_headid
static int tolua_set_RobotData_headid(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'headid'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->headid = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: holaid of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_get_RobotData_holaid
static int tolua_get_RobotData_holaid(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'holaid'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->holaid);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: holaid of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_set_RobotData_holaid
static int tolua_set_RobotData_holaid(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'holaid'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->holaid = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: camp of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_get_RobotData_camp
static int tolua_get_RobotData_camp(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'camp'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->camp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: camp of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_set_RobotData_camp
static int tolua_set_RobotData_camp(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'camp'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->camp = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ismirror of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_get_RobotData_ismirror
static int tolua_get_RobotData_ismirror(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'ismirror'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->ismirror);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ismirror of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_set_RobotData_ismirror
static int tolua_set_RobotData_ismirror(lua_State* tolua_S)
{
  RobotData* self = (RobotData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in accessing variable 'ismirror'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,(char*)"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ismirror = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_server_RobotData_new00
static int tolua_server_RobotData_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RobotData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RobotData* tolua_ret = (RobotData*)  new RobotData();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"RobotData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  RobotData */
#ifndef TOLUA_DISABLE_tolua_server_RobotData_new00_local
static int tolua_server_RobotData_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RobotData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RobotData* tolua_ret = (RobotData*)  new RobotData();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"RobotData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LRedis::Zadd */
#ifndef TOLUA_DISABLE_tolua_server_LRedis_Zadd00
static int tolua_server_LRedis_Zadd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* rankname = ((char*)  tolua_tostring(tolua_S,1,0));
  int score = ((int)  tolua_tonumber(tolua_S,2,0));
  char* actordata = ((char*)  tolua_tostring(tolua_S,3,0));
  {
   LRedis::Zadd(rankname,score,actordata);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'Zadd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NewSocket of class  LuaSocket */
#ifndef TOLUA_DISABLE_tolua_server_LuaSocket_NewSocket00
static int tolua_server_LuaSocket_NewSocket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaSocket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LuaSocket* tolua_ret = (LuaSocket*)  LuaSocket::NewSocket();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaSocket");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'NewSocket'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Release of class  LuaSocket */
#ifndef TOLUA_DISABLE_tolua_server_LuaSocket_Release00
static int tolua_server_LuaSocket_Release00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaSocket",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"LuaSocket",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaSocket* s = ((LuaSocket*)  tolua_tousertype(tolua_S,2,0));
  int step = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LuaSocket::Release(s,step);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'Release'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHostByName of class  LuaSocket */
#ifndef TOLUA_DISABLE_tolua_server_LuaSocket_GetHostByName00
static int tolua_server_LuaSocket_GetHostByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaSocket",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* host = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   double tolua_ret = (double)  LuaSocket::GetHostByName(host);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'GetHostByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send of class  LuaSocket */
#ifndef TOLUA_DISABLE_tolua_server_LuaSocket_send00
static int tolua_server_LuaSocket_send00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaSocket",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaSocket* self = (LuaSocket*)  tolua_tousertype(tolua_S,1,0);
  char* buf = ((char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'send'",NULL);
#endif
  {
   int tolua_ret = (int)  self->send(buf);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: connect of class  LuaSocket */
#ifndef TOLUA_DISABLE_tolua_server_LuaSocket_connect00
static int tolua_server_LuaSocket_connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaSocket",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaSocket* self = (LuaSocket*)  tolua_tousertype(tolua_S,1,0);
  const double addr = ((const double)  tolua_tonumber(tolua_S,2,0));
  const int port = ((const int)  tolua_tonumber(tolua_S,3,0));
  bool block = ((bool) (tolua_toboolean(tolua_S,4,true)!=0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'connect'",NULL);
#endif
  {
   int tolua_ret = (int)  self->connect(addr,port,block);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'connect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: readline of class  LuaSocket */
#ifndef TOLUA_DISABLE_tolua_server_LuaSocket_readline00
static int tolua_server_LuaSocket_readline00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaSocket",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaSocket* self = (LuaSocket*)  tolua_tousertype(tolua_S,1,0);
  int retval = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'readline'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->readline(retval);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
   tolua_pushnumber(tolua_S,(lua_Number)retval);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'readline'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: readall of class  LuaSocket */
#ifndef TOLUA_DISABLE_tolua_server_LuaSocket_readall00
static int tolua_server_LuaSocket_readall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaSocket",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaSocket* self = (LuaSocket*)  tolua_tousertype(tolua_S,1,0);
  int retval = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,(char*)"invalid 'self' in function 'readall'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->readall(retval);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
   tolua_pushnumber(tolua_S,(lua_Number)retval);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'readall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
int tolua_server_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,(char*)"LActorMgr",0);
  tolua_beginmodule(tolua_S,(char*)"LActorMgr");
   tolua_function(tolua_S,(char*)"getDbConn",tolua_server_LActorMgr_getDbConn00);
   tolua_function(tolua_S,(char*)"getDataPacket",tolua_server_LActorMgr_getDataPacket00);
   tolua_function(tolua_S,(char*)"SendToGate",tolua_server_LActorMgr_SendToGate00);
   tolua_function(tolua_S,(char*)"lowerCaseNameStr",tolua_server_LActorMgr_lowerCaseNameStr00);
   tolua_function(tolua_S,(char*)"checkNameStr",tolua_server_LActorMgr_checkNameStr00);
   tolua_function(tolua_S,(char*)"nameHasUser",tolua_server_LActorMgr_nameHasUser00);
   tolua_function(tolua_S,(char*)"createActor",tolua_server_LActorMgr_createActor00);
   tolua_function(tolua_S,(char*)"enterGame",tolua_server_LActorMgr_enterGame00);
   tolua_function(tolua_S,(char*)"getRandomName",tolua_server_LActorMgr_getRandomName00);
   tolua_function(tolua_S,(char*)"isLoginBattle",tolua_server_LActorMgr_isLoginBattle00);
   tolua_function(tolua_S,(char*)"isLogoutBattle",tolua_server_LActorMgr_isLogoutBattle00);
   tolua_function(tolua_S,(char*)"LoginOtherSrv",tolua_server_LActorMgr_LoginOtherSrv00);
   tolua_function(tolua_S,(char*)"LoginLianfuSrv",tolua_server_LActorMgr_LoginLianfuSrv00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,(char*)"aeNoEvent",aeNoEvent);
  tolua_constant(tolua_S,(char*)"aeStartBattle",aeStartBattle);
  tolua_constant(tolua_S,(char*)"aeStartPkState",aeStartPkState);
  tolua_constant(tolua_S,(char*)"aeLevel",aeLevel);
  tolua_constant(tolua_S,(char*)"aeSkillLevelup",aeSkillLevelup);
  tolua_constant(tolua_S,(char*)"aeAddEquiment",aeAddEquiment);
  tolua_constant(tolua_S,(char*)"aeDelEquiment",aeDelEquiment);
  tolua_constant(tolua_S,(char*)"aeInit",aeInit);
  tolua_constant(tolua_S,(char*)"aeBeforeLogin",aeBeforeLogin);
  tolua_constant(tolua_S,(char*)"aeUserLogin",aeUserLogin);
  tolua_constant(tolua_S,(char*)"aeUserFirstLogion",aeUserFirstLogion);
  tolua_constant(tolua_S,(char*)"aeUserLogout",aeUserLogout);
  tolua_constant(tolua_S,(char*)"aeEnterFuben",aeEnterFuben);
  tolua_constant(tolua_S,(char*)"aeLeftTeam",aeLeftTeam);
  tolua_constant(tolua_S,(char*)"aeReliveTimeOut",aeReliveTimeOut);
  tolua_constant(tolua_S,(char*)"aeRecharge",aeRecharge);
  tolua_constant(tolua_S,(char*)"aeNewDayArrive",aeNewDayArrive);
  tolua_constant(tolua_S,(char*)"aeUpdateVipInfo",aeUpdateVipInfo);
  tolua_constant(tolua_S,(char*)"aeKilledByActor",aeKilledByActor);
  tolua_constant(tolua_S,(char*)"aeStarQuest",aeStarQuest);
  tolua_constant(tolua_S,(char*)"aeOpenSys",aeOpenSys);
  tolua_constant(tolua_S,(char*)"aeTeleportComfirm",aeTeleportComfirm);
  tolua_constant(tolua_S,(char*)"aeDayEnd",aeDayEnd);
  tolua_constant(tolua_S,(char*)"aeConsumeYuanbao",aeConsumeYuanbao);
  tolua_constant(tolua_S,(char*)"aeConsumeGold",aeConsumeGold);
  tolua_constant(tolua_S,(char*)"aeChangePrestige",aeChangePrestige);
  tolua_constant(tolua_S,(char*)"aeRechargeOffline",aeRechargeOffline);
  tolua_constant(tolua_S,(char*)"aeJoinGuild",aeJoinGuild);
  tolua_constant(tolua_S,(char*)"aeLeftGuild",aeLeftGuild);
  tolua_constant(tolua_S,(char*)"aePetBattle",aePetBattle);
  tolua_constant(tolua_S,(char*)"aeCrossWar",aeCrossWar);
  tolua_constant(tolua_S,(char*)"aeNewDayHoursArrive",aeNewDayHoursArrive);
  tolua_constant(tolua_S,(char*)"aeStrongLevelChanged",aeStrongLevelChanged);
  tolua_constant(tolua_S,(char*)"aeNewWeekArrive",aeNewWeekArrive);
  tolua_constant(tolua_S,(char*)"aeNewDayHoursArriveInCommSrv",aeNewDayHoursArriveInCommSrv);
  tolua_constant(tolua_S,(char*)"aeStoreCost",aeStoreCost);
  tolua_constant(tolua_S,(char*)"aeDropItem",aeDropItem);
  tolua_constant(tolua_S,(char*)"aeSmeltEquip",aeSmeltEquip);
  tolua_constant(tolua_S,(char*)"aeFightPower",aeFightPower);
  tolua_constant(tolua_S,(char*)"aeSkirmish",aeSkirmish);
  tolua_constant(tolua_S,(char*)"aeUpgradeSkillCount",aeUpgradeSkillCount);
  tolua_constant(tolua_S,(char*)"aeWingLevelUp",aeWingLevelUp);
  tolua_constant(tolua_S,(char*)"aeWingStarUp",aeWingStarUp);
  tolua_constant(tolua_S,(char*)"aeWingTrain",aeWingTrain);
  tolua_constant(tolua_S,(char*)"aeUpgradeJingmai",aeUpgradeJingmai);
  tolua_constant(tolua_S,(char*)"aeUpgradeStone",aeUpgradeStone);
  tolua_constant(tolua_S,(char*)"aeUpgradeZhuling",aeUpgradeZhuling);
  tolua_constant(tolua_S,(char*)"aeUpgradeTupo",aeUpgradeTupo);
  tolua_constant(tolua_S,(char*)"aeEnterPublicBoss",aeEnterPublicBoss);
  tolua_constant(tolua_S,(char*)"aeOpenRole",aeOpenRole);
  tolua_constant(tolua_S,(char*)"aeZhuansheng",aeZhuansheng);
  tolua_constant(tolua_S,(char*)"aeUpgradeLoongSoul",aeUpgradeLoongSoul);
  tolua_constant(tolua_S,(char*)"aeUpgradeShield",aeUpgradeShield);
  tolua_constant(tolua_S,(char*)"aeFieldBoss",aeFieldBoss);
  tolua_constant(tolua_S,(char*)"aeAddEssence",aeAddEssence);
  tolua_constant(tolua_S,(char*)"aeAchievetaskFinish",aeAchievetaskFinish);
  tolua_constant(tolua_S,(char*)"aeChapterLevelFinish",aeChapterLevelFinish);
  tolua_constant(tolua_S,(char*)"aeFinishFuben",aeFinishFuben);
  tolua_constant(tolua_S,(char*)"aeCreateRole",aeCreateRole);
  tolua_constant(tolua_S,(char*)"aeBlessLevelChanged",aeBlessLevelChanged);
  tolua_constant(tolua_S,(char*)"aeLearnMiJi",aeLearnMiJi);
  tolua_constant(tolua_S,(char*)"aeGuildDonate",aeGuildDonate);
  tolua_constant(tolua_S,(char*)"aeChangeName",aeChangeName);
  tolua_constant(tolua_S,(char*)"aeTianTiChallenge",aeTianTiChallenge);
  tolua_constant(tolua_S,(char*)"aeMagicLevel",aeMagicLevel);
  tolua_constant(tolua_S,(char*)"aeWarSpiritlevel",aeWarSpiritlevel);
  tolua_constant(tolua_S,(char*)"aeWarSpiritstage",aeWarSpiritstage);
  tolua_constant(tolua_S,(char*)"aeOrange",aeOrange);
  tolua_constant(tolua_S,(char*)"aeLegend",aeLegend);
  tolua_constant(tolua_S,(char*)"aeCasting",aeCasting);
  tolua_constant(tolua_S,(char*)"aeArtifact",aeArtifact);
  tolua_constant(tolua_S,(char*)"aeArtifactstage",aeArtifactstage);
  tolua_constant(tolua_S,(char*)"aeParalysis",aeParalysis);
  tolua_constant(tolua_S,(char*)"aeProtective",aeProtective);
  tolua_constant(tolua_S,(char*)"aePersonalBoss",aePersonalBoss);
  tolua_constant(tolua_S,(char*)"aeFullBoss",aeFullBoss);
  tolua_constant(tolua_S,(char*)"aeTransferBoss",aeTransferBoss);
  tolua_constant(tolua_S,(char*)"aeHegemony",aeHegemony);
  tolua_constant(tolua_S,(char*)"aeloongLevelCount",aeloongLevelCount);
  tolua_constant(tolua_S,(char*)"aeShieldLevelCount",aeShieldLevelCount);
  tolua_constant(tolua_S,(char*)"aeXueyuLevelCount",aeXueyuLevelCount);
  tolua_constant(tolua_S,(char*)"aeGuildSkill",aeGuildSkill);
  tolua_constant(tolua_S,(char*)"aeAtkWorldBoss",aeAtkWorldBoss);
  tolua_constant(tolua_S,(char*)"aeMorship",aeMorship);
  tolua_constant(tolua_S,(char*)"aeGetTreasureBoxType",aeGetTreasureBoxType);
  tolua_constant(tolua_S,(char*)"aeChallengeFb",aeChallengeFb);
  tolua_constant(tolua_S,(char*)"aeTuJian",aeTuJian);
  tolua_constant(tolua_S,(char*)"aeFuWenLevel",aeFuWenLevel);
  tolua_constant(tolua_S,(char*)"aeTreasureBoxReward",aeTreasureBoxReward);
  tolua_constant(tolua_S,(char*)"aeReqChapterReward",aeReqChapterReward);
  tolua_constant(tolua_S,(char*)"aeReqChapterWorldReward",aeReqChapterWorldReward);
  tolua_constant(tolua_S,(char*)"aeKillChapterMonster",aeKillChapterMonster);
  tolua_constant(tolua_S,(char*)"aeXunBao",aeXunBao);
  tolua_constant(tolua_S,(char*)"aeGetWroldBossBelong",aeGetWroldBossBelong);
  tolua_constant(tolua_S,(char*)"aeKnighthoodLv",aeKnighthoodLv);
  tolua_constant(tolua_S,(char*)"aeNeiGongUp",aeNeiGongUp);
  tolua_constant(tolua_S,(char*)"aeActTogetherhit",aeActTogetherhit);
  tolua_constant(tolua_S,(char*)"aeUseTogetherhit",aeUseTogetherhit);
  tolua_constant(tolua_S,(char*)"aeActImba",aeActImba);
  tolua_constant(tolua_S,(char*)"aeActAExring",aeActAExring);
  tolua_constant(tolua_S,(char*)"aeUpAExring",aeUpAExring);
  tolua_constant(tolua_S,(char*)"aeOpenMonthCard",aeOpenMonthCard);
  tolua_constant(tolua_S,(char*)"aeShareGame",aeShareGame);
  tolua_constant(tolua_S,(char*)"aeTianTiLevel",aeTianTiLevel);
  tolua_constant(tolua_S,(char*)"aeSkirmishRank",aeSkirmishRank);
  tolua_constant(tolua_S,(char*)"aeDayLiLian",aeDayLiLian);
  tolua_constant(tolua_S,(char*)"aeDayFuBenSweep",aeDayFuBenSweep);
  tolua_constant(tolua_S,(char*)"aeFinishLimitTask",aeFinishLimitTask);
  tolua_constant(tolua_S,(char*)"aeGetItem",aeGetItem);
  tolua_constant(tolua_S,(char*)"aeActImbaItem",aeActImbaItem);
  tolua_constant(tolua_S,(char*)"aeCaiKuang",aeCaiKuang);
  tolua_constant(tolua_S,(char*)"aeDayFuBenWin",aeDayFuBenWin);
  tolua_constant(tolua_S,(char*)"aeHolyBoss",aeHolyBoss);
  tolua_constant(tolua_S,(char*)"aeNewWorldBoss",aeNewWorldBoss);
  tolua_constant(tolua_S,(char*)"aeCampBattleFb",aeCampBattleFb);
  tolua_constant(tolua_S,(char*)"aeGetWBossActScore",aeGetWBossActScore);
  tolua_constant(tolua_S,(char*)"aeMiJingBoss",aeMiJingBoss);
  tolua_constant(tolua_S,(char*)"aeLoseFuben",aeLoseFuben);
  tolua_constant(tolua_S,(char*)"aeJoinActivityId",aeJoinActivityId);
  tolua_constant(tolua_S,(char*)"aeRichManCircle",aeRichManCircle);
  tolua_constant(tolua_S,(char*)"aeExpFubenAwardType",aeExpFubenAwardType);
  tolua_constant(tolua_S,(char*)"aeWorldBoss",aeWorldBoss);
  tolua_constant(tolua_S,(char*)"aeZhuangBan",aeZhuangBan);
  tolua_constant(tolua_S,(char*)"aeChallengePVM",aeChallengePVM);
  tolua_constant(tolua_S,(char*)"aeAchievemwntAward",aeAchievemwntAward);
  tolua_constant(tolua_S,(char*)"aeSoulShieldAct",aeSoulShieldAct);
  tolua_constant(tolua_S,(char*)"aeNeiGongActive",aeNeiGongActive);
  tolua_constant(tolua_S,(char*)"fmCommon",fmCommon);
  tolua_constant(tolua_S,(char*)"fmSingle",fmSingle);
  tolua_constant(tolua_S,(char*)"fmTeam",fmTeam);
  tolua_constant(tolua_S,(char*)"fmTeamHero",fmTeamHero);
  tolua_constant(tolua_S,(char*)"fmGroup",fmGroup);
  tolua_constant(tolua_S,(char*)"fmGroupHero",fmGroupHero);
  tolua_constant(tolua_S,(char*)"fmJd",fmJd);
  tolua_constant(tolua_S,(char*)"fmMaxCount",fmMaxCount);
  tolua_constant(tolua_S,(char*)"tsCommon",tsCommon);
  tolua_constant(tolua_S,(char*)"tsReady",tsReady);
  tolua_constant(tolua_S,(char*)"tsWar",tsWar);
  tolua_constant(tolua_S,(char*)"ftCommon",ftCommon);
  tolua_constant(tolua_S,(char*)"ftChallenge",ftChallenge);
  tolua_constant(tolua_S,(char*)"ftWedding",ftWedding);
  tolua_constant(tolua_S,(char*)"fpPeaceful",fpPeaceful);
  tolua_constant(tolua_S,(char*)"fpTeam",fpTeam);
  tolua_constant(tolua_S,(char*)"fpGuild",fpGuild);
  tolua_constant(tolua_S,(char*)"fpZY",fpZY);
  tolua_constant(tolua_S,(char*)"fpPk",fpPk);
  tolua_constant(tolua_S,(char*)"fpAlly",fpAlly);
  tolua_constant(tolua_S,(char*)"fpUnion",fpUnion);
  tolua_constant(tolua_S,(char*)"fpServer",fpServer);
  tolua_constant(tolua_S,(char*)"fpSpecialPeaceful",fpSpecialPeaceful);
  tolua_constant(tolua_S,(char*)"fpCount",fpCount);
  tolua_constant(tolua_S,(char*)"qatItem",qatItem);
  tolua_constant(tolua_S,(char*)"qatRootExp",qatRootExp);
  tolua_constant(tolua_S,(char*)"qatExp",qatExp);
  tolua_constant(tolua_S,(char*)"qatGuildContribution",qatGuildContribution);
  tolua_constant(tolua_S,(char*)"qatZYContribution",qatZYContribution);
  tolua_constant(tolua_S,(char*)"qatBindMoney",qatBindMoney);
  tolua_constant(tolua_S,(char*)"qatMoney",qatMoney);
  tolua_constant(tolua_S,(char*)"qatBindYuanBao",qatBindYuanBao);
  tolua_constant(tolua_S,(char*)"qatTitle",qatTitle);
  tolua_constant(tolua_S,(char*)"qatSkill",qatSkill);
  tolua_constant(tolua_S,(char*)"qatShengWang",qatShengWang);
  tolua_constant(tolua_S,(char*)"qatRenown",qatRenown);
  tolua_constant(tolua_S,(char*)"qatPet",qatPet);
  tolua_constant(tolua_S,(char*)"qatStone",qatStone);
  tolua_constant(tolua_S,(char*)"qatYuanbao",qatYuanbao);
  tolua_constant(tolua_S,(char*)"qatHonor",qatHonor);
  tolua_constant(tolua_S,(char*)"qatCrossHonor",qatCrossHonor);
  tolua_constant(tolua_S,(char*)"qatCount",qatCount);
  tolua_constant(tolua_S,(char*)"qatCustomize",qatCustomize);
  tolua_constant(tolua_S,(char*)"gUseCallItem",gUseCallItem);
  tolua_constant(tolua_S,(char*)"gUpLevel",gUpLevel);
  tolua_constant(tolua_S,(char*)"gLeft",gLeft);
  tolua_constant(tolua_S,(char*)"seGiveUp",seGiveUp);
  tolua_constant(tolua_S,(char*)"seFinish",seFinish);
  tolua_constant(tolua_S,(char*)"seTimeout",seTimeout);
  tolua_constant(tolua_S,(char*)"seAddQuest",seAddQuest);
  tolua_constant(tolua_S,(char*)"seCanFinish",seCanFinish);
  tolua_constant(tolua_S,(char*)"seShowAccept",seShowAccept);
  tolua_constant(tolua_S,(char*)"eRrchargeType_NULL",eRrchargeType_NULL);
  tolua_constant(tolua_S,(char*)"eRrchargeType_FIRST",eRrchargeType_FIRST);
  tolua_constant(tolua_S,(char*)"eRrchargeType_NORMAL",eRrchargeType_NORMAL);
  tolua_constant(tolua_S,(char*)"eRrchargeType_MONTHCARD",eRrchargeType_MONTHCARD);
  tolua_constant(tolua_S,(char*)"eRrchargeType_PRIVIMONEY",eRrchargeType_PRIVIMONEY);
  tolua_constant(tolua_S,(char*)"eRrchargeType_LIMITPACKAGE",eRrchargeType_LIMITPACKAGE);
  tolua_constant(tolua_S,(char*)"eRrchargeType_ACTIVITY",eRrchargeType_ACTIVITY);
  tolua_module(tolua_S,(char*)"LActor",0);
  tolua_beginmodule(tolua_S,(char*)"LActor");
   tolua_function(tolua_S,(char*)"getEntity",tolua_server_LActor_getEntity00);
   tolua_function(tolua_S,(char*)"getId",tolua_server_LActor_getId00);
   tolua_function(tolua_S,(char*)"getActor",tolua_server_LActor_getActor00);
   tolua_function(tolua_S,(char*)"getActorById",tolua_server_LActor_getActorById00);
   tolua_function(tolua_S,(char*)"getServerId",tolua_server_LActor_getServerId00);
   tolua_function(tolua_S,(char*)"getServerIdById",tolua_server_LActor_getServerIdById00);
   tolua_function(tolua_S,(char*)"getActorByName",tolua_server_LActor_getActorByName00);
   tolua_function(tolua_S,(char*)"getActorByAccountName",tolua_server_LActor_getActorByAccountName00);
   tolua_function(tolua_S,(char*)"getActorIdByAccountName",tolua_server_LActor_getActorIdByAccountName00);
   tolua_function(tolua_S,(char*)"getActorIdByName",tolua_server_LActor_getActorIdByName00);
   tolua_function(tolua_S,(char*)"getActorData",tolua_server_LActor_getActorData00);
   tolua_function(tolua_S,(char*)"getName",tolua_server_LActor_getName00);
   tolua_function(tolua_S,(char*)"getLevel",tolua_server_LActor_getLevel00);
   tolua_function(tolua_S,(char*)"getJob",tolua_server_LActor_getJob00);
   tolua_function(tolua_S,(char*)"getSex",tolua_server_LActor_getSex00);
   tolua_function(tolua_S,(char*)"getLastLoginIp",tolua_server_LActor_getLastLoginIp00);
   tolua_function(tolua_S,(char*)"getActorDataById",tolua_server_LActor_getActorDataById00);
   tolua_function(tolua_S,(char*)"getActorLevel",tolua_server_LActor_getActorLevel00);
   tolua_function(tolua_S,(char*)"getActorZhuanShengLevel",tolua_server_LActor_getActorZhuanShengLevel00);
   tolua_function(tolua_S,(char*)"getActorName",tolua_server_LActor_getActorName00);
   tolua_function(tolua_S,(char*)"getActorPower",tolua_server_LActor_getActorPower00);
   tolua_function(tolua_S,(char*)"getActorJob",tolua_server_LActor_getActorJob00);
   tolua_function(tolua_S,(char*)"getActorSex",tolua_server_LActor_getActorSex00);
   tolua_function(tolua_S,(char*)"loginOtherSrv",tolua_server_LActor_loginOtherSrv00);
   tolua_function(tolua_S,(char*)"setLevel",tolua_server_LActor_setLevel00);
   tolua_function(tolua_S,(char*)"onLevelUp",tolua_server_LActor_onLevelUp00);
   tolua_function(tolua_S,(char*)"getExp",tolua_server_LActor_getExp00);
   tolua_function(tolua_S,(char*)"setExp",tolua_server_LActor_setExp00);
   tolua_function(tolua_S,(char*)"getRole",tolua_server_LActor_getRole00);
   tolua_function(tolua_S,(char*)"GetRoleByJob",tolua_server_LActor_GetRoleByJob00);
   tolua_function(tolua_S,(char*)"getRoleData",tolua_server_LActor_getRoleData00);
   tolua_function(tolua_S,(char*)"getRoleCount",tolua_server_LActor_getRoleCount00);
   tolua_function(tolua_S,(char*)"createRole",tolua_server_LActor_createRole00);
   tolua_function(tolua_S,(char*)"changeGold",tolua_server_LActor_changeGold00);
   tolua_function(tolua_S,(char*)"changeYuanBao",tolua_server_LActor_changeYuanBao00);
   tolua_function(tolua_S,(char*)"getCurrency",tolua_server_LActor_getCurrency00);
   tolua_function(tolua_S,(char*)"changeCurrency",tolua_server_LActor_changeCurrency00);
   tolua_function(tolua_S,(char*)"giveItem",tolua_server_LActor_giveItem00);
   tolua_function(tolua_S,(char*)"getEquipBagSpace",tolua_server_LActor_getEquipBagSpace00);
   tolua_function(tolua_S,(char*)"gmClearBag",tolua_server_LActor_gmClearBag00);
   tolua_function(tolua_S,(char*)"getShowName",tolua_server_LActor_getShowName00);
   tolua_function(tolua_S,(char*)"getHandle",tolua_server_LActor_getHandle00);
   tolua_function(tolua_S,(char*)"getActorOfflineTime",tolua_server_LActor_getActorOfflineTime00);
   tolua_function(tolua_S,(char*)"exitFuben",tolua_server_LActor_exitFuben00);
   tolua_function(tolua_S,(char*)"reEnterScene",tolua_server_LActor_reEnterScene00);
   tolua_function(tolua_S,(char*)"getFubenHandle",tolua_server_LActor_getFubenHandle00);
   tolua_function(tolua_S,(char*)"getSceneHandle",tolua_server_LActor_getSceneHandle00);
   tolua_function(tolua_S,(char*)"getFubenPrt",tolua_server_LActor_getFubenPrt00);
   tolua_function(tolua_S,(char*)"getFubenPtr",tolua_server_LActor_getFubenPtr00);
   tolua_function(tolua_S,(char*)"getScenePtr",tolua_server_LActor_getScenePtr00);
   tolua_function(tolua_S,(char*)"getFubenId",tolua_server_LActor_getFubenId00);
   tolua_function(tolua_S,(char*)"isInFuben",tolua_server_LActor_isInFuben00);
   tolua_function(tolua_S,(char*)"isBoss",tolua_server_LActor_isBoss00);
   tolua_function(tolua_S,(char*)"enterScene",tolua_server_LActor_enterScene00);
   tolua_function(tolua_S,(char*)"instantMove",tolua_server_LActor_instantMove00);
   tolua_function(tolua_S,(char*)"GetFuBenType",tolua_server_LActor_GetFuBenType00);
   tolua_function(tolua_S,(char*)"getChapterLevel",tolua_server_LActor_getChapterLevel00);
   tolua_function(tolua_S,(char*)"setChapterLevel",tolua_server_LActor_setChapterLevel00);
   tolua_function(tolua_S,(char*)"getVipLevel",tolua_server_LActor_getVipLevel00);
   tolua_function(tolua_S,(char*)"setVipLevel",tolua_server_LActor_setVipLevel00);
   tolua_function(tolua_S,(char*)"getMonthCard",tolua_server_LActor_getMonthCard00);
   tolua_function(tolua_S,(char*)"getRecharge",tolua_server_LActor_getRecharge00);
   tolua_function(tolua_S,(char*)"addRecharge",tolua_server_LActor_addRecharge00);
   tolua_function(tolua_S,(char*)"addRechargeOffline",tolua_server_LActor_addRechargeOffline00);
   tolua_function(tolua_S,(char*)"getEssence",tolua_server_LActor_getEssence00);
   tolua_function(tolua_S,(char*)"setEssence",tolua_server_LActor_setEssence00);
   tolua_function(tolua_S,(char*)"getExRingLevel",tolua_server_LActor_getExRingLevel00);
   tolua_function(tolua_S,(char*)"setExRingLevel",tolua_server_LActor_setExRingLevel00);
   tolua_function(tolua_S,(char*)"getActorExRingLevel",tolua_server_LActor_getActorExRingLevel00);
   tolua_function(tolua_S,(char*)"setActorExRingLevel",tolua_server_LActor_setActorExRingLevel00);
   tolua_function(tolua_S,(char*)"GetActorExRingIsEff",tolua_server_LActor_GetActorExRingIsEff00);
   tolua_function(tolua_S,(char*)"SetActorExRingIsEff",tolua_server_LActor_SetActorExRingIsEff00);
   tolua_function(tolua_S,(char*)"SetAexringMon",tolua_server_LActor_SetAexringMon00);
   tolua_function(tolua_S,(char*)"ClearExRingMonster",tolua_server_LActor_ClearExRingMonster00);
   tolua_function(tolua_S,(char*)"AddAerMonAttr",tolua_server_LActor_AddAerMonAttr00);
   tolua_function(tolua_S,(char*)"AddAerMonExAttr",tolua_server_LActor_AddAerMonExAttr00);
   tolua_function(tolua_S,(char*)"createSkirmishData",tolua_server_LActor_createSkirmishData00);
   tolua_function(tolua_S,(char*)"createKuangActorData",tolua_server_LActor_createKuangActorData00);
   tolua_function(tolua_S,(char*)"createFieldPlayerData",tolua_server_LActor_createFieldPlayerData00);
   tolua_function(tolua_S,(char*)"isDeath",tolua_server_LActor_isDeath00);
   tolua_function(tolua_S,(char*)"relive",tolua_server_LActor_relive00);
   tolua_function(tolua_S,(char*)"useSkill",tolua_server_LActor_useSkill00);
   tolua_function(tolua_S,(char*)"GetSkillLaveCD",tolua_server_LActor_GetSkillLaveCD00);
   tolua_function(tolua_S,(char*)"SetAllRoleSkillCdById",tolua_server_LActor_SetAllRoleSkillCdById00);
   tolua_function(tolua_S,(char*)"addSkillEffect",tolua_server_LActor_addSkillEffect00);
   tolua_function(tolua_S,(char*)"getMoneyCount",tolua_server_LActor_getMoneyCount00);
   tolua_function(tolua_S,(char*)"enterFuBen",tolua_server_LActor_enterFuBen00);
   tolua_function(tolua_S,(char*)"changeHp",tolua_server_LActor_changeHp00);
   tolua_function(tolua_S,(char*)"setHp",tolua_server_LActor_setHp00);
   tolua_function(tolua_S,(char*)"setMp",tolua_server_LActor_setMp00);
   tolua_function(tolua_S,(char*)"setNp",tolua_server_LActor_setNp00);
   tolua_function(tolua_S,(char*)"getHp",tolua_server_LActor_getHp00);
   tolua_function(tolua_S,(char*)"getNp",tolua_server_LActor_getNp00);
   tolua_function(tolua_S,(char*)"getHpMax",tolua_server_LActor_getHpMax00);
   tolua_function(tolua_S,(char*)"getMpMax",tolua_server_LActor_getMpMax00);
   tolua_function(tolua_S,(char*)"getAttr",tolua_server_LActor_getAttr00);
   tolua_function(tolua_S,(char*)"getAtkSum",tolua_server_LActor_getAtkSum00);
   tolua_function(tolua_S,(char*)"gmSetAttr",tolua_server_LActor_gmSetAttr00);
   tolua_function(tolua_S,(char*)"recover",tolua_server_LActor_recover00);
   tolua_function(tolua_S,(char*)"sendTipmsg",tolua_server_LActor_sendTipmsg00);
   tolua_function(tolua_S,(char*)"sendTipWithId",tolua_server_LActor_sendTipWithId00);
   tolua_function(tolua_S,(char*)"getActorPtrByName",tolua_server_LActor_getActorPtrByName00);
   tolua_function(tolua_S,(char*)"getLoginTime",tolua_server_LActor_getLoginTime00);
   tolua_function(tolua_S,(char*)"getLastLogoutTime",tolua_server_LActor_getLastLogoutTime00);
   tolua_function(tolua_S,(char*)"getLastLogoutDate",tolua_server_LActor_getLastLogoutDate00);
   tolua_function(tolua_S,(char*)"getLoginDate",tolua_server_LActor_getLoginDate00);
   tolua_function(tolua_S,(char*)"getStaticVar",tolua_server_LActor_getStaticVar00);
   tolua_function(tolua_S,(char*)"getCrossVar",tolua_server_LActor_getCrossVar00);
   tolua_function(tolua_S,(char*)"postScriptEvent",tolua_server_LActor_postScriptEvent00);
   tolua_function(tolua_S,(char*)"nextScriptEvent",tolua_server_LActor_nextScriptEvent00);
   tolua_function(tolua_S,(char*)"cancelScriptTimer",tolua_server_LActor_cancelScriptTimer00);
   tolua_function(tolua_S,(char*)"isMonster",tolua_server_LActor_isMonster00);
   tolua_function(tolua_S,(char*)"isActor",tolua_server_LActor_isActor00);
   tolua_function(tolua_S,(char*)"isPet",tolua_server_LActor_isPet00);
   tolua_function(tolua_S,(char*)"getActorId",tolua_server_LActor_getActorId00);
   tolua_function(tolua_S,(char*)"getCloneRoleActorId",tolua_server_LActor_getCloneRoleActorId00);
   tolua_function(tolua_S,(char*)"getAccountName",tolua_server_LActor_getAccountName00);
   tolua_function(tolua_S,(char*)"getAccountId",tolua_server_LActor_getAccountId00);
   tolua_function(tolua_S,(char*)"getEntityType",tolua_server_LActor_getEntityType00);
   tolua_function(tolua_S,(char*)"getPf",tolua_server_LActor_getPf00);
   tolua_function(tolua_S,(char*)"getAppid",tolua_server_LActor_getAppid00);
   tolua_function(tolua_S,(char*)"getPfId",tolua_server_LActor_getPfId00);
   tolua_function(tolua_S,(char*)"getCloneRoleIsMirror",tolua_server_LActor_getCloneRoleIsMirror00);
   tolua_function(tolua_S,(char*)"GetCloneRoleAttr",tolua_server_LActor_GetCloneRoleAttr00);
   tolua_function(tolua_S,(char*)"getItemCount",tolua_server_LActor_getItemCount00);
   tolua_function(tolua_S,(char*)"costItem",tolua_server_LActor_costItem00);
   tolua_function(tolua_S,(char*)"reCalcRoleAttr",tolua_server_LActor_reCalcRoleAttr00);
   tolua_function(tolua_S,(char*)"reCalcAttr",tolua_server_LActor_reCalcAttr00);
   tolua_function(tolua_S,(char*)"reCalcExAttr",tolua_server_LActor_reCalcExAttr00);
   tolua_function(tolua_S,(char*)"reCalcBattleAttr",tolua_server_LActor_reCalcBattleAttr00);
   tolua_function(tolua_S,(char*)"battleComparison",tolua_server_LActor_battleComparison00);
   tolua_function(tolua_S,(char*)"getWingInfo",tolua_server_LActor_getWingInfo00);
   tolua_function(tolua_S,(char*)"setWingLevel",tolua_server_LActor_setWingLevel00);
   tolua_function(tolua_S,(char*)"setWingStar",tolua_server_LActor_setWingStar00);
   tolua_function(tolua_S,(char*)"setWingExp",tolua_server_LActor_setWingExp00);
   tolua_function(tolua_S,(char*)"setWingStatus",tolua_server_LActor_setWingStatus00);
   tolua_function(tolua_S,(char*)"setWingCTime",tolua_server_LActor_setWingCTime00);
   tolua_function(tolua_S,(char*)"setWingPill",tolua_server_LActor_setWingPill00);
   tolua_function(tolua_S,(char*)"clearWingAttr",tolua_server_LActor_clearWingAttr00);
   tolua_function(tolua_S,(char*)"addWingAttr",tolua_server_LActor_addWingAttr00);
   tolua_function(tolua_S,(char*)"addWingTempAttr",tolua_server_LActor_addWingTempAttr00);
   tolua_function(tolua_S,(char*)"wingInfoSync",tolua_server_LActor_wingInfoSync00);
   tolua_function(tolua_S,(char*)"getEnhanceInfo",tolua_server_LActor_getEnhanceInfo00);
   tolua_function(tolua_S,(char*)"setEnhanceLevel",tolua_server_LActor_setEnhanceLevel00);
   tolua_function(tolua_S,(char*)"clearEnhanceAttr",tolua_server_LActor_clearEnhanceAttr00);
   tolua_function(tolua_S,(char*)"addEnhanceAttr",tolua_server_LActor_addEnhanceAttr00);
   tolua_function(tolua_S,(char*)"getFulingInfo",tolua_server_LActor_getFulingInfo00);
   tolua_function(tolua_S,(char*)"setFulingInfo",tolua_server_LActor_setFulingInfo00);
   tolua_function(tolua_S,(char*)"getFulingAttr",tolua_server_LActor_getFulingAttr00);
   tolua_function(tolua_S,(char*)"getFulingExAttr",tolua_server_LActor_getFulingExAttr00);
   tolua_function(tolua_S,(char*)"getSoulLevel",tolua_server_LActor_getSoulLevel00);
   tolua_function(tolua_S,(char*)"setSoulLevel",tolua_server_LActor_setSoulLevel00);
   tolua_function(tolua_S,(char*)"getSoulAttr",tolua_server_LActor_getSoulAttr00);
   tolua_function(tolua_S,(char*)"getSoulExAttr",tolua_server_LActor_getSoulExAttr00);
   tolua_function(tolua_S,(char*)"getJadePlateAttr",tolua_server_LActor_getJadePlateAttr00);
   tolua_function(tolua_S,(char*)"getJadePlateExAttr",tolua_server_LActor_getJadePlateExAttr00);
   tolua_function(tolua_S,(char*)"getZhiZunAttr",tolua_server_LActor_getZhiZunAttr00);
   tolua_function(tolua_S,(char*)"getZhiZunExAttr",tolua_server_LActor_getZhiZunExAttr00);
   tolua_function(tolua_S,(char*)"getLeiTingEquipAttrs",tolua_server_LActor_getLeiTingEquipAttrs00);
   tolua_function(tolua_S,(char*)"getLeiTingEquipExAttrs",tolua_server_LActor_getLeiTingEquipExAttrs00);
   tolua_function(tolua_S,(char*)"getTogetherPunchInfo",tolua_server_LActor_getTogetherPunchInfo00);
   tolua_function(tolua_S,(char*)"setTogetHerEquipLevel",tolua_server_LActor_setTogetHerEquipLevel00);
   tolua_function(tolua_S,(char*)"getTogetherPunchAttr",tolua_server_LActor_getTogetherPunchAttr00);
   tolua_function(tolua_S,(char*)"getTogetherPunchExAttr",tolua_server_LActor_getTogetherPunchExAttr00);
   tolua_function(tolua_S,(char*)"getMailInfo",tolua_server_LActor_getMailInfo00);
   tolua_function(tolua_S,(char*)"getMailList",tolua_server_LActor_getMailList00);
   tolua_function(tolua_S,(char*)"deleteMail",tolua_server_LActor_deleteMail00);
   tolua_function(tolua_S,(char*)"changeMailReadStatus",tolua_server_LActor_changeMailReadStatus00);
   tolua_function(tolua_S,(char*)"changeMailAwardStatus",tolua_server_LActor_changeMailAwardStatus00);
   tolua_function(tolua_S,(char*)"getStoneInfo",tolua_server_LActor_getStoneInfo00);
   tolua_function(tolua_S,(char*)"setStoneLevel",tolua_server_LActor_setStoneLevel00);
   tolua_function(tolua_S,(char*)"clearStoneAttr",tolua_server_LActor_clearStoneAttr00);
   tolua_function(tolua_S,(char*)"addStoneAttr",tolua_server_LActor_addStoneAttr00);
   tolua_function(tolua_S,(char*)"getJingmaiInfo",tolua_server_LActor_getJingmaiInfo00);
   tolua_function(tolua_S,(char*)"setJingmaiLevel",tolua_server_LActor_setJingmaiLevel00);
   tolua_function(tolua_S,(char*)"setJingmaiStage",tolua_server_LActor_setJingmaiStage00);
   tolua_function(tolua_S,(char*)"clearJingmaiAttr",tolua_server_LActor_clearJingmaiAttr00);
   tolua_function(tolua_S,(char*)"addJingmaiAttr",tolua_server_LActor_addJingmaiAttr00);
   tolua_function(tolua_S,(char*)"getZhulingInfo",tolua_server_LActor_getZhulingInfo00);
   tolua_function(tolua_S,(char*)"setZhulingLevel",tolua_server_LActor_setZhulingLevel00);
   tolua_function(tolua_S,(char*)"clearZhulingAttr",tolua_server_LActor_clearZhulingAttr00);
   tolua_function(tolua_S,(char*)"addZhulingAttr",tolua_server_LActor_addZhulingAttr00);
   tolua_function(tolua_S,(char*)"takeOutEquip",tolua_server_LActor_takeOutEquip00);
   tolua_function(tolua_S,(char*)"getEquipAttr",tolua_server_LActor_getEquipAttr00);
   tolua_function(tolua_S,(char*)"getEquipExAttr",tolua_server_LActor_getEquipExAttr00);
   tolua_function(tolua_S,(char*)"getZhuanShengAttr",tolua_server_LActor_getZhuanShengAttr00);
   tolua_function(tolua_S,(char*)"getNeigongAttr",tolua_server_LActor_getNeigongAttr00);
   tolua_function(tolua_S,(char*)"getExRingAttr",tolua_server_LActor_getExRingAttr00);
   tolua_function(tolua_S,(char*)"getExRingExAttr",tolua_server_LActor_getExRingExAttr00);
   tolua_function(tolua_S,(char*)"getActorExRingAttr",tolua_server_LActor_getActorExRingAttr00);
   tolua_function(tolua_S,(char*)"getActorExRingExAttr",tolua_server_LActor_getActorExRingExAttr00);
   tolua_function(tolua_S,(char*)"getActorExRingMonsterAttr",tolua_server_LActor_getActorExRingMonsterAttr00);
   tolua_function(tolua_S,(char*)"getActorExRingMonsterExAttr",tolua_server_LActor_getActorExRingMonsterExAttr00);
   tolua_function(tolua_S,(char*)"createActorExRingMonster",tolua_server_LActor_createActorExRingMonster00);
   tolua_function(tolua_S,(char*)"DestroyBattleRing",tolua_server_LActor_DestroyBattleRing00);
   tolua_function(tolua_S,(char*)"getActorExRingMonster",tolua_server_LActor_getActorExRingMonster00);
   tolua_function(tolua_S,(char*)"SetMasterHandle",tolua_server_LActor_SetMasterHandle00);
   tolua_function(tolua_S,(char*)"changeMonsterAi",tolua_server_LActor_changeMonsterAi00);
   tolua_function(tolua_S,(char*)"getTogetherHitAttr",tolua_server_LActor_getTogetherHitAttr00);
   tolua_function(tolua_S,(char*)"getTogetherHitExAttr",tolua_server_LActor_getTogetherHitExAttr00);
   tolua_function(tolua_S,(char*)"getTogetherHitSkillExAttr",tolua_server_LActor_getTogetherHitSkillExAttr00);
   tolua_function(tolua_S,(char*)"getActorsystemAttr",tolua_server_LActor_getActorsystemAttr00);
   tolua_function(tolua_S,(char*)"getZhuanShengLevel",tolua_server_LActor_getZhuanShengLevel00);
   tolua_function(tolua_S,(char*)"getReincarnateLv",tolua_server_LActor_getReincarnateLv00);
   tolua_function(tolua_S,(char*)"getRoleSkillLevel",tolua_server_LActor_getRoleSkillLevel00);
   tolua_function(tolua_S,(char*)"upgradeSkill",tolua_server_LActor_upgradeSkill00);
   tolua_function(tolua_S,(char*)"getRoleSkillBreakLevel",tolua_server_LActor_getRoleSkillBreakLevel00);
   tolua_function(tolua_S,(char*)"upgradeSkillBreak",tolua_server_LActor_upgradeSkillBreak00);
   tolua_function(tolua_S,(char*)"getStoreItemData",tolua_server_LActor_getStoreItemData00);
   tolua_function(tolua_S,(char*)"giveStoreItem",tolua_server_LActor_giveStoreItem00);
   tolua_function(tolua_S,(char*)"addStoreItem",tolua_server_LActor_addStoreItem00);
   tolua_function(tolua_S,(char*)"StoreClearList",tolua_server_LActor_StoreClearList00);
   tolua_function(tolua_S,(char*)"StoreDataSync",tolua_server_LActor_StoreDataSync00);
   tolua_function(tolua_S,(char*)"getAITarget",tolua_server_LActor_getAITarget00);
   tolua_function(tolua_S,(char*)"changeAITarget",tolua_server_LActor_changeAITarget00);
   tolua_function(tolua_S,(char*)"setAITarget",tolua_server_LActor_setAITarget00);
   tolua_function(tolua_S,(char*)"setAITargetNull",tolua_server_LActor_setAITargetNull00);
   tolua_function(tolua_S,(char*)"setAIPassivity",tolua_server_LActor_setAIPassivity00);
   tolua_function(tolua_S,(char*)"getAIPassivity",tolua_server_LActor_getAIPassivity00);
   tolua_function(tolua_S,(char*)"setAIAttackMonster",tolua_server_LActor_setAIAttackMonster00);
   tolua_function(tolua_S,(char*)"getSoulShieldinfo",tolua_server_LActor_getSoulShieldinfo00);
   tolua_function(tolua_S,(char*)"setSoulShieldLevel",tolua_server_LActor_setSoulShieldLevel00);
   tolua_function(tolua_S,(char*)"setSoulShieldStage",tolua_server_LActor_setSoulShieldStage00);
   tolua_function(tolua_S,(char*)"setSoulShieldExp",tolua_server_LActor_setSoulShieldExp00);
   tolua_function(tolua_S,(char*)"setSoulShieldAct",tolua_server_LActor_setSoulShieldAct00);
   tolua_function(tolua_S,(char*)"clearSoulShieldAttr",tolua_server_LActor_clearSoulShieldAttr00);
   tolua_function(tolua_S,(char*)"addSoulShieldAttr",tolua_server_LActor_addSoulShieldAttr00);
   tolua_function(tolua_S,(char*)"giveItemToDepot",tolua_server_LActor_giveItemToDepot00);
   tolua_function(tolua_S,(char*)"getDepotCount",tolua_server_LActor_getDepotCount00);
   tolua_function(tolua_S,(char*)"getRoleBasicAttr",tolua_server_LActor_getRoleBasicAttr00);
   tolua_function(tolua_S,(char*)"getKnighthoodAttr",tolua_server_LActor_getKnighthoodAttr00);
   tolua_function(tolua_S,(char*)"getKnighthoodExAttr",tolua_server_LActor_getKnighthoodExAttr00);
   tolua_function(tolua_S,(char*)"getYuPeiAttr",tolua_server_LActor_getYuPeiAttr00);
   tolua_function(tolua_S,(char*)"getYuPeiExAttr",tolua_server_LActor_getYuPeiExAttr00);
   tolua_function(tolua_S,(char*)"getPerstigeAttr",tolua_server_LActor_getPerstigeAttr00);
   tolua_function(tolua_S,(char*)"getArtifactsAttr",tolua_server_LActor_getArtifactsAttr00);
   tolua_function(tolua_S,(char*)"getTrainsystemAttr",tolua_server_LActor_getTrainsystemAttr00);
   tolua_function(tolua_S,(char*)"getTrainsystemExAttr",tolua_server_LActor_getTrainsystemExAttr00);
   tolua_function(tolua_S,(char*)"getChallengefbsystemAttr",tolua_server_LActor_getChallengefbsystemAttr00);
   tolua_function(tolua_S,(char*)"getRongLuAttr",tolua_server_LActor_getRongLuAttr00);
   tolua_function(tolua_S,(char*)"getMonthCardAttr",tolua_server_LActor_getMonthCardAttr00);
   tolua_function(tolua_S,(char*)"GetReincarnateAttr",tolua_server_LActor_GetReincarnateAttr00);
   tolua_function(tolua_S,(char*)"GetReincarnateExAttr",tolua_server_LActor_GetReincarnateExAttr00);
   tolua_function(tolua_S,(char*)"getPrivilegeAttr",tolua_server_LActor_getPrivilegeAttr00);
   tolua_function(tolua_S,(char*)"getVipAttr",tolua_server_LActor_getVipAttr00);
   tolua_function(tolua_S,(char*)"getNewWorldBossAttr",tolua_server_LActor_getNewWorldBossAttr00);
   tolua_function(tolua_S,(char*)"getGodWeaponAttr",tolua_server_LActor_getGodWeaponAttr00);
   tolua_function(tolua_S,(char*)"getGodWeaponExAttr",tolua_server_LActor_getGodWeaponExAttr00);
   tolua_function(tolua_S,(char*)"getCreateTime",tolua_server_LActor_getCreateTime00);
   tolua_function(tolua_S,(char*)"updataEquipBagCapacity",tolua_server_LActor_updataEquipBagCapacity00);
   tolua_function(tolua_S,(char*)"isImage",tolua_server_LActor_isImage00);
   tolua_function(tolua_S,(char*)"getGmLevel",tolua_server_LActor_getGmLevel00);
   tolua_function(tolua_S,(char*)"getEquipPointAttrs",tolua_server_LActor_getEquipPointAttrs00);
   tolua_function(tolua_S,(char*)"getActorInfoPacket",tolua_server_LActor_getActorInfoPacket00);
   tolua_function(tolua_S,(char*)"GetActorInfo",tolua_server_LActor_GetActorInfo00);
   tolua_function(tolua_S,(char*)"findTiantiActor",tolua_server_LActor_findTiantiActor00);
   tolua_function(tolua_S,(char*)"createRoldClone",tolua_server_LActor_createRoldClone00);
   tolua_function(tolua_S,(char*)"createRobot",tolua_server_LActor_createRobot00);
   tolua_function(tolua_S,(char*)"cloneRoleEmpty",tolua_server_LActor_cloneRoleEmpty00);
   tolua_function(tolua_S,(char*)"tiantiRefreshWeek",tolua_server_LActor_tiantiRefreshWeek00);
   tolua_function(tolua_S,(char*)"getEquipBlessAttrs",tolua_server_LActor_getEquipBlessAttrs00);
   tolua_function(tolua_S,(char*)"getTitleAttrs",tolua_server_LActor_getTitleAttrs00);
   tolua_function(tolua_S,(char*)"reCalcTitleAttr",tolua_server_LActor_reCalcTitleAttr00);
   tolua_function(tolua_S,(char*)"setRoleTitle",tolua_server_LActor_setRoleTitle00);
   tolua_function(tolua_S,(char*)"changeMiJi",tolua_server_LActor_changeMiJi00);
   tolua_function(tolua_S,(char*)"refreshMiJi",tolua_server_LActor_refreshMiJi00);
   tolua_function(tolua_S,(char*)"getRainingFirstCacheByType",tolua_server_LActor_getRainingFirstCacheByType00);
   tolua_function(tolua_S,(char*)"updateDynamicFirstCache",tolua_server_LActor_updateDynamicFirstCache00);
   tolua_function(tolua_S,(char*)"updateRanking",tolua_server_LActor_updateRanking00);
   tolua_function(tolua_S,(char*)"getRankDataByType",tolua_server_LActor_getRankDataByType00);
   tolua_function(tolua_S,(char*)"getRanking",tolua_server_LActor_getRanking00);
   tolua_function(tolua_S,(char*)"getRankCacheByType",tolua_server_LActor_getRankCacheByType00);
   tolua_function(tolua_S,(char*)"regAsynEvent",tolua_server_LActor_regAsynEvent00);
   tolua_function(tolua_S,(char*)"getGuildSkillAttrs",tolua_server_LActor_getGuildSkillAttrs00);
   tolua_function(tolua_S,(char*)"getGuildId",tolua_server_LActor_getGuildId00);
   tolua_function(tolua_S,(char*)"getGuildPtr",tolua_server_LActor_getGuildPtr00);
   tolua_function(tolua_S,(char*)"getGuildPos",tolua_server_LActor_getGuildPos00);
   tolua_function(tolua_S,(char*)"getGuildName",tolua_server_LActor_getGuildName00);
   tolua_function(tolua_S,(char*)"getTotalGx",tolua_server_LActor_getTotalGx00);
   tolua_function(tolua_S,(char*)"changeTotalGx",tolua_server_LActor_changeTotalGx00);
   tolua_function(tolua_S,(char*)"saveDb",tolua_server_LActor_saveDb00);
   tolua_function(tolua_S,(char*)"changeName",tolua_server_LActor_changeName00);
   tolua_function(tolua_S,(char*)"setEntityName",tolua_server_LActor_setEntityName00);
   tolua_function(tolua_S,(char*)"addEffect",tolua_server_LActor_addEffect00);
   tolua_function(tolua_S,(char*)"getItemData",tolua_server_LActor_getItemData00);
   tolua_function(tolua_S,(char*)"getItemIdByUid",tolua_server_LActor_getItemIdByUid00);
   tolua_function(tolua_S,(char*)"getItemInfoByUid",tolua_server_LActor_getItemInfoByUid00);
   tolua_function(tolua_S,(char*)"costItemByUid",tolua_server_LActor_costItemByUid00);
   tolua_function(tolua_S,(char*)"setCamp",tolua_server_LActor_setCamp00);
   tolua_function(tolua_S,(char*)"getCamp",tolua_server_LActor_getCamp00);
   tolua_function(tolua_S,(char*)"setCanChangeCamp",tolua_server_LActor_setCanChangeCamp00);
   tolua_function(tolua_S,(char*)"getLiveByPower",tolua_server_LActor_getLiveByPower00);
   tolua_function(tolua_S,(char*)"getLiveByJob",tolua_server_LActor_getLiveByJob00);
   tolua_function(tolua_S,(char*)"getEquipId",tolua_server_LActor_getEquipId00);
   tolua_function(tolua_S,(char*)"getEquipQuality",tolua_server_LActor_getEquipQuality00);
   tolua_function(tolua_S,(char*)"getEquipLevel",tolua_server_LActor_getEquipLevel00);
   tolua_function(tolua_S,(char*)"setZhanLingConfig",tolua_server_LActor_setZhanLingConfig00);
   tolua_function(tolua_S,(char*)"initZhanLingInfo",tolua_server_LActor_initZhanLingInfo00);
   tolua_function(tolua_S,(char*)"setZhanLingId",tolua_server_LActor_setZhanLingId00);
   tolua_function(tolua_S,(char*)"addZhanLingEffect",tolua_server_LActor_addZhanLingEffect00);
   tolua_function(tolua_S,(char*)"getBattlePet",tolua_server_LActor_getBattlePet00);
   tolua_function(tolua_S,(char*)"setZhuangBan",tolua_server_LActor_setZhuangBan00);
   tolua_function(tolua_S,(char*)"getZhuangBan",tolua_server_LActor_getZhuangBan00);
   tolua_function(tolua_S,(char*)"getRoleZhuangBanAttr",tolua_server_LActor_getRoleZhuangBanAttr00);
   tolua_function(tolua_S,(char*)"getMasterHdl",tolua_server_LActor_getMasterHdl00);
   tolua_function(tolua_S,(char*)"getMaster",tolua_server_LActor_getMaster00);
   tolua_function(tolua_S,(char*)"KillMonster",tolua_server_LActor_KillMonster00);
   tolua_function(tolua_S,(char*)"DestroyEntity",tolua_server_LActor_DestroyEntity00);
   tolua_function(tolua_S,(char*)"getOffMsg",tolua_server_LActor_getOffMsg00);
   tolua_function(tolua_S,(char*)"getOffMsgCnt",tolua_server_LActor_getOffMsgCnt00);
   tolua_function(tolua_S,(char*)"getOffMsgIndex",tolua_server_LActor_getOffMsgIndex00);
   tolua_function(tolua_S,(char*)"deleteOffMsg",tolua_server_LActor_deleteOffMsg00);
   tolua_function(tolua_S,(char*)"AddSkill",tolua_server_LActor_AddSkill00);
   tolua_function(tolua_S,(char*)"DelSkill",tolua_server_LActor_DelSkill00);
   tolua_function(tolua_S,(char*)"AddAISkill",tolua_server_LActor_AddAISkill00);
   tolua_function(tolua_S,(char*)"DelAISkill",tolua_server_LActor_DelAISkill00);
   tolua_function(tolua_S,(char*)"DelAllAISkill",tolua_server_LActor_DelAllAISkill00);
   tolua_function(tolua_S,(char*)"DelSkillById",tolua_server_LActor_DelSkillById00);
   tolua_function(tolua_S,(char*)"DelAllSkill",tolua_server_LActor_DelAllSkill00);
   tolua_function(tolua_S,(char*)"AddPassiveSkill",tolua_server_LActor_AddPassiveSkill00);
   tolua_function(tolua_S,(char*)"DelPassiveSkill",tolua_server_LActor_DelPassiveSkill00);
   tolua_function(tolua_S,(char*)"DelPassiveSkillById",tolua_server_LActor_DelPassiveSkillById00);
   tolua_function(tolua_S,(char*)"TogetherHitInfoSync",tolua_server_LActor_TogetherHitInfoSync00);
   tolua_function(tolua_S,(char*)"getFuWenuIdInfo",tolua_server_LActor_getFuWenuIdInfo00);
   tolua_function(tolua_S,(char*)"CheckFuWenByPost",tolua_server_LActor_CheckFuWenByPost00);
   tolua_function(tolua_S,(char*)"SetFuwen",tolua_server_LActor_SetFuwen00);
   tolua_function(tolua_S,(char*)"FuwenLevelup",tolua_server_LActor_FuwenLevelup00);
   tolua_function(tolua_S,(char*)"addFuWenExattr",tolua_server_LActor_addFuWenExattr00);
   tolua_function(tolua_S,(char*)"CalcExAttr",tolua_server_LActor_CalcExAttr00);
   tolua_function(tolua_S,(char*)"clearFuWenAttr",tolua_server_LActor_clearFuWenAttr00);
   tolua_function(tolua_S,(char*)"addFuWenAttr",tolua_server_LActor_addFuWenAttr00);
   tolua_function(tolua_S,(char*)"getFuWenAttr",tolua_server_LActor_getFuWenAttr00);
   tolua_function(tolua_S,(char*)"addImbaExattr",tolua_server_LActor_addImbaExattr00);
   tolua_function(tolua_S,(char*)"clearImbaAttr",tolua_server_LActor_clearImbaAttr00);
   tolua_function(tolua_S,(char*)"addImbaAttr",tolua_server_LActor_addImbaAttr00);
   tolua_function(tolua_S,(char*)"getImbaAttr",tolua_server_LActor_getImbaAttr00);
   tolua_function(tolua_S,(char*)"getPosition",tolua_server_LActor_getPosition00);
   tolua_function(tolua_S,(char*)"getOriginPosition",tolua_server_LActor_getOriginPosition00);
   tolua_function(tolua_S,(char*)"getDropBagData",tolua_server_LActor_getDropBagData00);
   tolua_function(tolua_S,(char*)"SetInvincible",tolua_server_LActor_SetInvincible00);
   tolua_function(tolua_S,(char*)"getActorByEt",tolua_server_LActor_getActorByEt00);
   tolua_function(tolua_S,(char*)"clearImbaActId",tolua_server_LActor_clearImbaActId00);
   tolua_function(tolua_S,(char*)"addImbaActId",tolua_server_LActor_addImbaActId00);
   tolua_function(tolua_S,(char*)"clearGodWeaponActId",tolua_server_LActor_clearGodWeaponActId00);
   tolua_function(tolua_S,(char*)"addGodWeaponActId",tolua_server_LActor_addGodWeaponActId00);
   tolua_function(tolua_S,(char*)"setGodWeaponPeak",tolua_server_LActor_setGodWeaponPeak00);
   tolua_function(tolua_S,(char*)"setGodWeaponLevel",tolua_server_LActor_setGodWeaponLevel00);
   tolua_function(tolua_S,(char*)"setGodWeaponPower",tolua_server_LActor_setGodWeaponPower00);
   tolua_function(tolua_S,(char*)"clearGodWeaponPower",tolua_server_LActor_clearGodWeaponPower00);
   tolua_function(tolua_S,(char*)"getHeirloomLv",tolua_server_LActor_getHeirloomLv00);
   tolua_function(tolua_S,(char*)"setHeirloomLv",tolua_server_LActor_setHeirloomLv00);
   tolua_function(tolua_S,(char*)"GetHeirloomAttrs",tolua_server_LActor_GetHeirloomAttrs00);
   tolua_function(tolua_S,(char*)"GetWeaponSoulAttrs",tolua_server_LActor_GetWeaponSoulAttrs00);
   tolua_function(tolua_S,(char*)"GetWeaponSoulExAttrs",tolua_server_LActor_GetWeaponSoulExAttrs00);
   tolua_function(tolua_S,(char*)"GetGodWingAttrs",tolua_server_LActor_GetGodWingAttrs00);
   tolua_function(tolua_S,(char*)"GetCampBattleAttrs",tolua_server_LActor_GetCampBattleAttrs00);
   tolua_function(tolua_S,(char*)"GetReincarnateEquipAttr",tolua_server_LActor_GetReincarnateEquipAttr00);
   tolua_function(tolua_S,(char*)"GetReincarnateEquipExAttr",tolua_server_LActor_GetReincarnateEquipExAttr00);
   tolua_function(tolua_S,(char*)"GetGodWingExAttrs",tolua_server_LActor_GetGodWingExAttrs00);
   tolua_function(tolua_S,(char*)"GetWingExAttrs",tolua_server_LActor_GetWingExAttrs00);
   tolua_function(tolua_S,(char*)"getUseingWeaponSoulId",tolua_server_LActor_getUseingWeaponSoulId00);
   tolua_function(tolua_S,(char*)"setUseingWeaponSoulId",tolua_server_LActor_setUseingWeaponSoulId00);
   tolua_function(tolua_S,(char*)"TuJianPower",tolua_server_LActor_TuJianPower00);
   tolua_function(tolua_S,(char*)"getEquipBasePower",tolua_server_LActor_getEquipBasePower00);
   tolua_function(tolua_S,(char*)"hasJobRole",tolua_server_LActor_hasJobRole00);
   tolua_function(tolua_S,(char*)"SetTogeLv",tolua_server_LActor_SetTogeLv00);
   tolua_function(tolua_S,(char*)"SetYuPeiLv",tolua_server_LActor_SetYuPeiLv00);
   tolua_function(tolua_S,(char*)"InSafeArea",tolua_server_LActor_InSafeArea00);
   tolua_function(tolua_S,(char*)"stopAI",tolua_server_LActor_stopAI00);
   tolua_function(tolua_S,(char*)"getSceneAreaIParm",tolua_server_LActor_getSceneAreaIParm00);
   tolua_function(tolua_S,(char*)"RequestFubenPathLine",tolua_server_LActor_RequestFubenPathLine00);
   tolua_function(tolua_S,(char*)"MonsterFubenPathLine",tolua_server_LActor_MonsterFubenPathLine00);
   tolua_function(tolua_S,(char*)"getSceneId",tolua_server_LActor_getSceneId00);
   tolua_function(tolua_S,(char*)"clearAttrs",tolua_server_LActor_clearAttrs00);
   tolua_function(tolua_S,(char*)"addAttrsBaseAttr",tolua_server_LActor_addAttrsBaseAttr00);
   tolua_function(tolua_S,(char*)"addAttrsExaPower",tolua_server_LActor_addAttrsExaPower00);
   tolua_function(tolua_S,(char*)"getAttrs",tolua_server_LActor_getAttrs00);
   tolua_function(tolua_S,(char*)"AddSkillRevise",tolua_server_LActor_AddSkillRevise00);
   tolua_function(tolua_S,(char*)"AddSkillReviseSelfBuff",tolua_server_LActor_AddSkillReviseSelfBuff00);
   tolua_function(tolua_S,(char*)"AddSkillReviseTarBuff",tolua_server_LActor_AddSkillReviseTarBuff00);
   tolua_function(tolua_S,(char*)"SetFlameStampLv",tolua_server_LActor_SetFlameStampLv00);
   tolua_function(tolua_S,(char*)"SetFlameStampSkillLv",tolua_server_LActor_SetFlameStampSkillLv00);
   tolua_function(tolua_S,(char*)"SetSkillCdById",tolua_server_LActor_SetSkillCdById00);
   tolua_function(tolua_S,(char*)"CIsEquip",tolua_server_LActor_CIsEquip00);
   tolua_function(tolua_S,(char*)"AddPVMRecord",tolua_server_LActor_AddPVMRecord00);
   tolua_function(tolua_S,(char*)"UpdataRank",tolua_server_LActor_UpdataRank00);
   tolua_function(tolua_S,(char*)"SendPVMRank",tolua_server_LActor_SendPVMRank00);
   tolua_function(tolua_S,(char*)"SendPVMRecord",tolua_server_LActor_SendPVMRecord00);
   tolua_function(tolua_S,(char*)"InitMaxRecordCount",tolua_server_LActor_InitMaxRecordCount00);
   tolua_function(tolua_S,(char*)"GetPlayerIDByPVMRank",tolua_server_LActor_GetPlayerIDByPVMRank00);
   tolua_function(tolua_S,(char*)"GetPVMRankByPlayerID",tolua_server_LActor_GetPVMRankByPlayerID00);
   tolua_function(tolua_S,(char*)"GetPVMRankSize",tolua_server_LActor_GetPVMRankSize00);
   tolua_function(tolua_S,(char*)"UpdataPvmRankOldData",tolua_server_LActor_UpdataPvmRankOldData00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,(char*)"Fuben",0);
  tolua_beginmodule(tolua_S,(char*)"Fuben");
   tolua_function(tolua_S,(char*)"createFuBen",tolua_server_Fuben_createFuBen00);
   tolua_function(tolua_S,(char*)"closeFuben",tolua_server_Fuben_closeFuben00);
   tolua_function(tolua_S,(char*)"setEnd",tolua_server_Fuben_setEnd00);
   tolua_function(tolua_S,(char*)"setBelong",tolua_server_Fuben_setBelong00);
   tolua_function(tolua_S,(char*)"setIsNeedAi",tolua_server_Fuben_setIsNeedAi00);
   tolua_function(tolua_S,(char*)"getFubenHandle",tolua_server_Fuben_getFubenHandle00);
   tolua_function(tolua_S,(char*)"getFubenPtr",tolua_server_Fuben_getFubenPtr00);
   tolua_function(tolua_S,(char*)"getStaticFubenHandle",tolua_server_Fuben_getStaticFubenHandle00);
   tolua_function(tolua_S,(char*)"createMonster",tolua_server_Fuben_createMonster00);
   tolua_function(tolua_S,(char*)"createDropBag",tolua_server_Fuben_createDropBag00);
   tolua_function(tolua_S,(char*)"RewardDropBag",tolua_server_Fuben_RewardDropBag00);
   tolua_function(tolua_S,(char*)"sendData",tolua_server_Fuben_sendData00);
   tolua_function(tolua_S,(char*)"sendDataNoActor",tolua_server_Fuben_sendDataNoActor00);
   tolua_function(tolua_S,(char*)"getAllActor",tolua_server_Fuben_getAllActor00);
   tolua_function(tolua_S,(char*)"getAllMonster",tolua_server_Fuben_getAllMonster00);
   tolua_function(tolua_S,(char*)"getAllDropBag",tolua_server_Fuben_getAllDropBag00);
   tolua_function(tolua_S,(char*)"getAllCloneRole",tolua_server_Fuben_getAllCloneRole00);
   tolua_function(tolua_S,(char*)"getActorCount",tolua_server_Fuben_getActorCount00);
   tolua_function(tolua_S,(char*)"GetResActorMirrorCount",tolua_server_Fuben_GetResActorMirrorCount00);
   tolua_function(tolua_S,(char*)"getCloneRole",tolua_server_Fuben_getCloneRole00);
   tolua_function(tolua_S,(char*)"releaseInstance",tolua_server_Fuben_releaseInstance00);
   tolua_function(tolua_S,(char*)"getMonsterId",tolua_server_Fuben_getMonsterId00);
   tolua_function(tolua_S,(char*)"isKillAllMonster",tolua_server_Fuben_isKillAllMonster00);
   tolua_function(tolua_S,(char*)"killAllMonster",tolua_server_Fuben_killAllMonster00);
   tolua_function(tolua_S,(char*)"clearAllMonster",tolua_server_Fuben_clearAllMonster00);
   tolua_function(tolua_S,(char*)"clearAllCloneRole",tolua_server_Fuben_clearAllCloneRole00);
   tolua_function(tolua_S,(char*)"clearCloneRoleById",tolua_server_Fuben_clearCloneRoleById00);
   tolua_function(tolua_S,(char*)"getMonsterMaxHp",tolua_server_Fuben_getMonsterMaxHp00);
   tolua_function(tolua_S,(char*)"setMonsterCamp",tolua_server_Fuben_setMonsterCamp00);
   tolua_function(tolua_S,(char*)"setBaseAttr",tolua_server_Fuben_setBaseAttr00);
   tolua_function(tolua_S,(char*)"getSceneMonsterById",tolua_server_Fuben_getSceneMonsterById00);
   tolua_function(tolua_S,(char*)"Getscenelist",tolua_server_Fuben_Getscenelist00);
   tolua_function(tolua_S,(char*)"getSceneHandlebyPtr",tolua_server_Fuben_getSceneHandlebyPtr00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,(char*)"print",tolua_server_print00);
  tolua_module(tolua_S,(char*)"System",0);
  tolua_beginmodule(tolua_S,(char*)"System");
   tolua_function(tolua_S,(char*)"version",tolua_server_System_version00);
   tolua_function(tolua_S,(char*)"reloadGlobalNpc",tolua_server_System_reloadGlobalNpc00);
   tolua_function(tolua_S,(char*)"getServerName",tolua_server_System_getServerName00);
   tolua_function(tolua_S,(char*)"getServerId",tolua_server_System_getServerId00);
   tolua_function(tolua_S,(char*)"getWebServer",tolua_server_System_getWebServer00);
   tolua_function(tolua_S,(char*)"isServerStarted",tolua_server_System_isServerStarted00);
   tolua_function(tolua_S,(char*)"getDate",tolua_server_System_getDate00);
   tolua_function(tolua_S,(char*)"getTime",tolua_server_System_getTime00);
   tolua_function(tolua_S,(char*)"getUnixTime",tolua_server_System_getUnixTime00);
   tolua_function(tolua_S,(char*)"getTick",tolua_server_System_getTick00);
   tolua_function(tolua_S,(char*)"getDayOfWeek",tolua_server_System_getDayOfWeek00);
   tolua_function(tolua_S,(char*)"getRandomNumber",tolua_server_System_getRandomNumber00);
   tolua_function(tolua_S,(char*)"getNowTime",tolua_server_System_getNowTime00);
   tolua_function(tolua_S,(char*)"encodeTime",tolua_server_System_encodeTime00);
   tolua_function(tolua_S,(char*)"getDiffendTime",tolua_server_System_getDiffendTime00);
   tolua_function(tolua_S,(char*)"getWeekDataTime",tolua_server_System_getWeekDataTime00);
   tolua_function(tolua_S,(char*)"isSameWeek",tolua_server_System_isSameWeek00);
   tolua_function(tolua_S,(char*)"trace",tolua_server_System_trace00);
   tolua_function(tolua_S,(char*)"deepCreateDirectory",tolua_server_System_deepCreateDirectory00);
   tolua_function(tolua_S,(char*)"fileExists",tolua_server_System_fileExists00);
   tolua_function(tolua_S,(char*)"getActorPtr",tolua_server_System_getActorPtr00);
   tolua_function(tolua_S,(char*)"broadcastTipmsg",tolua_server_System_broadcastTipmsg00);
   tolua_function(tolua_S,(char*)"broadcastLevelTipmsg",tolua_server_System_broadcastLevelTipmsg00);
   tolua_function(tolua_S,(char*)"broadcastTipmsgWithID",tolua_server_System_broadcastTipmsgWithID00);
   tolua_function(tolua_S,(char*)"broadcastData",tolua_server_System_broadcastData00);
   tolua_function(tolua_S,(char*)"getEntityByPtr",tolua_server_System_getEntityByPtr00);
   tolua_function(tolua_S,(char*)"getAllActorList",tolua_server_System_getAllActorList00);
   tolua_function(tolua_S,(char*)"getEntityTypeByHandle",tolua_server_System_getEntityTypeByHandle00);
   tolua_function(tolua_S,(char*)"getEntityPtrByActorID",tolua_server_System_getEntityPtrByActorID00);
   tolua_function(tolua_S,(char*)"isInTimeRange",tolua_server_System_isInTimeRange00);
   tolua_function(tolua_S,(char*)"getToday",tolua_server_System_getToday00);
   tolua_function(tolua_S,(char*)"getYesterday",tolua_server_System_getYesterday00);
   tolua_function(tolua_S,(char*)"getGlobalNpc",tolua_server_System_getGlobalNpc00);
   tolua_function(tolua_S,(char*)"getReserveNpc",tolua_server_System_getReserveNpc00);
   tolua_function(tolua_S,(char*)"getStaticVar",tolua_server_System_getStaticVar00);
   tolua_function(tolua_S,(char*)"getSystemDef",tolua_server_System_getSystemDef00);
   tolua_function(tolua_S,(char*)"getServerOpenTime",tolua_server_System_getServerOpenTime00);
   tolua_function(tolua_S,(char*)"isSameDay",tolua_server_System_isSameDay00);
   tolua_function(tolua_S,(char*)"setEntityShowName",tolua_server_System_setEntityShowName00);
   tolua_function(tolua_S,(char*)"getOpenServerDay",tolua_server_System_getOpenServerDay00);
   tolua_function(tolua_S,(char*)"getTimeToNowDay",tolua_server_System_getTimeToNowDay00);
   tolua_function(tolua_S,(char*)"getOpenServerStartDateTime",tolua_server_System_getOpenServerStartDateTime00);
   tolua_function(tolua_S,(char*)"getOpenServerTime",tolua_server_System_getOpenServerTime00);
   tolua_function(tolua_S,(char*)"setOpenServerTime",tolua_server_System_setOpenServerTime00);
   tolua_function(tolua_S,(char*)"getRestTimeFromOpenServer",tolua_server_System_getRestTimeFromOpenServer00);
   tolua_function(tolua_S,(char*)"bitOPMask",tolua_server_System_bitOPMask00);
   tolua_function(tolua_S,(char*)"bitOpNot",tolua_server_System_bitOpNot00);
   tolua_function(tolua_S,(char*)"bitOpAnd",tolua_server_System_bitOpAnd00);
   tolua_function(tolua_S,(char*)"bitOpOr",tolua_server_System_bitOpOr00);
   tolua_function(tolua_S,(char*)"bitOpRig",tolua_server_System_bitOpRig00);
   tolua_function(tolua_S,(char*)"bitOpLeft",tolua_server_System_bitOpLeft00);
   tolua_function(tolua_S,(char*)"bitOpSetMask",tolua_server_System_bitOpSetMask00);
   tolua_function(tolua_S,(char*)"makeInt16",tolua_server_System_makeInt1600);
   tolua_function(tolua_S,(char*)"makeInt32",tolua_server_System_makeInt3200);
   tolua_function(tolua_S,(char*)"makeHiInt16",tolua_server_System_makeHiInt1600);
   tolua_function(tolua_S,(char*)"makeLoInt16",tolua_server_System_makeLoInt1600);
   tolua_function(tolua_S,(char*)"makeHiInt8",tolua_server_System_makeHiInt800);
   tolua_function(tolua_S,(char*)"makeLoInt8",tolua_server_System_makeLoInt800);
   tolua_function(tolua_S,(char*)"int32Byte",tolua_server_System_int32Byte00);
   tolua_function(tolua_S,(char*)"byteInt32",tolua_server_System_byteInt3200);
   tolua_function(tolua_S,(char*)"timeEncode",tolua_server_System_timeEncode00);
   tolua_function(tolua_S,(char*)"timeDecode",tolua_server_System_timeDecode00);
   tolua_function(tolua_S,(char*)"logCounter",tolua_server_System_logCounter00);
   tolua_function(tolua_S,(char*)"logEnconomy",tolua_server_System_logEnconomy00);
   tolua_function(tolua_S,(char*)"logMilestone",tolua_server_System_logMilestone00);
   tolua_function(tolua_S,(char*)"logPayment",tolua_server_System_logPayment00);
   tolua_function(tolua_S,(char*)"logInstall",tolua_server_System_logInstall00);
   tolua_function(tolua_S,(char*)"logDau",tolua_server_System_logDau00);
   tolua_function(tolua_S,(char*)"logGameInfo",tolua_server_System_logGameInfo00);
   tolua_function(tolua_S,(char*)"logChat",tolua_server_System_logChat00);
   tolua_function(tolua_S,(char*)"logTLog",tolua_server_System_logTLog00);
   tolua_function(tolua_S,(char*)"logOnline",tolua_server_System_logOnline00);
   tolua_function(tolua_S,(char*)"getOnlineCount",tolua_server_System_getOnlineCount00);
   tolua_function(tolua_S,(char*)"actorMgrReloadScript",tolua_server_System_actorMgrReloadScript00);
   tolua_function(tolua_S,(char*)"actorMgrLoadFilterNames",tolua_server_System_actorMgrLoadFilterNames00);
   tolua_function(tolua_S,(char*)"dbClose",tolua_server_System_dbClose00);
   tolua_function(tolua_S,(char*)"dbConnect",tolua_server_System_dbConnect00);
   tolua_function(tolua_S,(char*)"getGameEngineGlobalDbConn",tolua_server_System_getGameEngineGlobalDbConn00);
   tolua_function(tolua_S,(char*)"createActorsDbConn",tolua_server_System_createActorsDbConn00);
   tolua_function(tolua_S,(char*)"delActorsDbConn",tolua_server_System_delActorsDbConn00);
   tolua_function(tolua_S,(char*)"dbQuery",tolua_server_System_dbQuery00);
   tolua_function(tolua_S,(char*)"dbExe",tolua_server_System_dbExe00);
   tolua_function(tolua_S,(char*)"dbResetQuery",tolua_server_System_dbResetQuery00);
   tolua_function(tolua_S,(char*)"dbCurrentRow",tolua_server_System_dbCurrentRow00);
   tolua_function(tolua_S,(char*)"dbGetRow",tolua_server_System_dbGetRow00);
   tolua_function(tolua_S,(char*)"dbGetRowCount",tolua_server_System_dbGetRowCount00);
   tolua_function(tolua_S,(char*)"dbNextRow",tolua_server_System_dbNextRow00);
   tolua_function(tolua_S,(char*)"geAddRoutes",tolua_server_System_geAddRoutes00);
   tolua_function(tolua_S,(char*)"geHasRoute",tolua_server_System_geHasRoute00);
   tolua_function(tolua_S,(char*)"getStrLenUtf8",tolua_server_System_getStrLenUtf800);
   tolua_function(tolua_S,(char*)"SendToDb",tolua_server_System_SendToDb00);
   tolua_function(tolua_S,(char*)"allocDBPacket",tolua_server_System_allocDBPacket00);
   tolua_function(tolua_S,(char*)"flushDBPacket",tolua_server_System_flushDBPacket00);
   tolua_function(tolua_S,(char*)"getDayDiff",tolua_server_System_getDayDiff00);
   tolua_function(tolua_S,(char*)"start5sScripte",tolua_server_System_start5sScripte00);
   tolua_function(tolua_S,(char*)"sendOffMsg",tolua_server_System_sendOffMsg00);
   tolua_function(tolua_S,(char*)"saveChatMonitoring",tolua_server_System_saveChatMonitoring00);
   tolua_function(tolua_S,(char*)"checkIdentity",tolua_server_System_checkIdentity00);
   tolua_function(tolua_S,(char*)"setEngineGcActorCnt",tolua_server_System_setEngineGcActorCnt00);
   tolua_function(tolua_S,(char*)"engineGc",tolua_server_System_engineGc00);
   tolua_function(tolua_S,(char*)"stopLog",tolua_server_System_stopLog00);
   tolua_function(tolua_S,(char*)"stopCounterLog",tolua_server_System_stopCounterLog00);
   tolua_function(tolua_S,(char*)"stopEconomyLog",tolua_server_System_stopEconomyLog00);
   tolua_function(tolua_S,(char*)"getSystemTime",tolua_server_System_getSystemTime00);
   tolua_function(tolua_S,(char*)"setActorDbSaveTime",tolua_server_System_setActorDbSaveTime00);
   tolua_function(tolua_S,(char*)"closeActor",tolua_server_System_closeActor00);
   tolua_function(tolua_S,(char*)"getSysVar",tolua_server_System_getSysVar00);
   tolua_function(tolua_S,(char*)"createSysVar",tolua_server_System_createSysVar00);
   tolua_function(tolua_S,(char*)"saveSysVar",tolua_server_System_saveSysVar00);
   tolua_function(tolua_S,(char*)"reloadSysVar",tolua_server_System_reloadSysVar00);
   tolua_function(tolua_S,(char*)"saveSysTmpVar",tolua_server_System_saveSysTmpVar00);
   tolua_function(tolua_S,(char*)"loadSysTmpVar",tolua_server_System_loadSysTmpVar00);
   tolua_function(tolua_S,(char*)"startOneGameClient",tolua_server_System_startOneGameClient00);
   tolua_function(tolua_S,(char*)"resetGameRoute",tolua_server_System_resetGameRoute00);
   tolua_function(tolua_S,(char*)"resetSingleGameRoute",tolua_server_System_resetSingleGameRoute00);
   tolua_function(tolua_S,(char*)"setBattleSrvFlag",tolua_server_System_setBattleSrvFlag00);
   tolua_function(tolua_S,(char*)"getBattleSrvFlag",tolua_server_System_getBattleSrvFlag00);
   tolua_function(tolua_S,(char*)"isBattleSrv",tolua_server_System_isBattleSrv00);
   tolua_function(tolua_S,(char*)"isLianFuSrv",tolua_server_System_isLianFuSrv00);
   tolua_function(tolua_S,(char*)"isCommSrv",tolua_server_System_isCommSrv00);
   tolua_function(tolua_S,(char*)"isCrossWarSrv",tolua_server_System_isCrossWarSrv00);
   tolua_function(tolua_S,(char*)"sendMsgToAllGameClient",tolua_server_System_sendMsgToAllGameClient00);
   tolua_function(tolua_S,(char*)"sendPacketToAllGameClient",tolua_server_System_sendPacketToAllGameClient00);
   tolua_function(tolua_S,(char*)"removeBattleSrv",tolua_server_System_removeBattleSrv00);
   tolua_function(tolua_S,(char*)"loadStringFromFile",tolua_server_System_loadStringFromFile00);
   tolua_function(tolua_S,(char*)"reloadFilterDb",tolua_server_System_reloadFilterDb00);
   tolua_function(tolua_S,(char*)"filterText",tolua_server_System_filterText00);
   tolua_function(tolua_S,(char*)"filterTextCount",tolua_server_System_filterTextCount00);
   tolua_function(tolua_S,(char*)"execute",tolua_server_System_execute00);
   tolua_function(tolua_S,(char*)"outputConfigFile",tolua_server_System_outputConfigFile00);
   tolua_function(tolua_S,(char*)"startAsyncWorker",tolua_server_System_startAsyncWorker00);
   tolua_function(tolua_S,(char*)"reloadWorkerScript",tolua_server_System_reloadWorkerScript00);
   tolua_function(tolua_S,(char*)"sendMessageToAsyncWorker",tolua_server_System_sendMessageToAsyncWorker00);
   tolua_function(tolua_S,(char*)"regScriptNetMsg",tolua_server_System_regScriptNetMsg00);
   tolua_function(tolua_S,(char*)"monUpdate",tolua_server_System_monUpdate00);
   tolua_function(tolua_S,(char*)"itemUpdate",tolua_server_System_itemUpdate00);
   tolua_function(tolua_S,(char*)"changePrestigeExp",tolua_server_System_changePrestigeExp00);
   tolua_function(tolua_S,(char*)"reloadLang",tolua_server_System_reloadLang00);
   tolua_function(tolua_S,(char*)"setDbRetRoute",tolua_server_System_setDbRetRoute00);
   tolua_function(tolua_S,(char*)"sendDataToCenter",tolua_server_System_sendDataToCenter00);
   tolua_function(tolua_S,(char*)"runGTest",tolua_server_System_runGTest00);
   tolua_function(tolua_S,(char*)"getInt64",tolua_server_System_getInt6400);
   tolua_function(tolua_S,(char*)"sendDataToActorServer",tolua_server_System_sendDataToActorServer00);
   tolua_function(tolua_S,(char*)"enableCheckDataValid",tolua_server_System_enableCheckDataValid00);
   tolua_function(tolua_S,(char*)"setActorDataValid",tolua_server_System_setActorDataValid00);
   tolua_function(tolua_S,(char*)"sendTipmsg",tolua_server_System_sendTipmsg00);
   tolua_function(tolua_S,(char*)"delOneGameClient",tolua_server_System_delOneGameClient00);
   tolua_function(tolua_S,(char*)"loadFileAsUserData",tolua_server_System_loadFileAsUserData00);
   tolua_function(tolua_S,(char*)"saveUserDataToFile",tolua_server_System_saveUserDataToFile00);
   tolua_function(tolua_S,(char*)"getOnlineActorList",tolua_server_System_getOnlineActorList00);
   tolua_function(tolua_S,(char*)"getAllActorData",tolua_server_System_getAllActorData00);
   tolua_function(tolua_S,(char*)"findSkirmish",tolua_server_System_findSkirmish00);
   tolua_function(tolua_S,(char*)"FindFieldPlayer",tolua_server_System_FindFieldPlayer00);
   tolua_function(tolua_S,(char*)"sendMail",tolua_server_System_sendMail00);
   tolua_function(tolua_S,(char*)"regInstanceMonsterDamage",tolua_server_System_regInstanceMonsterDamage00);
   tolua_function(tolua_S,(char*)"regInstanceActorDamage",tolua_server_System_regInstanceActorDamage00);
   tolua_function(tolua_S,(char*)"regStartScript",tolua_server_System_regStartScript00);
   tolua_function(tolua_S,(char*)"regEndScript",tolua_server_System_regEndScript00);
   tolua_function(tolua_S,(char*)"checkRuleTime",tolua_server_System_checkRuleTime00);
   tolua_function(tolua_S,(char*)"getRuleStartTime",tolua_server_System_getRuleStartTime00);
   tolua_function(tolua_S,(char*)"getRuleEndTime",tolua_server_System_getRuleEndTime00);
   tolua_function(tolua_S,(char*)"getGlobalMailMaxUid",tolua_server_System_getGlobalMailMaxUid00);
   tolua_function(tolua_S,(char*)"addGlobalMail",tolua_server_System_addGlobalMail00);
   tolua_function(tolua_S,(char*)"buyMonthCard",tolua_server_System_buyMonthCard00);
   tolua_function(tolua_S,(char*)"buyPrivilege",tolua_server_System_buyPrivilege00);
   tolua_function(tolua_S,(char*)"buyPrivilegeCard",tolua_server_System_buyPrivilegeCard00);
   tolua_function(tolua_S,(char*)"buyRechargeLimitPackage",tolua_server_System_buyRechargeLimitPackage00);
   tolua_function(tolua_S,(char*)"buyRechargeLimitPackageOffline",tolua_server_System_buyRechargeLimitPackageOffline00);
   tolua_function(tolua_S,(char*)"buyFund",tolua_server_System_buyFund00);
   tolua_function(tolua_S,(char*)"buyFundOffline",tolua_server_System_buyFundOffline00);
   tolua_function(tolua_S,(char*)"rand",tolua_server_System_rand00);
   tolua_function(tolua_S,(char*)"getTimeZone",tolua_server_System_getTimeZone00);
   tolua_function(tolua_S,(char*)"shutup",tolua_server_System_shutup00);
   tolua_function(tolua_S,(char*)"releaseShutup",tolua_server_System_releaseShutup00);
   tolua_function(tolua_S,(char*)"offlineChangeTitle",tolua_server_System_offlineChangeTitle00);
   tolua_function(tolua_S,(char*)"startGameConnSrv",tolua_server_System_startGameConnSrv00);
   tolua_function(tolua_S,(char*)"stopGameConnSrv",tolua_server_System_stopGameConnSrv00);
   tolua_function(tolua_S,(char*)"time2String",tolua_server_System_time2String00);
   tolua_function(tolua_S,(char*)"getActorCountOfZhuanShengLv",tolua_server_System_getActorCountOfZhuanShengLv00);
   tolua_function(tolua_S,(char*)"getGameTick",tolua_server_System_getGameTick00);
   tolua_function(tolua_S,(char*)"logDKMLog",tolua_server_System_logDKMLog00);
   tolua_function(tolua_S,(char*)"printAllLua",tolua_server_System_printAllLua00);
   tolua_function(tolua_S,(char*)"getClvariantSize",tolua_server_System_getClvariantSize00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,(char*)"LDataPack",0);
  tolua_beginmodule(tolua_S,(char*)"LDataPack");
   tolua_function(tolua_S,(char*)"allocPacket",tolua_server_LDataPack_allocPacket00);
   tolua_function(tolua_S,(char*)"allocPacketCache",tolua_server_LDataPack_allocPacketCache00);
   tolua_function(tolua_S,(char*)"releasePacketCache",tolua_server_LDataPack_releasePacketCache00);
   tolua_function(tolua_S,(char*)"allocExtraPacket",tolua_server_LDataPack_allocExtraPacket00);
   tolua_function(tolua_S,(char*)"allocPacketToCenter",tolua_server_LDataPack_allocPacketToCenter00);
   tolua_function(tolua_S,(char*)"flush",tolua_server_LDataPack_flush00);
   tolua_function(tolua_S,(char*)"flushLf",tolua_server_LDataPack_flushLf00);
   tolua_function(tolua_S,(char*)"test_allocPack",tolua_server_LDataPack_test_allocPack00);
   tolua_function(tolua_S,(char*)"getAvaliableLength",tolua_server_LDataPack_getAvaliableLength00);
   tolua_function(tolua_S,(char*)"getLength",tolua_server_LDataPack_getLength00);
   tolua_function(tolua_S,(char*)"getPosition",tolua_server_LDataPack_getPosition00);
   tolua_function(tolua_S,(char*)"setPosition",tolua_server_LDataPack_setPosition00);
   tolua_function(tolua_S,(char*)"readString",tolua_server_LDataPack_readString00);
   tolua_function(tolua_S,(char*)"readByte",tolua_server_LDataPack_readByte00);
   tolua_function(tolua_S,(char*)"readChar",tolua_server_LDataPack_readChar00);
   tolua_function(tolua_S,(char*)"readWord",tolua_server_LDataPack_readWord00);
   tolua_function(tolua_S,(char*)"readShort",tolua_server_LDataPack_readShort00);
   tolua_function(tolua_S,(char*)"readInt",tolua_server_LDataPack_readInt00);
   tolua_function(tolua_S,(char*)"readUInt",tolua_server_LDataPack_readUInt00);
   tolua_function(tolua_S,(char*)"readUint64",tolua_server_LDataPack_readUint6400);
   tolua_function(tolua_S,(char*)"readInt64",tolua_server_LDataPack_readInt6400);
   tolua_function(tolua_S,(char*)"readData",tolua_server_LDataPack_readData00);
   tolua_function(tolua_S,(char*)"writeString",tolua_server_LDataPack_writeString00);
   tolua_function(tolua_S,(char*)"writeByte",tolua_server_LDataPack_writeByte00);
   tolua_function(tolua_S,(char*)"writeChar",tolua_server_LDataPack_writeChar00);
   tolua_function(tolua_S,(char*)"writeWord",tolua_server_LDataPack_writeWord00);
   tolua_function(tolua_S,(char*)"writeShort",tolua_server_LDataPack_writeShort00);
   tolua_function(tolua_S,(char*)"writeInt",tolua_server_LDataPack_writeInt00);
   tolua_function(tolua_S,(char*)"writeUInt",tolua_server_LDataPack_writeUInt00);
   tolua_function(tolua_S,(char*)"writeUint64",tolua_server_LDataPack_writeUint6400);
   tolua_function(tolua_S,(char*)"writeInt64",tolua_server_LDataPack_writeInt6400);
   tolua_function(tolua_S,(char*)"writeInt64I",tolua_server_LDataPack_writeInt64I00);
   tolua_function(tolua_S,(char*)"writeDouble",tolua_server_LDataPack_writeDouble00);
   tolua_function(tolua_S,(char*)"writeUserItem",tolua_server_LDataPack_writeUserItem00);
   tolua_function(tolua_S,(char*)"writeData",tolua_server_LDataPack_writeData00);
   tolua_function(tolua_S,(char*)"writePacket",tolua_server_LDataPack_writePacket00);
   tolua_function(tolua_S,(char*)"writeProto",tolua_server_LDataPack_writeProto00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,(char*)"Ranking",0);
  tolua_beginmodule(tolua_S,(char*)"Ranking");
   tolua_function(tolua_S,(char*)"getRankingItemList",tolua_server_Ranking_getRankingItemList00);
   tolua_function(tolua_S,(char*)"addRef",tolua_server_Ranking_addRef00);
   tolua_function(tolua_S,(char*)"release",tolua_server_Ranking_release00);
   tolua_function(tolua_S,(char*)"getRef",tolua_server_Ranking_getRef00);
   tolua_function(tolua_S,(char*)"getRanking",tolua_server_Ranking_getRanking00);
   tolua_function(tolua_S,(char*)"add",tolua_server_Ranking_add00);
   tolua_function(tolua_S,(char*)"load",tolua_server_Ranking_load00);
   tolua_function(tolua_S,(char*)"save",tolua_server_Ranking_save00);
   tolua_function(tolua_S,(char*)"addColumn",tolua_server_Ranking_addColumn00);
   tolua_function(tolua_S,(char*)"getColumnCount",tolua_server_Ranking_getColumnCount00);
   tolua_function(tolua_S,(char*)"setColumnTitle",tolua_server_Ranking_setColumnTitle00);
   tolua_function(tolua_S,(char*)"addItem",tolua_server_Ranking_addItem00);
   tolua_function(tolua_S,(char*)"tryAddItem",tolua_server_Ranking_tryAddItem00);
   tolua_function(tolua_S,(char*)"getItemIndexFromId",tolua_server_Ranking_getItemIndexFromId00);
   tolua_function(tolua_S,(char*)"getItemPtrFromId",tolua_server_Ranking_getItemPtrFromId00);
   tolua_function(tolua_S,(char*)"updateItem",tolua_server_Ranking_updateItem00);
   tolua_function(tolua_S,(char*)"setItem",tolua_server_Ranking_setItem00);
   tolua_function(tolua_S,(char*)"setColumnDisplay",tolua_server_Ranking_setColumnDisplay00);
   tolua_function(tolua_S,(char*)"setSub",tolua_server_Ranking_setSub00);
   tolua_function(tolua_S,(char*)"setSubInt",tolua_server_Ranking_setSubInt00);
   tolua_function(tolua_S,(char*)"updateSubInt",tolua_server_Ranking_updateSubInt00);
   tolua_function(tolua_S,(char*)"removeRanking",tolua_server_Ranking_removeRanking00);
   tolua_function(tolua_S,(char*)"getRankItemCount",tolua_server_Ranking_getRankItemCount00);
   tolua_function(tolua_S,(char*)"getPoint",tolua_server_Ranking_getPoint00);
   tolua_function(tolua_S,(char*)"getId",tolua_server_Ranking_getId00);
   tolua_function(tolua_S,(char*)"getIndexFromPtr",tolua_server_Ranking_getIndexFromPtr00);
   tolua_function(tolua_S,(char*)"getSub",tolua_server_Ranking_getSub00);
   tolua_function(tolua_S,(char*)"getSubInt",tolua_server_Ranking_getSubInt00);
   tolua_function(tolua_S,(char*)"clearRanking",tolua_server_Ranking_clearRanking00);
   tolua_function(tolua_S,(char*)"getItemFromIndex",tolua_server_Ranking_getItemFromIndex00);
   tolua_function(tolua_S,(char*)"setDisplayName",tolua_server_Ranking_setDisplayName00);
   tolua_function(tolua_S,(char*)"setIdTitle",tolua_server_Ranking_setIdTitle00);
   tolua_function(tolua_S,(char*)"setPointTitle",tolua_server_Ranking_setPointTitle00);
   tolua_function(tolua_S,(char*)"removeId",tolua_server_Ranking_removeId00);
   tolua_function(tolua_S,(char*)"setAutoSave",tolua_server_Ranking_setAutoSave00);
   tolua_function(tolua_S,(char*)"swapEqualItem",tolua_server_Ranking_swapEqualItem00);
   tolua_function(tolua_S,(char*)"getLianfuRankData",tolua_server_Ranking_getLianfuRankData00);
   tolua_function(tolua_S,(char*)"getStaticRank",tolua_server_Ranking_getStaticRank00);
   tolua_function(tolua_S,(char*)"getSRIndexFromId",tolua_server_Ranking_getSRIndexFromId00);
   tolua_function(tolua_S,(char*)"getSRIdFromIdx",tolua_server_Ranking_getSRIdFromIdx00);
   tolua_function(tolua_S,(char*)"updateStaticRank",tolua_server_Ranking_updateStaticRank00);
   tolua_function(tolua_S,(char*)"getRankName",tolua_server_Ranking_getRankName00);
   tolua_function(tolua_S,(char*)"setRankName",tolua_server_Ranking_setRankName00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,(char*)"LGuild",0);
  tolua_beginmodule(tolua_S,(char*)"LGuild");
   tolua_function(tolua_S,(char*)"getStaticVar",tolua_server_LGuild_getStaticVar00);
   tolua_function(tolua_S,(char*)"nameHasUsed",tolua_server_LGuild_nameHasUsed00);
   tolua_function(tolua_S,(char*)"createGuild",tolua_server_LGuild_createGuild00);
   tolua_function(tolua_S,(char*)"deleteGuild",tolua_server_LGuild_deleteGuild00);
   tolua_function(tolua_S,(char*)"deleteMember",tolua_server_LGuild_deleteMember00);
   tolua_function(tolua_S,(char*)"addMember",tolua_server_LGuild_addMember00);
   tolua_function(tolua_S,(char*)"getGuildById",tolua_server_LGuild_getGuildById00);
   tolua_function(tolua_S,(char*)"getGuildByName",tolua_server_LGuild_getGuildByName00);
   tolua_function(tolua_S,(char*)"getGuildName",tolua_server_LGuild_getGuildName00);
   tolua_function(tolua_S,(char*)"getGuildMemberCount",tolua_server_LGuild_getGuildMemberCount00);
   tolua_function(tolua_S,(char*)"getGuildId",tolua_server_LGuild_getGuildId00);
   tolua_function(tolua_S,(char*)"setUpdate",tolua_server_LGuild_setUpdate00);
   tolua_function(tolua_S,(char*)"getLeaderId",tolua_server_LGuild_getLeaderId00);
   tolua_function(tolua_S,(char*)"getMemberInfo",tolua_server_LGuild_getMemberInfo00);
   tolua_function(tolua_S,(char*)"isMember",tolua_server_LGuild_isMember00);
   tolua_function(tolua_S,(char*)"getAutoApprove",tolua_server_LGuild_getAutoApprove00);
   tolua_function(tolua_S,(char*)"setAutoApprove",tolua_server_LGuild_setAutoApprove00);
   tolua_function(tolua_S,(char*)"getGuildList",tolua_server_LGuild_getGuildList00);
   tolua_function(tolua_S,(char*)"getGuildPosMemberCount",tolua_server_LGuild_getGuildPosMemberCount00);
   tolua_function(tolua_S,(char*)"getMemberIdList",tolua_server_LGuild_getMemberIdList00);
   tolua_function(tolua_S,(char*)"getJoinMsgIdList",tolua_server_LGuild_getJoinMsgIdList00);
   tolua_function(tolua_S,(char*)"postJoinMsg",tolua_server_LGuild_postJoinMsg00);
   tolua_function(tolua_S,(char*)"removeJoinMsg",tolua_server_LGuild_removeJoinMsg00);
   tolua_function(tolua_S,(char*)"getJoinMsg",tolua_server_LGuild_getJoinMsg00);
   tolua_function(tolua_S,(char*)"getGuildPos",tolua_server_LGuild_getGuildPos00);
   tolua_function(tolua_S,(char*)"changeGuildPos",tolua_server_LGuild_changeGuildPos00);
   tolua_function(tolua_S,(char*)"updateGuildPos",tolua_server_LGuild_updateGuildPos00);
   tolua_function(tolua_S,(char*)"getLargestContribution",tolua_server_LGuild_getLargestContribution00);
   tolua_function(tolua_S,(char*)"addGuildLog",tolua_server_LGuild_addGuildLog00);
   tolua_function(tolua_S,(char*)"broadcastData",tolua_server_LGuild_broadcastData00);
   tolua_function(tolua_S,(char*)"setGuildLevel",tolua_server_LGuild_setGuildLevel00);
   tolua_function(tolua_S,(char*)"setGuildAffairLevel",tolua_server_LGuild_setGuildAffairLevel00);
   tolua_function(tolua_S,(char*)"updateGuildRank",tolua_server_LGuild_updateGuildRank00);
   tolua_function(tolua_S,(char*)"getGuildLevel",tolua_server_LGuild_getGuildLevel00);
   tolua_function(tolua_S,(char*)"addChatLog",tolua_server_LGuild_addChatLog00);
   tolua_function(tolua_S,(char*)"writeChatLog",tolua_server_LGuild_writeChatLog00);
   tolua_function(tolua_S,(char*)"clearChatLog",tolua_server_LGuild_clearChatLog00);
   tolua_function(tolua_S,(char*)"resetTodayContrib",tolua_server_LGuild_resetTodayContrib00);
   tolua_function(tolua_S,(char*)"addStoreLog",tolua_server_LGuild_addStoreLog00);
   tolua_function(tolua_S,(char*)"writeStoreLog",tolua_server_LGuild_writeStoreLog00);
   tolua_function(tolua_S,(char*)"getOnlineActor",tolua_server_LGuild_getOnlineActor00);
   tolua_function(tolua_S,(char*)"getLeaderName",tolua_server_LGuild_getLeaderName00);
   tolua_function(tolua_S,(char*)"getOnlineLeaderActor",tolua_server_LGuild_getOnlineLeaderActor00);
   tolua_function(tolua_S,(char*)"GetMemberTotalGx",tolua_server_LGuild_GetMemberTotalGx00);
   tolua_function(tolua_S,(char*)"getChangeNameCount",tolua_server_LGuild_getChangeNameCount00);
   tolua_function(tolua_S,(char*)"setChangeNameCount",tolua_server_LGuild_setChangeNameCount00);
   tolua_function(tolua_S,(char*)"changeName",tolua_server_LGuild_changeName00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,(char*)"P_ID",P_ID);
  tolua_constant(tolua_S,(char*)"P_POS_X",P_POS_X);
  tolua_constant(tolua_S,(char*)"P_POS_Y",P_POS_Y);
  tolua_constant(tolua_S,(char*)"P_MODELID",P_MODELID);
  tolua_constant(tolua_S,(char*)"P_ICON",P_ICON);
  tolua_constant(tolua_S,(char*)"P_DIR",P_DIR);
  tolua_constant(tolua_S,(char*)"P_MAX_ENTITY",P_MAX_ENTITY);
  tolua_constant(tolua_S,(char*)"P_LEVEL",P_LEVEL);
  tolua_constant(tolua_S,(char*)"P_HP",P_HP);
  tolua_constant(tolua_S,(char*)"P_MP",P_MP);
  tolua_constant(tolua_S,(char*)"P_SPEED",P_SPEED);
  tolua_constant(tolua_S,(char*)"P_MAXHP",P_MAXHP);
  tolua_constant(tolua_S,(char*)"P_MAXMP",P_MAXMP);
  tolua_constant(tolua_S,(char*)"P_OUT_ATTACK",P_OUT_ATTACK);
  tolua_constant(tolua_S,(char*)"P_OUT_DEFENCE",P_OUT_DEFENCE);
  tolua_constant(tolua_S,(char*)"P_DEFCRITICALSTRIKES",P_DEFCRITICALSTRIKES);
  tolua_constant(tolua_S,(char*)"P_ALL_ATTACK",P_ALL_ATTACK);
  tolua_constant(tolua_S,(char*)"P_SUB_DEF",P_SUB_DEF);
  tolua_constant(tolua_S,(char*)"P_IN_ATTACK",P_IN_ATTACK);
  tolua_constant(tolua_S,(char*)"P_IN_DEFENCE",P_IN_DEFENCE);
  tolua_constant(tolua_S,(char*)"P_CRITICALSTRIKES",P_CRITICALSTRIKES);
  tolua_constant(tolua_S,(char*)"P_DODGERATE",P_DODGERATE);
  tolua_constant(tolua_S,(char*)"P_HITRATE",P_HITRATE);
  tolua_constant(tolua_S,(char*)"P_ATTACK_ADD",P_ATTACK_ADD);
  tolua_constant(tolua_S,(char*)"P_HP_RENEW",P_HP_RENEW);
  tolua_constant(tolua_S,(char*)"P_MP_RENEW",P_MP_RENEW);
  tolua_constant(tolua_S,(char*)"P_ATTACK_SPEED",P_ATTACK_SPEED);
  tolua_constant(tolua_S,(char*)"P_IN_ATTACK_DAMAGE_ADD",P_IN_ATTACK_DAMAGE_ADD);
  tolua_constant(tolua_S,(char*)"P_OUT_ATTACK_DAMAGE_ADD",P_OUT_ATTACK_DAMAGE_ADD);
  tolua_constant(tolua_S,(char*)"P_THUNDER_ATTACK",P_THUNDER_ATTACK);
  tolua_constant(tolua_S,(char*)"P_THUNDER_DEFENCE",P_THUNDER_DEFENCE);
  tolua_constant(tolua_S,(char*)"P_POISON_ATTACK",P_POISON_ATTACK);
  tolua_constant(tolua_S,(char*)"P_POISON_DEFENCE",P_POISON_DEFENCE);
  tolua_constant(tolua_S,(char*)"P_ICE_ATTACK",P_ICE_ATTACK);
  tolua_constant(tolua_S,(char*)"P_ICE_DEFENCE",P_ICE_DEFENCE);
  tolua_constant(tolua_S,(char*)"P_FIRE_ATTACK",P_FIRE_ATTACK);
  tolua_constant(tolua_S,(char*)"P_FIRE_DEFENCE",P_FIRE_DEFENCE);
  tolua_constant(tolua_S,(char*)"P_STATE",P_STATE);
  tolua_constant(tolua_S,(char*)"P_BASE_MAXHP",P_BASE_MAXHP);
  tolua_constant(tolua_S,(char*)"P_BASE_MAXMP",P_BASE_MAXMP);
  tolua_constant(tolua_S,(char*)"P_STAND_POINT",P_STAND_POINT);
  tolua_constant(tolua_S,(char*)"P_RESEVS0",P_RESEVS0);
  tolua_constant(tolua_S,(char*)"P_RESEVS1",P_RESEVS1);
  tolua_constant(tolua_S,(char*)"P_MAX_CREATURE",P_MAX_CREATURE);
  tolua_constant(tolua_S,(char*)"P_MONSTER_START",P_MONSTER_START);
  tolua_constant(tolua_S,(char*)"P_BORNPOINT",P_BORNPOINT);
  tolua_constant(tolua_S,(char*)"P_LEVEL_DIFF",P_LEVEL_DIFF);
  tolua_constant(tolua_S,(char*)"P_PET_TITLE",P_PET_TITLE);
  tolua_constant(tolua_S,(char*)"P_PET_COLOR",P_PET_COLOR);
  tolua_constant(tolua_S,(char*)"P_PET_RANK_TITLE",P_PET_RANK_TITLE);
  tolua_constant(tolua_S,(char*)"P_MAX_MONSTER",P_MAX_MONSTER);
  tolua_constant(tolua_S,(char*)"P_WEAPON",P_WEAPON);
  tolua_constant(tolua_S,(char*)"P_MOUNT",P_MOUNT);
  tolua_constant(tolua_S,(char*)"P_DIZZY_RATE11",P_DIZZY_RATE11);
  tolua_constant(tolua_S,(char*)"P_DIZZY_TIME1",P_DIZZY_TIME1);
  tolua_constant(tolua_S,(char*)"P_HP_STORE",P_HP_STORE);
  tolua_constant(tolua_S,(char*)"P_MP_STORE",P_MP_STORE);
  tolua_constant(tolua_S,(char*)"P_SPIRIT",P_SPIRIT);
  tolua_constant(tolua_S,(char*)"P_PK_MOD",P_PK_MOD);
  tolua_constant(tolua_S,(char*)"P_STRONG_EFFECT",P_STRONG_EFFECT);
  tolua_constant(tolua_S,(char*)"P_WING",P_WING);
  tolua_constant(tolua_S,(char*)"P_STAGE_EFFECT",P_STAGE_EFFECT);
  tolua_constant(tolua_S,(char*)"P_PET_HP_STORE",P_PET_HP_STORE);
  tolua_constant(tolua_S,(char*)"PROP_ACTOR_XIUWEI_RENEW_RATE",PROP_ACTOR_XIUWEI_RENEW_RATE);
  tolua_constant(tolua_S,(char*)"P_SEX",P_SEX);
  tolua_constant(tolua_S,(char*)"P_VOCATION",P_VOCATION);
  tolua_constant(tolua_S,(char*)"P_EXP",P_EXP);
  tolua_constant(tolua_S,(char*)"P_PK_VALUE",P_PK_VALUE);
  tolua_constant(tolua_S,(char*)"P_BAG_GRID",P_BAG_GRID);
  tolua_constant(tolua_S,(char*)"P_WEEK_CHARM",P_WEEK_CHARM);
  tolua_constant(tolua_S,(char*)"P_BIND_COIN",P_BIND_COIN);
  tolua_constant(tolua_S,(char*)"P_COIN",P_COIN);
  tolua_constant(tolua_S,(char*)"P_BIND_YB",P_BIND_YB);
  tolua_constant(tolua_S,(char*)"P_YB",P_YB);
  tolua_constant(tolua_S,(char*)"P_SHENGWANG",P_SHENGWANG);
  tolua_constant(tolua_S,(char*)"P_CHARM",P_CHARM);
  tolua_constant(tolua_S,(char*)"P_SPIRIT_SLOT",P_SPIRIT_SLOT);
  tolua_constant(tolua_S,(char*)"P_RENOWN",P_RENOWN);
  tolua_constant(tolua_S,(char*)"P_GUILD_ID",P_GUILD_ID);
  tolua_constant(tolua_S,(char*)"P_TEAM_ID",P_TEAM_ID);
  tolua_constant(tolua_S,(char*)"P_SOCIAL",P_SOCIAL);
  tolua_constant(tolua_S,(char*)"P_GUILD_EXP",P_GUILD_EXP);
  tolua_constant(tolua_S,(char*)"P_LUCKY",P_LUCKY);
  tolua_constant(tolua_S,(char*)"P_SYS_OPEN",P_SYS_OPEN);
  tolua_constant(tolua_S,(char*)"P_ROOT_EXP_POWER",P_ROOT_EXP_POWER);
  tolua_constant(tolua_S,(char*)"P_CHANGE_MODEL",P_CHANGE_MODEL);
  tolua_constant(tolua_S,(char*)"PROP_BANGBANGTANG_EXP",PROP_BANGBANGTANG_EXP);
  tolua_constant(tolua_S,(char*)"PROP_ACTOR_MAX_EXP",PROP_ACTOR_MAX_EXP);
  tolua_constant(tolua_S,(char*)"P_GIVE_YB",P_GIVE_YB);
  tolua_constant(tolua_S,(char*)"P_CRITICAL_STRIKE",P_CRITICAL_STRIKE);
  tolua_constant(tolua_S,(char*)"P_EXP_RATE",P_EXP_RATE);
  tolua_constant(tolua_S,(char*)"P_DEPOT_GRID",P_DEPOT_GRID);
  tolua_constant(tolua_S,(char*)"P_ANGER",P_ANGER);
  tolua_constant(tolua_S,(char*)"P_ROOT_EXP",P_ROOT_EXP);
  tolua_constant(tolua_S,(char*)"P_ACHIEVEPOINT",P_ACHIEVEPOINT);
  tolua_constant(tolua_S,(char*)"P_ZYCONT",P_ZYCONT);
  tolua_constant(tolua_S,(char*)"P_QQ_VIP",P_QQ_VIP);
  tolua_constant(tolua_S,(char*)"P_WING_ID",P_WING_ID);
  tolua_constant(tolua_S,(char*)"P_WING_SCORE",P_WING_SCORE);
  tolua_constant(tolua_S,(char*)"P_PET_SCORE",P_PET_SCORE);
  tolua_constant(tolua_S,(char*)"PROP_ACTOR_VIPFLAG",PROP_ACTOR_VIPFLAG);
  tolua_constant(tolua_S,(char*)"P_CAMP",P_CAMP);
  tolua_constant(tolua_S,(char*)"P_PET_SLOT",P_PET_SLOT);
  tolua_constant(tolua_S,(char*)"P_HONOR",P_HONOR);
  tolua_constant(tolua_S,(char*)"P_QING_YUAN",P_QING_YUAN);
  tolua_constant(tolua_S,(char*)"PROP_ACTOR_DUR_KILLTIMES",PROP_ACTOR_DUR_KILLTIMES);
  tolua_constant(tolua_S,(char*)"PROP_ACTOR_BASE_FIGHT",PROP_ACTOR_BASE_FIGHT);
  tolua_constant(tolua_S,(char*)"P_FIGHT_VALUE",P_FIGHT_VALUE);
  tolua_constant(tolua_S,(char*)"P_MAX_RENOWN",P_MAX_RENOWN);
  tolua_constant(tolua_S,(char*)"P_RECHARGE",P_RECHARGE);
  tolua_constant(tolua_S,(char*)"P_VIP_LEVEL",P_VIP_LEVEL);
  tolua_constant(tolua_S,(char*)"P_BEAST_LEVEL",P_BEAST_LEVEL);
  tolua_constant(tolua_S,(char*)"P_FOOT_EFFECT",P_FOOT_EFFECT);
  tolua_constant(tolua_S,(char*)"P_EQUIP_SCORE",P_EQUIP_SCORE);
  tolua_constant(tolua_S,(char*)"P_HAIR_MODEL",P_HAIR_MODEL);
  tolua_constant(tolua_S,(char*)"P_BUBBLE",P_BUBBLE);
  tolua_constant(tolua_S,(char*)"P_ACTOR_STATE",P_ACTOR_STATE);
  tolua_constant(tolua_S,(char*)"P_JINGJIE_TITLE",P_JINGJIE_TITLE);
  tolua_constant(tolua_S,(char*)"P_ZHUMOBI",P_ZHUMOBI);
  tolua_constant(tolua_S,(char*)"P_MAX_ACTOR",P_MAX_ACTOR);
  tolua_constant(tolua_S,(char*)"MAX_ROLE",MAX_ROLE);
  tolua_constant(tolua_S,(char*)"MAX_ACTOR_LEVEL",MAX_ACTOR_LEVEL);
  tolua_constant(tolua_S,(char*)"ZHUAN_SHENG_BASE_LEVEL",ZHUAN_SHENG_BASE_LEVEL);
  tolua_constant(tolua_S,(char*)"PACK_LEN",PACK_LEN);
  tolua_constant(tolua_S,(char*)"EntityType_Actor",EntityType_Actor);
  tolua_constant(tolua_S,(char*)"EntityType_Role",EntityType_Role);
  tolua_constant(tolua_S,(char*)"EntityType_Monster",EntityType_Monster);
  tolua_constant(tolua_S,(char*)"EntityType_Npc",EntityType_Npc);
  tolua_constant(tolua_S,(char*)"EntityType_CloneRole",EntityType_CloneRole);
  tolua_constant(tolua_S,(char*)"EntityType_GatherMonster",EntityType_GatherMonster);
  tolua_constant(tolua_S,(char*)"EntityType_DropBag",EntityType_DropBag);
  tolua_constant(tolua_S,(char*)"EntityType_Count",EntityType_Count);
  tolua_constant(tolua_S,(char*)"FuBenType_Chapter",FuBenType_Chapter);
  tolua_constant(tolua_S,(char*)"FuBenType_PublicBoss",FuBenType_PublicBoss);
  tolua_constant(tolua_S,(char*)"FuBenType_Pata",FuBenType_Pata);
  tolua_constant(tolua_S,(char*)"FuBenType_WorldBoss",FuBenType_WorldBoss);
  tolua_constant(tolua_S,(char*)"FuBenType_HomeBoss",FuBenType_HomeBoss);
  tolua_constant(tolua_S,(char*)"FuBenType_City",FuBenType_City);
  tolua_constant(tolua_S,(char*)"JobType_None",JobType_None);
  tolua_constant(tolua_S,(char*)"JobType_Warrior",JobType_Warrior);
  tolua_constant(tolua_S,(char*)"JobType_Mage",JobType_Mage);
  tolua_constant(tolua_S,(char*)"JobType_Taoist",JobType_Taoist);
  tolua_constant(tolua_S,(char*)"JobType_Max",JobType_Max);
  tolua_constant(tolua_S,(char*)"AwardType_Numeric",AwardType_Numeric);
  tolua_constant(tolua_S,(char*)"AwardType_Item",AwardType_Item);
  tolua_constant(tolua_S,(char*)"NumericType_Exp",NumericType_Exp);
  tolua_constant(tolua_S,(char*)"NumericType_Gold",NumericType_Gold);
  tolua_constant(tolua_S,(char*)"NumericType_YuanBao",NumericType_YuanBao);
  tolua_constant(tolua_S,(char*)"NumericType_Fame",NumericType_Fame);
  tolua_constant(tolua_S,(char*)"NumericType_Essence",NumericType_Essence);
  tolua_constant(tolua_S,(char*)"NumericType_GuildContrib",NumericType_GuildContrib);
  tolua_constant(tolua_S,(char*)"NumericType_GuildFund",NumericType_GuildFund);
  tolua_constant(tolua_S,(char*)"NumericType_Feats",NumericType_Feats);
  tolua_constant(tolua_S,(char*)"NumericType_Achieve",NumericType_Achieve);
  tolua_constant(tolua_S,(char*)"NumericType_Shatter",NumericType_Shatter);
  tolua_constant(tolua_S,(char*)"NumericType_SpeShatter",NumericType_SpeShatter);
  tolua_constant(tolua_S,(char*)"NumericType_Togeatter",NumericType_Togeatter);
  tolua_constant(tolua_S,(char*)"NumericType_TogeatterHigh",NumericType_TogeatterHigh);
  tolua_constant(tolua_S,(char*)"NumericType_GodWeaponExp",NumericType_GodWeaponExp);
  tolua_constant(tolua_S,(char*)"NumericType_PrestigeExp",NumericType_PrestigeExp);
  tolua_constant(tolua_S,(char*)"NumericType_Chips",NumericType_Chips);
  tolua_constant(tolua_S,(char*)"NumericType_ShenShouExp",NumericType_ShenShouExp);
  tolua_constant(tolua_S,(char*)"NumericType_VipExp",NumericType_VipExp);
  tolua_constant(tolua_S,(char*)"NumericType_SkillExp",NumericType_SkillExp);
  tolua_constant(tolua_S,(char*)"NumericType_Recharge",NumericType_Recharge);
  tolua_constant(tolua_S,(char*)"ItemType_Equip",ItemType_Equip);
  tolua_constant(tolua_S,(char*)"ItemType_Gem",ItemType_Gem);
  tolua_constant(tolua_S,(char*)"ItemType_YuanShen",ItemType_YuanShen);
  tolua_constant(tolua_S,(char*)"ItemType_Chest",ItemType_Chest);
  tolua_constant(tolua_S,(char*)"ItemType_WingEquip",ItemType_WingEquip);
  tolua_constant(tolua_S,(char*)"ItemType_TogetherHit",ItemType_TogetherHit);
  tolua_constant(tolua_S,(char*)"ItemType_FuWen",ItemType_FuWen);
  tolua_constant(tolua_S,(char*)"ItemType_Imba",ItemType_Imba);
  tolua_constant(tolua_S,(char*)"ItemType_Holy",ItemType_Holy);
  tolua_constant(tolua_S,(char*)"QualityType_White",QualityType_White);
  tolua_constant(tolua_S,(char*)"QualityType_Green",QualityType_Green);
  tolua_constant(tolua_S,(char*)"QualityType_Purple",QualityType_Purple);
  tolua_constant(tolua_S,(char*)"QualityType_Orange",QualityType_Orange);
  tolua_constant(tolua_S,(char*)"QualityType_Red",QualityType_Red);
  tolua_constant(tolua_S,(char*)"QualityType_Gold",QualityType_Gold);
  tolua_constant(tolua_S,(char*)"EquipType_Weapon",EquipType_Weapon);
  tolua_constant(tolua_S,(char*)"EquipType_Helmet",EquipType_Helmet);
  tolua_constant(tolua_S,(char*)"EquipType_Coat",EquipType_Coat);
  tolua_constant(tolua_S,(char*)"EquipType_Necklace",EquipType_Necklace);
  tolua_constant(tolua_S,(char*)"EquipType_Wrist",EquipType_Wrist);
  tolua_constant(tolua_S,(char*)"EquipType_Belt",EquipType_Belt);
  tolua_constant(tolua_S,(char*)"EquipType_Ring",EquipType_Ring);
  tolua_constant(tolua_S,(char*)"EquipType_Shoes",EquipType_Shoes);
  tolua_constant(tolua_S,(char*)"EquipType_Dzi",EquipType_Dzi);
  tolua_constant(tolua_S,(char*)"EquipType_Hats",EquipType_Hats);
  tolua_constant(tolua_S,(char*)"EquipType_Mark",EquipType_Mark);
  tolua_constant(tolua_S,(char*)"EquipType_Cloak",EquipType_Cloak);
  tolua_constant(tolua_S,(char*)"EquipType_Shield",EquipType_Shield);
  tolua_constant(tolua_S,(char*)"EquipType_Max",EquipType_Max);
  tolua_constant(tolua_S,(char*)"EquipType_Hub",EquipType_Hub);
  tolua_constant(tolua_S,(char*)"EquipType_Stone",EquipType_Stone);
  tolua_constant(tolua_S,(char*)"EquipType_Feathers",EquipType_Feathers);
  tolua_constant(tolua_S,(char*)"EquipType_Colorplume",EquipType_Colorplume);
  tolua_constant(tolua_S,(char*)"RankingType_Power",RankingType_Power);
  tolua_constant(tolua_S,(char*)"RankingType_Arena",RankingType_Arena);
  tolua_constant(tolua_S,(char*)"RankingType_Skirmish",RankingType_Skirmish);
  tolua_constant(tolua_S,(char*)"RankingType_ChapterLevel",RankingType_ChapterLevel);
  tolua_constant(tolua_S,(char*)"RankingType_ChallengeLevel",RankingType_ChallengeLevel);
  tolua_constant(tolua_S,(char*)"RankingType_Level",RankingType_Level);
  tolua_constant(tolua_S,(char*)"RankingType_Wing",RankingType_Wing);
  tolua_constant(tolua_S,(char*)"RankingType_Warrior",RankingType_Warrior);
  tolua_constant(tolua_S,(char*)"RankingType_Mage",RankingType_Mage);
  tolua_constant(tolua_S,(char*)"RankingType_Taoistpriest",RankingType_Taoistpriest);
  tolua_constant(tolua_S,(char*)"RankingType_Train",RankingType_Train);
  tolua_constant(tolua_S,(char*)"RankingType_TianTi",RankingType_TianTi);
  tolua_constant(tolua_S,(char*)"RankingType_Zhuling",RankingType_Zhuling);
  tolua_constant(tolua_S,(char*)"RankingType_ZhanLing",RankingType_ZhanLing);
  tolua_constant(tolua_S,(char*)"RankingType_LoongSoul",RankingType_LoongSoul);
  tolua_constant(tolua_S,(char*)"RankingType_Knighthood",RankingType_Knighthood);
  tolua_constant(tolua_S,(char*)"RankingType_WingLv",RankingType_WingLv);
  tolua_constant(tolua_S,(char*)"RankingType_TuJianPower",RankingType_TuJianPower);
  tolua_constant(tolua_S,(char*)"RankingType_ZhuanSheng",RankingType_ZhuanSheng);
  tolua_constant(tolua_S,(char*)"RankingType_EquipBasePower",RankingType_EquipBasePower);
  tolua_constant(tolua_S,(char*)"RankingType_Stone",RankingType_Stone);
  tolua_constant(tolua_S,(char*)"RankingType_ConsumeYB",RankingType_ConsumeYB);
  tolua_constant(tolua_S,(char*)"RankingType_Prestige",RankingType_Prestige);
  tolua_constant(tolua_S,(char*)"RankingType_TeamLike",RankingType_TeamLike);
  tolua_constant(tolua_S,(char*)"RankingType_Count",RankingType_Count);
  tolua_constant(tolua_S,(char*)"RankingType_Recharge",RankingType_Recharge);
  tolua_constant(tolua_S,(char*)"asStart",asStart);
  tolua_constant(tolua_S,(char*)"asEnhance",asEnhance);
  tolua_constant(tolua_S,(char*)"asZhuling",asZhuling);
  tolua_constant(tolua_S,(char*)"asStone",asStone);
  tolua_constant(tolua_S,(char*)"asLongSoul",asLongSoul);
  tolua_constant(tolua_S,(char*)"asShield",asShield);
  tolua_constant(tolua_S,(char*)"asHeartMethod",asHeartMethod);
  tolua_constant(tolua_S,(char*)"asHunGu",asHunGu);
  tolua_constant(tolua_S,(char*)"asCount",asCount);
  tolua_constant(tolua_S,(char*)"attrStart",attrStart);
  tolua_constant(tolua_S,(char*)"attrTuJian",attrTuJian);
  tolua_constant(tolua_S,(char*)"attrFlameStamp",attrFlameStamp);
  tolua_constant(tolua_S,(char*)"attrZhanLing",attrZhanLing);
  tolua_constant(tolua_S,(char*)"attrShenShou",attrShenShou);
  tolua_constant(tolua_S,(char*)"attrMax",attrMax);
  tolua_constant(tolua_S,(char*)"MOVELINE_NORMAL",MOVELINE_NORMAL);
  tolua_constant(tolua_S,(char*)"MOVELINE_SEND_REQUEST",MOVELINE_SEND_REQUEST);
  tolua_constant(tolua_S,(char*)"MOVELINE_DATA_PREPARE",MOVELINE_DATA_PREPARE);
  tolua_constant(tolua_S,(char*)"CampType_None",CampType_None);
  tolua_constant(tolua_S,(char*)"CampType_Player",CampType_Player);
  tolua_constant(tolua_S,(char*)"CampType_Count",CampType_Count);
  tolua_constant(tolua_S,(char*)"CampType_CampBattle_Ice",CampType_CampBattle_Ice);
  tolua_constant(tolua_S,(char*)"CampType_CampBattle_Fire",CampType_CampBattle_Fire);
  tolua_constant(tolua_S,(char*)"WorldBossCampType_Normal",WorldBossCampType_Normal);
  tolua_constant(tolua_S,(char*)"WorldBossCampType_Belong",WorldBossCampType_Belong);
  tolua_constant(tolua_S,(char*)"WorldBossCampType_Attack",WorldBossCampType_Attack);
  tolua_constant(tolua_S,(char*)"ExRingType_MabiRing",ExRingType_MabiRing);
  tolua_constant(tolua_S,(char*)"ExRingType_HuShenRing",ExRingType_HuShenRing);
  tolua_constant(tolua_S,(char*)"ExRingType_MAX",ExRingType_MAX);
  tolua_constant(tolua_S,(char*)"ActorExRingType_HuoYanRing",ActorExRingType_HuoYanRing);
  tolua_constant(tolua_S,(char*)"ActorExRingType_MAX",ActorExRingType_MAX);
  tolua_constant(tolua_S,(char*)"MALEACTOR",MALEACTOR);
  tolua_constant(tolua_S,(char*)"FEMALEACTOR",FEMALEACTOR);
  tolua_constant(tolua_S,(char*)"MAX_FUBEN",MAX_FUBEN);
  tolua_constant(tolua_S,(char*)"MAX_REINCARNATION",MAX_REINCARNATION);
  tolua_constant(tolua_S,(char*)"INT_MAX_NUM",INT_MAX_NUM);
  tolua_constant(tolua_S,(char*)"MAX_WING_SKILL_STORE",MAX_WING_SKILL_STORE);
  tolua_constant(tolua_S,(char*)"enActor",enActor);
  tolua_constant(tolua_S,(char*)"enMonster",enMonster);
  tolua_constant(tolua_S,(char*)"enNpc",enNpc);
  tolua_constant(tolua_S,(char*)"enMovingNPC",enMovingNPC);
  tolua_constant(tolua_S,(char*)"enPet",enPet);
  tolua_constant(tolua_S,(char*)"enTotom",enTotom);
  tolua_constant(tolua_S,(char*)"enDropBag",enDropBag);
  tolua_constant(tolua_S,(char*)"enDefender",enDefender);
  tolua_constant(tolua_S,(char*)"enPlant",enPlant);
  tolua_constant(tolua_S,(char*)"enTransfer",enTransfer);
  tolua_constant(tolua_S,(char*)"enBuilding",enBuilding);
  tolua_constant(tolua_S,(char*)"enEffects",enEffects);
  tolua_constant(tolua_S,(char*)"enGatherMonster",enGatherMonster);
  tolua_constant(tolua_S,(char*)"enClonePet",enClonePet);
  tolua_constant(tolua_S,(char*)"enScriptNpc",enScriptNpc);
  tolua_constant(tolua_S,(char*)"mtBindCoin",mtBindCoin);
  tolua_constant(tolua_S,(char*)"mtCoin",mtCoin);
  tolua_constant(tolua_S,(char*)"mtBindYuanbao",mtBindYuanbao);
  tolua_constant(tolua_S,(char*)"mtYuanbao",mtYuanbao);
  tolua_constant(tolua_S,(char*)"mtMoneyTypeCount",mtMoneyTypeCount);
  tolua_constant(tolua_S,(char*)"mtMoneyTypeStart",mtMoneyTypeStart);
  tolua_constant(tolua_S,(char*)"ftStatic",ftStatic);
  tolua_constant(tolua_S,(char*)"ftChapterBoss",ftChapterBoss);
  tolua_constant(tolua_S,(char*)"ftMaterial",ftMaterial);
  tolua_constant(tolua_S,(char*)"ftRetain1",ftRetain1);
  tolua_constant(tolua_S,(char*)"ftRetain2",ftRetain2);
  tolua_constant(tolua_S,(char*)"ftRetain3",ftRetain3);
  tolua_constant(tolua_S,(char*)"ftPersonalBoss",ftPersonalBoss);
  tolua_constant(tolua_S,(char*)"ftPublicBoss",ftPublicBoss);
  tolua_constant(tolua_S,(char*)"ssLoongSoul",ssLoongSoul);
  tolua_constant(tolua_S,(char*)"ciChannelSecret",ciChannelSecret);
  tolua_constant(tolua_S,(char*)"ciChannelNear",ciChannelNear);
  tolua_constant(tolua_S,(char*)"ciChannelWorld",ciChannelWorld);
  tolua_constant(tolua_S,(char*)"ciChannelGuild",ciChannelGuild);
  tolua_constant(tolua_S,(char*)"ciChannelTeam",ciChannelTeam);
  tolua_constant(tolua_S,(char*)"ciChannelBigTeam",ciChannelBigTeam);
  tolua_constant(tolua_S,(char*)"ciChannelMap",ciChannelMap);
  tolua_constant(tolua_S,(char*)"ciChannelAll",ciChannelAll);
  tolua_constant(tolua_S,(char*)"ciChannelCamp",ciChannelCamp);
  tolua_constant(tolua_S,(char*)"ciChannelSystem",ciChannelSystem);
  tolua_constant(tolua_S,(char*)"ciChannelKuafu",ciChannelKuafu);
  tolua_constant(tolua_S,(char*)"ciChannelSos",ciChannelSos);
  tolua_constant(tolua_S,(char*)"ciChannelCosign",ciChannelCosign);
  tolua_constant(tolua_S,(char*)"ciChannelLianfu",ciChannelLianfu);
  tolua_constant(tolua_S,(char*)"ciChannelMax",ciChannelMax);
  tolua_constant(tolua_S,(char*)"ttInvalidTmType",ttInvalidTmType);
  tolua_constant(tolua_S,(char*)"ttTipmsgWindow",ttTipmsgWindow);
  tolua_constant(tolua_S,(char*)"ttScreenCenter",ttScreenCenter);
  tolua_constant(tolua_S,(char*)"ttDialog",ttDialog);
  tolua_constant(tolua_S,(char*)"ttHearsay",ttHearsay);
  tolua_constant(tolua_S,(char*)"ttMessage",ttMessage);
  tolua_constant(tolua_S,(char*)"ttWarmTip",ttWarmTip);
  tolua_constant(tolua_S,(char*)"ttGmTip",ttGmTip);
  tolua_constant(tolua_S,(char*)"ttChatWindow",ttChatWindow);
  tolua_constant(tolua_S,(char*)"ttScreenMarquee",ttScreenMarquee);
  tolua_constant(tolua_S,(char*)"ttScreenCenterDown",ttScreenCenterDown);
  tolua_constant(tolua_S,(char*)"diItem",diItem);
  tolua_constant(tolua_S,(char*)"diActor",diActor);
  tolua_constant(tolua_S,(char*)"diQuest",diQuest);
  tolua_constant(tolua_S,(char*)"diSkill",diSkill);
  tolua_constant(tolua_S,(char*)"diStrong",diStrong);
  tolua_constant(tolua_S,(char*)"diGuild",diGuild);
  tolua_constant(tolua_S,(char*)"diSell",diSell);
  tolua_constant(tolua_S,(char*)"diSystem",diSystem);
  tolua_constant(tolua_S,(char*)"diStore",diStore);
  tolua_constant(tolua_S,(char*)"diNormalFuben",diNormalFuben);
  tolua_constant(tolua_S,(char*)"diFubenList",diFubenList);
  tolua_constant(tolua_S,(char*)"diBuyAnItem",diBuyAnItem);
  tolua_constant(tolua_S,(char*)"diFuncDia",diFuncDia);
  tolua_constant(tolua_S,(char*)"diMemoDia",diMemoDia);
  tolua_constant(tolua_S,(char*)"diRenown",diRenown);
  tolua_constant(tolua_S,(char*)"diStartPlay",diStartPlay);
  tolua_constant(tolua_S,(char*)"diRefreshTask",diRefreshTask);
  tolua_constant(tolua_S,(char*)"diQuickTelport",diQuickTelport);
  tolua_constant(tolua_S,(char*)"diDepot",diDepot);
  tolua_constant(tolua_S,(char*)"diProtection",diProtection);
  tolua_constant(tolua_S,(char*)"diProtectionTips",diProtectionTips);
  tolua_constant(tolua_S,(char*)"diTianYuanInfo",diTianYuanInfo);
  tolua_constant(tolua_S,(char*)"diFlower",diFlower);
  tolua_constant(tolua_S,(char*)"diLiudao",diLiudao);
  tolua_constant(tolua_S,(char*)"diPayGuid",diPayGuid);
  tolua_constant(tolua_S,(char*)"diAwardToDepot",diAwardToDepot);
  tolua_constant(tolua_S,(char*)"diLotterySY",diLotterySY);
  tolua_constant(tolua_S,(char*)"diPet",diPet);
  tolua_constant(tolua_S,(char*)"diMountTip",diMountTip);
  tolua_constant(tolua_S,(char*)"diGJGuid",diGJGuid);
  tolua_constant(tolua_S,(char*)"diVipCard",diVipCard);
  tolua_constant(tolua_S,(char*)"diWorldWar",diWorldWar);
  tolua_constant(tolua_S,(char*)"diDigongchuansong",diDigongchuansong);
  tolua_constant(tolua_S,(char*)"diwyyjLead",diwyyjLead);
  tolua_constant(tolua_S,(char*)"diMarryMarch",diMarryMarch);
  tolua_constant(tolua_S,(char*)"diNpcDialog",diNpcDialog);
  tolua_constant(tolua_S,(char*)"diZhuanShengTips",diZhuanShengTips);
  tolua_constant(tolua_S,(char*)"diEqsign",diEqsign);
  tolua_constant(tolua_S,(char*)"diQualitySign",diQualitySign);
  tolua_constant(tolua_S,(char*)"diExclusiveSign",diExclusiveSign);
  tolua_constant(tolua_S,(char*)"diZhuanZhi",diZhuanZhi);
  tolua_constant(tolua_S,(char*)"diMount",diMount);
  tolua_constant(tolua_S,(char*)"diEscort",diEscort);
  tolua_constant(tolua_S,(char*)"diRoutineQuest",diRoutineQuest);
  tolua_constant(tolua_S,(char*)"diZhengBa",diZhengBa);
  tolua_constant(tolua_S,(char*)"diJingjie",diJingjie);
  tolua_constant(tolua_S,(char*)"diQuestions",diQuestions);
  tolua_constant(tolua_S,(char*)"diBuyVip",diBuyVip);
  tolua_constant(tolua_S,(char*)"diPetJingJie",diPetJingJie);
  tolua_constant(tolua_S,(char*)"diInvestgate",diInvestgate);
  tolua_constant(tolua_S,(char*)"diBuyPetSkill",diBuyPetSkill);
  tolua_constant(tolua_S,(char*)"diZhuMoDian",diZhuMoDian);
  tolua_constant(tolua_S,(char*)"diFirstCharge",diFirstCharge);
  tolua_constant(tolua_S,(char*)"diRaiders",diRaiders);
  tolua_constant(tolua_S,(char*)"diTreasureofGold",diTreasureofGold);
  tolua_constant(tolua_S,(char*)"diFengQiangliBao",diFengQiangliBao);
  tolua_constant(tolua_S,(char*)"diCangbaoge",diCangbaoge);
  tolua_constant(tolua_S,(char*)"diRabbit",diRabbit);
  tolua_constant(tolua_S,(char*)"diSmashingEggs",diSmashingEggs);
  tolua_constant(tolua_S,(char*)"diAnHeiShendian",diAnHeiShendian);
  tolua_constant(tolua_S,(char*)"diAnHeiShendianMain",diAnHeiShendianMain);
  tolua_constant(tolua_S,(char*)"diMarry",diMarry);
  tolua_constant(tolua_S,(char*)"diDivorce",diDivorce);
  tolua_constant(tolua_S,(char*)"smGuildCommon",smGuildCommon);
  tolua_constant(tolua_S,(char*)"smGuildZl",smGuildZl);
  tolua_constant(tolua_S,(char*)"smGuildAssistLeader",smGuildAssistLeader);
  tolua_constant(tolua_S,(char*)"smGuildLeader",smGuildLeader);
  tolua_constant(tolua_S,(char*)"enGuildChatSystem",enGuildChatSystem);
  tolua_constant(tolua_S,(char*)"enGuildChatChat",enGuildChatChat);
  tolua_constant(tolua_S,(char*)"enGuildChatShow",enGuildChatShow);
  tolua_constant(tolua_S,(char*)"mssInvalid",mssInvalid);
  tolua_constant(tolua_S,(char*)"mssNear",mssNear);
  tolua_constant(tolua_S,(char*)"mssScene",mssScene);
  tolua_constant(tolua_S,(char*)"mssFuben",mssFuben);
  tolua_constant(tolua_S,(char*)"mssWorld",mssWorld);
  tolua_constant(tolua_S,(char*)"mssCamp",mssCamp);
  tolua_constant(tolua_S,(char*)"mssNearScene",mssNearScene);
  tolua_constant(tolua_S,(char*)"mssScreencenter",mssScreencenter);
  tolua_constant(tolua_S,(char*)"mssSelf",mssSelf);
  tolua_constant(tolua_S,(char*)"mssMax",mssMax);
  tolua_constant(tolua_S,(char*)"mspLt",mspLt);
  tolua_constant(tolua_S,(char*)"mspHead",mspHead);
  tolua_constant(tolua_S,(char*)"mspCenter",mspCenter);
  tolua_constant(tolua_S,(char*)"enVIPRedDiamond",enVIPRedDiamond);
  tolua_constant(tolua_S,(char*)"enVIPBlueDiamond",enVIPBlueDiamond);
  tolua_constant(tolua_S,(char*)"enVIPYellowDiamond",enVIPYellowDiamond);
  tolua_constant(tolua_S,(char*)"enVIPTypeMax",enVIPTypeMax);
  tolua_constant(tolua_S,(char*)"enMiscData_AddCampDailyTaskCount",enMiscData_AddCampDailyTaskCount);
  tolua_constant(tolua_S,(char*)"enMiscData_AddDailyTaskCount",enMiscData_AddDailyTaskCount);
  tolua_constant(tolua_S,(char*)"enMiscData_VIPXiuWeiAdd",enMiscData_VIPXiuWeiAdd);
  tolua_constant(tolua_S,(char*)"enMiscDataMax",enMiscDataMax);
  tolua_constant(tolua_S,(char*)"enGemStatusIdle",enGemStatusIdle);
  tolua_constant(tolua_S,(char*)"enGemStatusEquip",enGemStatusEquip);
  tolua_constant(tolua_S,(char*)"enGemStatusRide",enGemStatusRide);
  tolua_constant(tolua_S,(char*)"enGemMax",enGemMax);
  tolua_constant(tolua_S,(char*)"enGemSpriteCharAttack",enGemSpriteCharAttack);
  tolua_constant(tolua_S,(char*)"enGemSpriteCharDefence",enGemSpriteCharDefence);
  tolua_constant(tolua_S,(char*)"enGemSpriteCharAgility",enGemSpriteCharAgility);
  tolua_constant(tolua_S,(char*)"enGemSpriteCharHP",enGemSpriteCharHP);
  tolua_constant(tolua_S,(char*)"enGemSpriteCharMax",enGemSpriteCharMax);
  tolua_constant(tolua_S,(char*)"dtByte",dtByte);
  tolua_constant(tolua_S,(char*)"dtChar",dtChar);
  tolua_constant(tolua_S,(char*)"dtWord",dtWord);
  tolua_constant(tolua_S,(char*)"dtShort",dtShort);
  tolua_constant(tolua_S,(char*)"dtInt",dtInt);
  tolua_constant(tolua_S,(char*)"dtUint",dtUint);
  tolua_constant(tolua_S,(char*)"dtInt64",dtInt64);
  tolua_constant(tolua_S,(char*)"dtUint64",dtUint64);
  tolua_constant(tolua_S,(char*)"dtString",dtString);
  tolua_constant(tolua_S,(char*)"dtPointer",dtPointer);
  tolua_constant(tolua_S,(char*)"dtItem",dtItem);
  tolua_constant(tolua_S,(char*)"dtDouble",dtDouble);
  tolua_constant(tolua_S,(char*)"esStateStand",esStateStand);
  tolua_constant(tolua_S,(char*)"esStateMove",esStateMove);
  tolua_constant(tolua_S,(char*)"esStateRide",esStateRide);
  tolua_constant(tolua_S,(char*)"esStatePratice",esStatePratice);
  tolua_constant(tolua_S,(char*)"esGather",esGather);
  tolua_constant(tolua_S,(char*)"esStateUnderSunshade",esStateUnderSunshade);
  tolua_constant(tolua_S,(char*)"esStateBattle",esStateBattle);
  tolua_constant(tolua_S,(char*)"esStateDeath",esStateDeath);
  tolua_constant(tolua_S,(char*)"esStateMoveForbid",esStateMoveForbid);
  tolua_constant(tolua_S,(char*)"esStateDizzy",esStateDizzy);
  tolua_constant(tolua_S,(char*)"esStateAutoBattle",esStateAutoBattle);
  tolua_constant(tolua_S,(char*)"esStateReturnHome",esStateReturnHome);
  tolua_constant(tolua_S,(char*)"esDisableSkillCD",esDisableSkillCD);
  tolua_constant(tolua_S,(char*)"esChallenge",esChallenge);
  tolua_constant(tolua_S,(char*)"esNewCreate",esNewCreate);
  tolua_constant(tolua_S,(char*)"esStateDoubleSunBach",esStateDoubleSunBach);
  tolua_constant(tolua_S,(char*)"esStateAttackedForbid",esStateAttackedForbid);
  tolua_constant(tolua_S,(char*)"esShowBossName",esShowBossName);
  tolua_constant(tolua_S,(char*)"esNoTitle",esNoTitle);
  tolua_constant(tolua_S,(char*)"esJump",esJump);
  tolua_constant(tolua_S,(char*)"esMasterEquip",esMasterEquip);
  tolua_constant(tolua_S,(char*)"esProtection",esProtection);
  tolua_constant(tolua_S,(char*)"esPkState",esPkState);
  tolua_constant(tolua_S,(char*)"esPetState",esPetState);
  tolua_constant(tolua_S,(char*)"esDenyRefreshModel",esDenyRefreshModel);
  tolua_constant(tolua_S,(char*)"esStateSunBath",esStateSunBath);
  tolua_constant(tolua_S,(char*)"esStateHideForbid",esStateHideForbid);
  tolua_constant(tolua_S,(char*)"esStateInSandBeach",esStateInSandBeach);
  tolua_constant(tolua_S,(char*)"esStateImprison",esStateImprison);
  tolua_constant(tolua_S,(char*)"esStateHide",esStateHide);
  tolua_constant(tolua_S,(char*)"esStateVest",esStateVest);
  tolua_constant(tolua_S,(char*)"esStateJiuShiZhu",esStateJiuShiZhu);
  tolua_constant(tolua_S,(char*)"esReLive",esReLive);
  tolua_constant(tolua_S,(char*)"esMaxStateCount",esMaxStateCount);
  tolua_constant(tolua_S,(char*)"ebsSuperman",ebsSuperman);
  tolua_constant(tolua_S,(char*)"ebsNoAnger",ebsNoAnger);
  tolua_constant(tolua_S,(char*)"ebsAttackLog",ebsAttackLog);
  tolua_constant(tolua_S,(char*)"ebsHpEvent",ebsHpEvent);
  tolua_constant(tolua_S,(char*)"ebsTotem",ebsTotem);
  tolua_constant(tolua_S,(char*)"ebsGm",ebsGm);
  tolua_constant(tolua_S,(char*)"ebsVestEvent",ebsVestEvent);
  tolua_constant(tolua_S,(char*)"ebsMaxStateCount",ebsMaxStateCount);
  tolua_constant(tolua_S,(char*)"sftMin",sftMin);
  tolua_constant(tolua_S,(char*)"sftCount",sftCount);
  tolua_constant(tolua_S,(char*)"sftStrong",sftStrong);
  tolua_constant(tolua_S,(char*)"sftBless",sftBless);
  tolua_constant(tolua_S,(char*)"sftOutTime",sftOutTime);
  tolua_constant(tolua_S,(char*)"sftMax",sftMax);
  tolua_constant(tolua_S,(char*)"esFishingNormal",esFishingNormal);
  tolua_constant(tolua_S,(char*)"esUsingOtherHp",esUsingOtherHp);
  tolua_constant(tolua_S,(char*)"esHaveSunshade",esHaveSunshade);
  tolua_constant(tolua_S,(char*)"esAvenger",esAvenger);
  tolua_constant(tolua_S,(char*)"esGearsOfWar",esGearsOfWar);
  tolua_constant(tolua_S,(char*)"esChangeModel",esChangeModel);
  tolua_constant(tolua_S,(char*)"esMaxActorStateCount",esMaxActorStateCount);
  tolua_constant(tolua_S,(char*)"caleExp",caleExp);
  tolua_constant(tolua_S,(char*)"caleCoin",caleCoin);
  tolua_constant(tolua_S,(char*)"caleBindCoin",caleBindCoin);
  tolua_constant(tolua_S,(char*)"calelingli",calelingli);
  tolua_constant(tolua_S,(char*)"caleFubenTime",caleFubenTime);
  tolua_constant(tolua_S,(char*)"caleMonTime",caleMonTime);
  tolua_constant(tolua_S,(char*)"caleOther1",caleOther1);
  tolua_constant(tolua_S,(char*)"caleOther2",caleOther2);
  tolua_constant(tolua_S,(char*)"caleOther3",caleOther3);
  tolua_constant(tolua_S,(char*)"caleRemainMonster",caleRemainMonster);
  tolua_constant(tolua_S,(char*)"caleGameTime",caleGameTime);
  tolua_constant(tolua_S,(char*)"caleLiLiang",caleLiLiang);
  tolua_constant(tolua_S,(char*)"caleSceneExp",caleSceneExp);
  tolua_constant(tolua_S,(char*)"caleHonor",caleHonor);
  tolua_constant(tolua_S,(char*)"caleOther4",caleOther4);
  tolua_constant(tolua_S,(char*)"caleOther5",caleOther5);
  tolua_constant(tolua_S,(char*)"caleOther6",caleOther6);
  tolua_constant(tolua_S,(char*)"caleOther7",caleOther7);
  tolua_constant(tolua_S,(char*)"caleOther8",caleOther8);
  tolua_constant(tolua_S,(char*)"caleOther9",caleOther9);
  tolua_constant(tolua_S,(char*)"caleOther10",caleOther10);
  tolua_constant(tolua_S,(char*)"caleMax",caleMax);
  tolua_constant(tolua_S,(char*)"enRoutineQuest",enRoutineQuest);
  tolua_constant(tolua_S,(char*)"enGuildTask",enGuildTask);
  tolua_constant(tolua_S,(char*)"enGuildDice",enGuildDice);
  tolua_constant(tolua_S,(char*)"enGuildAnimal",enGuildAnimal);
  tolua_constant(tolua_S,(char*)"enGiveFlower",enGiveFlower);
  tolua_constant(tolua_S,(char*)"enExploreSecret",enExploreSecret);
  tolua_constant(tolua_S,(char*)"enWushenTai",enWushenTai);
  tolua_constant(tolua_S,(char*)"enCorpse",enCorpse);
  tolua_constant(tolua_S,(char*)"enEscort",enEscort);
  tolua_constant(tolua_S,(char*)"enFish",enFish);
  tolua_constant(tolua_S,(char*)"enWanyaoyiji",enWanyaoyiji);
  tolua_constant(tolua_S,(char*)"enBagua",enBagua);
  tolua_constant(tolua_S,(char*)"enHolybeast",enHolybeast);
  tolua_constant(tolua_S,(char*)"enLoveFuben",enLoveFuben);
  tolua_constant(tolua_S,(char*)"enNirana",enNirana);
  tolua_constant(tolua_S,(char*)"enMoneyFuben",enMoneyFuben);
  tolua_constant(tolua_S,(char*)"enPetsave",enPetsave);
  tolua_constant(tolua_S,(char*)"enQqshFuben",enQqshFuben);
  tolua_constant(tolua_S,(char*)"enATMax",enATMax);
  tolua_constant(tolua_S,(char*)"gvLastCallSL",gvLastCallSL);
  tolua_constant(tolua_S,(char*)"gvGuildMax",gvGuildMax);
  tolua_constant(tolua_S,(char*)"siMount",siMount);
  tolua_constant(tolua_S,(char*)"siGem",siGem);
  tolua_constant(tolua_S,(char*)"siGuildSys",siGuildSys);
  tolua_constant(tolua_S,(char*)"siEquipStrong",siEquipStrong);
  tolua_constant(tolua_S,(char*)"siSkillSystem",siSkillSystem);
  tolua_constant(tolua_S,(char*)"siWorship",siWorship);
  tolua_constant(tolua_S,(char*)"siSkill",siSkill);
  tolua_constant(tolua_S,(char*)"siPractice",siPractice);
  tolua_constant(tolua_S,(char*)"siRoot",siRoot);
  tolua_constant(tolua_S,(char*)"siDujie",siDujie);
  tolua_constant(tolua_S,(char*)"siOneKeyFriend",siOneKeyFriend);
  tolua_constant(tolua_S,(char*)"siExchange",siExchange);
  tolua_constant(tolua_S,(char*)"siWing",siWing);
  tolua_constant(tolua_S,(char*)"siPet",siPet);
  tolua_constant(tolua_S,(char*)"siFightSys",siFightSys);
  tolua_constant(tolua_S,(char*)"siZhuMoDian",siZhuMoDian);
  tolua_constant(tolua_S,(char*)"siMarry",siMarry);
  tolua_constant(tolua_S,(char*)"siMijiSys",siMijiSys);
  tolua_constant(tolua_S,(char*)"siArtifact",siArtifact);
  tolua_constant(tolua_S,(char*)"siFashionDeal",siFashionDeal);
  tolua_constant(tolua_S,(char*)"siWingShenTong",siWingShenTong);
  tolua_constant(tolua_S,(char*)"siWingSkill",siWingSkill);
  tolua_constant(tolua_S,(char*)"siMountSkill",siMountSkill);
  tolua_constant(tolua_S,(char*)"siMountStage",siMountStage);
  tolua_constant(tolua_S,(char*)"siSpiritSoul",siSpiritSoul);
  tolua_constant(tolua_S,(char*)"siFriendSys",siFriendSys);
  tolua_constant(tolua_S,(char*)"siXunBao",siXunBao);
  tolua_constant(tolua_S,(char*)"siDayQuest",siDayQuest);
  tolua_constant(tolua_S,(char*)"siLoopTask",siLoopTask);
  tolua_constant(tolua_S,(char*)"siDailySign",siDailySign);
  tolua_constant(tolua_S,(char*)"siGemStone",siGemStone);
  tolua_constant(tolua_S,(char*)"siShenZhuang",siShenZhuang);
  tolua_constant(tolua_S,(char*)"siSysMAX",siSysMAX);
  tolua_constant(tolua_S,(char*)"PI_ID",PI_ID);
  tolua_constant(tolua_S,(char*)"PI_MONSERID",PI_MONSERID);
  tolua_constant(tolua_S,(char*)"PI_HP",PI_HP);
  tolua_constant(tolua_S,(char*)"PI_LEVEL",PI_LEVEL);
  tolua_constant(tolua_S,(char*)"PI_FIGHT_TYPE",PI_FIGHT_TYPE);
  tolua_constant(tolua_S,(char*)"PI_HP_STORE",PI_HP_STORE);
  tolua_constant(tolua_S,(char*)"PI_EXP",PI_EXP);
  tolua_constant(tolua_S,(char*)"PI_EXP1",PI_EXP1);
  tolua_constant(tolua_S,(char*)"PI_AMBIT",PI_AMBIT);
  tolua_constant(tolua_S,(char*)"PI_QUALITY_LV",PI_QUALITY_LV);
  tolua_constant(tolua_S,(char*)"PI_QUALITY_EXP",PI_QUALITY_EXP);
  tolua_constant(tolua_S,(char*)"PI_TYPE",PI_TYPE);
  tolua_constant(tolua_S,(char*)"PI_ATTACK_TYPE",PI_ATTACK_TYPE);
  tolua_constant(tolua_S,(char*)"PI_TITLE_AMBIT",PI_TITLE_AMBIT);
  tolua_constant(tolua_S,(char*)"PI_TITLE_QUALITY",PI_TITLE_QUALITY);
  tolua_constant(tolua_S,(char*)"PI_NATURE",PI_NATURE);
  tolua_constant(tolua_S,(char*)"PI_ATTACK",PI_ATTACK);
  tolua_constant(tolua_S,(char*)"PI_MAGIC_DEFEN",PI_MAGIC_DEFEN);
  tolua_constant(tolua_S,(char*)"PI_PHY_DEFEN",PI_PHY_DEFEN);
  tolua_constant(tolua_S,(char*)"PI_CRITICALSTRIKES",PI_CRITICALSTRIKES);
  tolua_constant(tolua_S,(char*)"PI_HITRATE",PI_HITRATE);
  tolua_constant(tolua_S,(char*)"PI_DODGERATE",PI_DODGERATE);
  tolua_constant(tolua_S,(char*)"PI_DEFCRITICALSTRIKES",PI_DEFCRITICALSTRIKES);
  tolua_constant(tolua_S,(char*)"PI_HP_PRO",PI_HP_PRO);
  tolua_constant(tolua_S,(char*)"PI_AMBIT_ATTACK",PI_AMBIT_ATTACK);
  tolua_constant(tolua_S,(char*)"PI_AMBIT_MAG_DEFEN",PI_AMBIT_MAG_DEFEN);
  tolua_constant(tolua_S,(char*)"PI_AMBIT_PHY_DEFEN",PI_AMBIT_PHY_DEFEN);
  tolua_constant(tolua_S,(char*)"PI_AMBIT_CRITICALSTRIKES",PI_AMBIT_CRITICALSTRIKES);
  tolua_constant(tolua_S,(char*)"PI_AMBIT_HITRATE",PI_AMBIT_HITRATE);
  tolua_constant(tolua_S,(char*)"PI_AMBIT_DODGERATE",PI_AMBIT_DODGERATE);
  tolua_constant(tolua_S,(char*)"PI_AMBIT_DEFCRITICALSTRIKES",PI_AMBIT_DEFCRITICALSTRIKES);
  tolua_constant(tolua_S,(char*)"PI_AMBIT_HP",PI_AMBIT_HP);
  tolua_constant(tolua_S,(char*)"PI_QUA_BASE_ATTACK",PI_QUA_BASE_ATTACK);
  tolua_constant(tolua_S,(char*)"PI_QUA_BASE_MAG_DEFEN",PI_QUA_BASE_MAG_DEFEN);
  tolua_constant(tolua_S,(char*)"PI_QUA_BASE_PHY_DEFEN",PI_QUA_BASE_PHY_DEFEN);
  tolua_constant(tolua_S,(char*)"PI_QUA_BASE_CRITICALSTRIKES",PI_QUA_BASE_CRITICALSTRIKES);
  tolua_constant(tolua_S,(char*)"PI_QUA_BASE_HITRATE",PI_QUA_BASE_HITRATE);
  tolua_constant(tolua_S,(char*)"PI_QUA_BASE_DODGERATE",PI_QUA_BASE_DODGERATE);
  tolua_constant(tolua_S,(char*)"PI_QUA_BASE_DEFCRITICALSTRIKES",PI_QUA_BASE_DEFCRITICALSTRIKES);
  tolua_constant(tolua_S,(char*)"PI_QUA_BASE_HP",PI_QUA_BASE_HP);
  tolua_constant(tolua_S,(char*)"PI_FIGHT_VALUE",PI_FIGHT_VALUE);
  tolua_constant(tolua_S,(char*)"PI_SKILL_SLOT",PI_SKILL_SLOT);
  tolua_constant(tolua_S,(char*)"PI_TOTAL_MAX_HP",PI_TOTAL_MAX_HP);
  tolua_constant(tolua_S,(char*)"PI_PROP_MAX",PI_PROP_MAX);
  tolua_constant(tolua_S,(char*)"PI_REAL_QUA_ATTACK",PI_REAL_QUA_ATTACK);
  tolua_constant(tolua_S,(char*)"PI_REAL_QUA_MAG_DEFEN",PI_REAL_QUA_MAG_DEFEN);
  tolua_constant(tolua_S,(char*)"PI_REAL_QUA_PHY_DEFEN",PI_REAL_QUA_PHY_DEFEN);
  tolua_constant(tolua_S,(char*)"PI_REAL_QUA_CRITICALSTRIKES",PI_REAL_QUA_CRITICALSTRIKES);
  tolua_constant(tolua_S,(char*)"PI_REAL_QUA_HITRATE",PI_REAL_QUA_HITRATE);
  tolua_constant(tolua_S,(char*)"PI_REAL_QUA_DODGERATE",PI_REAL_QUA_DODGERATE);
  tolua_constant(tolua_S,(char*)"PI_REAL_QUA_DEFCRITICALSTRIKES",PI_REAL_QUA_DEFCRITICALSTRIKES);
  tolua_constant(tolua_S,(char*)"PI_REAL_QUA_HP",PI_REAL_QUA_HP);
  tolua_constant(tolua_S,(char*)"PI_MAX",PI_MAX);
  tolua_constant(tolua_S,(char*)"PET_SKILL_BAR",PET_SKILL_BAR);
  tolua_constant(tolua_S,(char*)"PET_SKILL_STORE",PET_SKILL_STORE);
  tolua_constant(tolua_S,(char*)"PET_SKILL_SLOT",PET_SKILL_SLOT);
  tolua_constant(tolua_S,(char*)"PET_SKILL_BOOK",PET_SKILL_BOOK);
  tolua_constant(tolua_S,(char*)"lfDB",lfDB);
  tolua_constant(tolua_S,(char*)"lfBI",lfBI);
  tolua_constant(tolua_S,(char*)"lfText",lfText);
  tolua_constant(tolua_S,(char*)"lfIsPay",lfIsPay);
  tolua_constant(tolua_S,(char*)"lfNormal",lfNormal);
  tolua_constant(tolua_S,(char*)"ipStart",ipStart);
  tolua_constant(tolua_S,(char*)"ipBag",ipBag);
  tolua_constant(tolua_S,(char*)"ipDepot",ipDepot);
  tolua_constant(tolua_S,(char*)"ipLottery",ipLottery);
  tolua_constant(tolua_S,(char*)"ipEntrust",ipEntrust);
  tolua_constant(tolua_S,(char*)"ipTreasure",ipTreasure);
  tolua_constant(tolua_S,(char*)"ipBabel",ipBabel);
  tolua_constant(tolua_S,(char*)"ipMax",ipMax);
  tolua_constant(tolua_S,(char*)"acStart",acStart);
  tolua_constant(tolua_S,(char*)"acRoot",acRoot);
  tolua_constant(tolua_S,(char*)"acTitle",acTitle);
  tolua_constant(tolua_S,(char*)"acAchieveMedal",acAchieveMedal);
  tolua_constant(tolua_S,(char*)"acSpirit",acSpirit);
  tolua_constant(tolua_S,(char*)"acSpiritLevel",acSpiritLevel);
  tolua_constant(tolua_S,(char*)"acSpiritSoul",acSpiritSoul);
  tolua_constant(tolua_S,(char*)"acSpiritFashion",acSpiritFashion);
  tolua_constant(tolua_S,(char*)"acWingLevel",acWingLevel);
  tolua_constant(tolua_S,(char*)"acWingStage",acWingStage);
  tolua_constant(tolua_S,(char*)"acWingShenTong",acWingShenTong);
  tolua_constant(tolua_S,(char*)"acWingModel",acWingModel);
  tolua_constant(tolua_S,(char*)"acMountExtra",acMountExtra);
  tolua_constant(tolua_S,(char*)"acMountStage",acMountStage);
  tolua_constant(tolua_S,(char*)"acMountAppearance",acMountAppearance);
  tolua_constant(tolua_S,(char*)"acEqExclusive",acEqExclusive);
  tolua_constant(tolua_S,(char*)"acEqsign",acEqsign);
  tolua_constant(tolua_S,(char*)"acGuildSkill",acGuildSkill);
  tolua_constant(tolua_S,(char*)"acGuildAnimal",acGuildAnimal);
  tolua_constant(tolua_S,(char*)"acVipBuff",acVipBuff);
  tolua_constant(tolua_S,(char*)"acJingjieCuiti",acJingjieCuiti);
  tolua_constant(tolua_S,(char*)"acSpiritFashionStrong",acSpiritFashionStrong);
  tolua_constant(tolua_S,(char*)"acEquipMelt",acEquipMelt);
  tolua_constant(tolua_S,(char*)"acXiaoyaoEquip",acXiaoyaoEquip);
  tolua_constant(tolua_S,(char*)"acRingStage",acRingStage);
  tolua_constant(tolua_S,(char*)"acRingCl",acRingCl);
  tolua_constant(tolua_S,(char*)"acZsheng",acZsheng);
  tolua_constant(tolua_S,(char*)"acShenZhuangHead",acShenZhuangHead);
  tolua_constant(tolua_S,(char*)"acShenZhuangHand",acShenZhuangHand);
  tolua_constant(tolua_S,(char*)"acShenZhuangShoulder",acShenZhuangShoulder);
  tolua_constant(tolua_S,(char*)"acShenZhuangKnee",acShenZhuangKnee);
  tolua_constant(tolua_S,(char*)"acArtifact",acArtifact);
  tolua_constant(tolua_S,(char*)"acEqRefine",acEqRefine);
  tolua_constant(tolua_S,(char*)"acMax",acMax);
  tolua_constant(tolua_S,(char*)"dbDefault",dbDefault);
  tolua_constant(tolua_S,(char*)"dbEntity",dbEntity);
  tolua_constant(tolua_S,(char*)"dbGuild",dbGuild);
  tolua_constant(tolua_S,(char*)"dbConsignment",dbConsignment);
  tolua_constant(tolua_S,(char*)"dbMsg",dbMsg);
  tolua_constant(tolua_S,(char*)"dbRank",dbRank);
  tolua_constant(tolua_S,(char*)"dbGlobal",dbGlobal);
  tolua_constant(tolua_S,(char*)"dbFight",dbFight);
  tolua_constant(tolua_S,(char*)"dbMail",dbMail);
  tolua_constant(tolua_S,(char*)"dbCommon",dbCommon);
  tolua_constant(tolua_S,(char*)"dbConfig",dbConfig);
  tolua_constant(tolua_S,(char*)"dbWarTeam",dbWarTeam);
  tolua_constant(tolua_S,(char*)"dbTxApi",dbTxApi);
  tolua_constant(tolua_S,(char*)"dbCommonDB",dbCommonDB);
  tolua_constant(tolua_S,(char*)"dbAuction",dbAuction);
  tolua_constant(tolua_S,(char*)"efwNone",efwNone);
  tolua_constant(tolua_S,(char*)"efwNormal",efwNormal);
  tolua_constant(tolua_S,(char*)"efwRelogin",efwRelogin);
  tolua_constant(tolua_S,(char*)"xfwNone",xfwNone);
  tolua_constant(tolua_S,(char*)"xfwNormal",xfwNormal);
  tolua_constant(tolua_S,(char*)"xfwLogout",xfwLogout);
  tolua_constant(tolua_S,(char*)"xfwReturnCity",xfwReturnCity);
  tolua_constant(tolua_S,(char*)"xfwTeleport",xfwTeleport);
  tolua_constant(tolua_S,(char*)"eaeUpgradeGuild",eaeUpgradeGuild);
  tolua_constant(tolua_S,(char*)"eaeUpgradeEquip",eaeUpgradeEquip);
  tolua_constant(tolua_S,(char*)"eaeUpgradeCross",eaeUpgradeCross);
  tolua_constant(tolua_S,(char*)"pseDizzy",pseDizzy);
  tolua_constant(tolua_S,(char*)"pseThread",pseThread);
  tolua_constant(tolua_S,(char*)"pseLj",pseLj);
  tolua_constant(tolua_S,(char*)"pseXx",pseXx);
  tolua_constant(tolua_S,(char*)"pseTs",pseTs);
  tolua_constant(tolua_S,(char*)"pseGw",pseGw);
  tolua_constant(tolua_S,(char*)"pseTl",pseTl);
  tolua_constant(tolua_S,(char*)"pseFss",pseFss);
  tolua_constant(tolua_S,(char*)"pseNgs",pseNgs);
  tolua_constant(tolua_S,(char*)"pseKlj",pseKlj);
  tolua_constant(tolua_S,(char*)"pseDhz",pseDhz);
  tolua_constant(tolua_S,(char*)"pseFty",pseFty);
  tolua_constant(tolua_S,(char*)"pseMiji",pseMiji);
  tolua_constant(tolua_S,(char*)"eEquipBase",eEquipBase);
  tolua_constant(tolua_S,(char*)"eEquipStone",eEquipStone);
  tolua_constant(tolua_S,(char*)"eEquipStrong",eEquipStrong);
  tolua_constant(tolua_S,(char*)"eEquipsTage",eEquipsTage);
  tolua_constant(tolua_S,(char*)"eEquipQuality",eEquipQuality);
  tolua_constant(tolua_S,(char*)"eEquipBaptize",eEquipBaptize);
  tolua_constant(tolua_S,(char*)"eMountHunger",eMountHunger);
  tolua_constant(tolua_S,(char*)"eMountSkill",eMountSkill);
  tolua_constant(tolua_S,(char*)"eMountStage",eMountStage);
  tolua_constant(tolua_S,(char*)"eMountAppearance",eMountAppearance);
  tolua_constant(tolua_S,(char*)"eShenZhuangHead",eShenZhuangHead);
  tolua_constant(tolua_S,(char*)"eShenZhuangHand",eShenZhuangHand);
  tolua_constant(tolua_S,(char*)"eShenZhuangShoulder",eShenZhuangShoulder);
  tolua_constant(tolua_S,(char*)"eShenZhuangKnee",eShenZhuangKnee);
  tolua_constant(tolua_S,(char*)"bgSystemBuff",bgSystemBuff);
  tolua_constant(tolua_S,(char*)"bgSkillBuff",bgSkillBuff);
  tolua_constant(tolua_S,(char*)"bgDisplayBuff",bgDisplayBuff);
  tolua_constant(tolua_S,(char*)"bgSceneBuff",bgSceneBuff);
  tolua_constant(tolua_S,(char*)"bgFubenBuff",bgFubenBuff);
  tolua_constant(tolua_S,(char*)"bgManualBuff",bgManualBuff);
  tolua_constant(tolua_S,(char*)"bgGuildAnimal",bgGuildAnimal);
  tolua_constant(tolua_S,(char*)"bgGearsOfWar",bgGearsOfWar);
  tolua_constant(tolua_S,(char*)"bgUserBuffMin",bgUserBuffMin);
  tolua_constant(tolua_S,(char*)"bgSkillBuffMin",bgSkillBuffMin);
  tolua_constant(tolua_S,(char*)"bgHorseSkillBuff",bgHorseSkillBuff);
  tolua_constant(tolua_S,(char*)"bgMountSkillBuff",bgMountSkillBuff);
  tolua_constant(tolua_S,(char*)"bgSpiritSkillBuff",bgSpiritSkillBuff);
  tolua_constant(tolua_S,(char*)"bgAgainstSkillBuff",bgAgainstSkillBuff);
  tolua_constant(tolua_S,(char*)"bgPetSkillBuff",bgPetSkillBuff);
  tolua_constant(tolua_S,(char*)"bgHorseSkillBuff2",bgHorseSkillBuff2);
  tolua_constant(tolua_S,(char*)"bgHorseSkillBuff3",bgHorseSkillBuff3);
  tolua_constant(tolua_S,(char*)"bgSkillBuffMax",bgSkillBuffMax);
  tolua_constant(tolua_S,(char*)"bgItemBuffMin",bgItemBuffMin);
  tolua_constant(tolua_S,(char*)"bgUserBuffMax",bgUserBuffMax);
  tolua_constant(tolua_S,(char*)"bgItemBuffMax",bgItemBuffMax);
  tolua_constant(tolua_S,(char*)"AnyBuffGroup",AnyBuffGroup);
  tolua_constant(tolua_S,(char*)"MaxBuffGroup",MaxBuffGroup);
  tolua_constant(tolua_S,(char*)"mstInvalid",mstInvalid);
  tolua_constant(tolua_S,(char*)"mstIdle",mstIdle);
  tolua_constant(tolua_S,(char*)"mstFoundTarget",mstFoundTarget);
  tolua_constant(tolua_S,(char*)"mstAttack",mstAttack);
  tolua_constant(tolua_S,(char*)"mstAttacked",mstAttacked);
  tolua_constant(tolua_S,(char*)"mstDead",mstDead);
  tolua_constant(tolua_S,(char*)"mstHpLow",mstHpLow);
  tolua_constant(tolua_S,(char*)"mstCreate",mstCreate);
  tolua_constant(tolua_S,(char*)"mstDisappear",mstDisappear);
  tolua_constant(tolua_S,(char*)"mstMax",mstMax);
  tolua_constant(tolua_S,(char*)"CommonTeam",CommonTeam);
  tolua_constant(tolua_S,(char*)"FbTeam",FbTeam);
  tolua_constant(tolua_S,(char*)"LianfuTeam",LianfuTeam);
  tolua_constant(tolua_S,(char*)"MaxTeamType",MaxTeamType);
  tolua_constant(tolua_S,(char*)"rankAllAttack",rankAllAttack);
  tolua_constant(tolua_S,(char*)"rankOutDefence",rankOutDefence);
  tolua_constant(tolua_S,(char*)"rankInDefence",rankInDefence);
  tolua_constant(tolua_S,(char*)"rankMaxHp",rankMaxHp);
  tolua_constant(tolua_S,(char*)"rankCriticalStrikes",rankCriticalStrikes);
  tolua_constant(tolua_S,(char*)"rankDefCriticalStrikes",rankDefCriticalStrikes);
  tolua_constant(tolua_S,(char*)"rankHitrate",rankHitrate);
  tolua_constant(tolua_S,(char*)"rankDodgerate",rankDodgerate);
  tolua_constant(tolua_S,(char*)"rankIntAttack",rankIntAttack);
  tolua_constant(tolua_S,(char*)"rankOutAttack",rankOutAttack);
  tolua_constant(tolua_S,(char*)"rankMaxDataNum",rankMaxDataNum);
  tolua_constant(tolua_S,(char*)"rdEquipStrong",rdEquipStrong);
  tolua_constant(tolua_S,(char*)"rdEquipStone",rdEquipStone);
  tolua_constant(tolua_S,(char*)"rdEquipQuality",rdEquipQuality);
  tolua_constant(tolua_S,(char*)"rdEquipStage",rdEquipStage);
  tolua_constant(tolua_S,(char*)"rdEquipBaptize",rdEquipBaptize);
  tolua_constant(tolua_S,(char*)"rdEquipSign",rdEquipSign);
  tolua_constant(tolua_S,(char*)"rdMountFeed",rdMountFeed);
  tolua_constant(tolua_S,(char*)"rdMountSkill",rdMountSkill);
  tolua_constant(tolua_S,(char*)"rdMountStage",rdMountStage);
  tolua_constant(tolua_S,(char*)"rdWingLevel",rdWingLevel);
  tolua_constant(tolua_S,(char*)"rdWingStage",rdWingStage);
  tolua_constant(tolua_S,(char*)"rdSpiritLevel",rdSpiritLevel);
  tolua_constant(tolua_S,(char*)"rdSpiritSoul",rdSpiritSoul);
  tolua_constant(tolua_S,(char*)"rdSpiritFashion",rdSpiritFashion);
  tolua_constant(tolua_S,(char*)"rdMountModel",rdMountModel);
  tolua_constant(tolua_S,(char*)"rdWingSkill",rdWingSkill);
  tolua_constant(tolua_S,(char*)"rdWingShenTong",rdWingShenTong);
  tolua_constant(tolua_S,(char*)"rdWingModel",rdWingModel);
  tolua_constant(tolua_S,(char*)"rdSpiritSkill",rdSpiritSkill);
  tolua_constant(tolua_S,(char*)"rdTitle",rdTitle);
  tolua_constant(tolua_S,(char*)"rdRoot",rdRoot);
  tolua_constant(tolua_S,(char*)"rdDress",rdDress);
  tolua_constant(tolua_S,(char*)"rdSkill",rdSkill);
  tolua_constant(tolua_S,(char*)"rdPetSkill",rdPetSkill);
  tolua_constant(tolua_S,(char*)"rdPetNature",rdPetNature);
  tolua_constant(tolua_S,(char*)"rdPetCross",rdPetCross);
  tolua_constant(tolua_S,(char*)"rdPetStar",rdPetStar);
  tolua_constant(tolua_S,(char*)"rdEquipBase",rdEquipBase);
  tolua_constant(tolua_S,(char*)"rdMountEquip",rdMountEquip);
  tolua_constant(tolua_S,(char*)"rdPetEquip",rdPetEquip);
  tolua_constant(tolua_S,(char*)"rdWingEquip",rdWingEquip);
  tolua_constant(tolua_S,(char*)"rdEquipExclusive",rdEquipExclusive);
  tolua_constant(tolua_S,(char*)"rdAchieve",rdAchieve);
  tolua_constant(tolua_S,(char*)"rdJingjieCuiti",rdJingjieCuiti);
  tolua_constant(tolua_S,(char*)"rdGuildAnimal",rdGuildAnimal);
  tolua_constant(tolua_S,(char*)"rdGuildSkill",rdGuildSkill);
  tolua_constant(tolua_S,(char*)"rdPetFeed",rdPetFeed);
  tolua_constant(tolua_S,(char*)"rdShenZhuangHead",rdShenZhuangHead);
  tolua_constant(tolua_S,(char*)"rdShenZhuangHand",rdShenZhuangHand);
  tolua_constant(tolua_S,(char*)"rdShenZhuangShoulder",rdShenZhuangShoulder);
  tolua_constant(tolua_S,(char*)"rdShenZhuangKnee",rdShenZhuangKnee);
  tolua_constant(tolua_S,(char*)"rdEqRefine",rdEqRefine);
  tolua_constant(tolua_S,(char*)"rdMax",rdMax);
  tolua_constant(tolua_S,(char*)"bsCommSrv",bsCommSrv);
  tolua_constant(tolua_S,(char*)"bsBattleSrv",bsBattleSrv);
  tolua_constant(tolua_S,(char*)"bsMainBattleSrv",bsMainBattleSrv);
  tolua_constant(tolua_S,(char*)"bsLianFuSrv",bsLianFuSrv);
  tolua_constant(tolua_S,(char*)"vlStart",vlStart);
  tolua_constant(tolua_S,(char*)"vlActorId",vlActorId);
  tolua_constant(tolua_S,(char*)"vlGuildId",vlGuildId);
  tolua_constant(tolua_S,(char*)"vlMax",vlMax);
  tolua_constant(tolua_S,(char*)"CROSSSERVER_ALL",CROSSSERVER_ALL);
  tolua_constant(tolua_S,(char*)"CROSSSERVER_CROSSBATTLE",CROSSSERVER_CROSSBATTLE);
  tolua_constant(tolua_S,(char*)"CROSSSERVER_LIANFU",CROSSSERVER_LIANFU);
  tolua_constant(tolua_S,(char*)"CROSSLOGIN_CROSSWAR",CROSSLOGIN_CROSSWAR);
  tolua_constant(tolua_S,(char*)"CROSSLOGIN_LIANFU",CROSSLOGIN_LIANFU);
  tolua_constant(tolua_S,(char*)"dtActorDeal",dtActorDeal);
  tolua_constant(tolua_S,(char*)"dtServerDeal",dtServerDeal);
  tolua_constant(tolua_S,(char*)"dtToActor",dtToActor);
  tolua_constant(tolua_S,(char*)"dtBroadCast",dtBroadCast);
  tolua_constant(tolua_S,(char*)"MonsterType_Normal",MonsterType_Normal);
  tolua_constant(tolua_S,(char*)"MonsterType_Boss",MonsterType_Boss);
  tolua_constant(tolua_S,(char*)"MonsterType_GatherMonster",MonsterType_GatherMonster);
  tolua_constant(tolua_S,(char*)"MonsterType_Pet",MonsterType_Pet);
  tolua_constant(tolua_S,(char*)"MonsterType_AexRing",MonsterType_AexRing);
  tolua_cclass(tolua_S,"ActorBasicData","ActorBasicData","",NULL);
  tolua_beginmodule(tolua_S,(char*)"ActorBasicData");
   tolua_variable(tolua_S,"account_id",tolua_get_ActorBasicData_unsigned_account_id,tolua_set_ActorBasicData_unsigned_account_id);
   tolua_variable(tolua_S,"account_name",tolua_get_ActorBasicData_account_name,tolua_set_ActorBasicData_account_name);
   tolua_variable(tolua_S,"actor_id",tolua_get_ActorBasicData_actor_id,tolua_set_ActorBasicData_actor_id);
   tolua_variable(tolua_S,"actor_name",tolua_get_ActorBasicData_actor_name,tolua_set_ActorBasicData_actor_name);
   tolua_variable(tolua_S,"server_idnex",tolua_get_ActorBasicData_unsigned_server_idnex,tolua_set_ActorBasicData_unsigned_server_idnex);
   tolua_variable(tolua_S,"job",tolua_get_ActorBasicData_unsigned_job,tolua_set_ActorBasicData_unsigned_job);
   tolua_variable(tolua_S,"sex",tolua_get_ActorBasicData_unsigned_sex,tolua_set_ActorBasicData_unsigned_sex);
   tolua_variable(tolua_S,"headimage",tolua_get_ActorBasicData_unsigned_headimage,tolua_set_ActorBasicData_unsigned_headimage);
   tolua_variable(tolua_S,"level",tolua_get_ActorBasicData_unsigned_level,tolua_set_ActorBasicData_unsigned_level);
   tolua_variable(tolua_S,"exp",tolua_get_ActorBasicData_unsigned_exp,tolua_set_ActorBasicData_unsigned_exp);
   tolua_variable(tolua_S,"fb_uid",tolua_get_ActorBasicData_fb_uid,tolua_set_ActorBasicData_fb_uid);
   tolua_variable(tolua_S,"fb_scene_id",tolua_get_ActorBasicData_unsigned_fb_scene_id,tolua_set_ActorBasicData_unsigned_fb_scene_id);
   tolua_variable(tolua_S,"create_time",tolua_get_ActorBasicData_unsigned_create_time,tolua_set_ActorBasicData_unsigned_create_time);
   tolua_variable(tolua_S,"last_online_time",tolua_get_ActorBasicData_unsigned_last_online_time,tolua_set_ActorBasicData_unsigned_last_online_time);
   tolua_variable(tolua_S,"last_login_ip",tolua_get_ActorBasicData_unsigned_last_login_ip,tolua_set_ActorBasicData_unsigned_last_login_ip);
   tolua_variable(tolua_S,"total_online",tolua_get_ActorBasicData_unsigned_total_online,tolua_set_ActorBasicData_unsigned_total_online);
   tolua_variable(tolua_S,"daily_online",tolua_get_ActorBasicData_unsigned_daily_online,tolua_set_ActorBasicData_unsigned_daily_online);
   tolua_variable(tolua_S,"bag_grid",tolua_get_ActorBasicData_unsigned_bag_grid,tolua_set_ActorBasicData_unsigned_bag_grid);
   tolua_variable(tolua_S,"gold",tolua_get_ActorBasicData_gold,tolua_set_ActorBasicData_gold);
   tolua_variable(tolua_S,"yuanbao",tolua_get_ActorBasicData_yuanbao,tolua_set_ActorBasicData_yuanbao);
   tolua_variable(tolua_S,"total_power",tolua_get_ActorBasicData_total_power,tolua_set_ActorBasicData_total_power);
   tolua_variable(tolua_S,"rank_power",tolua_get_ActorBasicData_rank_power,tolua_set_ActorBasicData_rank_power);
   tolua_variable(tolua_S,"recharge",tolua_get_ActorBasicData_unsigned_recharge,tolua_set_ActorBasicData_unsigned_recharge);
   tolua_variable(tolua_S,"paid",tolua_get_ActorBasicData_unsigned_paid,tolua_set_ActorBasicData_unsigned_paid);
   tolua_variable(tolua_S,"chapter_level",tolua_get_ActorBasicData_unsigned_chapter_level,tolua_set_ActorBasicData_unsigned_chapter_level);
   tolua_variable(tolua_S,"vip_level",tolua_get_ActorBasicData_unsigned_vip_level,tolua_set_ActorBasicData_unsigned_vip_level);
   tolua_variable(tolua_S,"essence",tolua_get_ActorBasicData_essence,tolua_set_ActorBasicData_essence);
   tolua_variable(tolua_S,"zhuansheng_lv",tolua_get_ActorBasicData_zhuansheng_lv,tolua_set_ActorBasicData_zhuansheng_lv);
   tolua_variable(tolua_S,"zhuansheng_exp",tolua_get_ActorBasicData_zhuansheng_exp,tolua_set_ActorBasicData_zhuansheng_exp);
   tolua_variable(tolua_S,"monthcard",tolua_get_ActorBasicData_unsigned_monthcard,tolua_set_ActorBasicData_unsigned_monthcard);
   tolua_variable(tolua_S,"tianti_level",tolua_get_ActorBasicData_tianti_level,tolua_set_ActorBasicData_tianti_level);
   tolua_variable(tolua_S,"tianti_dan",tolua_get_ActorBasicData_tianti_dan,tolua_set_ActorBasicData_tianti_dan);
   tolua_variable(tolua_S,"tianti_win_count",tolua_get_ActorBasicData_tianti_win_count,tolua_set_ActorBasicData_tianti_win_count);
   tolua_variable(tolua_S,"tianti_week_refres",tolua_get_ActorBasicData_tianti_week_refres,tolua_set_ActorBasicData_tianti_week_refres);
   tolua_variable(tolua_S,"total_wing_power",tolua_get_ActorBasicData_total_wing_power,tolua_set_ActorBasicData_total_wing_power);
   tolua_variable(tolua_S,"warrior_power",tolua_get_ActorBasicData_warrior_power,tolua_set_ActorBasicData_warrior_power);
   tolua_variable(tolua_S,"mage_power",tolua_get_ActorBasicData_mage_power,tolua_set_ActorBasicData_mage_power);
   tolua_variable(tolua_S,"taoistpriest_power",tolua_get_ActorBasicData_taoistpriest_power,tolua_set_ActorBasicData_taoistpriest_power);
   tolua_variable(tolua_S,"train_level",tolua_get_ActorBasicData_train_level,tolua_set_ActorBasicData_train_level);
   tolua_variable(tolua_S,"train_exp",tolua_get_ActorBasicData_train_exp,tolua_set_ActorBasicData_train_exp);
   tolua_variable(tolua_S,"total_stone_level",tolua_get_ActorBasicData_total_stone_level,tolua_set_ActorBasicData_total_stone_level);
   tolua_variable(tolua_S,"total_zhuling_level",tolua_get_ActorBasicData_total_zhuling_level,tolua_set_ActorBasicData_total_zhuling_level);
   tolua_variable(tolua_S,"guild_id_",tolua_get_ActorBasicData_guild_id_,tolua_set_ActorBasicData_guild_id_);
   tolua_variable(tolua_S,"guild_name_",tolua_get_ActorBasicData_guild_name_,tolua_set_ActorBasicData_guild_name_);
   tolua_variable(tolua_S,"zhan_ling_star",tolua_get_ActorBasicData_zhan_ling_star,tolua_set_ActorBasicData_zhan_ling_star);
   tolua_variable(tolua_S,"zhan_ling_stage",tolua_get_ActorBasicData_zhan_ling_stage,tolua_set_ActorBasicData_zhan_ling_stage);
   tolua_variable(tolua_S,"total_loongsoul_level",tolua_get_ActorBasicData_total_loongsoul_level,tolua_set_ActorBasicData_total_loongsoul_level);
   tolua_variable(tolua_S,"prestige_exp",tolua_get_ActorBasicData_prestige_exp,tolua_set_ActorBasicData_prestige_exp);
   tolua_variable(tolua_S,"feats",tolua_get_ActorBasicData_feats,tolua_set_ActorBasicData_feats);
   tolua_array(tolua_S,"ex_ring_lv",tolua_get_server_ActorBasicData_ex_ring_lv,tolua_set_server_ActorBasicData_ex_ring_lv);
   tolua_variable(tolua_S,"shatter",tolua_get_ActorBasicData_shatter,tolua_set_ActorBasicData_shatter);
   tolua_variable(tolua_S,"spcshatter",tolua_get_ActorBasicData_spcshatter,tolua_set_ActorBasicData_spcshatter);
   tolua_variable(tolua_S,"knighthood_lv",tolua_get_ActorBasicData_unsigned_knighthood_lv,tolua_set_ActorBasicData_unsigned_knighthood_lv);
   tolua_variable(tolua_S,"togeatter",tolua_get_ActorBasicData_togeatter,tolua_set_ActorBasicData_togeatter);
   tolua_variable(tolua_S,"total_wing_lv",tolua_get_ActorBasicData_total_wing_lv,tolua_set_ActorBasicData_total_wing_lv);
   tolua_variable(tolua_S,"total_tujian_power",tolua_get_ActorBasicData_total_tujian_power,tolua_set_ActorBasicData_total_tujian_power);
   tolua_variable(tolua_S,"total_equip_power",tolua_get_ActorBasicData_total_equip_power,tolua_set_ActorBasicData_total_equip_power);
   tolua_variable(tolua_S,"togeatterhigh",tolua_get_ActorBasicData_togeatterhigh,tolua_set_ActorBasicData_togeatterhigh);
   tolua_variable(tolua_S,"privilege_monthcard",tolua_get_ActorBasicData_unsigned_privilege_monthcard,tolua_set_ActorBasicData_unsigned_privilege_monthcard);
   tolua_variable(tolua_S,"reincarnate_lv",tolua_get_ActorBasicData_reincarnate_lv,tolua_set_ActorBasicData_reincarnate_lv);
   tolua_variable(tolua_S,"reincarnate_exp",tolua_get_ActorBasicData_reincarnate_exp,tolua_set_ActorBasicData_reincarnate_exp);
   tolua_variable(tolua_S,"field_chapter_level",tolua_get_ActorBasicData_field_chapter_level,tolua_set_ActorBasicData_field_chapter_level);
   tolua_variable(tolua_S,"field_chapter_progress",tolua_get_ActorBasicData_field_chapter_progress,tolua_set_ActorBasicData_field_chapter_progress);
   tolua_variable(tolua_S,"field_pk_mode",tolua_get_ActorBasicData_field_pk_mode,tolua_set_ActorBasicData_field_pk_mode);
   tolua_variable(tolua_S,"field_last_fuben_id",tolua_get_ActorBasicData_field_last_fuben_id,tolua_set_ActorBasicData_field_last_fuben_id);
   tolua_variable(tolua_S,"field_last_pos_x",tolua_get_ActorBasicData_field_last_pos_x,tolua_set_ActorBasicData_field_last_pos_x);
   tolua_variable(tolua_S,"field_last_pos_y",tolua_get_ActorBasicData_field_last_pos_y,tolua_set_ActorBasicData_field_last_pos_y);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,(char*)"toActorBasicData",tolua_server_toActorBasicData00);
  tolua_cclass(tolua_S,"SkillsData","SkillsData","",NULL);
  tolua_beginmodule(tolua_S,(char*)"SkillsData");
   tolua_array(tolua_S,"skill_level",tolua_get_server_SkillsData_skill_level,tolua_set_server_SkillsData_skill_level);
   tolua_array(tolua_S,"skill_index",tolua_get_server_SkillsData_skill_index,tolua_set_server_SkillsData_skill_index);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"YuanShenData","YuanShenData","",NULL);
  tolua_beginmodule(tolua_S,(char*)"YuanShenData");
   tolua_array(tolua_S,"slot_filled",tolua_get_server_YuanShenData_slot_filled,tolua_set_server_YuanShenData_slot_filled);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,(char*)"EquipSlotType_Weapon",EquipSlotType_Weapon);
  tolua_constant(tolua_S,(char*)"EquipSlotType_Helmet",EquipSlotType_Helmet);
  tolua_constant(tolua_S,(char*)"EquipSlotType_Coat",EquipSlotType_Coat);
  tolua_constant(tolua_S,(char*)"EquipSlotType_Necklace",EquipSlotType_Necklace);
  tolua_constant(tolua_S,(char*)"EquipSlotType_Wrist",EquipSlotType_Wrist);
  tolua_constant(tolua_S,(char*)"EquipSlotType_Belt",EquipSlotType_Belt);
  tolua_constant(tolua_S,(char*)"EquipSlotType_Ring",EquipSlotType_Ring);
  tolua_constant(tolua_S,(char*)"EquipSlotType_Shoes",EquipSlotType_Shoes);
  tolua_constant(tolua_S,(char*)"EquipSlotType_Dzi",EquipSlotType_Dzi);
  tolua_constant(tolua_S,(char*)"EquipSlotType_Hats",EquipSlotType_Hats);
  tolua_constant(tolua_S,(char*)"EquipSlotType_Mark",EquipSlotType_Mark);
  tolua_constant(tolua_S,(char*)"EquipSlotType_Cloak",EquipSlotType_Cloak);
  tolua_constant(tolua_S,(char*)"EquipSlotType_Shield",EquipSlotType_Shield);
  tolua_constant(tolua_S,(char*)"EquipSlotType_Max",EquipSlotType_Max);
  tolua_constant(tolua_S,(char*)"WingSlotType_Hub",WingSlotType_Hub);
  tolua_constant(tolua_S,(char*)"WingSlotType_Stone",WingSlotType_Stone);
  tolua_constant(tolua_S,(char*)"WingSlotType_Feathers",WingSlotType_Feathers);
  tolua_constant(tolua_S,(char*)"WingSlotType_Colorplume",WingSlotType_Colorplume);
  tolua_constant(tolua_S,(char*)"WingSlotType_Max",WingSlotType_Max);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"EquipSlotData","EquipSlotData","",tolua_collect_EquipSlotData);
  #else
  tolua_cclass(tolua_S,"EquipSlotData","EquipSlotData","",NULL);
  #endif
  tolua_beginmodule(tolua_S,(char*)"EquipSlotData");
   tolua_variable(tolua_S,"strength_lv",tolua_get_EquipSlotData_strength_lv,tolua_set_EquipSlotData_strength_lv);
   tolua_variable(tolua_S,"fuling_lv",tolua_get_EquipSlotData_fuling_lv,tolua_set_EquipSlotData_fuling_lv);
   tolua_variable(tolua_S,"gem_lv",tolua_get_EquipSlotData_gem_lv,tolua_set_EquipSlotData_gem_lv);
   tolua_variable(tolua_S,"equip_data",tolua_get_EquipSlotData_equip_data,tolua_set_EquipSlotData_equip_data);
   tolua_variable(tolua_S,"zhuling_lv",tolua_get_EquipSlotData_zhuling_lv,tolua_set_EquipSlotData_zhuling_lv);
   tolua_variable(tolua_S,"soul_lv",tolua_get_EquipSlotData_soul_lv,tolua_set_EquipSlotData_soul_lv);
   tolua_variable(tolua_S,"bless_lv",tolua_get_EquipSlotData_bless_lv,tolua_set_EquipSlotData_bless_lv);
   tolua_variable(tolua_S,"fuling_exp",tolua_get_EquipSlotData_fuling_exp,tolua_set_EquipSlotData_fuling_exp);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"EquipsData","EquipsData","",NULL);
  tolua_beginmodule(tolua_S,(char*)"EquipsData");
   tolua_array(tolua_S,"slot_data",tolua_get_server_EquipsData_slot_data,tolua_set_server_EquipsData_slot_data);
   tolua_array(tolua_S,"god_slot_data",tolua_get_server_EquipsData_god_slot_data,tolua_set_server_EquipsData_god_slot_data);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ExRingsData","ExRingsData","",NULL);
  tolua_beginmodule(tolua_S,(char*)"ExRingsData");
   tolua_array(tolua_S,"ring_level",tolua_get_server_ExRingsData_ring_level,tolua_set_server_ExRingsData_ring_level);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"WingsData","WingsData","",NULL);
  tolua_beginmodule(tolua_S,(char*)"WingsData");
   tolua_variable(tolua_S,"level",tolua_get_WingsData_level,tolua_set_WingsData_level);
   tolua_variable(tolua_S,"exp",tolua_get_WingsData_exp,tolua_set_WingsData_exp);
   tolua_variable(tolua_S,"openStatus",tolua_get_WingsData_openStatus,tolua_set_WingsData_openStatus);
   tolua_variable(tolua_S,"ctime",tolua_get_WingsData_unsigned_ctime,tolua_set_WingsData_unsigned_ctime);
   tolua_array(tolua_S,"pill",tolua_get_server_WingsData_pill,tolua_set_server_WingsData_pill);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"WingsEquip","WingsEquip","",NULL);
  tolua_beginmodule(tolua_S,(char*)"WingsEquip");
   tolua_array(tolua_S,"wing_slot",tolua_get_server_WingsEquip_wing_slot,tolua_set_server_WingsEquip_wing_slot);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"JingMaiData","JingMaiData","",NULL);
  tolua_beginmodule(tolua_S,(char*)"JingMaiData");
   tolua_variable(tolua_S,"level",tolua_get_JingMaiData_level,tolua_set_JingMaiData_level);
   tolua_variable(tolua_S,"stage",tolua_get_JingMaiData_stage,tolua_set_JingMaiData_stage);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"SkillsBreakData","SkillsBreakData","",NULL);
  tolua_beginmodule(tolua_S,(char*)"SkillsBreakData");
   tolua_array(tolua_S,"skill_break_level",tolua_get_server_SkillsBreakData_skill_break_level,tolua_set_server_SkillsBreakData_skill_break_level);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"LoogsoulData","LoogsoulData","",NULL);
  tolua_beginmodule(tolua_S,(char*)"LoogsoulData");
   tolua_variable(tolua_S,"stage",tolua_get_LoogsoulData_stage,tolua_set_LoogsoulData_stage);
   tolua_variable(tolua_S,"level",tolua_get_LoogsoulData_level,tolua_set_LoogsoulData_level);
   tolua_variable(tolua_S,"exp",tolua_get_LoogsoulData_exp,tolua_set_LoogsoulData_exp);
   tolua_variable(tolua_S,"act",tolua_get_LoogsoulData_act,tolua_set_LoogsoulData_act);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ShieldData","ShieldData","",NULL);
  tolua_beginmodule(tolua_S,(char*)"ShieldData");
   tolua_variable(tolua_S,"stage",tolua_get_ShieldData_stage,tolua_set_ShieldData_stage);
   tolua_variable(tolua_S,"level",tolua_get_ShieldData_level,tolua_set_ShieldData_level);
   tolua_variable(tolua_S,"exp",tolua_get_ShieldData_exp,tolua_set_ShieldData_exp);
   tolua_variable(tolua_S,"act",tolua_get_ShieldData_act,tolua_set_ShieldData_act);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"XueyuData","XueyuData","",NULL);
  tolua_beginmodule(tolua_S,(char*)"XueyuData");
   tolua_variable(tolua_S,"stage",tolua_get_XueyuData_stage,tolua_set_XueyuData_stage);
   tolua_variable(tolua_S,"level",tolua_get_XueyuData_level,tolua_set_XueyuData_level);
   tolua_variable(tolua_S,"exp",tolua_get_XueyuData_exp,tolua_set_XueyuData_exp);
   tolua_variable(tolua_S,"act",tolua_get_XueyuData_act,tolua_set_XueyuData_act);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"FuWenData","FuWenData","",NULL);
  tolua_beginmodule(tolua_S,(char*)"FuWenData");
   tolua_array(tolua_S,"fuwen_slot",tolua_get_server_FuWenData_fuwen_slot,tolua_set_server_FuWenData_fuwen_slot);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,(char*)"HEIRLOOM_TYPE_MAX",HEIRLOOM_TYPE_MAX);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"RoleData","RoleData","",tolua_collect_RoleData);
  #else
  tolua_cclass(tolua_S,"RoleData","RoleData","",NULL);
  #endif
  tolua_beginmodule(tolua_S,(char*)"RoleData");
   tolua_variable(tolua_S,"id",tolua_get_RoleData_id,tolua_set_RoleData_id);
   tolua_variable(tolua_S,"job",tolua_get_RoleData_job,tolua_set_RoleData_job);
   tolua_variable(tolua_S,"sex",tolua_get_RoleData_sex,tolua_set_RoleData_sex);
   tolua_variable(tolua_S,"power",tolua_get_RoleData_power,tolua_set_RoleData_power);
   tolua_variable(tolua_S,"skills",tolua_get_RoleData_skills,tolua_set_RoleData_skills);
   tolua_variable(tolua_S,"equips_data",tolua_get_RoleData_equips_data,tolua_set_RoleData_equips_data);
   tolua_variable(tolua_S,"ex_rings",tolua_get_RoleData_ex_rings,tolua_set_RoleData_ex_rings);
   tolua_variable(tolua_S,"wings",tolua_get_RoleData_wings,tolua_set_RoleData_wings);
   tolua_variable(tolua_S,"jingmai_data",tolua_get_RoleData_jingmai_data,tolua_set_RoleData_jingmai_data);
   tolua_variable(tolua_S,"loogsoul_data",tolua_get_RoleData_loogsoul_data,tolua_set_RoleData_loogsoul_data);
   tolua_variable(tolua_S,"fuwen_data",tolua_get_RoleData_fuwen_data,tolua_set_RoleData_fuwen_data);
   tolua_array(tolua_S,"heirloom",tolua_get_server_RoleData_heirloom,tolua_set_server_RoleData_heirloom);
   tolua_variable(tolua_S,"weapon_soul_id",tolua_get_RoleData_weapon_soul_id,tolua_set_RoleData_weapon_soul_id);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"RoleDatas","RoleDatas","",tolua_collect_RoleDatas);
  #else
  tolua_cclass(tolua_S,"RoleDatas","RoleDatas","",NULL);
  #endif
  tolua_beginmodule(tolua_S,(char*)"RoleDatas");
   tolua_variable(tolua_S,"role_count",tolua_get_RoleDatas_role_count,tolua_set_RoleDatas_role_count);
   tolua_array(tolua_S,"roles",tolua_get_server_RoleDatas_roles,tolua_set_server_RoleDatas_roles);
   tolua_function(tolua_S,(char*)"new",tolua_server_RoleDatas_new00);
   tolua_function(tolua_S,(char*)"new_local",tolua_server_RoleDatas_new00_local);
   tolua_function(tolua_S,".call",tolua_server_RoleDatas_new00_local);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,(char*)"Protocol",0);
  tolua_beginmodule(tolua_S,(char*)"Protocol");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"TestProto","Protocol::TestProto","BaseProto",tolua_collect_Protocol__TestProto);
   #else
   tolua_cclass(tolua_S,"TestProto","Protocol::TestProto","BaseProto",NULL);
   #endif
   tolua_beginmodule(tolua_S,(char*)"TestProto");
    tolua_function(tolua_S,(char*)"new",tolua_server_Protocol_TestProto_new00);
    tolua_function(tolua_S,(char*)"new_local",tolua_server_Protocol_TestProto_new00_local);
    tolua_function(tolua_S,".call",tolua_server_Protocol_TestProto_new00_local);
    tolua_variable(tolua_S,"a",tolua_get_Protocol__TestProto_a,tolua_set_Protocol__TestProto_a);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Test","Protocol::Test","",NULL);
   tolua_beginmodule(tolua_S,(char*)"Test");
    tolua_variable(tolua_S,"a",tolua_get_Protocol__Test_a,tolua_set_Protocol__Test_a);
    tolua_variable(tolua_S,"b",tolua_get_Protocol__Test_b,tolua_set_Protocol__Test_b);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Attribute","Attribute","",tolua_collect_Attribute);
  #else
  tolua_cclass(tolua_S,"Attribute","Attribute","",NULL);
  #endif
  tolua_beginmodule(tolua_S,(char*)"Attribute");
   tolua_constant(tolua_S,(char*)"atHp",Attribute::atHp);
   tolua_constant(tolua_S,(char*)"atMp",Attribute::atMp);
   tolua_constant(tolua_S,(char*)"atHpMax",Attribute::atHpMax);
   tolua_constant(tolua_S,(char*)"atMpMax",Attribute::atMpMax);
   tolua_constant(tolua_S,(char*)"atAtk",Attribute::atAtk);
   tolua_constant(tolua_S,(char*)"atDef",Attribute::atDef);
   tolua_constant(tolua_S,(char*)"atRes",Attribute::atRes);
   tolua_constant(tolua_S,(char*)"atCrit",Attribute::atCrit);
   tolua_constant(tolua_S,(char*)"atTough",Attribute::atTough);
   tolua_constant(tolua_S,(char*)"atMoveSpeed",Attribute::atMoveSpeed);
   tolua_constant(tolua_S,(char*)"atAttackSpeed",Attribute::atAttackSpeed);
   tolua_constant(tolua_S,(char*)"atHpEx",Attribute::atHpEx);
   tolua_constant(tolua_S,(char*)"atAtkEx",Attribute::atAtkEx);
   tolua_constant(tolua_S,(char*)"atStunPower",Attribute::atStunPower);
   tolua_constant(tolua_S,(char*)"atStunRes",Attribute::atStunRes);
   tolua_constant(tolua_S,(char*)"atStunTime",Attribute::atStunTime);
   tolua_constant(tolua_S,(char*)"atDamageReduction",Attribute::atDamageReduction);
   tolua_constant(tolua_S,(char*)"atCritHurt",Attribute::atCritHurt);
   tolua_constant(tolua_S,(char*)"atRegeneration",Attribute::atRegeneration);
   tolua_constant(tolua_S,(char*)"atCritEnhance",Attribute::atCritEnhance);
   tolua_constant(tolua_S,(char*)"atPenetrate",Attribute::atPenetrate);
   tolua_constant(tolua_S,(char*)"atRoleDamageEnhance",Attribute::atRoleDamageEnhance);
   tolua_constant(tolua_S,(char*)"atRoleDamageReduction",Attribute::atRoleDamageReduction);
   tolua_constant(tolua_S,(char*)"atDefEx",Attribute::atDefEx);
   tolua_constant(tolua_S,(char*)"atResEx",Attribute::atResEx);
   tolua_constant(tolua_S,(char*)"atNeiGong",Attribute::atNeiGong);
   tolua_constant(tolua_S,(char*)"atNeiGongMax",Attribute::atNeiGongMax);
   tolua_constant(tolua_S,(char*)"atNeiGongDamageAbsorb",Attribute::atNeiGongDamageAbsorb);
   tolua_constant(tolua_S,(char*)"atJob1HpEx",Attribute::atJob1HpEx);
   tolua_constant(tolua_S,(char*)"atJob2HpEx",Attribute::atJob2HpEx);
   tolua_constant(tolua_S,(char*)"atJob3HpEx",Attribute::atJob3HpEx);
   tolua_constant(tolua_S,(char*)"atNeiGongRestore",Attribute::atNeiGongRestore);
   tolua_constant(tolua_S,(char*)"atVamirePro",Attribute::atVamirePro);
   tolua_constant(tolua_S,(char*)"atVamirePen",Attribute::atVamirePen);
   tolua_constant(tolua_S,(char*)"atVamireCd",Attribute::atVamireCd);
   tolua_constant(tolua_S,(char*)"atCursePro",Attribute::atCursePro);
   tolua_constant(tolua_S,(char*)"atCurseCd",Attribute::atCurseCd);
   tolua_constant(tolua_S,(char*)"atAttAddDamPro",Attribute::atAttAddDamPro);
   tolua_constant(tolua_S,(char*)"atAttAddDamVal",Attribute::atAttAddDamVal);
   tolua_constant(tolua_S,(char*)"atBeAttAddHpPro",Attribute::atBeAttAddHpPro);
   tolua_constant(tolua_S,(char*)"atBeAttAddHpVal",Attribute::atBeAttAddHpVal);
   tolua_constant(tolua_S,(char*)"atAttMbAddDamPen",Attribute::atAttMbAddDamPen);
   tolua_constant(tolua_S,(char*)"atHpLtAddBuff",Attribute::atHpLtAddBuff);
   tolua_constant(tolua_S,(char*)"atAttHpLtPenAddDam",Attribute::atAttHpLtPenAddDam);
   tolua_constant(tolua_S,(char*)"atAttHpLtAddDamPen",Attribute::atAttHpLtAddDamPen);
   tolua_constant(tolua_S,(char*)"atJob1AtkEx",Attribute::atJob1AtkEx);
   tolua_constant(tolua_S,(char*)"atJob2AtkEx",Attribute::atJob2AtkEx);
   tolua_constant(tolua_S,(char*)"atJob3AtkEx",Attribute::atJob3AtkEx);
   tolua_constant(tolua_S,(char*)"atJob1DefEx",Attribute::atJob1DefEx);
   tolua_constant(tolua_S,(char*)"atJob2DefEx",Attribute::atJob2DefEx);
   tolua_constant(tolua_S,(char*)"atJob3DefEx",Attribute::atJob3DefEx);
   tolua_constant(tolua_S,(char*)"atJob1ResEx",Attribute::atJob1ResEx);
   tolua_constant(tolua_S,(char*)"atJob2ResEx",Attribute::atJob2ResEx);
   tolua_constant(tolua_S,(char*)"atJob3ResEx",Attribute::atJob3ResEx);
   tolua_constant(tolua_S,(char*)"atAttPerDamPan",Attribute::atAttPerDamPan);
   tolua_constant(tolua_S,(char*)"atDamageEnhance",Attribute::atDamageEnhance);
   tolua_constant(tolua_S,(char*)"atCritEnhanceResist",Attribute::atCritEnhanceResist);
   tolua_constant(tolua_S,(char*)"atHolyDamege",Attribute::atHolyDamege);
   tolua_constant(tolua_S,(char*)"atHolyMaster",Attribute::atHolyMaster);
   tolua_constant(tolua_S,(char*)"atHolyResist",Attribute::atHolyResist);
   tolua_constant(tolua_S,(char*)"atTogetherHolyDamege",Attribute::atTogetherHolyDamege);
   tolua_constant(tolua_S,(char*)"atTogetherHolyMaster",Attribute::atTogetherHolyMaster);
   tolua_constant(tolua_S,(char*)"atTogetherHolyResist",Attribute::atTogetherHolyResist);
   tolua_constant(tolua_S,(char*)"atZhuiMingPro",Attribute::atZhuiMingPro);
   tolua_constant(tolua_S,(char*)"atZhuiMingVal",Attribute::atZhuiMingVal);
   tolua_constant(tolua_S,(char*)"atHuiXinDamage",Attribute::atHuiXinDamage);
   tolua_constant(tolua_S,(char*)"atNeiGongEx",Attribute::atNeiGongEx);
   tolua_constant(tolua_S,(char*)"atDeadLyPro",Attribute::atDeadLyPro);
   tolua_constant(tolua_S,(char*)"atDeadLyMaster",Attribute::atDeadLyMaster);
   tolua_constant(tolua_S,(char*)"atDeadLyResist",Attribute::atDeadLyResist);
   tolua_constant(tolua_S,(char*)"atAddEnemyHp",Attribute::atAddEnemyHp);
   tolua_constant(tolua_S,(char*)"atHurtMyself",Attribute::atHurtMyself);
   tolua_constant(tolua_S,(char*)"atBladeMailPro",Attribute::atBladeMailPro);
   tolua_constant(tolua_S,(char*)"atBladeMailPer",Attribute::atBladeMailPer);
   tolua_constant(tolua_S,(char*)"atDefPen",Attribute::atDefPen);
   tolua_constant(tolua_S,(char*)"atResPen",Attribute::atResPen);
   tolua_constant(tolua_S,(char*)"atDeadLyHurt",Attribute::atDeadLyHurt);
   tolua_constant(tolua_S,(char*)"atDeadLyHurtResist",Attribute::atDeadLyHurtResist);
   tolua_constant(tolua_S,(char*)"atCritHurtResist",Attribute::atCritHurtResist);
   tolua_constant(tolua_S,(char*)"atHunGuPro",Attribute::atHunGuPro);
   tolua_constant(tolua_S,(char*)"atHunGuHurt",Attribute::atHunGuHurt);
   tolua_constant(tolua_S,(char*)"atHunGuCd",Attribute::atHunGuCd);
   tolua_constant(tolua_S,(char*)"atHearthDamege",Attribute::atHearthDamege);
   tolua_constant(tolua_S,(char*)"atHearthHurt",Attribute::atHearthHurt);
   tolua_constant(tolua_S,(char*)"atHearthCount",Attribute::atHearthCount);
   tolua_constant(tolua_S,(char*)"atCount",Attribute::atCount);
   tolua_function(tolua_S,(char*)"new",tolua_server_Attribute_new00);
   tolua_function(tolua_S,(char*)"new_local",tolua_server_Attribute_new00_local);
   tolua_function(tolua_S,".call",tolua_server_Attribute_new00_local);
   tolua_function(tolua_S,(char*)"new",tolua_server_Attribute_new01);
   tolua_function(tolua_S,(char*)"new_local",tolua_server_Attribute_new01_local);
   tolua_function(tolua_S,".call",tolua_server_Attribute_new01_local);
   tolua_function(tolua_S,(char*)"Reset",tolua_server_Attribute_Reset00);
   tolua_function(tolua_S,(char*)"Add",tolua_server_Attribute_Add00);
   tolua_function(tolua_S,(char*)"Set",tolua_server_Attribute_Set00);
   tolua_function(tolua_S,(char*)"Get",tolua_server_Attribute_Get00);
   tolua_function(tolua_S,(char*)".geti",tolua_server_Attribute__geti00);
   tolua_function(tolua_S,(char*)".seti",tolua_server_Attribute__seti00);
   tolua_function(tolua_S,(char*)".geti",tolua_server_Attribute__geti01);
   tolua_function(tolua_S,(char*)"GetValues",tolua_server_Attribute_GetValues00);
   tolua_function(tolua_S,(char*)"SetExtraPower",tolua_server_Attribute_SetExtraPower00);
   tolua_function(tolua_S,(char*)"AddExtraPower",tolua_server_Attribute_AddExtraPower00);
   tolua_function(tolua_S,(char*)"GetExtraPower",tolua_server_Attribute_GetExtraPower00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ExAttribute","ExAttribute","",tolua_collect_ExAttribute);
  #else
  tolua_cclass(tolua_S,"ExAttribute","ExAttribute","",NULL);
  #endif
  tolua_beginmodule(tolua_S,(char*)"ExAttribute");
   tolua_constant(tolua_S,(char*)"eatReflectProbability",ExAttribute::eatReflectProbability);
   tolua_constant(tolua_S,(char*)"eatReflectRate",ExAttribute::eatReflectRate);
   tolua_constant(tolua_S,(char*)"eatIgnoreReflect",ExAttribute::eatIgnoreReflect);
   tolua_constant(tolua_S,(char*)"eatGodBlessProbability",ExAttribute::eatGodBlessProbability);
   tolua_constant(tolua_S,(char*)"eatGodBlessRate",ExAttribute::eatGodBlessRate);
   tolua_constant(tolua_S,(char*)"eatDeathCurseProbability",ExAttribute::eatDeathCurseProbability);
   tolua_constant(tolua_S,(char*)"eatDeathCurseDamageIncrease",ExAttribute::eatDeathCurseDamageIncrease);
   tolua_constant(tolua_S,(char*)"eatDeathCurseTime",ExAttribute::eatDeathCurseTime);
   tolua_constant(tolua_S,(char*)"eatAllCrit",ExAttribute::eatAllCrit);
   tolua_constant(tolua_S,(char*)"eatAllCritTime",ExAttribute::eatAllCritTime);
   tolua_constant(tolua_S,(char*)"eatBeHitTimesDodge",ExAttribute::eatBeHitTimesDodge);
   tolua_constant(tolua_S,(char*)"eatAttackTimesCrit",ExAttribute::eatAttackTimesCrit);
   tolua_constant(tolua_S,(char*)"eatAttackAddHpProbability",ExAttribute::eatAttackAddHpProbability);
   tolua_constant(tolua_S,(char*)"eatAttackAddHpValue",ExAttribute::eatAttackAddHpValue);
   tolua_constant(tolua_S,(char*)"eatAddToWarriorDamageInc",ExAttribute::eatAddToWarriorDamageInc);
   tolua_constant(tolua_S,(char*)"eatAddToMageDamageInc",ExAttribute::eatAddToMageDamageInc);
   tolua_constant(tolua_S,(char*)"eatAddToTaoistDamageInc",ExAttribute::eatAddToTaoistDamageInc);
   tolua_constant(tolua_S,(char*)"eatSubWarriorDamageInc",ExAttribute::eatSubWarriorDamageInc);
   tolua_constant(tolua_S,(char*)"eatSubMageDamageInc",ExAttribute::eatSubMageDamageInc);
   tolua_constant(tolua_S,(char*)"eatSubTaoistDamageInc",ExAttribute::eatSubTaoistDamageInc);
   tolua_constant(tolua_S,(char*)"eatTogetherHitFree",ExAttribute::eatTogetherHitFree);
   tolua_constant(tolua_S,(char*)"eatTogetherHitMonDamageInc",ExAttribute::eatTogetherHitMonDamageInc);
   tolua_constant(tolua_S,(char*)"eatTogetherHitRoleDamageInc",ExAttribute::eatTogetherHitRoleDamageInc);
   tolua_constant(tolua_S,(char*)"eatTogetherHitCdSub",ExAttribute::eatTogetherHitCdSub);
   tolua_constant(tolua_S,(char*)"eatAdditionalHarm",ExAttribute::eatAdditionalHarm);
   tolua_constant(tolua_S,(char*)"eatReductionHarm",ExAttribute::eatReductionHarm);
   tolua_constant(tolua_S,(char*)"eatMiss",ExAttribute::eatMiss);
   tolua_constant(tolua_S,(char*)"eatBaseSkillExArg",ExAttribute::eatBaseSkillExArg);
   tolua_constant(tolua_S,(char*)"eatMultipleCrit",ExAttribute::eatMultipleCrit);
   tolua_constant(tolua_S,(char*)"eatMultipleCritCoeff",ExAttribute::eatMultipleCritCoeff);
   tolua_constant(tolua_S,(char*)"atMultipleCritHurt",ExAttribute::atMultipleCritHurt);
   tolua_constant(tolua_S,(char*)"eatAddWarriorDamageInc",ExAttribute::eatAddWarriorDamageInc);
   tolua_constant(tolua_S,(char*)"eatAddMageDamageInc",ExAttribute::eatAddMageDamageInc);
   tolua_constant(tolua_S,(char*)"eatAddTaoistDamageInc",ExAttribute::eatAddTaoistDamageInc);
   tolua_constant(tolua_S,(char*)"eatMultipleCritTime",ExAttribute::eatMultipleCritTime);
   tolua_constant(tolua_S,(char*)"eatAttackAddHpTime",ExAttribute::eatAttackAddHpTime);
   tolua_constant(tolua_S,(char*)"eatStunTime",ExAttribute::eatStunTime);
   tolua_constant(tolua_S,(char*)"eatGodPowerCd",ExAttribute::eatGodPowerCd);
   tolua_constant(tolua_S,(char*)"eatGodPowerProbability",ExAttribute::eatGodPowerProbability);
   tolua_constant(tolua_S,(char*)"eatGodPowerDamageIncrease",ExAttribute::eatGodPowerDamageIncrease);
   tolua_constant(tolua_S,(char*)"eatHpLtAddBuffId",ExAttribute::eatHpLtAddBuffId);
   tolua_constant(tolua_S,(char*)"eatHpLtAddBuffCd",ExAttribute::eatHpLtAddBuffCd);
   tolua_constant(tolua_S,(char*)"eatHit",ExAttribute::eatHit);
   tolua_constant(tolua_S,(char*)"eatSkillVamirePro",ExAttribute::eatSkillVamirePro);
   tolua_constant(tolua_S,(char*)"eatWarriorPeakDamageInc",ExAttribute::eatWarriorPeakDamageInc);
   tolua_constant(tolua_S,(char*)"eatMagePeakDamageInc",ExAttribute::eatMagePeakDamageInc);
   tolua_constant(tolua_S,(char*)"eatTaoistPeakDamageInc",ExAttribute::eatTaoistPeakDamageInc);
   tolua_constant(tolua_S,(char*)"eatPetSkillLevel",ExAttribute::eatPetSkillLevel);
   tolua_constant(tolua_S,(char*)"eatPetAttackInc",ExAttribute::eatPetAttackInc);
   tolua_constant(tolua_S,(char*)"eatSkillAddArgA",ExAttribute::eatSkillAddArgA);
   tolua_constant(tolua_S,(char*)"eatSkillAddArgB",ExAttribute::eatSkillAddArgB);
   tolua_constant(tolua_S,(char*)"eatResistDeathCd",ExAttribute::eatResistDeathCd);
   tolua_constant(tolua_S,(char*)"eatResistDeathPro",ExAttribute::eatResistDeathPro);
   tolua_constant(tolua_S,(char*)"eatResistDeathRate",ExAttribute::eatResistDeathRate);
   tolua_constant(tolua_S,(char*)"eatCritHpLt",ExAttribute::eatCritHpLt);
   tolua_constant(tolua_S,(char*)"eatCritHpLtAddDamage",ExAttribute::eatCritHpLtAddDamage);
   tolua_constant(tolua_S,(char*)"eatMiJiKNHpPer",ExAttribute::eatMiJiKNHpPer);
   tolua_constant(tolua_S,(char*)"eatMiJiKNHpSubPer",ExAttribute::eatMiJiKNHpSubPer);
   tolua_constant(tolua_S,(char*)"eatMiJiKNDamPer",ExAttribute::eatMiJiKNDamPer);
   tolua_constant(tolua_S,(char*)"eatMiJiZHDamPer",ExAttribute::eatMiJiZHDamPer);
   tolua_constant(tolua_S,(char*)"eatMiJiZHTime",ExAttribute::eatMiJiZHTime);
   tolua_constant(tolua_S,(char*)"eatMiJiBQHpTime",ExAttribute::eatMiJiBQHpTime);
   tolua_constant(tolua_S,(char*)"eatMiJiBQHpPer",ExAttribute::eatMiJiBQHpPer);
   tolua_constant(tolua_S,(char*)"eatMiJiBQBuffId",ExAttribute::eatMiJiBQBuffId);
   tolua_constant(tolua_S,(char*)"eatAddSkillDamageInc",ExAttribute::eatAddSkillDamageInc);
   tolua_constant(tolua_S,(char*)"eatSubSkillDamageInc",ExAttribute::eatSubSkillDamageInc);
   tolua_constant(tolua_S,(char*)"eatCount",ExAttribute::eatCount);
   tolua_function(tolua_S,(char*)"new",tolua_server_ExAttribute_new00);
   tolua_function(tolua_S,(char*)"new_local",tolua_server_ExAttribute_new00_local);
   tolua_function(tolua_S,".call",tolua_server_ExAttribute_new00_local);
   tolua_function(tolua_S,(char*)"new",tolua_server_ExAttribute_new01);
   tolua_function(tolua_S,(char*)"new_local",tolua_server_ExAttribute_new01_local);
   tolua_function(tolua_S,".call",tolua_server_ExAttribute_new01_local);
   tolua_function(tolua_S,(char*)"Reset",tolua_server_ExAttribute_Reset00);
   tolua_function(tolua_S,(char*)"Add",tolua_server_ExAttribute_Add00);
   tolua_function(tolua_S,(char*)"Set",tolua_server_ExAttribute_Set00);
   tolua_function(tolua_S,(char*)"Get",tolua_server_ExAttribute_Get00);
   tolua_function(tolua_S,(char*)".seti",tolua_server_ExAttribute__seti00);
   tolua_function(tolua_S,(char*)".geti",tolua_server_ExAttribute__geti00);
   tolua_function(tolua_S,(char*)"GetValues",tolua_server_ExAttribute_GetValues00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,(char*)"TogetherHitSlotType_Qian",TogetherHitSlotType_Qian);
  tolua_constant(tolua_S,(char*)"TogetherHitSlotType_Kun",TogetherHitSlotType_Kun);
  tolua_constant(tolua_S,(char*)"TogetherHitSlotType_Zhen",TogetherHitSlotType_Zhen);
  tolua_constant(tolua_S,(char*)"TogetherHitSlotType_Xun",TogetherHitSlotType_Xun);
  tolua_constant(tolua_S,(char*)"TogetherHitSlotType_Kan",TogetherHitSlotType_Kan);
  tolua_constant(tolua_S,(char*)"TogetherHitSlotType_Li",TogetherHitSlotType_Li);
  tolua_constant(tolua_S,(char*)"TogetherHitSlotType_Gen",TogetherHitSlotType_Gen);
  tolua_constant(tolua_S,(char*)"TogetherHitSlotType_Dui",TogetherHitSlotType_Dui);
  tolua_constant(tolua_S,(char*)"TogetherHitSlotType_Max",TogetherHitSlotType_Max);
  tolua_constant(tolua_S,(char*)"aaSaft",aaSaft);
  tolua_constant(tolua_S,(char*)"aaPassPoint",aaPassPoint);
  tolua_constant(tolua_S,(char*)"aaTransfer",aaTransfer);
  tolua_constant(tolua_S,(char*)"aaAttrCount",aaAttrCount);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"RobotData","RobotData","",tolua_collect_RobotData);
  #else
  tolua_cclass(tolua_S,"RobotData","RobotData","",NULL);
  #endif
  tolua_beginmodule(tolua_S,(char*)"RobotData");
   tolua_variable(tolua_S,"actor_id",tolua_get_RobotData_actor_id,tolua_set_RobotData_actor_id);
   tolua_variable(tolua_S,"name",tolua_get_RobotData_name,tolua_set_RobotData_name);
   tolua_variable(tolua_S,"level",tolua_get_RobotData_level,tolua_set_RobotData_level);
   tolua_variable(tolua_S,"job",tolua_get_RobotData_job,tolua_set_RobotData_job);
   tolua_variable(tolua_S,"sex",tolua_get_RobotData_sex,tolua_set_RobotData_sex);
   tolua_variable(tolua_S,"clothesId",tolua_get_RobotData_clothesId,tolua_set_RobotData_clothesId);
   tolua_variable(tolua_S,"weaponId",tolua_get_RobotData_weaponId,tolua_set_RobotData_weaponId);
   tolua_variable(tolua_S,"wingOpenState",tolua_get_RobotData_wingOpenState,tolua_set_RobotData_wingOpenState);
   tolua_variable(tolua_S,"wingLevel",tolua_get_RobotData_wingLevel,tolua_set_RobotData_wingLevel);
   tolua_variable(tolua_S,"attrs",tolua_get_RobotData_attrs,tolua_set_RobotData_attrs);
   tolua_array(tolua_S,"skills",tolua_get_server_RobotData_skills,tolua_set_server_RobotData_skills);
   tolua_variable(tolua_S,"headid",tolua_get_RobotData_headid,tolua_set_RobotData_headid);
   tolua_variable(tolua_S,"holaid",tolua_get_RobotData_holaid,tolua_set_RobotData_holaid);
   tolua_variable(tolua_S,"camp",tolua_get_RobotData_camp,tolua_set_RobotData_camp);
   tolua_variable(tolua_S,"ismirror",tolua_get_RobotData_ismirror,tolua_set_RobotData_ismirror);
   tolua_function(tolua_S,(char*)"new",tolua_server_RobotData_new00);
   tolua_function(tolua_S,(char*)"new_local",tolua_server_RobotData_new00_local);
   tolua_function(tolua_S,".call",tolua_server_RobotData_new00_local);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,(char*)"LRedis",0);
  tolua_beginmodule(tolua_S,(char*)"LRedis");
   tolua_function(tolua_S,(char*)"Zadd",tolua_server_LRedis_Zadd00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"LuaSocket","LuaSocket","",NULL);
  tolua_beginmodule(tolua_S,(char*)"LuaSocket");
   tolua_function(tolua_S,(char*)"NewSocket",tolua_server_LuaSocket_NewSocket00);
   tolua_function(tolua_S,(char*)"Release",tolua_server_LuaSocket_Release00);
   tolua_function(tolua_S,(char*)"GetHostByName",tolua_server_LuaSocket_GetHostByName00);
   tolua_function(tolua_S,(char*)"send",tolua_server_LuaSocket_send00);
   tolua_function(tolua_S,(char*)"connect",tolua_server_LuaSocket_connect00);
   tolua_function(tolua_S,(char*)"readline",tolua_server_LuaSocket_readline00);
   tolua_function(tolua_S,(char*)"readall",tolua_server_LuaSocket_readall00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 int luaopen_server (lua_State* tolua_S) {
 return tolua_server_open(tolua_S);
};
#endif

