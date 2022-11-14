#ifndef _ACTOR_LUA_VAR_SYSTEM_H_
#define _ACTOR_LUA_VAR_SYSTEM_H_

/************************************************************************
*                           ��ɫ��̬������ϵͳ
*   ��ɫ��̬������Ҫ������ű��ṩ��Ž�ɫ���ݡ���Щ����Ҳ����ֱ�ӱ�C++��ȡ���޸�
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

	//��ȡ��������
	inline CLVariant& GetVar() { return lua_var_; }

	// ��key��ȡ��������
	int GetIntValue(const char* key, int def = 0);
	// ��key������������
	void SetIntValue(const char* key, int value);

	//����DB����
	void Init(DataPacketReader& reader);
	//����
	void Save(ActorBasicData* pData);

protected:
	Actor		*actor_;
	CLVariant	lua_var_;//������
	bool		is_loaded_;;
	std::string db_buf_; ////�ְ���buf
	std::vector<bool> buf_index_;
};
#endif

