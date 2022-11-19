#ifndef _LUA_VARIANT_CLASS_H_
#define _LUA_VARIANT_CLASS_H_

/************************************************************************
*              基于BaseCLVClass类实现方式的LuaVariantClass导出类
************************************************************************/
class LuaVariantClass :
	public BaseCLVClass<CLVariant, LuaVariantClass>
{
public:
	typedef BaseCLVClass<CLVariant, LuaVariantClass> Inherited;

protected:
	CLVariant* create(lua_State *L);
	void destroy(lua_State *L, CLVariant *ptr);
	int get(lua_State *L, CLVariant *pInst);
	int set(lua_State *L, CLVariant *pInst);
	int eq(lua_State *L, CLVariant *pInst);
	int add(lua_State *L, CLVariant *pInst);
	int sub(lua_State *L, CLVariant *pInst);
	int mul(lua_State *L, CLVariant *pInst);
	int div(lua_State *L, CLVariant *pInst);
	int mod(lua_State *L, CLVariant *pInst);
	int unm(lua_State *L, CLVariant *pInst);
	int len(lua_State *L, CLVariant *pInst);
	int lt(lua_State *L, CLVariant *pInst);
	int le(lua_State *L, CLVariant *pInst);
	int concat(lua_State *L, CLVariant *pInst);
	int testCall(lua_State *L, CLVariant *pInst);
private:
	void setVarFromTable(lua_State *L, CLVariant *pVar, int vidx = -1);
	void setVarMember(lua_State *L, CLVariant *pVar, const char* sName, int vidx = -1);

private:
	static const FuncCall fnList[];
public:
	LuaVariantClass();
};


#endif

