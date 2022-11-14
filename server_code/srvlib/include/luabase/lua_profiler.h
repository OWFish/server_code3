#ifndef _LUA_PROFILER_H_
#define _LUA_PROFILER_H_

/************************************************************************
*
*                    LUA �ű�������������ͳ����
*
*    ����ͨ��lua_hook�ķ�ʽʵ���˼�¼��ͳ�ƽű��к�������ʱ�����ĵĹ��ܡ��Ժ�������ʱ��
* ���ĵ�Ĭ�ϼ��㷽ʽΪ���㺯������ǰ����úõ�ʱ����������ܱȽϴ󣬵������ҳ�����
* ���ĵ�ʱ��ϴ�ĺ�����ͬʱʵ���˽�ͳ����Ϣ����Ϊ�ı����Ĺ��ܣ�Ĭ�ϵ������ʽΪ����ͳ����
* Ϣ��
*
*    ����ͨ���������ಢ����HandleDebugHook����������ʵ�ֶԺ���������Ϣ�ļ�¼�����ܵ�ͳ
* �ƹ���
*
*    ����ͨ���������ಢ����Save����������ʵ�ֶ�ͳ����Ϣ����Ϊ�ı����������ʽ��
*
************************************************************************/

class LuaProfiler
{
public:
	typedef misc::RefObject<LuaPreProcessor::LineRangeList> SourceLineList;

public:
	LuaProfiler();
	virtual ~LuaProfiler();

	/*
	* Comments:��������ͳ�ƶ���
	* Param lua_State * L:
	* Param CSourceLineList * pLRList: ����ȡ��
	* @Return bool:���Ŀ������Ѿ�����װ������ͳ�ƣ���������false
	*/
	bool SetState(lua_State* L, SourceLineList* pLRList = NULL);
	/*
	* ��������������ͳ�Ʊ��浽����
	* ��������������д������ֽ�
	*/
	size_t Save(stream::BaseStream& stm);
	/*
	* Comments: ��ȡ����ʱ�����һ������ջ��ʱ��
	* @Return int64_t:
	*/
	int64_t GetMaxTotalTime();

protected:
	//��lua�д洢��ǰ����ͳ�Ƶ����������ֵ����
	static const char PerStaticDebuggerName[];
	//��̬hook������
	static void StaticCallTimeHook(lua_State* L, lua_Debug* ar);

protected:
	/** �������HOOK�ص� **/
	virtual void HandleDebugHook(lua_State* L, lua_Debug* ar);
public:
	/** Lua�����������ܼ�¼ **/
	class LuaCallRcd
	{
	public:
		char		sName[40];		//��������
		int			nLineNo;		//�к�
		int64_t		dwLastTime;	//�ϴε���ʱ��
		int64_t		dwMaxTime;		//������ʱ��
		int64_t		dwMinTime;		//��С����ʱ��
		int64_t		dwCallCount;	//���ô���
		int64_t		dwTotalTime;	//�������ܼƵ��ú�ʱ
		void*		pSubCallList;	//�Ӽ����ú���������ΪSubCallTable
	public:
		~LuaCallRcd();
	};
	//�Ӽ����ú�����
	typedef StrHashTable<LuaCallRcd> SubCallTable;
	//��ǰ���ö�ջ��
	typedef container::Vector<LuaCallRcd*> CallStack;

protected:
	lua_State*		lua_;
	CallStack		callStack_;		//��ǰ���ö�ջ
	SubCallTable	rootCallTable_;	//�����ü�¼��
	int64_t			igoreRecordTime_;//�ڱ��溯���������ܼ�¼ʱ������ʱ����ڴ�ֵ�ļ�¼
	SourceLineList	LRList_;//�з�Χ��¼�������ڸ�ʽ������ͳ��ʱȡ�ô�����ļ������к�
};

#endif
