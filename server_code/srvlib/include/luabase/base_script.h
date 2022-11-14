#ifndef _ROBOT_SCRIPT_H_
#define _ROBOT_SCRIPT_H_

class BaseScript :
	public BaseLua
{
public:
	typedef BaseLua Inherited;
	typedef misc::RefObject<LuaPreProcessor::LineRangeList> SourceLineList;

	//�ű���ʼ����������
	static const char* ScriptInitFnName;
	//�ű�������������
	static const char* ScriptUninitFnName;
	//��ű��б���˽ű�����ָ�������
	static const char* ScriptInstanceKeyName;
public:
	BaseScript();
	~BaseScript();
	
	/* ���ýű�����������ű����óɹ�����������true�����򷵻�false��
	 * �����ýű�ʧ��ʱ����������false���ڷ���ֵ�б��д洢1�������������ݵ��ַ���ֵ
	 * args				�ű������б�
	 * results			�ű�����ֵ�б�
	 * nResultCount		�����ķ���ֵ������LUA_MULTRET��ʾ������
	 */
	virtual bool Call(const char* fn, ScriptValueList *args, ScriptValueList *results, int ret_count = LUA_MULTRET);
	
	bool LoadScript(const char* fn);

	void SetVspDef(CVSPDefinition* vsp);
	/*
	* Comments: ���Ǹ������ýű����ݵĺ��������ӶԴ���ԭʼ�м�¼���ı���
	* Param const char* sText:
	* Param const CSourceLineList * pLRList:
	* @Return bool:
	*/
	bool setScript(const char* sText, SourceLineList* pLRList);
protected:
	//�ű����ô�������ɺ���
	static int ScriptCallErrorDispatcher(lua_State *L);

	virtual void ScriptCallError(const char* sFnName);
	virtual int HandleCallError();
	virtual lua_State* createLuaVM();
	virtual bool openBaseLibs();
	virtual bool registLocalLibs();
	virtual bool callInit();
	virtual bool onCallInit();
	virtual bool callFinal();
	virtual bool onCallFinal();
	virtual void showError(const char* err);
	virtual void onCallEnd(bool ret);
protected:
	SourceLineList		src_;		//ԭʼ�����м�¼�����ڻ�ȡ����ȷ�ĺ�������λ��
	CVSPDefinition*		vsp_;
};

#endif

