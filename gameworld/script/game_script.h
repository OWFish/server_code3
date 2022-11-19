#ifndef _GAME_SCRIPT_H_
#define _GAME_SCRIPT_H_

class Entity;

class GameScript :
	public BaseScript
{
public:
	typedef BaseScript Inherited;

	/* �ű��������ActorPacketָ�룬����ָ���Ա��ڽ�ɫ�������ݰ�����ֽű�����Ӷ��޷�flush���ݰ���ʱ��������ݰ���
	   ����ű����������ݰ�û�б����գ���ᵼ��������Ϸ����ʹ˲�����������
	*/
	static struct ActorPacket* ScriptActorPacket;

public:
	GameScript();
	~GameScript();

#ifdef _DEBUG
	/*
	* Comments: ����ű�������������ͳ�����ݵ��ļ�
	* Param const char* sFilePath:
	* @Return void:
	*/
	void SaveProfiler(const char* sFilePath);

#endif

	void SetEntity(Entity* et)
	{
		npc_ptr_ = et;
	}
protected:
	/* ���к�����Ϊ���Ǹ������ش����� */
	//�����ű������
	virtual lua_State* createLuaVM();
	//ע�᱾�غ����⡣����true��ʾ�ɹ���
	virtual bool registLocalLibs();
	//���ýű��ĳ�ʼ����������������true��ʾû�д�����������δ�ṩ���ó�ʼ��������ʵ�ʹ��ܡ�
	virtual bool onCallInit();
	//���ýű���ж�غ�������������true��ʾû�д�����������δ�ṩ����ж�غ�����ʵ�ʹ��ܡ�
	virtual bool onCallFinal();
	// cal����ִ����ִ�����
	virtual void onCallEnd(bool ret);
	// ��ʾ������Ϣ�ͱ��ͺ�̨
	virtual void showError(const char* err);
private:
	//�Ѵ�����Ϣ��¼����־��
	void logError(const char* sError);

protected:
	Entity*			npc_ptr_;	//�ű����������Ľ�ɫ��������NPC����
#ifdef _DEBUG
	LuaProfiler		m_Profiler;		//�ű�������������ͳ��
#endif
};

#endif
