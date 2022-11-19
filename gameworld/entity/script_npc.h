#ifndef _SCRIPT_NPC_H_
#define _SCRIPT_NPC_H_

// �˺꿪�����ڿ����Ƿ�ʹ�û����Lua�������ֽ�����������NPC�����ٶ�
// �رմ˺��ֱ�Ӽ��ؽű��ļ� 
//#define USE_LUA_BIN_CODE // Ȼ����û���õ�����Ϊconf_�ǿ�

class ScriptNpc : public Npc
{
	typedef Npc Inherited;
public:
	ScriptNpc();
	virtual ~ScriptNpc() {}

public:
	//��ʼ��
	bool Init(void* data, size_t size)
	{
		return Inherited::Init(data, size);
	}
	//ɾ����һЩ�ڴ����Ĳ���
	void OnDestroy();

	//����LogicRun��ʵ�ֶԽű����ڴ涨ʱ����
	void LogicRun(int64_t curr_t);

	virtual void ResetScript();

	//��ȡ�ű�����
	inline GameScript& GetScript()
	{
		return script_;
	}
	/*
	* Comments: ����/���¼���NPC�ű�
	* Param const char* sPath: �ű��ļ�·���������Ǿ���·������ڳ�������Ŀ¼�����·��
	* Param bool boReload:�Ƿ����¶�ȡ
	* @Return bool: ���ؼ��ؽű��Ƿ�ɹ�
	*/
	bool LoadScript(const char* sPath = NULL, bool boReload = false);

	//����npc�ű���һ������
	bool Call(const char* sFnName);

private:
	GameScript		script_;		//�ű�����
	Timer			script_gc_timer_;	//�ű������ռ���ʱ������̬ʱ�䣩

	//Optimization
	size_t			script_len_;	// �ű��ĳ��ȣ������ڷ����ı���ʱ��Ƶ��resize�ڴ�
};

#endif