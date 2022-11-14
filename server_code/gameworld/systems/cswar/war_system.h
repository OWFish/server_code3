#ifndef WAR_SYSTEM_H
#define WAR_SYSTEM_H

// ���սϵͳ
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

	int GetIntValue(const char* key, int def/* = 0*/);//���ʽű�����
public:

	CLVariant& GetVar()
	{
		return lua_var_;
	}


private:
	Actor		*actor_;

	CLVariant lua_var_;//������
	ActorCsData			srv_data_;	// �������������ͨ���������õ�����
	bool is_loaded_;   //���ݿ���Ϣ�Ƿ��Ѿ�����
	std::string db_buf_; ////�ְ���buf
	std::vector<bool> buf_index_;
};

#endif

