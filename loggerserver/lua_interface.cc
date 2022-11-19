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

#include "stdafx.h"
#include "logger_exp.h"
#include "lua_data_packet.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* function: print */
#ifndef TOLUA_DISABLE_tolua_server_print00
static int tolua_server_print00(lua_State* tolua_S)
{
	return print(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: logger::getDate */
#ifndef TOLUA_DISABLE_tolua_server_logger_getDate00
static int tolua_server_logger_getDate00(lua_State* tolua_S)
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
  int year = ((int)  tolua_tonumber(tolua_S,1,0));
  int month = ((int)  tolua_tonumber(tolua_S,2,0));
  int day = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   logger::getDate(year,month,day);
   tolua_pushnumber(tolua_S,(lua_Number)year);
   tolua_pushnumber(tolua_S,(lua_Number)month);
   tolua_pushnumber(tolua_S,(lua_Number)day);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getDate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: logger::getDateStr */
#ifndef TOLUA_DISABLE_tolua_server_logger_getDateStr00
static int tolua_server_logger_getDateStr00(lua_State* tolua_S)
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
   const char* tolua_ret = (const char*)  logger::getDateStr();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'getDateStr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: logger::exeSql */
#ifndef TOLUA_DISABLE_tolua_server_logger_exeSql00
static int tolua_server_logger_exeSql00(lua_State* tolua_S)
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
   int tolua_ret = (int)  logger::exeSql(db_connection,sql);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'exeSql'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: logger::urlEncode */
#ifndef TOLUA_DISABLE_tolua_server_logger_urlEncode00
static int tolua_server_logger_urlEncode00(lua_State* tolua_S)
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
  const char* msg = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  logger::urlEncode(msg);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'urlEncode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: logger::sendToScribe */
#ifndef TOLUA_DISABLE_tolua_server_logger_sendToScribe00
static int tolua_server_logger_sendToScribe00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int serverId = ((int)  tolua_tonumber(tolua_S,1,0));
  const char* para = ((const char*)  tolua_tostring(tolua_S,2,""));
  bool final = ((bool) (tolua_toboolean(tolua_S,3,true)!=0));
  const char* key = ((const char*)  tolua_tostring(tolua_S,4,"0948e5fa35a91677a2d8d8e7527ee461"));
  {
   logger::sendToScribe(serverId,para,final,key);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'sendToScribe'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DataPack::allocPacket */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_allocPacket00
static int tolua_server_DataPack_allocPacket00(lua_State* tolua_S)
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
   void* tolua_ret = (void*)  DataPack::allocPacket();
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,(char*)"#ferror in function 'allocPacket'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DataPack::getAvaliableLength */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_getAvaliableLength00
static int tolua_server_DataPack_getAvaliableLength00(lua_State* tolua_S)
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
   int tolua_ret = (int)  DataPack::getAvaliableLength(p);
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

/* function: DataPack::getLength */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_getLength00
static int tolua_server_DataPack_getLength00(lua_State* tolua_S)
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
   int tolua_ret = (int)  DataPack::getLength(p);
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

/* function: DataPack::writeString */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_writeString00
static int tolua_server_DataPack_writeString00(lua_State* tolua_S)
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
   DataPack::writeString(p,str);
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

/* function: DataPack::readString */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_readString00
static int tolua_server_DataPack_readString00(lua_State* tolua_S)
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
   char* tolua_ret = (char*)  DataPack::readString(p);
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

/* function: DataPack::readByte */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_readByte00
static int tolua_server_DataPack_readByte00(lua_State* tolua_S)
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
   unsigned char tolua_ret = (unsigned char)  DataPack::readByte(p);
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

/* function: DataPack::readChar */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_readChar00
static int tolua_server_DataPack_readChar00(lua_State* tolua_S)
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
   char tolua_ret = (char)  DataPack::readChar(p);
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

/* function: DataPack::readWord */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_readWord00
static int tolua_server_DataPack_readWord00(lua_State* tolua_S)
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
   unsigned short tolua_ret = (unsigned short)  DataPack::readWord(p);
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

/* function: DataPack::readShort */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_readShort00
static int tolua_server_DataPack_readShort00(lua_State* tolua_S)
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
   short tolua_ret = (short)  DataPack::readShort(p);
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

/* function: DataPack::readInt */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_readInt00
static int tolua_server_DataPack_readInt00(lua_State* tolua_S)
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
   int tolua_ret = (int)  DataPack::readInt(p);
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

/* function: DataPack::readUInt */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_readUInt00
static int tolua_server_DataPack_readUInt00(lua_State* tolua_S)
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
   unsigned int tolua_ret = (unsigned int)  DataPack::readUInt(p);
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

/* function: DataPack::readUint64 */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_readUint6400
static int tolua_server_DataPack_readUint6400(lua_State* tolua_S)
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
   double tolua_ret = (double)  DataPack::readUint64(p);
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

/* function: DataPack::readInt64 */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_readInt6400
static int tolua_server_DataPack_readInt6400(lua_State* tolua_S)
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
   double tolua_ret = (double)  DataPack::readInt64(p);
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

/* function: DataPack::readData */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_readData00
static int tolua_server_DataPack_readData00(lua_State* tolua_S)
{
	return DataPack::readData(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: DataPack::writeByte */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_writeByte00
static int tolua_server_DataPack_writeByte00(lua_State* tolua_S)
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
  unsigned char btValue = ((unsigned char)  tolua_tonumber(tolua_S,2,0));
  {
   DataPack::writeByte(p,btValue);
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

/* function: DataPack::writeChar */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_writeChar00
static int tolua_server_DataPack_writeChar00(lua_State* tolua_S)
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
  char cValue = ((char)  tolua_tonumber(tolua_S,2,0));
  {
   DataPack::writeChar(p,cValue);
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

/* function: DataPack::writeWord */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_writeWord00
static int tolua_server_DataPack_writeWord00(lua_State* tolua_S)
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
  unsigned short wValue = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
  {
   DataPack::writeWord(p,wValue);
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

/* function: DataPack::writeShort */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_writeShort00
static int tolua_server_DataPack_writeShort00(lua_State* tolua_S)
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
  short wValue = ((short)  tolua_tonumber(tolua_S,2,0));
  {
   DataPack::writeShort(p,wValue);
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

/* function: DataPack::writeInt */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_writeInt00
static int tolua_server_DataPack_writeInt00(lua_State* tolua_S)
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
  int nValue = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   DataPack::writeInt(p,nValue);
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

/* function: DataPack::writeUInt */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_writeUInt00
static int tolua_server_DataPack_writeUInt00(lua_State* tolua_S)
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
  unsigned int uValue = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   DataPack::writeUInt(p,uValue);
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

/* function: DataPack::writeUint64 */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_writeUint6400
static int tolua_server_DataPack_writeUint6400(lua_State* tolua_S)
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
  double value = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   DataPack::writeUint64(p,value);
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

/* function: DataPack::writeInt64 */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_writeInt6400
static int tolua_server_DataPack_writeInt6400(lua_State* tolua_S)
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
  double value = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   DataPack::writeInt64(p,value);
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

/* function: DataPack::writeData */
#ifndef TOLUA_DISABLE_tolua_server_DataPack_writeData00
static int tolua_server_DataPack_writeData00(lua_State* tolua_S)
{
	return DataPack::writeData(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
int tolua_server_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_function(tolua_S,(char*)"print",tolua_server_print00);
  tolua_module(tolua_S,(char*)"logger",0);
  tolua_beginmodule(tolua_S,(char*)"logger");
   tolua_function(tolua_S,(char*)"getDate",tolua_server_logger_getDate00);
   tolua_function(tolua_S,(char*)"getDateStr",tolua_server_logger_getDateStr00);
   tolua_function(tolua_S,(char*)"exeSql",tolua_server_logger_exeSql00);
   tolua_function(tolua_S,(char*)"urlEncode",tolua_server_logger_urlEncode00);
   tolua_function(tolua_S,(char*)"sendToScribe",tolua_server_logger_sendToScribe00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,(char*)"dtByte",dtByte);
  tolua_constant(tolua_S,(char*)"dtChar",dtChar);
  tolua_constant(tolua_S,(char*)"dtWord",dtWord);
  tolua_constant(tolua_S,(char*)"dtShort",dtShort);
  tolua_constant(tolua_S,(char*)"dtInt",dtInt);
  tolua_constant(tolua_S,(char*)"dtUint",dtUint);
  tolua_constant(tolua_S,(char*)"dtInt64",dtInt64);
  tolua_constant(tolua_S,(char*)"dtUint64",dtUint64);
  tolua_constant(tolua_S,(char*)"dtString",dtString);
  tolua_module(tolua_S,(char*)"DataPack",0);
  tolua_beginmodule(tolua_S,(char*)"DataPack");
   tolua_function(tolua_S,(char*)"allocPacket",tolua_server_DataPack_allocPacket00);
   tolua_function(tolua_S,(char*)"getAvaliableLength",tolua_server_DataPack_getAvaliableLength00);
   tolua_function(tolua_S,(char*)"getLength",tolua_server_DataPack_getLength00);
   tolua_function(tolua_S,(char*)"writeString",tolua_server_DataPack_writeString00);
   tolua_function(tolua_S,(char*)"readString",tolua_server_DataPack_readString00);
   tolua_function(tolua_S,(char*)"readByte",tolua_server_DataPack_readByte00);
   tolua_function(tolua_S,(char*)"readChar",tolua_server_DataPack_readChar00);
   tolua_function(tolua_S,(char*)"readWord",tolua_server_DataPack_readWord00);
   tolua_function(tolua_S,(char*)"readShort",tolua_server_DataPack_readShort00);
   tolua_function(tolua_S,(char*)"readInt",tolua_server_DataPack_readInt00);
   tolua_function(tolua_S,(char*)"readUInt",tolua_server_DataPack_readUInt00);
   tolua_function(tolua_S,(char*)"readUint64",tolua_server_DataPack_readUint6400);
   tolua_function(tolua_S,(char*)"readInt64",tolua_server_DataPack_readInt6400);
   tolua_function(tolua_S,(char*)"readData",tolua_server_DataPack_readData00);
   tolua_function(tolua_S,(char*)"writeByte",tolua_server_DataPack_writeByte00);
   tolua_function(tolua_S,(char*)"writeChar",tolua_server_DataPack_writeChar00);
   tolua_function(tolua_S,(char*)"writeWord",tolua_server_DataPack_writeWord00);
   tolua_function(tolua_S,(char*)"writeShort",tolua_server_DataPack_writeShort00);
   tolua_function(tolua_S,(char*)"writeInt",tolua_server_DataPack_writeInt00);
   tolua_function(tolua_S,(char*)"writeUInt",tolua_server_DataPack_writeUInt00);
   tolua_function(tolua_S,(char*)"writeUint64",tolua_server_DataPack_writeUint6400);
   tolua_function(tolua_S,(char*)"writeInt64",tolua_server_DataPack_writeInt6400);
   tolua_function(tolua_S,(char*)"writeData",tolua_server_DataPack_writeData00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 int luaopen_server (lua_State* tolua_S) {
 return tolua_server_open(tolua_S);
};
#endif

