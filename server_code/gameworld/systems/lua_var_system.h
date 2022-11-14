#ifndef _ACTOR_LUA_VAR_SYSTEM_H_
#define _ACTOR_LUA_VAR_SYSTEM_H_

/************************************************************************
*                           角色动态变量子系统
*   角色动态变量主要用于向脚本提供存放角色数据。这些数据也可以直接被C++读取和修改
************************************************************************/

class Actor;
class LuaVarSystem //:
//	public EntitySystem<enActorVarSystemID, LuaVarSystem, Actor>
{
public:
	//typedef EntitySystem<enActorVarSystemID, LuaVarSystem, Actor> Inherited;

public:
	LuaVarSystem(Actor* actor);
	~LuaVarSystem();

	//获取变量对象
	inline CLVariant& GetVar() { return lua_var_; }

	// 按key获取整数数据
	int GetIntValue(const char* key, int def = 0);
	// 按key设置整数数据
	void SetIntValue(const char* key, int value);

	//处理DB数据
	void Init(DataPacketReader& reader);
	//存盘
	void Save(ActorBasicData* pData);

protected:
	Actor		*actor_;
	CLVariant	lua_var_;//根变量
	bool		is_loaded_;;
	std::string db_buf_; ////分包的buf
	std::vector<bool> buf_index_;
};
#endif

