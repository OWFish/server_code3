#ifndef _NPC_H_
#define _NPC_H_

class Npc:
	public Entity
{
public:
	typedef Entity Inherited;

public:
	Npc();
	virtual ~Npc() {}

	void InitNPCAi();

	//��ʼ��
	bool Init(void* data, size_t size)
	{
		return Inherited::Init(data, size);
	}
	//ɾ����һЩ�ڴ����Ĳ���

	//����LogicRun��ʵ�ֶԽű����ڴ涨ʱ����
	void LogicRun(int64_t curr_t);
	virtual int GetId() { return 0; } // todo ����û�ã� npc��Ҫ�ع�
public:
	//inline void SetConfig(NpcConfig* conf) { conf_ = conf; }
	//inline NpcConfig* GetConfig() { return conf_; }
	/*
	* Comments: �û���NPC�Ի���ִ��ָ���ĺ���������ű����������ַ�������ô�ű�����ֵ�������ͻ��˳���
	* Param Actor* pActor: �Ի�����Ҷ���
	* Param const char* sFnName: ��������
	* @Return void:
	*/
	void Talk(Actor* pActor, const char* sFnName);

	void Talk(Actor* pActor, const char* sFnName, ScriptValueList& va);

	//�û����NPC�Ĵ�������Ĭ���ǵ���main����
	inline void Click(Actor* actor)
	{
		Talk(actor, "npcMain");
	}

	//������Ϣ���ر�npc�ĶԻ�����
	//void CloseDialog(Actor* pActor);

	/*
	* Comments: NPC����
	* @Return void:
	*/
	void NPCTalk();

	/*
	* Comments: ����ˢһ��ű�
	* @Return void:
	* @Remark: ���Ӵ˽ӿ���������ˢһ��NPC�ű�����Ҫ���NPC���á����ǵ���ǰ�Ѿ������ڲ�׶Σ���֤�ȶ���Ϊ�����Ժ���Կ���
	*		   ����reloadScript������call Uninitialize��Initialize�ӿڡ�
	*/
	virtual void ResetScript();

	/*
	* Comments: ͨ��������NPC�����ֻ�ȡNPC��ָ��
	* Param char * sSceneName:����������
	* Param char * sNpcName:npc������
	* @Return CNpc *:����NPC��ָ��
	*/
	static Npc* GetNpcPtr(char* sSceneName, char* sNpcName);
protected:
	/*
	* Comments:�����Ĳ�������Լ���ĸ�ʽΪ��������,����1������2���������Ժ�va �а�������1������2
	* Param const char*  str:����ĺ��������� ��ʽΪ��������,����1������2
	* Param CScriptValueList & va: �����б�
	* Param char *  & pFunc:����������
	* Param nOutBuffSize: pFunc����ַ�������ĳ���
	* @Return void:
	*/
	void FuncParamProcess(const char*  str, char* pFunc, int nOutBuffSize, ScriptValueList& va);

//protected:
	//npcConfig*		conf_;			//npc��������Ϣ
};

#endif

