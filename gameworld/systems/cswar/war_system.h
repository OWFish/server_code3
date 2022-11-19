#ifndef WAR_SYSTEM_H
#define WAR_SYSTEM_H

// 跨服战系统
class Actor;
class WarSystem 
{

public:
	WarSystem(Actor* actor);
	virtual ~WarSystem();

public:
	void InitLuaVar(DataPacketReader& reader);
	bool LoadCsData(void* pData, size_t size);
	virtual void Save();
	void SaveCsData();
	void SaveVar();

	int GetIntValue(const char* key, int def/* = 0*/);//访问脚本变量
public:

	CLVariant& GetVar()
	{
		return lua_var_;
	}


private:
	Actor		*actor_;

	CLVariant lua_var_;//根变量
	ActorCsData			srv_data_;	// 跨服服务器和普通服务器共用的数据
	bool is_loaded_;   //数据库信息是否已经加载
	std::string db_buf_; ////分包的buf
	std::vector<bool> buf_index_;
};

#endif

